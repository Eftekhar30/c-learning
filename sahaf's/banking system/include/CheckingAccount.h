#ifndef CHECKING_ACCOUNT_H
#define CHECKING_ACCOUNT_H

#include "Account.h"
#include "Customer.h"
#include "Admin.h"

class CheckingAccount : public Account {
private:
    std::string dataFile;
    int* size;
    Customer** customers;
    CheckingAccount** accounts;
    Admin admin;
    double feeCharge;
    
    int findAccount(int accountNum);
    void shiftAccountsLeft(int index);

public:
    CheckingAccount();
    CheckingAccount(const std::string& filename, int* sizePtr);
    CheckingAccount(const std::string& firstname, const std::string& lastname,
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
    
    ~CheckingAccount();
};

#endif