#include "iter.hpp"

void print(int& num);
void increment(int& num);
void printConst(const int& num);

int main() {
	std::cout << "non const type" << std::endl;
	int arr[] = {1, 2, 3, 4, 5};
	iter(arr, 5, print);
	iter(arr, 5, increment);
	iter(arr, 5, print);

	std::cout << "const type" << std::endl;
	const int carr[] = {1, 2, 3, 4, 5};
	iter(carr, 5, printConst);

	return (0);
}

void print(int& num) {
	std::cout << num << std::endl;
}

void printConst(const int& num) {
	std::cout << num << std::endl;
}

void increment(int& num) {
	num++;
}