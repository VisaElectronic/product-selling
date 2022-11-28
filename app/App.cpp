#include <iostream>
#include "../models/user/User.cpp"
#include "../models/user/UserModel.cpp"

class App
{
public:
    void signIn(std::string &username, std::string &password){
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;
    }

    void signUp(std::string &username, std::string &password, std::string &confirmPassword){
        this->signIn(username, password);
        std::cout << "Confirm Password: ";
        std::cin >> confirmPassword;
        if(password != confirmPassword)
        {
            std::cout << "Password Does Not Match" << std::endl;
        }
        UserModel::create(User("visa", "123456"));
    }
};