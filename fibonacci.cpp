#include "fibonacci.h"

#include "doctest.h"

static std::map<int, fibType> fibMap;

fibType getFibonacci(int n)
{
    if (n <= 1)
    {
        return n;
    }
    else if (fibMap.count(n) == 1)
    {
        return fibMap[n];
    }
    else
    {
        auto fib = getFibonacci(n-1) + getFibonacci(n-2);
        fibMap[n] = fib;
        return fib;
    }
}

TEST_CASE("testing the Fibonacci function") {
    
    CHECK(getFibonacci(0) == 0);
    CHECK(getFibonacci(1) == 1);
    CHECK(getFibonacci(19) == 4181);
    CHECK(getFibonacci(45) == 1134903170);
    CHECK(getFibonacci(88) == 1100087778366101931);
}
