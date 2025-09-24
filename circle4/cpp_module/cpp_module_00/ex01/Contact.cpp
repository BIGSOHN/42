#include "headers.hpp"
Contact::Contact() {
	idx = 0;
}

void	Contact::addContact() {
	setField(this->firstName, "First name :");
	setField(this->lastName, "Last name :");
	setField(this->nickName, "Nickname :");
	setField(this->phoneNumber, "Phone number :");
	setField(this->darkestSecret, "Darkest secret :");
	this->idx = 0;
}

void	Contact::setField(std::string &field, const char *comment) {
	field.clear();
	if (idx == 0 || idx == 1) {
		while (!correctNameField(field)) {
			std::cout << comment;
			if (!std::getline(std::cin, field))
				exit (1);
		}	
	}
	else if (idx == 2) {
		while (!correctAlnumField(field)) {
			std::cout << comment;
			if (!std::getline(std::cin, field))
				exit (1);
		}
	}
	else if (idx == 3) {
		while (!correctNumField(field)) {
			std::cout << comment;
			if (!std::getline(std::cin, field))
				exit (1);
		}
	}
	else {
		while (!correctSentenceField(field)) {
			std::cout << comment;
			if (!std::getline(std::cin, field))
				exit (1);
		}
	}
	idx++;
}

bool	Contact::correctNameField(std::string &field) {
	if (field.empty())
		return (false);
	for (int i = 0; i < field.length(); i++) {
		if (!isalpha(field[i])) {
			std::cout << "Please write only in English" << std::endl;
			return (false);
		}
	}
	return (true);
}

bool	Contact::correctNumField(std::string &field) {
	if (field.empty())
		return (false);
	for (int i = 0; i < field.length(); i++) {
		if (!isdigit(field[i])) {
			std::cout << "Please use only numbers." << std::endl;
			return (false);
		}
	}
	return (true);
}

bool	Contact::correctAlnumField(std::string &field) {
	if (field.empty())
		return (false);
	for (int i = 0; i < field.length(); i++) {
		if (!isalnum(field[i])) {
			std::cout << "Please use only English and numbers." << std::endl;
			return (false);
		}
	}
	return (true);
}

bool	Contact::correctSentenceField(std::string &field) {
	if (field.empty())
		return (false);
	for (int i = 0; i < field.length(); i++) {
		if (!isspace(field[i]))
			return (true);
		if (!isprint(field[i])) {
			std::cout << "The sentence can't print." << std::endl;
			return (false);
		}
	}
	std::cout << "It is a blank string. Please rewrite it." << std::endl;
	return (false);
}

void	Contact::showPreview() {
	truncateByLength(this->firstName);
	truncateByLength(this->lastName);
	truncateByLength(this->nickName);
}

void Contact::truncateByLength(std::string &field) {
	if (field.length() > 10)
		std::cout << field.substr(0, 9) << ".";
	else
		std::cout << std::setw(10) << field;
	std::cout << "|";
}

void	Contact::showContact() {
	std::cout << "First name : " << firstName << std::endl;
	std::cout << "Last name : " << lastName << std::endl;
	std::cout << "Nickname : " << nickName << std::endl;
	std::cout << "Phone number : " << phoneNumber << std::endl;
	std::cout << "Darkest secret : " << darkestSecret << std::endl;
}