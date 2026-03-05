#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "Account.h"
#include "Customer.h"
#include "Admin.h"

class SavingsAccount : public Account {
private:
    std::string dataFile;
    int* size;  // Pointer to actual size
    Customer** customers;
    SavingsAccount** accounts;
    Admin admin;
    
    int findAccount(int accountNum);
    void shiftAccountsLeft(int index);

public:
    SavingsAccount();
    SavingsAccount(const std::string& filename, int* sizePtr);
    SavingsAccount(const std::string& firstname, const std::string& lastname,
                   int accountNumber, double balance, const std::string& cardtype,
                   const std::string& email, const std::string& phonenumber);
    
    void deposit(double amount) override;
    void withdraw(double amount) override;
    void updateAccount() override;
    void addAccount(int& size) override;
    void searchAccount() override;
    void deleteAccount(const std::string& filename, int& size) override;
    void saveAccountData() override;
    void display() const override;
    
    ~SavingsAccount();
};

#endif