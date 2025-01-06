#include "LineData.h"
#include "Logger.h"
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

LineData::LineData(const string& line) {

    vector<string> values;
    stringstream ss(line);
    string value;

    while (getline(ss, value, ','))
    {
        // Remove double quotes from the value
        value.erase(remove(value.begin(), value.end(), '\"'), value.end());
        values.push_back(value);
    }

    this->date = values[0];

    this->autokonsumpcja = stof(values[1]);
    this->eksport = stof(values[2]);
    this->import = stof(values[3]);
    this->pobor = stof(values[4]);
    this->produkcja = stof(values[5]);

	logger.log("Wczytano linie: " + this->printString());

    //this->print();
}

void LineData::print()
{
    cout << date << " " << autokonsumpcja << " " << eksport << " " << import << " " << pobor << " " << produkcja << endl;
}

string LineData::printString()
{
    return date + " " + to_string(autokonsumpcja) + " " + to_string(eksport) + " " + to_string(import) + " " + to_string(pobor) + " " + to_string(produkcja);
}
