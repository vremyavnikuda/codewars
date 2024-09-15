#include <algorithm>
#include <iostream>
#include "Bag.h"

Bag::Bag(double maxWeight) : maxWeight(maxWeight) {}

void Bag::updateProductTemperatures(double newTemperature) {
    for (auto &product : products) {
        product.setTemperature(newTemperature);
        product.updateState();
    }
}

void addProduct(const Product &product)
{
    if (getTotalWeight() + product.getWeight() <= maxWeight)
    {
        products.push_back(product);
        updateProductTemperatures(product.getTemperature());
    }
    else
    {
        std::cout << "Cannot add product, bag is full." << std::endl;
    }
}

void removeProduct(const Product &product)
{
    auto it = std::find(products.begin(), products.end(), product);
    if (it != products.end())
    {
        products.erase(it);
    }
    else
    {
        std::cout << "Product not found in the bag." << std::endl;
    }
}

double getTotalWeight() const
{
    double totalWeight = 0.0;
    for (const auto &product : products)
    {
        totalWeight += product.getWeight();
    }
    return totalWeight;
}

int getProductCount() const
{
    return static_cast<int>(products.size());
}

int getCorruptedProductCount() const
{
    int corruptedCount = 0;
    for (const auto &product : products)
    {
        if (product.getState() != "Normal")
        {
            corruptedCount++;
        }
    }
    return corruptedCount;
}

int getCorruptedProductCountWithAddition(const std::vector<Product> &newProducts) const
{
    int corruptedCount = getCorruptedProductCount();
    double newTotalWeight = getTotalWeight();
    for (const auto &product : newProducts)
    {
        newTotalWeight += product.getWeight();
        if (newTotalWeight > maxWeight || product.getState() != "Normal")
        {
            corruptedCount++;
        }
    }
    return corruptedCount;
}

// Метод для получения количества поврежденных продуктов с добавлением новых продуктов
int Bag::getCorruptedProductCountWithAddition(const std::vector<Product> &newProducts) const {
    int corruptedCount = getCorruptedProductCount();
    double newTotalWeight = getTotalWeight();
    for (const auto &product : newProducts) {
        newTotalWeight += product.getWeight();
        if (newTotalWeight > maxWeight || product.getState() != "Normal") {
            corruptedCount++;
        }
    }
    return corruptedCount;
}
