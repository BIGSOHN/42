#include "MutantStack.hpp"

int main() {
	std::cout << "=== Testing with Mutant Stack ===" << std::endl;
	MutantStack<int>    mstack;

	mstack.push(5);
	mstack.push(17);
	
	std::cout << mstack.top() << std::endl;
	
	mstack.pop();
	
	std::cout << mstack.size() << std::endl;
	
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	
	++it;
	--it;
	while (it != ite) {
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);
	std::cout << std::endl;

	std::cout << "=== Testing with std::list ===" << std::endl;
	std::list<int> mlist;

	mlist.push_back(5);    // list는 push_back 사용
	mlist.push_back(17);

	std::cout << mlist.back() << std::endl;  // list는 back() 사용

	mlist.pop_back();

	std::cout << mlist.size() << std::endl;

	mlist.push_back(3);
	mlist.push_back(5);
	mlist.push_back(737);
	mlist.push_back(0);

	std::list<int>::iterator lit = mlist.begin();
	std::list<int>::iterator lite = mlist.end();

	++lit;
	--lit;
	while (lit != lite) {
		std::cout << *lit << std::endl;
		++lit;
	}

	return 0;
}