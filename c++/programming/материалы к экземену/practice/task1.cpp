#include <iostream>
#include <list>
#include <algorithm>

// Функция для проверки вхождения списка L1 в список L2
bool isSublist(const std::list<int> &L1, const std::list<int> &L2)
{
    if (L1.size() > L2.size())
        return false;
    auto it = std::search(L2.begin(), L2.end(), L1.begin(), L1.end());
    return it != L2.end();
}

// Функция для разделения лишних элементов из длинного списка в третий список
void separateLists(std::list<int> &L1, std::list<int> &L2, std::list<int> &L3)
{
    if (L1.size() > L2.size())
    {
        auto it = L1.begin();
        std::advance(it, L1.size() - L2.size());
        L3.splice(L3.begin(), L1, L1.begin(), it);
    }
    else if (L2.size() > L1.size())
    {
        auto it = L2.begin();
        std::advance(it, L2.size() - L1.size());
        L3.splice(L3.begin(), L2, L2.begin(), it);
    }
}

int main()
{
    // Создаем списки
    std::list<int> L1 = {1, 2, 3};
    std::list<int> L2 = {0, 1, 2, 3, 4};
    std::list<int> L3;

    // Проверяем вхождение списка L1 в L2
    bool L1_in_L2 = isSublist(L1, L2);
    bool L2_in_L1 = isSublist(L2, L1);

    std::cout << "L1 is sublist of L2: " << (L1_in_L2 ? "Yes" : "No") << std::endl;
    std::cout << "L2 is sublist of L1: " << (L2_in_L1 ? "Yes" : "No") << std::endl;

    // Разделяем лишние элементы в третий список
    separateLists(L1, L2, L3);

    // Выводим результаты
    std::cout << "L1 after separation: ";
    for (int n : L1)
        std::cout << n << " ";
    std::cout << std::endl;

    std::cout << "L2 after separation: ";
    for (int n : L2)
        std::cout << n << " ";
    std::cout << std::endl;

    std::cout << "L3 (extra elements): ";
    for (int n : L3)
        std::cout << n << " ";
    std::cout << std::endl;

    return 0;
}
