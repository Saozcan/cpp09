//
// Created by saozcan on 7/8/23.
//

#include "RPN.h"

int main(int ac, char** av) {

    if (ac != 2) {
        std::cout << "Usage: ./ex01 \"<string>\"" << std::endl;
        return 1;
    }

    RPN rpn(av[1]);

    rpn.print();
    return 0;
}
