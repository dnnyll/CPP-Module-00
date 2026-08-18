#include	<iostream>
#include	"../inc/BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: wrong number of arguments." << std::endl;
		return (1);
	}
	BitcoinExchange	btc;
	btc.parseInputFile(argv[1]);

	return (0);
}