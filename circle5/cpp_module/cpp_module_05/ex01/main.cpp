#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "headers.hpp"

int main() {
	std::cout << "===== test 1 : nomal case =====" << std::endl;
	try {
		Bureaucrat nomalCase1("nomalCase1", 50);
		std::cout << "Print : " << nomalCase1 << std::endl;
		Form formCase1("formCase1", 100, 100);
		std::cout << "Print : " << formCase1 << std::endl;
		nomalCase1.signForm(formCase1);
		std::cout << "Print : " << nomalCase1 << std::endl;
		std::cout << "Print : " << formCase1 << std::endl;
	}
	catch(const std::exception& e) {
		std::cout << "Unexpected Error : " << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "===== test 2 : Out of range case =====" << std::endl;
	try {
		Bureaucrat outCase1("outCase1", 50);
		std::cout << "Print : " << outCase1 << std::endl;
		Form formCase1("formCase1", 151, 151);
		outCase1.signForm(formCase1);
		std::cout << "Print : " << outCase1 << std::endl;
		Form formCase2("formCase2", 0, 0);
		outCase1.signForm(formCase2);
		std::cout << "Print : " << outCase1 << std::endl;
		std::cout << "Print : " << formCase1 << std::endl;
	}
	catch(const std::exception& e) {
		std::cout << "Unexpected Error : " << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "===== test 3 : over case =====" << std::endl;
	try {
		Bureaucrat upCase1("upCase1", 5);
		Form formCase1("formCase1", 1, 1);
		upCase1.signForm(formCase1);
		std::cout << "Print : " << upCase1 << std::endl;
		std::cout << "Print : " << formCase1 << std::endl;
	}
	catch(const std::exception& e) {
		std::cout << "Unexpected Error : " << e.what() << std::endl;
	}
}