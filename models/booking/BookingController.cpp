#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "../Manager.cpp"
#include "../user/User.cpp"
#include "Booking.cpp"

class Booking;

class BookingController : public Manager<BookingController>
{
private:
    static std::string filePath;
    static int generateId();
    static std::vector<Booking> rearrangeData(std::vector<std::string>);

public:
    BookingController() {}
    BookingController(std::string filePath)
    {
        BookingController::filePath = filePath;
    }
    std::string getStaticFilePath()
    {
        return BookingController::filePath;
    }
    static std::vector<Booking> findAll();
    static void create(Booking);
    static std::vector<Booking> findByBuyerId(std::string);
    static std::vector<Booking> findBySellerId(std::string);
    static Booking findByProdId(std::string);
};

std::string BookingController::filePath = "";

int BookingController::generateId()
{
    std::vector<std::string> stream = Manager::readAll();
    if (!stream.empty())
    {
        return std::stoi(stream[stream.size() - 7]) + 1;
    }
    else
        return 1;
}

void BookingController::create(Booking bk)
{
    std::vector<std::string> prod;
    prod.push_back(std::to_string(BookingController::generateId()));
    prod.push_back(bk.getBuyerId());
    prod.push_back(bk.getSellerId());
    prod.push_back(bk.getProdId());
    prod.push_back(bk.getPrice());
    prod.push_back(bk.getAmount());
    Manager::write(prod);
}

std::vector<Booking> BookingController::findAll()
{
    std::vector<std::string> stream; // Empty on creation
    stream = Manager::readAll();
    std::vector<Booking> prods = BookingController::rearrangeData(stream);
    return prods;
}

std::vector<Booking> BookingController::rearrangeData(std::vector<std::string> data)
{
    std::vector<Booking> bookings;
    std::string id, buyerId, sellerId, price, amount, prodId;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        int index = std::distance(data.begin(), it) + 1;
        if (index % 7 == 1)
        {
            id = *it;
        }
        if (index % 7 == 2)
        {
            buyerId = *it;
        }
        if (index % 7 == 3)
        {
            sellerId = *it;
        }
        if (index % 7 == 4)
        {
            prodId = *it;
        }
        if (index % 7 == 5)
        {
            price = *it;
        }
        if (index % 7 == 6)
        {
            amount = *it;
        }
        if (index % 7 == 0 || index == std::distance(data.begin(), data.end()))
        {
            Booking prod(buyerId, sellerId, prodId, price, amount, id);
            bookings.push_back(prod);
        }
    }
    return bookings;
}

std::vector<Booking> BookingController::findByBuyerId(std::string buyerId)
{
    std::vector<Booking> bk;
    std::vector<Booking> allBk = BookingController::findAll();
    for (auto it = allBk.begin(); it != allBk.end(); ++it)
    {
        if (it->getBuyerId() == buyerId)
        {
            bk.push_back(*it);
        }
        
    }
    return bk;
}

std::vector<Booking> BookingController::findBySellerId(std::string sellerId)
{
    std::vector<Booking> bk;
    std::vector<Booking> allBk = BookingController::findAll();
    for (auto it = allBk.begin(); it != allBk.end(); ++it)
    {
        if (it->getSellerId() == sellerId)
        {
            bk.push_back(*it);
        }
        
    }
    return bk;
}

Booking BookingController::findByProdId(std::string prodId)
{
    Booking bk;
    std::vector<Booking> allBk = BookingController::findAll();
    for (auto it = allBk.begin(); it != allBk.end(); ++it)
    {
        if (it->getProdId() == prodId)
        {
            bk = *it;
            return bk;
        }
        
    }
    return bk;
}
