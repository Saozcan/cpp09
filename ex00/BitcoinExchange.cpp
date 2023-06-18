//
// Created by saozcan on 6/18/23.
//

#include "BitcoinExchange.h"

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &BitcoinExchange) {
    return *this;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &BitcoinExchange) {}

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

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

void BitcoinExchange::printData() {
    for(int i=0;i<_data.size();i++)
    {
        for(int j=0;j<_data[i].size();j++)
        {
            std::cout<<_data[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}

BitcoinExchange::BitcoinExchange(const std::string &fname) {
    readData(CSV_FILE);
}

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















