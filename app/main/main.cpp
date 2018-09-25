#include <iostream>
#include "sessionitem.h"

int main()
{
    std::cout << "Hello world" << std::endl;
    QVariant var(5.0);
    SessionItem item(var);

    return 0;
}

