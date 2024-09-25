// Функция для поиска максимального элемента в списке #include <climits>
#include <climits>
#include <iostream>

// Функция для поиска максимального элемента в массиве и возврата его индекса
int findMaxElementAddress(int list[], int size) {
    // Инициализация максимального элемента как минимально возможного значения
    int maxElement = INT_MIN;
    // Инициализация адреса (индекса) максимального элемента как -1
    int address = -1;
    // Цикл по всем элементам массива
    for (int i = 0; i < size; i++) {
        // Если текущий элемент больше максимального, обновляем максимальный
        // элемент и его адрес
        if (list[i] > maxElement) {
            maxElement = list[i];
            address = i;
        }
    }
    // Возвращаем адрес максимального элемента
    return address;
}

// Функция для добавления элементов массива L2 в массив L1 после первого
// вхождения элемента E
int addElementsAfterFirstOccurrence(int L1[], int &L1Size, int E, int L2[],
                                    int L2Size) {
    // Инициализация индекса вставки как -1
    int insertIndex = -1;
    // Цикл по всем элементам массива L1
    for (int i = 0; i < L1Size; i++) {
        // Если текущий элемент равен E, обновляем индекс вставки и прерываем
        // цикл
        if (L1[i] == E) {
            insertIndex = i + 1;
            break;
        }
    }
    // Если индекс вставки не равен -1, то есть, если элемент E найден в массиве
    // L1
    if (insertIndex != -1) {
        // Цикл по всем элементам массива L2
        for (int i = 0; i < L2Size; i++) {
            // Сдвигаем все элементы массива L1, начиная с индекса вставки, на
            // одну позицию вправо
            for (int j = L1Size; j > insertIndex; j--) {
                L1[j] = L1[j - 1];
            }
            // Вставляем текущий элемент массива L2 на позицию индекса вставки в
            // массив L1
            L1[insertIndex++] = L2[i];
            // Увеличиваем размер массива L1
            L1Size++;
        }
    }
    // Возвращаем размер нового массива L1
    return L1Size;
}

int main() {

    const int SIZE1 = 5;
    const int SIZE2 = 3;

    int L1[SIZE1] = {54, 24, 34, 1, 154};
    int L2[SIZE2] = {6, 7, 8};

    int L1Size = SIZE1;
    int L2Size = SIZE2;

    int maxElementAddress = findMaxElementAddress(L1, L1Size);

    std::cout << "Max element address: " << maxElementAddress << std::endl;
    int elementToFind = 1;
    int newSize =
        addElementsAfterFirstOccurrence(L1, L1Size, elementToFind, L2, L2Size);
    std::cout << "New list size: " << newSize << std::endl;
    return 0;
}
