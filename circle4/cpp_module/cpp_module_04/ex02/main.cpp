#include "headers.hpp"
#include "classes.hpp"

int main()
{
	std::cout << "basic test" << std::endl;
	const AAnimal* j = new Dog();
	const AAnimal* i = new Cat();

	i->makeSound();
	j->makeSound();

	delete j;//should not create a leak
	delete i;
	std::cout << std::endl;
	
	std::cout << "array test" << std::endl;
	const int arraySize = 10;
	AAnimal *animals[arraySize];

	for (int i = 0; i < arraySize; i++) {
		if (i < arraySize / 2) {
			animals[i] = new Dog();
		}
		else {
			animals[i] = new Cat();
		}
	}
	for (int i = 0; i < arraySize; i++) {
		delete animals[i];
	}
	std::cout << std::endl;

	std::cout << "Copy dog test" << std::endl;
	Dog originalDog;
	originalDog.getBrain()->setIdea(0, "I love ball");

	Dog copyDog = originalDog;
	std::cout << "Original Dog idea : " << originalDog.getBrain()->getIdea(0) << std::endl;
	std::cout << "Copy Dog idea : " << copyDog.getBrain()->getIdea(0) << std::endl;
	std::cout << std::endl;

	std::cout << "Change copy dog's idea" << std::endl;
	copyDog.getBrain()->setIdea(0, "I love bones");
	std::cout << "Original Dog idea : " << originalDog.getBrain()->getIdea(0) << std::endl;
	std::cout << "Copy Dog idea : " << copyDog.getBrain()->getIdea(0) << std::endl;
	std::cout << std::endl;

	std::cout << "Copy cat test" << std::endl;
	Cat originalCat;
	Cat copyCat;

	originalCat.getBrain()->setIdea(0, "I hate water");
	copyCat = originalCat;
	std::cout << "Original Cat idea : " << originalCat.getBrain()->getIdea(0) << std::endl;
	std::cout << "Copy Cat idea : " << copyCat.getBrain()->getIdea(0) << std::endl;
	std::cout << std::endl;

	std::cout << "Change copy cat's idea" << std::endl;
	copyCat.getBrain()->setIdea(0, "Don't touch my tail");
	std::cout << "Original Cat idea : " << originalCat.getBrain()->getIdea(0) << std::endl;
	std::cout << "Copy Cat idea : " << copyCat.getBrain()->getIdea(0) << std::endl;
	std::cout << std::endl;
	return 0;
}
