#include <iostream>
#include <ostream>
//
// Created by vremyavnikuda on 9/23/24.
//
class Base {
public:
    virtual void show() {
        std::cout << "Base" << std::endl;
    }
};

class Derived : public Base {
public :
    void show() override {
        std::cout << "Derived" << std::endl;
    }
};

int main() {
    Base *obj = nullptr;
    obj->show();
}

/*
 *Ошибка времени выполнения -> вызываем виртуальную функцию show() через нулевой указатель (nullptr).Это приведет к неопределенному поведению.
 */
