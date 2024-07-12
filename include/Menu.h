

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

struct FoodItem { 
    std::string name;
    double price;
};

class Menu {
private:
    std::unordered_map<std::string, std::vector<FoodItem>> categories;

public:
    void addItem(const std::string& category, const FoodItem& item);
    bool deleteItem(const std::string& category, const std::string& itemName);
    bool updateItemPrice(const std::string& category, const std::string& itemName, double price);
    std::vector<std::string> getCategories() const;
    bool categoryExists(const std::string& category) const;
    std::vector<FoodItem> getItemsInCategory(const std::string& category) const;
    void printMenu() const;
    void loadMenuFromFile(const std::string& filename);
    void saveMenuToFile(const std::string& filename) const;
};

#endif // MENU_H



