#include "headers.hpp"
#include "Span.hpp"

int main() {
	std::cout << "=== Nomal Test Case ===" << std::endl;
	Span nums(5);
	for (int i = 0; i < 5; i++) {
		nums.addNumber(i);
	}
	std::cout << "nums class longest span : " << nums.longestSpan() << std::endl;
	std::cout << "nums class shortest span : " << nums.shortestSpan() << std::endl;
	std::cout << std::endl;

	std::cout << "=== Out of bounds Test Case ===" << std::endl;
	Span outOfNums(5);
	try {
		for (int i = 0; i < 6; i++) {
			outOfNums.addNumber(i);
		}
	}
	catch(const std::exception& e) {
		std::cerr << "Error : " << e.what() << " - Span is full" << std::endl;
	}
	std::cout << std::endl;

	std::cout << "=== Not Enough Elements Test Case ===" << std::endl;
	try {
		Span notEnough(1);
		notEnough.addNumber(1);
		std::cout << "notEnough class longest span : " << notEnough.longestSpan() << std::endl;
		std::cout << "notEnough class shortest span : " << notEnough.shortestSpan() << std::endl;		
	}
	catch(const std::exception& e) {
		std::cerr << "Error : " << e.what() << " - Not enough span class size." << std::endl;
	}
	
	return (0);
}