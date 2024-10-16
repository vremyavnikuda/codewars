/*
Задание

Реализуйте класс, моделирующий заданный тип объектов предметной области. Не должно быть возможности создать или перевести объект в некорректное состояние (например, человек с отрицательным возрастом). Хорошо подумайте над интерфейсом вашего класса. Необходимые поля и методы заданы, но вы можете добавить свои, если в этом есть необходимость. Описание класса должно быть разбито на два файла – заголовочный и реализации. Напишите программу, демонстрирующую работоспособность всех методов. Необходимо использовать функции и объекты стандартной библиотеки С++, а не С, где это возможно. Например, хранить строки в объекте класса std::string, а не в виде массива символов, использовать std::cin и std::cout для ввода и вывода соответственно.

7. Пищевой продукт
Необходимо разработать класс Продукт для информационной системы службы доставки, рекомендующей определённую компоновку сумок доставщиков продуктами для доставки с учётом их требований к температурному режиму. Изначально все продукты находятся в нормальном состоянии. При достижении продуктом максимально допустимой температуры, он навсегда переходит в состояние Перегрет. Аналогично в случае достижения минимальной температуры.
Поля: название, масса, температура, максимально допустимая температура, минимально допустимая температура, состояние (переморожен, перегрет, нормальное), теплоёмкость
Методы: конструктор со всеми полями, кроме состояния; возврат названия; возврат массы; возврат температуры; методы для возврата максимально и минимально допустимой температуры; возврат состояния; возврат теплоёмкости; передать тепловую энергию (возможно отрицательную); возврат температуры, достижимой при передаче заданного количества тепловой энергии (возможно, отрицательной).

Main function
*/
/**Setter
 * @setName
 * @setWeight
 * @setTemperature
 * @setTemperature
 * @setMaxTemperature
 * @setMinTemperature
 * @setState
 * @setHeatCapacity()
 *
 * Getter
 * @getName
 * @getWeight
 * @getTemperature
 * @getMaxTemperature
 * @getMinTemperature
 * @getState
 * @getHeatCapacity
 * Методы
 * @getAllInfo
 * @updateState
 * */
#include "Product.cpp"

int main()
{
    /*
    Name: Milk
    Weight: 1.5
    Temperature: 7
    Max Temperature: 6
    Min Temperature: 2
    State: Overheated
    Heat Capacity: 4.18
    */
    Product milk("Milk", 1.5, 4.0, 6.0, 2.0, "Normal", 4.18);
    milk.setTemperature(7.0);
    milk.updateState();
    std::cout << "Updated State: " << milk.getState() << std::endl;
    std::cout << "Product: " << milk.getName() << std::endl;
    std::cout << "Initial State: " << milk.getState() << std::endl;

    // Test 1: Normal product
    /*
    Name: Water
    Weight: 1
    Temperature: 25
    Max Temperature: 30
    Min Temperature: 10
    State: Normal
    Heat Capacity: 4.2
    */
    Product water("Water", 1.0, 20.0, 30.0, 10.0, "Normal", 4.2);
    std::cout << "Product: " << water.getName() << std::endl;
    std::cout << "Initial State: " << water.getState() << std::endl;
    water.setTemperature(25.0);
    water.updateState();
    std::cout << "Updated State: " << water.getState() << std::endl;

    // Test 2: Overheated product
    /*
    Name: Juice
    Weight: 1.5
    Temperature: 50
    Max Temperature: 45
    Min Temperature: 35
    State: Overheated
    Heat Capacity: 3.9
    */
    Product juice("Juice", 1.5, 40.0, 45.0, 35.0, "Normal", 3.9);
    std::cout << "Product: " << juice.getName() << std::endl;
    std::cout << "Initial State: " << juice.getState() << std::endl;
    juice.setTemperature(50.0);
    juice.updateState();
    std::cout << "Updated State: " << juice.getState() << std::endl;

    // Test 3: Frozen product
    /*
    Name: Ice Cream
    Weight: 1.2
    Temperature: -15
    Max Temperature: -5
    Min Temperature: 0
    State: Frozen
    Heat Capacity: 2.5
    */
    Product iceCream("Ice Cream", 1.2, -10.0, -5.0, 0.0, "Normal", 2.5);
    std::cout << "Product: " << iceCream.getName() << std::endl;
    std::cout << "Initial State: " << iceCream.getState() << std::endl;
    iceCream.setTemperature(-15.0);
    iceCream.updateState();
    std::cout << "Updated State: " << iceCream.getState() << std::endl;

    std::cout << milk.getAllInfo() << std::endl;
    std::cout << water.getAllInfo() << std::endl;
    std::cout << juice.getAllInfo() << std::endl;
    std::cout << iceCream.getAllInfo() << std::endl;

    return 0;
}
