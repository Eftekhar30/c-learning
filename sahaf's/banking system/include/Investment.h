#ifndef INVESTMENT_H
#define INVESTMENT_H

#include <string>

class Investment {
protected:
    int investmentID;
    std::string firstname;
    std::string lastname;
    double investmentAmount;
    std::string email;
    std::string phonenumber;

public:
    Investment();
    Investment(const std::string& firstname, const std::string& lastname, 
               int investmentID, double investmentAmount, 
               const std::string& email, const std::string& phonenumber);
    
    // Getters
    std::string getFirstName() const { return firstname; }
    std::string getLastName() const { return lastname; }
    int getInvestmentID() const { return investmentID; }
    double getInvestmentAmount() const { return investmentAmount; }
    std::string getEmail() const { return email; }
    std::string getPhoneNumber() const { return phonenumber; }
    
    // Setters
    void setFirstName(const std::string& name) { firstname = name; }
    void setLastName(const std::string& name) { lastname = name; }
    void setInvestmentID(int id) { investmentID = id; }
    void setInvestmentAmount(double amount) { investmentAmount = amount; }
    void setEmail(const std::string& mail) { email = mail; }
    void setPhoneNumber(const std::string& phone) { phonenumber = phone; }
    
    // Pure virtual functions
    virtual void calculateReturns() = 0;
    virtual void display() = 0;
    virtual void searchInvestment() = 0;
    virtual void saveData() = 0;
    virtual void addInvestment() = 0;
    virtual void deleteInvestment(const std::string& filename, int& size) = 0;
    virtual void updateInvestment() = 0;
    
    virtual ~Investment() {}
};

#endif