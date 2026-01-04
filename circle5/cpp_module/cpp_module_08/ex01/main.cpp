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
		std::cout << "Not Enough class longest span : " << notEnough.longestSpan() << std::endl;
		std::cout << "Not Enough class shortest span : " << notEnough.shortestSpan() << std::endl;		
	}
	catch(const std::exception& e) {
		std::cerr << "Error : " << e.what() << " - Not enough span class size." << std::endl;
	}
	std::cout << std::endl;

	std::cout << "=== 10,000+ Numbers Test Case ===" << std::endl;
	std::vector<int> largeVec;
	Span largeSpan(10000);
	try {
		for (int i = 0; i < 10000; i++) {
			largeVec.push_back(i);
		}
		largeSpan.addNumbers(largeVec.begin(), largeVec.end());
		std::cout << "Shortest span: " << largeSpan.shortestSpan() << std::endl;
		std::cout << "Longest span: " << largeSpan.longestSpan() << std::endl;
	}
	catch(const std::exception& e) {
		std::cerr << "Error : " << e.what() << " - Not enough span class size." << std::endl;
	}
	std::cout << std::endl;

	std::cout << "=== PDF Test Case ===" << std::endl;
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
	return (0);
}