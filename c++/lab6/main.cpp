#include <iostream>
#include "Product.h"
#include "Bag.h"

int main()
{
    try
    {
        Bag bag(10.0); // Создаем сумку с максимальным весом 10 кг

        Product milk("Milk", 1.5, 4.0, 6.0, 2.0, 4.18);
        Product water("Water", 1.0, 20.0, 30.0, 10.0, 4.2);
        Product juice("Juice", 1.5, 40.0, 45.0, 35.0, 3.9);
        Product iceCream("Ice Cream", 1.2, -10.0, -5.0, -20.0, 2.5);

        bag.addProduct(milk);
        bag.addProduct(water);
        bag.addProduct(juice);
        bag.addProduct(iceCream);

        std::cout << "Current weight: " << bag.getCurrentWeight() << " kg" << std::endl;
        std::cout << "Product count: " << bag.getProductCount() << std::endl;
        std::cout << "Spoiled product count: " << bag.getSpoiledProductCount() << std::endl;

        Product newProduct("New Product", 2.0, 50.0, 60.0, 40.0, 2.0);
        std::cout << "Products to spoil if adding new product: " << bag.getProductsToSpoilCount({newProduct}) << std::endl;

        bag.removeProduct("Juice");
        std::cout << "Spoiled product count after removing Juice: " << bag.getSpoiledProductCount() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
