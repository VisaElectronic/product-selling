#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "../Controller.cpp"
#include "User.cpp"

class User;

class UserController: public Controller<UserController>
{
private:
    static std::string filePath;
    static int generateId();
    static std::vector<User> rearrangeData(std::vector<std::string>);
    static User *findUserById(std::vector<std::string>, std::string);
    static std::vector<std::string> searchAndRemove(std::vector<std::string>, std::string);
    static bool findAndUpdate(std::vector<std::string>, User user);

public:
    UserController(){}
    UserController(std::string filePath){
        UserController::filePath = filePath;
    }
    std::string getStaticFilePath()
    {
        return UserController::filePath;
    }
    static int countUsers();
    static std::vector<User> findAll();
    static void create(User);
    static User findById(std::string);
    static void destroyById(std::string);
    static void update(User);
    static std::string login(std::string, std::string);
};

std::string UserController::filePath = "";

int UserController::countUsers()
{
    return UserController::findAll().size();
}

int UserController::generateId()
{
    std::vector<std::string> stream = Controller::readAll();
    if (!stream.empty())
    {
        return std::stoi(stream[stream.size() - 5]) + 1;
    }
    else
        return 1;
}

std::vector<User> UserController::rearrangeData(std::vector<std::string> data)
{
    std::vector<User> users;
    std::string id, username, password;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        int index = std::distance(data.begin(), it) + 1;
        if (index % 5 == 1)
        {
            id = *it;
        }
        if (index % 5 == 2)
        {
            username = *it;
        }
        if (index % 5 == 3)
        {
            password = *it;
        }
        if (index % 5 == 0 || index == std::distance(data.begin(), data.end()))
        {
            User user(username, password);
            users.push_back(user);
        }
    }
    return users;
}

User *UserController::findUserById(std::vector<std::string> data, std::string id)
{
    std::string userId, username, password, type;
    bool found = false;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        int index = std::distance(data.begin(), it) + 1;
        if (index % 5 == 1 && id == *it)
        {
            found = true;
            userId = *it;
        }
        if (found)
        {
            if (index % 5 == 2)
            {
                username = *it;
            }
            if (index % 5 == 3)
            {
                password = *it;
            }
            if (index % 5 == 4)
            {
                type = *it;
            }
            if (index % 5 == 0 || index == std::distance(data.begin(), data.end()))
            {
                return new User(username, password, type, id=userId);
            }
        }
    }
    return NULL;
}

std::vector<std::string> UserController::searchAndRemove(std::vector<std::string> data, std::string id)
{
    for (std::vector<std::string>::size_type i = 0; i != data.size(); i++)
    {
        if (i % 5 == 0 && data[i] == id)
        {
            data.erase(std::next(data.begin(), i), std::next(data.begin(), i + 5));
            break;
        }
    }
    return data;
}

bool UserController::findAndUpdate(std::vector<std::string> data, User user)
{
    bool found = false;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        int index = std::distance(data.begin(), it) + 1;
        if (index % 5 == 1 && user.getId() == *it)
        {
            found = true;
        }
        if (found)
        {
            if (index % 5 == 2)
            {
                data[index - 1] = user.getName();
            }
            if (index % 5 == 3)
            {
                data[index - 1] = user.getPassword();
            }
            if (index % 5 == 0 || index == std::distance(data.begin(), data.end()))
            {
                // if (Controller::removeFile(constants::USER_FILE_PATH))
                // {
                //     Controller::createFile(constants::USER_FILE_PATH);
                //     Controller::write(data);
                //     return true;
                // }
            }
        }
    }
    return false;
}

std::vector<User> UserController::findAll()
{
    std::vector<std::string> stream; // Empty on creation
    stream = Controller::readAll();
    std::vector<User> users = UserController::rearrangeData(stream);
    return users;
}

void UserController::create(User user)
{
    std::vector<std::string> userVec;
    userVec.push_back(std::to_string(UserController::generateId()));
    userVec.push_back(user.getName());
    userVec.push_back(user.getPassword());
    userVec.push_back("0");
    Controller::write(userVec);
}

User UserController::findById(std::string id)
{
    User *userPtr = UserController::findUserById(Controller::readAll(), id);
    if (!userPtr)
    {
        delete userPtr;
        return User();
    }
    User user = *userPtr;
    delete userPtr;
    return user;
}

void UserController::destroyById(std::string id)
{
    std::vector<std::string> data; // Empty on creation
    data = Controller::readAll();
    data = UserController::searchAndRemove(data, id);
    // if (Controller::removeFile(constants::USER_FILE_PATH))
    // {
    //     Controller::createFile(constants::USER_FILE_PATH);
    //     Controller::write(data);
    // }
}

void UserController::update(User updatedUser)
{
    try
    {
        std::vector<std::string> stream; // Empty on creation
        stream = Controller::readAll();
        bool updated = UserController::findAndUpdate(stream, updatedUser);
        if (!updated)
        {
            throw std::invalid_argument("User Not Found");
        }
        std::cout << "User update successfully!" << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        // do stuff with exception...
        std::cout << e.what() << std::endl;
    }
}

std::string UserController::login(std::string username, std::string password)
{
    std::vector<std::string> stream = Controller::readAll();
    std::string userId, uname, psw;
    bool matchedUsername = false;
    bool matchedPassword = false;
    for (auto it = stream.begin(); it != stream.end(); ++it)
    {
        int index = std::distance(stream.begin(), it) + 1;
        if (index % 5 == 1)
        {
            userId = *it;
        }
        if (index % 5 == 2 && username == *it)
        {
            matchedUsername = true;
            uname = *it;
        }
        if (matchedUsername && index % 5 == 3 && password == *it)
        {
            matchedPassword = true;
        }
        else if(index % 5 != 2 && !matchedPassword)
        {
            matchedUsername = false;
        }
        if (matchedUsername && matchedPassword)
        {
            if (index % 5 == 0 || index == std::distance(stream.begin(), stream.end()))
            {
                return userId;
            }
        }
    }
    return "";
}
