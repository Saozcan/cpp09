//
// Created by saozcan on 7/8/23.
//

#include "RPN.h"

RPN::RPN() {

}

RPN::~RPN() {

}

RPN::RPN(const std::string &str) {
    std::vector<char> firstStack;
    for (int i = 0; i < str.length(); i++) {
        if (isspace(str[i]))
            continue;
        firstStack.push_back(str[i]);
    }
    _stack.push_back(firstStack);
}

RPN::RPN(const RPN &obj) {
    *this = obj;
}

RPN &RPN::operator=(const RPN &obj) {
    if (this != &obj) {
        // copy
    }
    return *this;
}

void RPN::print() {
    checkAndCalculate(_stack[0]);
    std::stack<int> tempStack = _tempStack;
    while (!tempStack.empty()) {
        std::cout << tempStack.top() << " ";
        tempStack.pop();
    }
    std::cout << std::endl;
}
//endline silinecek

void RPN::checkAndCalculate(const std::vector<char> &stack) {
    std::stack<int> tempStack;
    for (int i = 0; i < stack.size(); i++) {
        if (isdigit(stack[i])) {
            tempStack.push((stack[i] - '0'));
        } else {
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
    std::cout << "a: " << a << " b: " << b << " op: " << op << std::endl;
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



