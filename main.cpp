#include <iostream>
#include "implementation/interface.h"

int main(int argc, char* argv[]) {
    std::string file1, file2;
    Comparator compare;
    if(argc == 1) {
        std::cout << "Enter file path for file 1: ";
        std::cin >> file1;
        std::cout << "Enter file path for file 2: ";
        std::cin >> file2;
    }
    else if(argc == 2) {
        file1 = argv[1];
        std::cout << "You have entered only the path of one file\nPlease enter the path for file2: ";
        std::cin >> file2;
    }
    else{
        file1 = argv[1];
        file2 = argv[2];
    }

    std::ifstream fileA(file1, std::ifstream::in);
    std::ifstream fileB(file2, std::ifstream::in);

    ComparisonReport result = compare.compare(fileA, fileB);

    std::cout << "Common words: " << result.commonWords.getSize() << " From them " << result.commonWords.countOfUniqueWords() << " are unique.\n";
    std::cout << "Words left from file 1: " << result.uniqueWords[0].getSize() << " From them " << result.uniqueWords[0].countOfUniqueWords() << " are unique.\n";
    std::cout << "Words left from file 2: " << result.uniqueWords[1].getSize() << " From them " << result.uniqueWords[1].countOfUniqueWords() << " are unique.\n";

    return 0;
}
