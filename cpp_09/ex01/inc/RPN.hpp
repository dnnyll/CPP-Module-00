#ifndef		RPN_HPP
# define	RPN_HPP

#include	<stack>
#include	<string>

class	RPN
{

	// variables
	private:
		std::stack<int>	_data;

	// methods
	private:
	
	public:
		RPN();										// default constructor
		RPN(const RPN &src);						// copy constructor
		RPN &operator=(const RPN &rhs);				// assignment operator
		~RPN();										// destructor

		int		getResult() const;
		bool	parseInput(const std::string &inputLine);
		bool	isOperator(std::string input, size_t currentPosition);
		bool	calculate(char op);

};

#endif
