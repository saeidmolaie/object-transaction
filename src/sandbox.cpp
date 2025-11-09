#include <iostream>

#include "object_transaction.hpp"

int main()
{
    int x = 10;
    std::cout << x << std::endl;
    objtran::object_transaction transaction(&x);

    x = 20;
    std::cout << x << std::endl;

    transaction.rollback();
    std::cout << x << std::endl;

    return 0;
}