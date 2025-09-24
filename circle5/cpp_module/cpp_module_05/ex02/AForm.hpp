#ifndef AForm_HPP
# define AForm_HPP

#include "headers.hpp"

class Bureaucrat;

class AForm
{
private:
	const std::string name;
	bool isSigned;
	const int gradeToSign;
	const int gradeToExecute;
public:
	AForm();
	AForm(const std::string &name, int gradeToSign, int gradeToExecute);
	virtual ~AForm();
	AForm(const AForm& other);
	AForm& operator=(const AForm& other);

	std::string getName() const;
	int getGradeToSign() const;
	int getGradeToExecute() const;
	bool getIsSigned() const;
	void	beSigned(Bureaucrat &bureaucrat);

	virtual void execute(Bureaucrat const &executor) const = 0;
	void checkExecuteRequirements(Bureaucrat const &executor) const;

	class GradeTooHighException : public std::exception {
		public:
			virtual const char* what() const throw();
	};

	class GradeTooLowException : public std::exception {
		public:
			virtual const char* what() const throw();
	};

	class FormNotSignedException : public std::exception {
		public:
			virtual const char* what() const throw();
	};
};

std::ostream& operator<<(std::ostream& out, const AForm& AForm);


#endif