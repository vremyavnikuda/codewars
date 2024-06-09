#include <iostream>
#include "DataStorage.h"
#include "Partition.h"
/*

Код моделирует работу с накопителем данных (жесткий диск) и его разделами (partition). Программа включает два основных класса: DataStorage и Partition, а также функцию main, которая демонстрирует их использование.

Класс Partition
Класс Partition представляет собой раздел накопителя. В нем хранятся данные о начальном и конечном байтах раздела, его имени, файловой системе и занятом пространстве. В классе реализованы методы для получения и изменения этих данных.

Класс DataStorage
Класс DataStorage представляет собой накопитель данных. В нем хранятся информация о производителе, модели, серийном номере, типе, емкости и типе таблицы разделов. Класс также включает методы для работы с разделами, такие как создание таблицы разделов, добавление и удаление разделов, проверка на пересечение разделов и получение информации о разделах.

Функция main
Функция main демонстрирует создание объекта DataStorage, создание таблицы разделов, добавление разделов и вывод информации о накопителе и его разделах.

Вывод информации о разделах
* Partition -> Раздел
* Name -> Имя
* Start byte -> Стартовый байт
* End byte -> Конечный байт
* File system -> Файловая система
* Occupied space -> Занимаемая площадь

*/

int main() {
    try {
        // Создаем объект DataStorage с заданными параметрами
        DataStorage ds1("Seagate", "Barracuda", "SN123456", "HDD", 1000);

        // Создаем таблицу разделов типа GPT
        ds1.createPartitionTable("GPT");

        // Добавляем два раздела
        ds1.addPartition(0, 299, "System", "NTFS", 200);
        ds1.addPartition(300, 799, "Data", "FAT32", 400);

        /**
        * Manufacturer -> Производитель
        * Model-> Модель
        * Serial number -> Серийный номер
        * Type -> Тип
        * Volume -> Объем
        * Number of sections -> Количество секций
        * Total volume of partitions -> Общий объем разделов
        * Partition table type -> Тип таблицы разделов
        * Free space -> Свободное пространство
        * Is there a partition table -> Есть ли таблица разделов (Да,Нет)
        */

        // Выводим информацию о накопителе и его разделах
        std::cout << "Manufacturer: " << ds1.getManufacturer() << std::endl;
        std::cout << "Model: " << ds1.getModel() << std::endl;
        std::cout << "Serial number: " << ds1.getSerialNumber() << std::endl;
        std::cout << "Type: " << ds1.getType() << std::endl;
        std::cout << "Volume: " << ds1.getCapacity() << std::endl;
        std::cout << "Partition table type: " << ds1.getPartitionTableType() << std::endl;
        std::cout << "Number of sections: " << ds1.getPartitionCount() << std::endl;
        std::cout << "Total volume of partitions: " << ds1.getPartitionTotalSize() << std::endl;
        std::cout << "Free space: " << ds1.getFreeSpace() << std::endl;
        std::cout << "Is there a partition table: " << (ds1.hasPartitionTable() ? "Yes" : "No") << std::endl;

        // Выводим информацию о каждом разделе
        for (int i = 0; i < ds1.getPartitionCount(); ++i) {
            Partition part = ds1.getPartition(i);
            std::cout << "Partition " << i + 1 << ": " << std::endl;
            std::cout << "    Name: " << part.getName() << std::endl;
            std::cout << "    Start byte: " << part.getStartByte() << std::endl;
            std::cout << "    End byte: " << part.getEndByte() << std::endl;
            std::cout << "    File system: " << part.getFileSystem() << std::endl;
            std::cout << "    Occupied space: " << part.getOccupiedSpace() << std::endl;
        }
    } catch (const std::exception &e) {
        // Обработка исключений
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
