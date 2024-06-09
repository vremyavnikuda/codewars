//
// Created by vremyavnikuda on 08.06.2024.
//
#include "Partition.h"
#include <stdexcept>

// Конструктор класса Partition
Partition::Partition(int startByte, int endByte, std::string name, std::string fileSystem, int occupiedSpace)
    : startByte(startByte), endByte(endByte), name(std::move(name)), fileSystem(std::move(fileSystem)),
      occupiedSpace(occupiedSpace) {
    if (startByte < 0 || endByte <= startByte) {
        throw std::invalid_argument("Invalid start or end byte.");
    }
    if (occupiedSpace < 0 || occupiedSpace > getSize()) {
        throw std::invalid_argument("Invalid occupied space.");
    }
}

// Получение размера раздела
int Partition::getSize() const {
    return endByte - startByte + 1;
}

// Получение начального байта раздела
int Partition::getStartByte() const {
    return startByte;
}

// Получение конечного байта раздела
int Partition::getEndByte() const {
    return endByte;
}

// Получение имени раздела
std::string Partition::getName() const {
    return name;
}

// Установка имени раздела
void Partition::setName(const std::string &newName) {
    name = newName;
}

// Получение файловой системы раздела
std::string Partition::getFileSystem() const {
    return fileSystem;
}

// Установка файловой системы раздела
void Partition::setFileSystem(const std::string &newFileSystem) {
    fileSystem = newFileSystem;
    occupiedSpace = 0;
}

// Получение занятого пространства раздела
int Partition::getOccupiedSpace() const {
    return occupiedSpace;
}

// Установка занятого пространства раздела
void Partition::setOccupiedSpace(int newOccupiedSpace) {
    if (newOccupiedSpace < 0 || newOccupiedSpace > getSize()) {
        throw std::invalid_argument("Invalid occupied space.");
    }
    occupiedSpace = newOccupiedSpace;
}
