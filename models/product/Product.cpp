#pragma once
#include <iostream>
#include <string>
#include "../Model.cpp"
#include "../../app/App.cpp"

class Product: public Model
{
private:
    std::string userId;
    std::string amount;
    std::string status;
public:
    Product(): Model::Model(), userId(""), amount(""), status("") {}
    Product(std::string name, std::string amount, std::string status = "1", std::string id = "0"): Model::Model(id, name), userId(App::sessionId), amount(amount), status(status) {}
    std::string getUserId()
    {
        return this->userId;
    }
    std::string getAmount()
    {
        return this->amount;
    }
    std::string getStatus()
    {
        return this->status;
    }
};