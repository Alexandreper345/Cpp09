#include "RPN.hpp"

RPN::RPN()
{
}


void    RPN::execute(const std::string& expression)
{
    for (size_t i = 0; i < expression.length(); i++)
    {
        if (expression[i] == ' ')
            continue;
            else if (expression[i] >= '0' && expression[i] <= '9')
            _stack.push(expression[i] - '0');
            else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
            {
                if (_stack.size() < 2)
                {
                    std::cerr << "Error: not enough operands for operator " << expression[i] << std::endl;
                    return ;
                }
                int b = _stack.top();
                _stack.pop();
                int a = _stack.top();
                _stack.pop();
            int result;
            switch (expression[i])
            {
                case '+':
                result = a + b;
                break;
                case '-':
                result = a - b;
                break;
                case '*':
                result = a * b;
                break;
                case '/':
                if (b == 0)
                {
                    std::cerr << "Error: division by zero" << std::endl;
                    return ;
                }
                result = a / b;
                break;
            }
            _stack.push(result);
        }
        else
        {
            std::cerr << "Error: invalid character " << expression[i] << std::endl;
            return ;
        }
    }
    if (_stack.size() != 1)
    {
        std::cerr << "Error: invalid expression" << std::endl;
        return ;
    }
    std::cout << _stack.top() << std::endl;
}


RPN::~RPN()
{
}