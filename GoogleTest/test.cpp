#include "pch.h"
#include "../analizaEnergetyczna/LineData.h"
#include "../analizaEnergetyczna/LineData.cpp"
#include "../analizaEnergetyczna/TreeData.h"
#include "../analizaEnergetyczna/TreeData.cpp"
#include "../analizaEnergetyczna/Logger.h"
#include "../analizaEnergetyczna/Logger.cpp"

using namespace std;

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

//TEST(TreeDataTest, Serialization) {
//    TreeData treeData;
//    string line = "15.10.2023 12:00:00,100.5,200.5,300.5,400.5,500.5";
//    LineData ld(line);
//    treeData.addData(ld);
//
//    ofstream out("treeData.bin", ios::binary);
//    treeData.serialize(out);
//    out.close();
//
//    TreeData treeData2;
//    ifstream in("treeData.bin", ios::binary);
//    treeData2.deserialize(in);
//    in.close();
//
//    vector<LineData> data = treeData2.getDataBetweenDates("15.10.2023 00:00", "15.10.2023 23:59");
//    ASSERT_EQ(data.size(), 1);
//    EXPECT_EQ(data[0].getDate(), "15.10.2023 12:00:00");
//    EXPECT_FLOAT_EQ(data[0].getAutokonsumpcja(), 100.5);
//    EXPECT_FLOAT_EQ(data[0].getEksport(), 200.5);
//    EXPECT_FLOAT_EQ(data[0].getImport(), 300.5);
//    EXPECT_FLOAT_EQ(data[0].getPobor(), 400.5);
//    EXPECT_FLOAT_EQ(data[0].getProdukcja(), 500.5);
//}