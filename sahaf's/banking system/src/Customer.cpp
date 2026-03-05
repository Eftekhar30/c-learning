#include "Customer.h"
#include <iostream>

Customer::Customer() : User() {}

Customer::Customer(const std::string& username, const std::string& password) 
    : User(username, password) {}

bool Customer::login() {
    std::string enteredUser, enteredPass;
    std::cout << "\t\t\tEnter Username: ";
    std::cin >> enteredUser;
    std::cout << "\t\t\tEnter PIN code: ";
    std::cin >> enteredPass;

    if (enteredUser == username && enteredPass == password) {
        std::cout << "\t\t\tLogin successful!\n";
        return true;
    }
    
    std::cout << "\t\t\tInvalid credentials. Login failed.\n";
    std::cout << "\t\t\tChange password? (Y/N): ";
    char choice;
    std::cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        changePassword();
    }
    return false;
}