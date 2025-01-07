/// \file LineValidation.h
/// \brief Zawiera funkcj� waliduj�c� wiersze z pliku CSV.

#ifndef LINEVALIDATION_H
#define LINEVALIDATION_H

#include <string>
#include <cctype>
#include <algorithm>
#include "Logger.h"

/// \brief Funkcja sprawdzaj�ca poprawno�� wiersza danych.
/// \details Sprawdza, czy wiersz zawiera odpowiedni� liczb� parametr�w, czy nie jest pusty i czy nie zawiera liter.
/// \param line Wiersz danych wej�ciowych.
/// \return true, je�li wiersz jest poprawny, false w przeciwnym razie.
bool lineValidation(const std::string& line)
{
    if (line.empty())
    {
        loggerError.log("Pusta linia");
        return false;
    }
    else if (line.find("Time") != std::string::npos)
    {
        loggerError.log("Znaleziono nag��wek: " + line);
        return false;
    }
    else if (std::any_of(line.begin(), line.end(), [](char c) { return std::isalpha(c); }))
    {
        loggerError.log("Znaleziono inne dane: " + line);
        return false;
    }
    else if (std::count(line.begin(), line.end(), ',') != 5)
    {
        loggerError.log("Nieprawid�owa liczba parametr�w: " + line);
        return false;
    }
    else
    {
        return true;
    }
}

#endif // LINEVALIDATION_H
