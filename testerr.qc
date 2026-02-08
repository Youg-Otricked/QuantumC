int main() {
    
    
    return 0;
}
// ✅ Should work - basic types
    int x = 40;
    x += 2;
    int age = 13;
    float pi = 3.14f;
    double precise = 3.14159265359;
    short int s = 10;
    long int l = 1000000;
    long double ld = 3.141592653589793238;
    
    // ✅ Should work - arithmetic
    int a = 10 + 5;
    int b = 20 - 3;
    int c = 4 * 7;
    int d = 100 / 10;
    int e = 17 % 5;
    int f = 2 ^* 8;  // 2^8 = 256
    
    // ✅ Should work - compound assignment
    a += 5;
    b -= 2;
    c *= 3;
    d /= 2;
    e %= 3;
    
    // ❌ ERROR: String not supported yet
    string name = "Lucas";
    
    // ❌ ERROR: Char not supported yet
    char letter = 'A';
    
    // ❌ ERROR: Bool not supported yet
    bool flag = true;
    
    // ❌ ERROR: qbool not supported yet
    qbool quantum = qtrue;
    
    // ❌ ERROR: Arrays not supported yet
    int[] arr = {1, 2, 3};
    
    // ❌ ERROR: Pointers not supported yet
    int* ptr = &x;
    
    // ❌ ERROR: Functions not supported yet
    void test() {
        println("hello");
    }
    
    // ❌ ERROR: If statements not supported yet
    if (x > 10) {
        x = 5;
    }
    
    // ❌ ERROR: Loops not supported yet
    for (int i = 0; i < 10; i++) {
        x += i;
    }
    
    // ❌ ERROR: Classes not supported yet
    class Point {
        int x;
        int y;
    }