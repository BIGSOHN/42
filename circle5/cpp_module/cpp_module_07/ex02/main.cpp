#include "headers.hpp"
#include "Array.hpp"

int main() {
	int *a = new int();
	std::cout << *a << std::endl; // 0으로 나옴
	delete a;

	std::cout << "=== TEST1 : Nomal Case ===" << std::endl;
	Array<int> emptyCase;
	std::cout << "emptyCase size : "<< emptyCase.size() << std::endl;
	std::cout << std::endl;

	Array<int> case1(5);
	std::cout << "case1 size : "<< case1.size() << std::endl;
	for (unsigned int i = 0; i < case1.size(); i++) {
		case1[i] = i;
		std::cout << "case1[" << i << "] : " << case1[i] << std::endl;
	}
	std::cout << std::endl;

	std::cout << "=== TEST2 : Deep Copy Test ===" << std::endl;
	Array<int> copyCase1(case1);
	for (unsigned int i = 0; i < copyCase1.size(); i++) {
		copyCase1[i]++;
		std::cout << "case1[" << i << "] : " << case1[i] << std::endl;
		std::cout << "copyCase1[" << i << "] : " << copyCase1[i] << std::endl;
		std::cout << std::endl;
	}

	std::cout << "=== TEST3 : Copy Constructor Test ===" << std::endl;
	Array<int> copyCase2(copyCase1);
	for (unsigned int i = 0; i < copyCase2.size(); i++) {
		copyCase2[i]++;
		std::cout << "copyCase1[" << i << "] : " << copyCase1[i] << std::endl;
		std::cout << "copyCase2[" << i << "] : " << copyCase2[i] << std::endl;
		std::cout << std::endl;
	}

	std::cout << "=== TEST4 : Assignment Operator Test ===" << std::endl;
	copyCase2 = case1;
	for (unsigned int i = 0; i < copyCase2.size(); i++) {
		std::cout << "case1[" << i << "] : " << case1[i] << std::endl;
		std::cout << "copyCase2[" << i << "] : " << copyCase2[i] << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (unsigned int i = 0; i < copyCase2.size(); i++) {
		copyCase2[i]++;
		std::cout << "case1[" << i << "] : " << case1[i] << std::endl;
		std::cout << "copyCase2[" << i << "] : " << copyCase2[i] << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "TEST5 : Out of Bounds" << std::endl;
	try
	{
		Array<int> outCase1(5);
		std::cout << "outCase1 size : " << outCase1.size() << std::endl;
		std::cout << "outCase1[5] : " << outCase1[5] << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}