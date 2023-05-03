#include <iostream>
#include <string>
#include <vector>

#include "circleintersection.h"
#include "fibonacci.h"

int main()
{
    std::vector<std::string> msg{"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const std::string& word : msg)
    {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    int n = 88;
    fibMapType fibMap;
    std::cout << "Fibonacci of " << n << " is: " << getFibonacci(fibMap, n) << std::endl;

    CircleIntersection();
}
