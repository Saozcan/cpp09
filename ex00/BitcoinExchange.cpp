//
// Created by saozcan on 6/18/23.
//

#include <cstring>
#include "BitcoinExchange.h"

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &BitcoinExchange) {
    return *this;
}

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
    _fileData.clear();
}


/**
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

    std::fstream file (fname, std::ios::in);
    if(file.is_open())
    {
        while(getline(file, line))
        {
            if (line.empty() || line == "date | value")
                continue;
            row.clear();
            std::stringstream str(line);
            while(getline(str, word, '|'))
                row.push_back(trimWhiteSpace(word));
            std::map<std::string, double>::iterator it = _dataMap.find(trimWhiteSpace(row[0]));
            double exhangeValue;
            if (row.size() == 2) {
                if (!errorCheck(row).empty()) {
                    _fileData.push_back(errorCheck(row));
                    continue;
                }
                if (it != _dataMap.end()) {
                    exhangeValue = it->second * atof(row[1].c_str());
                }
                else
                    exhangeValue = _dataMap.upper_bound(trimWhiteSpace(row[0]))->second * atof(row[1].c_str());
            }
            else {
                _fileData.push_back("Error: bad input => " + row[0]);
                continue;
            }
            _fileData.push_back(row[0] + " => " + row[1] + " = " + std::to_string(exhangeValue));
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

const std::vector<std::string> &BitcoinExchange::getFileDate() {
    return _fileData;
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
        return "Error: invalid date format.";
    if (atol(date.substr(5, 2).c_str()) < 1 || atol(date.substr(5, 2).c_str()) > 12)
        return "Error: invalid date format.";
    if (atol(date.substr(8, 2).c_str()) < 1 || atol(date.substr(8, 2).c_str()) > 31)
        return "Error: invalid date format.";
    return "";
}

