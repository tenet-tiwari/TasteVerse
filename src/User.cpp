
#include "User.h"
#include "Menu.h"
#include "Order.h"
#include <limits>
#include <iostream>


const std::string menuFile = "menu.txt";

void customerMode(Menu& menu) {
    menu.loadMenuFromFile(menuFile);

    Order order;
    std::string category;
    int itemNumber, quantity;
    char more = 'y';

    while (more == 'y' || more == 'Y') {
        std::cout << "\nAvailable categories:\n";
        auto categories = menu.getCategories();
        for (const auto& categoryName : categories) {
            std::cout << "- " << categoryName << "\n";
        }
        std::cout << "Enter category: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, category);

        if (!menu.categoryExists(category)) {
            std::cout << "Invalid category. Please try again.\n";
            continue;
        }

        std::cout << "\nAvailable items in " << category << ":\n";
        auto items = menu.getItemsInCategory(category);
        int itemIndex = 1;
        for (const auto& item : items) {
            std::cout << itemIndex++ << ". " << item.name << " - $" << item.price << "\n";
        }

        std::cout << "\nEnter item number: ";
        std::cin >> itemNumber;
        std::cout << "Enter quantity: ";
        std::cin >> quantity;

        if (itemNumber > 0 && itemNumber <= items.size()) {
            auto it = items.begin();
            std::advance(it, itemNumber - 1);
            order.addItem(*it, quantity);
            std::cout << "Item added to order.\n";
        } else {
            std::cout << "Invalid item number.\n";
        }

        std::cout << "Would you like to order more items? (y/n): ";
        std::cin >> more;
    }

    order.printBill();
}

void chefMode(Menu& menu) {
    menu.loadMenuFromFile(menuFile);

    std::string password;
    std::cout << "Enter chef password: ";
    std::cin >> password;

    if (password != "admin123") {
        std::cout << "Incorrect password. Access denied.\n";
        return;
    }

    int choice;
    std::string category, itemName;
    double price;

    do {
        std::cout << "\n1. Add new food item\n";
        std::cout << "2. Delete a food item\n";
        std::cout << "3. Update the price of a food item\n";
        std::cout << "4. Print current menu\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                std::cout << "Enter category: ";
                std::getline(std::cin, category);
                std::cout << "Enter food item name: ";
                std::getline(std::cin, itemName);
                std::cout << "Enter price: ";
                std::cin >> price;
                menu.addItem(category, {itemName, price});
                std::cout << "Food item added successfully!\n";
                break;
            case 2:
                std::cout << "Enter category: ";
                std::getline(std::cin, category);
                std::cout << "Enter food item name: ";
                std::getline(std::cin, itemName);
                menu.deleteItem(category, itemName);
                std::cout << "Food item deleted successfully!\n";
                break;
            case 3:
                std::cout << "Enter category: ";
                std::getline(std::cin, category);
                std::cout << "Enter food item name: ";
                std::getline(std::cin, itemName);
                std::cout << "Enter new price: ";
                std::cin >> price;
                menu.updateItemPrice(category, itemName, price);
                std::cout << "Food item price updated successfully!\n";
                break;
            case 4:
                menu.printMenu();
                break;
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
        menu.saveMenuToFile(menuFile);
    } while (choice != 5);
}

