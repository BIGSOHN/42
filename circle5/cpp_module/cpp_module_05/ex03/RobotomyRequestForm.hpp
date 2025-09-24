#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include "headers.hpp"

class RobotomyRequestForm : public AForm
{
private:
	const std::string target;
public:
	RobotomyRequestForm();
	RobotomyRequestForm(const std::string &target);
	virtual ~RobotomyRequestForm();
	RobotomyRequestForm(const RobotomyRequestForm& other);
	RobotomyRequestForm& operator=(const RobotomyRequestForm& other);

	std::string getTarget() const;
	virtual void execute(Bureaucrat const &executor) const;
};

#endif