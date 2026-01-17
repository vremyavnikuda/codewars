#pragma once

#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <iostream>
#include <iomanip>

// Статусы результатов вставки
enum class InsertResult
{
    SUCCESS_NEW,
    SUCCESS_UPDATE,
    ERR_KEY_RANGE,
    ERR_TABLE_FULL
};

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
        KeyType key{};
        T value{};
        State state = EMPTY;
    };
    std::vector<Slot> table;
    size_t capacity{};
    size_t num_elements = 0;
    const double c1 = 0.0;
    const double c2 = 1.0;
    // Границы ключей
    KeyType min_key{};
    KeyType max_key{};
    bool use_key_validation{false};
    // Статистика последней операции
    mutable uint32_t last_hash_value = 0;
    mutable int last_probes_count = 0;
    mutable size_t last_index = 0;
    // Метод свёртки
    uint32_t fold(KeyType k) const
    {
        uint32_t sum = 0;
        uint64_t key_val = static_cast<uint64_t>(k);
        while (key_val > 0)
        {
            sum += static_cast<uint32_t>(key_val % 1000);
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
        size_t limit = std::min(static_cast<size_t>(10), capacity);
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

    // ВСПОМОГАТЕЛЬНЫЙ МЕТОД: Поиск числа Мерсенна (2^p - 1) >= n
    size_t get_next_mersenne(size_t n)
    {
        if (n == 0)
            return 1;

        size_t mersenne = 1;
        while (mersenne < n)
        {
            mersenne = (mersenne << 1) | 1;
            if (mersenne == std::numeric_limits<size_t>::max())
                break;
        }
        return mersenne;
    }

public:
    // Конструктор: max_elements - предельное количество элементов
    HashTable(size_t max_elements, KeyType min_k = 0, KeyType max_k = 0)
        : min_key(min_k), max_key(max_k), use_key_validation(min_k < max_k)
    {
        size_t required_size = max_elements * 2;
        if (required_size == 0)
            required_size = 1;

        capacity = get_next_mersenne(required_size);
        table.resize(capacity);
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
        if (idx != capacity)
        {
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
        std::cout << "[Индекс] | Статус   | Ключ           | Значение\n";
        std::cout << "------------------------------------------------\n";
        for (size_t i = 0; i < capacity; ++i)
        {
            std::cout << " [" << std::setw(6) << i << "] | ";
            if (table[i].state == OCCUPIED)
                std::cout << "OCCUPIED | " << std::setw(12) << table[i].key << " | " << table[i].value;
            else if (table[i].state == DELETED)
                std::cout << "DELETED  | -            | -";
            else
                std::cout << "EMPTY    | -            | -";
            std::cout << "\n";
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
        return (1.0 / alpha) * std::log(1.0 / (1.0 - alpha));
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
                throw std::logic_error("Ошибка: Итератор инвалидирован.");
            if (ht == nullptr || pos >= ht->capacity)
                throw std::out_of_range("Ошибка: Разыменование end-итератора.");
            if (ht->table[pos].state != OCCUPIED)
                throw std::runtime_error("Ошибка: Итератор указывает на незанятую ячейку.");
            return ht->table[pos].value;
        }
        T &operator*()
        {
            if (!is_valid)
                throw std::logic_error("Ошибка: Итератор инвалидирован.");
            if (ht == nullptr || pos >= ht->capacity)
                throw std::out_of_range("Ошибка: Разыменование end-итератора.");
            if (ht->table[pos].state != OCCUPIED)
                throw std::runtime_error("Ошибка: Итератор указывает на незанятую ячейку.");
            return ht->table[pos].value;
        }
        const KeyType &key() const
        {
            if (!is_valid)
                throw std::logic_error("Ошибка: Итератор инвалидирован.");
            if (ht == nullptr || pos >= ht->capacity)
                throw std::out_of_range("Ошибка: Доступ к ключу end-итератора.");
            return ht->table[pos].key;
        }
        size_t index() const { return pos; }
        Iterator &operator++()
        {
            if (!is_valid)
                throw std::logic_error("Ошибка: Инкремент инвалидированного итератора.");
            if (ht == nullptr || pos >= ht->capacity)
                throw std::out_of_range("Ошибка: Инкремент end-итератора невозможен.");
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
        std::random_device rd;
        std::mt19937 gen(rd());
        KeyType range_min = use_key_validation ? min_key : static_cast<KeyType>(1000000000);
        KeyType range_max = use_key_validation ? max_key : static_cast<KeyType>(3000000000);
        std::uniform_int_distribution<KeyType> dist(range_min, range_max);
        for (int exp = 0; exp < num_experiments; ++exp)
        {
            std::vector<int> freq(capacity, 0);
            for (int i = 0; i < N; ++i)
                freq[hash_func(dist(gen))]++;
            double expected = static_cast<double>(N) / capacity;
            double chi2 = 0.0;
            for (int f : freq)
                chi2 += std::pow(f - expected, 2) / expected;
            total_chi2 += chi2;
        }
        return total_chi2 / num_experiments;
    }
};