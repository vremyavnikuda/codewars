
# Описание классов `Partition` и `DataStorage`

## Класс `Partition`

| Поле                  | Тип       | Описание                                        |
|-----------------------|-----------|-------------------------------------------------|
| `name`                | `std::string` | Имя раздела                                      |
| `startByte`           | `int`     | Начальный байт раздела                           |
| `endByte`             | `int`     | Конечный байт раздела                            |
| `fileSystem`          | `std::string` | Файловая система раздела                          |
| `occupiedSpace`       | `int`     | Занятое пространство в разделе (в байтах)        |

| Метод                      | Тип возвращаемого значения | Параметры                              | Типы параметров                         |
|----------------------------|---------------------------|----------------------------------------|-----------------------------------------|
| `Partition` (конструктор)  |                           | `startByte`, `endByte`, `name`, `fileSystem`, `occupiedSpace` | `int`, `int`, `std::string`, `std::string`, `int` |
| `getSize`                  | `int`                     |                                        |                                          |
| `getStartByte`             | `int`                     |                                        |                                          |
| `getEndByte`               | `int`                     |                                        |                                          |
| `getName`                  | `std::string`             |                                        |                                          |
| `setName`                  | `void`                    | `newName`                              | `const std::string&`                     |
| `getFileSystem`            | `std::string`             |                                        |                                          |
| `setFileSystem`            | `void`                    | `newFileSystem`                        | `const std::string&`                     |
| `getOccupiedSpace`         | `int`                     |                                        |                                          |
| `setOccupiedSpace`         | `void`                    | `newOccupiedSpace`                     | `int`                                    |

## Класс `DataStorage`

| Поле                  | Тип           | Описание                                            |
|-----------------------|---------------|-----------------------------------------------------|
| `manufacturer`        | `std::string` | Производитель                                       |
| `model`               | `std::string` | Модель                                              |
| `serialNumber`        | `std::string` | Серийный номер                                      |
| `type`                | `std::string` | Тип накопителя                                      |
| `capacity`            | `int`         | Емкость накопителя (в байтах)                       |
| `partitionTableType`  | `std::string` | Тип таблицы разделов (GPT, MBR или None)            |
| `partitions`          | `std::vector<Partition>` | Вектор разделов                                    |

| Метод                      | Тип возвращаемого значения | Параметры                           | Типы параметров                    |
|----------------------------|---------------------------|-------------------------------------|------------------------------------|
| `DataStorage` (конструктор)|                           | `manufacturer`, `model`, `serialNumber`, `type`, `capacity` | `std::string`, `std::string`, `std::string`, `std::string`, `int` |
| `~DataStorage` (деструктор) | `void`                    |                                     |                                    |
| `getManufacturer`          | `std::string`             |                                     |                                    |
| `getModel`                 | `std::string`             |                                     |                                    |
| `getSerialNumber`          | `std::string`             |                                     |                                    |
| `getType`                  | `std::string`             |                                     |                                    |
| `getCapacity`              | `int`                     |                                     |                                    |
| `getPartitionTableType`    | `std::string`             |                                     |                                    |
| `getPartitionCount`        | `int`                     |                                     |                                    |
| `getPartitionTotalSize`    | `int`                     |                                     |                                    |
| `getFreeSpace`             | `int`                     |                                     |                                    |
| `createPartitionTable`     | `void`                    | `type`                              | `const std::string&`                |
| `hasPartitionTable`        | `bool`                    |                                     |                                    |
| `addPartition`             | `void`                    | `startByte`, `endByte`, `name`, `fileSystem`, `occupiedSpace` | `int`, `int`, `const std::string&`, `const std::string&`, `int` |
| `removePartition`          | `void`                    | `index`                             | `int`                              |
| `getPartition`             | `Partition`               | `index`                             | `int`                              |
| `isOverlap`                | `bool`                    | `startByte`, `endByte`              | `int`, `int`                       |

# Обоснование выбора типа коллекции и описание методов контейнера

## Обоснование выбора типа коллекции

