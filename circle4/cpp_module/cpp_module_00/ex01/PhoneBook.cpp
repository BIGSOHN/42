#include "headers.hpp"

PhoneBook::PhoneBook() {
	this->idx = 0;
	this->flag = 0;
}

void	PhoneBook::add() {
	this->contacts[idx].addContact();
	if (idx >= 7) {
		idx = 0;
		flag = 1;
	}
	else
		idx++;
}

void	PhoneBook::search() {
	int	count;
	std::string index;

	index.clear();
	if (this->idx == 0 && flag == 0) {
		std::cout << "The phonebook is empty" << std::endl;
		return ;
	}
	std::cout << std::setw(10) << "Index" << "|";
	std::cout << std::setw(10) << "FirstName" << "|";
	std::cout << std::setw(10) << "LastName" << "|";
	std::cout << std::setw(10) << "Nickname" << "|" << std::endl;
	if (flag == 0)
		count = idx;
	else
		count = 8;
	for (int i = 0; i < count; i++) {
		std::cout << std::setw(10) << i + 1 << "|";
		this->contacts[i].showPreview();
		std::cout << std::endl;
	}
	while (!checkIndex(index, count)) {
		std::cout << "Index : ";
		if (!std::getline(std::cin, index))
			exit (1);
	}
	this->contacts[atoi(index.c_str()) - 1].showContact();
}

void	PhoneBook::printCommand() {
	std::cout << "===== COMMAND =====" << std::endl;
	std::cout << "ADD" << std::endl;
	std::cout << "SEARCH" << std::endl;
	std::cout << "EXIT" << std::endl;
	std::cout << "===================" << std::endl;
}

bool	PhoneBook::getCommand() {
	std::string command;

	std::cout << "COMMAND : ";
	if (!std::getline(std::cin, command))
		exit (1);
	if (command.compare("ADD") == 0 || command.compare("add") == 0)
		add();
	else if (command.compare("SEARCH") == 0 || command.compare("search") == 0)
		search();
	else if (command.compare("EXIT") == 0 || command.compare("exit") == 0)
		return false;
	else
		std::cout << "The command does not exist." << std::endl;
	return true;
}

bool	PhoneBook::checkIndex(std::string &index, int count) {
	if (index.empty())
		return (false);
	if (std::atoi(index.c_str()) < 1 || std::atoi(index.c_str()) > count) {
		std::cout << "The number is out of range." << std::endl;
		return (false);
	}
	for (int i = 0; i < index.length(); i++) {
		if (!isdigit(index[i])) {
			std::cout << "Please use only numbers." << std::endl;
			return (false);
		}
	}
	return (true);
}