/* 
If you want to learn this language better, read along while actually codeing in it at learnhardcode.dpdns.org/QuantumC/qc.html   */
////////////////////////////////////////////////////////////////////////////////
// QUANTUM C (C^4) - INTERACTIVE DEMO
// Run this file to see all current features in action!
////////////////////////////////////////////////////////////////////////////////
// @print-ast
namespace Outer {
    int outerVar = 10;

    namespace Inner {
        int innerVar = 20;
        
        int getInner() {
            return innerVar;
        }
        int getoi() {
            return outerVar;
        }
    }

    int getOuter() {
        return outerVar;
    }

    namespace Inner2 {
        int inner2Var = 30;
    }

    enum Color {
        Red = 0;
        Green = 1;
        Blue = 2;
    }

    type MyUnion = int | float;

    type AliasInt = int;
}
namespace Inner {
    class InnerClass {
        int y;
        InnerClass(int y) {
            this.y = y;
        }
        int getY() { return this.y; }
    }
}
int main() {
    //==============================================================================
    // BASIC ARITHMETIC
    //==============================================================================
    9 + 10;         // 19
    100 - 42;       // 58
    7 * 8;          // 56
    100 / 4;        // 25
    10 % 3;         // 1

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
    bool work_to_do = !can_drive ^ is_adult;
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
    if (int thngy = 21; thngy < 22) {
        thngy = 1;
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
        auto make_adder = fn(int x, int y) -> int {
            return x + y;
        };

        ////////////////////////////////////////////////////////////////////////////////
        // EXAMPLE 4: Immediate invocation of a lambda (call right away)
        ////////////////////////////////////////////////////////////////////////////////
        auto immediate_result = fn(int a, int b) -> int { return a * b; }(3, 4); // 12

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
        auto hello_lambda = fn() -> void {
            greet("Lambda");
        };

        ////////////////////////////////////////////////////////////////////////////////
        // EXAMPLE 7: Recursion using a variable-held lambda
        ////////////////////////////////////////////////////////////////////////////////
        auto factorial = fn(int n) -> int {
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
     // ========================================
    // 1D ARRAYS (Basic)
    // ========================================
    
    int numbers[] = [1, 2, 3, 4, 5];
    println(numbers[0]);  // 1
    println(numbers[4]);  // 5
    
    string names[] = ["Alice", "Bob", "Charlie"];
    println(names[1]);  // Bob
    
    float prices[] = [9.99, 19.99, 29.99];
    println(prices[2]);  // 29.99
    
    
    // ========================================
    // 2D ARRAYS (Grids)
    // ========================================
    
    // Uniform grid (all rows same length)
    int grid[][] = [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9]
    ];
    println(grid[0][0]);  // 1
    println(grid[1][1]);  // 5
    println(grid[2][2]);  // 9
    
    // String grid
    string board[][] = [
        ["X", "O", "X"],
        ["O", "X", "O"],
        ["X", "O", "X"]
    ];
    println(board[0][1]);  // O
    
    
    // ========================================
    // JAGGED ARRAYS (Different row lengths!)
    // ========================================
    
    int jagged[][] = [
        [1, 2],           // Row 0: 2 elements
        [3, 4, 5],        // Row 1: 3 elements
        [6],              // Row 2: 1 element
        [7, 8, 9, 10]     // Row 3: 4 elements
    ];
    println(jagged[0][0]);  // 1
    println(jagged[1][2]);  // 5
    println(jagged[2][0]);  // 6
    println(jagged[3][3]);  // 10
    
    // Jagged string array (like a paragraph)
    string paragraph[][] = [
        ["The", "quick", "brown"],
        ["fox"],
        ["jumps", "over", "the", "lazy", "dog"]
    ];
    println(paragraph[0][1]);  // quick
    println(paragraph[2][4]);  // dog
    
    
    // ========================================
    // 3D ARRAYS (Cubes)
    // ========================================
    
    // 2x2x2 cube
    int cube[][][] = [
        [
            [1, 2],
            [3, 4]
        ],
        [
            [5, 6],
            [7, 8]
        ]
    ];
    println(cube[0][0][0]);  // 1
    println(cube[0][1][1]);  // 4
    println(cube[1][0][1]);  // 6
    println(cube[1][1][1]);  // 8
    
    // RGB image (3x3 pixels, 3 color channels)
    int image[][][] = [
        [[255, 0, 0], [0, 255, 0], [0, 0, 255]],  // Row 1
        [[255, 255, 0], [255, 0, 255], [0, 255, 255]],  // Row 2
        [[128, 128, 128], [0, 0, 0], [255, 255, 255]]   // Row 3
    ];
    println(image[0][0][0]);  // 255 (red channel of pixel 0,0)
    println(image[1][2][1]);  // 255 (green channel of pixel 1,2)
    
    
    // ========================================
    // JAGGED 3D ARRAYS (Different depths!)
    // ========================================
    
    int jagged3d[][][] = [
        [
            [1, 2],
            [3, 4, 5]  // Different length!
        ],
        [
            [6],       // Single element
            [7, 8, 9, 10]  // Four elements!
        ]
    ];
    println(jagged3d[0][1][2]);  // 5
    println(jagged3d[1][1][3]);  // 10
    
    
    // ========================================
    // 4D ARRAYS (Tesseracts/Hypercubes!)
    // ========================================
    
    // 2x2x2x2 tesseract
    int tesseract[][][][] = [
        [
            [
                [1, 2],
                [3, 4]
            ],
            [
                [5, 6],
                [7, 8]
            ]
        ],
        [
            [
                [9, 10],
                [11, 12]
            ],
            [
                [13, 14],
                [15, 16]
            ]
        ]
    ];
    println(tesseract[0][0][0][0]);  // 1
    println(tesseract[0][1][1][1]);  // 8
    println(tesseract[1][0][1][0]);  // 11
    println(tesseract[1][1][1][1]);  // 16
    
    // Video data (time, height, width, RGB)
    // 2 frames, 2x2 pixels, 3 color channels
    int video[][][][] = [
        [  // Frame 1
            [[255, 0, 0], [0, 255, 0]],     // Row 1
            [[0, 0, 255], [255, 255, 0]]    // Row 2
        ],
        [  // Frame 2
            [[255, 0, 255], [0, 255, 255]],  // Row 1
            [[128, 128, 128], [0, 0, 0]]     // Row 2
        ]
    ];
    println(video[0][0][0][0]);  // 255 (Frame 1, pixel 0,0, red)
    println(video[1][1][1][2]);  // 0   (Frame 2, pixel 1,1, blue)
    
    
    // ========================================
    // MIXED TYPES
    // ========================================
    
    double matrix[][] = [
        [1.1, 2.2, 3.3],
        [4.4, 5.5, 6.6]
    ];
    println(matrix[1][2]);  // 6.6
    
    char letters[][] = [
        ['a', 'b', 'c'],
        ['x', 'y', 'z']
    ];
    println(letters[0][2]);  // c
    std::qout << matrix << '\n';
    // you make a list with type[] name and a array with type name[]
    int[] plswork = [1];
    //you can push values to an list like this
    plswork.push(123);
    // pushing a array to a list
    plswork.push([1, 2, 4]);
    // defining a second list
    char[] works = ['c', 'd'];
    int[] migthtwotk = [2];
    // pushing an list on a list
    // plswork.push(works); - Runtime Error: cannot push a list<char> to a list of type int
    plswork.push(migthtwotk);
    // plswork.push("hello"); - Runtime Error: cannot push a string to a list of type int
    // popping from lists
    plswork.push(1);
    plswork.push(2121212121);
    std::qout << plswork << '\n';
    plswork.pop();
    std::qout << plswork << '\n';
    plswork.pop();
    std::qout << plswork << '\n';
    // pushing inner list = pushing list its linked to
    migthtwotk.push(123);
    std::qout << plswork << '\n';
    std::qout << plswork[2][0] << '\n' << plswork[3][0] << '\n';
    // =======================================
    // returning colleciton types from functions (im not sure if this works yet)
    // =======================================
    
    int[] make_array() {
        return [1, 2, 3];
    }

    void print_any(auto v) {
        println(v);
    }

    int[] bbb = make_array();
    int bb[] = make_array();
    println(bbb);           // should print [1, 2, 3]
    print_any(bbb);         // should also print [1, 2, 3]
    void print_int_list(list<int> xs) {
        println(xs);
    }

    int[] a = [1, 2, 3];
    print_int_list(a); 
    int[] copyInt(list<int> x) {
        return x;
    }
    int[] copyIntArr(int[] z) {
        return z;
    }
    int[] cpl = [9, 9, 1, 4];
    int cpa[] = [1, 99999, 34234];
    int[] copyed = copyInt(cpl);
    int copyedArr[] = copyIntArr(cpa);
    std::qout << cpl << cpa << copyed << copyedArr << '\n';
    // --- list<int> params, return, and multi-return ---
    int[] id_list(list<int> xs) {
        return xs;
    }

   

    void print_int_list(list<int> xs) {
        println(xs);
    }

    int[] base = [1, 2, 3, 4];
    int[] copy = id_list(base);        // base is list<int> internally
    print_int_list(copy);                  // [1, 2, 3, 4]


    // --- mixing arrays and lists ---

    int grid[][] = [
        [1, 2],
        [3, 4]
    ];
    println(grid);         // [[1, 2], [3, 4]]
    println(grid[0][1]);   // 2

    int[] l1 = [5, 6, 7];
    int[] l2 = l1;
    l2.push(8);
    println(l1);           // [5, 6, 7, 8] if aliasing, or [5,6,7] if copied
    println(l2);           // [5, 6, 7, 8]

    // LIST AND ARRAY SUMMARY
    // define a array with type name[] = value
    string example[] = ["This is an example"];
    // define a list with type[] name = value
    string[] listexample = ["This is a list"];
    // add to list with .push and subtract with .pop
    listexample.push("This");
    listexample.pop();
    // when returnign a array or list use the type[] syntax amd when passing one as argument arrays are type[] and lists are list<type>
    // ==============================================
    // foreach loop
    // ==============================================
    foreach (int x in [1, 2, 3, 4, 5]) {
        println(x);
    }
    // ==============================================
    // spread (@) operator
    // ==============================================
    int grid[][] = [[1, 2], [3, 4]];
    int flat[] = [@grid[0], @grid[1]];
    println(flat);
    int arr1[] = [1, 2, 3];
    int arr2[] = [4, 5, 6];
    int combined[] = [@arr1, @arr2];
    println(combined);
    int[] list1 = [10, 20];
    int[] list2 = [30, 40];
    int[] merged = [@list1, @list2, 50];
    println(merged);
    int[] a = [1, 2];
    int[] b = [3, 4];
    int[] c = [5, 6];
    int[] all = [0, @a, @b, @c, 7];
    println(all);
    void print_three(int x, int y, int z) {
        println(x);
        println(y);
        println(z);
    }
    
    int args[] = [100, 200, 300];
    print_three(@args);
    auto sum_lambda = fn(int a, int b, int c) -> int {
        return a + b + c;
    };

    int result = sum_lambda(1, 2, 3);
    println(result);
    int args_list[] = [4, 5, 6];
    int result2 = sum_lambda(@args_list);
    println(result2);
    // ========================================
    // QUANTUM BOOLEAN 
    // ========================================
    qbool qb = none;      // Neither true nor false
    qb = qtrue;           // Definitely true
    qb = qfalse;          // Definitely false
    qb = both;            // Superposition! Both true AND false!
    
    std::qout << "QBool: " << qb << "\n";
    // =======================================
    // Quantum Logic & control flow
    // =======================================
    println("=== QTRUE ===");
    qbool q1 = qtrue;
    qif (q1) {
        println("True");
    } qelse {
        println("False");
    }
    
    println("\n=== QFALSE ===");
    qbool q2 = qfalse;
    qif (q2) {
        println("True");
    } qelse {
        println("False");
    }
    
    println("\n=== BOTH ===");
    qbool q3 = both;
    qif (q3) {
        println("True");
    } qelse {
        println("False");
    }
    
    println("\n=== NONE ===");
    qbool q4 = none;
    qif (q4) {
        println("True");
    } qelse {
        println("False");
    }
    // use qelif for else if statments
    qb = both;
    
    qswitch (qb) {
        case t:
            println("True case!");
            break;
        case f:
            println("False case!");
            break;
        case n:
            println("None case!");
            break;
        case b:
            println("Both case!");
            break;
    }
    std::qout << "Type qtrue qfalse none or both" << '\n';
    qbool z = qtrue;
    qbool n = both;
    std::qin >> z;
    std::qout << "\nType qtrue qfalse none or both" << '\n';
    std::qin >> n;
    std::qout << z &&& n; // if both sides can be true and one is both both
    std::qout << z ||| n; // if at least one side is both both
    std::qout << z ^^ n; // ||| !!&&&
    std::qout << "z" === 1; // if left is eqaul to ight true
    std::qout << "z" !== 1;// === but !=
    std::qout << n;
    std::qout << !!n;// ! but for QBOOLs
    std::qout << !n;
    std::qout << z |&| !!n; // if either side is true or both true
    std::qout << z &|& n; // if both sides are true or both true
    map<string, int> ages = {
        "Alice": 25,
        "Bob": 30
    };
    
    println(ages["Alice"]);  // 25
    
    ages["Charlie"] = 35;
    ages.set("Dave", 40);
    
    println(ages.size);  // 4
    println(ages.has("Bob"));  // true
    
    ages.remove("Bob");
    println(ages.has("Bob"));  // false
    
    foreach (string key in ages.keys()) {
        println(key + ": " + f"{ages[key]}");
    }
    seed(time());
    
    println(random());        // 0.0 to 1.0
    println(random(10));      // 0 to 9
    println(random(5, 15));   // 5 to 14
    // INPUT AND short or long

    // USACO fence problem
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    std::qout << "Type two numbers seperated by a space";
    std::qin >> a >> b;
    std::qout << "Type two numbers seperated by a space";
    std::qin >> c >> d;
    if (a < c && b < c || c < a &&  d < a) {
        std::qout << b - a + d - c;
    }
    else if (a < c) {
        if (b < d) {
            std::qout << d - a;
        }  else {
            std::qout << b - a;
        }
    } else {
        if (b < d) {
            std::qout << d - c;
        }  else {
            std::qout << b - c;
        }
    }
    // end of fence
    short int x = 100;
    int y = 50000;
    long int z = 9999999999;
    float f = 3.14f;
    double d = 3.14159;
    long double ld = 3.14159265358979323846;
    
    println(x);
    println(y);
    println(z);
    println(f);
    println(d);
    println(ld);
    struct Vector2 {
        float x;
        float y;
    };

    struct Inventory {
        int[] bag;     
        string slots[];
    };

    struct Player {
        string name;
        int hp;
        Vector2 pos;
        Inventory inv;
    };

    Player p = {
        "Alice",
        100,   
        {1.0f, 2.0f},
        { [1, 2, 3], ["head"] }
    };

    println(p.name);
    println(p.hp);
    println(p.pos.x);
    println(p.pos.y);
    println(p.inv.bag.length);
    println(p.inv.slots[0]);

    Player q = p;
    q.name = "Bob";
    q.hp = 50;
    q.pos.x = 9.0f;

    println(p.name);
    println(p.hp);
    println(p.pos.x);

    println(q.name);
    println(q.hp);
    println(q.pos.x); 

    p.inv.bag.push(4);
    println(p.inv.bag.length);
    map<string,int> ages = { "Alice":25, "Bob":30 };
    ages["Charlie"] = 35;
    ages.remove("Bob");
    println(ages.has("Alice"));
    foreach (string k in ages.keys()) { println(k + ": " + f"{ages[k]}"); }
    type ApiTier = "Pro" | "Free" | "Basic" | "Enterprise";
    int getRateLimitForTier(ApiTier tier) {
        switch (tier) {
            case "Free":
            return 10;
            case "Basic":
            return 100;
            case "Pro":
            return 1000;
            case "Enterprise":
            return 10000;
        }
    }
    ApiTier tier = "Pro";
    std::qout << getRateLimitForTier(tier);
    type Weird = 1 | 2 | "ok" | 'x' | true | qtrue | int;

    Weird a = 1;        
    Weird b = "ok";     
    Weird c = 'x';    
    Weird d = true; 
    Weird e = qtrue;    
    Weird f = 42;  
    ApiTier GetTierFromRate(int rate) {
        switch (rate) {
            case 10:
            return "Free";
            case 100:
            return "Basic";
            case 1000:
            return "Pro";
            case 10000:
            return "Enterprise";
            default:
            return "Free";
        }
    }
    ApiTier thingy = GetTierFromRate(f);
    std::qout << typeof(thingy);
    if (typeof(thingy) != "string") {
        throw("Should have been string");
    }
    enum Api {
        Free = "Free";
        Pro  = "Pro";
    }

    Api t = Api.Pro;
    println(t);            
    println(typeof(t));
    class Enemy {
        int hp;

        public Enemy(int hp) {
            this.hp = hp;
        }

        public void damage(int amount) {
            this.hp -= amount;
        }
        protected void repr() {
            println(this.hp);
        }
        public int getHp() {
            return this.hp;
        }
    }

    class Boss : Enemy {
        int rage;

        public Boss(int hp, int rage) {
            this.rage = rage;
            this.hp = hp * 10;
        }

        public void enrage() {
            this.rage += 10;
        }
    }
    class FinalBoss : Boss {
        int lackeys;

        public FinalBoss(int lackeys, int hp, int rage) {
            this.rage = rage;
            this.hp = hp * 10;
            this.lackeys = lackeys;
        }

        public void pnt() {
            this.repr();
        }
        public void kill_lackey() {
            this.lackeys -= 1;
        }
        public final void enrage() { // If you made a overwrite of this funciton it woulf error
            this.rage += 20;
        }
    }
    Boss b = Boss(100, 0);
    b.damage(30);
    println(b.getHp());
    b.enrage();
    FinalBoss fb = FinalBoss(1000, 100, 10);
    fb.pnt();
    fb.enrage();
    println(fb.rage);
    std::qout << p.has("hp");
    int globalVar = 1;
    // Access global
    globalVar = 2;

    // Access outer + inner
    Outer::outerVar = 100;
    Outer::Inner::innerVar = 200;

    // Call functions
    int a = Outer::getOuter();
    int b = Outer::Inner::getInner();


    // Struct using namespace member type

    // Enums
    Outer::Color col = Outer::Color.Red;

    // Union
    Outer::MyUnion u;
    u = 42;

    // Inner class
    Inner::InnerClass ic = Inner::InnerClass(123);
    int iy = ic.getY();

    int res = a + b + col + u + Outer::Inner::getoi();
    abstract class Base {
    int x;
    int y;
    }
    class Vec2 : Base {
        Vec2(int x, int y) {
            this.x = x;
            this.y = y;
        }

        Vec2 operator+(Vec2 other) {
            Vec2 r = Vec2(0, 0);
            r.x = this.x + other.x;
            r.y = this.y + other.y;
            return r;
        }

        bool operator==(Vec2 other) {
            return this.x == other.x && this.y == other.y;
        }
        bool eval() {
        return true;
        }
        string repr() {
        return f"Dimentions: {this.x} x {this.y}";
        }
    }
    Vec2 a = Vec2(1, 2);
    Vec2 b = Vec2(3, 4);
    Vec2 c = a + b;

    Vec2 d = Vec2(4, 6);
    bool eq1 = (c == d);
    bool eq2 = (a == b);

    int result = 0;
    if (eq1) {
        result += 10;
    }
    if (eq2) {
        result += 1;
    }
    if (a) {
      std::qout << "Eval works" << '\n';
    }
    std::qout << a << '\n';
    std::qout << "c.x=" << c.x << " c.y=" << c.y << "\n";
    std::qout << "eq1=" << eq1 << " eq2=" << eq2 << "\n";
    // END OF DEMO
    // All features shown above are working in Quantum C v10.0.0!
    //==============================================================================
    return res;
}
