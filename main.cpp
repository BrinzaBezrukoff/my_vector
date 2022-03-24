#include <iostream>

#include "vector.h"


void vInfo(Vector& v) {
    std::cout << "Capacity: " << v.capacity() << std::endl;
    std::cout << "Size: " << v.size() << std::endl;
    std::cout << "LoadFactor: " << v.loadFactor() << std::endl;
}

void vShow(Vector& v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << ((i == v.size() - 1) ? '\n' : ',');
    }
}


int main() {

    Vector v;

    // reserve memory for 100 values, add only 6
    v.reserve(100);
    v.pushBack(10);
    v.pushFront(8);
    v.pushFront(5);
    v.pushBack(20);

    vInfo(v);
    vShow(v);

    // add 2 more values, shrink allocation to size
    v.pushBack(30);
    v.pushFront(3);
    v.shrinkToFit();

    vInfo(v);
    vShow(v);

    // test insert methods
    v.insert(15, 4);

    Value array[] = {22, 24, 26, 28};
    v.insert(array, 4, 6);

    Vector additional;
    additional.pushBack(-8);
    additional.pushBack(-5);
    additional.pushBack(-3);
    v.insert(additional, 0);

    vShow(v);

    // test find method
    std::cout << "Index of 10 (exists): " << v.find(10) << std::endl;
    std::cout << "Index of 888 (not exists): " << v.find(888) << std::endl;

    // test pop methods
    vInfo(v);
    v.popBack();
    v.popFront();
    vShow(v);
    vInfo(v);

    return 0;
}
