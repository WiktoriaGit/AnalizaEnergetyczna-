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

    void print();
	
	string printString();

	void serialize(ofstream& out);

	void deserialize(ifstream& in);

private:
    // Time,Autokonsumpcja (W),Eksport (W),Import (W),Pobór (W),Produkcja (W)
    string date;

	float autokonsumpcja;

	float eksport;

	float import;

	float pobor;

	float produkcja;
};