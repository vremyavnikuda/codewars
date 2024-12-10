#ifndef ADLIST_H
#define ADLIST_H

#include "AdStruct.h"
#include <chrono>

class AdList {
private:
    AdStruct *head;
    AdStruct *tail;
    int count;

public:
    // Конструктор
    AdList();

    // Деструктор
    ~AdList();

    // Добавление объявления в конец списка
    void addAd(const char *cat, const char *rub, const char *txt, const char *dat, const char *phn);

    // Удаление объявления по логическому номеру
    void deleteAd(int logicalNum);

    // Сортировка объявлений по дате
    void sortAds();

    // Поиск объявлений по рубрике
    void searchByRubric(const char *rubric);

    // Поиск объявлений по ключевому слову в тексте
    void searchByKeyword(const char *keyword);

    // Сохранение списка в двоичный файл
    void saveToFile(const char *filename);

    // Загрузка списка из двоичного файла
    void loadFromFile(const char *filename);

    // Отображение всех объявлений
    void displayAll() const;

    // Проверка, является ли строка датой в формате YYYY-MM-DD
    static bool isValidDate(const char *date);
};

#endif // ADLIST_H
