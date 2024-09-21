#include <iostream>
int main()
{   
    //инициализация переменной 
    int a = 0, b = 1, result;
    //счетчик 
    int count = 30;
    
    std::cout << a << " " << b << " ";
    // основной цикл который генерирует числа фибо
    for (int i = 2; i < count; i++)
    {
        //присваиваем переменной result значение следующей последовательности фибо
        result = a + b;
        //выводим результат фибо
        std::cout << result << " ";
        //теперь а == число б
        a = b;
        b = result;
    }
    return 0;
}