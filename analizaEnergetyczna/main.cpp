#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "LineData.h"
#include "Logger.h"

using namespace std;

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


int main()
{
    ifstream file("Chart Export.csv");
    if (!file.is_open())
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

	// Vector to store the data from the file using the LineData class
    vector<LineData> data;
    string line; 

    while (getline(file, line))
    {
        if (lineValidation(line))
        {
            LineData ld(line);
            data.push_back(ld);
        }
    }

    file.close();

	cout << "Wczytano " << data.size() << " linii" << endl;
	cout << "Znaleziono " << loggerErrorCount << " bledow" << endl;

    return 0;
}