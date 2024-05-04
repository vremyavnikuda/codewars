//
// Created by andre on 28.04.2024.
//

#ifndef LAB_6_BAG_H
#define LAB_6_BAG_H

#include <vector>
#include "Product.h"

class Bag {
public:
    explicit Bag(double maxWeight);

    void addProduct(const Product &product);
    void removeProduct(const Product &product);
    double getTotalWeight() const;
    int getProductCount() const;
    int getCorruptedProductCount() const;
    int getCorruptedProductCountWithAddition(const std::vector<Product> &newProducts) const;

private:
    std::vector<Product> products;
    double maxWeight;

    void updateProductTemperatures(double newTemperature);
};

#endif //LAB_6_BAG_H
