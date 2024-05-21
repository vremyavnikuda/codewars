#include <iostream>

#include <string>
#include <utility>
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

// Конструктор
Product::Product(std::string name, double weight, double temperature, double maxTemp, double minTemp, const std::string &state, double heatCapacity)
    : name(std::move(name)), weight(weight), temperature(temperature), maxTemperature(maxTemp),
      minTemperature(minTemp), state(state), heatCapacity(heatCapacity) {}

// Метод устанавливает имя продукта
void Product::setName(const std::string &name)
{
    this->name = name;
}

// Метод установки веса продукта
void Product::setWeight(double weight)
{
    this->weight = weight;
}

// Метод установки температуры продукта
void Product::setTemperature(double temperature)
{
    this->temperature = temperature;
}

// Метод установки максимальной температуры продукта
void Product::setMaxTemperature(double maxTemp)
{
    this->maxTemperature = maxTemp;
}

// Метод установки минимальной температуры продукта
void Product::setMinTemperature(double minTemp)
{
    this->minTemperature = minTemp;
}

// Метод установки состояния продукта
void Product::setState(const std::string &state)
{
    this->state = state;
}

// Метод установки теплоёмкости продукта
void Product::setHeatCapacity(double heatCapacity)
{
    this->heatCapacity = heatCapacity;
}

// Метод возвращает имя продукта
std::string Product::getName() const
{
    return name;
}

// Метод возвращает вес продукта
double Product::getWeight() const
{
    return weight;
}

// Метод возвращает температуру продукта
double Product::getTemperature() const
{
    return temperature;
}

// Метод возвращает максимальную температуру продукта
double Product::getMaxTemperature() const
{
    return maxTemperature;
}

// Метод возвращает минимальную температуру продукта
double Product::getMinTemperature() const
{
    return minTemperature;
}

// Метод возвращает состояние продукта
std::string Product::getState() const
{
    return state;
}

// Метод возвращает теплоёмкость продукта
double Product::getHeatCapacity() const
{
    return heatCapacity;
}

// Метод возвращает полную информацию о продукте
// @getAllInfo
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

// Метод для обновления состояния на основе температуры
void Product::updateState()
{
    if (temperature >= maxTemperature)
    {
        // Перегретый
        state = "Overheated";
    }
    else if (temperature <= minTemperature)
    {
        // Перемороженный
        state = "Frozen";
    }
    else
    {
        // Нормальный
        state = "Normal";
    }
}
