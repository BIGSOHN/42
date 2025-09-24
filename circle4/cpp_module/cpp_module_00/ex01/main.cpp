#include "headers.hpp"

int main() {
	PhoneBook phoneBook;

	while (true) {
		phoneBook.printCommand();
		if (phoneBook.getCommand() == false) {
			break;
		}
	}
}
