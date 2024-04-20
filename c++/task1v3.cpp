#include <iostream>
#include <cstring>
#include <windows.h>

// Массив слов для построения кроссворда
const char* w[] = { "apple", "banana", "", "date", "elderberry", "fig", "grape", nullptr };

// Массив для хранения лучшего (максимального) кроссворда
const char* best_w[sizeof(w) / sizeof(w[0])];

// Длина лучшего кроссворда
int best_len = 0;

// Функция для построения кроссворда
void buildCrossword(int k)
{
    // Вычисляем текущую длину кроссворда
    int len = 0;
    for (int i = 0; i <= k; ++i)
        len += strlen(w[i]);

    // Если текущий кроссворд длиннее лучшего, обновляем лучший
    if (len > best_len)
    {
        best_len = len;
        for (int i = 0; i <= k; ++i)
            best_w[i] = w[i];
        best_w[k + 1] = nullptr;
    }

    // Если все слова использованы, прекращаем построение
    if (w[k + 1] == nullptr)
        return;

    // Ищем следующее слово, которое начинается с той же буквы, что и заканчивается предыдущее
    int l = 0;
    if (k != -1)
        l = strlen(w[k]) - 1;

    for (int n = k + 1; w[n] != nullptr; n++)
        if (k == -1 || w[k][l] == w[n][0])
        {
            // Меняем местами слова
            const char* q = w[k + 1];
            w[k + 1] = w[n];
            w[n] = q;

            // Продолжаем строить кроссворд
            buildCrossword(k + 1);

            // Возвращаем слова на их места
            q = w[k + 1];
            w[k + 1] = w[n];
            w[n] = q;
        }
}

int main()
{
    // Строим кроссворд
    buildCrossword(-1);

    // Выводим лучший кроссворд
    for (int s = 0, i = 0; best_w[i] != nullptr; i++)
    {
        for (int j = 0; j < s; j++)
            std::cout << ' ';

        s += strlen(best_w[i]) - 1;
        std::cout << best_w[i] << std::endl;
    }

    return 0;
}
