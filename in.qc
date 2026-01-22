int main() {
    long int sum = 0;
    
    // 100 million iterations if your runtime can handle it,
    // drop to 10_000_000 if it's too slow in WASM.
    for (int i = 0; i < 10000000; i++) {
        sum += i % 7;
        
        if (i % 2000000 == 0) {
            println(f"Checkpoint {i}, sum = {sum}");
        }
    }
    
    println(f"Final sum = {sum}");
    return 0;
}