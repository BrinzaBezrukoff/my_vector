#include <iostream>

#include "vector/Vector.h"


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
    std::cout << "reserve memory for 100 values, add only 6" << std::endl;
    v.reserve(100);
    v.pushBack(10);
    v.pushFront(8);
    v.pushFront(5);
    v.pushBack(20);

    vInfo(v);
    vShow(v);

    std::cout << "add 2 more values, shrink allocation to size" << std::endl;
    v.pushBack(30);
    v.pushFront(3);
    v.shrinkToFit();

    vInfo(v);
    vShow(v);

    std::cout << "test insert methods" << std::endl;
    v.insert(15, 4);

    Value array[] = {22, 24, 26, 28};
    v.insert(array, 4, 6);

    Vector additional;
    additional.pushBack(-8);
    additional.pushBack(-5);
    additional.pushBack(-3);
    v.insert(additional, 0);

    vInfo(v);
    vShow(v);

    std::cout << "test find method" << std::endl;
    std::cout << "Index of 10 (exists): " << v.find(10) << std::endl;
    std::cout << "Index of 888 (not exists): " << v.find(888) << std::endl;

    std::cout << "test pop methods" << std::endl;
    vInfo(v);
    v.popBack();
    v.popFront();
    vShow(v);
    vInfo(v);

    std::cout << "test erase methods" << std::endl;
    v.erase(1, 2);
    v.eraseBetween(6, 8);
    vShow(v);
    vInfo(v);

    std::cout << "test copy constructor" << std::endl;
    Vector v2 (v);
    vShow(v2);
    vInfo(v2);

    std::cout << "test copy assignment" << std::endl;
    v2 = v;
    vShow(v2);
    vInfo(v2);

    std::cout << "test move copy" << std::endl;
    Vector v3 (std::move(v2));
    vShow(v3);
    vInfo(v3);
    vInfo(v2);

    std::cout << "test iterators" << std::endl << "| ";
    for (auto&& value: v3) {
        std::cout << value << " | ";
    }
    std::cout << std::endl;

    return 0;
}
