#include <iostream>
#include <string>
#include <random>
#include <iomanip>
#include <ctime>
#include <memory>
#include <limits>

#include "HashTable.h"

using namespace std;

// cin значений
template <typename T>
void safeInput(T &var, const string &prompt)
{
    while (true)
    {
        cout << prompt;
        if (cin >> var)
        {
            break;
        }
        else
        {
            cout << ">>> Ошибка ввода! Пожалуйста, введите число." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), ' ');
        }
    }
}

uint32_t genkey()
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<uint32_t> dist(1000000000u, 3000000000u);
    return dist(gen);
}

void run_efficiency_test(size_t max_table_elements, double alpha)
{
    if (alpha <= 0 || alpha >= 1.0)
    {
        cout << ">>> ОШИБКА: Для открытой адресации alpha должно быть (0, 1)." << endl;
        return;
    }
    HashTable<uint32_t, int> temp(max_table_elements, 1000000000u, 3000000000u);
    size_t actual_capacity = temp.get_capacity();
    int k = static_cast<int>(actual_capacity * alpha);
    if (k == 0)
        k = 1;
    HashTable<uint32_t, int> table(max_table_elements, 1000000000u, 3000000000u);
    vector<uint32_t> m;
    m.reserve(k);
    cout << ">>> Подготовка к тесту..." << endl;
    cout << "    Ёмкость (M): " << actual_capacity << endl;
    cout << "    Целевое кол-во (k): " << k << endl;
    while (static_cast<int>(m.size()) < k)
    {
        uint32_t key = genkey();
        if (table.insert(key, 1) == InsertResult::SUCCESS_NEW)
        {
            m.push_back(key);
        }
    }
    cout << ">>> Заполнение завершено." << endl;
    cout << "    Items count: " << table.size() << endl;
    cout << "    Current Alpha: " << (double)table.size() / table.get_capacity() << endl;
    double sum_I = 0, sum_D = 0, sum_S = 0;
    int operations_count = k / 2;
    if (operations_count < 100)
        operations_count = 100;
    cout << ">>> Запуск потока из " << operations_count << " операций..." << endl;
    for (int i = 0; i < operations_count; ++i)
    {
        // 10% промахи
        if (i % 10 == 0)
        {
            uint32_t trash_key = genkey();
            table.remove(trash_key);
            sum_D += table.get_last_probes();
            if (!m.empty())
            {
                uint32_t existing_key = m[rand() % m.size()];
                table.insert(existing_key, 1);
                sum_I += table.get_last_probes();
            }
            table.find(genkey());
            sum_S += table.get_last_probes();
        }
        else
        {
            if (!m.empty())
            {
                int ind = rand() % m.size();
                uint32_t key_to_del = m[ind];
                table.remove(key_to_del);
                sum_D += table.get_last_probes();
                uint32_t new_key = genkey();
                while (table.find(new_key) != nullptr)
                {
                    new_key = genkey();
                }
                table.insert(new_key, 1);
                sum_I += table.get_last_probes();
                m[ind] = new_key;
                uint32_t key_to_find = m[rand() % m.size()];
                table.find(key_to_find);
                sum_S += table.get_last_probes();
            }
        }
    }

    cout << string(50, '-') << endl;
    cout << "РЕЗУЛЬТАТЫ ЭКСПЕРИМЕНТА:" << endl;
    cout << "Items count end: " << table.size() << endl;
    double final_alpha = (double)table.size() / table.get_capacity();
    cout << "Alpha end:       " << fixed << setprecision(4) << final_alpha << endl;
    cout << string(50, '-') << endl;
    cout << "Теор. Успех (BigO):    " << HashTable<uint32_t, int>::BigO_Success(alpha) << endl;
    cout << "Теор. Неуспех (BigO):  " << HashTable<uint32_t, int>::BigO_Unsuccess(alpha) << endl;
    cout << string(50, '-') << endl;
    cout << "Exp. ср. ВСТАВКА (I):  " << sum_I / operations_count << endl;
    cout << "Exp. ср. УДАЛЕНИЕ (D): " << sum_D / operations_count << endl;
    cout << "Exp. ср. ПОИСК (S):    " << sum_S / operations_count << endl;
    cout << string(50, '-') << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(0)));
    size_t max_elem;
    safeInput(max_elem, "Введите предельное количество элементов (N): ");
    HashTable<uint32_t, string> ht(max_elem, 1000000000u, 3000000000u);
    cout << ">>> Таблица создана." << endl;
    unique_ptr<HashTable<uint32_t, string>::Iterator> stepIterator = nullptr;
    bool iteratorActive = false;
    int choice;
    uint32_t key;
    string value;
    do
    {
        cout << "" << string(55, '=') << endl;
        cout << "                   МЕНЮ ОПЕРАЦИЙ" << endl;
        cout << string(55, '=') << endl;
        cout << " [Базовые операции]" << endl;
        cout << "  1.  Количество элементов" << endl;
        cout << "  2.  Ёмкость таблицы" << endl;
        cout << "  3.  Проверка на пустоту" << endl;
        cout << "  4.  Очистка таблицы" << endl;
        cout << "  5.  Поиск элемента по ключу" << endl;
        cout << "  6.  Вставка элемента" << endl;
        cout << "  7.  Удаление элемента" << endl;
        cout << "  8.  Вывод структуры" << endl;
        cout << string(55, '-') << endl;
        cout << " [Статистика]" << endl;
        cout << "  9.  Опрос последнего хеш-значения" << endl;
        cout << " 10.  Опрос числа проб" << endl;
        cout << " 11.  Опрос последнего индекса" << endl;
        cout << string(55, '-') << endl;
        cout << " [Тестирование]" << endl;
        cout << " 12.  Тест качества (Хи-квадрат)" << endl;
        cout << " 13.  ТЕСТ ТРУДОЕМКОСТИ" << endl;
        cout << string(55, '-') << endl;
        cout << " [ПОШАГОВЫЙ ИТЕРАТОР]" << endl;
        cout << " 20.  Создать итератор (begin)" << endl;
        cout << " 21.  Показать текущий элемент (*)" << endl;
        cout << " 22.  Перейти к следующему (++)" << endl;
        cout << " 23.  Изменить данные текущего элемента" << endl;
        cout << string(55, '-') << endl;
        cout << "  0.  Выход" << endl;
        cout << string(55, '=') << endl;
        if (iteratorActive)
            cout << " >>> [Итератор АКТИВЕН]" << endl;
        safeInput(choice, "Выберите действие: ");
        try
        {
            switch (choice)
            {
            case 1:
                cout << ">>> Элементов: " << ht.size() << endl;
                break;
            case 2:
                cout << ">>> Ёмкость: " << ht.get_capacity() << endl;
                break;
            case 3:
                cout << ">>> Таблица " << (ht.empty() ? "пуста" : "содержит элементы") << endl;
                break;
            case 4:
                ht.clear();
                cout << ">>> Таблица очищена." << endl;
                if (iteratorActive)
                {
                    stepIterator->invalidate();
                    iteratorActive = false;
                    cout << ">>> Итератор инвалидирован." << endl;
                }
                break;
            case 5:
                safeInput(key, "Ключ для поиска: ");
                if (auto *v = ht.find(key))
                {
                    cout << ">>> НАЙДЕНО: " << *v << endl;
                    cout << "    Индекс: " << ht.get_last_index()
                         << ", Проб: " << ht.get_last_probes() << endl;
                }
                else
                {
                    cout << ">>> НЕ НАЙДЕНО." << endl;
                    cout << "    Проб: " << ht.get_last_probes() << endl;
                }
                break;
            case 6:
                safeInput(key, "Ключ: ");
                cout << "Значение: ";
                cin >> value;
                {
                    if (ht.find(key))
                        throw overflow_error("Такой элемент уже существует!");

                    InsertResult res = ht.insert(key, value);
                    switch (res)
                    {
                    case InsertResult::SUCCESS_NEW:
                        cout << ">>> УСПЕХ: Новый элемент добавлен." << endl;
                        break;
                    case InsertResult::SUCCESS_UPDATE:
                        cout << ">>> УСПЕХ: Элемент обновлен." << endl;
                        break;
                    case InsertResult::ERR_KEY_RANGE:
                        cout << ">>> ОШИБКА: Ключ вне диапазона!" << endl;
                        break;
                    case InsertResult::ERR_TABLE_FULL:
                        cout << ">>> ОШИБКА: Таблица переполнена! (Достигнут capacity)" << endl;
                        break;
                    }
                    cout << "    Индекс: " << ht.get_last_index()
                         << ", Проб: " << ht.get_last_probes() << endl;

                    if (iteratorActive && (res == InsertResult::SUCCESS_NEW))
                    {
                        stepIterator->invalidate();
                        iteratorActive = false;
                        cout << ">>> Итератор инвалидирован (структура изменена)." << endl;
                    }
                }
                break;
            case 7:
                safeInput(key, "Ключ для удаления: ");
                if (ht.remove(key))
                {
                    cout << ">>> УСПЕХ: Элемент удален." << endl;
                    cout << "    Индекс: " << ht.get_last_index()
                         << ", Проб: " << ht.get_last_probes() << endl;

                    if (iteratorActive)
                    {
                        stepIterator->invalidate();
                        iteratorActive = false;
                        cout << ">>> Итератор инвалидирован." << endl;
                    }
                    if (ht.size() == 0)
                        ht.clear();
                }
                else
                {
                    cout << ">>> ОШИБКА: Ключ не найден." << endl;
                    cout << "    Проб: " << ht.get_last_probes() << endl;
                }
                break;
            case 8:
                ht.show();
                break;
            case 9:
                cout << ">>> Последнее хеш-значение: " << ht.get_last_hash() << endl;
                break;
            case 10:
                cout << ">>> Число проб: " << ht.get_last_probes() << endl;
                break;
            case 11:
                cout << ">>> Последний индекс: " << ht.get_last_index() << endl;
                break;
            case 12:
                cout << ">>> Вычисление Хи-квадрат..." << endl;
                cout << ">>> Результат: " << ht.compute_chi_square(100, 1000) << endl;
                break;
            case 13:
            {
                double a;
                safeInput(a, "Введите alpha (0.1 - 0.99): ");
                if (a > 0 && a < 1)
                    run_efficiency_test(ht.get_capacity(), a);
                else
                    cout << ">>> ОШИБКА: Некорректный alpha!" << endl;
                break;
            }
            case 20:
                stepIterator = make_unique<HashTable<uint32_t, string>::Iterator>(ht.begin());
                iteratorActive = true;
                if (stepIterator->isEnd())
                    cout << ">>> Итератор создан (end)." << endl;
                else
                    cout << ">>> Итератор создан. Указывает на первый элемент." << endl;
                break;
            case 21:
                if (!iteratorActive || !stepIterator)
                    throw runtime_error("Iter not created");
                if (stepIterator->isEnd())
                    throw out_of_range("Iter at end");
                cout << ">>> KEY: " << stepIterator->key()
                     << ", VAL: " << **stepIterator << endl;
                break;
            case 22:
                if (!iteratorActive || !stepIterator)
                    throw runtime_error("Iter not created");
                if (stepIterator->isEnd())
                    throw out_of_range("Iter at end");
                ++(*stepIterator);
                cout << ">>> Сдвиг выполнен." << (stepIterator->isEnd() ? " (Теперь END)" : "") << endl;
                break;
            case 23:
                if (!iteratorActive || !stepIterator || stepIterator->isEnd())
                    throw out_of_range("Cannot edit");
                cout << "Val: ";
                cin >> value;
                **stepIterator = value;
                cout << ">>> Updated." << endl;
                break;
            case 0:
                cout << "Выход." << endl;
                break;
            default:
                cout << ">>> Неверная команда." << endl;
            }
        }
        catch (const exception &e)
        {
            cerr << ">>> EXCEPTION: " << e.what() << endl;
        }

    } while (choice != 0);
    return 0;
}