#include "AdStruct.h"
#include <cstring>
#include <iostream>

// Конструктор
AdStruct::AdStruct(const char *cat, const char *rub, const char *txt, const char *dat, const char *phn) {
    category = new char[strlen(cat) + 1];
    if (!category) throw std::bad_alloc();
    strcpy(category, cat);

    rubric = new char[strlen(rub) + 1];
    if (!rubric) throw std::bad_alloc();
    strcpy(rubric, rub);

    text = new char[strlen(txt) + 1];
    if (!text) throw std::bad_alloc();
    strcpy(text, txt);

    date = new char[strlen(dat) + 1];
    if (!date) throw std::bad_alloc();
    strcpy(date, dat);

    phone = new char[strlen(phn) + 1];
    if (!phone) throw std::bad_alloc();
    strcpy(phone, phn);

    next = nullptr;
    prev = nullptr;
}


// Деструктор
AdStruct::~AdStruct() {
    delete[] category;
    delete[] rubric;
    delete[] text;
    delete[] date;
    delete[] phone;
}

// Копирующий конструктор
AdStruct::AdStruct(const AdStruct &other) {
    category = new char[strlen(other.category) + 1];
    strcpy(category, other.category);

    rubric = new char[strlen(other.rubric) + 1];
    strcpy(rubric, other.rubric);

    text = new char[strlen(other.text) + 1];
    strcpy(text, other.text);

    date = new char[strlen(other.date) + 1];
    strcpy(date, other.date);

    phone = new char[strlen(other.phone) + 1];
    strcpy(phone, other.phone);

    next = nullptr;
    prev = nullptr;
}

// Оператор присваивания
AdStruct &AdStruct::operator=(const AdStruct &other) {
    if (this != &other) {
        delete[] category;
        delete[] rubric;
        delete[] text;
        delete[] date;
        delete[] phone;

        category = new char[strlen(other.category) + 1];
        strcpy(category, other.category);

        rubric = new char[strlen(other.rubric) + 1];
        strcpy(rubric, other.rubric);

        text = new char[strlen(other.text) + 1];
        strcpy(text, other.text);

        date = new char[strlen(other.date) + 1];
        strcpy(date, other.date);

        phone = new char[strlen(other.phone) + 1];
        strcpy(phone, other.phone);

        next = nullptr;
        prev = nullptr;
    }
    return *this;
}

// Отображение содержимого объявления
void AdStruct::display() const {
    std::cout << "Category: " << category << std::endl;
    std::cout << "Rubric: " << rubric << std::endl;
    std::cout << "Text: " << text << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "Phone: " << phone << std::endl;
    std::cout << "------------------------" << std::endl;
}

// Обмен данными с другим AdStruct
void AdStruct::swapData(AdStruct &other) {
    std::swap(category, other.category);
    std::swap(rubric, other.rubric);
    std::swap(text, other.text);
    std::swap(date, other.date);
    std::swap(phone, other.phone);
}
