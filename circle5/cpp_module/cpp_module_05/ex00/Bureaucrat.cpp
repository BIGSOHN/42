#include "headers.hpp"
#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("Default"), grade(150) {
    std::cout << "Default constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(const std::string &name, int grade) : name(name) {
    if (grade < 1) {
        throw GradeTooHighException();
    }
    if (grade > 150) {
        throw GradeTooLowException();
    }
    std::cout << this->name << " constructor called" << std::endl;
    this->grade = grade;
}

Bureaucrat::~Bureaucrat() {
    std::cout << "Destructor called" << std::endl;
}


Bureaucrat::Bureaucrat(const Bureaucrat& other) : name(other.name), grade(other.grade) {
    std::cout << "Copy constructor called" << std::endl;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
    std::cout << "Copy assignment operator called " << std::endl;
    if (this != &other) {
        // const이므로 이름은 변경 불가!
        // this->name = other.getName();
        this->grade = other.grade;
    }
    return *this;
}

std::string Bureaucrat::getName() const {
    return (name);
}

int Bureaucrat::getGrade() const {
    return (grade);
}

void Bureaucrat::incrementGrade() {
    // 1이 제일 높은 등급이라고 했으므로 실질적인 수를 감소해야함
    if (grade <= 1) {
        throw GradeTooHighException();
    }
    this->grade--;
}

void Bureaucrat::decrementGrade() {
    // 150이 제일 낮은 등급이라고 했으므로 실질적인 수를 증가해야함
    if (grade >= 150) {
        throw GradeTooLowException();
    }
    this->grade++;
}

const char *Bureaucrat::GradeTooHighException::what() const throw() {
    return ("Bureaucrat grade is too high (minimum grade is 1)");
}

const char *Bureaucrat::GradeTooLowException::what() const throw() {
    return ("Bureaucrat grade is too low (maximum grade is 150)");
}

std::ostream& operator<<(std::ostream& out, const Bureaucrat& bureaucrat) {
    out << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
    return out;
}