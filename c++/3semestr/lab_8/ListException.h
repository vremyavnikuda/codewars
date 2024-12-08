#ifndef LISTEXCEPTION_H
#define LISTEXCEPTION_H

#include <exception>

/**
 * @brief Пользовательский класс исключений для ошибок во время операций со списком.
 */
class ListException : public std::exception {
public:
    /**
     * @brief Возвращает строку в стиле C, описывающую ошибку.
     * @return const char*, описывающий ошибку.
     */
    const char *what() const noexcept override {
        return "error_during_list_operation";
    }
};

#endif // LISTEXCEPTION_H
