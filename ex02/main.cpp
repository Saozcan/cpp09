#include <iostream>
#include <vector>
#include "PmergeMe.h"
#include <exception>

int main(int ac, char **av) {
    
    if (ac == 1) {
        return 0;
    }

    try {
        PmergeMe pmergeMe(av);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
