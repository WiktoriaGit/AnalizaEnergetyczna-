#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    ifstream file("Chart Export.csv");
    if (!file.is_open())
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string value;
        vector<string> values;
        while (getline(ss, value, ','))
        {
            values.push_back(value);
        }

        for (const auto& val : values)
        {
            cout << val << " ";
        }
        cout << endl;
    }

    file.close();

    return 0;
}