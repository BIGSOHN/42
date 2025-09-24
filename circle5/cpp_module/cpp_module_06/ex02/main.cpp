#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "functions.hpp"

int main() {
	std::srand(std::time(NULL));

	for (int i = 0; i < 5; i++) {
		Base *ptr = generate();
		std::cout << "Point Test :";
		identify(ptr);
		std::cout << "Reference Test :";
		identify(*ptr);

		delete(ptr);
	}
	return (0);
}