#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"
#include "headers.hpp"

class PresidentialPardonForm : public AForm
{
private:
	const std::string target;
public:
	PresidentialPardonForm();
	PresidentialPardonForm(const std::string &target);
	virtual ~PresidentialPardonForm();
	PresidentialPardonForm(const PresidentialPardonForm& other);
	PresidentialPardonForm& operator=(const PresidentialPardonForm& other);

	std::string getTarget() const;
	virtual void execute(Bureaucrat const &executor) const;
};

#endif