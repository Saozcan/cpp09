#include <iostream>
#include "BitcoinExchange.h"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        cout << "Usage: ./a.out <filename>" << endl;
        return 1;
    }

    try {
        BitcoinExchange btcExchange(av[1]);
    } catch (std::exception &e) {
        cout << e.what() << endl;
    }

//    cout << "Btc value: " << btcExchange.getBitcoinValue(2022, 02, 01) << endl;

    return 0;
}