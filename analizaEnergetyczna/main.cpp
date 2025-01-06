#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
        while (getline(ss, value, ','))
        {
            cout << value << " ";
        }
        cout << endl;
    }

    file.close();


	return 0;
}