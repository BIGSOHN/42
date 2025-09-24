#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() 
: AForm("PresidentialPardonForm", 25, 5), target("Default") {
	std::cout << "PresidentialPardonForm default constructor called" << std::endl;
}
PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
: AForm("PresidentialPardonForm", 25, 5), target(target) {
	std::cout << "PresidentialPardonForm constructor called" << std::endl;
}
PresidentialPardonForm::~PresidentialPardonForm() {
	std::cout << "PresidentialPardonForm destructor called" << std::endl;
}
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other) 
: AForm(other), target(other.target) {
	std::cout << "PresidentialPardonForm copy constructor called" << std::endl;
}
PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& other) {
	std::cout << "PresidentialPardonForm assignment operator called" << std::endl;
	if (this != &other) {
		AForm::operator=(other);
		// target은 const이므로 변경 불가
	}
	return *this;
}

std::string PresidentialPardonForm::getTarget() const {
	return target;
}
void PresidentialPardonForm::execute(Bureaucrat const &executor) const {
	this->checkExecuteRequirements(executor);

	std::cout << target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}