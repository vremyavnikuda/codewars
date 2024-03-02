#include <cstdio>
#include <stddef.h>
#include <string.h>
char* w[] = {
    "sinus",
    "prefix",
    "setup",
    "plintus",
    "drop",
    "xeon",
    NULL
};

// k - номер шага
void buildCrossword(int k)
{
    if (w[k + 1] == nullptr) throw 1; // Все слова выбраны - успех

    int l = 0;
    if (k != -1) l = strlen(w[k]) - 1; // Выход из цепочки рекурсивных вызовов

    for (int n = k + 1; w[n] != nullptr; n++) // через исключение
        if (k == -1 ||
            w[k][l] == w[n][0])
        {
            // совпадение символов или первое слово

            char* q = w[k + 1];
            w[k + 1] = w[n];
            w[n] = q; // Обмен найденного со следующим за...

            buildCrossword(k + 1); // попытка вывести цепочку из нового слова

            q = w[k + 1];
            w[k + 1] = w[n];
            w[n] = q; // Обратный обмен для продолжения поиска
        }
}

int main()
{
    try
    {
        buildCrossword(-1);
    }
    catch (int v)
    {
        // Обработчик исключения -

        for (int s = 0, i = 0; w[i] != nullptr;
             i++)
        {
            // вывод слов «лесенкой» с подсчетом

            for (int j = 0; j < s; j++)
                putchar(' '); // числа символов в предыдущих словах

            s += strlen(w[i]) - 1;
            puts(w[i]);
        }
    }
    return 0;
}
