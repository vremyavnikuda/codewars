#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
#include <cmath>
#include <limits>
#include <algorithm>
#include <ctime>
#include <memory>
#include <stdexcept>

using namespace std;

// Статусы результатов вставки
enum class InsertResult
{
    SUCCESS_NEW,    // Успешно добавлен новый элемент
    SUCCESS_UPDATE, // Ключ существовал, значение обновлено
    ERR_KEY_RANGE,  // Ошибка: ключ вне допустимого диапазона
    ERR_TABLE_FULL  // Ошибка: таблица переполнена
};

// --- Утилита для безопасного ввода чисел ---
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

// ШАБЛОННЫЙ КЛАСС ХЕШ-ТАБЛИЦЫ С ОТКРЫТОЙ АДРЕСАЦИЕЙ
template <typename KeyType, typename T>
class HashTable
{
private:
    enum State
    {
        EMPTY,
        OCCUPIED,
        DELETED
    };

    struct Slot
    {
        KeyType key;
        T value;
        State state = EMPTY;
    };

    vector<Slot> table;
    size_t capacity;
    size_t num_elements = 0;

    const double c1 = 0.0;
    const double c2 = 1;

    // Границы ключей
    KeyType min_key;
    KeyType max_key;
    bool use_key_validation;

    // Статистика последней операции
    mutable uint32_t last_hash_value = 0;
    mutable int last_probes_count = 0;
    mutable size_t last_index = 0;

    // Метод свёртки (folding)
    uint32_t fold(KeyType k) const
    {
        uint32_t sum = 0;
        uint64_t key_val = static_cast<uint64_t>(k);
        while (key_val > 0)
        {
            sum += key_val % 1000;
            key_val /= 1000;
        }
        return sum;
    }

    // Хеш-функция (модульная)
    size_t hash_func(KeyType k) const
    {
        return fold(k) % capacity;
    }

    // Поиск индекса (Классическое квадратичное пробирование: h + i^2)
    size_t find_index(KeyType k, bool &found) const
    {
        size_t h = hash_func(k);
        last_hash_value = static_cast<uint32_t>(h);
        last_probes_count = 0;

        found = false;
        size_t first_deleted = capacity;

        size_t limit = min((size_t)10, capacity);

        for (size_t i = 0; i < limit; ++i)
        {
            last_probes_count++;

            size_t idx = (h + i * i) % capacity;

            if (table[idx].state == EMPTY)
            {

                last_index = (first_deleted != capacity) ? first_deleted : idx;
                return last_index;
            }
            if (table[idx].state == OCCUPIED && table[idx].key == k)
            {
                found = true;
                last_index = idx;
                return idx;
            }

            if (table[idx].state == DELETED && first_deleted == capacity)
            {
                first_deleted = idx;
            }
        }

        last_index = (first_deleted != capacity) ? first_deleted : capacity;
        return last_index;
    }

    // --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД: Поиск числа Мерсенна ---
    size_t get_next_mersenne(size_t n)
    {
        if (n == 0)
            return 1;

        // Побитовый алгоритм поиска ближайшего числа Мерсенна (2^p - 1) >= n
        // Пример: если n=6, нужно (2^3 - 1) = 7.
        // Mersenne числа в бинарном виде это всегда единицы: 1, 11, 111, 1111...

        size_t mersenne = 1;
        while (mersenne < n)
        {
            mersenne = (mersenne << 1) | 1; // Сдвигаем влево и ставим 1 в младший бит

            // Защита от переполнения size_t (бесконечный цикл)
            if (mersenne == numeric_limits<size_t>::max())
                break;
        }
        return mersenne;
    }

public:
    // Конструктор: max_elements - предельное количество элементов
    HashTable(size_t max_elements, KeyType min_k = 0, KeyType max_k = 0)
        : min_key(min_k), max_key(max_k), use_key_validation(min_k < max_k)
    {
        // --- ИСПРАВЛЕНИЕ: Расчет емкости ---
        // 1. Берем необходимый размер с запасом (коэффициент 2)
        size_t required_size = max_elements * 2;
        if (required_size == 0)
            required_size = 1;

        // 2. Ищем ближайшее число Мерсенна
        capacity = get_next_mersenne(required_size);

        table.resize(capacity);

        // Для отладки можно раскомментировать
        // cout << "[DEBUG] Запрошено: " << max_elements
        //      << ", Target: " << required_size
        //      << ", Mersenne Capacity: " << capacity << endl;
    }

