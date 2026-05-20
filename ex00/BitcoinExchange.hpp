#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <fstream>

class BitcoinExchange
{
private:
	std::map<std::string, double>	_database;
	std::map<std::string, double>	data;
public:
	BitcoinExchange();
	BitcoinExchange(std::string file);
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	~BitcoinExchange();

	void	save_in_database(void);

};
#endif