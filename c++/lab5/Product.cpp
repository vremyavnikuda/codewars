#include <iostream>

#include <string>

class Product
{
public:
    // Constructor
    Product(const std::string &name, double weight, double temperature, double maxTemp, double minTemp, const std::string &state, double heatCapacity);

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

    // Method to update state based on temperature
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

Product::Product(const std::string &name, double weight, double temperature, double maxTemp, double minTemp, const std::string &state, double heatCapacity)
    : name(name), weight(weight), temperature(temperature), maxTemperature(maxTemp), minTemperature(minTemp), state(state), heatCapacity(heatCapacity) {}

void Product::setName(const std::string &name)
{
    this->name = name;
}

void Product::setWeight(double weight)
{
    this->weight = weight;
}

void Product::setTemperature(double temperature)
{
    this->temperature = temperature;
}

void Product::setMaxTemperature(double maxTemp)
{
    this->maxTemperature = maxTemp;
}

void Product::setMinTemperature(double minTemp)
{
    this->minTemperature = minTemp;
}

void Product::setState(const std::string &state)
{
    this->state = state;
}

void Product::setHeatCapacity(double heatCapacity)
{
    this->heatCapacity = heatCapacity;
}

std::string Product::getName() const
{
    return name;
}

double Product::getWeight() const
{
    return weight;
}

double Product::getTemperature() const
{
    return temperature;
}

double Product::getMaxTemperature() const
{
    return maxTemperature;
}

double Product::getMinTemperature() const
{
    return minTemperature;
}

std::string Product::getState() const
{
    return state;
}

double Product::getHeatCapacity() const
{
    return heatCapacity;
}

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
