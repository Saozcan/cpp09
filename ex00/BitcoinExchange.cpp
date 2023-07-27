//
// Created by saozcan on 6/18/23.
//

#include <cstring>
#include "BitcoinExchange.h"

BitcoinExchange::BitcoinExchange(const BitcoinExchange &BitcoinExchange) {
    *this = BitcoinExchange;
}


BitcoinExchange::BitcoinExchange(const std::string &fname) {
    readDataIntoMap(CSV_FILE);
    readFileAndExchange(fname);
}

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {
    _dataMap.clear();
}


/**
 * Read functions
 */
void BitcoinExchange::readDataIntoMap(const std::string &fname) {
    std::deque<std::string> row;
    std::string line, word;

    std::fstream file (fname, std::ios::in);
    if(file.is_open()) {
        while(getline(file, line)) {
            row.clear();
            std::stringstream str(line);
            while(getline(str, word, ','))
                row.push_back(trimWhiteSpace(word));
            if (row.size() == 2)
                _dataMap.insert(std::pair<std::string, double>(row[0], atof(row[1].c_str())));
        }
    }
    else
        throw std::invalid_argument("Cannot open file\n");
}

void BitcoinExchange::readFileAndExchange(const std::string &fname) {
    std::deque<std::string> row;
    std::string line, word;
    int pass = 0;

    std::fstream file (fname, std::ios::in);
    if(file.is_open()) {
        while(getline(file, line)) {
            if (pass++ == 0)
                continue;
            row.clear();
            std::stringstream str(line);
            while(getline(str, word, '|'))
                row.push_back(trimWhiteSpace(word));
            std::map<std::string, double>::iterator it = _dataMap.find(trimWhiteSpace(row[0]));
            double exchangeValue;
            if (row.size() == 2) {
                if (!errorCheck(row).empty()) {
                    std::cout << (errorCheck(row)) << std::endl;
                    continue;
                }
                if (it != _dataMap.end()) {
                    exchangeValue = it->second * atof(row[1].c_str());
                }
                else
                {
                    std::map<std::string, double>::iterator it = _dataMap.lower_bound(trimWhiteSpace(row[0]));
                    std::string previousKey;
                    if(it != _dataMap.begin()){
                        it--;
                        previousKey = it->first;
                    }
                    exchangeValue = _dataMap.find(previousKey)->second * atof(row[1].c_str());
                }
            }
            else {
                std::cout << ("Error: bad input => " + row[0]) << std::endl;
                continue;
            }
            std::string trimmedValue = trimZerosAfterDecimal(exchangeValue);
            std::cout << (row[0] + " => " + row[1] + " = " + trimmedValue) << std::endl;
}
    }
    else
        throw std::invalid_argument("Cannot open file\n");
}


/**
 * Print
 */
void BitcoinExchange::printFileData(std::deque<std::string> &fileData) {
    for(int i=0;i<fileData.size();i++)
        std::cout<<fileData[i]<<std::endl;
}


/**
 * Getters
 */
const std::map<std::string, double>& BitcoinExchange::getDateMap() {
    return _dataMap;
}


/**
 * Helpers
 */
std::string BitcoinExchange::trimWhiteSpace(std::string str) {
    int i = 0;
    while (str[i] == ' ')
        i++;
    str = str.substr(i, str.length() - i);
    i = str.length() - 1;
    while (str[i] == ' ')
        i--;
    str = str.substr(0, i + 1);
    return str;
}

std::string BitcoinExchange::errorCheck(std::deque<std::string> &row) {
    if (atof(row[1].c_str()) < 0)
        return "Error: not a positive number.";
    if (atol(row[1].c_str()) > 1000)
        return "Error: too large a number.";
    return invalidDateCheck(trimWhiteSpace(row[0]));
}

std::string BitcoinExchange::invalidDateCheck(const std::string &date) {
    if (date.length() != 10)
        return "Error: invalid date format.";
    if (date[4] != '-' || date[7] != '-')
        return "Error: invalid date format.";

    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());
    int monthLimits[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    std::cout << date << std::endl;

    if (year < 2009 || year > 2023){
        std::cout << year << std::endl;
        return "Error: Out of range.";
    }
    if (month < 1 || month > 12)
        return "Error: invalid date format.";
    if (day < 1 || day > monthLimits[month - 1])
        return "Error: invalid date format.";
    if (year == 2009 && month == 1 && day == 1) {
        std::cout << "Hello\n";
        return "Error: Out of range.";
    }
    if (year == 2022 && month >= 3 || day > 29) {
        return "Error: Out of range.";
    }
    return "";
}

std::string BitcoinExchange::trimZerosAfterDecimal(double value) {
    std::string str = std::to_string(value);
    std::string::iterator it = prev(str.end());
    if (value == 0.0)
        return "0";
    for (; it != str.begin() ; it--) {
        if (*it == '0' || *it == '.')
            str.pop_back();
        else
            break;
    }
    return str;
}


/**
 * tarih icinde sayi haric gelenlerin kontrolu
 * if 29 dan buyukse kontrolu 
 * 