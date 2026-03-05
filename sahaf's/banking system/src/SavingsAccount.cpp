#include "SavingsAccount.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

SavingsAccount::SavingsAccount() 
    : Account(), dataFile(""), size(nullptr), customers(nullptr), accounts(nullptr) {}

SavingsAccount::SavingsAccount(const std::string& filename, int* sizePtr)
    : Account(), dataFile(filename), size(sizePtr) {
    
    customers = new Customer*[*size];
    accounts = new SavingsAccount*[*size];
    
    for (int i = 0; i < *size; i++) {
        customers[i] = nullptr;
        accounts[i] = nullptr;
    }
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "\t\t\tFailed to open " << filename << std::endl;
        return;
    }
    
    int index = 0;
    std::string line;
    while (std::getline(file, line) && index < *size) {
        std::istringstream iss(line);
        std::string fname, lname, uname, pword, ctype, mail, phone;
        int accNum;
        double bal;
        
        iss >> fname >> lname >> uname >> pword >> accNum >> bal >> ctype >> mail >> phone;
        
        customers[index] = new Customer(uname, pword);
        accounts[index] = new SavingsAccount(fname, lname, accNum, bal, ctype, mail, phone);
        index++;
    }
    file.close();
}

SavingsAccount::SavingsAccount(const std::string& firstname, const std::string& lastname,
                               int accountNumber, double balance, const std::string& cardtype,
                               const std::string& email, const std::string& phonenumber)
    : Account(firstname, lastname, accountNumber, balance, cardtype, email, phonenumber),
      dataFile(""), size(nullptr), customers(nullptr), accounts(nullptr) {}

int SavingsAccount::findAccount(int accountNum) {
    for (int i = 0; i < *size; i++) {
        if (accounts[i] && accounts[i]->accountNumber == accountNum) {
            return i;
        }
    }
    return -1;
}

void SavingsAccount::deposit(double amount) {
    int accountNum;
    std::cout << "\t\t\tEnter account number: ";
    std::cin >> accountNum;
    
    int idx = findAccount(accountNum);
    if (idx == -1) {
        std::cout << "\t\t\tAccount not found!\n";
        return;
    }
    
    if (customers[idx]->login()) {
        accounts[idx]->balance += amount;
        std::cout << "\t\t\tDeposit of $" << amount << " successful.\n";
        std::cout << "\t\t\tNew balance: $" << accounts[idx]->balance << std::endl;
        saveAccountData();
    }
}

void SavingsAccount::withdraw(double amount) {
    int accountNum;
    std::cout << "\t\t\tEnter account number: ";
    std::cin >> accountNum;
    
    int idx = findAccount(accountNum);
    if (idx == -1) {
        std::cout << "\t\t\tAccount not found!\n";
        return;
    }
    
    if (!customers[idx]->login()) return;
    
    if (accounts[idx]->balance < amount) {
        std::cout << "\t\t\tInsufficient balance!\n";
        std::cout << "\t\t\tCurrent balance: $" << accounts[idx]->balance << std::endl;
        std::cout << "\t\t\tEnter amount to withdraw: ";
        double newAmount;
        std::cin >> newAmount;
        withdraw(newAmount);
        return;
    }
    
    accounts[idx]->balance -= amount;
    std::cout << "\t\t\tWithdrawal of $" << amount << " successful.\n";
    std::cout << "\t\t\tNew balance: $" << accounts[idx]->balance << std::endl;
    saveAccountData();
}

