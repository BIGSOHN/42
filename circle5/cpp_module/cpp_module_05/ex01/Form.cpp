#include "headers.hpp"
#include "Form.hpp"
#include "Bureaucrat.hpp"


Form::Form() : name("Default"), isSigned(false), gradeToSign(150), gradeToExecute(150) {
	std::cout << "Default constructor called" << std::endl;
}

Form::Form(const std::string &name, int gradeToSign, int gradeToExecute) : name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute) {
	if (gradeToExecute < 1 || gradeToSign < 1) {
		throw GradeTooHighException();
	}
	if (gradeToExecute > 150 || gradeToSign > 150) {
		throw GradeTooLowException();
	}
	std::cout << this->name << " constructor called" << std::endl;
}

Form::~Form() {
	std::cout << "Destructor called" << std::endl;
}

Form::Form(const Form& other) : name(other.name), isSigned(other.isSigned), gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute) {
	std::cout << "Copy constructor called" << std::endl;
}

Form& Form::operator=(const Form& other) {
	std::cout << "Copy assignment operator called " << std::endl;
	if (this != &other) {
		this->isSigned = other.isSigned;
	}
	return *this;
}

std::string Form::getName() const {
	return (name);
}

int Form::getGradeToSign() const {
	return(gradeToSign);
}

int Form::getGradeToExecute() const {
	return (gradeToExecute);
}

bool Form::getIsSigned() const {
	return (isSigned);
}

void	Form::beSigned(Bureaucrat &bureaucrat) {
	if (this->isSigned == true) {
		return ;
	}
	if (bureaucrat.getGrade() <= this->getGradeToSign()) {
		this->isSigned = true;
	} else {
		throw GradeTooLowException();
	}
}

const char* Form::GradeTooHighException::what() const throw() {
	return ("Form grade is too high (minimum grade is 1)");
}

const char* Form::GradeTooLowException::what() const throw() {
	return ("Form grade is too low (maximum grade is 150)");
}

std::ostream& operator<<(std::ostream& out, const Form& form) {
    out << form.getName() << ", grade to sign " << form.getGradeToSign()  <<  \
	", grade to execute " << form.getGradeToExecute() \
	<< ", signed " << form.getIsSigned() << ".";
    return out;
}
