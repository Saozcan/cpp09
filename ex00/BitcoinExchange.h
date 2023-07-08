//
// Created by saozcan on 6/18/23.
//

#ifndef CPP09_BitcoinExchange_H
#define CPP09_BitcoinExchange_H

#include <vector>
#include "map"
#include <string>
#include "fstream"
#include <sstream>
#include <iostream>
#include <cstdlib>

#define CSV_FILE "data.csv"

using std::cout;
using std::endl;

enum BtcErrors{
    INVALID_DATE = -9999,
    NOT_POSITIVE,
    BAD_INPUT,
    TOO_LARGE_NUMBER,
};

class BitcoinExchange {
public:
    BitcoinExchange();
    BitcoinExchange(const std::string &fname);
    BitcoinExchange(const BitcoinExchange &BitcoinExchange);
    BitcoinExchange &operator=(const BitcoinExchange &BitcoinExchange);
    ~BitcoinExchange();

    void readDataIntoMap(const std::string &fname);
    void readFileAndExchange(const std::string &fname);
    static void printFileData(const std::vector<std::string> &fileData);
    std::string errorCheck(const std::vector<std::string> &row);


    void readData(const std::string &fname);
//    void readFile(const std::string &fname);
    static void printData(const std::map<std::string, double> &map);
    int getBitcoinValue(int year, int month, int day);


    const std::map<std::string, double> &getDateMap();
    const std::vector<std::string> &getFileDate();

private:
    std::vector<std::string> _fileData;
    std::map<std::string, double> _dataMap;

    std::vector<std::vector<std::string>> _data;
    std::map<std::string, double> _fileDateMap;

    int getClosestBitcoinValue(int year, int month, int day);
    std::string getDate(int year, int month, int day);
    std::string trimWhiteSpace(std::string str);

};

#endif //CPP09_BitcoinExchange_H
