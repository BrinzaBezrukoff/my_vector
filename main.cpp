#include <iostream>

#include "vector.h"


int main() {

    Vector v;

    // reserve memory for 100 values, add only 6
    v.reserve(100);
    v.pushBack(10);
    v.pushFront(20);
    v.pushFront(30);
    v.pushBack(40);
    std::cout << v.capacity() << std::endl;
    std::cout << v.size() << std::endl;
    std::cout << v.loadFactor() << std::endl;

    // add 2 more values, shrink allocation to size
    v.pushBack(50);
    v.pushFront(60);
    v.shrinkToFit();
    std::cout << v.capacity() << std::endl;
    std::cout << v.size() << std::endl;
    std::cout << v.loadFactor() << std::endl;

    return 0;
}
