#include <iostream>
#include "App.cpp"

class UserApp : public App
{
public:
    UserApp() {}

    void run()
    {
        std::string choiceStr;
        do
        {
            /* code */
            system("clear");
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