void SavingsAccount::updateAccount() {
    display();
    
    int accountNum;
    std::cout << "\t\t\tEnter account number to update: ";
    std::cin >> accountNum;
    
    int idx = findAccount(accountNum);
    if (idx == -1) {
        std::cout << "\t\t\tAccount not found!\n";
        return;
    }
    
    std::cout << "\n\t\t\tCurrent Information:\n";
    std::cout << "\t\t\tName: " << accounts[idx]->firstname << " " << accounts[idx]->lastname << std::endl;
    std::cout << "\t\t\tAccount Number: " << accounts[idx]->accountNumber << std::endl;
    std::cout << "\t\t\tBalance: $" << accounts[idx]->balance << std::endl;
    
    std::string fname, lname, uname, pword, ctype, mail, phone;
    int newAccNum;
    double bal;
    
    std::cout << "\n\t\t\tEnter new details:\n";
    std::cout << "\t\t\tFirst name: "; std::cin >> fname;
    std::cout << "\t\t\tLast name: "; std::cin >> lname;
    std::cout << "\t\t\tUsername: "; std::cin >> uname;
    std::cout << "\t\t\tPassword: "; std::cin >> pword;
    std::cout << "\t\t\tCard Type: "; std::cin >> ctype;
    std::cout << "\t\t\tAccount Number: "; std::cin >> newAccNum;
    std::cout << "\t\t\tBalance: "; std::cin >> bal;
    std::cout << "\t\t\tEmail: "; std::cin >> mail;
    std::cout << "\t\t\tPhone: "; std::cin >> phone;
    
    customers[idx]->setUsername(uname);
    customers[idx]->setPassword(pword);
    accounts[idx]->setFirstName(fname);
    accounts[idx]->setLastName(lname);
    accounts[idx]->setAccountNumber(newAccNum);
    accounts[idx]->setBalance(bal);
    accounts[idx]->setCardType(ctype);
    accounts[idx]->setEmail(mail);
    accounts[idx]->setPhoneNumber(phone);
    
    std::cout << "\t\t\tAccount updated successfully!\n";
    saveAccountData();
}

void SavingsAccount::addAccount(int& sizeRef) {
    std::ofstream file(dataFile, std::ios::app);
    if (!file.is_open()) {
        std::cout << "\t\t\tFailed to open file!\n";
        return;
    }
    
    char choice;
    do {
        std::string fname, lname, uname, pword, ctype, mail, phone;
        int accNum;
        double bal;
        
        std::cout << "\n\t\t\t=== CUSTOMER ACCOUNT REGISTRATION ===\n";
        std::cout << "\t\t\tFirst name: "; std::cin >> fname;
        std::cout << "\t\t\tLast name: "; std::cin >> lname;
        std::cout << "\t\t\tUsername: "; std::cin >> uname;
        std::cout << "\t\t\tPassword: "; std::cin >> pword;
        std::cout << "\t\t\tCard Type: "; std::cin >> ctype;
        std::cout << "\t\t\tAccount Number: "; std::cin >> accNum;
        std::cout << "\t\t\tInitial Balance: "; std::cin >> bal;
        std::cout << "\t\t\tEmail: "; std::cin >> mail;
        std::cout << "\t\t\tPhone: "; std::cin >> phone;
        
        file << std::left << std::setw(20) << fname
             << std::setw(20) << lname
             << std::setw(20) << uname
             << std::setw(20) << pword
             << std::setw(20) << accNum
             << std::setw(20) << bal
             << std::setw(20) << ctype
             << std::setw(30) << mail
             << std::setw(20) << phone << std::endl;
        
        std::cout << "\t\t\tAccount registered at " << getCurrentTime() << std::endl;
        std::cout << "\t\t\tAdd another? (Y/N): ";
        std::cin >> choice;
    } while (choice == 'Y' || choice == 'y');
    
    file.close();
}

void SavingsAccount::searchAccount() {
    int accountNum;
    std::cout << "\t\t\tEnter account number: ";
    std::cin >> accountNum;
    
    int idx = findAccount(accountNum);
    if (idx == -1) {
        std::cout << "\t\t\tAccount not found!\n";
        return;
    }
    
    std::cout << "\n\t\t\t=== Account Details ===\n";
    std::cout << "\t\t\tName: " << accounts[idx]->firstname << " " << accounts[idx]->lastname << std::endl;
    std::cout << "\t\t\tUsername: " << customers[idx]->getUsername() << std::endl;
    std::cout << "\t\t\tAccount Number: " << accounts[idx]->accountNumber << std::endl;
    std::cout << "\t\t\tBalance: $" << accounts[idx]->balance << std::endl;
    std::cout << "\t\t\tCard Type: " << accounts[idx]->cardtype << std::endl;
    std::cout << "\t\t\tEmail: " << accounts[idx]->email << std::endl;
    std::cout << "\t\t\tPhone: " << accounts[idx]->phonenumber << std::endl;
}

