
#include <iostream>
#include "kalkulator_BER.h"
#include "calculateResullt.h"
#include "logger.h"


using namespace std;

std::stringstream msg;
clock_t czas1;
clock_t czas2;


testData zaladujZpliku(string path1, string path2) {
    unsigned char num;
    string sciezka{};
    bool przelacznik{true};
    int licznik{0};
    testData daneTestowe;

    while (przelacznik) {
        if (licznik == 0) sciezka = path1;
        if (licznik == 1) sciezka = path2;
        ifstream file(sciezka, ios::binary | ios::out);
        if (!file.is_open()) {
            cout << "Błąð podczas otwierania pliku." << endl;
        } else {
            while (!file.eof()) {
                if (sciezka == path1 && !file.eof()) {
                    file.read((char *) &num, sizeof(num));
                    daneTestowe.data1.push_back(num);
                } else if (sciezka == path2 && !file.eof()) {
                    file.read((char *) &num, sizeof(num));
                    daneTestowe.data2.push_back(num);
                }
            }
            file.close();
        }
        licznik++;
        if(licznik == 2) przelacznik = false;
    }
    return daneTestowe;
}
void test_1()
{
    otworzLoga("tests.txt");

    testData test_1_data;
    const string s1 = "test_1_1.dat";
    const string s2 = "test_1_2.dat";
    char val_1;
    char val_2;
    int zleBity{0};
    double BER_value;
    clock_t time = clock();
    test_1_data = zaladujZpliku(s1, s2);
    size_t calokwitaIloscBitow = test_1_data.data1.size() * 2 * 8;
    czas1=clock();
    for (int i = 0; i <  test_1_data.data1.size(); ++i) {
        val_1 = test_1_data.data1.at(i);
        val_2 = test_1_data.data2[i];
        zleBity+= policzBadBits(reinterpret_cast<char>(val_1), reinterpret_cast<char>(val_2));
        BER_value = zleBity / (double)calokwitaIloscBitow;

    }
    czas2=clock();
    msg<<"Test 1 zakończony"<<endl;
    msg << "Ilość błędnych bitów w teście 1 : " << zleBity << endl;
    msg<<"Bit Error Rate w teście 1 : "<< BER_value<<endl;
    msg << "Czas obliczeń wyniósł : " << fixed << ((float)czas2 - czas1) / CLOCKS_PER_SEC << " sec " << std::endl;
    msg<<"================================================"<<endl;
    zapiszLog(msg.str());
    zamknijLog();
}
void test_2()
{
    otworzLoga("tests.txt");

    testData test_2_data;
    const string s3 = "test_2_1.dat";
    const string s4 = "test_2_2.dat";
    char val_1;
    char val_2;
    int zleBity{0};
    double BER_value;
    test_2_data = zaladujZpliku(s3, s4);
    size_t totalNumOfBits = test_2_data.data1.size() * 2* 8;
    czas1=clock();
    for (int i = 0; i < 100; ++i) {
        val_1 = test_2_data.data1[i];
        val_2 = test_2_data.data2[i];
        zleBity+= policzBadBits(reinterpret_cast<char>(val_1), reinterpret_cast<char>(val_2));
        BER_value = zleBity/(double)totalNumOfBits;
    }
    czas2=clock();
    msg<<"Test 2 zakończony"<<endl;
    msg<<"Ilość błędnych bitów w teście 2 : "<< zleBity<<endl;
    msg<<"Bit Error Rate w teście 2 : "<< BER_value<<endl;
    msg <<"Czas obliczeń wyniósł : " << fixed << ((float)czas2 - czas1) / CLOCKS_PER_SEC << " sec " << std::endl;
    msg<<"================================================"<<endl;
    zapiszLog(msg.str());
    zamknijLog();
}
void test_3()
{
    otworzLoga("tests.txt");
    testData test_3_data;
    const string s5 = "test_3_1.dat";
    const string s6 = "test_3_2.dat";
    char val_1;
    char val_2;
    int zleBity{0};
    double BER_value;
    test_3_data = zaladujZpliku(s5, s6);
    size_t totalNumOfBits = test_3_data.data2.size()*2*8;
    czas1=clock();

    for (int i = 0; i < 400000000; ++i) {
        val_1 = test_3_data.data1[i];
        val_2 = test_3_data.data2[i];
        zleBity+= policzBadBits(reinterpret_cast<char>(val_1), reinterpret_cast<char>(val_2));
        BER_value = zleBity/(double)totalNumOfBits;
    }
    czas2=clock();
    msg<<"Test 3 performed"<<endl;
    msg<<"Number of bad bits in test 3 files : "<< zleBity<<endl;
    msg<<"Bit Error Rate for files in Test 3 : "<< BER_value<<endl;
    msg<<"End of log for test 3"<<endl;
    msg << "Time of the calculation was: " << fixed << ((float)czas2 - czas1) / CLOCKS_PER_SEC << " sec " << std::endl;
    msg<<"======================================================="<<endl;
    zapiszLog(msg.str());
    zamknijLog();
}

