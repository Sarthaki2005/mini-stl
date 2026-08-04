#include <iostream>
#include "vector.hpp"

int main()
{
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);

    std::cout << v[0] << '\n';
    std::cout << v[1] << '\n';
}
