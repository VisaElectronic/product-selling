#pragma once
#include <iostream>

class App
{
private:

public:
    // session = 1 for admin
    // session = 2 for normal user
    static int session;

    virtual void run(){};
};

int App::session = 0;