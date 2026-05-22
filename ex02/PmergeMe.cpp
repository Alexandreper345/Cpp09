#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

void PmergeMe::parseInput(char **argv)
{
    for (int i = 1; argv[i] != nullptr; ++i)
    {
        try
        {
            int num = std::stoi(argv[i]);
            if (num < 0)
                throw std::invalid_argument("Negative numbers are not allowed");
            _vec.push_back(num);
            _deq.push_back(num);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

void PmergeMe::mergeInsertionSortVector(std::vector<int>& vec)
{
    if (vec.size() <= 1)
        return ;
    if (vec.size() <= 10)
    {
        std::sort(vec.begin(), vec.end());
        return ;
    }
    std::vector<int> left(vec.begin(), vec.begin() + vec.size() / 2);
    std::vector<int> right(vec.begin() + vec.size() / 2, vec.end());
    mergeInsertionSortVector(left);
    mergeInsertionSortVector(right);
    std::merge(left.begin(), left.end(), right.begin(), right.end(), vec.begin());
}

void PmergeMe::mergeInsertionSortDeque(std::deque<int>& deq)
{
    if (deq.size() <= 1)
        return ;
    if (deq.size() <= 10)
    {
        std::sort(deq.begin(), deq.end());
        return ;
    }
    std::deque<int> left(deq.begin(), deq.begin() + deq.size() / 2);
    std::deque<int> right(deq.begin() + deq.size() / 2, deq.end());
    mergeInsertionSortDeque(left);
    mergeInsertionSortDeque(right);
    std::merge(left.begin(), left.end(), right.begin(), right.end(), deq.begin());
}

void PmergeMe::printBefore() const
{
    std::cout << "Before: ";
    for (size_t i = 0; i < _vec.size(); ++i)
    {
        std::cout << _vec[i] << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::printAfter() const
{
    std::cout << "After: ";
    for (size_t i = 0; i < _vec.size(); ++i)
    {
        std::cout << _vec[i] << " ";
    }
    std::cout << std::endl;
}


PmergeMe::~PmergeMe()
{
}


void PmergeMe::process()
{
    printBefore();
    mergeInsertionSortVector(_vec);
    mergeInsertionSortDeque(_deq);
    printAfter();
}