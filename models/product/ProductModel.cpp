#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "../../commons/IOFile.cpp"
#include "../Product.cpp"
#include "../Model.cpp"

class ProductModel: public Model
{
public:
    ProductModel() {}
    static void create(Product);
};

void ProductModel::create(Product product)
{
    IOFile file;
    std::vector<std::string> userVec;
    // userVec.push_back(std::to_string(UserModel::generateId()));
    // userVec.push_back(user.getUsername());
    // userVec.push_back(user.getPassword());
    // userVec.push_back("0");
    file.write(userVec, constants::PRODUCT_FILE_PATH);
    std::cout << "Product created successfully!" << std::endl;
}
