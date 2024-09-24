//
// Created by vremyavnikuda on 9/25/24.
//
#include <iostream>

void print_hor(int width);
void print_vert(int width, int height);

void print_hor(int width) {
    for (int i = 0; i < width; i++) {
        std::cout << "#";
    }
    std::cout << std::endl;
}

void print_vert(int width, int height) {
    for (int i = 0; i < height - 2; i++) {
        std::cout << "#";
        for (int j = 0; j < width - 2; j++) {
            std::cout << " ";
        }
        std::cout << "#" << std::endl;
    }
}

void print(int width, int height) {
    print_hor(width);
    print_vert(width, height);
    print_hor(width);
}

int main() {
    int width, height;
    std::cin >> width >> height;
    print(width, height);
}
