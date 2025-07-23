#include "logger.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace SLog {
namespace {
const char* levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

std::string getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_point = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::ostringstream oss;

    // Cross-platform thread-safe time formatting
    std::tm tm_buf{};
#ifdef _WIN32
    localtime_s(&tm_buf, &time_point);
#else
    localtime_r(&time_point, &tm_buf);
#endif

    oss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S");
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}
}  // namespace

Logger::Logger(const std::string filePath, bool clearFile, LogLevel minLogLevel)
    : _minLogLevel(minLogLevel), _isRunning(true) {
    auto flags = std::ios::binary;
    if (!clearFile) {
        flags |= std::ios::app;
    }
    _output = std::ofstream(filePath, flags);
    _isValid = _output.is_open();
    if (!_isValid) {
        std::cerr << "Failed to open a file " << filePath << std::endl;
        return;
    }

    _writerThread = std::thread(&Logger::writerThreadUpdate, this);
}

Logger::~Logger() {
    _isRunning = false;
    _shouldWriteCond.notify_one();
    if (_writerThread.joinable()) {
        _writerThread.join();
    }
    cleanup();
}

std::string formatString(LogLevel level, const char* message) {
    std::ostringstream oss;
    oss << "[" << getTimestamp() << "] " << "[" << levelToString(level) << "] " << message << '\n';
    return oss.str();
}

void Logger::log(LogLevel level, const char* message) {
    if (!_isValid) {
        std::cerr << "Output file wasn't open correctly. See the details above." << std::endl;
        return;
    }

    if (level < _minLogLevel) {
        return;
    }

    auto formattedMessage = formatString(level, message);
    std::lock_guard<std::mutex> lock(_logMutex);
    _messageQueue.push(formattedMessage);
    _shouldWriteCond.notify_one();
}

void Logger::debug(const char* message) {
    log(LogLevel::DEBUG, message);
}

void Logger::info(const char* message) {
    log(LogLevel::INFO, message);
}

void Logger::warning(const char* message) {
    log(LogLevel::WARNING, message);
}

void Logger::error(const char* message) {
    log(LogLevel::ERROR, message);
}

void Logger::writerThreadUpdate() {
    while (_isRunning) {
        std::unique_lock<std::mutex> lock(_logMutex);
        _shouldWriteCond.wait(lock, [&] { return !_messageQueue.empty() || !_isRunning; });

        while (!_messageQueue.empty()) {
            auto message = _messageQueue.front();
            _messageQueue.pop();
            _output << message;
            if (_output.fail()) {
                std::cerr << "Failed to log a message." << std::endl;
                return;
            }
        }
        _output.flush();
    }
}

void Logger::cleanup() {
    if (_output.is_open()) {
        _output.close();
    }
}
}  // namespace SLog
