#include "Loan.h"

Loan::Loan() 
    : loanNumber(0), loanAmount(0.0), interestRate(0.0), 
      email(""), phonenumber(""), firstname(""), lastname("") {}

Loan::Loan(const std::string& firstname, const std::string& lastname, int loanNumber,
           double loanAmount, double interestRate, const std::string& email,
           const std::string& phonenumber)
    : loanNumber(loanNumber), loanAmount(loanAmount), interestRate(interestRate),
      email(email), phonenumber(phonenumber), firstname(firstname), lastname(lastname) {}