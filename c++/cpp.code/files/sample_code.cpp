#include <fstream>
#include <iostream>

//
// Created by vremyavnikuda on 9/26/24.
//
int main() {
    std::ofstream ifs("/home/vremyavnikuda/repository/codewars/c++/cpp.code/files/sample_code.txt",std::ios::app);

    if (ifs.is_open()) {
        ifs << "Это первая записать "<< std::endl;
        ifs << "Это первая записать "<< std::endl;
        ifs.close();
    }else {
        std::cerr<<"Fatal Error"<<std::endl;
        return 1;
    }

    std::ifstream in_files("/home/vremyavnikuda/repository/codewars/c++/cpp.code/files/sample_code.txt");
    if (in_files.is_open()) {
        std::string line;
        while (std::getline(in_files, line)) {
            std::cout << line << std::endl;
        }
        in_files.close();
    }else {
        std::cerr<<"Fatal Error"<<std::endl;
        return 1;
    }
    return 1;
}