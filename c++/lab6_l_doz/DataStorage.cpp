#include "DataStorage.h"
#include <stdexcept>

// Конструктор класса DataStorage
DataStorage::DataStorage(std::string manufacturer, std::string model, std::string serialNumber, std::string type,
                         int capacity)
    : manufacturer(std::move(manufacturer)), model(std::move(model)), serialNumber(std::move(serialNumber)),
      type(std::move(type)), capacity(capacity), partitionTableType("None") {
    if (capacity <= 0) {
        throw std::invalid_argument("The volume must be greater than 0.");
    }
}

// Деструктор класса DataStorage
DataStorage::~DataStorage() = default;

// Получение производителя
std::string DataStorage::getManufacturer() const { return manufacturer; }

// Получение модели
std::string DataStorage::getModel() const { return model; }

// Получение серийного номера
std::string DataStorage::getSerialNumber() const { return serialNumber; }

// Получение типа накопителя
std::string DataStorage::getType() const { return type; }

// Получение емкости накопителя
int DataStorage::getCapacity() const { return capacity; }

// Получение типа таблицы разделов
std::string DataStorage::getPartitionTableType() const { return partitionTableType; }

// Получение количества разделов
int DataStorage::getPartitionCount() const { return partitions.size(); }

// Получение общего объема занятых разделами данных
int DataStorage::getPartitionTotalSize() const {
    int totalSize = 0;
    for (const auto &partition: partitions) {
        totalSize += partition.getOccupiedSpace();
    }
    return totalSize;
}

// Получение свободного места на накопителе
int DataStorage::getFreeSpace() const {
    int usedSpace = getPartitionTotalSize();
    return capacity - usedSpace;
}

// Создание таблицы разделов
void DataStorage::createPartitionTable(const std::string &type) {
    if (type != "GPT" && type != "MBR") {
        throw std::invalid_argument("Invalid partition table type.");
    }
    partitionTableType = type;
    partitions.clear();
}

// Проверка наличия таблицы разделов
bool DataStorage::hasPartitionTable() const { return partitionTableType != "None"; }

// Добавление раздела
void DataStorage::addPartition(int startByte, int endByte, const std::string &name, const std::string &fileSystem,
                               int occupiedSpace) {
    if (startByte < 0 || endByte >= capacity || startByte >= endByte) {
        throw std::invalid_argument("Invalid start or end byte.");
    }
    if (isOverlap(startByte, endByte)) {
        throw std::invalid_argument("Partition overlaps with existing partitions.");
    }
    partitions.emplace_back(startByte, endByte, name, fileSystem, occupiedSpace);
}

// Удаление раздела
void DataStorage::removePartition(int index) {
    if (index < 0 || index >= partitions.size()) {
        throw std::invalid_argument("Invalid partition index.");
    }
    partitions.erase(partitions.begin() + index);
}

// Получение раздела по индексу
Partition DataStorage::getPartition(int index) const {
    if (index < 0 || index >= partitions.size()) {
        throw std::invalid_argument("Invalid partition index.");
    }
    return partitions[index];
}

// Проверка на пересечение разделов
bool DataStorage::isOverlap(int startByte, int endByte) const {
    for (const auto &partition: partitions) {
        if ((startByte >= partition.getStartByte() && startByte <= partition.getEndByte()) ||
            (endByte >= partition.getStartByte() && endByte <= partition.getEndByte())) {
            return true;
        }
    }
    return false;
}
