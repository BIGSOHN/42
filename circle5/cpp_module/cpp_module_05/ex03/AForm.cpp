#include "headers.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"


AForm::AForm() : name("Default"), isSigned(false), gradeToSign(150), gradeToExecute(150) {
	std::cout << "Default constructor called" << std::endl;
}

AForm::AForm(const std::string &name, int gradeToSign, int gradeToExecute) : name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute) {
	if (gradeToExecute < 1 || gradeToSign < 1) {
		throw GradeTooHighException();
	}
	if (gradeToExecute > 150 || gradeToSign > 150) {
		throw GradeTooLowException();
	}
	std::cout << this->name << " constructor called" << std::endl;
}

AForm::~AForm() {
	std::cout << "Destructor called" << std::endl;
}

AForm::AForm(const AForm& other) : name(other.name), isSigned(other.isSigned), gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute) {
	std::cout << "Copy constructor called" << std::endl;
}

AForm& AForm::operator=(const AForm& other) {
	std::cout << "Copy assignment operator called " << std::endl;
	if (this != &other) {
		this->isSigned = other.isSigned;
	}
	return *this;
}

std::string AForm::getName() const {
	return (name);
}

int AForm::getGradeToSign() const {
	return(gradeToSign);
}

int AForm::getGradeToExecute() const {
	return (gradeToExecute);
}

bool AForm::getIsSigned() const {
	return (isSigned);
}

void	AForm::beSigned(Bureaucrat &bureaucrat) {
	if (this->isSigned == true) {
		return ;
	}
	if (bureaucrat.getGrade() <= this->getGradeToSign()) {
		this->isSigned = true;
	} else {
		throw GradeTooLowException();
	}
}

void	AForm::checkExecuteRequirements(Bureaucrat const &executor) const {
	if (!this->isSigned) {
		throw FormNotSignedException();
	}
	if (executor.getGrade() > this->gradeToExecute) {
		throw GradeTooLowException();
	}
}

const char* AForm::GradeTooHighException::what() const throw() {
	return ("AForm grade is too high (minimum grade is 1)");
}

const char* AForm::GradeTooLowException::what() const throw() {
	return ("AForm grade is too low (maximum grade is 150)");
}

const char* AForm::FormNotSignedException::what() const throw() {
	return ("Form is not signed");
}

std::ostream& operator<<(std::ostream& out, const AForm& AForm) {
    out << AForm.getName() << ", grade to sign " << AForm.getGradeToSign()  <<  \
	", grade to execute " << AForm.getGradeToExecute() \
	<< ", signed " << AForm.getIsSigned() << ".";
    return out;
}
