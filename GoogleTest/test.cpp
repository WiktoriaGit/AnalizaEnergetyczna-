/// \file test.cpp
/// \brief Zawiera zestaw test�w jednostkowych dla modu��w LineData, TreeData, Logger i LineValidation.
/// \details Testy jednostkowe zosta�y zaimplementowane z u�yciem frameworka GoogleTest.

#include "pch.h"
#include "../analizaEnergetyczna/LineData.h"
#include "../analizaEnergetyczna/LineData.cpp"
#include "../analizaEnergetyczna/TreeData.h"
#include "../analizaEnergetyczna/TreeData.cpp"
#include "../analizaEnergetyczna/Logger.h"
#include "../analizaEnergetyczna/Logger.cpp"
#include "../analizaEnergetyczna/LineValidation.h"

using namespace std;

/// \brief Testuje konstruktor klasy LineData.
/// \details Sprawdza, czy warto�ci wczytane z ci�gu znak�w s� poprawnie przypisane.
TEST(LineDataTest, ConstructorFromString) {
    string line = "15.10.2023 12:00:00,100.5,200.5,300.5,400.5,500.5";
    LineData ld(line);

    EXPECT_EQ(ld.getDate(), "15.10.2023 12:00:00");
    EXPECT_FLOAT_EQ(ld.getAutokonsumpcja(), 100.5);
    EXPECT_FLOAT_EQ(ld.getEksport(), 200.5);
    EXPECT_FLOAT_EQ(ld.getImport(), 300.5);
    EXPECT_FLOAT_EQ(ld.getPobor(), 400.5);
    EXPECT_FLOAT_EQ(ld.getProdukcja(), 500.5);
}

/// \brief Testuje serializacj� i deserializacj� klasy LineData.
/// \details Sprawdza, czy dane zapisane do pliku binarnego s� poprawnie odczytywane.
TEST(LineDataTest, Serialization) {
    string line = "15.10.2023 12:00:00,100.5,200.5,300.5,400.5,500.5";
    LineData ld(line);

    ofstream out("test.bin", ios::binary);
    ld.serialize(out);
    out.close();

    ifstream in("test.bin", ios::binary);
    LineData ld2(in);
    in.close();

    EXPECT_EQ(ld2.getDate(), "15.10.2023 12:00:00");
    EXPECT_FLOAT_EQ(ld2.getAutokonsumpcja(), 100.5);
    EXPECT_FLOAT_EQ(ld2.getEksport(), 200.5);
    EXPECT_FLOAT_EQ(ld2.getImport(), 300.5);
    EXPECT_FLOAT_EQ(ld2.getPobor(), 400.5);
    EXPECT_FLOAT_EQ(ld2.getProdukcja(), 500.5);
}

/// \brief Testuje funkcj� waliduj�c� puste linie.
/// \details Sprawdza, czy funkcja zwraca false dla pustej linii.
TEST(LineValidationTest, EmptyLine) {
    string line = "";
    EXPECT_FALSE(lineValidation(line));
}

/// \brief Testuje funkcj� waliduj�c� linie z nag��wkami.
/// \details Sprawdza, czy funkcja zwraca false dla linii z nag��wkiem.
TEST(LineValidationTest, HeaderLine) {
    string line = "Time,Autokonsumpcja (W),Eksport (W),Import (W),Pobor (W),Produkcja (W)";
    EXPECT_FALSE(lineValidation(line));
}

/// \brief Testuje funkcj� waliduj�c� linie z nieprawid�owymi znakami.
/// \details Sprawdza, czy funkcja zwraca false dla linii z literami.
TEST(LineValidationTest, LineWithInvalidCharacters) {
    string line = "2023-10-15 12:00:00,X,200.5,300.5,400.5,500.5";
    EXPECT_FALSE(lineValidation(line));
}

/// \brief Testuje dodawanie danych do struktury drzewa.
/// \details Sprawdza, czy dane s� poprawnie przechowywane w strukturze drzewa.
TEST(TreeDataTest, AddData) {
    TreeData treeData;
    string line = "15.10.2023 12:00:00,100.5,200.5,300.5,400.5,500.5";
    LineData ld(line);
    treeData.addData(ld);

    vector<LineData> data = treeData.getDataBetweenDates("15.10.2023 00:00", "15.10.2023 23:59");
    ASSERT_EQ(data.size(), 1);
    EXPECT_EQ(data[0].getDate(), "15.10.2023 12:00:00");
    EXPECT_FLOAT_EQ(data[0].getAutokonsumpcja(), 100.5);
    EXPECT_FLOAT_EQ(data[0].getEksport(), 200.5);
    EXPECT_FLOAT_EQ(data[0].getImport(), 300.5);
    EXPECT_FLOAT_EQ(data[0].getPobor(), 400.5);
    EXPECT_FLOAT_EQ(data[0].getProdukcja(), 500.5);
}

/// \brief Testuje obliczanie sum w strukturze drzewa.
/// \details Sprawdza, czy sumy s� poprawnie obliczane w okre�lonym przedziale czasowym.
TEST(TreeDataTest, CalculateSumsBetweenDates) {
    TreeData treeData;
    string line1 = "15.10.2023 12:00:00,100.5,200.5,300.5,400.5,500.5";
    string line2 = "15.10.2023 18:00:00,150.5,250.5,350.5,450.5,550.5";
    LineData ld1(line1);
    LineData ld2(line2);
    treeData.addData(ld1);
    treeData.addData(ld2);

    float autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum;
    treeData.calculateSumsBetweenDates("15.10.2023 00:00", "15.10.2023 23:59", autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum);

    EXPECT_FLOAT_EQ(autokonsumpcjaSum, 251.0);
    EXPECT_FLOAT_EQ(eksportSum, 451.0);
    EXPECT_FLOAT_EQ(importSum, 651.0);
    EXPECT_FLOAT_EQ(poborSum, 851.0);
    EXPECT_FLOAT_EQ(produkcjaSum, 1051.0);
}
