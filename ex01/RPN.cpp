//
// Created by saozcan on 7/8/23.
//

#include "RPN.h"

RPN::RPN() {
}

RPN::~RPN() {
}

RPN::RPN(const std::string &str) {
    const std::string checkArr = "0123456789+-*/ ";
    for (int i = 0; i < str.length(); i++) {
        if (checkArr.find(str[i]) == std::string::npos)
            throw std::runtime_error("Typing Error: Invalid Arguments...");
        else if (str[i] != ' ')
            this->_allNumbs += str[i];
    }
    checkAndCalculate(_allNumbs);
}

RPN::RPN(const RPN &obj) {
    *this = obj;
}

RPN &RPN::operator=(const RPN &obj) {
    this->_tempStack = obj._tempStack;
    return *this;
}

void RPN::print() {
    std::stack<int> tempStack = _tempStack;
    while (!tempStack.empty()) {
        std::cout << tempStack.top() << " ";
        tempStack.pop();
    }
    std::cout << std::endl;
}

void RPN::checkAndCalculate(const std::string &stack) {
    std::stack<int> tempStack;
    for (int i = 0; i < stack.size(); i++) {
        if (isdigit(stack[i])) {
            tempStack.push((stack[i] - '0'));
        } else {
            if (tempStack.size() <= 1)
                throw std::runtime_error("Typing Error...");
            int a = tempStack.top();
            tempStack.pop();
            int b = tempStack.top();
            tempStack.pop();
            tempStack.push(_calculate(a, b, stack[i]));
        }
    }
    _tempStack = tempStack;
}

int RPN::_calculate(int a, int b, char op) {
    if (op == '/' && b == 0) {
        throw std::invalid_argument("Bad condition...");
    }
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '/':
            return a / b;
        case '*':
            return a * b;
        default:
            return 0;
    }
}



