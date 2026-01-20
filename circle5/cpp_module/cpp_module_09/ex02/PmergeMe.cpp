#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {

}

PmergeMe::PmergeMe(const PmergeMe& other) : _vec(other._vec), _deq(other._deq) {

}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}

PmergeMe::~PmergeMe() {

}

void PmergeMe::mergeInsertSortVec(std::vector<int>& vec) {
	std::vector<std::pair<int, int>> pairs;
	int lastOdd = -1;
	bool hasLastOdd = (vec.size() % 2 == 1);

	for (size_t i = 0; i + 1 < vec.size(); i += 2) {
		if (vec[i] < vec[i + 1])
			pairs.push_back(std::make_pair(vec[i + 1], vec[i]));
		else
			pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
	}
	if (hasLastOdd) {
		lastOdd = vec.back();
	}
	// merge sort를 이용해서 mainChain을 정렬
	if (!pairs.empty()) {
		mergesortVec(pairs, 0, pairs.size() - 1);
	}
	
	std::vector<int> mainChain;
	std::vector<int> pendingElements;

	if (!pairs.empty()) {
		mainChain.push_back(pairs[0].second); // 첫 번째 숫자 중 제일 작은 변수를 먼저 넣음
		for (size_t i = 0; i < pairs.size(); i++) {
			mainChain.push_back(pairs[i].first);
		}
		for (size_t i = 1; i < pairs.size(); i++) {
			pendingElements.push_back(pairs[i].second);
		}
		if (hasLastOdd) {
			pendingElements.push_back(lastOdd);
		}
	}
}

void PmergeMe::mergesortVec(std::vector<std::pair<int, int>>& vec, int left, int right) {
	int mid;

	if (left < right) {
		mid = left + ((right - left) / 2);
		mergesortVec(vec, left, mid);
		mergesortVec(vec, mid + 1, right);
		mergeVec(vec, left, mid, right);
	}
}

void PmergeMe::mergeVec(std::vector<std::pair<int, int>>& vec, int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	int k = 0;
	std::vector<std::pair<int, int>> temp(right - left + 1);

	while (i <= mid && j <= right) {
		if (vec[i].first <= vec[j].first) {
			temp[k++] = vec[i++];
		} else {
			temp[k++] = vec[j++];
		}
	}
	while (i <= mid) {
		temp[k++] = vec[i++];
	}
	while (j <= right) {
		temp[k++] = vec[j++];
	}
	for (int i = left; i <= right; i++) {
		vec[i] = temp[i - left];
	}
}

void PmergeMe::mergeInsertSortDeq(std::deque<int>& deq) {

}

void PmergeMe::mergesortDeq(std::deque<int>& deq, int left, int right) {
	
}

void PmergeMe::mergeDeq(std::deque<int>& deq, int left, int mid, int right) {
	
}

bool PmergeMe::parseInput(int argc, char** argv) {
	for (int i = 1; i < argc; i++) {
		std::string str = argv[i];

		if (str.empty()) {
			return false;
		}

		for (size_t j = 0; j < str.length(); j++) {
			if (!isdigit(str[j])) {
				return false;
			}
		}

		int num = atoi(str.c_str());

		if (num < 0) {
			return false;
		}

		_vec.push_back(num);
		_deq.push_back(num);
	}
	_size = _vec.size();
	return true;
}
void PmergeMe::sort() {
	clock_t start, end;

	// vector 정렬
	start = clock();
	mergeInsertSortVec(_vec);
	end = clock();
	_vecTime = static_cast<double>(end - start);

	// deque 정렬
	start = clock();
	mergeInsertSortDeq(_deq);
	end = clock();
	_deqTime = static_cast<double>(end - start);
}
void PmergeMe::printBefore() {
	std::cout << "Before: ";
	for (size_t i = 0; i < _vec.size(); i++) {
		std::cout << _vec[i];
		if (i < _vec.size() - 1) {
			std::cout << " ";
		}
	}
	std::cout << std::endl;
}
void PmergeMe::printAfter() {
	std::cout << "After: ";
	for (size_t i = 0; i < _vec.size(); i++) {
		std::cout << _vec[i];
		if (i < _vec.size() - 1) {
			std::cout << " ";
		}
	}
	std::cout << std::endl;
}
void PmergeMe::printTime() {
	std::cout << "Time to process a range of " << _size
				<< " elements with std::vector : "
				<< _vecTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _size
				<< " elements with std::deque : "
				<< _deqTime << " us" << std::endl;
}