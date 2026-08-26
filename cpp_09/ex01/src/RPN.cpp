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
	return (_data.top());
}
bool	RPN::isOperator(std::string input, size_t currentPosition)
{

	if(!(input[currentPosition] == '+'
		|| input[currentPosition] == '-'
		|| input[currentPosition] == '*'
		|| input[currentPosition] == '/'))
			return (false);

	char c = input[currentPosition];

	return (c == '+' || c == '-' || c == '*' || c == '/');
}


// 		case 5:



bool	RPN::calculate(char op)
{

	int	valueA;
	int	valueB;
	int	result;
	
	std::cout << "[calculate] called with op = '" << op << "'" << std::endl;
	std::cout << "[calculate] stack size before pop = " << _data.size() << std::endl;
	if (_data.size() < 2)
	{
		std::cerr << "Error: malformed input." << std::endl;
		return (false);
	}

	valueB = _data.top();
	std::cout << "[calculate] popping valueB (top) = " << valueB << std::endl;
	_data.pop();

	valueA = _data.top();
	std::cout << "[calculate] popping valueA (new top) = " << valueA << std::endl;
	_data.pop();

	std::cout << "[calculate] remaining stack size = " << _data.size() << std::endl;




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
		return(false);
}

bool	RPN::parseInput(const std::string &inputLine)
{
	size_t	currentPosition;

	currentPosition = 0;

	while (currentPosition < inputLine.size())
	{
		if (std::isspace(inputLine[currentPosition]))
		{
			currentPosition++;
			continue ;
		}
		else if (std::isdigit(inputLine[currentPosition]))
		{
			_data.push(inputLine[currentPosition] - '0');
			currentPosition++;
			if(currentPosition < inputLine.size() && !std::isspace(inputLine[currentPosition]))
			{
				std::cerr << "Error: " << std::endl;
				return (false);
			}
			continue ;
		}
		else if(isOperator(inputLine, currentPosition))
		{
			if(!calculate(inputLine[currentPosition]))
				return (false);
			currentPosition++;
			continue ;
		}
		else
		{
			std::cerr << "Error: unsupported input." << std::endl;
			return (false);
		}
	}
	return (true);
}