void SavingsAccount::shiftAccountsLeft(int index) {
    for (int i = index; i < *size - 1; i++) {
        customers[i] = customers[i + 1];
        accounts[i] = accounts[i + 1];
    }
}

void SavingsAccount::deleteAccount(const std::string& filename, int& sizeRef) {
    if (!admin.login()) return;
    
    display();
    
    int accountNum;
    std::cout << "\t\t\tEnter account number to delete: ";
    std::cin >> accountNum;
    
    int idx = findAccount(accountNum);
    if (idx == -1) {
        std::cout << "\t\t\tAccount not found!\n";
        return;
    }
    
    std::cout << "\n\t\t\tAccount to be deleted:\n";
    std::cout << "\t\t\tName: " << accounts[idx]->firstname << " " << accounts[idx]->lastname << std::endl;
    std::cout << "\t\t\tAccount Number: " << accounts[idx]->accountNumber << std::endl;
    std::cout << "\t\t\tBalance: $" << accounts[idx]->balance << std::endl;
    
    char confirm;
    std::cout << "\n\t\t\tConfirm deletion? (Y/N): ";
    std::cin >> confirm;
    
    if (confirm == 'Y' || confirm == 'y') {
        delete customers[idx];
        delete accounts[idx];
        shiftAccountsLeft(idx);
        (*size)--;
        saveAccountData();
        std::cout << "\t\t\tAccount deleted at " << getCurrentTime() << std::endl;
    } else {
        std::cout << "\t\t\tDeletion cancelled.\n";
    }
}

void SavingsAccount::saveAccountData() {
    std::ofstream file(dataFile);
    if (!file.is_open()) {
        std::cout << "\t\t\tFailed to save data!\n";
        return;
    }
    
    for (int i = 0; i < *size; i++) {
        file << std::left << std::setw(20) << accounts[i]->firstname
             << std::setw(20) << accounts[i]->lastname
             << std::setw(20) << customers[i]->getUsername()
             << std::setw(20) << customers[i]->getPassword()
             << std::setw(20) << accounts[i]->accountNumber
             << std::setw(20) << accounts[i]->balance
             << std::setw(20) << accounts[i]->cardtype
             << std::setw(30) << accounts[i]->email
             << std::setw(20) << accounts[i]->phonenumber << std::endl;
    }
    file.close();
}

void SavingsAccount::display() const {
    std::cout << "\n\t\t\t=== SAVINGS ACCOUNT LIST ===\n";
    std::cout << std::left << std::setw(10) << "Type"
              << std::setw(20) << "Name"
              << std::setw(15) << "Account No"
              << std::setw(20) << "Username"
              << std::setw(15) << "Card Type"
              << std::setw(30) << "Email"
              << std::setw(15) << "Phone"
              << std::setw(15) << "Balance" << std::endl;
    std::cout << std::string(150, '=') << std::endl;
    
    for (int i = 0; i < *size; i++) {
        std::cout << std::left << std::setw(10) << "Savings"
                  << std::setw(20) << (accounts[i]->firstname + " " + accounts[i]->lastname)
                  << std::setw(15) << accounts[i]->accountNumber
                  << std::setw(20) << customers[i]->getUsername()
                  << std::setw(15) << accounts[i]->cardtype
                  << std::setw(30) << accounts[i]->email
                  << std::setw(15) << accounts[i]->phonenumber
                  << std::setw(15) << accounts[i]->balance << std::endl;
    }
}

SavingsAccount::~SavingsAccount() {
    if (customers) {
        for (int i = 0; i < *size; i++) {
            delete customers[i];
        }
        delete[] customers;
    }
    if (accounts) {
        for (int i = 0; i < *size; i++) {
            delete accounts[i];
        }
        delete[] accounts;
    }
}