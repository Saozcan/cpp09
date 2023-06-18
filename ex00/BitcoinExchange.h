//
// Created by saozcan on 6/18/23.
//

#ifndef CPP09_BitcoinExchange_H
#define CPP09_BitcoinExchange_H

#include <vector>
#include <string>
#include "fstream"
#include <sstream>
#include <iostream>
#include <cstdlib>

#define CSV_FILE "data.csv"

using std::cout;
using std::endl;

enum BtcErrors{
    INVALID_DATE = -10,
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

    void readData(const std::string &fname);
    viod readFile(const std::string &fname);
    void printData();
    int getBitcoinValue(int year, int month, int day);

private:
    std::vector<std::vector<std::string>> _data;
    std::vector<std::vector<std::string>> _fileData;

    int getClosestBitcoinValue(int year, int month, int day);
    std::string getDate(int year, int month, int day);

};

#endif //CPP09_BitcoinExchange_H
