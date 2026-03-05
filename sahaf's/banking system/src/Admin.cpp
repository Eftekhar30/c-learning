#include "Admin.h"
#include <iostream>

Admin::Admin() : User("admin", "admin") {}

Admin::Admin(const std::string& username, const std::string& password) 
    : User(username, password) {}

bool Admin::login() {
    std::string enteredUser, enteredPass;
    std::cout << "\t\t\tEnter admin username: ";
    std::cin >> enteredUser;
    std::cout << "\t\t\tEnter admin password: ";
    std::cin >> enteredPass;

    if (enteredUser == username && enteredPass == password) {
        std::cout << "\t\t\tAdmin login successful!\n";
        return true;
    }
    
    std::cout << "\t\t\tInvalid admin credentials.\n";
    std::cout << "\t\t\tChange password? (Y/N): ";
    char choice;
    std::cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        changePassword();
    }
    return false;
}