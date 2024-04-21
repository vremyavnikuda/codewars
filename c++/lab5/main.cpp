/*
Задание

Реализуйте класс, моделирующий заданный тип объектов предметной области. Не должно быть возможности создать или перевести объект в некорректное состояние (например, человек с отрицательным возрастом). Хорошо подумайте над интерфейсом вашего класса. Необходимые поля и методы заданы, но вы можете добавить свои, если в этом есть необходимость. Описание класса должно быть разбито на два файла – заголовочный и реализации. Напишите программу, демонстрирующую работоспособность всех методов. Необходимо использовать функции и объекты стандартной библиотеки С++, а не С, где это возможно. Например, хранить строки в объекте класса std::string, а не в виде массива символов, использовать std::cin и std::cout для ввода и вывода соответственно.

7. Пищевой продукт
Необходимо разработать класс Продукт для информационной системы службы доставки, рекомендующей определённую компоновку сумок доставщиков продуктами для доставки с учётом их требований к температурному режиму. Изначально все продукты находятся в нормальном состоянии. При достижении продуктом максимально допустимой температуры, он навсегда переходит в состояние Перегрет. Аналогично в случае достижения минимальной температуры.
Поля: название, масса, температура, максимально допустимая температура, минимально допустимая температура, состояние (переморожен, перегрет, нормальное), теплоёмкость
Методы: конструктор со всеми полями, кроме состояния; возврат названия; возврат массы; возврат температуры; методы для возврата максимально и минимально допустимой температуры; возврат состояния; возврат теплоёмкости; передать тепловую энергию (возможно отрицательную); возврат температуры, достижимой при передаче заданного количества тепловой энергии (возможно, отрицательной).
*/

/*
Main function
*/

#include "Product.cpp"
int main()
{
    Product milk("Milk", 1.5, 4.0, 6.0, 2.0, "Normal", 4.18);

    std::cout << "Product: " << milk.getName() << std::endl;
    std::cout << "Initial State: " << milk.getState() << std::endl;

    milk.setTemperature(7.0);
    milk.updateState();

    std::cout << "Updated State: " << milk.getState() << std::endl;

    return 0;
}
