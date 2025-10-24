#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base* generate(void) {
	int random = std::rand() % 3;
	switch (random) {
		case 0: return new A();
		case 1: return new B();
		case 2: return new C();
		default: return new A();
	}
}

void identify(Base* p) {
	if (dynamic_cast<A*>(p) != NULL) {
		std::cout << "A" << std::endl;
	} else if (dynamic_cast<B*>(p) != NULL) {
		std::cout << "B" << std::endl;
	} else if (dynamic_cast<C*>(p) != NULL) {
		std::cout << "C" << std::endl;
	} else {
		std::cout << "Unknown" << std::endl;
	}
}
void identify(Base& p) {
	try {
		A& aRef = dynamic_cast<A&>(p);
		(void) aRef;
		std::cout << "A" << std::endl;
		return;
	} catch(const std::exception& e) {
		
	}
	try {
		B& bRef = dynamic_cast<B&>(p);
		(void) bRef;
		std::cout << "B" << std::endl;
		return;
	} catch(const std::exception& e) {
		
	}
	try {
		C& cRef = dynamic_cast<C&>(p);
		(void) cRef;
		std::cout << "C" << std::endl;
		return;
	} catch(const std::exception& e) {
		// 모든 try 실패 후 마지막에 한 번만 출력
		std::cout << "Unknown" << std::endl;
	}
}