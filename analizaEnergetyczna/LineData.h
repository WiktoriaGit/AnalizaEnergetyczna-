#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class LineData {
public:

    LineData(const string& line);

    void print();
	
	string printString();

private:
    // Time,Autokonsumpcja (W),Eksport (W),Import (W),Pobór (W),Produkcja (W)
    string date;

	float autokonsumpcja;

	float eksport;

	float import;

	float pobor;

	float produkcja;
};