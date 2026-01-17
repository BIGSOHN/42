#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {

}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _database(other._database) {

}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		_database = other._database;
	}
	return *this;
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
	if (date.length() != 10) {
		return false;
	}
	if (date[4] != '-' || date[7] != '-') {
		return false;
	}
	int year = atoi(date.substr(0, 4).c_str());
	int month = atoi(date.substr(5, 2).c_str());
	int day = atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12) {
		return false;
	}
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		daysInMonth[1] = 29;

	if (day < 1 || day > daysInMonth[month - 1]) {
		return false;
	}

	return true;
}

bool BitcoinExchange::parseValue(const std::string& str, double& value) {
	std::stringstream ss(str);
	ss >> value;
	if (ss.fail()) {
		std::cerr << "Error: bad input => " << str << std::endl;
		return false;
	}
	std::string leftover;
	ss >> leftover;
	if (!leftover.empty()) {
		std::cerr << "Error: bad input => " << str << std::endl;
		return false;
	}
	if (value < 0) {
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	if (value > 1000) {
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	return true;
}

double BitcoinExchange::getExchangeRate(const std::string& date) const {
	// lower_bound(date)는 date 이상인 첫 번째 요소 반환
	std::map<std::string, double>::const_iterator it = _database.lower_bound(date);
	if (it != _database.end() && it->first == date) {
		return it->second;
	}
	if (it == _database.begin()) {
		return (-1);
	}
	--it;
	return it->second;
}

void BitcoinExchange::processLine(const std::string& line) {
	size_t bar = line.find('|');
	if (bar == std::string::npos) {
		std::cerr << "Error: bad input => " << line << std::endl;
		return;
	}
	std::string date = trim(line.substr(0, bar));
	std::string strValue = trim(line.substr(bar + 1));
	double value;

	if (!isValidDate(date)) {
		std::cerr << "Error: wrong date" << std::endl;
		return;
	}
	if (!parseValue(strValue, value)) {
		return;
	}

	double rate = getExchangeRate(date);
	if (rate == -1) {
		std::cerr << "Error: date too early." << std::endl;
		return;
	}
	double result = value * rate;

	std::cout << date << " => " << value << " = " << result << std::endl;
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
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
	std::string line;
	std::getline(file, line);
	if (line.find("date") == std::string::npos) {
		processLine(line);
	}
	while (std::getline(file, line)) {
		if (line.empty())
			continue;
		processLine(line);
	}
	file.close();
}