    size_t size() const { return num_elements; }
    size_t get_capacity() const { return capacity; }
    bool empty() const { return num_elements == 0; }

    void clear()
    {
        for (auto &slot : table)
            slot.state = EMPTY;
        num_elements = 0;
    }

    T *find(KeyType k)
    {
        bool found = false;
        size_t idx = find_index(k, found);
        return found ? &table[idx].value : nullptr;
    }

    InsertResult insert(KeyType k, const T &val)
    {
        if (use_key_validation && (k < min_key || k > max_key))
        {
            return InsertResult::ERR_KEY_RANGE;
        }

        bool found = false;
        size_t idx = find_index(k, found);

        // Проверяем, удалось ли найти место для вставки (EMPTY или DELETED) за 10 проб
        if (idx != capacity)
        {
            // Дополнительная проверка на физическое переполнение (на всякий случай)
            if (num_elements >= capacity)
            {
                return InsertResult::ERR_TABLE_FULL;
            }

            table[idx].key = k;
            table[idx].value = val;
            table[idx].state = OCCUPIED;
            num_elements++;
            return InsertResult::SUCCESS_NEW;
        }

        // Если idx == capacity, значит за 10 проб не нашли ни ключа, ни пустой, ни удаленной ячейки
        return InsertResult::ERR_TABLE_FULL;
    }

    bool remove(KeyType k)
    {
        bool found = false;
        size_t idx = find_index(k, found);
        if (found)
        {
            table[idx].state = DELETED;
            num_elements--;
            return true;
        }
        return false;
    }

    void show() const
    {
        cout << "[Индекс] | Статус   | Ключ           | Значение" << endl;
        cout << "------------------------------------------------" << endl;
        for (size_t i = 0; i < capacity; ++i)
        {
            cout << " [" << setw(6) << i << "] | ";
            if (table[i].state == OCCUPIED)
                cout << "OCCUPIED | " << setw(12) << table[i].key << " | " << table[i].value;
            else if (table[i].state == DELETED)
                cout << "DELETED  | -            | -";
            else
                cout << "EMPTY    | -            | -";
            cout << endl;
        }
    }

    uint32_t get_last_hash() const { return last_hash_value; }
    int get_last_probes() const { return last_probes_count; }
    size_t get_last_index() const { return last_index; }

    static double BigO_Success(double alpha)
    {
        if (alpha <= 0)
            return 1.0;
        if (alpha >= 1.0)
            alpha = 0.99;
        return (1.0 / alpha) * log(1.0 / (1.0 - alpha));
    }

    static double BigO_Unsuccess(double alpha)
    {
        if (alpha >= 1.0)
            alpha = 0.99;
        return 1.0 / (1.0 - alpha);
    }

    // ИТЕРАТОР
    class Iterator
    {
    private:
        HashTable *ht;
        size_t pos;
        bool is_valid;

        void advance()
        {
            while (pos < ht->capacity && ht->table[pos].state != OCCUPIED)
            {
                pos++;
            }
        }

    public:
        Iterator(HashTable *h, size_t p) : ht(h), pos(p), is_valid(true)
        {
            if (ht != nullptr && pos < ht->capacity)
            {
                advance();
            }
        }

        bool isValid() const { return is_valid && ht != nullptr; }
        bool isEnd() const { return ht == nullptr || pos >= ht->capacity; }

        const T &operator*() const
        {
            if (!is_valid)
                throw logic_error("Ошибка: Итератор инвалидирован.");
            if (ht == nullptr || pos >= ht->capacity)
                throw out_of_range("Ошибка: Разыменование end-итератора.");
            if (ht->table[pos].state != OCCUPIED)
                throw runtime_error("Ошибка: Итератор указывает на незанятую ячейку.");
            return ht->table[pos].value;
        }

