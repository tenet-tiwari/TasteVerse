
#include <iostream>
#include "User.h"
#include "Menu.h"
#include "Order.h"

int main() {
    Menu menu; 

    int userType;
    std::cout << "Choose your user type:\n";
    std::cout << "1. Customer\n";
    std::cout << "2. Chef\n";
    std::cout << "Enter choice: ";
    std::cin >> userType;

    if (userType == 1) {
        customerMode(menu);
    } else if (userType == 2) {
        chefMode(menu);
    }

    return 0;
}

