#include <iostream>
#include <string>
#include <vector>
#include "../../commons/IOFile.cpp"
#include "User.cpp"

class UserModel
{
public:
    UserModel() {}
    std::vector<User> rearrangeData(std::vector<std::string> data);
    std::vector<std::string> findAll();
};

std::vector<User> UserModel::rearrangeData(std::vector<std::string> data)
{
    std::cout << "Rearrange Data" << std::endl;
    std::vector<User> users;
    User user;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        int index = std::distance(data.begin(), it) + 1;
        std::cout << "index = " << index << std::endl;
        if(index % 4 == 1) {
            User tempUser;
            user = tempUser;
            user.setId(*it);
        }
        if(index % 4 == 2) { user.setUsername(*it); }
        if(index % 4 == 3) { user.setPassword(*it); }
        if(index % 4 == 0 || index == std::distance(data.begin(), data.end())) {
            users.push_back(user);
        }
    }
    return users;
}

std::vector<std::string> UserModel::findAll()
{
    IOFile file;
    std::vector<std::string> stream; // Empty on creation
    stream = file.readAll(constants::DATABASE_PATH);
    std::vector<User> users = this->rearrangeData(stream);
    return stream;
}