        T &operator*()
        {
            if (!is_valid)
                throw logic_error("Ошибка: Итератор инвалидирован.");
            if (ht == nullptr || pos >= ht->capacity)
                throw out_of_range("Ошибка: Разыменование end-итератора.");
            if (ht->table[pos].state != OCCUPIED)
                throw runtime_error("Ошибка: Итератор указывает на незанятую ячейку.");
            return ht->table[pos].value;
        }

        const KeyType &key() const
        {
            if (!is_valid)
                throw logic_error("Ошибка: Итератор инвалидирован.");
            if (ht == nullptr || pos >= ht->capacity)
                throw out_of_range("Ошибка: Доступ к ключу end-итератора.");
            return ht->table[pos].key;
        }

        size_t index() const { return pos; }

        Iterator &operator++()
        {
            if (!is_valid)
                throw logic_error("Ошибка: Инкремент инвалидированного итератора.");
            if (ht == nullptr || pos >= ht->capacity)
                throw out_of_range("Ошибка: Инкремент end-итератора невозможен.");
            pos++;
            advance();
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Iterator &other) const
        {
            if (isEnd() && other.isEnd())
                return true;
            return ht == other.ht && pos == other.pos;
        }

        bool operator!=(const Iterator &other) const
        {
            return !(*this == other);
        }

        void invalidate() { is_valid = false; }
    };

    Iterator begin() { return Iterator(this, 0); }
    Iterator end() { return Iterator(this, capacity); }

    double compute_chi_square(int num_experiments, int N) const
    {
        if (capacity == 0)
            return 0.0;
        double total_chi2 = 0.0;
        random_device rd;
        mt19937 gen(rd());

        KeyType range_min = use_key_validation ? min_key : 1000000000;
        KeyType range_max = use_key_validation ? max_key : 3000000000;
        uniform_int_distribution<KeyType> dist(range_min, range_max);

        for (int exp = 0; exp < num_experiments; ++exp)
        {
            vector<int> freq(capacity, 0);
            for (int i = 0; i < N; ++i)
                freq[hash_func(dist(gen))]++;
            double expected = static_cast<double>(N) / capacity;
            double chi2 = 0.0;
            for (int f : freq)
                chi2 += pow(f - expected, 2) / expected;
            total_chi2 += chi2;
        }
        return total_chi2 / num_experiments;
    }
};

uint32_t genkey()
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<uint32_t> dist(1000000000, 3000000000);
    return dist(gen);
}

