#include <iostream>
#include <fstream>
#include <string>
#include "auth/Auth.cpp"
#include "app/App.cpp"
#include "app/AdminApp.cpp"
#include "app/UserApp.cpp"
#include "database/Database.cpp"

int main()
{
  App* app;
  Auth auth;
  Database::init();
  std::string choiceStr;
  do
  {
    /* code */
    std::string username, password, confirmPassword;
    std::cout << "***********************************************************************\n\n\n";
    std::cout << "                      Product Selling System                               \n\n";
    std::cout << "***********************        MENU        ******************************\n\n";
    std::cout << "1.LOGIN" << std::endl;
    std::cout << "2.REGISTER" << std::endl;
    std::cout << "3.Exit" << std::endl;
    std::cout << "\nEnter your choice :";
    std::getline(std::cin, choiceStr);
    std::cout << std::endl;
    switch (std::stoi(choiceStr))
    {
    case 1:
      auth.signIn(username, password);
      if (App::session == 1)
      {
        AdminApp adminApp;
        app = &adminApp;
        app->run();
      }
      else if (App::session == 2)
      {
        UserApp userApp;
        app = &userApp;
        app->run();
      }
      break;
    case 2:
      auth.signUp(username, password, confirmPassword);
      // app.signUp(username, password, confirmPassword);
      break;
    case 3:

      std::cout << "Thanks for using this program.\nThis program is created by @SophaVisa\n\n";
      break;
    default:
      system("clear");
      std::cout << "Invalid option, Try again..\n"
                << std::endl;
    }
  } while (choiceStr != "3");

  return 0;
}