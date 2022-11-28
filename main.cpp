#include <iostream>
#include <fstream>
#include "commons/IOFile.cpp"
#include "app/App.cpp"

int main()
{
  App app;
  int choice;
  std::string username, password, confirmPassword;
  std::cout << "***********************************************************************\n\n\n";
  std::cout << "                      Product Selling System                               \n\n";
  std::cout << "***********************        MENU        ******************************\n\n";
  std::cout << "1.LOGIN" << std::endl;
  std::cout << "2.REGISTER" << std::endl;
  std::cout << "3.Exit" << std::endl;
  std::cout << "\nEnter your choice :";
  std::cin >> choice;
  std::cout << std::endl;
  switch (choice)
  {
  case 1:
    app.signIn(username, password);
    break;
  case 2:
    app.signUp(username, password, confirmPassword);
    app.signUp(username, password, confirmPassword);
    break;
  case 3:

    std::cout << "Thanks for using this program.\nThis program is created by @SophaVisa\n\n";
    break;
  default:
    system("clear");
    std::cout << "Invalid option, Try again..\n"
              << std::endl;
  }
  // UserModel usersModel;
  // User user = usersModel.findById("2");
  // usersModel.update(User("3", "Love Kunthea", "@@@"));

  return 0;
}