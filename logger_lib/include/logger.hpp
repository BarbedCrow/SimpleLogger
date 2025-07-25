#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <fstream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

namespace SLog {
enum class LogLevel { DEBUG, INFO, WARNING, ERROR };

class Logger {
  public:
    Logger(const std::string filePath, bool clearFile = true, LogLevel minLogLevel = LogLevel::DEBUG);
    ~Logger();

    void log(LogLevel level, const char* message);

    void debug(const char* message);
    void info(const char* message);
    void warning(const char* message);
    void error(const char* message);

  private:
    void cleanup();
    void writerThreadUpdate();

  private:
    LogLevel _minLogLevel = LogLevel::DEBUG;

    std::ofstream _output;
    std::atomic<bool> _isValid = false;
    std::atomic<bool> _isRunning = false;

    std::queue<std::string> _messageQueue;
    std::mutex _logMutex;
    std::condition_variable _shouldWriteCond;
    std::thread _writerThread;
};
}  // namespace SLog
