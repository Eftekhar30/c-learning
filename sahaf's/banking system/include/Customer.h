#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"

class Customer : public User {
public:
    Customer();
    Customer(const std::string& username, const std::string& password);
    
    bool login() override;
    
    ~Customer() {}
};

#endif