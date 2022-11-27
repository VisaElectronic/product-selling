#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "constant/constants.hpp"

class IOFile
{
private:
    // static const std::string DATABASE_PATH = "./database/database.txt"; // error because string is not integral type ?

public:
    IOFile() {}
    void write(std::string input, std::string FILE_PATH = constants::DATABASE_PATH);
    std::vector<std::string> readAll(std::string FILE_PATH = constants::DATABASE_PATH);
};

std::vector<std::string> split_string_by_newline(const std::string &str)
{
    auto result = std::vector<std::string>();
    std::stringstream ss(str);

    for (std::string line; std::getline(ss, line, '\n');)
    {
        result.push_back(line);
    }

    return result;
}

void IOFile::write(std::string input, std::string FILE_PATH)
{
    std::ofstream myfile(FILE_PATH);
    if (myfile.is_open())
    {
        myfile << input;
        myfile.close();
    }
    else
        std::cout << "Unable to open file";
}

std::vector<std::string> IOFile::readAll(std::string FILE_PATH)
{
    int numUsers = 0;
    std::string line;
    std::ifstream myfile(FILE_PATH);
    auto result = std::vector<std::string>();
    auto data = std::vector<std::string>();
    if (myfile.is_open())
    {
        while (getline(myfile, line, '@'))
        {
            numUsers++;
            result = split_string_by_newline(line);
            // if (numUsers == 1)
            // {
            //     result.insert(result.begin(), ""); // insert empty string to the frist user to justify number of elements
            // }
            for (auto it = result.begin(); it != result.end(); ++it)
            {
                int index = std::distance(result.begin(), it);
                data.push_back(*it);
            }
        }
        myfile.close();
    }
    else
        std::cout << "Unable to open file";
    return data;
}
