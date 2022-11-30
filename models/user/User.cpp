#pragma once
#include <iostream>
#include <string>

class User
{
private:
    std::string id;
    std::string username;
    std::string password;
    std::string type;

public:
    User(): id(0), username(""), password(""), type("0") {}
    User(std::string username, std::string password) : id("1"), username(username), password(password), type("0") {}
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
    std::string getType()
    {
        return this->type;
    }
};
