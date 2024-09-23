#include <iostream>
#include <sstream>
/*https://www.geeksforgeeks.org/convert-string-to-int-in-cpp/*/
std::string sum_str(const std::string &a, const std::string &b) {
    try {
        std::string result;
        std::stringstream num_1(a), num_2(b);
        int int_num_1 = 0, int_num_2 = 0;
        num_1 >> int_num_1;
        num_2 >> int_num_2;
        int sum = int_num_1 + int_num_2;
        return std::to_string(sum);
    } catch (std::invalid_argument &e) {
        return e.what();
    }
}

/*return std::to_string(std::stoi(a == "" ? "0" : a) + std::stoi(b == "" ? "0" : b));*/

int main() { std::cout << sum_str("-5", "3") << std::endl; }
