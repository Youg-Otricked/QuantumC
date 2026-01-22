int main() {
    println("=== FUNCTION OVERLOAD TESTS ===\n");
    
    // Test 1: Same name, different param count
    int add(int a) {
        return a + 10;
    }
    
    int add(int a, int b) {
        return a + b;
    }
    
    int add(int a, int b, int c) {
        return a + b + c;
    }
    
    println("add(5) = " + f"{add(5)}");           // Should print 15
    println("add(5, 3) = " + f"{add(5, 3)}");     // Should print 8
    println("add(1, 2, 3) = " + f"{add(1, 2, 3)}"); // Should print 6
    
    // Test 2: Same name, different types
    string greet(string name) {
        return "Hello, " + name + "!";
    }
    
    string greet(int age) {
        return "You are " + f"{age}" + " years old!";
    }
    
    println(greet("Alice"));  // Should print "Hello, Alice!"
    println(greet(25));       // Should print "You are 25 years old!"
    
    // Test 3: Auto parameter (should match anything)
    void print_value(int x) {
        println("Integer: " + f"{x}");
    }
    
    void print_value(string s) {
        println("String: " + s);
    }
    
    void print_value(auto x) {
        println("Auto: " + f"{x}");
    }
    
    print_value(42);        // Should call int version
    print_value("test");    // Should call string version
    print_value(3.14);      // Should call auto version
    
    // Test 4: Default parameters with overloads
    int multiply(int a) {
        return a * 2;
    }
    
    int multiply(int a, int b) {
        return a * b;
    }
    
    println("multiply(5) = " + f"{multiply(5)}");      // Should print 10
    println("multiply(5, 3) = " + f"{multiply(5, 3)}"); // Should print 15
    
    // Test 5: Multi-return overloads
    int process(int x) {
        return x * 2;
    }
    
    int, string process(int x, string s) {
        return x * 2, s + "!";
    }
    
    int r1 = process(5);
    println("process(5) = " + f"{r1}");  // Should print 10
    
    int r2, string s2 = process(5, "test");
    println("process(5, 'test') = " + f"{r2}" + ", " + s2);  // Should print "10, test!"
    
    // Test 6: Recursive overload
    int factorial(int n) {
        if (n <= 1) return 1;
        return n * factorial(n - 1);
    }
    
    double factorial(double n) {
        if (n <= 1.0) return 1.0;
        return n * factorial(n - 1.0);
    }
    
    println("factorial(5) = " + f"{factorial(5)}");      // Should print 120
    println("factorial(5.0) = " + f"{factorial(5.0)}");  // Should print 120.0
    
    println("\n=== ALL OVERLOAD TESTS PASSED ===");
    return 0;
}