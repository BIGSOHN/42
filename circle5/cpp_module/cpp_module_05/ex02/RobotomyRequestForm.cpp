#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() 
: AForm("RobotomyRequestForm", 72, 45), target("Default") {
	std::cout << "RobotomyRequestForm default constructor called" << std::endl;
}
RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
: AForm("RobotomyRequestForm", 72, 45), target(target) {
	std::cout << "RobotomyRequestForm constructor called" << std::endl;
}
RobotomyRequestForm::~RobotomyRequestForm() {
	std::cout << "RobotomyRequestForm destructor called" << std::endl;
}
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other) 
: AForm(other), target(other.target) {
	std::cout << "RobotomyRequestForm copy constructor called" << std::endl;
}
RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other) {
	std::cout << "RobotomyRequestForm assignment operator called" << std::endl;
	if (this != &other) {
		AForm::operator=(other);
		// target은 const이므로 변경 불가
	}
	return *this;
}

std::string RobotomyRequestForm::getTarget() const {
	return target;
}
void RobotomyRequestForm::execute(Bureaucrat const &executor) const {
	this->checkExecuteRequirements(executor);

	std::cout << "DRILL DRILL DRILL" << std::endl;

	srand(time(NULL));
	if (rand() % 2 == 0) {
		std::cout << target << " robotomy success" << std::endl;
	} else {
		std::cout << target << " robotomy failed" << std::endl;
	}
}