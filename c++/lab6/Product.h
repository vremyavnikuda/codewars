#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <sstream>

// Класс для хранения информации о продукте
class Product
{
public:
    // Конструктор
    Product(std::string name, double weight, double temperature, double maxTemp, double minTemp,
            const std::string &state, double heatCapacity);

    // Setters
    void setName(const std::string &name);
    void setWeight(double weight);
    void setTemperature(double temperature);
    void setMaxTemperature(double maxTemp);
    void setMinTemperature(double minTemp);
    void setState(const std::string &state);
    void setHeatCapacity(double heatCapacity);

    // Getters
    std::string getName() const;
    double getWeight() const;
    double getTemperature() const;
    double getMaxTemperature() const;
    double getMinTemperature() const;
    std::string getState() const;
    double getHeatCapacity() const;

    // Метод возвращает полную информацию о продукте
    std::string getAllInfo() const;

    // Метод для обновления состояния на основе температуры
    void updateState();

private:
    std::string name;
    double weight;
    double temperature;
    double maxTemperature;
    double minTemperature;
    std::string state;
    double heatCapacity;
};

#endif // PRODUCT_H