/// \file LineData.cpp
/// \brief Implementacja klasy LineData do obs�ugi danych wierszy z pliku CSV.

#include "LineData.h"
#include "Logger.h"
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

/// \brief Konstruktor przetwarzaj�cy wiersz danych z formatu CSV.
/// \param line Wiersz danych wej�ciowych.
LineData::LineData(const string& line) {
    vector<string> values;
    stringstream ss(line);
    string value;

    while (getline(ss, value, ',')) {
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
}

/// \brief Konstruktor odczytuj�cy dane z pliku binarnego.
/// \param in Strumie� wej�ciowy.
LineData::LineData(ifstream& in) {
    deserialize(in);
}

/// \brief Wypisuje wszystkie dane na standardowe wyj�cie.
void LineData::print() const {
    cout << date << " " << autokonsumpcja << " " << eksport << " " << import << " " << pobor << " " << produkcja << endl;
}

/// \brief Wypisuje tylko dane liczbowe (bez daty) na standardowe wyj�cie.
void LineData::printData() const {
    cout << "\t\t\t\t" << autokonsumpcja << " " << eksport << " " << import << " " << pobor << " " << produkcja << endl;
}

/// \brief Zwraca dane jako ci�g znak�w.
/// \return Dane w formacie tekstowym.
string LineData::printString() {
    return date + " " + to_string(autokonsumpcja) + " " + to_string(eksport) + " " + to_string(import) + " " +
        to_string(pobor) + " " + to_string(produkcja);
}

/// \brief Serializuje obiekt do pliku binarnego.
/// \param out Strumie� wyj�ciowy.
void LineData::serialize(ofstream& out) const {
    size_t dateSize = date.size();
    out.write(reinterpret_cast<const char*>(&dateSize), sizeof(dateSize));
    out.write(date.c_str(), dateSize);
    out.write(reinterpret_cast<const char*>(&autokonsumpcja), sizeof(autokonsumpcja));
    out.write(reinterpret_cast<const char*>(&eksport), sizeof(eksport));
    out.write(reinterpret_cast<const char*>(&import), sizeof(import));
    out.write(reinterpret_cast<const char*>(&pobor), sizeof(pobor));
    out.write(reinterpret_cast<const char*>(&produkcja), sizeof(produkcja));
}

/// \brief Deserializuje obiekt z pliku binarnego.
/// \param in Strumie� wej�ciowy.
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
