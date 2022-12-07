// reading a text file
#include <iostream>
#include "../models/user/User.cpp"
#include "../models/user/UserController.cpp"
#include "../commons/Validator.cpp"
#include "../app/App.cpp"

class Auth
{
private:
    void inputSignIn(std::string &username, std::string &password)
    {
        // bool check;
        do
        {
            std::cout << "Username: ";
            std::getline(std::cin, username);
            if (!Validator::check(username))
            {
                continue;
            }
            std::cout << "Password: ";
            std::getline(std::cin, password);
            if (!Validator::check(password))
            {
                continue;
            }
            break;
            /* code */
        } while (true);
    }
    void inputSignUp(std::string &username, std::string &password, std::string &confirmPassword)
    {
        this->inputSignIn(username, password);
        std::cout << "Confirm Password: ";
        std::getline(std::cin, confirmPassword);
        if (password != confirmPassword)
        {
            std::cout << "Password Does Not Match, Try again!" << std::endl;
            inputSignUp(username, password, confirmPassword);
        }
    }

public:
    void signIn(std::string &username, std::string &password)
    {
        this->inputSignIn(username, password);
        std::string userId = UserController::login(username, password);
        if(userId == "")
        {
            std::cout << "\033[1;31mUser Not Found!\033[0m" << std::endl;
            std::cin.get();
            App::session = 0;
            return;
        }
        std::cout << "\033[1;32mLogin Successfully!\033[0m" << std::endl;
        User user = UserController::findById(userId);
        user.getType() == "1" ? App::session = 1 : App::session = 2;
        App::sessionId = user.getId();
    }

    void signUp(std::string &username, std::string &password, std::string &confirmPassword)
    {
        this->inputSignUp(username, password, confirmPassword);
        UserController::create(User(username, password));
    }
};