#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <stdexcept>

class Product
{
public:
    // Конструктор
    Product(const std::string &name, double weight, double temperature, double maxTemp, double minTemp, double heatCapacity);

    // Сеттеры
    void setName(const std::string &name);
    void setWeight(double weight);
    void setTemperature(double temperature);
    void setMaxTemperature(double maxTemp);
    void setMinTemperature(double minTemp);
    void setHeatCapacity(double heatCapacity);

    // Геттеры
    std::string getName() const;
    double getWeight() const;
    double getTemperature() const;
    double getMaxTemperature() const;
    double getMinTemperature() const;
    std::string getState() const;
    double getHeatCapacity() const;

    // Методы
    std::string getAllInfo() const;                    // Получить полную информацию о продукте
    void updateState();                                // Обновить состояние продукта
    void transferHeatEnergy(double energy);            // Передача тепловой энергии
    double achievableTemperature(double energy) const; // Расчет достижимой температуры

private:
    std::string name;      // Наименование продукта
    double weight;         // Вес продукта
    double temperature;    // Текущая температура продукта
    double maxTemperature; // Максимальная температура продукта
    double minTemperature; // Минимальная температура продукта
    std::string state;     // Состояние продукта
    double heatCapacity;   // Теплоемкость продукта
};

#endif
