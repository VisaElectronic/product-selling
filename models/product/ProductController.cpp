#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "../Controller.cpp"
#include "../user/User.cpp"
#include "Product.cpp"

class Product;

class ProductController : public Controller<ProductController>
{
private:
    static std::string filePath;
    static int generateId();
    static std::vector<Product> rearrangeData(std::vector<std::string>);
    static Product *findUserById(std::vector<std::string>, std::string);
    static std::vector<std::string> searchAndRemove(std::vector<std::string>, std::string);
    static bool findAndUpdate(std::vector<std::string>, Product user);

public:
    ProductController() {}
    ProductController(std::string filePath)
    {
        ProductController::filePath = filePath;
    }
    std::string getStaticFilePath()
    {
        return ProductController::filePath;
    }
    static int countUsers();
    static std::vector<Product> findAll();
    static std::vector<Product> findAll(std::string);
    static std::vector<Product> findOtherAll(std::string);
    static void create(Product);
    static Product findById(std::string);
    static Product find(std::string);
    static void destroyById(std::string);
    static void update(Product);
};

std::string ProductController::filePath = "";

int ProductController::countUsers()
{
    return ProductController::findAll().size();
}

int ProductController::generateId()
{
    std::vector<std::string> stream = Controller::readAll();
    if (!stream.empty())
    {
        return std::stoi(stream[stream.size() - 7]) + 1;
    }
    else
        return 1;
}

std::vector<Product> ProductController::rearrangeData(std::vector<std::string> data)
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

Product *ProductController::findUserById(std::vector<std::string> data, std::string id)
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

std::vector<std::string> ProductController::searchAndRemove(std::vector<std::string> data, std::string id)
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

bool ProductController::findAndUpdate(std::vector<std::string> data, Product prod)
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
                if (Controller::removeFile())
                {
                    Controller::createFile();
                    Controller::write(data);
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<Product> ProductController::findAll()
{
    std::vector<std::string> stream; // Empty on creation
    stream = Controller::readAll();
    std::vector<Product> prods = ProductController::rearrangeData(stream);
    return prods;
}

// product belong to specific user
std::vector<Product> ProductController::findAll(std::string sessionId)
{
    std::vector<Product> prods;
    std::vector<Product> allProds = ProductController::findAll();
    for (auto it = allProds.begin(); it != allProds.end(); ++it)
    {
        if (it->getUserId() == sessionId)
        {
            prods.push_back(*it);
        }
        
    }
    return prods;
}

std::vector<Product> ProductController::findOtherAll(std::string sessionId)
{
    std::vector<Product> prods;
    std::vector<Product> allProds = ProductController::findAll();
    for (auto it = allProds.begin(); it != allProds.end(); ++it)
    {
        if (it->getUserId() != sessionId)
        {
            prods.push_back(*it);
        }
        
    }
    return prods;
}

void ProductController::create(Product product)
{
    std::vector<std::string> prod;
    prod.push_back(std::to_string(ProductController::generateId()));
    prod.push_back(product.getUserId());
    prod.push_back(product.getName());
    prod.push_back(product.getPrice());
    prod.push_back(product.getAmount());
    prod.push_back(product.getStatus());
    Controller::write(prod);
}

Product ProductController::findById(std::string id)
{
    Product *prodPtr = ProductController::findUserById(Controller::readAll(), id);
    if (!prodPtr)
    {
        delete prodPtr;
        return Product();
    }
    Product prod = *prodPtr;
    delete prodPtr;
    return prod;
}

Product ProductController::find(std::string id)
{
    bool found = false;
    Product prod;
    std::vector<Product> allProds = ProductController::findAll(App::sessionId);
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

void ProductController::destroyById(std::string id)
{
    std::vector<std::string> data; // Empty on creation
    data = Controller::readAll();
    data = ProductController::searchAndRemove(data, id);
    if (Controller::removeFile())
    {
        Controller::createFile();
        Controller::write(data);
    }
}

void ProductController::update(Product updatedProd)
{
    try
    {
        std::vector<std::string> stream; // Empty on creation
        stream = Controller::readAll();
        bool updated = ProductController::findAndUpdate(stream, updatedProd);
        if (!updated)
        {
            throw std::invalid_argument("Product Not Found");
        }
    }
    catch (const std::invalid_argument &e)
    {
        // do stuff with exception...
        std::cout << e.what() << std::endl;
    }
}
