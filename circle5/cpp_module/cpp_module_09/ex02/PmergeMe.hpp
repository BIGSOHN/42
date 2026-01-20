#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include "headers.hpp"

class PmergeMe
{
private:
	std::vector<int> _vec;
	std::deque<int> _deq;

	double _vecTime;
	double _deqTime;
	size_t _size;

	std::vector<int> generateInsertOrder(size_t pendingSize);

	void mergeInsertSortVec(std::vector<int>& vec);
	void mergesortVec(std::vector<std::pair<int, int> >& vec, int left, int right);
	void mergeVec(std::vector<std::pair<int, int> >& vec, int left, int mid, int right);
	int binarySearchVec(std::vector<int>& arr, int value);

	void mergeInsertSortDeq(std::deque<int>& deq);
	void mergesortDeq(std::deque<std::pair<int, int> >& deq, int left, int right);
	void mergeDeq(std::deque<std::pair<int, int> >& deq, int left, int mid, int right);
	int binarySearchDeq(std::deque<int>& arr, int value);

public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	bool parseInput(int argc, char** argv);
	void sort();
	void printBefore();
	void printAfter();
	void printTime();
};

#endif