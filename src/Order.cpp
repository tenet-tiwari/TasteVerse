#include "Order.h"
#include <iostream>

void Order::addItem(const FoodItem& item, int quantity) {
    items.push_back({item, quantity});
}

void Order::printBill() {
    double total = 0.0;
    std::cout << "\nOrder Details:\n";
    for (const auto& orderedItem : items) {
        std::cout << orderedItem.quantity << " x " << orderedItem.item.name << " - $" << orderedItem.item.price << " each\n";
        total += orderedItem.item.price * orderedItem.quantity;
    }
    std::cout << "Total: $" << total << "\n";
}
