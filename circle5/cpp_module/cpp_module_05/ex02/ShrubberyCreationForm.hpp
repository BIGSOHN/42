#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include "headers.hpp"

class ShrubberyCreationForm : public AForm
{
private:
	const std::string target;
public:
	ShrubberyCreationForm();
	ShrubberyCreationForm(const std::string &target);
	virtual ~ShrubberyCreationForm();
	ShrubberyCreationForm(const ShrubberyCreationForm& other);
	ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);

	std::string getTarget() const;
	virtual void execute(Bureaucrat const &executor) const;
};


#endif