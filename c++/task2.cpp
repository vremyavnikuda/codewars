#include <iostream>
#include <vector>
#include <algorithm>


//Лабораторная работа №2 "Односвязные списки"
//Найти максимальный элемент списка, вернуть адрес.
int* findMaxElementAddress(std::vector<int>& vec) {
    if(vec.empty()) {
        return nullptr; // Возвращаем nullptr, если вектор пуст
    }
    auto maxElementIter = std::max_element(vec.begin(), vec.end());
    return &(*maxElementIter);
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    int* maxElementAddress = findMaxElementAddress(vec);
    if(maxElementAddress) {
        std::cout << "Адрес максимального элемента: " << maxElementAddress << std::endl;
        std::cout << "Максимальный элемент: " << *maxElementAddress << std::endl;
    }
    return 0;
}

/// @brief 
/// @param L1 
/// @param E 
/// @param L2 
/// @return
///Добавить в список L1 за первым вхождением элемента Е все элементы списка L2, вернуть длину нового списка. 
int addElementsAfterE(std::vector<int>& L1,int E,const std::vector<int>& L2) {
    //Находим первое вхождение элемента Е в списке L1
    auto it = std::find(L1.begin(), L1.end(), E);

    //Если элемент е найдем , то добавляем все элементы из l2 после e
    if (it != L1.end()) {
        L1.insert(it + 1, L2.begin(), L2.end());
        return L1.size();
    }
    // e not found in the list
    return -1;
}


//тут я с кайфом перебираю вектора и вывожу их в консоль ,ну тип как в java только в с++
void printVector(const std::vector<int>& vec) {
    for (const auto& el : vec) {
        std::cout << el << ' ';
    }
    std::cout << std::endl;
}

int main(){
    std::vector<int> L1 = {1, 2, 3, 4, 5};
    int E = 3;
    std::vector<int> L2={6, 7, 8, 9, 10};
    int newLength = addElementsAfterE(L1, E, {6, 7, 8, 9, 10});

    std::cout << "Полученный список: ";
    printVector(L1);
    std::cout << "Исходный список: ";
    printVector(L2);
    
    std::cout << "Длина нового списка: " << newLength << std::endl;
    return 0;
}