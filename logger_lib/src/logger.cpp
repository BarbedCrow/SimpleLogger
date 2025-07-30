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

    _messageQueue.enqueue(formatString(level, message));

    _writerCv.notify_one();
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
    std::string message;
    std::string buffer;

    const size_t bufferThreshold = 4096;  // symbols
    const size_t msgThreshold = 20;       // messages
    size_t currMsgThreshold = msgThreshold;
    const auto writeInterval = std::chrono::milliseconds(100);
    auto lastWrite = std::chrono::steady_clock::now();

    while (_isRunning) {
        bool hasDequeued = false;
        while (_messageQueue.try_dequeue(message)) {
            hasDequeued = true;
            buffer += message;
            if (buffer.size() > bufferThreshold || --currMsgThreshold == 0) {
                _output.write(buffer.data(), buffer.size());
                buffer.clear();
                currMsgThreshold = msgThreshold;
                lastWrite = std::chrono::steady_clock::now();
            }
        }

        const auto now = std::chrono::steady_clock::now();
        if (!buffer.empty() && (now - lastWrite) >= writeInterval) {
            _output.write(buffer.data(), buffer.size());
            buffer.clear();
            currMsgThreshold = msgThreshold;
            lastWrite = now;
        }

        std::unique_lock<std::mutex> lock(_writerCvMutex);
        _writerCv.wait_for(lock, std::chrono::milliseconds(10), [this]() { return !_isRunning; });
    }

    message = "";
    while (_messageQueue.try_dequeue(message)) {
        buffer += message;
    }
    if (!buffer.empty()) {
        _output.write(buffer.data(), buffer.size());
    }

    _output.flush();
}

void Logger::cleanup() {
    if (_output.is_open()) {
        _output.flush();
        _output.close();
    }
}
}  // namespace SLog
