#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {

}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {

}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {

}

BitcoinExchange::~BitcoinExchange() {

}

std::string BitcoinExchange::trim(const std::string& str) {
	size_t start = str.find_first_not_of(" \t\r\n");
	if (start == std::string::npos)
		return "";
	
	size_t end = str.find_last_not_of(" \t\r\n");
	return str.substr(start, end - start + 1);
}

bool BitcoinExchange::isValidDate(const std::string& date) {

}

bool BitcoinExchange::parseValue(const std::string& str, double& value) {

}

double BitcoinExchange::getExchangeRate(const std::string& date) const {

}

void BitcoinExchange::processLine(const std::string& line) {

}


bool BitcoinExchange::loadDatabase(const std::string& filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		std::cerr << "Error: could not open file." << std::endl;
		return false;
	}
	// 맨 위에 한 줄 패스
	std::string line;
	std::getline(file, line);

	while (std::getline(file, line)) {
		// 파싱 로직
		if (line.empty())
			continue;
		size_t comma = line.find(',');
		if (comma == std::string::npos)
			continue;
		std::string date = trim(line.substr(0, comma));
		std::string priceStr = trim(line.substr(comma + 1));

		std::stringstream ss(priceStr);
		double price;
		ss >> price;

		if (ss.fail())
			continue;

		_database[date] = price;
	}
	file.close();
	return true;
}

void BitcoinExchange::processInputFile(const std::string& filename) {

}
