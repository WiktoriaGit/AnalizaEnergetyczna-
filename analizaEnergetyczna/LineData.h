#ifndef LINEDATA_H
#define LINEDATA_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class LineData {
public:

    LineData(const string& line);

	LineData(ifstream& in);

    void print() const;

	void printData() const;
	
	string printString();

	void serialize(ofstream& out) const;

	void deserialize(ifstream& in);

	string getDate() const { return date; }

	float getAutokonsumpcja() const { return autokonsumpcja; }

	float getEksport() const { return eksport; }

	float getImport() const { return import; }

	float getPobor() const { return pobor; }

	float getProdukcja() const { return produkcja; }

private:
    // Time,Autokonsumpcja (W),Eksport (W),Import (W),Pobór (W),Produkcja (W)
    string date;

	float autokonsumpcja;

	float eksport;

	float import;

	float pobor;

	float produkcja;
};

#endif // LINEDATA_H