#ifndef BAG_H
#define BAG_H

#include <vector>
#include <string>
#include "Product.h"

class Bag
{
private:
    std::vector<Product> products; // Вектор продуктов в сумке
    double maxWeight;              // Максимальный вес сумки
    double currentWeight;          // Текущий вес сумки

    void updateTemperatures(); // Внутренний метод для обновления температур продуктов в сумке

public:
    // Конструктор сумки с заданным максимальным весом
    Bag(double maxWeight);

    // Добавление продукта в сумку
    bool addProduct(const Product &product);

    // Удаление продукта из сумки по названию
    bool removeProduct(const std::string &name);

    // Получение текущего веса сумки
    double getCurrentWeight() const;

    // Получение количества продуктов в сумке
    int getProductCount() const;

    // Получение количества испорченных продуктов в сумке
    int getSpoiledProductCount() const;

    // Получение количества продуктов, которые испортятся при добавлении новых продуктов
    int getProductsToSpoilCount(const std::vector<Product> &newProducts) const;
};

#endif
