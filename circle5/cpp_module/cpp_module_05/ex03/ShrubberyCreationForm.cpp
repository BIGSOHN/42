#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() 
: AForm("ShrubberyCreationForm", 145, 137), target("Default") {
	std::cout << "ShrubberyCreationForm default constructor called" << std::endl;
}
ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
: AForm("ShrubberyCreationForm", 145, 137), target(target) {
	std::cout << "ShrubberyCreationForm constructor called" << std::endl;
}
ShrubberyCreationForm::~ShrubberyCreationForm() {
	std::cout << "ShrubberyCreationForm destructor called" << std::endl;
}
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other) 
: AForm(other), target(other.target) {
	std::cout << "ShrubberyCreationForm copy constructor called" << std::endl;
}
ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
	std::cout << "ShrubberyCreationForm assignment operator called" << std::endl;
	if (this != &other) {
		AForm::operator=(other);
		// target은 const이므로 변경 불가
	}
	return *this;
}

std::string ShrubberyCreationForm::getTarget() const {
	return target;
}
void ShrubberyCreationForm::execute(Bureaucrat const &executor) const {
	this->checkExecuteRequirements(executor);

	std::string filename = target + "_shrubbery";
	std::ofstream file(filename.c_str());

	if (!file.is_open()) {
		std::cout << "Error: could not create file " << filename << std::endl;
		return ;
	}

	file << "       ###\n";
    file << "      #o###\n";
    file << "    #####o###\n";
    file << "   #o#\\#|#/###\n";
    file << "    ###\\|/#o#\n";
    file << "     # }|{  #\n";
    file << "       }|{\n";
    
    file.close();
    std::cout << "Shrubbery has been planted at " << target << std::endl;
}