#ifndef LINEVALIDATION_H
#define LINEVALIDATION_H

#include <string>
#include "Logger.h"

bool lineValidation(const string& line)
{
	if (line.empty())
	{
		// Log empty line
		loggerError.log("Pusta linia");
		return false;
	}
	else if (line.find("Time") != string::npos)
	{
		// Log header line
		loggerError.log("Znaleziono naglowek: " + line);
		return false;
	}
	else if ((line.find("X") != string::npos) ||
		(line.find("y") != string::npos) ||
		(line.find("Y") != string::npos) ||
		(line.find("x") != string::npos))
	{
		// Log other data
		loggerError.log("Znaleziono inne dane: " + line);
		return false;
	}
	else if (count(line.begin(), line.end(), ',') != 5)
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
