#include <iostream>
#include "CircularLinkedList.h"
#include "Dog.h"
#include "Cat.h"

void runTask() {
    try {
        CircularLinkedList list;

        // Добавление животных в список
        list.addToEnd(new Dog("Rex"));
        list.addToEnd(new Cat("Whiskers"));
        list.addToEnd(new Dog("Buddy"));
        list.addToEnd(new Cat("Mittens"));

        std::cout << "Displaying all animals in the list:" << std::endl;
        list.displayAll();

        const char *searchName = "Buddy";
        Animal *foundAnimal = list.findByName(searchName);

        if (foundAnimal) {
            std::cout << "\nFound animal with name '" << searchName << "':" << std::endl;
            foundAnimal->display();
        } else {
            std::cout << "\nAnimal with name '" << searchName << "' not found." << std::endl;
        }

        // Удаление по индексу
        list.removeAt(1);
        std::cout << "\nAfter removing second animal:" << std::endl;
        list.displayAll();

        // Вставка по индексу
        list.insertAt(1, new Dog("Max"));
        std::cout << "\nAfter inserting Max at index 1:" << std::endl;
        list.displayAll();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