void run_efficiency_test(size_t max_table_elements, double alpha)
{
    if (alpha <= 0 || alpha >= 1.0)
    {
        cout << ">>> ОШИБКА: Для открытой адресации alpha должно быть (0, 1)." << endl;
        return;
    }

    // 1. Создание таблицы. Размер подаем такой, чтобы при нужном k выполнялся alpha.
    // Т.к. HashTable внутри сама считает capacity = next_mersenne(N*2),
    // нам нужно аккуратно создать её.

    // Создадим "болванку" чтобы узнать, какой будет реальный capacity
    HashTable<uint32_t, int> temp(max_table_elements, 1000000000, 3000000000);
    size_t actual_capacity = temp.get_capacity();

    // Рассчитываем количество ключей k = capacity * alpha
    int k = static_cast<int>(actual_capacity * alpha);
    if (k == 0)
        k = 1;

    // Пересоздаем таблицу (хотя можно было использовать temp)
    HashTable<uint32_t, int> table(max_table_elements, 1000000000, 3000000000);

    // Вектор m для хранения существующих ключей (чтобы делать успешные поиск/удаление)
    vector<uint32_t> m;
    m.reserve(k);

    cout << ">>> Подготовка к тесту..." << endl;
    cout << "    Ёмкость (M): " << actual_capacity << endl;
    cout << "    Целевое кол-во (k): " << k << endl;

    // Заполнение таблицы до уровня alpha
    while (m.size() < k)
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

    // Обнуление счетчиков
    double sum_I = 0, sum_D = 0, sum_S = 0;

    // Количество операций в потоке (k/2 по заданию)
    int operations_count = k / 2;
    if (operations_count < 100)
        operations_count = 100; // Минимум 100 итераций для статистики

    cout << ">>> Запуск потока из " << operations_count << " операций..." << endl;

    for (int i = 0; i < operations_count; ++i)
    {
        // Условие промаха (неуспеха) - 10% случаев
        if (i % 10 == 0)
        {
            // 1. Неуспешное удаление (удаляем случайный ключ, которого скорее всего нет)
            uint32_t trash_key = genkey();
            // Шанс что trash_key случайно совпадет с m[...] есть, но мал.
            // В задании сказано "промахом считается удаление значения, отсутствующего в коллекции"
            table.remove(trash_key);
            sum_D += table.get_last_probes();

            // 2. Неуспешная вставка (вставляем дубликат)
            if (!m.empty())
            {
                uint32_t existing_key = m[rand() % m.size()];
                table.insert(existing_key, 1); // вернет SUCCESS_UPDATE или переполнение
                sum_I += table.get_last_probes();
            }

            // 3. Неуспешный поиск
            table.find(genkey());
            sum_S += table.get_last_probes();
        }
        else
        {
            // 90% Успешных операций
            if (!m.empty())
            {
                // 1. Успешное удаление
                int ind = rand() % m.size();
                uint32_t key_to_del = m[ind];

                table.remove(key_to_del);
                sum_D += table.get_last_probes();

                // 2. Успешная вставка (восстанавливаем баланс)
                uint32_t new_key = genkey();
                // Гарантируем уникальность для чистоты эксперимента
                while (table.find(new_key) != nullptr)
                {
                    new_key = genkey();
                }

                table.insert(new_key, 1);
                sum_I += table.get_last_probes();

                // Обновляем массив m, так как key_to_del удален, а new_key добавлен
                m[ind] = new_key;

                // 3. Успешный поиск
                uint32_t key_to_find = m[rand() % m.size()];
                table.find(key_to_find);
                sum_S += table.get_last_probes();
            }
        }
    }

    // --- Вывод результатов по заданию ---
    cout << string(50, '-') << endl;
    cout << "РЕЗУЛЬТАТЫ ЭКСПЕРИМЕНТА:" << endl;
    cout << "Items count end: " << table.size() << endl;
    double final_alpha = (double)table.size() / table.get_capacity();
    cout << "Alpha end:       " << fixed << setprecision(4) << final_alpha << endl;
    cout << string(50, '-') << endl;

    // Теоретические (для успешного поиска)
    cout << "Теор. Успех (BigO):    " << HashTable<uint32_t, int>::BigO_Success(alpha) << endl;
    // Теоретические (для неуспешного)
    cout << "Теор. Неуспех (BigO):  " << HashTable<uint32_t, int>::BigO_Unsuccess(alpha) << endl;
    cout << string(50, '-') << endl;

    // Экспериментальные средние
    // Делим на operations_count, так как в каждой итерации было по одной операции каждого типа
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

    // Теперь таблица автоматически рассчитает размер ближайшего числа Мерсенна >= 2*N
    HashTable<uint32_t, string> ht(max_elem, 1000000000, 3000000000);

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
        // ... (Меню осталось тем же, код main идентичен кроме вывода выше)
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
        {
            cout << " >>> [Итератор АКТИВЕН]" << endl;
        }

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
                    cout << "    Индекс: " << ht.get_last_index() << ", Проб: " << ht.get_last_probes() << endl;
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
                    case InsertResult::ERR_KEY_RANGE:
                        cout << ">>> ОШИБКА: Ключ вне диапазона!" << endl;
                        break;
                    case InsertResult::ERR_TABLE_FULL:
                        cout << ">>> ОШИБКА: Таблица переполнена! (Достигнут capacity)" << endl;
                        break;
                    }
                    cout << "    Индекс: " << ht.get_last_index() << ", Проб: " << ht.get_last_probes() << endl;

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
                    cout << "    Индекс: " << ht.get_last_index() << ", Проб: " << ht.get_last_probes() << endl;
                    if (iteratorActive)
                    {
                        stepIterator->invalidate();
                        iteratorActive = false;
                        cout << ">>> Итератор инвалидирован." << endl;
                    }
                    if (ht.size() == 0)
                    {
                        ht.clear();
                    }
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
                cout << ">>> KEY: " << stepIterator->key() << ", VAL: " << **stepIterator << endl;
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
