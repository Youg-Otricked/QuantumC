#include <iostream>
volatile long long sink = 0;
long long heavy_compute(int n) {
    long long x = 1;
    for (int i = 1; i < n; i++) {
        x ^= (x << 3);
        x += i * 2654435761u;
        x ^= (x >> 5);
        x *= 31;
        if ((i % 3) == 0) x += i * i;
        if ((i % 5) == 0) x ^= (x >> 2);
        if ((i % 7) == 0) x += (x << 1);
    }
    return x;
}
int main() {
    const int outer = 50;
    const int inner = 200000;
    long long total = 0;
    std::cout << "Starting heavy benchmark...\n";
    for (int i = 0; i < outer; i++) {
        long long result = heavy_compute(inner);
        total += result;
        std::cout << "Run " << i << " result: " << result << "\n";
    }
    sink = total;
    std::cout << "Final sink: " << sink << "\n";
    std::cout << "Done.\n";
    return 0;
}
