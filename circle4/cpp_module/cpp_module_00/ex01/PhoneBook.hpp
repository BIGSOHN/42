#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "headers.hpp"

class PhoneBook {
	private:
		int idx;
		int flag;
		std::string command;
		Contact contacts[8];
	public:
		PhoneBook();
		void add();
		void search();
		void printCommand();
		bool getCommand();
		bool checkIndex(std::string &index, int count);
};

#endif