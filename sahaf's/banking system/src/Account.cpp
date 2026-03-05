#include "Account.h"

Account::Account() 
    : accountNumber(0), firstname(""), lastname(""), balance(0.0),
      cardtype(""), email(""), phonenumber("") {}

Account::Account(const std::string& firstname, const std::string& lastname,
                 int accountNumber, double balance, const std::string& cardtype,
                 const std::string& email, const std::string& phonenumber)
    : accountNumber(accountNumber), firstname(firstname), lastname(lastname),
      balance(balance), cardtype(cardtype), email(email), phonenumber(phonenumber) {}