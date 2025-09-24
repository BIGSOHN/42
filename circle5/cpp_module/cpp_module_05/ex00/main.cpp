#include "Bureaucrat.hpp"
#include "headers.hpp"

int main() {
	std::cout << "===== test 1 : nomal case =====" << std::endl;
	try {
		Bureaucrat nomalCase1;
		std::cout << "Print : " << nomalCase1 << std::endl;
		Bureaucrat nomalCase2("nomalCase2", 1);
		std::cout << "Print : " << nomalCase2 << std::endl;
		Bureaucrat nomalCase3("nomalCase3", 150);
		std::cout << "Print : " << nomalCase3 << std::endl;
		Bureaucrat nomalCase4("nomalCase4", 50);
		std::cout << "Print : " << nomalCase4 << std::endl;
	}
	catch(const std::exception& e) {
		std::cout << "Unexpected Error : " << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "===== test 2 : Out of range case =====" << std::endl;
	try {
		Bureaucrat outCase1("outCase1", 151);
		Bureaucrat outCase2("outCase2", 0);
	}
	catch(const std::exception& e) {
		std::cout << "Unexpected Error : " << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "===== test 3 : down case =====" << std::endl;
	try {
		Bureaucrat downCase1("downCase1", 145);
		for(int i = 0; i < 10; i++) {
			std::cout << "Print : " << downCase1 << std::endl;
			downCase1.decrementGrade();
		}
	}
	catch(const std::exception& e) {
		std::cout << "Unexpected Error : " << e.what() << std::endl;	
	}
	std::cout << std::endl;

	std::cout << "===== test 4 : up case =====" << std::endl;
	try {
		Bureaucrat upCase1("upCase1", 5);
		for (int i = 0; i < 10; i++) {
			std::cout << "Print : " << upCase1 << std::endl;
			upCase1.incrementGrade();
		}

	}
	catch(const std::exception& e) {
		std::cout << "Unexpected Error : " << e.what() << std::endl;
	}
}