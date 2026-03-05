#ifndef STUDENT_FEE_LOAN_H
#define STUDENT_FEE_LOAN_H

#include <string>
#include "Loan.h"
#include "Customer.h"
#include "Admin.h"

class StudentFeeLoan : public Loan {
private:
    std::string enrollmentYear;
    std::string dataFile;
    int* size;
    Customer** customers;
    StudentFeeLoan** loans;
    Admin admin;
    
    int findLoan(int loanNum);
    void shiftLoansLeft(int index);

public:
    StudentFeeLoan();
    StudentFeeLoan(const std::string& filename, int* sizePtr);
    StudentFeeLoan(const std::string& firstname, const std::string& lastname,
                   int loanNumber, double loanAmount, double interestRate,
                   const std::string& enrollmentYear, const std::string& email,
                   const std::string& phonenumber);
    
    std::string getEnrollmentYear() const { return enrollmentYear; }
    void setEnrollmentYear(const std::string& year) { enrollmentYear = year; }
    
    void calculateInterest() override;
    void display() override;
    void saveLoanData() override;
    void searchLoan() override;
    void addLoan() override;
    void updateLoan() override;
    void deleteLoan(const std::string& filename, int& size) override;
    
    ~StudentFeeLoan();
};

#endif // STUDENT_FEE_LOAN_H