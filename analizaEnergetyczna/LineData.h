/// \file LineData.h
/// \brief Deklaracja klasy LineData do przechowywania i przetwarzania danych wierszy z pliku CSV.

#ifndef LINEDATA_H
#define LINEDATA_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

/// \class LineData
/// \brief Klasa reprezentuj¹ca dane jednego wiersza z pliku CSV.
class LineData {
public:
    /// \brief Konstruktor przetwarzaj¹cy wiersz danych z formatu CSV.
    /// \param line Wiersz danych wejœciowych.
    LineData(const string& line);

    /// \brief Konstruktor odczytuj¹cy dane z pliku binarnego.
    /// \param in Strumieñ wejœciowy.
    LineData(ifstream& in);

    /// \brief Wypisuje wszystkie dane na standardowe wyjœcie.
    void print() const;

    /// \brief Wypisuje tylko dane liczbowe (bez daty) na standardowe wyjœcie.
    void printData() const;

    /// \brief Zwraca dane jako ci¹g znaków.
    /// \return Dane w formacie tekstowym.
    string printString();

    /// \brief Serializuje obiekt do pliku binarnego.
    /// \param out Strumieñ wyjœciowy.
    void serialize(ofstream& out) const;

    /// \brief Deserializuje obiekt z pliku binarnego.
    /// \param in Strumieñ wejœciowy.
    void deserialize(ifstream& in);

    /// \brief Zwraca datê.
    /// \return Data w formacie tekstowym.
    string getDate() const { return date; }

    /// \brief Zwraca wartoœæ autokonsumpcji.
    /// \return Autokonsumpcja jako liczba zmiennoprzecinkowa.
    float getAutokonsumpcja() const { return autokonsumpcja; }

    /// \brief Zwraca wartoœæ eksportu.
    /// \return Eksport jako liczba zmiennoprzecinkowa.
    float getEksport() const { return eksport; }

    /// \brief Zwraca wartoœæ importu.
    /// \return Import jako liczba zmiennoprzecinkowa.
    float getImport() const { return import; }

    /// \brief Zwraca wartoœæ poboru.
    /// \return Pobór jako liczba zmiennoprzecinkowa.
    float getPobor() const { return pobor; }

    /// \brief Zwraca wartoœæ produkcji.
    /// \return Produkcja jako liczba zmiennoprzecinkowa.
    float getProdukcja() const { return produkcja; }

private:
    string date; ///< Data wiersza.
    float autokonsumpcja; ///< Autokonsumpcja w W.
    float eksport; ///< Eksport w W.
    float import; ///< Import w W.
    float pobor; ///< Pobór w W.
    float produkcja; ///< Produkcja w W.
};

#endif // LINEDATA_H
