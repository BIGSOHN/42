#ifndef INTERN_HPP
# define INTERN_HPP

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
private:
	typedef AForm* (*FormCreator)(const std::string& target);

	struct FormMapping {
		std::string name;
		FormCreator creator;
	};

	static FormMapping formMappings[3];

	static AForm* createShrubbery(const std::string& target);
	static AForm* createRobotomy(const std::string& target);
	static AForm* createPardon(const std::string& target);
	
public:
	Intern();
	~Intern();
	Intern(const Intern& other);
	Intern& operator=(const Intern& other);

	AForm* makeForm(const std::string& formName, const std::string& target);
};


#endif