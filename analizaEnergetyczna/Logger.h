#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger {
public:
    Logger(const std::string& filename);
    ~Logger();
    void log(const std::string& message);

private:
    std::ofstream logFile;
};

// Declare global logger instances
extern Logger logger;
extern Logger loggerError;

// Declare global counter for loggerError executions
extern int loggerErrorCount;

#endif // LOGGER_H
