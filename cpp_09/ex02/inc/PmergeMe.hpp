#ifndef		PMERGEME_HPP
# define	PMERGEME_HPP

#include	<stack>
#include	<string>

class	PmergeMe
{

	// variables
	private:
		std::stack<int>	_data;

	// methods
	private:
	
	public:
		PmergeMe();											// default constructor
		PmergeMe(const PmergeMe &src);						// copy constructor
		PmergeMe &operator=(const PmergeMe &rhs);			// assignment operator
		~PmergeMe();										// destructor

		int		getResult() const;
		bool	parseInput(const std::string &inputLine);
		bool	calculate(char op);

};

#endif
