#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(std::string file)
{
	if (file.size() < 4 || file.substr(file.size() - 4) != ".txt")
	{
		std::cerr << "Error: invalid file extension\n" << std::endl;
		return ;
	}

	this->save_in_database();
	std::ifstream fileStream(file);
	if (!fileStream.is_open())
	{
		std::cerr << "Error: cannot open file\n" << std::endl;
		return ;
	}
	std::string line;
	while (std::getline(fileStream, line))
	{
		std::string date = line.substr(0, line.find('|'));
		std::string value = line.substr(line.find('|') + 1);
		if (date.empty() || value.empty())
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (data.find(date) != data.end())
		{
			std::cerr << "Error: duplicate date => " << date << std::endl;
			continue;
		}
		if (this->_database.find(date) == this->_database.end())
		{
			std::cerr << "Error: date not found in database => " << date << std::endl;
			continue;
		}
		double valueDouble;
		try
		{
			valueDouble = std::stod(value);
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: invalid value => " << value << std::endl;
			continue;
		}
		if (valueDouble < 0)
		{
			std::cerr << "Error: not a positive number => " << value << std::endl;
			continue;
		}
		if (valueDouble > 1000)
		{
			std::cerr << "Error: too large a number => " << value << std::endl;
		}
		std::map<std::string, double>::iterator it = this->_database.lower_bound(date);
		if (it == this->_database.end())
			it = --this->_database.end();
		else if (it->first != date && it != this->_database.begin())
		{
			--it;
		}
		std::cout << date << " => " << valueDouble << " = " << valueDouble * it->second << std::endl;
		data[date] = valueDouble;
	}
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
	{
		std::cerr << "Error: cannot open data.csv\n" << std::endl;
		return ;
	}
	std::string line;
	std::getline(fileStream, line);
	
	while (std::getline(fileStream, line))
	{
		_database[line.substr(0, line.find(','))] = std::stod(line.substr(line.find(',') + 1));
	}
}

BitcoinExchange::~BitcoinExchange(){}