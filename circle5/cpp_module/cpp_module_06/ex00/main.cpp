#include "headers.hpp"
#include "ScalarConverter.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		return (0);
	}
	std::string str = argv[1];
	ScalarConverter::convert(str);

	return(0);
}