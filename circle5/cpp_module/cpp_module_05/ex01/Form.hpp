#ifndef FORM_HPP
# define FORM_HPP

#include "headers.hpp"

class Bureaucrat;

class Form
{
private:
	const std::string name;
	bool isSigned;
	const int gradeToSign;
	const int gradeToExecute;
public:
	Form();
	Form(const std::string &name, int gradeToSign, int gradeToExecute);
	~Form();
	Form(const Form& other);
	Form& operator=(const Form& other);

	std::string getName() const;
	int getGradeToSign() const;
	int getGradeToExecute() const;
	bool getIsSigned() const;
	void	beSigned(Bureaucrat &bureaucrat);

	class GradeTooHighException : public std::exception {
		public:
			virtual const char* what() const throw();
	};

	class GradeTooLowException : public std::exception {
		public:
			virtual const char* what() const throw();
	};
};

std::ostream& operator<<(std::ostream& out, const Form& form);


#endif