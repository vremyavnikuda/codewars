#include <exception>

// Исключение для ошибок выделения памяти
class MemoryException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Memory allocation failed!";
    }
};

// Исключение для ошибок выхода за пределы диапазона
class IndexOutOfRangeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Index is out of range!";
    }
};
