/// \file Logger.h
/// \brief Deklaracja klasy Logger do obs³ugi logowania komunikatów.

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

/// \class Logger
/// \brief Klasa obs³uguj¹ca logowanie komunikatów do plików tekstowych.
class Logger {
public:
    /// \brief Konstruktor klasy Logger.
    /// \details Tworzy plik logu z unikaln¹ nazw¹ opart¹ na aktualnej dacie i godzinie.
    /// \param filename Nazwa podstawowa pliku logu.
    Logger(const std::string& filename);

    /// \brief Destruktor klasy Logger.
    /// \details Zamyka otwarty plik logu.
    ~Logger();

    /// \brief Zapisuje komunikat do pliku logu.
    /// \param message Komunikat do zapisania.
    void log(const std::string& message);

private:
    std::ofstream logFile; ///< Strumieñ pliku logu.
};

/// \var logger
/// \brief Globalny logger dla standardowych komunikatów.
extern Logger logger;

/// \var loggerError
/// \brief Globalny logger dla komunikatów b³êdów.
extern Logger loggerError;

/// \var loggerErrorCount
/// \brief Licznik wyst¹pieñ b³êdów logowanych przez loggerError.
extern int loggerErrorCount;

#endif // LOGGER_H
