#include	<string>
#include	<iostream>
#include	<cstdlib>
#include	"../inc/RPN.hpp"

RPN::RPN()
{
	#ifdef DEBUG
	std::cout << "[CONSTRUCTOR]\tcalled." << std::endl;
	#endif
}

RPN::RPN(const RPN &src)
{
	#ifdef DEBUG
	std::cout << "[COPY CONSTRUCTOR]\tcalled." << std::endl;
	#endif

	*this = src;
}

RPN &RPN::operator=(const RPN &input)
{
	#ifdef DEBUG
	std::cout << "[COPY A.OPER.]\tcalled." << std::endl;
	#endif

	if (this != &input)
		_data = input._data;
	return (*this);
}

RPN::~RPN()
{
	#ifdef DEBUG
	std::cout << "[DESTRUCTOR]\tcalled." << std::endl;
	#endif
}

static bool	isOperator(std::string input, size_t	currentPosition)
{
	if(!(input[currentPosition] == '+'
		|| input[currentPosition] == '-'
		|| input[currentPosition] == '*'
		|| input[currentPosition] == '/'))
			return (false);
	return (true);
}

bool	RPN::splitLine(const std::string &inputLine)
{
	size_t	startPosition;
	// size_t   endPosition;
	size_t	currentPosition;

	currentPosition = 0;
	startPosition = 0;
	while (currentPosition < inputLine.size())
	{
		std::cout << "----" << std::endl;
		std::cout << "startPosition = " << startPosition
				<< " | currentPosition = " << currentPosition
				<< " | char at currentPosition = '"
				<< inputLine[currentPosition] << "'" << std::endl;

		//  is a valid number store as token?
		if (inputLine[currentPosition] == ' ')
		{
			std::cout << "mark isSpace -> '" << inputLine[currentPosition]
					<< "' at position " << currentPosition << std::endl;
			currentPosition++;
			continue ;
		}
		// is a valid digit?
		else if (std::isdigit(inputLine[currentPosition]))
		{
			std::cout << "mark isDigit -> '" << inputLine[currentPosition]
					<< "' at position " << currentPosition << std::endl;
			_data.push(inputLine[currentPosition] - '0');
			currentPosition++;
			continue ;
		}

		// is a valid operator?
		else if(isOperator(inputLine, currentPosition))
		{
			std::cout << "mark isOperator -> '" << inputLine[currentPosition]
					<< "' at position " << currentPosition << std::endl;
			calculate()
			currentPosition++;
			continue ;
		}
		// trigger calculation of previous elements?

		else
		{
			std::cerr << "ERROR at position " << currentPosition
					<< " char '" << inputLine[currentPosition] << "'" << std::endl;
			return (false);
		}
	}
	return (true);
}

void	RPN::parseInput(std::string inputLine)
{
	splitLine(inputLine);
}