#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "LineData.h"

using namespace std;

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
    getline(file, line);

    while (getline(file, line))
    {
        // Skip empty lines !!!!!!!!!!!
        if (line.empty()) break;

        LineData ld(line);
        data.push_back(ld);
    }

    for (int i = 0; i < data.size(); i++)
    {
        data[i].print();
    }

    file.close();

    return 0;
}