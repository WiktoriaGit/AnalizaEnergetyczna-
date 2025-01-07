#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "LineData.h"
#include "Logger.h"
#include "TreeData.h"
#include "LineValidation.h"

using namespace std;


void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Load data from file" << endl;
    cout << "2. Print tree structure" << endl;
    cout << "3. Get data between dates" << endl;
    cout << "4. Calculate sums between dates" << endl;
    cout << "5. Calculate averages between dates" << endl;
    cout << "6. Compare data between dates" << endl;
    cout << "7. Search records with tolerance" << endl;
    cout << "8. Save data to binary file" << endl;
    cout << "9. Load data from binary file" << endl;
    cout << "10. Exit" << endl;
    cout << "Enter your choice: ";
}

int main()
{
    TreeData treeData;
    vector<LineData> data;
    string line;
    ifstream file;
    string startDate, endDate, startDate1, endDate1, startDate2, endDate2;
    float autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum;
    float autokonsumpcjaDiff, eksportDiff, importDiff, poborDiff, produkcjaDiff;
    float searchValue, tolerance;
    vector<LineData> filteredData, recordsWithTolerance;

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;
        cin.ignore(); // Ignore the newline character left in the buffer

        switch (choice) {
        case 1:
            file.open("Chart Export.csv");
            if (!file.is_open())
            {
                cerr << "Error opening file" << endl;
                return 1;
            }

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
            cout << "Data loaded successfully." << endl;
            break;

        case 2:
            treeData.print();
            break;

        case 3:
            cout << "Enter start date (dd.mm.yyyy hh:mm): ";
            getline(cin, startDate);
            cout << "Enter end date (dd.mm.yyyy hh:mm): ";
            getline(cin, endDate);
            filteredData = treeData.getDataBetweenDates(startDate, endDate);
            cout << "Data between " << startDate << " and " << endDate << ":" << endl;
            for (const auto& ld : filteredData) {
                ld.print();
            }
            break;

        case 4:
            cout << "Enter start date (dd.mm.yyyy hh:mm): ";
            getline(cin, startDate);
            cout << "Enter end date (dd.mm.yyyy hh:mm): ";
            getline(cin, endDate);
            treeData.calculateSumsBetweenDates(startDate, endDate, autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum);
            cout << "Sums between " << startDate << " and " << endDate << ":" << endl;
            cout << "Autokonsumpcja: " << autokonsumpcjaSum << endl;
            cout << "Eksport: " << eksportSum << endl;
            cout << "Import: " << importSum << endl;
            cout << "Pobor: " << poborSum << endl;
            cout << "Produkcja: " << produkcjaSum << endl;
            break;

        case 5:
            cout << "Enter start date (dd.mm.yyyy hh:mm): ";
            getline(cin, startDate);
            cout << "Enter end date (dd.mm.yyyy hh:mm): ";
            getline(cin, endDate);
            treeData.calculateAveragesBetweenDates(startDate, endDate, autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum);
            cout << "Averages between " << startDate << " and " << endDate << ":" << endl;
            cout << "Autokonsumpcja: " << autokonsumpcjaSum << endl;
            cout << "Eksport: " << eksportSum << endl;
            cout << "Import: " << importSum << endl;
            cout << "Pobor: " << poborSum << endl;
            cout << "Produkcja: " << produkcjaSum << endl;
            break;

        case 6:
            cout << "Enter first start date (dd.mm.yyyy hh:mm): ";
            getline(cin, startDate1);
            cout << "Enter first end date (dd.mm.yyyy hh:mm): ";
            getline(cin, endDate1);
            cout << "Enter second start date (dd.mm.yyyy hh:mm): ";
            getline(cin, startDate2);
            cout << "Enter second end date (dd.mm.yyyy hh:mm): ";
            getline(cin, endDate2);
            treeData.compareDataBetweenDates(startDate1, endDate1, startDate2, endDate2, autokonsumpcjaDiff, eksportDiff, importDiff, poborDiff, produkcjaDiff);
            cout << "Differences between " << startDate1 << " - " << endDate1 << " and " << startDate2 << " - " << endDate2 << ":" << endl;
            cout << "Autokonsumpcja: " << autokonsumpcjaDiff << endl;
            cout << "Eksport: " << eksportDiff << endl;
            cout << "Import: " << importDiff << endl;
            cout << "Pobor: " << poborDiff << endl;
            cout << "Produkcja: " << produkcjaDiff << endl;
            break;

        case 7:
            cout << "Enter start date (dd.mm.yyyy hh:mm): ";
            getline(cin, startDate);
            cout << "Enter end date (dd.mm.yyyy hh:mm): ";
            getline(cin, endDate);
            cout << "Enter search value: ";
            cin >> searchValue;
            cout << "Enter tolerance: ";
            cin >> tolerance;
            recordsWithTolerance = treeData.searchRecordsWithTolerance(startDate, endDate, searchValue, tolerance);
            cout << "Records with value " << searchValue << " ± " << tolerance << " between " << startDate << " and " << endDate << ":" << endl;
            for (const auto& ld : recordsWithTolerance) {
                ld.print();
            }
            break;

        case 8:
        {
            // Export data to binary file
            ofstream binaryFile("data.bin", ios::binary);
            if (!binaryFile.is_open()) {
                cerr << "Error opening binary file" << endl;
                return 1;
            }

            for (const auto& ld : data) {
                ld.serialize(binaryFile);
            }

            binaryFile.close();
            cout << "Data saved to binary file successfully." << endl;
        }
        break;

        case 9:
        {
            // Import data from binary file
            ifstream binaryFileIn("data.bin", ios::binary);
            if (!binaryFileIn.is_open()) {
                cerr << "Error opening binary file for reading" << endl;
                return 1;
            }

            vector<LineData> importedData;
            while (binaryFileIn.peek() != EOF) {
                LineData ld(binaryFileIn);
                importedData.push_back(ld);
            }

            binaryFileIn.close();
            cout << "Data loaded from binary file successfully." << endl;

            //Print imported data
            //for (const auto& ld : importedData) {
            //    ld.print();
            //}
        }
        break;

        case 10:
            cout << "Exiting..." << endl;
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
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