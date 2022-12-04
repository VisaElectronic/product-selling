#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "../Manager.cpp"
#include "../user/User.cpp"
#include "Product.cpp"

class Product;

class ProductManager : public Manager<ProductManager>
{
private:
    static std::string filePath;
    static int generateId();
    static std::vector<User> rearrangeData(std::vector<std::string>);
    static User *findUserById(std::vector<std::string>, std::string);
    static std::vector<std::string> searchAndRemove(std::vector<std::string>, std::string);
    static bool findAndUpdate(std::vector<std::string>, User user);

public:
    ProductManager(){}
    ProductManager(std::string filePath) {
        ProductManager::filePath = filePath;
    }
    std::string getStaticFilePath()
    {
        return ProductManager::filePath;
    }
    static int countUsers();
    static std::vector<User> findAll();
    static void create(Product);
    static User findById(std::string);
    static void destroyById(std::string);
    static void update(User);
    static std::string login(std::string, std::string);
};

std::string ProductManager::filePath = "";

int ProductManager::countUsers()
{
    return ProductManager::findAll().size();
}

int ProductManager::generateId()
{
    std::vector<std::string> stream = Manager::readAll();
    if (!stream.empty())
    {
        return std::stoi(stream[stream.size() - 6]) + 1;
    }
    else
        return 1;
}

std::vector<User> ProductManager::rearrangeData(std::vector<std::string> data)
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

User *ProductManager::findUserById(std::vector<std::string> data, std::string id)
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
                return new User(username, password, type);
            }
        }
    }
    return NULL;
}

std::vector<std::string> ProductManager::searchAndRemove(std::vector<std::string> data, std::string id)
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

bool ProductManager::findAndUpdate(std::vector<std::string> data, User user)
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
                if (Manager::removeFile(constants::USER_FILE_PATH))
                {
                    Manager::createFile(constants::USER_FILE_PATH);
                    Manager::write(data);
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<User> ProductManager::findAll()
{
    std::vector<std::string> stream; // Empty on creation
    stream = Manager::readAll();
    std::vector<User> users = ProductManager::rearrangeData(stream);
    return users;
}

void ProductManager::create(Product product)
{
    std::vector<std::string> prod;
    prod.push_back(std::to_string(ProductManager::generateId()));
    prod.push_back(product.getUserId());
    prod.push_back(product.getName());
    prod.push_back(product.getAmount());
    prod.push_back(product.getStatus());
    Manager::write(prod);
    std::cout << "Product is created successfully!" << std::endl;
}

User ProductManager::findById(std::string id)
{
    User *userPtr = ProductManager::findUserById(Manager::readAll(), id);
    if (!userPtr)
    {
        delete userPtr;
        return User();
    }
    User user = *userPtr;
    delete userPtr;
    return user;
}

void ProductManager::destroyById(std::string id)
{
    std::vector<std::string> data; // Empty on creation
    data = Manager::readAll();
    data = ProductManager::searchAndRemove(data, id);
    if (Manager::removeFile(constants::USER_FILE_PATH))
    {
        Manager::createFile(constants::USER_FILE_PATH);
        Manager::write(data);
    }
}

void ProductManager::update(User updatedUser)
{
    try
    {
        std::vector<std::string> stream; // Empty on creation
        stream = Manager::readAll();
        bool updated = ProductManager::findAndUpdate(stream, updatedUser);
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

std::string ProductManager::login(std::string username, std::string password)
{
    std::vector<std::string> stream = Manager::readAll();
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
        else if (index % 5 != 2 && !matchedPassword)
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
