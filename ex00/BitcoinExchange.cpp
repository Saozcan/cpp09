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


/**œ
 * Read functions
 */
void BitcoinExchange::readDataIntoMap(const std::string &fname) {
    std::vector<std::string> row;
    std::string line, word;

    std::fstream file (fname, std::ios::in);
    if(file.is_open())
    {
        while(getline(file, line))
        {
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
    std::vector<std::string> row;
    std::string line, word;
    int pass = 0;

    std::fstream file (fname, std::ios::in);
    if(file.is_open())
    {
        while(getline(file, line))
        {
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
                    exchangeValue = _dataMap.upper_bound(trimWhiteSpace(row[0]))->second * atof(row[1].c_str());
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
void BitcoinExchange::printFileData(const std::vector<std::string> &fileData) {
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

std::string BitcoinExchange::errorCheck(const std::vector<std::string> &row) {
    if (atof(row[1].c_str()) < 0)
        return "Error: not a positive number.";
    if (atol(row[1].c_str()) > INT32_MAX)
        return "Error: too large a number.";
    return invalidDateCheck(trimWhiteSpace(row[0]));
}

std::string BitcoinExchange::invalidDateCheck(const std::string &date) {
    if (date.length() != 10)
        return "Error: invalid date format.";
    if (date[4] != '-' || date[7] != '-')
        return "Error: invalid date format.";
    if (atol(date.substr(0, 4).c_str()) < 2009 || atol(date.substr(0, 4).c_str()) > 2023)
        return "Error: Out of range.";
    if (atol(date.substr(5, 2).c_str()) < 1 || atol(date.substr(5, 2).c_str()) > 12)
        return "Error: invalid date format.";
    if (atol(date.substr(8, 2).c_str()) < 1 || atol(date.substr(8, 2).c_str()) > 31)
        return "Error: invalid date format.";
    return "";
}

std::string BitcoinExchange::trimZerosAfterDecimal(double value) {
    std::string str = std::to_string(value);
    size_t decimalPos = str.find('.');
    if (decimalPos != std::string::npos) {
        size_t lastNonZero = str.find_last_not_of('0');
        if (lastNonZero != std::string::npos && lastNonZero > decimalPos)
            str.erase(lastNonZero + 1);
    }
    return str;
}

