#include	<iostream>
#include	<string>
#include	<fstream>
#include	"../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	// could call loadDatabase("data.csv") here, or leave it to be called explicitly
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	*this = src;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	if (this != &rhs)
		_data = rhs._data;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

void	BitcoinExchange::parseInputFile(const std::string& inputFilename)
{
	std::ifstream	file(inputFilename.c_str());	//	opens the file and ifstream doesnt read strings so c_str converts the string to const char*
	
	if(!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return ;
	}
	
	std::string	line;
	std::getline(file, line);	// skip headerline ("date" | "value")

	while (std::getline(file, line))
	{
		// TODO: parse `line` into date + value
		size_t	position = line.find('|');

		if(position == std::string::npos)
		{
			std::cerr << "Error: wrong text format." << std::endl;
			return ;
		}
		std::string	dateStr = line.substr(0, position);
		std::string	valueStr = line.substr(position + 1);
		// debug
		std::cout << "date: [" << dateStr << "] value: [" << valueStr << "]" << std::endl;
		// TODO: validate date and value

		// TODO: look up rate in _database
		// TODO: print result
	}
}
