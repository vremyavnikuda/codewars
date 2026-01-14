#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <random>
#include <limits>
#include <cstdint>
#include <cmath>
#include <iomanip>

static bool is_prime(std::size_t x)
{
    if (x < 2)
        return false;
    if (x % 2 == 0)
        return x == 2;
    for (std::size_t d = 3; d * d <= x; d += 2)
    {
        if (x % d == 0)
            return false;
    }
    return true;
}

static std::size_t next_prime(std::size_t x)
{
    if (x <= 2)
        return 2;
    if (x % 2 == 0)
        ++x;
    while (!is_prime(x))
        x += 2;
    return x;
}

template <class K, class V>
class HashTable
{
public:
    enum class State
    {
        FREE,
        BUSY,
        DELETED
    };
    struct Cell
    {
        K key{};
        V value{};
        State state{State::FREE};
    };
    class Iterator
    {
    public:
        Iterator(HashTable *ht, std::size_t start) : ht_(ht), pos_(start)
        {
            advance_to_busy();
        }
        V &operator*() const
        {
            return ht_->table_[pos_].value;
        }
        Iterator &operator++()
        {
            ++pos_;
            advance_to_busy();
            return *this;
        }
        bool operator==(const Iterator &other) const
        {
            return ht_ == other.ht_ && pos_ == other.pos_;
        }
        bool operator!=(const Iterator &other) const
        {
            return !(*this == other);
        }
        std::size_t index() const { return pos_; }
        const K &key() const { return ht_->table_[pos_].key; }

    private:
        HashTable *ht_{nullptr};
        std::size_t pos_{0};
        void advance_to_busy()
        {
            if (!ht_)
                return;
            while (pos_ < ht_->m_ && ht_->table_[pos_].state != State::BUSY)
            {
                ++pos_;
            }
        }
    };

    explicit HashTable(std::size_t n_max)
    {
        // Для open addressing α=0.5 => m >= 2*n_max
        // Берём ближайшее простое сверху для стабильности зондирования.
        m_ = next_prime(std::max<std::size_t>(5, 2 * n_max));
        table_.assign(m_, Cell{});
        n_ = 0;
        last_hash_ = 0;
        last_probes_ = 0;
    }

    std::size_t Size() const { return n_; }
    std::size_t Capacity() const { return m_; }
    bool Empty() const { return n_ == 0; }
    void Clear()
    {
        for (auto &c : table_)
            c.state = State::FREE;
        n_ = 0;
        last_hash_ = 0;
        last_probes_ = 0;
    }

    bool Insert(const K &key, const V &value)
    {
        reset_last_stats();
        if ((n_ + 1) * 2 > m_)
        {
            last_probes_ = 0;
            return false;
        }
        bool found = false;
        std::size_t idx = find_slot(key, true, found);
        if (idx == npos)
            return false;
        if (found)
        {
            table_[idx].value = value;
            return false;
        }
        table_[idx].key = key;
        table_[idx].value = value;
        table_[idx].state = State::BUSY;
        ++n_;
        return true;
    }

    V *Find(const K &key)
    {
        reset_last_stats();
        bool found = false;
        std::size_t idx = find_slot(key, false, found);
        if (idx == npos || !found)
            return nullptr;
        return &table_[idx].value;
    }

    bool Erase(const K &key)
    {
        reset_last_stats();
        bool found = false;
        std::size_t idx = find_slot(key, false, found);
        if (idx == npos || !found)
            return false;
        table_[idx].state = State::DELETED;
        --n_;
        return true;
    }