В программе для хранения разделов в классе `DataStorage` используется контейнер `std::vector`. Вот обоснование выбора этого контейнера:

1. **Динамическое изменение размера**: `std::vector` позволяет динамически изменять размер, что удобно для добавления и удаления разделов.
2. **Производительность**: `std::vector` обеспечивает постоянное время доступа к элементам по индексу, что важно для операций чтения/записи разделов.
3. **Удобство использования**: `std::vector` предоставляет простые и интуитивно понятные методы для добавления, удаления и доступа к элементам.
4. **Стандартная библиотека**: Использование контейнера из стандартной библиотеки C++ гарантирует стабильность и совместимость.

## Описание методов контейнера, используемых в программе

1. **Добавление элемента (`emplace_back`)**
    ```cpp
    partitions.emplace_back(startByte, endByte, name, fileSystem, occupiedSpace);
    ```
    Метод `emplace_back` добавляет новый элемент в конец вектора. Он вызывает конструктор элемента на месте, что экономит ресурсы на создание временных объектов.

2. **Удаление элемента (`erase`)**
    ```cpp
    partitions.erase(partitions.begin() + index);
    ```
    Метод `erase` удаляет элемент по указанному итератору. В данном случае используется комбинация `partitions.begin() + index` для получения итератора к нужному элементу по индексу.

3. **Получение количества элементов (`size`)**
    ```cpp
    return partitions.size();
    ```
    Метод `size` возвращает количество элементов в векторе, что используется для определения числа разделов.

4. **Доступ к элементу по индексу (`operator[]`)**
    ```cpp
    return partitions[index];
    ```
    Перегруженный оператор `[]` позволяет получить доступ к элементу вектора по указанному индексу. Это обеспечивает быстрый доступ к разделу.

5. **Очистка вектора (`clear`)**
    ```cpp
    partitions.clear();
    ```
    Метод `clear` удаляет все элементы из вектора, что используется при создании новой таблицы разделов.

6. **Итерация по элементам (`range-based for loop`)**
    ```cpp
    for (const auto& partition : partitions) {
        totalSize += partition.getOccupiedSpace();
    }
    ```
    Диапазонный цикл `for` используется для итерации по всем элементам вектора. Это удобно для суммирования размеров разделов или для проверки перекрытия разделов.

### Примеры использования методов

#### Добавление раздела
```cpp
void DataStorage::addPartition(int startByte, int endByte, const std::string& name, const std::string& fileSystem, int occupiedSpace) {
    if (startByte < 0 || endByte >= capacity || startByte >= endByte) {
        throw std::invalid_argument("Invalid start or end byte.");
    }
    if (isOverlap(startByte, endByte)) {
        throw std::invalid_argument("Partition overlaps with existing partitions.");
    }
    partitions.emplace_back(startByte, endByte, name, fileSystem, occupiedSpace);
}
```

#### Удаление раздела
```cpp
void DataStorage::removePartition(int index) {
    if (index < 0 || index >= partitions.size()) {
        throw std::invalid_argument("Invalid partition index.");
    }
    partitions.erase(partitions.begin() + index);
}
```

#### Получение общего размера разделов
```cpp
int DataStorage::getPartitionTotalSize() const {
    int totalSize = 0;
    for (const auto& partition : partitions) {
        totalSize += partition.getOccupiedSpace();
    }
    return totalSize;
}
```

#### Очистка таблицы разделов
```cpp
void DataStorage::createPartitionTable(const std::string& type) {
    if (type != "GPT" && type != "MBR") {
        throw std::invalid_argument("Invalid partition table type.");
    }
    partitionTableType = type;
    partitions.clear();
}
```

## Заключение

Использование `std::vector` в данном контексте обосновано его гибкостью, эффективностью и простотой в использовании. Методы `std::vector`, такие как `emplace_back`, `erase`, `size`, `clear`, и оператор `[]`, идеально подходят для управления коллекцией разделов, обеспечивая как производительность, так и удобство программирования.
