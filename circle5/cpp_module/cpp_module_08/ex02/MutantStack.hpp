#include "headers.hpp"

template <class T, class Container = std::deque<T> > // Container의 기본값이 deque로 설정.
class MutantStack : public std::stack<T, Container> {
	public:
		MutantStack();
		MutantStack(const MutantStack& other);
		MutantStack& operator=(const MutantStack& other);
		~MutantStack();

		typedef typename Container::iterator iterator; // Container의 iterator 타입을 우리 클래스의 iterator라는 이름으로 사용하겠다.

		iterator begin();
		iterator end();
};

#include "MutantStack.tpp"