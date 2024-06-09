//
// Created by vremyavnikuda on 08.06.2024.
//
#ifndef PARTITION_H
#define PARTITION_H

#include <string>

class Partition {
private:
    std::string name;
    int startByte;
    int endByte;
    std::string fileSystem;
    int occupiedSpace;

public:
    Partition(int startByte, int endByte, std::string name = "", std::string fileSystem = "", int occupiedSpace = 0);

    int getSize() const;
    int getStartByte() const;
    int getEndByte() const;
    std::string getName() const;
    void setName(const std::string& newName);
    std::string getFileSystem() const;
    void setFileSystem(const std::string& newFileSystem);
    int getOccupiedSpace() const;
    void setOccupiedSpace(int newOccupiedSpace);
};

#endif // PARTITION_H
