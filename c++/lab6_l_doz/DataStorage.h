#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H

#include <string>
#include <vector>
#include "Partition.h"

class DataStorage {
private:
    std::string manufacturer;
    std::string model;
    std::string serialNumber;
    std::string type;
    int capacity;
    std::string partitionTableType;
    std::vector<Partition> partitions;

    bool isOverlap(int startByte, int endByte) const;

public:
    DataStorage(std::string manufacturer, std::string model, std::string serialNumber, std::string type, int capacity);

    ~DataStorage();

    std::string getManufacturer() const;

    std::string getModel() const;

    std::string getSerialNumber() const;

    std::string getType() const;

    int getCapacity() const;

    std::string getPartitionTableType() const;

    int getPartitionCount() const;

    int getPartitionTotalSize() const;

    int getFreeSpace() const;

    void createPartitionTable(const std::string &type);

    bool hasPartitionTable() const;

    void addPartition(int startByte, int endByte, const std::string &name = "", const std::string &fileSystem = "",
                      int occupiedSpace = 0);

    void removePartition(int index);

    Partition getPartition(int index) const;
};

#endif // DATA_STORAGE_H
