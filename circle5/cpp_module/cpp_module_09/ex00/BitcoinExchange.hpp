#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include "headers.hpp"

class BitcoinExchange
{
private:
	std::map<std::string, double> _database;

	std::string trim(const std::string& str);
	bool isValidDate(const std::string& date);
	bool parseValue(const std::string& str, double& value);
	double getExchangeRate(const std::string& date) const;
	void processLine(const std::string& line);
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	bool loadDatabase(const std::string& filename);
	void processInputFile(const std::string& filename);
};

#endif