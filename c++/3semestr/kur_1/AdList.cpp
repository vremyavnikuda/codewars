#include "AdList.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <chrono>

// Конструктор
AdList::AdList() : head(nullptr), tail(nullptr), count(0) {
}

// Деструктор
AdList::~AdList() {
    if (head == nullptr) {
        return;
    }
    AdStruct *current = head;
    do {
        AdStruct *temp = current;
        current = current->next;
        delete temp;
    } while (current != head);

    head = nullptr;
    tail = nullptr;
    count = 0;
}

// Добавление объявления в конец списка
void AdList::addAd(const char *cat, const char *rub, const char *txt, const char *dat, const char *phn) {
    AdStruct *newAd = new AdStruct(cat, rub, txt, dat, phn);

    if (head == nullptr) {
        head = newAd;
        tail = newAd;
        newAd->next = newAd;
        newAd->prev = newAd;
    } else {
        tail->next = newAd;
        newAd->prev = tail;
        newAd->next = head;
        head->prev = newAd;
        tail = newAd;
    }
    count++;
}

// Удаление объявления по логическому номеру
void AdList::deleteAd(int logicalNum) {
    if (logicalNum < 1 || logicalNum > count) {
        std::cout << "invalidLogicalNumber" << std::endl;
        return;
    }

    AdStruct *current = head;
    for (int i = 1; i < logicalNum; i++) {
        current = current->next;
    }

    if (count == 1) {
        delete current;
        head = nullptr;
        tail = nullptr;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        if (current == head) {
            head = current->next;
        }
        if (current == tail) {
            tail = current->prev;
        }
        delete current;
    }
    count--;
}

// Сортировка объявлений по дате
// Реализовано отображение времени выполнения операции (по условию задания №6)
void AdList::sortAds() {
    if (count <= 1) {
        return; // Если список пуст или содержит одно объявление, сортировка не нужна
    }

    // Засекаем начальное время
    auto start = std::chrono::high_resolution_clock::now();

    bool swapped;
    do {
        swapped = false;
        AdStruct *current = head;
        do {
            AdStruct *nextAd = current->next;
            if (strcmp(current->date, nextAd->date) > 0) {
                // Сравниваем даты строками
                current->swapData(*nextAd); // Меняем данные местами
                swapped = true;
            }
            current = current->next;
        } while (current != head);
    } while (swapped);

    // Засекаем конечное время
    auto end = std::chrono::high_resolution_clock::now();

    // Вычисляем длительность в микросекундах
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Выводим длительность выполнения
    std::cout << "Sorting took " << duration.count() << " microseconds." << std::endl;
}


// Поиск объявлений по рубрике
void AdList::searchByRubric(const char *rubric) {
    AdStruct *current = head;
    do {
        if (strcmp(current->rubric, rubric) == 0) {
            current->display();
        }
        current = current->next;
    } while (current != head);
}

// Поиск объявлений по ключевому слову в тексте
void AdList::searchByKeyword(const char *keyword) {
    AdStruct *current = head;
    do {
        if (strstr(current->text, keyword) != nullptr) {
            current->display();
        }
        current = current->next;
    } while (current != head);
}

// Сохранение списка в двоичный файл
void AdList::saveToFile(const char *filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        throw std::ios_base::failure("errorOpeningFileForWriting");
    }
    outFile.write(reinterpret_cast<char *>(&count), sizeof(int));
    AdStruct *current = head;
    do {
        int catLen = strlen(current->category) + 1;
        outFile.write(reinterpret_cast<char *>(&catLen), sizeof(int));
        outFile.write(current->category, catLen);

        int rubLen = strlen(current->rubric) + 1;
        outFile.write(reinterpret_cast<char *>(&rubLen), sizeof(int));
        outFile.write(current->rubric, rubLen);

        int txtLen = strlen(current->text) + 1;
        outFile.write(reinterpret_cast<char *>(&txtLen), sizeof(int));
        outFile.write(current->text, txtLen);

        int datLen = strlen(current->date) + 1;
        outFile.write(reinterpret_cast<char *>(&datLen), sizeof(int));
        outFile.write(current->date, datLen);

        int phnLen = strlen(current->phone) + 1;
        outFile.write(reinterpret_cast<char *>(&phnLen), sizeof(int));
        outFile.write(current->phone, phnLen);

        current = current->next;
    } while (current != head);
    outFile.close();
}

// Загрузка списка из двоичного файла
void AdList::loadFromFile(const char *filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        throw std::ios_base::failure("Failed to open file for reading");
    }

    int loadedCount = 0;
    inFile.read(reinterpret_cast<char *>(&loadedCount), sizeof(int));

    for (int i = 0; i < loadedCount; i++) {
        try {
            int catLen, rubLen, txtLen, datLen, phnLen;
            inFile.read(reinterpret_cast<char *>(&catLen), sizeof(int));
            char *category = new char[catLen];
            inFile.read(category, catLen);

            inFile.read(reinterpret_cast<char *>(&rubLen), sizeof(int));
            char *rubric = new char[rubLen];
            inFile.read(rubric, rubLen);

            inFile.read(reinterpret_cast<char *>(&txtLen), sizeof(int));
            char *text = new char[txtLen];
            inFile.read(text, txtLen);

            inFile.read(reinterpret_cast<char *>(&datLen), sizeof(int));
            char *date = new char[datLen];
            inFile.read(date, datLen);

            inFile.read(reinterpret_cast<char *>(&phnLen), sizeof(int));
            char *phone = new char[phnLen];
            inFile.read(phone, phnLen);

            addAd(category, rubric, text, date, phone);

            delete[] category;
            delete[] rubric;
            delete[] text;
            delete[] date;
            delete[] phone;
        } catch (...) {
            while (head != nullptr) {
                AdStruct *temp = head->next;
                delete head;
                if (temp == head) break;
                head = temp;
            }
            throw;
        }
    }
    inFile.close();
}


// Отображение всех объявлений
void AdList::displayAll() const {
    AdStruct *current = head;
    if (current == nullptr) {
        return;
    }
    do {
        current->display();
        current = current->next;
    } while (current != head);
}

// Проверка, является ли строка датой в формате YYYY-MM-DD
bool AdList::isValidDate(const char *date) {
    // Проверяем длину строки
    if (strlen(date) != 10) {
        return false;
    }

    // Проверяем формат YYYY-MM-DD
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (date[i] != '-') {
                return false; // Должны быть разделители '-'
            }
        } else {
            if (!isdigit(date[i])) {
                return false; // Остальные символы должны быть цифрами
            }
        }
    }

    // Извлекаем год, месяц и день
    int year = atoi(date);
    int month = atoi(date + 5);
    int day = atoi(date + 8);

    // Проверяем диапазоны
    if (year < 1900 || year > 2100) {
        return false;
    }
    if (month < 1 || month > 12) {
        return false;
    }

    // Проверяем количество дней в месяце
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Проверка високосного года
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29; // В феврале 29 дней
    }

    if (day < 1 || day > daysInMonth[month - 1]) {
        return false;
    }

    return true;
}
