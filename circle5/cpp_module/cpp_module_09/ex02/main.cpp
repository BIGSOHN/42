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

    pmerge.printBefore();
    pmerge.sort();
    pmerge.printAfter();
   
    return 0;
}