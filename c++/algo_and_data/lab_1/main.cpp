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
#include <limits>
#include <stdexcept>
#include "HashTable.h"

using std::cin;
using std::cout;

static constexpr std::uint64_t kMinKey = 1000000000ULL;
static constexpr std::uint64_t kMaxKey = 3000000000ULL;

static void clear_input_line()
{
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    system("chcp 65001 > nul");
    setlocale(LC_ALL, "ru_RU.UTF-8");

    std::size_t n_max = 0;
    while (true)
    {
        try
        {
            cout << "Введите n_max (планируемое максимальное количество элементов): ";
            cout.flush();
            long long n_max_in;
            if (!(cin >> n_max_in))
                throw std::invalid_argument("Invalid n_max.");
            if (n_max_in <= 0)
                throw std::out_of_range("n_max must be > 0.");
            if (static_cast<unsigned long long>(n_max_in) > std::numeric_limits<std::size_t>::max())
                throw std::out_of_range("n_max is too large.");
            n_max = static_cast<std::size_t>(n_max_in);
            break;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << "\n";
            clear_input_line();
        }
    }

    HashTable<std::uint64_t, std::string> ht(n_max);

    while (true)
    {
        try
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
                throw std::invalid_argument("Invalid command input.");
            if (cmd < 0 || cmd > 7)
                throw std::out_of_range("Unknown command. Use 0..7.");

            if (cmd == 0)
                break;

            if (cmd == 1)
            {
                long long key_in;
                std::string value;
                cout << "ключ (uint64): ";
                cin >> key_in;
                if (!cin)
                    throw std::invalid_argument("Invalid key input.");
                if (key_in < static_cast<long long>(kMinKey) || key_in > static_cast<long long>(kMaxKey))
                    throw std::out_of_range("Key out of range [1000000000; 3000000000].");
                std::uint64_t key = static_cast<std::uint64_t>(key_in);
                cout << "значение : ";
                cin >> value;
                if (!cin)
                    throw std::invalid_argument("Invalid value input.");
                bool inserted = ht.Insert(key, value);
                cout << (inserted ? "Вставлен НОВЫЙ элемент.\n" : "Обновлено существующее или не удалось вставить.\n");
                cout << "хеш = " << ht.LastHash() << " зондирования = " << ht.LastProbes() << "\n";
            }
            else if (cmd == 2)
            {
                long long key_in;
                cout << "ключ: ";
                cin >> key_in;
                if (!cin)
                    throw std::invalid_argument("Invalid key input.");
                if (key_in < static_cast<long long>(kMinKey) || key_in > static_cast<long long>(kMaxKey))
                    throw std::out_of_range("Key out of range [1000000000; 3000000000].");
                std::uint64_t key = static_cast<std::uint64_t>(key_in);
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
                long long key_in;
                cout << "ключ: ";
                cin >> key_in;
                if (!cin)
                    throw std::invalid_argument("Invalid key input.");
                if (key_in < static_cast<long long>(kMinKey) || key_in > static_cast<long long>(kMaxKey))
                    throw std::out_of_range("Key out of range [1000000000; 3000000000].");
                std::uint64_t key = static_cast<std::uint64_t>(key_in);
                bool ok = ht.Erase(key);
                cout << (ok ? "Удалено.\n" : "Ключ не найден.\n");
                cout << "хеш = " << ht.LastHash() << " зондирования = " << ht.LastProbes() << "\n";
            }
            else if (cmd == 4)
            {
                ht.Print(std::cout);
                cout << "последний хеш =" << ht.LastHash()
                     << " последнее зондирование =" << ht.LastProbes() << "\n";
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
                long long N_in;
                cin >> N_in;
                if (!cin)
                    throw std::invalid_argument("Invalid N input.");
                if (N_in < 0)
                    throw std::out_of_range("N must be >= 0.");
                if (N_in != 0)
                    N = static_cast<std::size_t>(N_in);
                cout << "Введите количество испытаний (например, 5 или 10): ";
                long long trials_in;
                cin >> trials_in;
                if (!cin)
                    throw std::invalid_argument("Invalid trials input.");
                if (trials_in <= 0 || trials_in > std::numeric_limits<int>::max())
                    throw std::out_of_range("Trials must be a positive int.");
                trials = static_cast<int>(trials_in);
                chi_square_for_capacity(m, N, trials);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << "\n";
            clear_input_line();
        }
        catch (...)
        {
            std::cerr << "Unknown error.\n";
            clear_input_line();
        }
    }
    return 0;
}
