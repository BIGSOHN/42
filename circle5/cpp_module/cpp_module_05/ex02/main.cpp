#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "headers.hpp"

int main() {
	std::cout << "===== test 1 : ShrubberyCreationForm =====" << std::endl;
	try {
		Bureaucrat alpha("Alpha", 100);
		ShrubberyCreationForm shrubForm("shrubForm");

		std::cout << alpha << std::endl;
		std::cout << shrubForm << std::endl;

		alpha.signForm(shrubForm);
		alpha.executeForm(shrubForm);

		Bureaucrat bravo("Bravo", 140);
		ShrubberyCreationForm cratForm("cratForm");
		bravo.signForm(cratForm);
		bravo.executeForm(cratForm);
	}
	catch(const std::exception& e) {
		std::cout << "Unexpected Error : " << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "===== test 2 : RobotomyRequestForm =====" << std::endl;
	try {
		Bureaucrat charlie("Charlie", 40);
		RobotomyRequestForm robotForm("robot");

		std::cout << charlie << std::endl;
		std::cout << robotForm << std::endl;

		charlie.signForm(robotForm);
	
		charlie.executeForm(robotForm);
		charlie.executeForm(robotForm);
		charlie.executeForm(robotForm);

		Bureaucrat delta("Delta", 80);
		RobotomyRequestForm robotForm2("tomy");
		delta.signForm(robotForm2);
	}
	catch(const std::exception& e) {
		std::cout << "Unexpected Error : " << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "===== test 3 : PresidentialPardonForm =====" << std::endl;
	try {
		Bureaucrat echo("Echo", 1);
		PresidentialPardonForm presidentForm("presidentForm");

		std::cout << echo << std::endl;
		std::cout << presidentForm << std::endl;

		echo.signForm(presidentForm);
		echo.executeForm(presidentForm);

		Bureaucrat foxtrot("foxtrot", 30);
		PresidentialPardonForm pardonForm("pardonForm");
		foxtrot.signForm(pardonForm);

		Bureaucrat golf("golf", 10);
		PresidentialPardonForm form("form");
		golf.signForm(form);
		golf.executeForm(form);
	}
	catch(const std::exception& e) {
		std::cout << "Unexpected Error : " << e.what() << std::endl;
	}
	return (0);
}