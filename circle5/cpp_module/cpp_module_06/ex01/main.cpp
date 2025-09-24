#include "Serializer.hpp"

int main() {
	Data* data = new Data(42);

	std::cout << "=====Test=====" << std::endl;
	std::cout << "Original Data" << std::endl;
	std::cout << "Address : " << data << std::endl;
	std::cout << "Value : " << data->value << std::endl;

	std::cout << "Serialized Data" << std::endl;
	uintptr_t serialized = Serializer::serialize(data);
	std::cout << "Address : " << data << std::endl;

	std::cout << "Deserialized Data" << std::endl;
	Data* deserialized = Serializer::deserialize(serialized);
	std::cout << "Address : " << deserialized << std::endl;
	std::cout << "Value : " << deserialized->value << std::endl;

	delete (data);
}