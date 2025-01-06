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
    int hour = stoi(lineData.getDate().substr(11, 5)); // Assuming the date format is "YYYY-MM-DD HH:MM:SS"

    // Add data to the tree
    years[year].year = year;
    years[year].months[month].month = month;
    years[year].months[month].days[day].day = day;
    years[year].months[month].days[day].hours[hour].hour = hour;
    years[year].months[month].days[day].hours[hour].data.push_back(lineData);
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

                for (const auto& hourPair : dayNode.hours) {
                    const HourNode& hourNode = hourPair.second;
                    cout << "\t\t\tHour: " << hourNode.hour << endl;

                    for (const auto& lineData : hourNode.data) {
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
    //ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
    time_t start = mktime(&tm);

    ss.clear();
    ss.str(endDate);
    //ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
    time_t end = mktime(&tm);

    for (const auto& yearPair : years) {
        const YearNode& yearNode = yearPair.second;
        for (const auto& monthPair : yearNode.months) {
            const MonthNode& monthNode = monthPair.second;
            for (const auto& dayPair : monthNode.days) {
                const DayNode& dayNode = dayPair.second;
                for (const auto& hourPair : dayNode.hours) {
                    const HourNode& hourNode = hourPair.second;
                    for (const auto& lineData : hourNode.data) {
                        // Convert lineData.date to time_t
                        std::tm tm = {};
                        std::istringstream ss(lineData.getDate());
                        //ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
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
