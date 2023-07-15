//
// Created by saozcan on 7/8/23.
//

#include "RPN.h"

int main(int ac, char** av) {

    if (ac != 2) {
        std::cout << "Usage: ./ex01 \"<string>\"" << std::endl;
        return 1;
    }

    try {
        RPN rpn(av[1]);
        rpn.print();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
