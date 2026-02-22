class Calculator {
    int value;
    
    Calculator(int value) {
        this.value = value;
    }
    
    // ✅ OVERLOAD 1: int + int
    int add(int x) {
        return this.value + x;
    }
    
    // ✅ OVERLOAD 2: int + float
    float add(float x) {
        return to_float(this.value) + x;
    }
    
    // ✅ OVERLOAD 3: int + int + int
    int add(int x, int y) {
        return this.value + x + y;
    }
    
    // ✅ OVERLOAD 4: string concat
    string add(string x) {
        return to_string(this.value) + x;
    }
}

class Printer {
    // ✅ OVERLOAD 1: print int
    void print(int x) {
        println("Int: " + to_string(x));
    }
    
    // ✅ OVERLOAD 2: print float
    void print(float x) {
        println("Float: " + to_string(x));
    }
    
    // ✅ OVERLOAD 3: print string
    void print(string x) {
        println("String: " + x);
    }
    
    // ✅ OVERLOAD 4: print int array
    void print(int[] arr) {
        println("Array of ints");
    }
}

class Vector2D {
    int x;
    int y;
    
    Vector2D(int x, int y) {
        this.x = x;
        this.y = y;
    }
    
    // ✅ OPERATOR OVERLOAD 1: Vector + Vector
    Vector2D operator+(Vector2D other) {
        println("=== OPERATOR+ DEBUG ===");
        println("this.x = " + to_string(this.x));
        println("this.y = " + to_string(this.y));
        println("other.x = " + to_string(other.x));
        println("other.y = " + to_string(other.y));
        
        int sumX = this.x + other.x;
        int sumY = this.y + other.y;
        
        println("sumX = " + to_string(sumX));
        println("sumY = " + to_string(sumY));
        
        Vector2D result = Vector2D(sumX, sumY);
        
        println("result.x = " + to_string(result.x));
        println("result.y = " + to_string(result.y));
        
        return result;
    }
    
    // ✅ OPERATOR OVERLOAD 2: Vector + int (scale)
    Vector2D operator+(int scalar) {
        return Vector2D(this.x + scalar, this.y + scalar);
    }
    
    void print() {
        println("(" + to_string(this.x) + ", " + to_string(this.y) + ")");
    }
}

int main() {
    println("=== CALCULATOR OVERLOAD TEST ===");
    
    Calculator calc = Calculator(10);
    
    int r1 = calc.add(5);           // Calls add(int) -> 15
    println("add(5): " + to_string(r1));
    
    float r2 = calc.add(3.5f);      // Calls add(float) -> 13.5
    println("add(3.5f): " + to_string(r2));
    
    int r3 = calc.add(2, 3);        // Calls add(int, int) -> 15
    println("add(2, 3): " + to_string(r3));
    
    string r4 = calc.add(" points"); // Calls add(string) -> "10 points"
    println("add(\" points\"): " + r4);
    
    println("\n=== PRINTER OVERLOAD TEST ===");
    
    Printer p = Printer();
    
    p.print(42);           // Calls print(int)
    p.print(3.14f);        // Calls print(float)
    p.print("Hello!");     // Calls print(string)
    
    int arr[] = [1, 2, 3];
    p.print(arr);          // Calls print(int[])
    
    println("\n=== VECTOR OPERATOR OVERLOAD TEST ===");
    
    Vector2D v1 = Vector2D(1, 2);
    println("v1.x: " + to_string(v1.x));
    println("v1.y: " + to_string(v1.y));
    Vector2D v2 = Vector2D(3, 4);
    
    Vector2D v3 = v1 + v2;  // Calls operator+(Vector2D)
    print("v1 + v2 = ");
    v3.print();
    
    Vector2D v4 = v1 + 10;  // Calls operator+(int)
    print("v1 + 10 = ");
    v4.print();
    
    println("\n=== INHERITANCE OVERLOAD TEST ===");
    
    class Animal {
        void speak(int times) {
            println("Animal speaks " + to_string(times) + " times");
        }
        
        void speak(string message) {
            println("Animal says: " + message);
        }
    }
    
    class Dog : Animal {
        Dog() {

        }
        void speak(int times) {
            println("Dog barks " + to_string(times) + " times");
        }
        
        void speak(float volume) {
            println("Dog barks at volume " + to_string(volume));
        }
    }
    
    Dog dog = Dog();
    dog.speak(3);           // Calls Dog's speak(int)
    dog.speak("woof");      // Calls Animal's speak(string) - inherited!
    dog.speak(5.5f);        // Calls Dog's speak(float)
    
    println("\n=== ALL OVERLOAD TESTS COMPLETE ===");
    
    return 0;
}