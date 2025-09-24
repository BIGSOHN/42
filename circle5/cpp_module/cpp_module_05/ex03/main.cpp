#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Intern.hpp"
#include "headers.hpp"

int main() {
	std::cout << "===== test : Intern =====" << std::endl;
	try {
		Intern intern;
		AForm* forms[4];

		forms[0] = intern.makeForm("shrubbery creation", "alpha");
		std::cout << std::endl;
		forms[1] = intern.makeForm("robotomy request", "bravo");
		std::cout << std::endl;
		forms[2] = intern.makeForm("presidential pardon", "charlie");
		std::cout << std::endl;
		forms[3] = intern.makeForm("unknown form", "delta");
		std::cout << std::endl;

		for(int i = 0; i < 3; i++) {
			if (forms[i] != NULL) {
				delete forms[i];
			}
		}
	}
	catch(const std::exception& e) {
		std::cout << "Unexpected Error : " << e.what() << std::endl;
	}
	return (0);
}