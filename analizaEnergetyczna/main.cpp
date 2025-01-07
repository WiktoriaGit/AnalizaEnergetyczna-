/// \file main.cpp
/// \brief G³ówny plik programu obs³uguj¹cego analizê danych z pliku CSV.
/// \details Program umo¿liwia wczytywanie danych z pliku CSV, ich analizê, przetwarzanie oraz zapisywanie w pliku binarnym.
/// Oferuje funkcje takie jak obliczanie sum i œrednich, porównywanie danych oraz wyszukiwanie z tolerancj¹.

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

/// \brief Wyœwietla menu u¿ytkownika.
/// \details Funkcja drukuje dostêpne opcje programu na standardowe wyjœcie.
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

/// \brief Funkcja g³ówna programu.
/// \details G³ówna pêtla programu, która obs³uguje menu i poszczególne funkcjonalnoœci.
/// \return Zwraca 0 w przypadku pomyœlnego zakoñczenia programu.
int main() {
    TreeData treeData; ///< Struktura drzewa do przechowywania danych.
    vector<LineData> data; ///< Wektor przechowuj¹cy dane wierszy z pliku.
    string line; ///< Aktualnie przetwarzany wiersz danych.
    ifstream file; ///< Strumieñ do odczytu pliku CSV.
    string startDate, endDate, startDate1, endDate1, startDate2, endDate2; ///< Daty u¿ywane w analizie danych.
    float autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum; ///< Wyniki obliczeñ sum.
    float autokonsumpcjaDiff, eksportDiff, importDiff, poborDiff, produkcjaDiff; ///< Wyniki porównañ.
    float searchValue, tolerance; ///< Parametry do wyszukiwania z tolerancj¹.
    vector<LineData> filteredData, recordsWithTolerance; ///< Wyniki filtracji danych.

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;
        cin.ignore(); ///< Ignoruj znak nowej linii pozostawiony w buforze.

        switch (choice) {
        case 1:
            /// \brief Wczytanie danych z pliku CSV.
            /// \details Dane s¹ wczytywane do struktury drzewa i wektora, a niepoprawne wiersze s¹ logowane.
            file.open("Chart Export.csv");
            if (!file.is_open()) {
                cerr << "Error opening file" << endl;
                return 1;
            }

            while (getline(file, line)) {
                if (lineValidation(line)) {
                    LineData ld(line);
                    data.push_back(ld);
                    treeData.addData(ld);
                }
            }

            file.close();
            cout << "Data loaded successfully." << endl;
            cout << "Loaded " << data.size() << " lines" << endl;
            cout << "Found " << loggerErrorCount << " faulty lines" << endl;
            cout << "Check log and log_error files for more details" << endl;
            break;

        case 2:
            /// \brief Wyœwietlenie struktury drzewa.
            treeData.print();
            break;

        case 3:
            /// \brief Pobranie danych w okreœlonym przedziale czasowym.
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
            /// \brief Obliczenie sum w okreœlonym przedziale czasowym.
            cout << "Enter start date (dd.mm.yyyy hh:mm): ";
            getline(cin, startDate);
            cout << "Enter end date (dd.mm.yyyy hh:mm): ";
            getline(cin, endDate);
            treeData.calculateSumsBetweenDates(startDate, endDate, autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum);
            cout << "Sums between " << startDate << " and " << endDate << ":" << endl;
            cout << "Autokonsumpcja: " << autokonsumpcjaSum << endl;
            cout << "Eksport: " << eksportSum << endl;
            cout << "Import: " << importSum << endl;
            cout << "Pobór: " << poborSum << endl;
            cout << "Produkcja: " << produkcjaSum << endl;
            break;

        case 5:
            /// \brief Obliczenie œrednich w okreœlonym przedziale czasowym.
            cout << "Enter start date (dd.mm.yyyy hh:mm): ";
            getline(cin, startDate);
            cout << "Enter end date (dd.mm.yyyy hh:mm): ";
            getline(cin, endDate);
            treeData.calculateAveragesBetweenDates(startDate, endDate, autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum);
            cout << "Averages between " << startDate << " and " << endDate << ":" << endl;
            cout << "Autokonsumpcja: " << autokonsumpcjaSum << endl;
            cout << "Eksport: " << eksportSum << endl;
            cout << "Import: " << importSum << endl;
            cout << "Pobór: " << poborSum << endl;
            cout << "Produkcja: " << produkcjaSum << endl;
            break;

        case 6:
            /// \brief Porównanie danych miêdzy dwoma zakresami czasowymi.
            cout << "Enter first start date (dd.mm.yyyy hh:mm): ";
            getline(cin, startDate1);
            cout << "Enter first end date (dd.mm.yyyy hh:mm): ";
            getline(cin, endDate1);
            cout << "Enter second start date (dd.mm.yyyy hh:mm): ";
            getline(cin, startDate2);
            cout << "Enter second end date (dd.mm.yyyy hh:mm): ";
            getline(cin, endDate2);
            treeData.compareDataBetweenDates(startDate1, endDate1, startDate2, endDate2, autokonsumpcjaDiff, eksportDiff, importDiff, poborDiff, produkcjaDiff);
            cout << "Differences between ranges:" << endl;
            cout << "Autokonsumpcja: " << autokonsumpcjaDiff << endl;
            cout << "Eksport: " << eksportDiff << endl;
            cout << "Import: " << importDiff << endl;
            cout << "Pobór: " << poborDiff << endl;
            cout << "Produkcja: " << produkcjaDiff << endl;
            break;

        case 7:
            /// \brief Wyszukiwanie danych w okreœlonym przedziale czasowym z tolerancj¹.
            cout << "Enter start date (dd.mm.yyyy hh:mm): ";
            getline(cin, startDate);
            cout << "Enter end date (dd.mm.yyyy hh:mm): ";
            getline(cin, endDate);
            cout << "Enter search value: ";
            cin >> searchValue;
            cout << "Enter tolerance: ";
            cin >> tolerance;
            recordsWithTolerance = treeData.searchRecordsWithTolerance(startDate, endDate, searchValue, tolerance);
            cout << "Records within tolerance:" << endl;
            for (const auto& ld : recordsWithTolerance) {
                ld.print();
            }
            break;

        case 8:
            /// \brief Zapisanie danych do pliku binarnego.
        {
            ofstream binaryFile("data.bin", ios::binary);
            if (!binaryFile.is_open()) {
                cerr << "Error opening binary file" << endl;
                return 1;
            }
            for (const auto& ld : data) {
                ld.serialize(binaryFile);
            }
            binaryFile.close();
            cout << "Data saved successfully." << endl;
        }
        break;

        case 9:
            /// \brief Wczytanie danych z pliku binarnego.
        {
            ifstream binaryFileIn("data.bin", ios::binary);
            if (!binaryFileIn.is_open()) {
                cerr << "Error opening binary file for reading" << endl;
                return 1;
            }
            while (binaryFileIn.peek() != EOF) {
                LineData ld(binaryFileIn);
                treeData.addData(ld);
            }
            binaryFileIn.close();
            cout << "Data loaded successfully." << endl;
        }
        break;

        case 10:
            /// \brief Wyjœcie z programu.
            cout << "Exiting..." << endl;
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}
