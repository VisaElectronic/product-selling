#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>
#include <type_traits>
#include "../commons/constant/constants.hpp"

template <typename C>
class Manager
{
private:
    std::string FILE_PATH = "";

protected:
    // get file path
    virtual std::string getStaticFilePath() = 0;
    // write to file
    // template <typename T>
    // static void write(T str, std::string FILE_PATH);
    // read from file
    static std::vector<std::string> readAll();
    // create file
    static void createFile();
    // remove file
    static bool removeFile();

    template <typename T, typename DUMMY = void>
    struct Func
    {
        static void write(T input)
        {
            C child;
            std::ofstream myfile(child.getStaticFilePath(), std::ios::app);
            if (myfile.is_open())
            {
                myfile << input << constants::DELIMITER << "\n";
                myfile.close();
            }
            else
                std::cout << "Unable to open file\n";
        }
    };

    template <typename DUMMY>
    struct Func<std::vector<std::string>, DUMMY>
    {
        static void write(std::vector<std::string> input)
        {
            C child;
            std::ofstream myfile(child.getStaticFilePath(), std::ios::app);
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
                        if (*(it + 1) == "")
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
                std::cout << "Unable to open file\n";
        }
    };

    template <typename T>
    static void write(T str) { Func<T>::write(str); }

public:
    Manager() {}
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

// template <typename C>
// template <typename T>
// void Manager<C>::write(T input, std::string FILE_PATH)
// {
//     std::ofstream myfile(FILE_PATH, std::ios::app);
//     if (myfile.is_open())
//     {
//         myfile << input << constants::DELIMITER << "\n";
//         myfile.close();
//     }
//     else
//         std::cout << "Unable to open file";
// }

// template <typename C>
// template <>
// void Manager<C>::write<std::vector<std::string>>(std::vector<std::string> input, std::string FILE_PATH)
// {
//     std::ofstream myfile(FILE_PATH, std::ios::app);
//     if (myfile.is_open())
//     {
//         for (std::vector<std::string>::iterator it = input.begin(); it != input.end(); ++it)
//         {
//             if (*it != "" && (it + 1) == input.end())
//             {
//                 myfile << *it << constants::DELIMITER << "\n";
//             }
//             else if (*it != "")
//             {
//                 myfile << *it;
//                 if (*(it + 1) == "")
//                 {
//                     myfile << constants::DELIMITER << "\n";
//                 }
//                 else
//                     myfile << "\n";
//             }
//         }
//         myfile.close();
//     }
//     else
//         std::cout << "Unable to open file";
// }

template <typename C>
std::vector<std::string> Manager<C>::readAll()
{
    C child;
    int numUsers = 0;
    std::string line;
    std::ifstream myfile(child.getStaticFilePath());
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

template <typename C>
bool Manager<C>::removeFile()
{
    C child;
    std::string FILE_PATH = child.getStaticFilePath();
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

template <typename C>
void Manager<C>::createFile()
{
    C child;
    std::ofstream createFile(child.getStaticFilePath());
}
