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

int	RPN::getResult() const
{
	#ifdef DEBUG
	std::cout << "[GETRESULT]\tcalled." << std::endl;
	#endif

	return (_data.top());
}

static bool	isOperator(std::string input, size_t currentPosition)
{
	#ifdef DEBUG
	std::cout << "[ISOPERATOR]\tcalled." << std::endl;
	#endif

	if(!(input[currentPosition] == '+'
		|| input[currentPosition] == '-'
		|| input[currentPosition] == '*'
		|| input[currentPosition] == '/'))
			return (false);

	return (true);
}

bool	RPN::calculate(char op)
{
	#ifdef DEBUG
	std::cout << "[CALCULATE]\tcalled." << std::endl;
	#endif

	int	valueA;
	int	valueB;
	int	result;

	if (_data.size() < 2)
	{
		std::cerr << "Error: malformed input." << std::endl;
		return (false);
	}

	valueB = _data.top();
	_data.pop();
	valueA = _data.top();
	_data.pop();

	switch(op)
	{
		case '+':
			result = valueA + valueB;
			break ;

		case '-':
			result = valueA - valueB;
			break ;

		case '*':
			result = valueA * valueB;
			break ;

		case '/':
			result = valueA / valueB;
			break ;
		}
		_data.push(result);
		return(true);
}

bool	RPN::parseInput(const std::string &inputLine)
{
	#ifdef DEBUG
	std::cout << "[PARSEINPUT]\tcalled." << std::endl;
	#endif

	size_t	currentPosition;

	currentPosition = 0;

	while (currentPosition < inputLine.size())
	{
		//	skip spaces
		if (std::isspace(inputLine[currentPosition]))
		{
			currentPosition++;
			continue ;
		}
		//	check if isdigit, yes = push value, check if next character is digit = wrong
		else if (std::isdigit(inputLine[currentPosition]))
		{
			_data.push(inputLine[currentPosition] - '0');
			currentPosition++;
			if(currentPosition < inputLine.size() && !std::isspace(inputLine[currentPosition]))
			{
				std::cerr << "Error: malformed input." << std::endl;
				return (false);
			}
			continue ;
		}
		//	check if char is valid operator, if yes calculate
		else if(isOperator(inputLine, currentPosition))
		{
			if(!calculate(inputLine[currentPosition]))
				return (false);
			currentPosition++;
			continue ;
		}
		else
		{
			std::cerr << "Error: malformed input." << std::endl;
			return (false);
		}
	}
	//	final check if we have more than 1 value at the end of operations
	if (_data.size() != 1)
	{
		std::cerr << "Error: malformed inputasdasd." << std::endl;
		return (false);
	}
	return (true);
}
