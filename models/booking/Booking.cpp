#pragma once
#include <iostream>
#include <string>
#include "../Model.cpp"
#include "../../app/App.cpp"

class Booking
{
private:
    std::string id;
    std::string buyerId;
    std::string sellerId;
    std::string prodId;
    std::string price;
    std::string amount;
public:
    Booking(): id(""), buyerId(""), sellerId(""), price(""), prodId(""), amount("") {}
    Booking(std::string buyerId, std::string sellerId, std::string prodId, std::string price, std::string amount, std::string id = "0"): buyerId(buyerId), sellerId(sellerId), price(price), prodId(prodId), amount(amount), id(id) {}
    
    std::string getId()
    {
        return this->id;
    }
    std::string getBuyerId()
    {
        return this->buyerId;
    }
    std::string getSellerId()
    {
        return this->sellerId;
    }
    std::string getPrice()
    {
        return this->price;
    }
    std::string getProdId()
    {
        return this->prodId;
    }
    std::string getAmount()
    {
        return this->amount;
    }
};