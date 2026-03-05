#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
    Admin();
    Admin(const std::string& username, const std::string& password);
    
    bool login() override;
    
    ~Admin() {}
};

#endif