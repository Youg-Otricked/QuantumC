
class Calculator {
    int value;
    
    Calculator(int v) {
        this.value = v;
    }
    
    // Overload 1: Add int
    int add(int x) {
        return this.value + x;
    }
    
    // Overload 2: Add double
    double add(double x) {
        return to_double(this.value) + x;
    }
    
    // Overload 3: Add string (concatenate)
    string add(string s) {
        return f"{this.value}" + s;
    }
    
    // Overload 4: Add two ints
    int add(int x, int y) {
        return this.value + x + y;
    }
}

class Vec2 {
    int x;
    int y;
    
    Vec2(int x, int y) {
        this.x = x;
        this.y = y;
    }
    
    // Overload operator+ with Vec2
    Vec2 operator+(Vec2 other) {
        return Vec2(this.x + other.x, this.y + other.y);
    }
    
    // Overload operator+ with int (scalar)
    Vec2 operator+(int scalar) {
        return Vec2(this.x + scalar, this.y + scalar);
    }
    
    // Overload operator+ with double (scalar)
    Vec2 operator+(double scalar) {
        int s = to_int(scalar);
        return Vec2(this.x + s, this.y + s);
    }
    
    string repr() {
        return f"({this.x}, {this.y})";
    }
}

int main() {
    println("=== METHOD OVERLOAD TESTS ===\n");
    
    Calculator calc = Calculator(10);
    
    println("calc.add(5) = " + f"{calc.add(5)}");
    println("calc.add(3.14) = " + f"{calc.add(3.14)}");
    println("calc.add(\" items\") = " + calc.add(" items"));
    println("calc.add(2, 3) = " + f"{calc.add(2, 3)}");
    
    Vec2 a = Vec2(1, 2);
    Vec2 b = Vec2(3, 4);
    
    Vec2 c = a + b;
    println("Vec2(1,2) + Vec2(3,4) = " + c.repr());
    
    Vec2 d = a + 10;
    println("Vec2(1,2) + 10 = " + d.repr());
    
    Vec2 e = a + 5.5;
    println("Vec2(1,2) + 5.5 = " + e.repr());
    
    println("\n=== ALL TESTS PASSED ===");
    return 0;
}