#include <iostream>
#include "App.cpp"

class AdminApp : public App
{
public:
    AdminApp() {}

    void run()
    {
        std::string choiceStr;
        do
        {
            /* code */
            system("clear");
            std::cout << "***********************************************************************\n\n";
            std::cout << "                                 OPTIONS                               \n\n";
            std::cout << "***********************        ADMIN  MENU        ******************************\n\n";
            std::cout << "1.VIEW ALL USERS" << std::endl;
            std::cout << "2.LOGOUT" << std::endl;
            // std::cout << "3.Exit" << std::endl;
            std::cout << "\nEnter your choice :";
            std::getline(std::cin, choiceStr);
            std::cout << std::endl;
            switch (std::stoi(choiceStr))
            {
            case 1:
                std::cout << "View All Users" << std::endl;
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