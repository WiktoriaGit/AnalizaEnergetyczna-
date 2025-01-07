/// \file TreeData.cpp
/// \brief Implementacja klasy TreeData do przechowywania i analizy danych w strukturze drzewa.

#include "TreeData.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

/// \brief Dodaje dane do struktury drzewa.
/// \param lineData Obiekt LineData reprezentuj¹cy dane wiersza.
void TreeData::addData(const LineData& lineData) {
    stringstream ss(lineData.getDate());
    string token;
    vector<int> dateParts;

    while (getline(ss, token, '.')) {
        dateParts.push_back(stoi(token));
    }

    int year = dateParts[2];
    int month = dateParts[1];
    int day = dateParts[0];
    int hour = stoi(lineData.getDate().substr(11, 2));
    int minute = stoi(lineData.getDate().substr(14, 2));
    int quarter = (hour * 60 + minute) / 360;

    years[year].year = year;
    years[year].months[month].month = month;
    years[year].months[month].days[day].day = day;
    years[year].months[month].days[day].quarters[quarter].quarter = quarter;
    years[year].months[month].days[day].quarters[quarter].hour = hour;
    years[year].months[month].days[day].quarters[quarter].minute = minute;
    years[year].months[month].days[day].quarters[quarter].data.push_back(lineData);
}

/// \brief Wyœwietla zawartoœæ drzewa na standardowym wyjœciu.
void TreeData::print() const {
    for (const auto& yearPair : years) {
        const YearNode& yearNode = yearPair.second;
        cout << "Year: " << yearNode.year << endl;

        for (const auto& monthPair : yearNode.months) {
            const MonthNode& monthNode = monthPair.second;
            cout << "\tMonth: " << monthNode.month << endl;

            for (const auto& dayPair : monthNode.days) {
                const DayNode& dayNode = dayPair.second;
                cout << "\t\tDay: " << dayNode.day << endl;

                for (const auto& quarterPair : dayNode.quarters) {
                    const QuarterNode& quarterNode = quarterPair.second;
                    cout << "\t\t\tQuarter: " << quarterNode.quarter
                        << " (Hour: " << quarterNode.hour << ", Minute: " << quarterNode.minute << ")" << endl;

                    for (const auto& lineData : quarterNode.data) {
                        lineData.printData();
                    }
                }
            }
        }
    }
}

/// \brief Pobiera dane z drzewa w okreœlonym przedziale czasowym.
/// \param startDate Data pocz¹tkowa w formacie dd.mm.yyyy hh:mm.
/// \param endDate Data koñcowa w formacie dd.mm.yyyy hh:mm.
/// \return Wektor obiektów LineData w podanym przedziale czasowym.
std::vector<LineData> TreeData::getDataBetweenDates(const std::string& startDate, const std::string& endDate) const {
    std::vector<LineData> result;

    std::tm tm = {};
    std::istringstream ss(startDate);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
    time_t start = mktime(&tm);

    ss.clear();
    ss.str(endDate);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
    time_t end = mktime(&tm);

    for (const auto& yearPair : years) {
        const YearNode& yearNode = yearPair.second;
        for (const auto& monthPair : yearNode.months) {
            const MonthNode& monthNode = monthPair.second;
            for (const auto& dayPair : monthNode.days) {
                const DayNode& dayNode = dayPair.second;
                for (const auto& quarterPair : dayNode.quarters) {
                    const QuarterNode& quarterNode = quarterPair.second;
                    for (const auto& lineData : quarterNode.data) {
                        std::tm tm = {};
                        std::istringstream ss(lineData.getDate());
                        ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
                        time_t dataTime = mktime(&tm);

                        if (dataTime >= start && dataTime <= end) {
                            result.push_back(lineData);
                        }
                    }
                }
            }
        }
    }

    return result;
}

/// \brief Oblicza sumy wartoœci w okreœlonym przedziale czasowym.
/// \param startDate Data pocz¹tkowa w formacie dd.mm.yyyy hh:mm.
/// \param endDate Data koñcowa w formacie dd.mm.yyyy hh:mm.
/// \param[out] autokonsumpcjaSum Suma autokonsumpcji.
/// \param[out] eksportSum Suma eksportu.
/// \param[out] importSum Suma importu.
/// \param[out] poborSum Suma poboru.
/// \param[out] produkcjaSum Suma produkcji.
void TreeData::calculateSumsBetweenDates(const std::string& startDate, const std::string& endDate, float& autokonsumpcjaSum, float& eksportSum, float& importSum, float& poborSum, float& produkcjaSum) const {
    autokonsumpcjaSum = 0.0f;
    eksportSum = 0.0f;
    importSum = 0.0f;
    poborSum = 0.0f;
    produkcjaSum = 0.0f;

    std::vector<LineData> data = getDataBetweenDates(startDate, endDate);
    for (const auto& lineData : data) {
        autokonsumpcjaSum += lineData.getAutokonsumpcja();
        eksportSum += lineData.getEksport();
        importSum += lineData.getImport();
        poborSum += lineData.getPobor();
        produkcjaSum += lineData.getProdukcja();
    }
}

/// \brief Oblicza œrednie wartoœci w okreœlonym przedziale czasowym.
/// \param startDate Data pocz¹tkowa w formacie dd.mm.yyyy hh:mm.
/// \param endDate Data koñcowa w formacie dd.mm.yyyy hh:mm.
/// \param[out] autokonsumpcjaAvg Œrednia autokonsumpcji.
/// \param[out] eksportAvg Œrednia eksportu.
/// \param[out] importAvg Œrednia importu.
/// \param[out] poborAvg Œrednia poboru.
/// \param[out] produkcjaAvg Œrednia produkcji.
void TreeData::calculateAveragesBetweenDates(const std::string& startDate, const std::string& endDate, float& autokonsumpcjaAvg, float& eksportAvg, float& importAvg, float& poborAvg, float& produkcjaAvg) const {
    float autokonsumpcjaSum = 0.0f, eksportSum = 0.0f, importSum = 0.0f, poborSum = 0.0f, produkcjaSum = 0.0f;
    int count = 0;

    std::vector<LineData> data = getDataBetweenDates(startDate, endDate);
    for (const auto& lineData : data) {
        autokonsumpcjaSum += lineData.getAutokonsumpcja();
        eksportSum += lineData.getEksport();
        importSum += lineData.getImport();
        poborSum += lineData.getPobor();
        produkcjaSum += lineData.getProdukcja();
        count++;
    }

    if (count > 0) {
        autokonsumpcjaAvg = autokonsumpcjaSum / count;
        eksportAvg = eksportSum / count;
        importAvg = importSum / count;
        poborAvg = poborSum / count;
        produkcjaAvg = produkcjaSum / count;
    }
    else {
        autokonsumpcjaAvg = eksportAvg = importAvg = poborAvg = produkcjaAvg = 0.0f;
    }
}
