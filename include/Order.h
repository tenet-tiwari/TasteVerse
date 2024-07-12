#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>
#include "Menu.h" // Assuming Order needs Menu's FoodItem struct or class

class Order {
public:
    void addItem(const FoodItem& item, int quantity);
    void printBill();

private:
    struct OrderedItem {
        FoodItem item;
        int quantity;
    };
    std::vector<OrderedItem> items;
};

#endif // ORDER_H
