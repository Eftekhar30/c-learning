#include "User.h"
#include <iostream>

User::User() : username(""), password("") {}

User::User(const std::string& username, const std::string& password) 
    : username(username), password(password) {}

void User::changePassword() {
    std::string newPassword;
    std::cout << "\t\t\tEnter new password: ";
    std::cin >> newPassword;
    password = newPassword;
    std::cout << "\t\t\tPassword changed successfully!\n";
}