#pragma once
#include <iostream>
#include "../models/user/UserController.cpp"
#include "../models/product/ProductController.cpp"
#include "../models/booking/BookingController.cpp"

class Database
{
public:
    static void init()
    {
        UserController UserController(constants::USER_FILE_PATH);
        ProductController ProductController(constants::PRODUCT_FILE_PATH);
        BookingController bookingController(constants::BOOKING_FILE_PATH);
    }
};
