int main() {
    seed(12345);
    
    println(random());        // 0.0 to 1.0
    println(random(10));      // 0 to 9
    println(random(5, 15));   // 5 to 14
    
    return 0;
}