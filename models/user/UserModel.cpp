#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "../../commons/IOFile.cpp"
#include "User.cpp"

class User;

class UserModel
{
private:
    static int generateId();
    std::vector<User> rearrangeData(std::vector<std::string>);
    static User *findUserById(std::vector<std::string>, std::string);
    std::vector<std::string> searchAndRemove(std::vector<std::string>, std::string);
    bool findAndUpdate(std::vector<std::string>, User user);

public:
    UserModel() {}
    static int countUsers();
    std::vector<User> findAll();
    static void create(User);
    static User findById(std::string);
    void destroyById(std::string);
    void update(User);
    static std::string login(std::string, std::string);
    static std::string test();
};

int UserModel::countUsers()
{
    UserModel userModel;
    return userModel.findAll().size();
}

int UserModel::generateId()
{
    IOFile file;
    std::vector<std::string> stream = file.readAll(constants::USER_FILE_PATH);
    if (!stream.empty())
    {
        return std::stoi(stream[stream.size() - 4]) + 1;
    }
    else
        return 1;
}

std::vector<User> UserModel::rearrangeData(std::vector<std::string> data)
{
    std::vector<User> users;
    std::string id, username, password;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        int index = std::distance(data.begin(), it) + 1;
        if (index % 4 == 1)
        {
            id = *it;
        }
        if (index % 4 == 2)
        {
            username = *it;
        }
        if (index % 4 == 3)
        {
            password = *it;
        }
        if (index % 4 == 0 || index == std::distance(data.begin(), data.end()))
        {
            User user(username, password);
            users.push_back(user);
        }
    }
    return users;
}

User *UserModel::findUserById(std::vector<std::string> data, std::string id)
{
    std::string userId, username, password;
    bool found = false;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        int index = std::distance(data.begin(), it) + 1;
        if (index % 4 == 1 && id == *it)
        {
            found = true;
            userId = *it;
        }
        if (found)
        {
            if (index % 4 == 2)
            {
                username = *it;
            }
            if (index % 4 == 3)
            {
                password = *it;
            }
            if (index % 4 == 0 || index == std::distance(data.begin(), data.end()))
            {
                return new User(username, password);
            }
        }
    }
    return NULL;
}

std::vector<std::string> UserModel::searchAndRemove(std::vector<std::string> data, std::string id)
{
    for (std::vector<std::string>::size_type i = 0; i != data.size(); i++)
    {
        if (i % 4 == 0 && data[i] == id)
        {
            data.erase(std::next(data.begin(), i), std::next(data.begin(), i + 4));
            break;
        }
    }
    return data;
}

bool UserModel::findAndUpdate(std::vector<std::string> data, User user)
{
    bool found = false;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        int index = std::distance(data.begin(), it) + 1;
        if (index % 4 == 1 && user.getId() == *it)
        {
            found = true;
        }
        if (found)
        {
            if (index % 4 == 2)
            {
                data[index - 1] = user.getUsername();
            }
            if (index % 4 == 3)
            {
                data[index - 1] = user.getPassword();
            }
            if (index % 4 == 0 || index == std::distance(data.begin(), data.end()))
            {
                IOFile file;
                if (file.removeFile(constants::USER_FILE_PATH))
                {
                    file.createFile(constants::USER_FILE_PATH);
                    file.write(data, constants::USER_FILE_PATH);
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<User> UserModel::findAll()
{
    IOFile file;
    std::vector<std::string> stream; // Empty on creation
    stream = file.readAll(constants::USER_FILE_PATH);
    std::vector<User> users = this->rearrangeData(stream);
    return users;
}

void UserModel::create(User user)
{
    IOFile file;
    std::vector<std::string> userVec;
    userVec.push_back(std::to_string(UserModel::generateId()));
    userVec.push_back(user.getUsername());
    userVec.push_back(user.getPassword());
    file.write(userVec, constants::USER_FILE_PATH);
    std::cout << "User created successfully!" << std::endl;
}

User UserModel::findById(std::string id)
{
    IOFile file;
    User *userPtr = UserModel::findUserById(file.readAll(constants::USER_FILE_PATH), id);
    if (!userPtr)
    {
        delete userPtr;
        return User();
    }
    User user = *userPtr;
    delete userPtr;
    return user;
}

void UserModel::destroyById(std::string id)
{
    IOFile file;
    std::vector<std::string> data; // Empty on creation
    data = file.readAll(constants::USER_FILE_PATH);
    data = this->searchAndRemove(data, id);
    if (file.removeFile(constants::USER_FILE_PATH))
    {
        file.createFile(constants::USER_FILE_PATH);
        file.write(data, constants::USER_FILE_PATH);
    }
}

void UserModel::update(User updatedUser)
{
    try
    {
        IOFile file;
        std::vector<std::string> stream; // Empty on creation
        stream = file.readAll(constants::USER_FILE_PATH);
        bool updated = this->findAndUpdate(stream, updatedUser);
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

std::string UserModel::login(std::string username, std::string password)
{
    IOFile file;
    std::vector<std::string> stream = file.readAll(constants::USER_FILE_PATH);
    std::string userId, uname, psw;
    bool matchedUsername = false;
    bool matchedPassword = false;
    for (auto it = stream.begin(); it != stream.end(); ++it)
    {
        int index = std::distance(stream.begin(), it) + 1;
        if (index % 4 == 1)
        {
            userId = *it;
        }
        if (index % 4 == 2 && username == *it)
        {
            matchedUsername = true;
            uname = *it;
        }
        if (matchedUsername && index % 4 == 3 && password == *it)
        {
            matchedPassword = true;
        }
        else if(index % 4 != 2 && !matchedPassword)
        {
            matchedUsername = false;
        }
        if (matchedUsername && matchedPassword)
        {
            if (index % 4 == 0 || index == std::distance(stream.begin(), stream.end()))
            {
                return userId;
            }
        }
    }
    return "";
}

std::string UserModel::test()
{
    std::cout << "test" <<std::endl;
    return "";
}
