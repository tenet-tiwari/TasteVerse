
#include "Menu.h"
#include <algorithm>
#include <fstream>
#include <sstream>

void Menu::addItem(const std::string& category, const FoodItem& item) {
    categories[category].push_back(item);
}

bool Menu::deleteItem(const std::string& category, const std::string& itemName) {
    auto& items = categories[category];
    auto it = std::find_if(items.begin(), items.end(), [&itemName](const FoodItem& item) {
        return item.name == itemName;
    });

    if (it != items.end()) {
        items.erase(it);
        return true;
    } else {
        std::cout << "Item not found in category: " << category << std::endl;
        return false;
    }
}

bool Menu::updateItemPrice(const std::string& category, const std::string& itemName, double price) {
    auto& items = categories[category];
    auto it = std::find_if(items.begin(), items.end(), [&itemName](const FoodItem& item) {
        return item.name == itemName;
    });
    if (it != items.end()) {
        it->price = price;
        return true;
    }
    return false;
}

std::vector<std::string> Menu::getCategories() const {
    std::vector<std::string> categoryList;
    for (const auto& pair : categories) {
        categoryList.push_back(pair.first);
    }
    return categoryList;
}

bool Menu::categoryExists(const std::string& category) const {
    return categories.find(category) != categories.end();
}

std::vector<FoodItem> Menu::getItemsInCategory(const std::string& category) const {
    auto it = categories.find(category);
    if (it != categories.end()) {
        return it->second;
    }
    return {};
}

void Menu::printMenu() const {
    std::cout << "\nCurrent Menu:\n";
    for (const auto& pair : categories) {
        std::cout << "- " << pair.first << ":\n";
        for (const auto& item : pair.second) {
            std::cout << "  - " << item.name << " - $" << item.price << "\n";
        }
    }
}

void Menu::loadMenuFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string category, itemName;
        double price;
        if (!(std::getline(iss, category, '|') && std::getline(iss, itemName, '|') && iss >> price)) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue;
        }

        addItem(category, {itemName, price});
        //std::cout << "Loaded: " << category << " | " << itemName << " | " << price << "\n"; // Debug statement
    }

    file.close();
}

void Menu::saveMenuToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return;
    }

    for (const auto& pair : categories) {
        for (const auto& item : pair.second) {
            file << pair.first << "|" << item.name << "|" << item.price << "\n";
            //std::cout << "Saved: " << pair.first << " | " << item.name << " | " << item.price << "\n"; // Debug statement
        }
    }

    file.close();
}




