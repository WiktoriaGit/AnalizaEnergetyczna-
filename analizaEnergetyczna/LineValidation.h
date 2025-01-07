/// \file LineValidation.h
/// \brief Zawiera funkcjê waliduj¹c¹ wiersze z pliku CSV.

#ifndef LINEVALIDATION_H
#define LINEVALIDATION_H

#include <string>
#include <cctype>
#include <algorithm>
#include "Logger.h"

/// \brief Funkcja sprawdzaj¹ca poprawnoœæ wiersza danych.
/// \details Sprawdza, czy wiersz zawiera odpowiedni¹ liczbê parametrów, czy nie jest pusty i czy nie zawiera liter.
/// \param line Wiersz danych wejœciowych.
/// \return true, jeœli wiersz jest poprawny, false w przeciwnym razie.
bool lineValidation(const std::string& line)
{
    if (line.empty())
    {
        loggerError.log("Pusta linia");
        return false;
    }
    else if (line.find("Time") != std::string::npos)
    {
        loggerError.log("Znaleziono nag³ówek: " + line);
        return false;
    }
    else if (std::any_of(line.begin(), line.end(), [](char c) { return std::isalpha(c); }))
    {
        loggerError.log("Znaleziono inne dane: " + line);
        return false;
    }
    else if (std::count(line.begin(), line.end(), ',') != 5)
    {
        loggerError.log("Nieprawid³owa liczba parametrów: " + line);
        return false;
    }
    else
    {
        return true;
    }
}

#endif // LINEVALIDATION_H
