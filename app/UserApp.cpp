#include <iostream>
#include "App.cpp"
#include "../models/product/Product.cpp"
#include "../models/product/ProductManager.cpp"

class UserApp : public App
{
public:
    UserApp() : App::App() {}

    void run()
    {
        std::string choiceStr;
        std::string prodName, userId, amount, status;
        do
        {
            /* code */
            // system("clear");
            std::cout << "***********************************************************************\n\n";
            std::cout << "                                OPTIONS                               \n\n";
            std::cout << "***********************        USER  MENU        ******************************\n\n";
            std::cout << "1.ADD PRODUCT" << std::endl;
            std::cout << "2.LOGOUT" << std::endl;
            // std::cout << "3.Exit" << std::endl;
            std::cout << "\nEnter your choice :";
            std::getline(std::cin, choiceStr);
            std::cout << std::endl;
            switch (std::stoi(choiceStr))
            {
            case 1:
                std::cout << "Add Product" << std::endl;

                std::cout << "Product Name: ";
                std::getline(std::cin, prodName);
                std::cout << "Product Amount: ";
                std::getline(std::cin, amount);

                ProductManager::create(Product(prodName, amount));
                break;
            case 2:
                std::cout << "Log Out!" << std::endl;
                break;
            default:
                system("clear");
                std::cout << "Invalid option, Try again..\n"
                          << std::endl;
            }
        } while (choiceStr != "2");
    }
};
