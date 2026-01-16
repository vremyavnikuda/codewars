// main.cpp
// ЛР1: Хеш-таблица (вариант 7)
// Открытая адресация + свёртка (folding) + модульное хеширование + квадратичное зондирование
//
// Ключ: натуральное число ~ [1_000_000_000; 3_000_000_000] (используем uint64_t)
// Поведение Insert: если ключ уже есть — значение ОБНОВЛЯЕТСЯ, а функция возвращает false (не "новая вставка").
//
// Компилировать (пример):

#include <iostream>
#include <string>
#include <clocale>
#include <cstdlib>
#include "HashTable.h"

using std::cin;
using std::cout;

int main()
{
    system("chcp 65001 > nul");
    setlocale(LC_ALL, "ru_RU.UTF-8");

    std::size_t n_max;
    cout << "Введите n_max (планируемое максимальное количество элементов): ";
    cout.flush();
    if (!(cin >> n_max))
        return 0;

    HashTable<std::uint64_t, std::string> ht(n_max);

    while (true)
    {
        cout << "\n МЕНЮ\n"
             << "1) Вставить (ключ, значение)\n"
             << "2) Найти (ключ)\n"
             << "3) Удалить (ключ)\n"
             << "4) Вывести таблицу\n"
             << "5) Информация о таблице (размер/ёмкость/последний хеш/зондирования)\n"
             << "6) Итерировать по занятым элементам\n"
             << "7) Эксперимент хи-квадрат (качество хеша)\n"
             << "0) Выход\n"
             << "Выберите: ";
        cout.flush();

        int cmd;
        cin >> cmd;
        if (!cin)
            break;

        if (cmd == 0)
            break;

        if (cmd == 1)
        {
            std::uint64_t key;
            std::string value;
            cout << "ключ (uint64): ";
            cin >> key;
            cout << "значение : ";
            cin >> value;
            bool inserted = ht.Insert(key, value);
            cout << (inserted ? "Вставлен НОВЫЙ элемент.\n" : "Обновлено существующее или не удалось вставить.\n");
            cout << "хеш = " << ht.LastHash() << " зондирования = " << ht.LastProbes() << "\n";
        }
        else if (cmd == 2)
        {
            std::uint64_t key;
            cout << "ключ: ";
            cin >> key;
            auto *p = ht.Find(key);
            if (p)
            {
                cout << "Найдено. значение = " << *p << "\n";
            }
            else
            {
                cout << "Не найдено.\n";
            }
            cout << "хеш = " << ht.LastHash() << " зондирования = " << ht.LastProbes() << "\n";
        }
        else if (cmd == 3)
        {
            std::uint64_t key;
            cout << "ключ: ";
            cin >> key;
            bool ok = ht.Erase(key);
            cout << (ok ? "Удалено.\n" : "Ключ не найден.\n");
            cout << "хеш = " << ht.LastHash() << " зондирования = " << ht.LastProbes() << "\n";
        }
        else if (cmd == 4)
        {
            ht.Print(std::cout);
        }
        else if (cmd == 5)
        {
            cout << "размер =" << ht.Size()
                 << " ёмкость =" << ht.Capacity()
                 << " пусто =" << (ht.Empty() ? "истина" : "ложь") << "\n";
            cout << "последний хеш =" << ht.LastHash()
                 << " последнее зондирование =" << ht.LastProbes() << "\n";
        }
        else if (cmd == 6)
        {
            cout << "Занятые элементы:\n";
            for (auto it = ht.Begin(); it != ht.End(); ++it)
            {
                cout << "индекс = " << it.index() << " ключ = " << it.key() << " значение = " << *it << "\n";
            }
        }
        else if (cmd == 7)
        {
            std::size_t m = ht.Capacity();
            std::size_t N = 20 * m;
            int trials = 5;
            cout << "Текущая ёмкость m = " << m << "\n";
            cout << "По умолчанию N=20*m = " << N << "\n";
            cout << "Введите N (0 для сохранения по умолчанию): ";
            std::size_t N_in;
            cin >> N_in;
            if (N_in != 0)
                N = N_in;
            cout << "Введите количество испытаний (например, 5 или 10): ";
            cin >> trials;
            if (trials <= 0)
                trials = 5;
            chi_square_for_capacity(m, N, trials);
        }
        else
        {
            cout << "Неизвестная команда.\n";
        }
    }
    return 0;
}
