int main() {
    // Basic arithmetic
    int a = 5;
    int b = 3;
    int sum = a + b;
    int prod = a * b;
    println(sum);    // 8
    println(prod);   // 15

    // Strings
    string name = "Quantum";
    string greeting = "Hello, " + name;
    println(greeting);

    // Boolean logic
    bool flag = true;
    bool check = !flag || (a > b);
    println(check);  // true

    // QBool
    qbool qb = both;
    qif (qb) {
        println("Superposition!");
    } qelse {
        println("Nothing");
    }

    // Array & List
    int[] numbers = [1, 2, 3];
    numbers.push(4);
    println(numbers[3]);   // 4

    // Function & Lambda
    int add(int x, int y) { return x + y; }
    auto doubleVal = fn(int x) -> int { return x * 2; };
    println(add(2, 3));        // 5
    println(doubleVal(4));      // 8

    // Struct
    struct Vec2 { float x; float y; };
    Vec2 point = {1.0f, 2.0f};
    println(point.x);           // 1.0
    println(point.y);           // 2.0

    // Map
    map<string,int> ages = { "Alice":25, "Bob":30 };
    ages["Charlie"] = 35;
    println(ages["Bob"]);       // 30

    // Control flow
    int val = 10;
    if (val > 5) {
        val = val + 1;
    } else {
        val = val - 1;
    }
    println(val);               // 11

    // Loop
    int i = 0;
    while (i < 3) {
        println(i);
        i = i + 1;
    }

    return 0;
}
