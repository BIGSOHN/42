#ifndef CONTACT_HPP
# define CONTACT_HPP

#include "headers.hpp"

class Contact {
	private:
		int idx;
		std::string firstName;
		std::string lastName;
		std::string nickName;
		std::string phoneNumber;
		std::string darkestSecret;
	public:
		Contact();
		void addContact();
		void setField(std::string &field, const char *comment);
		bool correctNameField(std::string &field);
		bool correctNumField(std::string &field);
		bool correctAlnumField(std::string &field);
		bool correctSentenceField(std::string &field);
		void showPreview();
		void truncateByLength(std::string &field);
		void showContact();
};

#endif