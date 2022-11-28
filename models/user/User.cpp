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
    User(): id(0), username(""), password("") {}
    User(std::string username, std::string password) : id("1"), username(username), password(password) {}
    std::string getId() const
    {
        return this->id;
    }
    // void setId(std::string id)
    // {
    //     this->id = id;
    // }
    std::string getUsername()
    {
        return this->username;
    }
    // void setUsername(std::string username)
    // {
    //     this->username = username;
    // }
    std::string getPassword()
    {
        return this->password;
    }
    // void setPassword(std::string password)
    // {
    //     this->password = password;
    // }
};
