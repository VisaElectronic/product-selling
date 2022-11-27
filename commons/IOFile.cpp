#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>
#include <type_traits>
#include "constant/constants.hpp"

class IOFile
{
private:

public:
    IOFile() {}
    // write to file
    template <typename T>
    void write(T str, std::string FILE_PATH);
    // read from file
    std::vector<std::string> readAll(std::string FILE_PATH);
    void createFile(std::string FILE_PATH);
    // remove file
    bool removeFile(std::string FILE_PATH);
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

template <typename T>
void IOFile::write(T input, std::string FILE_PATH)
{
    std::ofstream myfile(FILE_PATH, std::ios::app);
    if (myfile.is_open())
    {
        myfile << input << constants::DELIMITER << "\n";
        myfile.close();
    }
    else
        std::cout << "Unable to open file";
}

template <>
void IOFile::write< std::vector<std::string> >(std::vector<std::string> input, std::string FILE_PATH)
{
    std::ofstream myfile(FILE_PATH, std::ios::app);
    if (myfile.is_open())
    {
        for (std::vector<std::string>::iterator it = input.begin(); it != input.end(); ++it)
        {
            if (*it != "" && (it + 1) == input.end())
            {
                myfile << *it << constants::DELIMITER << "\n";
            }
            else if (*it != "")
            {
                myfile << *it;
                if(*(it + 1) == "")
                {
                    myfile << constants::DELIMITER << "\n";
                }
                else
                    myfile << "\n";
            }
        }
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
        while (getline(myfile, line, constants::DELIMITER))
        {
            numUsers++;
            result = split_string_by_newline(line);
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

bool IOFile::removeFile(std::string FILE_PATH)
{
    const char *filename = FILE_PATH.c_str();

    // deletes the file if it exists
    int result = remove(filename);

    // check if file has been deleted successfully
    if (result != 0)
    {
        // print error message
        return false;
    }
    else
    {
        return true;
    }
}

void IOFile::createFile(std::string FILE_PATH)
{
    std::ofstream createFile(FILE_PATH);
}
