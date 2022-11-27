#include <iostream>
#include <fstream>
#include "commons/IOFile.cpp"
#include "models/user/UserModel.cpp"

int main()
{
  // int choice;
  // std::cout << "***********************************************************************\n\n\n";
  // std::cout << "                      Welcome To Sudoku Game                               \n\n";
  // std::cout << "***********************        MENU        ******************************\n\n";
  // std::cout << "1.LOGIN" << std::endl;
  // std::cout << "2.REGISTER" << std::endl;
  // std::cout << "3.Exit" << std::endl;
  // std::cout << "\nEnter your choice :";
  // std::cin >> choice;
  // std::cout << std::endl;
  // switch (choice)
  // {
  // case 1:

  //   break;
  // case 2:

  //   break;
  // case 3:

  //   std::cout << "Thanks for using this program.\nThis program is created by @SophaVisa\n\n";
  //   break;
  // default:
  //   system("clear");
  //   std::cout << "Invalid option, Try again..\n"
  //             << std::endl;
  //   main();
  // }
  UserModel usersModel;
  // User user("33", "testinguser", "hello");
  // usersModel.create(user);
  // std::vector<User> users = usersModel.findAll();
  // std::cout << users[1].getUsername() << std::endl;
  User user2 = usersModel.findById("20");
  std::cout << user2.getUsername() << std::endl;
  usersModel.destroyById("20");

  return 0;
}