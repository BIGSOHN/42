#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include "headers.hpp"

class ScalarConverter
{
private:
	ScalarConverter();

	static bool isChar(const std::string& str);
	static bool isInt(const std::string& str);
	static bool isFloat(const std::string& str);
	static bool isDouble(const std::string& str);
	static bool hasValidFloatForm(const std::string &str);

	static bool isNaN(double num);
	static bool isInF(double num);

	static void convertFromWhat(const std::string& literal);

	static void printChar(const std::string& literal);
	static void printInt(const std::string& literal);
	static void printFloat(const std::string& literal);
	static void printDouble(const std::string& literal);

public:
	static void convert(const std::string& literal);
};

#endif