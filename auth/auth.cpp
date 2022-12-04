// reading a text file
#include <iostream>
#include "../models/user/User.cpp"
#include "../models/user/UserManager.cpp"
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
        std::string userId = UserManager::login(username, password);
        if(userId == "")
        {
            std::cout << "User Not Found!" << std::endl;
            return;
        }
        User user = UserManager::findById(userId);
        std::cout << "Login Successfully!" << std::endl;
        user.getType() == "1" ? App::session = 1 : App::session = 2;
        App::sessionId = user.getId();
        std::cout << "sessionId: " << user.getName() << std::endl;
    }

    void signUp(std::string &username, std::string &password, std::string &confirmPassword)
    {
        this->inputSignUp(username, password, confirmPassword);
        UserManager::create(User(username, password));
    }
};