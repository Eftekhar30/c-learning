#ifndef PERSONAL_LOAN_H
#define PERSONAL_LOAN_H

#include "Loan.h"
#include "Customer.h"
#include "Admin.h"

class PersonalLoan : public Loan {
private:
    int loanDuration; // in years
    std::string dataFile;
    int* size;
    Customer** customers;
    PersonalLoan** loans;
    Admin admin;
    
    int findLoan(int loanNum);
    void shiftLoansLeft(int index);

public:
    PersonalLoan();
    PersonalLoan(const std::string& filename, int* sizePtr);
    PersonalLoan(const std::string& firstname, const std::string& lastname,
                 int loanNumber, double loanAmount, double interestRate,
                 int loanDuration, const std::string& email,
                 const std::string& phonenumber);
    
    int getLoanDuration() const { return loanDuration; }
    void setLoanDuration(int duration) { loanDuration = duration; }
    
    void calculateInterest() override;
    void display() override;
    void saveLoanData() override;
    void searchLoan() override;
    void addLoan() override;
    void updateLoan() override;
    void deleteLoan(const std::string& filename, int& size) override;
    
    ~PersonalLoan();
};

#endif