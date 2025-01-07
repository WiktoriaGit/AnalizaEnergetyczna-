#include "TreeData.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

void TreeData::addData(const LineData& lineData) {
    // Parse the date from the LineData
    stringstream ss(lineData.getDate());
    string token;
    vector<int> dateParts;

    while (getline(ss, token, '.')) {
        dateParts.push_back(stoi(token));
    }

    int year = dateParts[2];
    int month = dateParts[1];
    int day = dateParts[0];
    int hour = stoi(lineData.getDate().substr(11, 2)); // Assuming the date format is "YYYY-MM-DD HH:MM:SS"
    int minute = stoi(lineData.getDate().substr(14, 2));
    int quarter = (hour * 60 + minute) / 360; // Calculate the quarter of the day (6-hour intervals)

    // Add data to the tree
    years[year].year = year;
    years[year].months[month].month = month;
    years[year].months[month].days[day].day = day;
    years[year].months[month].days[day].quarters[quarter].quarter = quarter;
    years[year].months[month].days[day].quarters[quarter].hour = hour;
    years[year].months[month].days[day].quarters[quarter].minute = minute;
    years[year].months[month].days[day].quarters[quarter].data.push_back(lineData);
}

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
                    cout << "\t\t\tQuarter: " << quarterNode.quarter << " (Hour: " << quarterNode.hour << ", Minute: " << quarterNode.minute << ")" << endl;

                    for (const auto& lineData : quarterNode.data) {
                        lineData.printData();
                    }
                }
            }
        }
    }
}

std::vector<LineData> TreeData::getDataBetweenDates(const std::string& startDate, const std::string& endDate) const {
    std::vector<LineData> result;

    // Convert startDate and endDate to time_t
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
                        // Convert lineData.date to time_t
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

void TreeData::calculateSumsBetweenDates(const std::string& startDate, const std::string& endDate, float& autokonsumpcjaSum, float& eksportSum, float& importSum, float& poborSum, float& produkcjaSum) const {
    autokonsumpcjaSum = 0.0f;
    eksportSum = 0.0f;
    importSum = 0.0f;
    poborSum = 0.0f;
    produkcjaSum = 0.0f;

    // Convert startDate and endDate to time_t
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
                        // Convert lineData.date to time_t
                        std::tm tm = {};
                        std::istringstream ss(lineData.getDate());
                        ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
                        time_t dataTime = mktime(&tm);

                        if (dataTime >= start && dataTime <= end) {
							autokonsumpcjaSum += lineData.getAutokonsumpcja();
							eksportSum += lineData.getEksport();
                            importSum += lineData.getImport();
                            poborSum += lineData.getPobor();
                            produkcjaSum += lineData.getProdukcja();
                        }
                    }
                }
            }
        }
    }
}

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
        autokonsumpcjaAvg = 0.0f;
        eksportAvg = 0.0f;
        importAvg = 0.0f;
        poborAvg = 0.0f;
        produkcjaAvg = 0.0f;
    }
}

void TreeData::compareDataBetweenDates(const std::string& startDate1, const std::string& endDate1, const std::string& startDate2, const std::string& endDate2, float& autokonsumpcjaDiff, float& eksportDiff, float& importDiff, float& poborDiff, float& produkcjaDiff) const {
    float autokonsumpcjaSum1 = 0.0f, eksportSum1 = 0.0f, importSum1 = 0.0f, poborSum1 = 0.0f, produkcjaSum1 = 0.0f;
    float autokonsumpcjaSum2 = 0.0f, eksportSum2 = 0.0f, importSum2 = 0.0f, poborSum2 = 0.0f, produkcjaSum2 = 0.0f;

    calculateSumsBetweenDates(startDate1, endDate1, autokonsumpcjaSum1, eksportSum1, importSum1, poborSum1, produkcjaSum1);
    calculateSumsBetweenDates(startDate2, endDate2, autokonsumpcjaSum2, eksportSum2, importSum2, poborSum2, produkcjaSum2);

    autokonsumpcjaDiff = autokonsumpcjaSum1 - autokonsumpcjaSum2;
    eksportDiff = eksportSum1 - eksportSum2;
    importDiff = importSum1 - importSum2;
    poborDiff = poborSum1 - poborSum2;
    produkcjaDiff = produkcjaSum1 - produkcjaSum2;
}