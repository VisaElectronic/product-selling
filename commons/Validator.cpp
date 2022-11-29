#include <iostream>
#include <string>

class Validator
{
    public:
    Validator(){}
    static bool check(std::string input)
    {
        std::size_t found;
        if (input == "")
        {
            std::cout << "Invalid Input" << std::endl;
            return false;
        }
        found = input.find('~');
        if (found!=std::string::npos)
        {
            std::cout << "Invalid Input" << std::endl;
            return false;
        }
        if (input.size() > 25)
        {
            std::cout << "Input lenght must be less than or equal 25!" << std::endl;
            return false;
        }
        return true;
    }
};