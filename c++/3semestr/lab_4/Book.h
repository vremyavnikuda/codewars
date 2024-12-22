#ifndef BOOK_H
#define BOOK_H

#include <iostream>

class Book {
protected:
  // Название книги
  char *title;
  // Количество страниц
  int pages;
  // Тираж
  int circulation;

  // Функция для безопасного копирования C-строк
  char *copyString(const char *str);

public:
  // Конструктор по умолчанию
  Book();

  // Конструктор инициализации книги
  Book(const char *t, int p, int c);

  // Конструктор копирования
  Book(const Book &other);

  // Виртуальный деструктор для правильного удаления при наследовании
  virtual ~Book();

  // Оператор присваивания
  Book &operator=(const Book &other);

  // Оператор сложения для объединения двух книг
  Book operator+(const Book &other) const;

  // Дружественная функция для вычитания книг
  friend Book operator-(const Book &lhs, const Book &rhs);

  // Префиксный инкремент
  Book &operator++();

  // Постфиксный инкремент
  Book operator++(int);

  // Оператор преобразования в int
  operator int() const;

  // Устанавливает данные книги
  void setBook(const char *title, int pages, int circulation);

  // Выводит информацию о книге
  virtual void display() const;

  // Перегрузка оператора << для вывода
  friend std::ostream &operator<<(std::ostream &os, const Book &book);

  // Перегрузка оператора >> для ввода
  friend std::istream &operator>>(std::istream &is, Book &book);

  // Сохраняет данные книги в двоичный файл
  virtual void saveToBinaryFile(const char *filename) const;

  // Загружает данные книги из двоичного файла
  virtual void loadFromBinaryFile(const char *filename);

  // Сохраняет данные книги в текстовый файл
  virtual void saveToTextFile(const char *filename) const;
};

#endif // BOOK_H
