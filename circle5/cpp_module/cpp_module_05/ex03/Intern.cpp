#include "Intern.hpp"

Intern::FormMapping Intern::formMappings[3] = {
	{"shrubbery creation", &Intern::createShrubbery},
	{"robotomy request", &Intern::createRobotomy},
	{"presidential pardon", &Intern::createPardon}
};

Intern::Intern() {
	std::cout << "Intern constructor called" << std::endl;
}

Intern::~Intern() {
	std::cout << "Intern destructor called" << std::endl;
}

Intern::Intern(const Intern& other) {
	(void)other; // 아무것도 없으니까 안쓴다는 명시적 표기
	std::cout << "Intern copy constructor called" << std::endl;
}

Intern& Intern::operator=(const Intern &other) {
	(void)other;
	std::cout << "Intern assignment operator called" << std::endl;
	return *this;
}

AForm* Intern::createShrubbery(const std::string& target) {
	return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomy(const std::string& target) {
	return new RobotomyRequestForm(target);
}

AForm* Intern::createPardon(const std::string& target) {
	return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) {
	for (int i = 0; i < 3; i++) {
		if (formName == formMappings[i].name) {
			std::cout << "Intern creates " << formName << std::endl;
			return formMappings[i].creator(target);
		}
	}
	std::cout << "Error: Unknown form name " << formName << std::endl;
	return NULL;
}