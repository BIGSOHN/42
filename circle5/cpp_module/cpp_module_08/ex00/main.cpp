#include "easyfind.hpp"
#include "headers.hpp"

int main() {
	std::cout << "===Test Normal Case===" << std::endl;
	std::vector<int> v(5);
	for (int i = 0; i < 5; i++) {
		v[i] = i;
	}
	std::vector<int>::iterator result = easyfind(v, 3);
	std::cout << "찾은 값은? : " << *result << std::endl;
	std::cout << "다음 인덱스의 값은? : " << *(result + 1) << std::endl;
	std::cout << std::endl;

	std::cout << "===Test Abnormal Case===" << std::endl;
	try {
		result = easyfind(v, 100);
		std::cout << "찾음 : " << *result << std::endl;
	} catch(const std::exception& e) {
		std::cerr << "에러 : " << e.what() << '\n';
	}
	
	return (0);
}