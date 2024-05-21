#include "Product.h"
#include <sstream>

// Конструктор
Product::Product(const std::string &name, double weight, double temperature, double maxTemp, double minTemp, double heatCapacity)
    : name(name), weight(weight), temperature(temperature), maxTemperature(maxTemp), minTemperature(minTemp), state("Normal"), heatCapacity(heatCapacity)
{
    // Проверка корректности входных данных
    if (weight <= 0 || heatCapacity <= 0)
    {
        throw std::invalid_argument("Weight and heat capacity must be positive values.");
    }
    updateState(); // Обновление состояния продукта
}

// Сеттер для имени продукта
void Product::setName(const std::string &name)
{
    this->name = name;
}

// Сеттер для веса продукта
void Product::setWeight(double weight)
{
    // Проверка корректности входных данных
    if (weight <= 0)
    {
        throw std::invalid_argument("Weight must be a positive value.");
    }
    this->weight = weight;
}

// Сеттер для температуры продукта
void Product::setTemperature(double temperature)
{
    this->temperature = temperature;
    updateState(); // Обновление состояния продукта
}

// Сеттер для максимальной температуры продукта
void Product::setMaxTemperature(double maxTemp)
{
    this->maxTemperature = maxTemp;
}

// Сеттер для минимальной температуры продукта
void Product::setMinTemperature(double minTemp)
{
    this->minTemperature = minTemp;
}

// Сеттер для теплоемкости продукта
void Product::setHeatCapacity(double heatCapacity)
{
    // Проверка корректности входных данных
    if (heatCapacity <= 0)
    {
        throw std::invalid_argument("Heat capacity must be a positive value.");
    }
    this->heatCapacity = heatCapacity;
}

// Геттер для имени продукта
std::string Product::getName() const
{
    return name;
}

// Геттер для веса продукта
double Product::getWeight() const
{
    return weight;
}

// Геттер для температуры продукта
double Product::getTemperature() const
{
    return temperature;
}

// Геттер для максимальной температуры продукта
double Product::getMaxTemperature() const
{
    return maxTemperature;
}

// Геттер для минимальной температуры продукта
double Product::getMinTemperature() const
{
    return minTemperature;
}

// Геттер для состояния продукта
std::string Product::getState() const
{
    return state;
}

// Геттер для теплоемкости продукта
double Product::getHeatCapacity() const
{
    return heatCapacity;
}

// Метод для получения полной информации о продукте
std::string Product::getAllInfo() const
{
    std::stringstream ss;
    ss << "Name: " << getName() << "\n"
       << "Weight: " << getWeight() << "\n"
       << "Temperature: " << getTemperature() << "\n"
       << "Max Temperature: " << getMaxTemperature() << "\n"
       << "Min Temperature: " << getMinTemperature() << "\n"
       << "State: " << getState() << "\n"
       << "Heat Capacity: " << getHeatCapacity();
    return ss.str();
}

// Метод для обновления состояния продукта
void Product::updateState()
{
    if (temperature >= maxTemperature)
    {
        state = "Overheated";
    }
    else if (temperature <= minTemperature)
    {
        state = "Frozen";
    }
    else
    {
        state = "Normal";
    }
}

// Метод для передачи тепловой энергии продукту
void Product::transferHeatEnergy(double energy)
{
    double deltaT = energy / (weight * heatCapacity);
    setTemperature(temperature + deltaT);
}

// Метод для расчета достижимой температуры продукта при передаче тепловой энергии
double Product::achievableTemperature(double energy) const
{
    return temperature + energy / (weight * heatCapacity);
}
