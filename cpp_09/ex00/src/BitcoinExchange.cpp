#include	<iostream>
#include	<string>
#include	<fstream>
#include	<cstdlib>
#include	<map>
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

// trims content removing shitespaces or tabs
std::string trim(const std::string &str)
{
	size_t	start = str.find_first_not_of(" \t");
	size_t	end = str.find_last_not_of(" \t");

	if (start == std::string::npos)
		return ("");

	std::string	trimedStr = str.substr(start, end - start + 1);

	return (trimedStr);
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
		std::cout << "splitLine" << std::endl;
		std::cout << "date: [" << dateStr << "] value: [" << valueStr << "]" << std::endl;
		return (true);
}

// converts date str into int and verifies if the date is in the calendar
static bool	convertYear(const std::string &dateStr)
{
	int	year = std::atoi(dateStr.substr(0, 4).c_str());
	int	month = std::atoi(dateStr.substr(5, 2).c_str());
	int	day = std::atoi(dateStr.substr(8, 2).c_str());
	
	if (month < 1 || month > 12)
		return (false);

	int	monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	int	maxDays = monthDays[month - 1];

	if (month == 2 && ((year % 4 == 0 && year %100 != 0) || year %400 == 0))
		maxDays = 29;

	if (day < 1 || day > maxDays)
		return (false);

	return (true);
}

bool	BitcoinExchange::validateDate(const std::string &dateStr)
{
	if(dateStr.size() != 10)
		return (false);

	if(dateStr[4] != '-' || dateStr[7] != '-')
		return (false);
	
	int	i = 0;
	
	while (i < 10)
	{
		if (i == 4 || i == 7)
		{
			i++;
			continue ;
		}
		if (!isdigit(dateStr[i]))
			return (false);
		i++;
	}
	if(!convertYear(dateStr))
		return (false);

	return (true);
}

bool	BitcoinExchange::validateValue(std::string &valueStr)
{
	char	*lastChar;
	double	value = std::strtod(valueStr.c_str(), &lastChar);

	if (*lastChar != '\0')
	{
		std::cerr << "Error: not a valid number." << std::endl;
		return (false);
	}
	if (value < 1)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}
	if (value > 1000)
	{
		std::cerr << "Error: number is too large." << std::endl;
		return (false);
	}
	return (true);
}


double	BitcoinExchange::getRate(const std::string &dateStr)
{
	std::map<std::string, float>::iterator it = _data.lower_bound(dateStr);

	if (it == _data.end() || it ->first != dateStr)
	{
		if (it == _data.begin())
		{
			throw std::exception();
		}
		--it;
	}
	return (it->second);
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
		
		dateStr = trim(dateStr);
		valueStr = trim(valueStr);

		// debug
		std::cout << "trimed" << std::endl;
		std::cout << "date: [" << dateStr << "] value: [" << valueStr << "]" << std::endl;


		if (!validateDate(dateStr))
			continue ;

		if (!validateValue(valueStr))
			continue ;

		if (!getRate(dateStr))
			continue ;

		// TODO: print result
	}
}
