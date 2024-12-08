#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

// Исключение для ошибок выделения памяти
class MemoryException : public std::exception {
public:
    const char* what() const noexcept override {
        return "memoryAllocationFailed";
    }
};

// Исключение для ошибок выхода за пределы диапазона
class IndexOutOfRangeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "indexOutOfRange";
    }
};

#endif // EXCEPTIONS_H
