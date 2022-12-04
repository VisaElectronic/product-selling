#pragma once
#include <iostream>
#include "../models/user/UserManager.cpp"
#include "../models/product/ProductManager.cpp"

class Database
{
public:
    static void init()
    {
        UserManager userManager(constants::USER_FILE_PATH);
        ProductManager productManager(constants::PRODUCT_FILE_PATH);
    }
};
