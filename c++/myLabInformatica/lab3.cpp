#include <iostream>

// Функция для циклического сдвига массива влево на k позиций
void rotateLeft(int arr[], int n, int k)
{
    // Убедимся, что k находится в пределах [0, n)
    k = k % n;
    if (k < 0)
        k += n;

    // Используем временный массив для хранения первых k элементов
    int *temp = new int[k];
    for (int i = 0; i < k; ++i)
    {
        temp[i] = arr[i];
    }

    // Перемещаем оставшиеся элементы влево
    for (int i = 0; i < n - k; ++i)
    {
        arr[i] = arr[i + k];
    }

    // Копируем временные элементы в конец массива
    for (int i = 0; i < k; ++i)
    {
        arr[n - k + i] = temp[i];
    }

    // Освобождаем временный массив
    delete[] temp;
}

// Функция для вывода массива
void printArray(const int arr[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int n, k;

    std::cout << "Enter the number of elements in the array: ";
    std::cin >> n;

    int *arr = new int[n];

    std::cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i];
    }

    std::cout << "Enter the number of positions to rotate left: ";
    std::cin >> k;

    rotateLeft(arr, n, k);

    std::cout << "Array after left rotation: ";
    printArray(arr, n);

    // Освобождаем динамически выделенный массив
    delete[] arr;

    return 0;
}
