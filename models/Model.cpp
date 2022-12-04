#pragma once
#include <iostream>
#include "../commons/constant/constants.hpp"

class Model
{
private:
    std::string id;
    std::string name;
public:
    Model(): id("0"), name("") {}
    Model(std::string id, std::string name): id(id), name(name) {}

    virtual std::string getId() const
    {
        return this->id;
    }

    virtual std::string getName() const
    {
        return this->name;
    }
};
