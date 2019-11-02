#include <iostream>

class A {
    public:
        int a, b;
        double c;
};

int main(void)
{
    A myobject;
    myobject.a = 3;
    std::cout << myobject.a << std::endl;
}