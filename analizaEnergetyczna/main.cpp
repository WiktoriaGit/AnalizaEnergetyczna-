#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "LineData.h"
#include "Logger.h"
#include "TreeData.h"

using namespace std;

bool lineValidation(const string& line)
{
	if (line.empty())
	{
		// Log empty line
		loggerError.log("Pusta linia");
		return false;
	}
	else if (line.find("Time") != string::npos)
	{
		// Log header line
		loggerError.log("Znaleziono naglowek: " + line);
		return false;
	}
    else if ((line.find("X") != string::npos) || 
             (line.find("y") != string::npos) || 
             (line.find("Y") != string::npos) || 
             (line.find("x") != string::npos))
    {
		// Log other data
        loggerError.log("Znaleziono inne dane: " + line);
        return false;
    }
    else if (count(line.begin(), line.end(), ',') != 5)
    {
		// Log invalid number of parameters
        loggerError.log("Nieprawidlowa liczba parametrow: " + line);
        return false;
    }
    else
	{
		return true;
	}
}


int main()
{
    ifstream file("Chart Export.csv");
    if (!file.is_open())
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

	// Vector to store the data from the file using the LineData class
    vector<LineData> data;
    TreeData treeData;
    string line; 

    while (getline(file, line))
    {
        if (lineValidation(line))
        {
            LineData ld(line);
            data.push_back(ld);
			treeData.addData(ld);
        }
    }

    file.close();


    //treeData.print();

    // Get data between dates
    string startDate = "01.10.2020 00:00";
    string endDate = "01.10.2020 09:00";
    vector<LineData> filteredData = treeData.getDataBetweenDates(startDate, endDate);

    cout << "Data between " << startDate << " and " << endDate << ":" << endl;
    for (const auto& ld : filteredData) {
        ld.print();
    }

    // Calculate sums between dates
    float autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum;
    treeData.calculateSumsBetweenDates(startDate, endDate, autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum);
	
    cout << "Sums between " << startDate << " and " << endDate << ":" << endl;
    cout << "Autokonsumpcja: " << autokonsumpcjaSum << endl;
    cout << "Eksport: " << eksportSum << endl;
    cout << "Import: " << importSum << endl;
    cout << "Pobor: " << poborSum << endl;
    cout << "Produkcja: " << produkcjaSum << endl;

	// claculate averages between dates
    treeData.calculateAveragesBetweenDates(startDate, endDate, autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum);

    cout << "Average between " << startDate << " and " << endDate << ":" << endl;
    cout << "Autokonsumpcja: " << autokonsumpcjaSum << endl;
    cout << "Eksport: " << eksportSum << endl;
    cout << "Import: " << importSum << endl;
    cout << "Pobor: " << poborSum << endl;
    cout << "Produkcja: " << produkcjaSum << endl;

    string startDate1 = "01.10.2020 00:00";
    string endDate1 = "01.10.2020 09:00";
    string startDate2 = "02.10.2020 00:00";
    string endDate2 = "02.10.2020 09:00";


	// compare data between dates
    float autokonsumpcjaDiff, eksportDiff, importDiff, poborDiff, produkcjaDiff;
    treeData.compareDataBetweenDates(startDate1, endDate1, startDate2, endDate2, autokonsumpcjaDiff, eksportDiff, importDiff, poborDiff, produkcjaDiff);
    cout << "Differences between " << startDate1 << " - " << endDate1 << " and " << startDate2 << " - " << endDate2 << ":" << endl;
    cout << "Autokonsumpcja: " << autokonsumpcjaDiff << endl;
    cout << "Eksport: " << eksportDiff << endl;
    cout << "Import: " << importDiff << endl;
    cout << "Pobor: " << poborDiff << endl;
    cout << "Produkcja: " << produkcjaDiff << endl;


    // Search records with tolerance
    float searchValue = 449.2026;
    float tolerance = 0.01f;

    vector<LineData> recordsWithTolerance = treeData.searchRecordsWithTolerance(startDate, endDate, searchValue, tolerance);

    cout << "Records with value " << searchValue << " ± " << tolerance << " between " << startDate << " and " << endDate << ":" << endl;
    for (const auto& ld : recordsWithTolerance) {
        ld.print();
    }



    // Export data to binary file
    //ofstream binaryFile("data.bin", ios::binary);
    //if (!binaryFile.is_open()) {
    //    cerr << "Error opening binary file" << endl;
    //    return 1;
    //}

    //for (const auto& ld : data) {
    //    ld.serialize(binaryFile);
    //}


    //binaryFile.close();

    //// Import data from binary file
    //ifstream binaryFileIn("data.bin", ios::binary);
    //if (!binaryFileIn.is_open()) {
    //    cerr << "Error opening binary file for reading" << endl;
    //    return 1;
    //}

    //vector<LineData> importedData;
    //while (binaryFileIn.peek() != EOF) {
    //    LineData ld(binaryFileIn);
    //    importedData.push_back(ld);
    //}

    //binaryFileIn.close();

    //// Print imported data
    ////for (const auto& ld : importedData) {
    ////    ld.print();
    ////}









	cout << "Wczytano " << data.size() << " linii" << endl;
	cout << "Znaleziono " << loggerErrorCount << " bledow" << endl;

    return 0;
}