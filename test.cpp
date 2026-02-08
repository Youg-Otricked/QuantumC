#include <iostream>

int main() {
    long long sum = 0;
    long long prod = 1;
    long long max_outer = 1000;
    long long max_inner = 1000;

    for (long long i = 0; i < max_outer; ++i) {
        for (long long j = 1; j < max_inner; ++j) {
            if ((i * j) % 7 == 0 && (i + j) % 3 != 0) {
                sum += i*i + j*j*j;
            } else if ((i - j) % 5 == 0 || (i + j) % 11 == 0) {
                prod *= (i + 1);
                if (prod > 1'000'000'000) prod %= 1'000'000'000;
            } else {
                sum -= j*j;
            }

            // Simulate quantum boolean
            bool qb = true;  // always true for testing
            if (qb) sum += 1;
            else sum -= 1;
        }
    }

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Prod: " << prod << std::endl;
    return 0;
}
