// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include "../commons/IOFile.cpp"

class Auth {
  private:
    const std::string USERS_FILES = "./database/users.txt";
  public:
    Auth(){}

    std::string signUp(std::string username, std::string password){
      
      return username;
    }

};