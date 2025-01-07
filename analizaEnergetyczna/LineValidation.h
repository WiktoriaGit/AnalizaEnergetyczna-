#ifndef LINEVALIDATION_H
#define LINEVALIDATION_H

#include <string>
#include <cctype>
#include <algorithm>
#include "Logger.h"

bool lineValidation(const std::string& line)
{
    if (line.empty())
    {
        // Log empty line
        loggerError.log("Pusta linia");
        return false;
    }
    else if (line.find("Time") != std::string::npos)
    {
        // Log header line
        loggerError.log("Znaleziono naglowek: " + line);
        return false;
    }
    else if (std::any_of(line.begin(), line.end(), [](char c) { return std::isalpha(c); }))
    {
        // Log other data
        loggerError.log("Znaleziono inne dane: " + line);
        return false;
    }
    else if (std::count(line.begin(), line.end(), ',') != 5)
    {
        // Log invalid number of parameters
        loggerError.log("Nieprawidlowa liczba parametrow: " + line);
        return false;
    }
    else
    {
        return true;
    }
}

#endif // LINEVALIDATION_H