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

std::vector<int> PmergeMe::generateInsertOrder(size_t pendingSize) {
	std::vector<int> jacobsthal;
	jacobsthal.push_back(0); // J(0) = 0;
	jacobsthal.push_back(1); // J(1) = 1;
	// pendingSize를 초과할 때까지 계산
	while ((size_t)jacobsthal.back() < pendingSize)	{
		size_t size = jacobsthal.size();
		int next = jacobsthal[size - 1] + (2 * jacobsthal[size - 2]);
		jacobsthal.push_back(next);
	}
	std::vector<int> insertOrder;
	int lastInserted = 0; // 마지막으로 삽입된 인덱스 추적
	for (size_t i = 1; i < jacobsthal.size(); i++) {
		int start = std::min(jacobsthal[i], (int)pendingSize) - 1;
		int end = lastInserted;
		for (int j = start; j >= end; j--) {
			insertOrder.push_back(j);
		}
		lastInserted = std::min(jacobsthal[i], (int)pendingSize);
	}
	return insertOrder;
}

void PmergeMe::mergeInsertSortVec(std::vector<int>& vec) {
	if (vec.size() <= 1) {
		return ;
	}
	std::vector<std::pair<int, int> > pairs;
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
	mergesortVec(pairs, 0, pairs.size() - 1);
	
	std::vector<int> mainChain;
	std::vector<int> pendingElements;

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

	// 야콥스탈 수열을 이용해서 정렬
	std::vector<int> insertOrder = generateInsertOrder(pendingElements.size());
	for (size_t i = 0; i < insertOrder.size(); i++) {
		int idx = insertOrder[i];
		int value = pendingElements[idx];

		// 이진탐색 수행
		int pos = binarySearchVec(mainChain, value);
		mainChain.insert(mainChain.begin() + pos, value);
	}

	vec = mainChain;
}

int PmergeMe::binarySearchVec(std::vector<int>& arr, int value) {
	int left = 0;
	int right = arr.size() - 1;

	while (left <= right) {
		int mid = left + ((right - left) / 2);

		if (arr[mid] < value) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return left;
}

void PmergeMe::mergesortVec(std::vector<std::pair<int, int> >& vec, int left, int right) {
	int mid;

	if (left < right) {
		mid = left + ((right - left) / 2);
		mergesortVec(vec, left, mid);
		mergesortVec(vec, mid + 1, right);
		mergeVec(vec, left, mid, right);
	}
}

void PmergeMe::mergeVec(std::vector<std::pair<int, int> >& vec, int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	int k = 0;
	std::vector<std::pair<int, int> > temp(right - left + 1);

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
	if (deq.size() <= 1) {
		return ;
	}
	std::deque<std::pair<int, int> > pairs;
	int lastOdd = -1;
	bool hasLastOdd = (deq.size() % 2 == 1);

	for (size_t i = 0; i + 1 < deq.size(); i += 2) {
		if (deq[i] < deq[i + 1])
			pairs.push_back(std::make_pair(deq[i + 1], deq[i]));
		else
			pairs.push_back(std::make_pair(deq[i], deq[i + 1]));
	}
	if (hasLastOdd) {
		lastOdd = deq.back();
	}
	mergesortDeq(pairs, 0, pairs.size() - 1);

	std::deque<int> mainChain;
	std::deque<int> pendingElements;

	mainChain.push_back(pairs[0].second);
	for (size_t i = 0; i < pairs.size(); i++) {
		mainChain.push_back(pairs[i].first);
	}
	for (size_t i = 1; i < pairs.size(); i++) {
		pendingElements.push_back(pairs[i].second);
	}
	if (hasLastOdd) {
		pendingElements.push_back(lastOdd);
	}

	std::vector<int> insertOrder = generateInsertOrder(pendingElements.size());
	for (size_t i = 0; i < insertOrder.size(); i++) {
		int idx = insertOrder[i];
		int value = pendingElements[idx];

		int pos = binarySearchDeq(mainChain, value);
		mainChain.insert(mainChain.begin() + pos, value);
	}

	deq = mainChain;
}

int PmergeMe::binarySearchDeq(std::deque<int>& arr, int value) {
	int left = 0;
	int right = arr.size() - 1;

	while (left <= right) {
		int mid = left + ((right - left) / 2);

		if (arr[mid] < value) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return left;
}

void PmergeMe::mergesortDeq(std::deque<std::pair<int, int> >& deq, int left, int right) {
	int mid;

	if (left < right) {
		mid = left + ((right - left) / 2);
		mergesortDeq(deq, left, mid);
		mergesortDeq(deq, mid + 1, right);
		mergeDeq(deq, left, mid, right);
	}
}

void PmergeMe::mergeDeq(std::deque<std::pair<int, int> >& deq, int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	int k = 0;
	std::deque<std::pair<int, int> > temp(right - left + 1);

	while (i <= mid && j <= right) {
		if (deq[i].first <= deq[j].first) {
			temp[k++] = deq[i++];
		} else {
			temp[k++] = deq[j++];
		}
	}
	while (i <= mid) {
		temp[k++] = deq[i++];
	}
	while (j <= right) {
		temp[k++] = deq[j++];
	}
	for (int i = left; i <= right; i++) {
		deq[i] = temp[i - left];
	}
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