#include <iostream>
#include <fstream>
#include <string>

int main() {

    std::ifstream inputFile("test2.txt");
    std::ofstream fileF2("f2.txt");
    std::ofstream fileF3("f3.txt");
    
    int lengthThreshold;

    if (!inputFile.is_open() || !fileF2.is_open() || !fileF3.is_open()) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    std::cout << "Enter len of stf to separate: ";
    std::cin >> lengthThreshold;

    std::string line;
    while (std::getline(inputFile, line))
    {
        if (line.length() < lengthThreshold)
        {
            fileF2 << line << std::endl;
        }
        else
        {
            fileF3 << line << std::endl;
        }
    }

    inputFile.close();
    fileF2.close();
    fileF3.close();

    std::cout << "Done." << std::endl;

    return 0;
}

