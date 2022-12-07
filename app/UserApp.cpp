#include <iostream>
#include <iomanip>
#include "App.cpp"
#include "../models/product/Product.cpp"
#include "../models/product/ProductManager.cpp"
#include "../models/user/UserManager.cpp"
#include "../models/booking/BookingController.cpp"

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
        std::cout << "List Products: " << std::endl;
        std::vector<Product> prods = ProductManager::findAll(App::sessionId);
        std::cout << std::setw(2) << "Id" << std::setw(15) << "Name" << std::setw(10) << "Amount" << std::endl;
        for (auto it = prods.begin(); it != prods.end(); ++it)
        {
            std::cout << std::setw(2) << it->getId() << std::setw(15) << it->getName() << std::setw(10) << it->getAmount() << std::endl;
        }
    }

    void listOtherProducts()
    {
        std::cout << "List Other Products: " << std::endl;
        std::vector<Product> prods = ProductManager::findOtherAll(App::sessionId);
        std::cout << "\033[1;34m" << std::setw(2) << "Id" << std::setw(15) << "Name" << std::setw(10) << "Price" << std::setw(10) << "Amount" << std::setw(12) << "Status" << "\033[0m" << std::endl;
        for (auto it = prods.begin(); it != prods.end(); ++it)
        {
            std::cout << std::setw(2) << it->getId() << std::setw(15) << it->getName() << std::setw(10) << it->getPrice() << std::setw(10) << it->getAmount() << std::setw(12) << (it->getAmount() != "0" ? "Available" : "Sold") << std::endl;
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
                std::cout << "\033[1;32mProduct is updated successfully!\033[0m" << std::endl;
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
                Booking bookProd = BookingController::findByProdId(prodId);
                if (bookProd.getId() != "")
                {
                    std::cout << "\033[1;31mProduct is booked! Can not delete!\033[0m" << std::endl;
                    std::cin.get();
                    continue;
                }
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

    void bookProduct()
    {
        std::string prodId;
        std::string amount;
        Product prod;
        do
        {
            system(constants::CLEAR);
            this->listOtherProducts();
            std::cout << "\n\033[1;33m***** Book Product *****\033[0m" << std::endl;
            std::cout << "\nEnter Product Id (press e to exit): ";
            std::getline(std::cin, prodId);
            if (prodId == "e")
            {
                break;
            }
            prod = ProductManager::findById(prodId);
            if (prod.getId() != "0")
            {
                std::cout << "Enter amount to book: ";
                std::getline(std::cin, amount);
                if (std::stoi(amount) <= std::stoi(prod.getAmount()))
                {
                    int amt = std::stoi(prod.getAmount()) - std::stoi(amount);
                    ProductManager::update(Product(prod.getName(), prod.getPrice(), std::to_string(amt), "1", prod.getUserId(), prodId));
                    BookingController::create(Booking(App::sessionId, prod.getUserId(), prod.getId(), prod.getPrice(), amount));
                    std::cout << "\033[1;32mBooked product successfully!\033[0m" << std::endl;
                }
                else
                {
                    std::cout << "\033[1;31mNot enough product amount!\033[0m" << std::endl;
                }
            }
            else
            {
                std::cout << "\033[1;31mProduct Not Found\033[0m" << std::endl;
            }
            std::cin.get();
            /* code */
        } while (true);
    }

    void showMyBookingProducts()
    {
        system(constants::CLEAR);
        std::cout << "\n\033[1;33m***** I Booked The Products *****\033[0m\n" << std::endl;
        std::vector<Booking> allBk = BookingController::findByBuyerId(App::sessionId);
        std::cout << "\033[1;34m" << std::setw(2) << "Id" << std::setw(15) << "Name" << std::setw(10) << "Price" << std::setw(10) << "Amount" << std::setw(12) << "Seller"  << "\033[0m" << std::endl;
        for (auto it = allBk.begin(); it != allBk.end(); ++it)
        {
            User user = UserManager::findById(it->getSellerId());
            Product prod = ProductManager::findById(it->getProdId());
            std::cout << std::setw(2) << it->getId() << std::setw(15) << prod.getName() << std::setw(10) << it->getPrice() << std::setw(10) << it->getAmount() << std::setw(12) << user.getName() << std::endl;
        }
        std::cin.get();
    }

    void showBookedProducts()
    {
        system(constants::CLEAR);
        std::cout << "\n\033[1;33m***** Someone Booked Our Product *****\033[0m\n" << std::endl;
        std::vector<Booking> allBk = BookingController::findBySellerId(App::sessionId);
        std::cout << "\033[1;34m" << std::setw(2) << "Id" << std::setw(15) << "Name" << std::setw(10) << "Price" << std::setw(10) << "Amount" << std::setw(12) << "Buyer"  << "\033[0m" << std::endl;
        for (auto it = allBk.begin(); it != allBk.end(); ++it)
        {
            User user = UserManager::findById(it->getBuyerId());
            Product prod = ProductManager::findById(it->getProdId());
            std::cout << std::setw(2) << it->getId() << std::setw(15) << prod.getName() << std::setw(10) << it->getPrice() << std::setw(10) << it->getAmount() << std::setw(12) << user.getName() << std::endl;
        }
        std::cin.get();
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
            std::cout << "2.VIEW MY PRODUCTS" << std::endl;
            std::cout << "3.EDIT PRODUCT" << std::endl;
            std::cout << "4.DELETE PRODUCT" << std::endl;
            std::cout << "5.BOOK PRODUCT" << std::endl;
            std::cout << "6.MY BOOKING PRODUCT" << std::endl;
            std::cout << "7.BOOKED PRODUCT" << std::endl;
            std::cout << "8.LOGOUT" << std::endl;
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
                this->bookProduct();
                break;
            case 6:
                this->showMyBookingProducts();
                break;
            case 7:
                // list record of other book our product 
                this->showBookedProducts();
                break;
            case 8:
                system(constants::CLEAR);
                break;
            default:
                system(constants::CLEAR);
                std::cout << "Invalid option, Try again..\n"
                          << std::endl;
            }
        } while (choiceStr != "8");
    }
};
