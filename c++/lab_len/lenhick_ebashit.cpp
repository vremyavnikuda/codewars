#include <stdlib.h>
#include <string.h>
#include <stdio.h>

double SrArifm(int *list, int size)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += list[i];
    }
    return size > 0 ? sum / size : 0;
}

int checkid(int *list1, int *list2, int size1, int size2)
{
    if (size1 == 0 || size2 == 0)
    {
        return -1; // Возвращаем -1, если один из списков пустой
    }
    for (int i = 0; i <= size2 - size1; i++)
    {
        bool flug = true;
        for (int j = 0; j < size1; j++)
        {
            if (list1[j] != list2[j + i])
            {
                flug = false;
                break;
            }
        }
        if (flug)
        {
            return i; // Возвращаем индекс начала вхождения
        }
    }
    return -1; // Возвращаем -1, если список list1 не найден в list2
}

int main()
{
    int size1, size2;

    // Запрашиваем размер списков у пользователя
    printf("Enter size of list 1: ");
    scanf("%d", &size1);
    printf("Enter size of list 2: ");
    scanf("%d", &size2);
    getchar(); // Очищаем символ новой строки из входного буфера

    // Выделяем память под списки
    int *list1 = (int *)malloc(size1 * sizeof(int));
    int *list2 = (int *)malloc(size2 * sizeof(int));

    if (list1 == NULL || list2 == NULL)
    {
        printf("Fail\n");
        return 1;
    }

    // Заполняем первый список
    printf("elementi pervogo spiska cherez probel: ");
    for (int i = 0; i < size1; i++)
    {
        scanf("%d", &list1[i]);
    }
    getchar(); // Очищаем символ новой строки из входного буфера

    // Заполняем второй список
    printf("elementi vtorogo spiska cherez probel: ");
    for (int i = 0; i < size2; i++)
    {
        scanf("%d", &list2[i]);
    }
    getchar(); // Очищаем символ новой строки из входного буфера

    // Выводим содержимое обоих списков
    printf("\n pervii spisok:\n");
    for (int i = 0; i < size1; i++)
    {
        printf("%d ", list1[i]);
    }

    printf("\n vtoroi spisok:\n");
    for (int i = 0; i < size2; i++)
    {
        printf("%d ", list2[i]);
    }
    // ввывод среднего арифметического
    printf("sreednee 1: %.1f\n", SrArifm(list1, size1));
    printf("sreednee 2: %.1f\n", SrArifm(list2, size2));

    // Проверяем вхождение первого списка во второй и выводим результат и индекс первого совпадения, если он есть
    int index = checkid(list1, list2, size1, size2);
    if (index != -1)
    {
        printf("spisok 1 vhodit v spisok 2\n");
        printf("index vhozhdeniya: %d\n", index);
    }
    else
    {
        printf("spisok 1 ne vhodit v spisok 2\n");
    }

    free(list1);
    free(list2);
    // printf("%d", checkind(list1, list2, size));
    return 0;
}
