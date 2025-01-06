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

private:
    // Time,Autokonsumpcja (W),Eksport (W),Import (W),Pob�r (W),Produkcja (W)
    string date;

	float autokonsumpcja;

	float eksport;

	float import;

	float pobor;

	float produkcja;
};