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

LineData::LineData(ifstream& in) {
    deserialize(in);
}


void LineData::print()
{
    cout << date << " " << autokonsumpcja << " " << eksport << " " << import << " " << pobor << " " << produkcja << endl;
}

string LineData::printString()
{
    return date + " " + to_string(autokonsumpcja) + " " + to_string(eksport) + " " + to_string(import) + " " + to_string(pobor) + " " + to_string(produkcja);
}

void LineData::serialize(ofstream& out) {
    size_t dateSize = date.size();
    out.write(reinterpret_cast<const char*>(&dateSize), sizeof(dateSize));
    out.write(date.c_str(), dateSize);
    out.write(reinterpret_cast<const char*>(&autokonsumpcja), sizeof(autokonsumpcja));
    out.write(reinterpret_cast<const char*>(&eksport), sizeof(eksport));
    out.write(reinterpret_cast<const char*>(&import), sizeof(import));
    out.write(reinterpret_cast<const char*>(&pobor), sizeof(pobor));
    out.write(reinterpret_cast<const char*>(&produkcja), sizeof(produkcja));
}

void LineData::deserialize(ifstream& in) {
    size_t dateSize;
    in.read(reinterpret_cast<char*>(&dateSize), sizeof(dateSize));
    date.resize(dateSize);
    in.read(&date[0], dateSize);
    in.read(reinterpret_cast<char*>(&autokonsumpcja), sizeof(autokonsumpcja));
    in.read(reinterpret_cast<char*>(&eksport), sizeof(eksport));
    in.read(reinterpret_cast<char*>(&import), sizeof(import));
    in.read(reinterpret_cast<char*>(&pobor), sizeof(pobor));
    in.read(reinterpret_cast<char*>(&produkcja), sizeof(produkcja));
}