template <typename T>
Array<T>::Array() : _elements(NULL), _size(0){
}

template <typename T>
Array<T>::Array(unsigned int n) : _size(n) {
	if (n == 0) {
		_elements = NULL;
	} else {
		// 괄호가 있음으로서 값이 초기화 됨
		_elements = new T[n]();
	}
}

template <typename T>
Array<T>::~Array() {
	delete[] _elements;
}

template <typename T>
Array<T>::Array(const Array& other) : _size(other._size) {
	if (other._size == 0) {
		_elements = NULL;
	} else {
		_elements = new T[_size]();
		for (unsigned int i = 0; i < _size; i++) {
			_elements[i] = other._elements[i];
		}
	}
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
	if (this != &other) {
		delete[] _elements;

		_size = other._size;
		if (_size == 0) {
			_elements = NULL;
		} else {
			_elements = new T[_size]();
			for (unsigned int i = 0; i < _size; i++) {
				_elements[i] = other._elements[i];
			}
		}
	}
	return *this;
}

template <typename T>
T& Array<T>::operator[](unsigned int index) {
	if (index >= _size) {
		throw std::out_of_range("Index out of Bounds.");
	}
	return _elements[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const {
	if (index >= _size) {
		throw std::out_of_range("Index out of Bounds.");
	}
	return _elements[index];
}

template <typename T>
unsigned int Array<T>::size() const {
	return _size;
}