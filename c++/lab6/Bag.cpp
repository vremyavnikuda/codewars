#include "Bag.h"
#include <algorithm>
#include <stdexcept>

// Конструктор
Bag::Bag(double maxWeight) : maxWeight(maxWeight), currentWeight(0) {}

// Метод для обновления температур продуктов в сумке
void Bag::updateTemperatures()
{
    double totalHeatCapacity = 0;
    double totalHeat = 0;
    for (const auto &product : products)
    {
        totalHeatCapacity += product.getWeight() * product.getHeatCapacity();
        totalHeat += product.getWeight() * product.getHeatCapacity() * product.getTemperature();
    }

    double newTemperature = totalHeat / totalHeatCapacity;

    for (auto &product : products)
    {
        product.setTemperature(newTemperature);
    }
}

// Метод для добавления продукта в сумку
bool Bag::addProduct(const Product &product)
{
    if (currentWeight + product.getWeight() > maxWeight)
    {
        throw std::overflow_error("Cannot add product: bag is overfilled.");
    }

    products.push_back(product);
    currentWeight += product.getWeight();
    updateTemperatures();
    return true;
}

// Метод для удаления продукта из сумки по названию
bool Bag::removeProduct(const std::string &name)
{
    auto it = std::find_if(products.begin(), products.end(), [&](const Product &p)
                           { return p.getName() == name; });

    if (it == products.end())
    {
        throw std::invalid_argument("Product not found in the bag.");
    }

    currentWeight -= it->getWeight();
    products.erase(it);
    updateTemperatures();
    return true;
}

// Метод для получения текущего веса сумки
double Bag::getCurrentWeight() const
{
    return currentWeight;
}

// Метод для получения количества продуктов в сумке
int Bag::getProductCount() const
{
    return products.size();
}

// Метод для получения количества испорченных продуктов в сумке
int Bag::getSpoiledProductCount() const
{
    int count = 0;
    for (const auto &product : products)
    {
        if (product.getState() != "Normal")
        {
            count++;
        }
    }
    return count;
}

// Метод для получения количества продуктов, которые испортятся при добавлении новых продуктов
int Bag::getProductsToSpoilCount(const std::vector<Product> &newProducts) const
{
    std::vector<Product> tempProducts = products;
    for (const auto &product : newProducts)
    {
        tempProducts.push_back(product);
    }

    double totalHeatCapacity = 0;
    double totalHeat = 0;
    for (const auto &product : tempProducts)
    {
        totalHeatCapacity += product.getWeight() * product.getHeatCapacity();
        totalHeat += product.getWeight() * product.getHeatCapacity() * product.getTemperature();
    }

    double newTemperature = totalHeat / totalHeatCapacity;

    int count = 0;
    for (auto &product : tempProducts)
    {
        product.setTemperature(newTemperature);
        product.updateState();
        if (product.getState() != "Normal")
        {
            count++;
        }
    }
    return count - getSpoiledProductCount();
}
