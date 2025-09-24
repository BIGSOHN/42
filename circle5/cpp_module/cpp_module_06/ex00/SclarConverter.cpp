#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {};

bool ScalarConverter::isChar(const std::string& str) {
	if (str.empty()) {
		return (false);
	}
	if (str.length() == 1) {
		return true;
	}
	return (false);
}
bool ScalarConverter:: isInt(const std::string& str) {
	size_t i = 0;
	
	if (str.empty()) {
		return (false);
	}
	if (str[i] == '+' || str[i] == '-') {
		i++;
	}
	while (i < str.length()) {
		if (!isdigit(str[i])) {
			return (false);
		}
		i++;
	}
	return (true);
}
bool ScalarConverter:: isFloat(const std::string& str) {
	if (str.empty()) {
		return false;
	}
	if (str == "inff" || str == "nanf" || str == "+inff" || str == "-inff") {
		return true;
	}
	if (hasValidFloatForm(str)) {
		return (true);
	}
	return (false);
}
bool ScalarConverter:: isDouble(const std::string& str) {
	if (str.empty()) {
		return false;
	}
	if (str == "inf" || str == "nan" || str == "+inf" || str == "-inf") {
		return true;
	}
	if (hasValidFloatForm(str) && str[str.length() - 1] != 'f') {
		return (true);
	}
	return (false);
}

bool ScalarConverter::hasValidFloatForm(const std::string &str) {
	if (str.empty()) {
		return (false);
	}
	
	bool hasDot = false;
	bool hasDigit = false;
	size_t i = 0;
	size_t len = str.length();

	if (str[i] == '+' || str[i] == '-') {
		i++;
	}
	if (str[len - 1] == 'f') {
		len--;
	}
	for (; i < len; i++) {
		if (isdigit(str[i])) {
			hasDigit = true;
		} else if (str[i] == '.') { // 점 처리 로직 점 앞에 숫자가 있어야 함.
			if (hasDot == true || hasDigit == false) {
				return (false);
			}
			hasDot = true;
		} else {
			return (false);
		}
	}
	return (hasDigit && hasDot);
}

bool ScalarConverter::isNaN(double num) {
	return (num != num);
}

bool ScalarConverter::isInF(double num) {
	return (num == std::numeric_limits<double>::infinity() || 
			num == -std::numeric_limits<double>::infinity());
}

void ScalarConverter::convertFromChar(const std::string& literal) {
	printChar(literal);
	printInt(literal);
	printFloat(literal);
	printDouble(literal);
}
void ScalarConverter::convertFromInt(const std::string& literal) {
	printChar(literal);
	printInt(literal);
	printFloat(literal);
	printDouble(literal);
}
void ScalarConverter::convertFromFloat(const std::string& literal) {
	printChar(literal);
	printInt(literal);
	printFloat(literal);
	printDouble(literal);
}
void ScalarConverter::convertFromDouble(const std::string& literal) {
	printChar(literal);
	printInt(literal);
	printFloat(literal);
	printDouble(literal);
}

void ScalarConverter::printChar(const std::string& literal) {
	long long num = strtoll(literal.c_str(), NULL, 10);

	if (num > 127 || num < 0 || literal == "inff" || literal == "nanf" || literal == "+inff" || literal == "-inff"
	|| literal == "inf" || literal == "nan" || literal == "+inf" || literal == "-inf") {
		std::cout << "char: impossible" << std::endl;
	} else if (literal.length() == 1 && !isdigit(literal[0])) {
		char c = literal[0];
		if (isprint(c)) {
			std::cout << "char: " << "\'" << c << "\'" << std::endl; 
		} else {
			std::cout << "char: non displayable" << std::endl; 
		}
	} else {
		if (isprint(num)) {
			std::cout << "char: " << "\'" << static_cast<char>(num) << "\'" << std::endl; 
		} else {
			std::cout << "char: non displayable" << std::endl; 
		}
	}
}

void ScalarConverter::printInt(const std::string& literal) {
	if (isChar(literal) && !isdigit(literal[0])) {
		std::cout << "int: " << static_cast<int>(literal[0]) << std::endl;
		return ;
	}
	long long num = strtoll(literal.c_str(), NULL, 10);
	if (literal.length() > 11 || num > INT_MAX || num < INT_MIN 
	|| literal == "inff" || literal == "nanf" || literal == "+inff" || literal == "-inff"
	|| literal == "inf" || literal == "nan" || literal == "+inf" || literal == "-inf") {
		std::cout << "int: impossible" << std::endl;
	} else {
		std::cout << "int: " << static_cast<int>(num) << std::endl;
	}
}

void ScalarConverter::printFloat(const std::string& literal) {
	if (isChar(literal) && !isdigit(literal[0])) {
		std::cout << "float: " << static_cast<int>(literal[0]) << ".0f" << std::endl;
		return ;
	}
	errno = 0;
	if (literal == "inff" || literal == "nanf" || literal == "+inff" || literal == "-inff") {
		std::cout << "float: " << literal << std::endl;
		return;
	}
	if (literal == "inf" || literal == "nan" || literal == "+inf" || literal == "-inf") {
		std::cout << "float: " << literal << "f" << std::endl;
		return;
	}
	double num = strtod(literal.c_str(), NULL);
	if(isInF(num) || (num > std::numeric_limits<float>::max()) || (num < -std::numeric_limits<float>::max())) {
		if (num < 0) {
			std::cout << "float: -inff" << std::endl;
		} else {
			std::cout << "float: inff" << std::endl;
		}
	} else if (isNaN(num)) {
		std::cout << "float: nanf" << std::endl;
	} else {
		if (isInt(literal)) {
			std::cout << "float: " << static_cast<float>(num) << ".0f" << std::endl;
		} else {
			std::cout << "float: " << static_cast<float>(num) << ".f" << std::endl;
		}
	}
}

void ScalarConverter::printDouble(const std::string& literal) {
	if (isChar(literal) && !isdigit(literal[0])) {
		std::cout << "double: " << static_cast<double>(literal[0]) << ".0" << std::endl;
		return ;
	}
	errno = 0;
	if (literal == "inff" || literal == "nanf" || literal == "+inff" || literal == "-inff") {
		std::cout << "double: " << literal.substr(0, literal.length() - 1) << std::endl;
		return;
	}
	if (literal == "inf" || literal == "nan" || literal == "+inf" || literal == "-inf") {
		std::cout << "double: " << literal << std::endl;
		return;
	}
	double num = strtod(literal.c_str(), NULL);
	if(isInF(num)) {
		if (num < 0) {
			std::cout << "double: -inf" << std::endl;
		} else {
			std::cout << "double: inf" << std::endl;
		}
	} else if (isNaN(num)) {
		std::cout << "double: nan" << std::endl;
	} else {
		if (isInt(literal)) {
			std::cout << "double: " << static_cast<double>(num) << ".0" << std::endl;
		} else {
			std::cout << "double: " << static_cast<double>(num) << std::endl;
		}
	}
}

void ScalarConverter::convert(const std::string& literal) {
	if (isChar(literal)) {
		convertFromChar(literal);
	} else if (isInt(literal)) {
		convertFromInt(literal);
	} else if (isFloat(literal)) {
		convertFromFloat(literal);
	} else if (isDouble(literal)) {
		convertFromDouble(literal);
	} else {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	}
}