#include	<iostream>
#include	"../inc/RPN.hpp"

int	main(int argc, char **argv)
{
	#ifdef DEBUG
	std::cout << "[MAIN]\t\tcalled." << std::endl;
	#endif

	if(argc != 2)
	{
		std::cerr << "Error: amount number of arguments." << std::endl;
		return (1);
	}

	RPN	rpn;

	if (rpn.parseInput(argv[1]))
		std::cout << rpn.getResult() << std::endl;

	return (0);
}