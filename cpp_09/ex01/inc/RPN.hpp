#ifndef		RPN_HPP
# define	RPN_HPP

#include	<stack>
#include	<string>
#include	"../inc/RPN.hpp"

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
		void	parseInput(std::string inputLine);
		bool	splitLine(const std::string &inputLine);


};

#endif
