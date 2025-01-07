/// \file Logger.cpp
/// \brief Implementacja klasy Logger do obs³ugi logowania komunikatów.

#include "Logger.h"
#include <iomanip>
#include <ctime>
#include <cstdio>
#include <sstream>

/// \var logger
/// \brief Globalny logger dla standardowych komunikatów.
Logger logger("log");

/// \var loggerError
/// \brief Globalny logger dla komunikatów b³êdów.
Logger loggerError("log_error");

/// \var loggerErrorCount
/// \brief Licznik wyst¹pieñ b³êdów logowanych przez loggerError.
int loggerErrorCount = 0;

/// \brief Konstruktor klasy Logger.
/// \details Tworzy plik logu z unikaln¹ nazw¹ opart¹ na aktualnej dacie i godzinie.
/// \param filename Nazwa podstawowa pliku logu.
Logger::Logger(const std::string& filename) {
    auto t = std::time(nullptr);
    std::tm tm;
    localtime_s(&tm, &t);
    std::ostringstream oss;
    oss << filename << "_" << std::put_time(&tm, "%d%m%Y_%H%M%S") << ".txt";
    std::string datedFilename = oss.str();

    if (std::remove(datedFilename.c_str()) != 0) {
        // Plik nie istnieje lub nie mo¿na go usun¹æ.
    }
    logFile.open(datedFilename, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Nie mo¿na otworzyæ pliku logu");
    }
}

/// \brief Destruktor klasy Logger.
/// \details Zamykany jest otwarty plik logu.
Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

/// \brief Zapisuje komunikat do pliku logu.
/// \param message Komunikat do zapisania.
void Logger::log(const std::string& message) {
    if (logFile.is_open()) {
        auto t = std::time(nullptr);
        std::tm tm;
        localtime_s(&tm, &t);
        logFile << std::put_time(&tm, "%d.%m.%Y %H:%M:%S") << " " << message << std::endl;
    }

    if (this == &loggerError) {
        ++loggerErrorCount;
    }
}
