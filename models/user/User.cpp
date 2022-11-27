#pragma once
#include <iostream>
#include <string>

class User
{
private:
    std::string id;
    std::string username;
    std::string password;

public:
    User() {}
    std::string getId() {
        return this->id;
    }
    void setId(std::string id) {
        this->id = id;
    }
    std::string getUsername() {
        return this->username;
    }
    void setUsername(std::string username) {
        this->username = username;
    }
    void setPassword(std::string password) {
        this->password = password;
    }
};
