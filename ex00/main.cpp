#include <iostream>
#include "BitcoinExchange.h"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        cout << "Usage: ./a.out <filename>" << endl;
        return 1;
    }

    BitcoinExchange btcExchange(av[1]);

    btcExchange.printFileData(btcExchange.getFileDate());

//    cout << "Btc value: " << btcExchange.getBitcoinValue(2022, 02, 01) << endl;

    return 0;
}