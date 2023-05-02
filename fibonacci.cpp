#include "fibonacci.h"

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
