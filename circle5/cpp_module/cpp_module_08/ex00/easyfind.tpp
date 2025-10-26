template <typename T>
typename T::iterator easyfind (T& container, int value) {
	typename T::iterator result = std::find(container.begin(), container.end(), value);
	if (result == container.end()) {
		throw std::exception();
	}
	return result;
}