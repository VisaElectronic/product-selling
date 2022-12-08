#include <iostream>
#include "App.cpp"
#include "../commons/constant/constants.hpp"
#include "../models/product/ProductController.cpp"
#include "../models/user/UserController.cpp"
#include "../models/booking/BookingController.cpp"

class AdminApp : public App
{
public:
    AdminApp(): App::App() {}

    void viewAllUsers()
    {
        std::cout << "\n\033[1;33m***** List Users *****\033[0m" << std::endl;
        std::vector<User> users = UserController::findAll();
        std::cout << "\033[1;32m" << std::setw(2) << "Id" << std::setw(15) << "Name" << "\033[0m" << std::endl;
        for (auto it = users.begin(); it != users.end(); ++it)
        {
            if (it->getType() != "1")
            {
                std::cout << std::setw(2) << it->getId() << std::setw(15) << it->getName() << std::endl;
            }
            
        }
        std::cin.get();
    }

    void viewAllProducts()
    {
        std::cout << "\n\033[1;33m***** List Products *****\033[0m" << std::endl;
        std::vector<Product> prods = ProductController::findAll();
        std::cout << "\033[1;32m" << std::setw(2) << "Id" << std::setw(15) << "Name" << std::setw(10) << "Price" << std::setw(10) << "Amount" << std::setw(12) << "Status" << std::setw(10) << "By" << "\033[0m" << std::endl;
        for (auto it = prods.begin(); it != prods.end(); ++it)
        {
            User user = UserController::findById(it->getUserId());
            std::cout << std::setw(2) << it->getId() << std::setw(15) << it->getName() << std::setw(10) << it->getPrice() << std::setw(10) << it->getAmount() << std::setw(12) << (it->getStatus() == "1" ? "Available" : "Sold") << std::setw(10) << user.getName() << std::endl;
        }
        std::cin.get();
    }

    void viewAllBooking()
    {
        std::cout << "\n\033[1;33m***** List Booking *****\033[0m" << std::endl;
        std::vector<Booking> bks = BookingController::findAll();
        std::cout << "\033[1;32m" << std::setw(2) << "Id" << std::setw(15) << "Product" << std::setw(10) << "Price" << std::setw(10) << "Amount" << std::setw(12) << "Buyer" << std::setw(10) << "Seller" << "\033[0m" << std::endl;
        for (auto it = bks.begin(); it != bks.end(); ++it)
        {
            User buyer = UserController::findById(it->getBuyerId());
            User seller = UserController::findById(it->getSellerId());
            Product prod = ProductController::findById(it->getProdId());
            std::cout << std::setw(2) << it->getId() << std::setw(15) << prod.getName() << std::setw(10) << it->getPrice() << std::setw(10) << it->getAmount() << std::setw(12) << buyer.getName() << std::setw(10) << seller.getName() << std::endl;
        }
        std::cin.get();
    }

    void run()
    {
        std::string choiceStr;
        do
        {
            /* code */
            system(constants::CLEAR);
            std::cout << "***********************************************************************\n\n";
            std::cout << "                                 OPTIONS                               \n\n";
            std::cout << "***********************        ADMIN  MENU        ******************************\n\n";
            std::cout << "1.VIEW ALL USERS" << std::endl;
            std::cout << "2.VIEW ALL PRODUCTS" << std::endl;
            std::cout << "3.VIEW ALL BOOKING" << std::endl;
            std::cout << "4.LOGOUT" << std::endl;
            // std::cout << "3.Exit" << std::endl;
            std::cout << "\nEnter your choice :";
            std::getline(std::cin, choiceStr);
            std::cout << std::endl;
            switch (std::stoi(choiceStr))
            {
            case 1:
                this->viewAllUsers();
                break;
            case 2:
                this->viewAllProducts();
                break;
            case 3:
                this->viewAllBooking();
                break;
            case 4:
                App::session = 0;
                App::sessionId = "";
                break;
            default:
                system(constants::CLEAR);
                std::cout << "Invalid option, Try again..\n"
                          << std::endl;
            }
        } while (choiceStr != "4");
    }
};