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

// splits and stores key and value from the input string
bool	BitcoinExchange::splitLine(const std::string &line, std::string &dateStr, std::string &valueStr)
{
		size_t	position = line.find('|');

		if(position == std::string::npos)
		{
			std::cerr << "Error: bad input." << std::endl;
			return (false);
		}
		dateStr = line.substr(0, position);
		valueStr = line.substr(position + 1);

		// debug
		std::cout << "date: [" << dateStr << "] value: [" << valueStr << "]" << std::endl;
		return (true);
}

void	BitcoinExchange::parseInputFile(const std::string& inputFilename)
{
	//	opens the file and ifstream doesnt read strings so c_str converts the string to const char*
	std::ifstream	file(inputFilename.c_str());
	
	if(!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return ;
	}

	std::string	line;
	std::getline(file, line);	// skip headerline ("date" | "value")

	while (std::getline(file, line))
	{
		std::string	dateStr;
		std::string	valueStr;

		if(!splitLine(line, dateStr, valueStr))
			continue ;

		// TODO: validate date and value

		// TODO: look up rate in _database
		// TODO: print result
	}
}
