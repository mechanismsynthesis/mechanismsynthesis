#include <map>

using fibType = unsigned long long;
using fibMapType = std::map<int, fibType>;

fibType getFibonacci(fibMapType &fibMap, int n);
