#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string username;
    std::string password;

public:
    User();
    User(const std::string& username, const std::string& password);
    
    virtual bool login() = 0; // Pure virtual
    void changePassword();
    
    // Getters
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    
    // Setters
    void setUsername(const std::string& name) { username = name; }
    void setPassword(const std::string& pass) { password = pass; }
    
    virtual ~User() {}
};

#endif