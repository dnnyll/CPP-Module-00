#ifndef		BITCOINEXCHANGE_HPP
# define	BITCOINEXCHANGE_HPP

#include	<map>

class	BitcoinExchange
{

	private:
		std::map<std::string, float>	_data;
		//this will contain the date and the exchange rate value of that day
		//key = date string ("2011-01-03")
		//value = exchange rate (3.29 or whatever it is that day)

	void	loadDatabase(const std::string &filename);

	public:
		BitcoinExchange();										// default constructor
		BitcoinExchange(const BitcoinExchange &src);			// copy constructor
		BitcoinExchange &operator=(const BitcoinExchange &rhs);	// assignment operator
		~BitcoinExchange();										// destructor

		void	parseInputFile(const std::string& inputFilename);
		bool	splitLine(const std::string &line, std::string &dateStr, std::string &valueStr);
		bool	validateDate(const std::string &dateStr);
		bool	validateValue(std::string &valueStr);
		double	getRate(const std::string &dateStr);



};

// static bool	convertYear(std::string &dateStr);


#endif