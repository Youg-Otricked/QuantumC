/* 
If you want to learn this language better, read along while actually codeing in it at learnhardcode.dpdns.org/QuantumC/qc.html   */
////////////////////////////////////////////////////////////////////////////////
// QUANTUM C (C^4) - INTERACTIVE DEMO
// Run this file to see all current features in action!
////////////////////////////////////////////////////////////////////////////////
int main() {
    //==============================================================================
    // BASIC ARITHMETIC
    //==============================================================================
    9 + 10;         // 19
    100 - 42;       // 58
    7 * 8;          // 56
    100 / 4;        // 25
    10 % 3;         // 1 //SOON^TM

    //==============================================================================
    // POWER OPERATOR (C++'s missing feature!)
    //==============================================================================
    2 ** 8;         // 256
    2 ** 3 ** 2;    // 512 (right-associative!)
    3 ** 3;         // 27

    //==============================================================================
    // OPERATOR PRECEDENCE
    //==============================================================================
    2 + 3 * 4;          // 14
    (2 + 3) * 4;        // 20
    2 ** 3 + 4 * 5;     // 28
    -2 ** 4;            // -16
    (-2) ** 4;          // 16

    //==============================================================================
    // VARIABLES & TYPES
    //==============================================================================
    int age = 13;
    float pi = 3.14f;
    double precise = 3.14159265359;
    string name = "Quantum C";
    char initial = 'Q';
    bool cool = true;

    age;            // 13
    pi;             // 3.14
    name;           // Quantum C

    //==============================================================================
    // STRING OPERATIONS
    //==============================================================================
    string first = "Quantum";
    string last = "C";
    string full = first + " " + last;
    full;           // Quantum C

    string greeting = "Hello, " + "World!";
    greeting;       // Hello, World!

    //==============================================================================
    // VARIABLE REASSIGNMENT
    //==============================================================================
    int counter = 0;
    counter = counter + 5;
    counter;        // 5
    counter = counter * 2;
    counter;        // 10

    //==============================================================================
    // UNARY OPERATORS
    //==============================================================================
    int x = 5;
    -x;             // -5
    ++x;            // 6
    --x;            // 4

    //==============================================================================
    // CHAIN ASSIGNMENT
    //==============================================================================
    int a = 0;
    int b = 0;
    a = b = 100;
    a;              // 100
    b;              // 100
    // Basic compound assignments
    int x = 10;
    x += 5;     // 15
    x;

    x -= 3;     // 12
    x;

    x *= 2;     // 24
    x;

    x /= 4;     // 6
    x;

    x %= 4;     // 2
    x;

    // Chain them
    int y = 100;
    y += 10;    // 110
    y -= 5;     // 105
    y *= 2;     // 210
    y /= 3;     // 70
    y %= 9;     // 7
    y;

    // With expressions on right side
    int z = 5;
    z += 2 + 3;     // 10
    z;

    z *= 1 + 1;     // 20
    z;

    z -= 5 * 2;     // 10
    z;

    z /= 2 ** 2;    // 2.5 or 2 depending on int division
    z;

    // With variables on right side
    int a = 10;
    int b = 5;
    a += b;         // 15
    a;

    a -= b;         // 10
    a;

    a *= b;         // 50
    a;

    a /= b;         // 10
    a;

    a %= b;         // 0
    a;

    // Edge cases
    int edge = 0;
    edge += 5;      // 5
    edge;

    edge %= 3;      // 2
    edge;

    // Modulo specifically
    int mod_test = 17;
    mod_test %= 5;  // 2
    mod_test;

    mod_test %= 2;  // 0
    mod_test;
    //==============================================================================
    // COMPLEX EXPRESSIONS
    //==============================================================================
    int result = ((5 + 3) * 2 ** 2 - 10) / 3;
    result;         // 18

    //==============================================================================
    // ESCAPE SEQUENCES
    //==============================================================================
    string quote = "He said: \"Hello!\"";
    string path = "C:\\Users\\Dev";
    string newline = "Line 1\nLine 2";

    quote;
    path;

    //==============================================================================
    // DEFAULT VALUES
    //==============================================================================
    int unset;
    unset;          // 0

    string empty;
    empty;          // ""

    //==============================================================================
    // EDGE CASES
    //==============================================================================
    0 ** 0;         // 1
    5 ** 0;         // 1
    0 ** 5;         // 0
    0 / 5;          // 0

    //==============================================================================
    // DEEP NESTING
    //==============================================================================
    ((((((1 + 1))))));                  // 2
    2 ** (2 ** (2 ** 1));               // 16

    //==============================================================================
    // LONG CHAINS
    //==============================================================================
    1+1+1+1+1+1+1+1+1+1;                // 10

    //==============================================================================
    // MIXED TYPES
    //==============================================================================
    int whole = 10;
    double decimal = 3.14;
    float precise_f = 2.5f;

    whole;
    decimal;
    precise_f;
    //==============================================================================
    // 13. COMPARISON OPERATORS
    //==============================================================================
    5 == 5;         // true
    5 != 3;         // true
    10 > 5;         // true
    5 < 10;         // true
    5 >= 5;         // true
    5 <= 5;         // true

    int age = 18;
    age >= 18;      // true
    age < 21;       // true

    //==============================================================================
    // 14. LOGICAL OPERATORS
    //==============================================================================
    bool is_adult = age >= 18;
    bool has_license = true;
    bool can_drive = is_adult && has_license;  // true

    bool is_weekend = false;
    bool is_holiday = true;
    bool day_off = is_weekend || is_holiday;   // true

    bool is_working = !day_off;                // false

    //==============================================================================
    // 15. COMPLEX LOGIC
    //==============================================================================
    int score = 85;
    bool passed = score >= 60;
    bool honor_roll = score >= 90;
    bool needs_improvement = score < 70;

    passed;                 // true
    honor_roll;             // false
    needs_improvement;      // false

    // Combining conditions
    bool eligible = age >= 18 && score >= 70;
    eligible;               // true

    //=============================================================================
    // 16. CONSTANTS
    //==============================================================================

    const double pi = 3.14159;

    // pi = 3.1 //erors. cannot assign to a const

    const string name = "Quantum C";


    ////////////////////////////////////////////////////////////////////////////////
    // SECTION 17: IF / ELSE / ELSE IF (CONTROL FLOW)
    ////////////////////////////////////////////////////////////////////////////////

    // Basic if/else
    int v = 5;
    if (v > 10) {
        v = 100;
    } else if (v > 3) {
        v = v + 1;
    } else {
        v = 0;
    }
    v;                      // expect 6

    // Single-statement if (no braces) - allowed
    int s = 0;
    if (v == 6) s = 1;
    s;                      // expect 1

    // Nested if/else
    if (v > 0) {
        if (v % 2 == 0) {
            v = v / 2;
        } else {
            v = v * 2;
        }
    }
    v;                      // if v==6 -> 3

    // Multi-branch else-if chain
    int score_if = 85;
    string grade = "";
    if (score_if >= 90) {
        grade = "A";
    } else if (score_if >= 80) {
        grade = "B";
    } else if (score_if >= 70) {
        grade = "C";
    } else {
        grade = "F";
    }
    grade;                  // expect "B"

    // Truthiness in conditions (strings and numbers)
    string maybe = "";
    int flag = 0;
    if (maybe) {
        flag = 1;
    } else {
        flag = 2;
    }
    flag;                   // expect 2 (empty string falsy)

    // else with only a single statement
    int x_if = 2;
    if (x_if > 10) {
        x_if = 10;
    } else x_if = x_if + 3;
    x_if;                   // expect 5

    // Edge: if with boolean values
    bool b_if = true;
    if (b_if) {
        b_if = false;
    } else {
        b_if = true;
    }
    b_if;                   // expect false

    // Complex nested chains
    int nested = 0;
    if (v > 10) {
        nested = 100;
    } else if (v > 2) {
        if (v % 3 == 0) {
            nested = 30;
        } else {
            nested = 20;
        }
    } else {
        nested = 5;
    }
    nested;

    // Expressiotn pre init

    if (int this = 21; this < 22) {
        this = 1;
    }
    //=============================================================================
    // SECTION 18: switch statments
    // ============================================================================
    int x = 2;

    switch (x) {
    case 1:
        x = 10;
        break;
    case 2:
        x = 20;
        break;
    default:
        x = 30;
        break;
    }

    int i = 0;
    while (i < 10) {
        i = i + 1;
        if (i == 3) continue;
        if (i == 5) break;
    }
    i;  // expect 5
    for (int j = 0; j < 5; j = j + 1) {
        if (j == 1) continue;
        if (j == 3) break;
    }
    int w2 = 0;
    int guard = 0;
    while (guard < 10) {
        guard = guard + 1;
        w2 = w2 + 1;
        if (w2 == 3) {
            break;
        }
    }
    w2;     // should be 3
    guard;  // should be 3 or 4-ish, but definitely < 10
    //=======================================
    //Write to console
    //=======================================
    //You cna write to consoel with std::qout or print or println

    std::qout << "Hello, World!" << '\n';

    print("Hello, World!\n");
    println("Hello, World!\n");

////////////////////////////////////////////////////////////////////////////////
// SECTION: FUNCTIONS & LAMBDAS.
////////////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////////////
        // EXAMPLE 1: Named function (returning value)
        ////////////////////////////////////////////////////////////////////////////////
        int add(int a, int b) {
            return a + b;
        }

        ////////////////////////////////////////////////////////////////////////////////
        // EXAMPLE 2: Void function with default arguments(no return value)
        ////////////////////////////////////////////////////////////////////////////////
        void greet(string name = "world", int times = 1) {
            int i = 0;
            while (i < times) {
                print("Hello, " + name + "!");
                i = i + 1;
            }
        }


        ////////////////////////////////////////////////////////////////////////////////
        // EXAMPLE 3: Assigning a lambda to a variable (use auto)
        ////////////////////////////////////////////////////////////////////////////////
        auto make_adder = fn(int x, int y) {
            return x + y;
        };

        ////////////////////////////////////////////////////////////////////////////////
        // EXAMPLE 4: Immediate invocation of a lambda (call right away)
        ////////////////////////////////////////////////////////////////////////////////
        auto immediate_result = fn(int a, int b) { return a * b; }(3, 4); // 12

        ////////////////////////////////////////////////////////////////////////////////
        // EXAMPLE 5: Higher-order function (accepts a function)
        ////////////////////////////////////////////////////////////////////////////////
        void twice(auto f, int v) {
            f(v);
            f(v);
        }

        ////////////////////////////////////////////////////////////////////////////////
        // EXAMPLE 6: Lambda calling a void function
        ////////////////////////////////////////////////////////////////////////////////
        auto hello_lambda = fn() {
            greet("Lambda");
        };

        ////////////////////////////////////////////////////////////////////////////////
        // EXAMPLE 7: Recursion using a variable-held lambda
        ////////////////////////////////////////////////////////////////////////////////
        auto factorial = fn(int n) {
            if (n <= 1) return 1;
            return n * factorial(--n); // recursion through the variable name
        };
    int r1 = add(2, 3);           // 5
    println(r1);

    // Void function
    greet();               
    greet("Alice");        
    greet("Bob", 3);      

    // Lambda assigned to variable
    auto sum = make_adder;
    println(sum(10, 20));         // prints 30

    // Immediate invocation
    println(immediate_result);    // prints 12

    // Higher-order usage
    auto printer = fn(int n) { println(n); };
    twice(printer, 7);            // prints 7 twice

    // Lambda that calls a void function
    hello_lambda();               // prints "Hello, Lambda"

    // Recursion
    println(factorial(5));        // prints 120
    ////////////////////////////////////////////////////////
    // F strings
    ///////////////////////////////////////////////////////
    // f strings are python style
    string this = f"Hello, {add(1, 2)}, {w2}";
    std::qout << this;
    //=============================================================================
    // SECTION 21: Multi-Return Values
    //=============================================================================

    // Single return (traditional)
    int add(int a, int b) {
        return a + b;
    }

    // Multi-return function - returns multiple values
    int, string get_user() {
        return 123, "Alice";
    }

    // Multi-return with 3+ values
    int, float, bool get_data() {
        return 100, 3.14f, true;
    }

    // Multi-variable declaration - destructuring multi-return
    int id, string name = get_user();
    id;    // 123
    name;  // "Alice"

    // Multi-return with 3 variables
    int code, float pi, bool flag = get_data();
    code;  // 100
    pi;    // 3.14
    flag;  // true

    // Multi-return with default parameters
    int, string greet(string name = "World") {
        return 200, "Hello, " + name;
    }

    int status1, string msg1 = greet();
    status1;  // 200
    msg1;     // "Hello, World"

    int status2, string msg2 = greet("Quantum C");
    status2;  // 200
    msg2;     // "Hello, Quantum C"

    // Type checking still applies
    int x, string y = get_user();  // ✓ Correct types
    // int x, int y = get_user();   // ✗ Error: type mismatch

    // Must match number of return values
    // int x = get_user();          // ✗ Error: can't assign multi-return to single variable
    // int x, string y, bool z = get_user();  // ✗ Error: expected 2 values, got 3
    // END OF DEMO
    // All features shown above are working in Quantum C v2.0!
    //==============================================================================
    return 0;
}
