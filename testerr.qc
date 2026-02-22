class Calculator {
    auto add(auto a, auto b) {
        return a + b;
    }
    
    auto multiply(auto x, auto y) {
        return x * y;
    }
}

int main() {
    Calculator calc = Calculator();
    
    int sum1 = calc.add(5, 3);           // Generates add_int_int
    float sum2 = calc.add(2.5f, 3.7f);   // Generates add_float_float
    
    int prod1 = calc.multiply(4, 5);     // Generates multiply_int_int
    float prod2 = calc.multiply(2.0f, 3.0f);  // Generates multiply_float_float
    
    println(to_string(sum1));   // 8
    println(to_string(sum2));   // 6.2
    println(to_string(prod1));  // 20
    println(to_string(prod2));  // 6.0
    
    return 0;
}