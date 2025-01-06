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
	// check number of commas to see how many columns are in the line
    int commaCount = count(line.begin(), line.end(), ',');

	if (line.empty())
	{
		loggerError.log("Pusta linia");
		return false;
	}
	else if (line.find("Time") != string::npos)
	{
		loggerError.log("Znaleziono naglowek: " + line);
		return false;
	}
    else if (   (line.find("X") != string::npos) || 
                (line.find("y") != string::npos) || 
                (line.find("Y") != string::npos) || 
                (line.find("x") != string::npos))
    {
        loggerError.log("Znaleziono inne dane: " + line);
        return false;
    }
    else if (commaCount != 5)
    {
        loggerError.log("Nieprawidlowa liczba parametrow: " + line);
        return false;
    }
    else
	{
		return true;
	}



	return true;
}


int main()
{
    ifstream file("Chart Export.csv");
    if (!file.is_open())
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    vector<LineData> data;

    string line; 
    // Skip the first line !!!!!!!!!!!!
    //getline(file, line);

    while (getline(file, line))
    {
        if (lineValidation(line))
        {
            LineData ld(line);
            data.push_back(ld);
        }
    }

    for (int i = 0; i < data.size(); i++)
    {
        //data[i].print();
        logger.log("Dodano linie do wektora: " + data[i].printString());
    }

    file.close();

    return 0;
}