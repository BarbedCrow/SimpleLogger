#pragma once

#include <fstream>
#include <string>

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

  private:
    std::ofstream _output;
    std::atomic<bool> _isValid = false;
    LogLevel _minLogLevel = LogLevel::DEBUG;
};
}  // namespace SLog
