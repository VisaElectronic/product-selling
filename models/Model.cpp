#include <iostream>

class Model
{
public:
    Model() {}

    template <class T>
    static void create(T);
};