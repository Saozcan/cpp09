cmake_minimum_required(VERSION 3.25)
project(cpp09)

set(CMAKE_CXX_STANDARD 14)

include_directories(ex00)

add_executable(cpp09
        ex00/main.cpp ex00/BitcoinExchange.h ex00/BitcoinExchange.cpp ex00/Btc.h)
