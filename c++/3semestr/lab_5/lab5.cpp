//
// Created by vremyavnikuda on 05.12.2024.
//
#include <iostream>
#include <cstring>

// Animal
class Animal {
protected:
    char *name;

public:
    Animal(const char *n) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }

    virtual ~Animal() {
        delete[] name;
    }

    // display()
    virtual void display() const {
        std::cout << "Animal Name: " << name << std::endl;
    }

    const char* getName() const {
        return name;
    }
};

// Dog <- Animal
class Dog : public Animal {
public:
    Dog(const char *n) : Animal(n) {}

    void display() const override {
        std::cout << "Dog Name: " << name << std::endl;
    }
};

// Cat <- Animal
class Cat : public Animal {
public:
    Cat(const char *n) : Animal(n) {}

    void display() const override {
        std::cout << "Cat Name: " << name << std::endl;
    }
};

// Структура элемента списка
struct Node {
    Animal *data;
    Node *next;
};

// Цикличный односвязный список
class CircularLinkedList {
private:
    Node *head;

public:
    CircularLinkedList() : head(nullptr) {}

    ~CircularLinkedList() {
        if (head) {
            Node *current = head;
            do {
                Node *temp = current;
                current = current->next;
                delete temp->data;
                delete temp;
            } while (current-> next != head);
        }
    }

    // @addToEnd()
    // Метод для добавления элемента в конец списка
    void addToEnd(Animal *animal) {
        Node *newNode = new Node{animal, nullptr};
        if (!head) {
            head = newNode;
            newNode->next = head;
        } else {
            Node *current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = newNode;
            newNode->next = head;
        }
    }

    // @insertAt()
    // Метод для добавления элемента по номеру
    void insertAt(int index, Animal *animal) {
        if (index < 0) return;
        Node *newNode = new Node{animal, nullptr};
        if (index == 0) {
            if (!head) {
                head = newNode;
                newNode->next = head;
            } else {
                Node *current = head;
                while (current->next != head) {
                    current = current->next;
                }
                current->next = newNode;
                newNode->next = head;
                head = newNode;
            }
            return;
        }

        Node *current = head;
        for (int i = 0; i < index - 1; ++i) {
            if (current->next == head) break;
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    // @removeAt()
    // Метод для удаления элемента по номеру
    void removeAt(int index) {
        if (index < 0 || !head) return;
        if (index == 0) {
            if (head->next == head) {
                delete head->data;
                delete head;
                head = nullptr;
            } else {
                Node *current = head;
                while (current->next != head) {
                    current = current->next;
                }
                Node *temp = head;
                current->next = head->next;
                head = head->next;
                delete temp->data;
                delete temp;
            }
            return;
        }

        Node *current = head;
        for (int i = 0; i < index - 1; ++i) {
            if (current->next == head) return;
            current = current->next;
        }

        Node *temp = current->next;
        current->next = temp->next;
        delete temp->data;
        delete temp;
    }

    // @findByName()
    // Метод для поиска элемента по имени
    Animal* findByName(const char *name) {
        if (!head) return nullptr;
        Node *current = head;
        do {
            if (strcmp(current->data->getName(), name) == 0) {
                return current->data;
            }
            current = current->next;
        } while (current != head);

        return nullptr;
    }

    // @displayAll()
    // Метод для отображения всех элементов списка
    void displayAll() const {
        if (!head) {
            std::cout << "The list is empty." << std::endl;
            return;
        }
        Node *current = head;
        do {
            current->data->display();
            current = current->next;
        } while (current != head);
    }
};

// @startTask
void startTask() {
    CircularLinkedList list;

    // Добавление объектов разных классов
    list.addToEnd(new Dog("Rex"));
    list.addToEnd(new Cat("Whiskers"));
    list.addToEnd(new Dog("Buddy"));
    list.addToEnd(new Cat("Mittens"));

    std::cout << "Displaying all animals in the list:" << std::endl;
    list.displayAll();

    // Поиск по имени
    const char *searchName = "Buddy";
    Animal *foundAnimal = list.findByName(searchName);
    if (foundAnimal) {
        std::cout << "\nFound animal with name '" << searchName << "':" << std::endl;
        foundAnimal->display();
    } else {
        std::cout << "\nAnimal with name '" << searchName << "' not found." << std::endl;
    }

    // Удаление элемента
    // Удаляем второй элемент
    list.removeAt(1);
    std::cout << "\nAfter removing second animal:" << std::endl;
    list.displayAll();

    // Вставка по индексу
    list.insertAt(1, new Dog("Max"));
    std::cout << "\nAfter inserting Max at index 1:" << std::endl;
    list.displayAll();
}

// main функция
int main() {
    startTask();
    return 0;
}