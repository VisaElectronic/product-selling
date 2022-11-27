#include <iostream>
#include <string>
#include <vector>
#include "../../commons/IOFile.cpp"
#include "User.cpp"

class UserModel
{
private:
    std::vector<User> rearrangeData(std::vector<std::string>);
    User* findUserById(std::vector<std::string>, std::string);
    std::vector<std::string> searchAndRemove(std::vector<std::string>, std::string);

public:
    UserModel() {}
    void create(User);
    std::vector<User> findAll();
    User findById(std::string);
    void destroyById(std::string);
};

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
            User user(id, username, password);
            users.push_back(user);
        }
    }
    return users;
}

User* UserModel::findUserById(std::vector<std::string> data, std::string id)
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
                return new User(id, username, password);
            }
        }
    }
    return NULL;
}

std::vector<std::string> UserModel::searchAndRemove(std::vector<std::string> data, std::string id)
{
    for(std::vector<std::string>::size_type i = 0; i != data.size(); i++) {
        if (i % 4 == 0 && data[i] == id)
        {
            data.erase(std::next(data.begin(), i), std::next(data.begin(), i + 4));
            break;
        }
    }
    return data;
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
    userVec.push_back(user.getId());
    userVec.push_back(user.getUsername());
    userVec.push_back(user.getPassword());
    file.write(userVec, constants::USER_FILE_PATH);
    std::cout << "User created successfully!" << std::endl;
}

User UserModel::findById(std::string id)
{
    IOFile file;
    User* userPtr = this->findUserById(file.readAll(constants::USER_FILE_PATH), id);
    if(!userPtr) {
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
    if(file.removeFile(constants::USER_FILE_PATH))
    {
        file.createFile(constants::USER_FILE_PATH);
        file.write(data, constants::USER_FILE_PATH);
    }
}
