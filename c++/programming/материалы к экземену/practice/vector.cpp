/*
Создайте класс vector, представляющий векторы в трехмерном пространстве. Включите в закрытую часть класса вещественные переменные x, y и z, представляющие координаты вектора. Включите в открытую часть класса конструктор с параметрами. Добавьте в программу перегруженный оператор > =, который является функцией-другом класса vector и возвращает результат операции “больше или равно” над модулями двух векторов, представляемых двумя объектами класса vector. Напишите функцию main, которая создает три объекта класса vector, представляющие векторы с координатами (1; 2; 3), (7; 8 ;9) и (4; 5; 6), а затем, применяя к этим объектам попарно перегруженный оператор >=, получает результат сравнения указанных векторов и печатает его.
*/

#include <math.h>
#include <iostream>
class vector
{
private:
    double x, y, z;

public:
    // Конструктор с параметрами
    vector(double xVal, double yVal, double zVal) : x(xVal), y(yVal), z(zVal){};

    friend bool operator>=(const vector &v1, const vector &v2);

    double magnitude() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }
};

bool operator>=(const vector &v1, const vector &v2)
{
    return v1.magnitude() >= v2.magnitude();
}

int main()
{
    vector v1(1, 2, 3);
    vector v2(7, 8, 9);
    vector v3(4, 5, 6);

    std::cout << "v1 >= v2: " << (v1 >= v2) << std::endl;
    std::cout << "v1 >= v3: " << (v1 >= v3) << std::endl;
    std::cout << "v2 >= v3: " << (v2 >= v3) << std::endl;
    return 0;
}
