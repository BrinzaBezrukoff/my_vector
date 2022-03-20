#include <iostream>

#define MOD 1000000007


long fastpow(long num, long power);


int main() {

    long result = fastpow(4, 10);

    std::cout << result << std::endl;

    return 0;
}

long fastpow(long num, long power) {
    if (power == 0) {
        return 1;
    }
    if (power % 2 == 0) {
        long t = fastpow(num, power / 2);
        return t * t;
    }
    else {
        return num * fastpow(num, power - 1);
    }
}
