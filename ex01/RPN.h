//
// Created by saozcan on 7/8/23.
//

#ifndef EX01_RPN_H
#define EX01_RPN_H

#include <vector>
#include "stack"
#include "iostream"

class RPN {

public:
    RPN();
    RPN(const std::string &str);
    RPN(const RPN& obj);
    RPN &operator=(const RPN& obj);
    ~RPN();

    void print();

private:
    std::vector<std::vector<char>> _stack;
    std::stack<int> _tempStack;

    void checkAndCalculate(const std::vector<char> &stack);
    int _calculate(int a, int b, char op);
    //Helper functions
};


#endif //EX01_RPN_H
