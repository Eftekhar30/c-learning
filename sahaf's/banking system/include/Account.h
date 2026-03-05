#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
protected:
    int accountNumber;
    std::string firstname;
    std::string lastname;
    double balance;
    std::string cardtype;
    std::string email;
    std::string phonenumber;

public:
    Account();
    Account(const std::string& firstname, const std::string& lastname, 
            int accountNumber, double balance, const std::string& cardtype,
            const std::string& email, const std::string& phonenumber);
    
    // Getters
    std::string getFirstName() const { return firstname; }
    std::string getLastName() const { return lastname; }
    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    std::string getCardType() const { return cardtype; }
    std::string getEmail() const { return email; }
    std::string getPhoneNumber() const { return phonenumber; }
    
    // Setters
    void setFirstName(const std::string& name) { firstname = name; }
    void setLastName(const std::string& name) { lastname = name; }
    void setAccountNumber(int num) { accountNumber = num; }
    void setBalance(double bal) { balance = bal; }
    void setCardType(const std::string& type) { cardtype = type; }
    void setEmail(const std::string& mail) { email = mail; }
    void setPhoneNumber(const std::string& phone) { phonenumber = phone; }
    
    // Pure virtual functions
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual void display() const = 0;
    virtual void saveAccountData() = 0;
    virtual void searchAccount() = 0;
    virtual void addAccount(int& size) = 0;
    virtual void updateAccount() = 0;
    virtual void deleteAccount(const std::string& filename, int& size) = 0;
    
    virtual ~Account() {}
};

#endif