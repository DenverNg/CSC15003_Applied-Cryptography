#include <iostream>
#include "bigint.h"  // Sử dụng thư viện bigint

using namespace std;

bool millerRabinTest(bigint d, bigint n) {
    bigint a = 2 + rand() % (stoi(n.str) - 4);  // Chọn số ngẫu nhiên a trong khoảng [2, n-2]
    bigint x = bigint::_big_pow(a, d) % n;
    if (x == 1 || x == n - 1) {
        return true;
    }
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;
        if (x == 1) return false;
        if (x == n - 1) return true;
    }
    return false;
}

bool isPrime(bigint n, int k) {
    if (n == 2 || n == 3) return true;
    if (n < 2 || n % 2 == 0) return false;

    bigint d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }
    for (int i = 0; i < k; i++) {
        if (!millerRabinTest(d, n)) {
            return false;
        }
    }
    return true;
}

int main() {
    bigint n = bigint::bigint("5");
    int k = 5; // Số lần kiểm tra để tăng độ chính xác
    if (isPrime(n, k)) {
        cout << n << " is prime.\n";
    }
    else {
        cout << n << " is composite.\n";
    }
    return 0;
}
