#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

std::string trim(const std::string& str)
{
	size_t start = str.find_first_not_of(" \t\r\n");
	size_t end = str.find_last_not_of(" \t\r\n");

	if (start == std::string::npos)
		return "";
	
	return str.substr(start, end - start + 1);
}

bool isLeap(int year)
{
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}
bool BitcoinExchange::validDate(const std::string& date)
{
	if (date.length() != 10)
		return false;
	
	if (date[4] != '-' || date[7] != '-')
		return false;
	
	for (size_t i = 0; i < date.length(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		
		if (!std::isdigit(date[i]))
			return false;
	}

	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	int	year = std::atoi(date.substr(0, 4).c_str());
	int	daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};

	if (month < 1 || month > 12)
		return false;
	
	if (day < 1 || day > 31)
		return false;

	if (month == 2)
	{
		if (day > 28 + isLeap(year))
			return false;
	}
	else if (day > daysInMonth[month - 1])
		return false;


	return true;
}


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
	std::getline(fileStream, line);
	while (std::getline(fileStream, line))
	{

		line = trim(line);
		if (line.empty())
			continue;

		if (line[0] == '#')
			continue;

		size_t pipe = line.find("|");


		if (pipe == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = trim(line.substr(0, pipe));
		std::string value = trim(line.substr(pipe + 1));
		
		if (!validDate(date) || date.empty() || value.empty())
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		double valueDouble;
		size_t idx;
		try
		{
			std::string cleanValue = trim(value);
			valueDouble = std::stod(cleanValue, &idx);
			if (idx != value.size())
        		throw std::invalid_argument("extra chars");
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: invalid value => " << value << std::endl;
			continue;
		}
		
		if (data.find(date) != data.end())
		{
    		std::cerr << "Error: duplicate date => " << date << std::endl;
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
			continue;
		}
		
		if (_database.empty())
		{
			std::cerr << "Error: empty database" << std::endl;
    		return;
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