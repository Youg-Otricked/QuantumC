volatile long long sink = 0;
#include <cstdio>

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

    std::printf("Starting heavy benchmark...\n");

    for (int i = 0; i < outer; i++) {
        long long result = heavy_compute(inner);
        total += result;
        std::printf("Run %d result: %lld\n", i, result);
    }

    sink = total;

    std::printf("Final sink: %lld\n", sink);
    std::printf("Done.\n");

    return 0;
}
