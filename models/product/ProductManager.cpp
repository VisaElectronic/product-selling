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
    static std::vector<Product> rearrangeData(std::vector<std::string>);
    static Product *findUserById(std::vector<std::string>, std::string);
    static std::vector<std::string> searchAndRemove(std::vector<std::string>, std::string);
    static bool findAndUpdate(std::vector<std::string>, Product user);

public:
    ProductManager() {}
    ProductManager(std::string filePath)
    {
        ProductManager::filePath = filePath;
    }
    std::string getStaticFilePath()
    {
        return ProductManager::filePath;
    }
    static int countUsers();
    static std::vector<Product> findAll();
    static std::vector<Product> findAll(std::string);
    static void create(Product);
    static Product findById(std::string);
    static Product find(std::string);
    static void destroyById(std::string);
    static void update(Product);
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
        return std::stoi(stream[stream.size() - 7]) + 1;
    }
    else
        return 1;
}

std::vector<Product> ProductManager::rearrangeData(std::vector<std::string> data)
{
    std::vector<Product> users;
    std::string id, userId, name, price, amount, status;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        int index = std::distance(data.begin(), it) + 1;
        if (index % 7 == 1)
        {
            id = *it;
        }
        if (index % 7 == 2)
        {
            userId = *it;
        }
        if (index % 7 == 3)
        {
            name = *it;
        }
        if (index % 7 == 4)
        {
            price = *it;
        }
        if (index % 7 == 5)
        {
            amount = *it;
        }
        if (index % 7 == 6)
        {
            status = *it;
        }
        if (index % 7 == 0 || index == std::distance(data.begin(), data.end()))
        {
            Product prod(name, price, amount, status, userId, id);
            users.push_back(prod);
        }
    }
    return users;
}

Product *ProductManager::findUserById(std::vector<std::string> data, std::string id)
{
    std::string prodId, userId, name, price, amount, status;
    bool found = false;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        int index = std::distance(data.begin(), it) + 1;
        if (index % 7 == 1 && id == *it)
        {
            found = true;
            prodId = *it;
        }
        if (found)
        {
            if (index % 7 == 2)
            {
                userId = *it;
            }
            if (index % 7 == 3)
            {
                name = *it;
            }
            if (index % 7 == 4)
            {
                price = *it;
            }
            if (index % 7 == 5)
            {
                amount = *it;
            }
            if (index % 7 == 6)
            {
                status = *it;
            }
            if (index % 7 == 0 || index == std::distance(data.begin(), data.end()))
            {
                return new Product(name, price, amount, status, userId, prodId);
            }
        }
    }
    return NULL;
}

std::vector<std::string> ProductManager::searchAndRemove(std::vector<std::string> data, std::string id)
{
    for (std::vector<std::string>::size_type i = 0; i != data.size(); i++)
    {
        if (i % 7 == 0 && data[i] == id)
        {
            data.erase(std::next(data.begin(), i), std::next(data.begin(), i + 7));
            break;
        }
    }
    return data;
}

bool ProductManager::findAndUpdate(std::vector<std::string> data, Product prod)
{
    bool found = false;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        int index = std::distance(data.begin(), it) + 1;
        if (index % 7 == 1 && prod.getId() == *it)
        {
            found = true;
        }
        if (found)
        {
            if (index % 7 == 2)
            {
                data[index - 1] = prod.getUserId();
            }
            if (index % 7 == 3)
            {
                data[index - 1] = prod.getName();
            }
            if (index % 7 == 4)
            {
                data[index - 1] = prod.getPrice();
            }
            if (index % 7 == 5)
            {
                data[index - 1] = prod.getAmount();
            }
            if (index % 7 == 6)
            {
                data[index - 1] = prod.getStatus();
            }
            if (index % 7 == 0 || index == std::distance(data.begin(), data.end()))
            {
                if (Manager::removeFile())
                {
                    Manager::createFile();
                    Manager::write(data);
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<Product> ProductManager::findAll()
{
    std::vector<std::string> stream; // Empty on creation
    stream = Manager::readAll();
    std::vector<Product> prods = ProductManager::rearrangeData(stream);
    return prods;
}

// product belong to specific user
std::vector<Product> ProductManager::findAll(std::string sessionId)
{
    std::vector<Product> prods;
    std::vector<Product> allProds = ProductManager::findAll();
    for (auto it = allProds.begin(); it != allProds.end(); ++it)
    {
        if (it->getUserId() == sessionId)
        {
            prods.push_back(*it);
        }
        
    }
    return prods;
}

void ProductManager::create(Product product)
{
    std::vector<std::string> prod;
    prod.push_back(std::to_string(ProductManager::generateId()));
    prod.push_back(product.getUserId());
    prod.push_back(product.getName());
    prod.push_back(product.getPrice());
    prod.push_back(product.getAmount());
    prod.push_back(product.getStatus());
    Manager::write(prod);
}

Product ProductManager::findById(std::string id)
{
    Product *prodPtr = ProductManager::findUserById(Manager::readAll(), id);
    if (!prodPtr)
    {
        delete prodPtr;
        return Product();
    }
    Product prod = *prodPtr;
    delete prodPtr;
    return prod;
}

Product ProductManager::find(std::string id)
{
    bool found = false;
    Product prod;
    std::vector<Product> allProds = ProductManager::findAll(App::sessionId);
    Product *prodPtr = ProductManager::findUserById(Manager::readAll(), id);
    for (auto it = allProds.begin(); it != allProds.end(); ++it)
    {
        if (it->getId() == id)
        {
            prod = *it;
            return prod;
        }
        
    }
    return Product();
}

void ProductManager::destroyById(std::string id)
{
    std::vector<std::string> data; // Empty on creation
    data = Manager::readAll();
    data = ProductManager::searchAndRemove(data, id);
    if (Manager::removeFile())
    {
        Manager::createFile();
        Manager::write(data);
    }
}

void ProductManager::update(Product updatedProd)
{
    try
    {
        std::vector<std::string> stream; // Empty on creation
        stream = Manager::readAll();
        bool updated = ProductManager::findAndUpdate(stream, updatedProd);
        if (!updated)
        {
            throw std::invalid_argument("Product Not Found");
        }
        std::cout << "\033[1;32mProduct is updated successfully!\033[0m" << std::endl;
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
