#include <iostream>

#include "CircularLinkedList.h"
#include "Dog.h"
#include "Cat.h"

void runTask() {
    // Создаем экземпляр циклического связного списка
    CircularLinkedList list;

    // Добавляем собаку с именем "Rex" в конец списка
    list.addToEnd(new Dog("Rex"));
    // Добавляем кошку с именем "Whiskers" в конец списка
    list.addToEnd(new Cat("Whiskers"));
    // Добавляем собаку с именем "Buddy" в конец списка
    list.addToEnd(new Dog("Buddy"));
    // Добавляем кошку с именем "Mittens" в конец списка
    list.addToEnd(new Cat("Mittens"));

    // Выводим сообщение о выводе всех животных
    std::cout << "Displaying all animals in the list:" << std::endl;
    // Выводим все животные в списке
    list.displayAll();

    // Устанавливаем имя для поиска
    const char *searchName = "Buddy";

    // Ищем с заданным именем
    Animal *foundAnimal = list.findByName(searchName);

    if (foundAnimal) {
        // Если найден
        // Выводим сообщение
        std::cout << "\nFound animal with name '" << searchName << "':" << std::endl;
        // Выводим информацию
        foundAnimal->display();
    } else {
        // Если не найден
        // Выводим сообщение
        std::cout << "\nAnimal with name '" << searchName << "' not found." << std::endl;
    }

    // Удаляем с индексом 1 из списка
    list.removeAt(1);
    // Выводим сообщение после удаления
    std::cout << "\nAfter removing second animal:" << std::endl;
    // Выводим список после удаления
    list.displayAll();

    // Вставляем собаку с именем "Max" на позицию 1 в списке
    list.insertAt(1, new Dog("Max"));
    // Выводим сообщение после вставки
    std::cout << "\nAfter inserting Max at index 1:" << std::endl;
    // Выводим список после вставки
    list.displayAll();
}
