//
// Created by saozcan on 6/18/23.
//

#include "BitcoinExchange.h"

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &BitcoinExchange) {
    return *this;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &BitcoinExchange) {
    *this = BitcoinExchange;
}

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}


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
        std::cout<<"File not found\n"; //TODO: throw exception
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
            double exhangeValue = 0.0;
            if (row.size() == 2) {
                if (it != _dataMap.end()) {
                    if (errorCheck(row) != "") {
                        _fileData.push_back(errorCheck(row));
                        continue;
                    }
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
        std::cout<<"File not found\n"; //TODO: throw exception
}


/**
 * Print functions
 */
void BitcoinExchange::printData(const std::map<std::string, double> &map) {
    std::map<std::string, double>::const_iterator it = map.begin();
    for(;it!=map.end();it++)
        std::cout<<it->first<<" "<<it->second<<std::endl;
    std::cout<<"finished printing\n";
}

void BitcoinExchange::printFileData(const std::vector<std::string> &fileData) {
    for(int i=0;i<fileData.size();i++)
        std::cout<<fileData[i]<<std::endl;
    std::cout<<"finished printing\n";
}

BitcoinExchange::BitcoinExchange(const std::string &fname) {
    readDataIntoMap(CSV_FILE);
    readFileAndExchange(fname);
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
    return "";
}

/**
 * olds
 */
//void BitcoinExchange::readFile(const std::string &fname) {
//    std::vector<std::string> row;
//    std::string line, word;
//
//    std::fstream file (fname, std::ios::in);
//    if(file.is_open())
//    {
//        while(getline(file, line))
//        {
//            row.clear();
//            std::stringstream str(line);
//            while(getline(str, word, '|'))
//                row.push_back(trimWhiteSpace(word));
//            _fileData.push_back(row);
//        }
//    }
//    else
//        std::cout<<"File not found\n"; //TODO: throw exception
//}

int BitcoinExchange::getBitcoinValue(int year, int month, int day) {
    if (year < 2009 || year > 2023 || month < 1 || month > 12 || day < 1 || day > 31)
        return INVALID_DATE;

    std::string searchDate = getDate(year, month, day);
    int btcValue = -1;

    for(int i=0;i<_data.size();i++)
    {
        if(_data[i][0] == searchDate)
            btcValue = atoi(_data[i][1].c_str());
    }
    if (btcValue == -1)
        return getClosestBitcoinValue(year, month, day);
    return btcValue;
}

int BitcoinExchange::getClosestBitcoinValue(int year, int month, int day) {
    int k = 1;

    for(int i=0; i < _data.size(); i++)
    {
        if (day - k < 1) {
            k = 1;
            if (month - 1 < 1) {
                day = 32;
                month = 12;
                year -= 1;
            }
            else {
                day = 31;
                month -= 1;
            }
        }
        std::string date = getDate(year, month, day - k);
        for(int j=0; j < _data.size(); j++)
        {
            if(_data[j][0] == date)
                return atoi(_data[j][1].c_str());
        }
        cout << date << endl;
        k += 1;
    }
    return INVALID_DATE;
}

void BitcoinExchange::readData(const std::string &fname) {
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
                row.push_back(word);
            _data.push_back(row);
        }
    }
    else
        std::cout<<"File not found\n"; //TODO: throw exception
}

std::string BitcoinExchange::getDate(int year, int month, int day) {
    std::string searchDate = std::to_string(year) + "-";
    if (month < 10)
        searchDate += "0" + std::to_string(month) + "-";
    else
        searchDate += std::to_string(month) + "-";
    if (day < 10)
        searchDate += "0" + std::to_string(day);
    else
        searchDate += std::to_string(day);
    return searchDate;
}






