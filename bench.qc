long int sink = 0;
long int heavy_compute(int n) {
    long int x = 1;
    for (int i = 1; i < n; i++) {
        x = x $ (x << 3);
        x += i * 2654435761;
        x = x $ (x >> 5);
        x *= 31;
        if ((i % 3) == 0) x += i * i;
        if ((i % 5) == 0) x = x $ (x >> 2);
        if ((i % 7) == 0) x += (x << 1);
    }
    return x;
}
int main() {
    const int outer = 50;
    const int inner = 200000;
    long int total = 0;
    qout("Starting heavy benchmark...\n");
    for (int i = 0; i < outer; i++) {
        long int result = heavy_compute(inner);
        total += result;
        qout("Run %i result: %i\n", i, result);
    }
    sink = total;
    qout("Final sink: %i\n", sink);
    return 0;
}

