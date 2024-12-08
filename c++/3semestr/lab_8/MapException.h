#ifndef MAPEXCEPTION_H
#define MAPEXCEPTION_H

#include <exception>

/**
 * @brief Класс пользовательского исключения для ошибок при операциях с multimap.
 *
 * Этот класс наследуется от std::exception и используется для обработки конкретных ошибок,
 * возникающих при операциях с multimap.
 */
class MapException : public std::exception {
public:
    /**
     * @brief Возвращает C-style строку, описывающую ошибку.
     *
     * Эта функция предоставляет описание ошибки в виде постоянной C-style строки.
     * @return const char* Константная строка, описывающая природу ошибки.
     */
    const char *what() const noexcept override {
        return "error_during_multimap_operation";
    }
};

#endif // MAPEXCEPTION_H
