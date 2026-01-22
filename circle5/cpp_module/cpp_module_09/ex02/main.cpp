#include "PmergeMe.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    
    PmergeMe pmerge;
    
    if (!pmerge.parseInput(argc, argv)) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    std::cout << "Before : ";
    pmerge.printSTL();
    std::cout << std::endl;

    pmerge.sort();
    
    std::cout << "After : ";
    pmerge.printSTL();
    std::cout << std::endl;
    pmerge.printTime();

    return 0;
}