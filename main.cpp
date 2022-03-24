#include <iostream>

#include "vector.h"


int main() {

    Vector v;

    // reserve memory for 100 values, add only 6
    v.reserve(100);
    v.pushBack(10);
    v.pushFront(8);
    v.pushFront(5);
    v.pushBack(20);
    std::cout << v.capacity() << std::endl;
    std::cout << v.size() << std::endl;
    std::cout << v.loadFactor() << std::endl;

    // add 2 more values, shrink allocation to size
    v.pushBack(30);
    v.pushFront(3);
    v.shrinkToFit();
    std::cout << v.capacity() << std::endl;
    std::cout << v.size() << std::endl;
    std::cout << v.loadFactor() << std::endl;

    // show vector items
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << ", ";
    }
    std::cout << std::endl;

    // test insert methods
    v.insert(15, 4);

    Value array[] = {22, 24, 26, 28};
    v.insert(array, 4, 6);

    Vector additional;
    additional.pushBack(-8);
    additional.pushBack(-5);
    additional.pushBack(-3);
    v.insert(additional, 0);

    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << ", ";
    }
    std::cout << std::endl;

    return 0;
}
