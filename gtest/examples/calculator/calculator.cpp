/* calculator.cpp */
#include <iostream>
#include "calculator.h"

int calculator::plus(int a, int b)
{
    std::cout << a + b << std::endl;

    return a + b;
}

int calculator::minus(int a, int b)
{
    std::cout << a - b << std::endl;

    return a - b;
}

int calculator::divide(int a, int b)
{
    std::cout << a / b << std::endl;

    return a / b;
}

int calculator::multiply(int a, int b)
{
    std::cout << a * b << std::endl;

    return a * b;
}