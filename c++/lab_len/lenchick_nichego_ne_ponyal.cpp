#include <iostream>
#include <list>

/**
 * Функция, определяющая, входит ли список L1 в список L2.
 * @param L1 - список элементов первого списка
 * @param L2 - список элементов второго списка
 * @return Итератор на начало вхождения списка L1 в L2 (конец списка L2, если не найден)
 */
std::list<int>::iterator findSublist(std::list<int> &L1, std::list<int> &L2)
{
    // Если один из списков пустой, возвращаем конец списка L2
    if (L1.empty() || L2.empty())
    {
        return L2.end();
    }

    // Проходим по всем возможным позициям, с которых список L1 может начинаться в L2
    for (auto it = L2.begin(); it != std::prev(L2.end(), L1.size() - 1); ++it)
    {
        bool found = true;
        // Сравниваем элементы списков L1 и L2, начиная с текущей позиции в L2
        auto it1 = L1.begin();
        for (auto it2 = it; it2 != std::next(it, L1.size()); ++it2)
        {
            if (*it1 != *it2)
            {
                found = false;
                break;
            }
            ++it1;
        }
        // Если все элементы списка L1 найдены в L2, возвращаем итератор на начало вхождения
        if (found)
        {
            return it;
        }
    }

    // Если список L1 не найден в L2, возвращаем конец списка L2
    return L2.end();
}

int main()
{
    std::list<int> L1 = {3, 4};
    std::list<int> L2 = {1, 1, 3, 4, 5};

    // Вызываем функцию findSublist и выводим результат
    auto it = findSublist(L1, L2);
    if (it != L2.end())
    {
        std::cout << "Address: " << *it << std::endl;
    }
    else
    {
        std::cout << "Sublist not found in the main list." << std::endl;
    }

    return 0;
}
