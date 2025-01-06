#include "Logger.h"
#include <iomanip>
#include <ctime>
#include <cstdio>
#include <sstream>

// Define global logger instances
Logger logger("log");
Logger loggerError("log_error");

Logger::Logger(const std::string& filename) {
    auto t = std::time(nullptr);
    std::tm tm;
    localtime_s(&tm, &t);
    std::ostringstream oss;
    oss << filename << "_" << std::put_time(&tm, "%d%m%Y_%H%M%S") << ".txt";
    std::string datedFilename = oss.str();

    if (std::remove(datedFilename.c_str()) != 0) {
        // File does not exist or could not be deleted
    }
    logFile.open(datedFilename, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Unable to open log file");
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const std::string& message) {
    if (logFile.is_open()) {
        auto t = std::time(nullptr);
        std::tm tm;
        localtime_s(&tm, &t);
        logFile << std::put_time(&tm, "%d.%m.%Y %H:%M:%S") << " " << message << std::endl;
    }
}
