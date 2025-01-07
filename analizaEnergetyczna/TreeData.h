#ifndef TREEDATA_H
#define TREEDATA_H

#include <map>
#include <string>
#include <vector>
#include "LineData.h"

class TreeData {
public:
    struct QuarterNode {
        int quarter;
        int hour;
        int minute;
        std::vector<LineData> data;
    };

    struct DayNode {
        int day;
        std::map<int, QuarterNode> quarters;
    };

    struct MonthNode {
        int month;
        std::map<int, DayNode> days;
    };

    struct YearNode {
        int year;
        std::map<int, MonthNode> months;
    };

    void addData(const LineData& lineData);
    void print() const;
    std::vector<LineData> getDataBetweenDates(const std::string& startDate, const std::string& endDate) const;

private:
    std::map<int, YearNode> years;
};

#endif // TREEDATA_H