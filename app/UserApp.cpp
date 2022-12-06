#include <iostream>
#include <iomanip>
#include "App.cpp"
#include "../models/product/Product.cpp"
#include "../models/product/ProductManager.cpp"

class UserApp : public App
{
public:
    UserApp() : App::App() {}

    void addProduct()
    {
        do
        {
            /* code */
            std::cout << "\n\033[1;33m***** Add Product *****\033[0m" << std::endl;
            std::string prodName, price, amount;
            std::cout << "Add Product (press e + enter to exit)" << std::endl;

            std::cout << "Product Name: ";
            std::getline(std::cin, prodName);
            if (prodName == "e")
            {
                break;
            }
            std::cout << "Product Price: ";
            std::getline(std::cin, price);
            if (price == "e")
            {
                break;
            }
            std::cout << "Product Amount: ";
            std::getline(std::cin, amount);
            if (amount == "e")
            {
                break;
            }
            system(constants::CLEAR);
            if (prodName == "" || price == "" || amount == "")
            {
                std::cout << "\033[1;31mInput can not empty!\033[0m" << std::endl;
                std::cin.get();
                continue;
            }

            ProductManager::create(Product(prodName, price, amount));
            std::cout << "\033[1;32mProduct is added successfully!\033[0m" << std::endl;
            std::cin.get();
            break;
        } while (true);
    }

    void listProducts()
    {
        std::cout << "List Product: " << std::endl;
        std::vector<Product> prods = ProductManager::findAll(App::sessionId);
        std::cout << std::setw(2) << "Id" << std::setw(15) << "Name" << std::setw(10) << "Amount" << std::endl;
        for (auto it = prods.begin(); it != prods.end(); ++it)
        {
            std::cout << std::setw(2) << it->getId() << std::setw(15) << it->getName() << std::setw(10) << it->getAmount() << std::endl;
        }
    }

    void viewProduct()
    {
        std::string prodId;
        Product prod;
        do
        {
            this->listProducts();
            std::cout << "\nEnter Product Id (press e to exit): ";
            std::getline(std::cin, prodId);
            if (prodId == "e")
            {
                break;
            }
            system(constants::CLEAR);
            prod = ProductManager::find(prodId);
            if (prod.getId() != "0")
            {
                std::cout << std::setw(2) << "Id" << std::setw(15) << "Name" << std::setw(10) << "Price" << std::setw(10) << "Amount" << std::setw(12) << "Status" << std::endl;
                std::cout << "\033[1;32m" << std::setw(2) << prod.getId() << std::setw(15) << prod.getName() << std::setw(10) << prod.getPrice() << std::setw(10) << prod.getAmount() << std::setw(12) << (prod.getStatus() == "1" ? "Available" : "Sold") << "\033[0m" << std::endl;
                // std::cin.ignore();
            }
            else
            {
                std::cout << "\033[1;31mProduct Not Found\033[0m" << std::endl;
            }
            std::cin.get();
            /* code */
        } while (true);
    }

    void editProduct()
    {
        std::string prodId;
        Product prod;
        do
        {
            this->listProducts();
            std::cout << "\n\033[1;33m***** Edit Product *****\033[0m" << std::endl;
            std::cout << "Enter Product Id (press e to exit): ";
            std::getline(std::cin, prodId);
            if (prodId == "e")
            {
                break;
            }
            system(constants::CLEAR);
            prod = ProductManager::find(prodId);
            if (prod.getId() != "0")
            {
                std::cout << std::setw(2) << "Id" << std::setw(15) << "Name" << std::setw(10) << "Price" << std::setw(10) << "Amount" << std::setw(12) << "Status" << std::endl;
                std::cout << "\033[1;32m" << std::setw(2) << prod.getId() << std::setw(15) << prod.getName() << std::setw(10) << prod.getPrice() << std::setw(10) << prod.getAmount() << std::setw(12) << (prod.getStatus() == "1" ? "Available" : "Sold") << "\033[0m" << std::endl;
                std::string prodName, price, amount;
                std::cout << "Product New Name: ";
                std::getline(std::cin, prodName);
                std::cout << "Product New Price: ";
                std::getline(std::cin, price);
                std::cout << "Product New Amount: ";
                std::getline(std::cin, amount);
                if (prodName == "")
                {
                    prodName = prod.getName();
                }
                if (price == "")
                {
                    price = prod.getPrice();
                }
                if (amount == "")
                {
                    amount = prod.getAmount();
                }
                ProductManager::update(Product(prodName, price, amount, "1", App::sessionId, prodId));
            }
            else
            {
                std::cout << "\033[1;31mProduct Not Found\033[0m" << std::endl;
            }
            std::cin.get();
            /* code */
        } while (true);
    }

    void deleteProduct()
    {
        std::string prodId;
        Product prod;
        do
        {
            this->listProducts();
            std::cout << "\n\033[1;33m***** Delete Product *****\033[0m" << std::endl;
            std::cout << "Enter Product Id (press e to exit): ";
            std::getline(std::cin, prodId);
            if (prodId == "e")
            {
                break;
            }
            system(constants::CLEAR);
            prod = ProductManager::find(prodId);
            if (prod.getId() != "0")
            {
                ProductManager::destroyById(prodId);
                std::cout << "\033[1;32mProduct is deleted successfully!\033[0m" << std::endl;
            }
            else
            {
                std::cout << "\033[1;31mProduct Not Found\033[0m" << std::endl;
            }
            std::cin.get();
            /* code */
        } while (true);
    }

    void run()
    {
        std::string choiceStr;
        std::string prodName, price, userId, amount, status;
        do
        {
            /* code */
            system(constants::CLEAR);
            std::cout << "\n***********************     \033[1;32mUSER  MENU\033[0m     ******************************\n\n";
            std::cout << "1.ADD PRODUCT" << std::endl;
            std::cout << "2.VIEW PRODUCT" << std::endl;
            std::cout << "3.EDIT PRODUCT" << std::endl;
            std::cout << "4.DELETE PRODUCT" << std::endl;
            std::cout << "5.LOGOUT" << std::endl;
            // std::cout << "3.Exit" << std::endl;
            std::cout << "\nEnter your choice :";
            std::getline(std::cin, choiceStr);
            std::cout << std::endl;
            switch (std::stoi(choiceStr))
            {
            case 1:
                this->addProduct();
                break;
            case 2:
                this->viewProduct();
                break;
            case 3:
                this->editProduct();
                break;
            case 4:
                this->deleteProduct();
                break;
            case 5:
                system(constants::CLEAR);
                break;
            default:
                system(constants::CLEAR);
                std::cout << "Invalid option, Try again..\n"
                          << std::endl;
            }
        } while (choiceStr != "5");
    }
};
