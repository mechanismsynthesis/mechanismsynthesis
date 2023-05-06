#include "fibonacci.h"

#include "doctest.h"

fibType getFibonacci(fibMapType &fibMap, int n)
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
        auto fib = getFibonacci(fibMap, n-1) + getFibonacci(fibMap, n-2);
        fibMap[n] = fib;
        return fib;
    }
}

TEST_CASE("testing the factorial function") {
    fibMapType fibMap;
    CHECK(getFibonacci(fibMap, 0) == 0);
    CHECK(getFibonacci(fibMap, 1) == 1);
    CHECK(getFibonacci(fibMap, 19) == 4181);
    CHECK(getFibonacci(fibMap, 45) == 1134903170);
    CHECK(getFibonacci(fibMap, 88) == 1100087778366101931);
}
