#include <iostream>
#include <string>
//
// Created by vremyavnikuda on 9/23/24.
//2. Слова наоборот
int main() {
    std::string word;
    getline(std::cin, word);
    char temp[word.length()];

    for (int i = 0; i < word.length(); i++) {
        temp[i]=word[word.length()-i-1];
        std::cout<<temp[i];
    }
}
