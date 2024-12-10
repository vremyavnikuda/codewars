#ifndef ADSTRUCT_H
#define ADSTRUCT_H

#include <cstring>
#include <new>

class AdList;

class AdStruct {
private:
    char *category;
    char *rubric;
    char *text;
    char *date;
    char *phone;
    friend class AdList;

public:
    AdStruct *next;
    AdStruct *prev;

    // Конструктор
    AdStruct(const char *cat, const char *rub, const char *txt, const char *dat, const char *phn);

    // Деструктор
    ~AdStruct();

    // Копирующий конструктор
    AdStruct(const AdStruct &other);

    // Оператор присваивания
    AdStruct &operator=(const AdStruct &other);

    // Отображение содержимого объявления
    void display() const;

    // Обмен данными с другим AdStruct
    void swapData(AdStruct &other);
};

#endif // ADSTRUCT_H
