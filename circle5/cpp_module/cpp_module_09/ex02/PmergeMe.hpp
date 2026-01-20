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

	void mergeInsertSortVec(std::vector<int>& vec);
	void mergesortVec(std::vector<std::pair<int, int>>& vec, int left, int right);
	void mergeVec(std::vector<std::pair<int, int>>& vec, int left, int mid, int right);
	void mergeInsertSortDeq(std::deque<int>& deq);
	void mergesortDeq(std::deque<int>& deq, int left, int right);
	void mergeDeq(std::deque<int>& deq, int left, int mid, int right);

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