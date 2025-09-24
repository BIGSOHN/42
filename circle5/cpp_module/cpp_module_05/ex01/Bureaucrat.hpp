#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include "headers.hpp"

class Form;

class Bureaucrat
{
private:
	const std::string name;
	int grade;
public:
	Bureaucrat();
	Bureaucrat(const std::string &name, int grade);
	~Bureaucrat();
	Bureaucrat(const Bureaucrat& other);
	Bureaucrat& operator=(const Bureaucrat& other);

	//getter는 read-only 이므로 뒤에 const를 붙여줘야 함
	// 뒤 const: 이 함수는 객체의 상태를 변경하지 않음
	// 앞 const: 반환값이 상수
	std::string getName() const;
	int getGrade() const;
	void incrementGrade();
	void decrementGrade();
	void signForm(Form &form);

	class GradeTooHighException : public std::exception {
		public:
			virtual const char* what() const throw();
	};

	class GradeTooLowException : public std::exception {
		public:
			virtual const char* what() const throw();
	};
};

// 오퍼레이터 연산자는 외부에 선언해야 함
std::ostream& operator<<(std::ostream& out, const Bureaucrat& bureaucrat);

#endif