#include "Investment.h"

Investment::Investment() 
    : investmentID(0), firstname(""), lastname(""), investmentAmount(0.0),
      email(""), phonenumber("") {}

Investment::Investment(const std::string& firstname, const std::string& lastname,
                       int investmentID, double investmentAmount,
                       const std::string& email, const std::string& phonenumber)
    : investmentID(investmentID), firstname(firstname), lastname(lastname),
      investmentAmount(investmentAmount), email(email), phonenumber(phonenumber) {}