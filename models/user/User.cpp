#pragma once
#include <iostream>
#include <string>
#include "../Model.cpp"

class User: public Model
{
private:
    std::string password;
    std::string type;

public:
    User(): Model::Model(), password(""), type("0") {}
    User(std::string username, std::string password, std::string type = "0", std::string id = "0") : Model::Model(id, username), password(password), type(type) {}
    std::string getPassword() const
    {
        return this->password;
    }
    std::string getType() const
    {
        return this->type;
    }
};
