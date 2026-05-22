#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <stdexcept>
#include <chrono>

class PmergeMe
{
private:
    std::vector<int> _vec;
    std::deque<int> _deq;
public:
    PmergeMe();
    PmergeMe(const PmergeMe& other) = delete;
    PmergeMe& operator=(const PmergeMe& other) = delete;
    ~PmergeMe();
    
    void parseInput(char **argv);
    void mergeInsertionSortVector(std::vector<int>& vec);
    void mergeInsertionSortDeque(std::deque<int>& deq);
    void printBefore() const;
    void printAfter() const;

    void process();
};

#endif