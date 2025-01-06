#include "LineData.h"
#include <algorithm>

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

    this->print();
}

void LineData::print()
{
    cout << date << " " << autokonsumpcja << " " << eksport << " " << import << " " << pobor << " " << produkcja << endl;
}
