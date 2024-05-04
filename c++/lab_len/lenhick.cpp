#include <iostream>

/**
 * Функция, определяющая, входит ли список L1 в список L2.
 * @param L1 - массив элементов первого списка
 * @param size1 - размер первого списка
 * @param L2 - массив элементов второго списка
 * @param size2 - размер второго списка
 * @return Адрес начала вхождения списка L1 в L2 (0, если не найден)
 */
int findSublist(int L1[], int size1, int L2[], int size2)
{
    // Если один из списков пустой, возвращаем 0
    if (size1 == 0 || size2 == 0)
    {
        return 0; 
    }
    // Проходим по всем возможным позициям, с которых список L1 может начинаться в L2
    for (int i = 0; i <= size2 - size1; i++)
    {
        bool found = true;
        // Сравниваем элементы списков L1 и L2, начиная с позиции i в L2
        for (int j = 0; j < size1; j++)
        {
            if (L1[j] != L2[i + j])
            {
                found = false;
                break;
            }
        }
        // Если все элементы списка L1 найдены в L2, возвращаем адрес начала вхождения
        if (found)
        {
            return i; // Возвращаем адрес начала вхождения
        }
    }
    // Если список L1 не найден в L2, возвращаем 0
    return 0;
}

int main()
{
    int L1[] = {3, 4};
    int L2[] = {1, 1,  4, 5};
    int size1 = sizeof(L1) / sizeof(L1[0]);
    int size2 = sizeof(L2) / sizeof(L2[0]);
    // Вызываем функцию findSublist и выводим результат
    int address = findSublist(L1, size1, L2, size2);
    std::cout << "Address: " << address << std::endl;
    return 0;
}
