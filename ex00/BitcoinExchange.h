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
    ~BitcoinExchange();

    static void printFileData(std::deque<std::string> &fileData);
    const std::map<std::string, double> &getDateMap();

private:
    std::map<std::string, double> _dataMap;

    std::string trimWhiteSpace(std::string str);
    void readDataIntoMap(const std::string &fname);
    void readFileAndExchange(const std::string &fname);
    std::string errorCheck(std::deque<std::string> &row);
    std::string invalidDateCheck(const std::string &date);
    std::string trimZerosAfterDecimal(double value);

};

#endif //CPP09_BitcoinExchange_H
