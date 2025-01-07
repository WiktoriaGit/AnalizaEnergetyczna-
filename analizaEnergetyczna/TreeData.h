/// \file TreeData.h
/// \brief Deklaracja klasy TreeData do przechowywania i analizy danych w strukturze drzewa.

#ifndef TREEDATA_H
#define TREEDATA_H

#include <map>
#include <string>
#include <vector>
#include "LineData.h"

/// \class TreeData
/// \brief Klasa obs³uguj¹ca hierarchiczn¹ strukturê danych z pliku CSV.
class TreeData {
public:
    /// \struct QuarterNode
    /// \brief Reprezentuje dane z podzia³em na kwarta³y dnia.
    struct QuarterNode {
        int quarter; ///< Numer kwarta³u (0-3).
        int hour; ///< Godzina rozpoczêcia kwarta³u.
        int minute; ///< Minuta rozpoczêcia kwarta³u.
        std::vector<LineData> data; ///< Dane przypisane do kwarta³u.
    };

    /// \struct DayNode
    /// \brief Reprezentuje dane dzienne.
    struct DayNode {
        int day; ///< Dzieñ miesi¹ca.
        std::map<int, QuarterNode> quarters; ///< Mapa kwartalnych danych w dniu.
    };

    /// \struct MonthNode
    /// \brief Reprezentuje dane miesiêczne.
    struct MonthNode {
        int month; ///< Numer miesi¹ca.
        std::map<int, DayNode> days; ///< Mapa dziennych danych w miesi¹cu.
    };

    /// \struct YearNode
    /// \brief Reprezentuje dane roczne.
    struct YearNode {
        int year; ///< Rok.
        std::map<int, MonthNode> months; ///< Mapa miesiêcznych danych w roku.
    };

    /// \brief Dodaje dane do struktury drzewa.
    /// \param lineData Obiekt LineData reprezentuj¹cy wiersz danych.
    void addData(const LineData& lineData);

    /// \brief Wyœwietla ca³¹ strukturê drzewa.
    void print() const;

    /// \brief Pobiera dane w podanym przedziale czasowym.
    /// \param startDate Data pocz¹tkowa w formacie dd.mm.yyyy hh:mm.
    /// \param endDate Data koñcowa w formacie dd.mm.yyyy hh:mm.
    /// \return Wektor obiektów LineData w podanym zakresie czasowym.
    std::vector<LineData> getDataBetweenDates(const std::string& startDate, const std::string& endDate) const;

    /// \brief Oblicza sumy danych w podanym przedziale czasowym.
    /// \param startDate Data pocz¹tkowa w formacie dd.mm.yyyy hh:mm.
    /// \param endDate Data koñcowa w formacie dd.mm.yyyy hh:mm.
    /// \param[out] autokonsumpcjaSum Suma autokonsumpcji.
    /// \param[out] eksportSum Suma eksportu.
    /// \param[out] importSum Suma importu.
    /// \param[out] poborSum Suma poboru.
    /// \param[out] produkcjaSum Suma produkcji.
    void calculateSumsBetweenDates(const std::string& startDate, const std::string& endDate, float& autokonsumpcjaSum, float& eksportSum, float& importSum, float& poborSum, float& produkcjaSum) const;

    /// \brief Oblicza œrednie dane w podanym przedziale czasowym.
    /// \param startDate Data pocz¹tkowa w formacie dd.mm.yyyy hh:mm.
    /// \param endDate Data koñcowa w formacie dd.mm.yyyy hh:mm.
    /// \param[out] autokonsumpcjaAvg Œrednia autokonsumpcji.
    /// \param[out] eksportAvg Œrednia eksportu.
    /// \param[out] importAvg Œrednia importu.
    /// \param[out] poborAvg Œrednia poboru.
    /// \param[out] produkcjaAvg Œrednia produkcji.
    void calculateAveragesBetweenDates(const std::string& startDate, const std::string& endDate, float& autokonsumpcjaAvg, float& eksportAvg, float& importAvg, float& poborAvg, float& produkcjaAvg) const;

    /// \brief Porównuje dane miêdzy dwoma zakresami czasowymi.
    /// \param startDate1 Data pocz¹tkowa pierwszego zakresu.
    /// \param endDate1 Data koñcowa pierwszego zakresu.
    /// \param startDate2 Data pocz¹tkowa drugiego zakresu.
    /// \param endDate2 Data koñcowa drugiego zakresu.
    /// \param[out] autokonsumpcjaDiff Ró¿nica autokonsumpcji.
    /// \param[out] eksportDiff Ró¿nica eksportu.
    /// \param[out] importDiff Ró¿nica importu.
    /// \param[out] poborDiff Ró¿nica poboru.
    /// \param[out] produkcjaDiff Ró¿nica produkcji.
    void compareDataBetweenDates(const std::string& startDate1, const std::string& endDate1, const std::string& startDate2, const std::string& endDate2, float& autokonsumpcjaDiff, float& eksportDiff, float& importDiff, float& poborDiff, float& produkcjaDiff) const;

    /// \brief Wyszukuje rekordy w podanym zakresie czasowym z uwzglêdnieniem tolerancji.
    /// \param startDate Data pocz¹tkowa w formacie dd.mm.yyyy hh:mm.
    /// \param endDate Data koñcowa w formacie dd.mm.yyyy hh:mm.
    /// \param value Wartoœæ wyszukiwana.
    /// \param tolerance Tolerancja dla wartoœci.
    /// \return Wektor obiektów LineData spe³niaj¹cych kryteria wyszukiwania.
    std::vector<LineData> searchRecordsWithTolerance(const std::string& startDate, const std::string& endDate, float value, float tolerance) const;

private:
    std::map<int, YearNode> years; ///< Mapa lat zawieraj¹cych dane w hierarchii.
};

#endif // TREEDATA_H
