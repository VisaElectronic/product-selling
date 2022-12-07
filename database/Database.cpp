#pragma once
#include <iostream>
#include "../models/user/UserManager.cpp"
#include "../models/product/ProductManager.cpp"
#include "../models/booking/BookingController.cpp"

class Database
{
public:
    static void init()
    {
        UserManager userManager(constants::USER_FILE_PATH);
        ProductManager productManager(constants::PRODUCT_FILE_PATH);
        BookingController bookingController(constants::BOOKING_FILE_PATH);
    }
};
