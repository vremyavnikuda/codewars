/*
Создайте класс box, представляющий коробки. Закрытые данные-элементы (ДЭ) класса должны представлять ширину, длину, высоту и цвет коробки. Для задания цвета используйте перечисляемый тип данных. Включите в открытую часть класса следующие функции-элементы: конструктор с параметрами; конструктор копирования, который устанавливает в копии для цвета коробки значение “зеленый”, а для остальных ДЭ класса – значения одноименных ДЭ из объекта-оригинала; функция show, печатающая содержимое объекта класса.
Напишите функцию main, которая создает объект класса box, представляющий коробку красного цвета с размерами 2х3х8, затем посредством конструктора копий создает копию этого объекта, представляющую коробку зеленого цвета, и в заключение печатает содержимое объекта и копии.
*/
#include <string>
#include <iostream>
#include <ostream>
enum class Color
{
    RED,
    GREEN,
    BLUE
};

class Box
{
private:
    double length;
    double width;
    double height;
    Color color;

public:
    Box(double l, double w, double h, Color c) : length(l), width(w), height(h), color(c){};
    Box(const Box &ofher) : width(ofher.width), length(ofher.length), height(ofher.height), color(Color::GREEN){};
    void show() const
    {
        std::cout << "razmer box " << width << "x" << length << "x" << height << std::endl;
        std::cout << "Color: ";
        switch (color)
        {
        case Color::RED:
            std::cout << "red";
            break;
        case Color::GREEN:
            std::cout << "green";
            break;
        case Color::BLUE:
            std::cout << "blue";
            break;
        }
        std::cout << std::endl;
    }
};

int main()
{
    Box redBox(2.0, 3.0, 1.5, Color::RED);
    std::cout << "redBox: ";
    redBox.show();
    Box greenBox = redBox;
    std::cout << "greenBox: ";
    greenBox.show();
    return 0;
}