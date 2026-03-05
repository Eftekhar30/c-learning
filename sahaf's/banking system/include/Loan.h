#ifndef LOAN_H
#define LOAN_H

#include <string>

class Loan {
protected:
    int loanNumber;
    double loanAmount;
    double interestRate;
    std::string email;
    std::string phonenumber;
    std::string firstname;
    std::string lastname;

public:
    Loan();
    Loan(const std::string& firstname, const std::string& lastname, int loanNumber,
         double loanAmount, double interestRate, const std::string& email, 
         const std::string& phonenumber);
    
    // Getters
    std::string getFirstName() const { return firstname; }
    std::string getLastName() const { return lastname; }
    int getLoanNumber() const { return loanNumber; }
    double getLoanAmount() const { return loanAmount; }
    double getInterestRate() const { return interestRate; }
    std::string getEmail() const { return email; }
    std::string getPhoneNumber() const { return phonenumber; }
    
    // Setters
    void setFirstName(const std::string& name) { firstname = name; }
    void setLastName(const std::string& name) { lastname = name; }
    void setLoanNumber(int num) { loanNumber = num; }
    void setLoanAmount(double amount) { loanAmount = amount; }
    void setInterestRate(double rate) { interestRate = rate; }
    void setEmail(const std::string& mail) { email = mail; }
    void setPhoneNumber(const std::string& phone) { phonenumber = phone; }
    
    // Pure virtual functions
    virtual void calculateInterest() = 0;
    virtual void display() = 0;
    virtual void saveLoanData() = 0;
    virtual void searchLoan() = 0;
    virtual void addLoan() = 0;
    virtual void updateLoan() = 0;
    virtual void deleteLoan(const std::string& filename, int& size) = 0;
    
    virtual ~Loan() {}
};

#endif // LOAN_H