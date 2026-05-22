#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>

class RPN
{
private:
    std::stack<int> _stack;
public:
    RPN();
    RPN(const RPN& other) = delete;
    RPN& operator=(const RPN& other) = delete;
    void execute(const std::string& expression);
    ~RPN();
};

#endif