    void Print(std::ostream &out) const
    {
        for (std::size_t i = 0; i < m_; ++i)
        {
            out << std::left << std::setw(8) << i;
            if (table_[i].state == State::BUSY)
            {
                out << std::setw(16) << table_[i].value;
            }
            else
            {
                out << std::setw(16) << "";
            }
            if (table_[i].state == State::FREE)
            {
                out << "f";
            }
            else if (table_[i].state == State::DELETED)
            {
                out << "d";
            }
            else
            {
                out << "b";
            }
            out << "\n";
        }
    }
    std::size_t LastHash() const { return last_hash_; }
    std::size_t LastProbes() const { return last_probes_; }
    Iterator Begin() { return Iterator(this, 0); }
    Iterator End() { return Iterator(this, m_); }
    std::size_t HashIndexOnly(const K &key) const
    {
        std::size_t h0 = static_cast<std::size_t>(fold_key(key) % m_);
        return h0;
    }

private:
    static constexpr std::size_t npos = std::numeric_limits<std::size_t>::max();
    std::vector<Cell> table_;
    std::size_t m_{0};
    std::size_t n_{0};
    std::size_t last_hash_{0};
    std::size_t last_probes_{0};
    void reset_last_stats()
    {
        last_hash_ = 0;
        last_probes_ = 0;
    }
    static std::uint64_t fold_key(std::uint64_t k)
    {
        std::uint64_t sum = 0;
        while (k > 0)
        {
            sum += (k % 1000ULL);
            k /= 1000ULL;
        }
        return sum;
    }
    // Квадратичное зондирование: (h + i + i^2) mod m
    std::size_t probe(std::size_t h, std::size_t i) const
    {
        // i + i^2 может переполниться при огромных i, но i <= m в нашем проходе.
        std::size_t offset = i + i * i;
        return (h + offset) % m_;
    }
    // - false: ищем только ключ, останавливаемся на FREE (значит "не найдено").
    // - true : ищем место вставки (первый DELETED можно использовать, но если ключ встретили — это "found").
    std::size_t find_slot(const K &key, bool for_insert, bool &found)
    {
        found = false;
        // ключ натуральный => ожидаем uint64_t
        static_assert(std::is_same<K, std::uint64_t>::value,
                      "Для варианта 7 ожидается K = uint64_t.");
        std::size_t h0 = static_cast<std::size_t>(fold_key(key) % m_);
        last_hash_ = h0;
        std::size_t first_deleted = npos;
        for (std::size_t i = 0; i < m_; ++i)
        {
            ++last_probes_;
            std::size_t idx = probe(h0, i);
            const auto st = table_[idx].state;
            if (st == State::BUSY)
            {
                if (table_[idx].key == key)
                {
                    found = true;
                    return idx;
                }
                continue;
            }
            if (st == State::DELETED)
            {
                if (for_insert && first_deleted == npos)
                    first_deleted = idx;
                continue;
            }
            // FREE
            if (!for_insert)
            {
                // "не найдено" (found=false)
                return idx;
            }
            // вставка: если был DELETED — используем его, иначе этот FREE
            return (first_deleted != npos) ? first_deleted : idx;
        }
        if (for_insert && first_deleted != npos)
            return first_deleted;
        return npos;
    }
};

static double chi_square_for_capacity(std::size_t m,
                                      std::size_t N,
                                      int trials,
                                      std::uint64_t key_min = 1'000'000'000ULL,
                                      std::uint64_t key_max = 3'000'000'000ULL)
{
    std::mt19937_64 rng(std::random_device{}());
    std::uniform_int_distribution<std::uint64_t> dist(key_min, key_max);
    double sum = 0.0;
    for (int t = 1; t <= trials; ++t)
    {
        std::vector<std::size_t> count(m, 0);
        // Используем ту же формулу индекса, что и в таблице: fold(key)%m
        for (std::size_t i = 0; i < N; ++i)
        {
            std::uint64_t k = dist(rng);
            std::uint64_t kk = 0;
            std::uint64_t tmp = k;
            while (tmp > 0)
            {
                kk += (tmp % 1000ULL);
                tmp /= 1000ULL;
            }
            std::size_t j = static_cast<std::size_t>(kk % m);
            count[j]++;
        }
        const double E = static_cast<double>(N) / static_cast<double>(m);
        double chi2 = 0.0;
        for (std::size_t j = 0; j < m; ++j)
        {
            double diff = static_cast<double>(count[j]) - E;
            chi2 += (diff * diff) / E;
        }
        std::cout << "Trial " << t << ": chi^2 = " << chi2 << "\n";
        sum += chi2;
    }
    double avg = sum / static_cast<double>(trials);
    std::cout << "Average chi^2 over " << trials << " trials: " << avg << "\n";
    return avg;
}

#endif
