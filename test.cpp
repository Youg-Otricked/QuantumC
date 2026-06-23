#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// Function to do some math work
int compute(int x, int y) {
    int sum = 0;
    for (int i = 0; i < 100; i++) { sum += (x * y + i) % (i + 1); }
    return sum;
}

int main() {
    const int N = 1000000; // 1 million iterations
    int total = 0;

    vector<int> nums(N, 1);

    for (int i = 0; i < N; i++) {
        nums[i] = compute(i, i % 100 + 1);
        total += nums[i];
    }

    // Nested loop to really stress CPU
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) { total += (i * j) % 7; }
    }

    cout << "Final total: " << total << endl;
    return 0;
}