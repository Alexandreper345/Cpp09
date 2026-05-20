#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(std::string file)
{
	if (file.size() < 4 || file.substr(file.size() - 4) != ".txt")
		std::cerr << "Error: invalid file extension\n" << std::endl;

	std::ifstream fileStream(file);
	if (!fileStream.is_open())
		std::cerr << "Error: cannot open file\n" << std::endl;

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		this->_database = other._database;
	return *this;
}

void	BitcoinExchange::save_in_database()
{
	std::ifstream fileStream("data.csv");
	if (!fileStream.is_open())
		std::cerr << "Error: cannot open data.csv\n" << std::endl;
	
}

BitcoinExchange::~BitcoinExchange(){}