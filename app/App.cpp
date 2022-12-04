#pragma once
#include <iostream>

class App
{
public:
    App(){}
    // session = 1 for admin
    // session = 2 for normal user
    static int session;
    static std::string sessionId;

    virtual void run(){};
};

int App::session = 0;
std::string App::sessionId = "";