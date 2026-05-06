struct Point {
    int x;
    int y;
};
struct Rectangle {
    Point topLeft;
    Point bottomRight;
};
int add(int a, int b) {
    return a + b;
}

int, string get_user() {
    return 123, "Alice";
}
int mul_add(int a, int b, int c) {
    return a * b + c;
}
void greet(string name = "World", int times = 1) {
    std::qout << name;
}
double square(double x) {
    return x * x;
}
int[] make_array() {
    int arr[] = [1, 2, 3];
    return arr;
}

int[], string get_both() {
    int arr[] = [4, 5, 6];
    return arr, "test";
}

void print_array(int[] arr, int size) {
    for (int i = 0; i < size; i += 1) {
        std::qout << arr[i] << " ";
    }
    println("");
}
list<int> make_list() {
    println("Creating list");
    list<int> nums = [1, 2, 3];
    println("After creation, length:");
    std::qout << nums.length << '\n';
    return nums;
}

list<int> double_list(list<int> input) {
    list<int> result = [];
    foreach (int x in input) {
        result.push(x * 2);
    }
    return result;
}

list<int>, int get_list_and_count() {
    list<int> data = [10, 20, 30];
    return data, 3;
}
int inc(int x) { return x + 1; }
int twice(int x) { return inc(inc(x)); }
int main() {
    int testerf = 5;
    int thing[] = [1, 2, 3, 4, 5];
    float testerfloat = 3.5f;
    string fstringt = f"answer={testerf}, b={testerfloat}";
    std::qout << fstringt << '\n';
    int xdddddddd = add(2, 3);
    function adder = fn(int a, int b) -> int { return a + b; };
    int ydddddddd = adder(10, 20);
    int idddddd, string asdfname = get_user();
    greet();             
    greet("Alice");     
    greet("Bob", 3);
    std::qout << ydddddddd << '\n';
    int v1 = mul_add(2, 3, 4);       // 10
    double v2 = square(1.5);         // 2.25
    int v3 = mul_add(v1, 3, 1);// 10*2 + 1 = 21 (or adjust casts)
    // ===== INTEGER TYPES =====
    int regular = 42;
    short int tiny = 100;
    long int huge = 9999999;

    // ===== FLOATING POINT =====
    float pi = 3.14f;
    double precise = 3.14159265359;

    // ===== CHARACTER =====
    char letter = 'A';
    char digit = '7';
    char symbol = '@';

    // ===== BOOLEAN =====
    bool isAwesome = true;
    bool isBoring = false;

    // ===== QUANTUM BOOLEAN =====
    qbool superposition = both;
    qbool collapsed = qtrue;
    qbool empty = none;
    qbool negative = qfalse;

    // ===== STRING =====
    string name = "Luca";
    string greeting = "Hello, Compiler!";
    string emoji = "🔥";
    int x = 10;
    int y = 3;

    // Basic operations
    int sum = x + y;        // 13
    int diff = x - y;       // 7
    int prod = x * y;       // 30
    int quot = x / y;       // 3
    int rem = x % y;        // 1
    int power = 2 ^* 8;     // 256

    // Compound assignments
    x += 5;   // x = 15
    x -= 3;   // x = 12
    x *= 2;   // x = 24
    x /= 4;   // x = 6
    x %= 5;   // x = 1

    // Floating point
    float a = 10.5f;
    float b = 2.5f;

    float fsum = a + b;     // 13.0
    float fdiff = a - b;    // 8.0
    float fprod = a * b;    // 26.25
    float fquot = a / b;    // 4.2

    a += 1.5f;  // 12.0
    a -= 2.0f;  // 10.0
    a *= 3.0f;  // 30.0
    a /= 5.0f;  // 6.0
    int i = 10;
    float f = 3.14f;
    double d = 2.718;

    // Float promotion
    double result1 = f + d;  // float → double

    // Integer operations
    int result2 = i + i;
    int result3 = i * 2;

    // Compound with different types
    i += 5;
    f += 1.5f;
    d += 0.001;
    char start = 'A';
    char end = 'Z';
    char space = ' ';
    char newline = '\n';
    char tab = '\t';

    // Reassignment
    start = 'B';
    end = 'Y';
    bool yes = true;
    bool no = false;

    // Flipping
    yes = false;
    no = true;
    yes = true;
    qbool schrodinger = both;      // 0b11
    qbool alive = qtrue;           // 0b10
    qbool dead = qfalse;           // 0b01
    qbool nul = none;             // 0b00

    // State transitions
    schrodinger = qtrue;
    alive = both;
    dead = none;
    nul = qfalse;
    string hello = "Hello";
    string world = "World";
    string exclaim = "!";

    string non = "";
    string quote = "She said \"Hi\"";
    string path = "C:\\Users\\Luca(JK its ~/C^4 becuase i dont use the disgusting windows powershell)";
    int base = 2;
    int exp = 10;

    float fbase = 2.0f;
    float fexp = 3.0f;
    float fresult = fbase ^* fexp;  // 8.0

    double dbase = 1.5;
    double dexp = 2.0;
    double dresult = dbase ^* dexp;  // 2.25
    int xdd = 5;
    int ydd = 10;

    bool eq = xdd == ydd;      // false
    bool ne = xdd != ydd;      // true
    bool lt = xdd < ydd;       // true
    bool gt = xdd > ydd;       // false
    bool lte = xdd <= ydd;     // true
    bool gte = xdd >= ydd;     // false
    int result = 0;

    if (xdd > 3) {
        result = 10;
    } else {
        result = 20;
    }
    i = 0;
    sum = 0;
    while (i < 5) {
        sum += i;
        i += 1;
    }
    sum = 0;
    for (int xyz = 0; xyz < 5; xyz += 1) {
        sum += xyz;
    }
    bool ata = true;
    bool btb = false;
    bool and_test = ata && btb;
    bool or_test = ata || btb;
    bool xor_test = ata ^ btb;
    bool not_test = !ata;
    switch (sum) {
        case 1:
            break;
        case 5:
            sum = 2;
            break;
        default:
            sum = 0;
            break;
    }
    qbool both_tester = both;
    qif(both_tester) {
        sum += 123;
    } qelse {
        sum += 321;
    }
    x = 0;

    qswitch (both_tester) {
        case b:
            x = 1;
            break;
        case t:
            x = 2;
    }
    qbool q1 = 5 === 5; 
    qbool q2 = 5 !== 5;
    qbool q3 = 5 === 10;
    qbool q4 = 5 !== 10;

    qbool q5 = 5 === 5.0;
    qbool q6 = "hi" === "hi";
    qbool q7 = "hi" !== "bye";

    std::qout << q1 << q2 << q3 << q4 << q5 << q6 << q7;
    int t = time();
    seed(t);
    
    float r = random();
    int ri = random(10);
    int rr = random(5, 15);
    
    string s = "Hello";
    int l = len(s);
    string upper = to_upper(s);
    string lower = to_lower(s);
    
    bool c = contains(s, "ell");
    bool sw = startswith(s, "Hel");
    bool ew = endswith(s, "lo");
    
    string sub = substring(s, 1, 3);
    string trimmed = trim("  hi  ");
    string replaced = replace(s, "l", "L");
    
    i = to_int("42");
    f = to_float("3.14");
    
    string si = to_string(123);
    string sf = to_string(3.14f);
    
    print("Hello ");
    println("World");
    println("Before grid");
    int grid[][] = [[1, 2,  3], [3, 4]];
    println("After grid creation");
    int val = grid[0][1];
    println("After grid access");
    std::qout << val << grid;
    println("After printing val + grid");
    int regular[][] = [[1, 2], [3, 4]];
    
    // Jagged 2D
    int jagged[][] = [
        [
            1, 
            2, 
            3
        ], 
        [
            4, 
            5
        ]
    ];
    // Jagged 3D
    int deep[][][] = [
        [
            [
                1, 
                2
            ], 
            [
                3
            ]
        ], 
        [
            [
                4, 
                5, 
                6
            ]
        ]
    ];
    
    std::qout << "Regular: " << regular << '\n';
    std::qout << "Jagged: " << jagged << '\n';
    std::qout << "Deep: " << deep << '\n';
    
    // Access
    int val1 = jagged[0][2];  // 3
    int val2 = jagged[1][1];  // 5
    int[] array1 = make_array();
    print_array(array1, 3);
    int[] brray1, string strnthing = get_both();
    std::qout << val1 << " " << val2 << '\n';
    list<int> aList = [1, 2, 3, 4];
    std::qout << aList[0] << aList[1];
    int arr[] = [1, 2, 3, 4, 5];
    
    println("Array length:");
    int arr_len = arr.length;
    std::qout << arr_len << '\n';
    
    println("Array foreach:");
    foreach (int vz in arr) {
        std::qout << vz << " ";
    }
    println("");
    
    // Test lists
    list<int> myList = [10, 20, 30];
    
    println("List length:");
    int list_len = myList.length;
    std::qout << list_len << '\n';
    
    println("List push:");
    myList.push(40);
    myList.push(50);
    std::qout << myList.length << '\n';
    
    println("List foreach:");
    foreach (int y in myList) {
        std::qout << y << " ";
    }
    println("");
    
    println("List pop:");
    myList.pop();
    std::qout << myList.length << '\n';
    
    println("List access:");
    std::qout << myList[0] << " " << myList[1] << '\n';
    println("Test 1: Return list from function");
    list<int> listy = make_list();
    println("List length:");
    std::qout << listy.length << '\n';
    println("List contents:");
    foreach (int xccc in listy) {
        std::qout << xccc << " ";
    }
    println("");
    
    println("Test 2: Pass list to function");
    list<int> doubled = double_list(listy);
    println("Doubled list:");
    foreach (int xccc in doubled) {
        std::qout << xccc << " ";
    }
    println("");
    
    println("Test 3: Multi-return with list");
    list<int> datacc, int countcc = get_list_and_count();
    println("Count:");
    std::qout << countcc << '\n';
    println("Data:");
    foreach (int xyzd in datacc) {
        std::qout << xyzd << " ";
    }
    println("");
    // ========================================
    // MAP TESTS
    // ========================================

    println("=== MAP CREATION ===");
    map<string, int> ages = {
        "Alice": 25,
        "Bob": 30,
        "Charlie": 35
    };

    std::qout << ages << '\n';

    println("=== MAP ACCESS ===");
    std::qout << ages["Alice"] << '\n';
    std::qout << ages["Bob"] << '\n';
    std::qout << ages["Charlie"] << '\n';

    println("=== MAP SET (NEW KEY) ===");
    ages["Dave"] = 40;
    std::qout << ages << '\n';

    println("=== MAP SET (UPDATE) ===");
    ages["Alice"] = 26;
    std::qout << ages << '\n';

    println("=== MAP SIZE ===");
    std::qout << ages.size << '\n';

    println("=== MAP HAS ===");
    std::qout << ages.has("Alice") << '\n';
    std::qout << ages.has("Bob") << '\n';
    std::qout << ages.has("Eve") << '\n';

    println("=== MAP REMOVE ===");
    ages.remove("Bob");
    std::qout << ages << '\n';
    std::qout << ages.has("Bob") << '\n';
    std::qout << ages.size << '\n';

    println("=== MAP KEYS ===");
    foreach (string key in ages.keys()) {
        std::qout << key << ": " << ages[key] << '\n';
    }
    println("=== MAP WITH INT KEYS ===");
    map<int, string> names = {
        1: "Alice",
        2: "Bob",
        3: "Charlie"
    };

    std::qout << names << '\n';
    std::qout << names[2] << '\n';

    names[4] = "Dave";
    std::qout << names << '\n';

    println("=== EMPTY MAP ===");
    map<string, int> empty_map = {};
    std::qout << empty_map << '\n';
    std::qout << empty_map.size << '\n';

    empty_map["first"] = 1;
    std::qout << empty_map << '\n';
    std::qout << empty_map.size << '\n';

    println("=== MAP LITERAL ASSIGNMENT ===");
    map<string, int> myMap = { "x": 10, "y": 20 };
    std::qout << myMap << '\n';
    std::qout << myMap["x"] << '\n';

    println("=== MAP AS PARAMETER ===");
    void print_map_size(map<string, int> m) {
        std::qout << m.size << '\n';
    }

    print_map_size(ages);

    println("=== ALL MAP TESTS COMPLETE ===");
    println("=== SPREAD TESTS ===");
    
    // ========================================
    // TEST 1: Spread in array literals
    // ========================================
    println("\n--- Test 1: Spread arrays into array ---");
    int arr1[] = [1, 2, 3];
    int arr2[] = [4, 5];
    int combined[] = [@arr1, @arr2, 6, 7];
    
    foreach (int xdxdxdx in combined) {
        std::qout << xdxdxdx << " ";
    }
    println("");  // Expected: 1 2 3 4 5 6 7
    
    // ========================================
    // TEST 2: Spread in list literals
    // ========================================
    println("\n--- Test 2: Spread into list ---");
    list<int> list1 = [10, 20];
    list<int> list2 = [30, 40];
    list<int> merged = [@list1, @list2, 50];
    
    foreach (int xdxdxdx in merged) {
        std::qout << xdxdxdx << " ";
    }
    println("");  // Expected: 10 20 30 40 50
    
    // ========================================
    // TEST 3: Spread array into list
    // ========================================
    println("\n--- Test 3: Spread array into list ---");
    int nums[] = [100, 200, 300];
    println("Past array creation");
    list<int> fromArray = [@nums, 400];
    println("Past list creation");
    foreach (int xxxdxxx in fromArray) {
        std::qout << xxxdxxx << " ";
    }
    println("");  // Expected: 100 200 300 400
    
    // ========================================
    // TEST 4: Spread list into array
    // ========================================
    println("\n--- Test 4: Spread list into array ---");
    list<int> ListList = [5, 6, 7];
    println("Past list creation");
    int arrFromList[] = [1, 2, @ListList, 8];
    println("Past actual spreading");
    foreach (int xcxxc in arrFromList) {
        std::qout << xcxxc << " ";
    }
    println("");  // Expected: 1 2 5 6 7 8
    
    // ========================================
    // TEST 5: Multiple spreads
    // ========================================
    println("\n--- Test 5: Multiple spreads ---");
    int a[] = [1, 2];
    int b[] = [3, 4];
    int c[] = [5, 6];
    int multi[] = [@a, @b, @c];
    
    foreach (int xcxcxc in multi) {
        std::qout << xcxcxc << " ";
    }
    println("");  // Expected: 1 2 3 4 5 6
    
    // ========================================
    // TEST 6: Spread in function calls
    // ========================================
    println("\n--- Test 6: Spread in function calls ---");
    
    void print_three(int x, int y, int z) {
        std::qout << "x=" << x << " y=" << y << " z=" << z << '\n';
    }
    
    int args[] = [10, 20, 30];
    print_three(@args);  // Expected: x=10 y=20 z=30
    
    // ========================================
    // TEST 7: Spread with lambda
    // ========================================
    println("\n--- Test 7: Spread with lambda ---");
    
    function sumsum = fn(int a, int b, int c) -> int {
        return a + b + c;
    };
    
    int values[] = [5, 10, 15];
    int result = sumsum(@values);
    std::qout << "Sum: " << result << '\n';  // Expected: Sum: 30
    
    // ========================================
    // TEST 8: Mixed spread and regular args
    // ========================================
    println("\n--- Test 8: Mixed spread and regular ---");
    
    void print_five(int a, int b, int c, int d, int e) {
        std::qout << a << " " << b << " " << c << " " << d << " " << e << '\n';
    }
    
    int first[] = [1, 2];
    print_five(@first, 3, 4, 5);  // Expected: 1 2 3 4 5
    
    // ========================================
    // TEST 9: Spread strings
    // ========================================
    println("\n--- Test 9: Spread strings ---");
    
    string names1[] = ["Alice", "Bob"];
    string names2[] = ["Charlie", "Dave"];
    string allNames[] = [@names1, @names2];
    
    foreach (string namenamename in allNames) {
        std::qout << namenamename << " ";
    }
    println("");  // Expected: Alice Bob Charlie Dave
    
    // ========================================
    // TEST 10: Empty spread
    // ========================================
    println("\n--- Test 10: Empty spread ---");
    
    int empty[] = [];
    int withEmpty[] = [1, @empty, 2];
    println(typeof(empty));
    foreach (int xccccccc in withEmpty) {
        std::qout << xccccccc << " ";
    }
    println("");  // Expected: 1 2
    println("\n=== ALL SPREAD TESTS COMPLETE ===");
    println("=== STRUCT TESTS ===");
    
    // Test 1: Basic struct creation
    println("\n--- Test 1: Basic struct ---");
    Point p = {10, 20};
    println("Point created");
    std::qout << "x: " << p.x << '\n';
    std::qout << "y: " << p.y << '\n';
    
    // Test 2: Struct modification
    println("\n--- Test 2: Modify fields ---");
    p.x = 30;
    p.y = 40;
    std::qout << "x: " << p.x << '\n';
    std::qout << "y: " << p.y << '\n';
    
    // Test 3: Struct as function parameter
    println("\n--- Test 3: Function parameter ---");
    void printPoint(Point pt) {
        std::qout << "Point(" << pt.x << ", " << pt.y << ")\n";
    }
    printPoint(p);
    
    // Test 4: Struct as return value
    println("\n--- Test 4: Function return ---");
    Point makePoint(int x, int y) {
        Point result = {x, y};
        return result;
    }
    Point p2 = makePoint(50, 60);
    printPoint(p2);
    
    // Test 5: Nested structs
    println("\n--- Test 5: Nested structs ---");
    Rectangle rect = {{0, 0}, {100, 100}};
    std::qout << "Top-left: (" << rect.topLeft.x << ", " << rect.topLeft.y << ")\n";
    std::qout << "Bottom-right: (" << rect.bottomRight.x << ", " << rect.bottomRight.y << ")\n";
    
    println("\n=== ALL STRUCT TESTS COMPLETE ===");
    println("\n=== UNION TESTS ===");

    // Test 1: Basic union with literals and types
    println("\n--- Test 1: Literal variants ---");
    type Result = "ok" | "error" | int;

    Result r1 = "ok";
    if (r1 == "ok") {
        println("r1 is ok");
    }

    Result r2 = "error";
    if (r2 == "error") {
        println("r2 is error");
    }

    Result r3 = 42;
    if (r3 == 42) {
        println("r3 is 42");
    }

    // Test 2: Type-only union
    println("\n--- Test 2: Type-only union ---");
    type Value = int | string | float;

    Value vrv1 = 100;
    std::qout << "v1: " << vrv1 << '\n';

    Value vrv2 = "hello";
    std::qout << "v2: " << vrv2 << '\n';

    Value vrv3 = 3.14f;
    std::qout << "v3: " << vrv3 << '\n';

    // Test 3: Comparison
    println("\n--- Test 3: Comparisons ---");
    if (vrv1 == 100) println("v1 == 100: PASS");
    if (vrv2 == "hello") println("v2 == hello: PASS");
    if (vrv3 == 3.14f) println("v3 == 3.14: PASS");

    if (vrv1 != "wrong") println("v1 != wrong: PASS");
    if (vrv2 != 999) println("v2 != 999: PASS");

    // Test 4: Reassignment
    println("\n--- Test 4: Reassignment ---");
    type Multi = 1 | 2 | 3 | string | bool;

    Multi mrv = 1;
    std::qout << "m = " << mrv << '\n';

    mrv = "changed";
    std::qout << "m = " << mrv << '\n';

    mrv = true;
    std::qout << "m = " << mrv << '\n';

    mrv = 3;
    std::qout << "m = " << mrv << '\n';

    // Test 5: Union in if statements
    println("\n--- Test 5: Control flow ---");
    type Status = "pending" | "done" | "failed";

    Status srvrv = "pending";
    if (srvrv == "pending") {
        println("Status is pending");
        srvrv = "done";
    }

    if (srvrv == "done") {
        println("Status is done");
    }

    // Test 6: Union with numbers
    println("\n--- Test 6: Numeric variants ---");
    type Code = 200 | 404 | 500 | int;

    Code codeValue = 200;
    if (codeValue == 200) println("Success!");

    codeValue = 404;
    if (codeValue == 404) println("Not found!");

    codeValue = 999;
    std::qout << "Custom code: " << c << '\n';

    // Test 7: Mixed types
    println("\n--- Test 7: Mixed types ---");
    type Mixed = int | float | string | bool | char;

    Mixed mx1 = 42;
    Mixed mx2 = 3.14f;
    Mixed mx3 = "test";
    Mixed mx4 = true;
    Mixed mx5 = 'A';

    std::qout << mx1 << " " << mx2 << " " << mx3 << " " << mx4 << " " << mx5 << '\n';

    // Test 8: Union equality
    println("\n--- Test 8: Equality tests ---");
    type Pair = int | string;

    Pair p1 = 10;
    Pair p2222 = 10;
    Pair p3 = 20;

    if (p1 == p2222) println("p1 == p2: PASS");
    if (p1 != p3) println("p1 != p3: PASS");

    Pair p4 = "same";
    Pair p5 = "same";
    Pair p6 = "different";

    if (p4 == p5) println("p4 == p5: PASS");
    if (p4 != p6) println("p4 != p6: PASS");

    // Test 9: Union in functions
    println("\n--- Test 9: Functions ---");
    type Response = "success" | "failure" | int;

    Response process(int code) {
        if (code == 0) {
            return "success";
        } else if (code == 1) {
            return "failure";
        } else {
            return code;
        }
    }

    Response resp1 = process(0);
    if (resp1 == "success") println("Process returned success");

    Response resp2 = process(1);
    if (resp2 == "failure") println("Process returned failure");

    Response resp3 = process(42);
    if (resp3 == 42) println("Process returned 42");

    println("\n=== ALL UNION TESTS COMPLETE ===");
    println("\n=== QIN TEST (USACO FENCE) ===");
    int aaaaa = 0;
    int bbbbb = 0;
    int ccccc = 0;
    int ddddd = 0;
    std::qout << "Type two numbers seperated by a space";
    std::qin >> aaaaa >> bbbbb;
    std::qout << "Type two numbers seperated by a space";
    std::qin >> ccccc >> ddddd;
    if (aaaaa < ccccc && bbbbb < ccccc || ccccc < aaaaa &&  ddddd < aaaaa) {
        std::qout << bbbbb - aaaaa + ddddd - ccccc;
    }
    else if (aaaaa < ccccc) {
        if (bbbbb < ddddd) {
            std::qout << ddddd - aaaaa;
        }  else {
            std::qout << bbbbb - aaaaa;
        }
    } else {
        if (bbbbb < ddddd) {
            std::qout << ddddd - ccccc;
        } else {
            std::qout << bbbbb - ccccc;
        }
    }
    println("\n=== QIN SUCCESS ===");
    println("\n=== FILE I/O TESTS ===");

    // Test 1: Write to file
    println("\n--- Test 1: Write to file ---");
    string outFile = fopen("test_output.txt", "w");
    fwrite(outFile, "Line 1: Hello from QC!");
    fwrite(outFile, "Line 2: File I/O works!");
    fwrite(outFile, "Line 3: Amazing!");
    fclose(outFile);
    println("Wrote 3 lines to test_output.txt");

    // Test 2: Read from file
    println("\n--- Test 2: Read from file ---");
    string inFile = fopen("test_output.txt", "r");
    string line1 = fread(inFile);
    string line2 = fread(inFile);
    string line3 = fread(inFile);
    fclose(inFile);

    println("Read from file:");
    println(line1);
    println(line2);
    println(line3);

    // Test 3: Append to file
    println("\n--- Test 3: Append to file ---");
    string appendFile = fopen("test_output.txt", "a");
    fwrite(appendFile, "Line 4: Appended!");
    fclose(appendFile);

    string readAgain = fopen("test_output.txt", "r");
    println("After append:");
    string line;
    line = fread(readAgain);
    while (line != "") {
        println(line);
        line = fread(readAgain);
    }
    fclose(readAgain);

    println("\n=== ALL FILE I/O TESTS COMPLETE ===");
    println("\n=== TYPE ALIAS TESTS ===");

    // Test 1: Basic aliases
    println("\n--- Test 1: Basic type aliases ---");
    type MyInt = int;
    type MyString = string;
    type MyFloat = float;

    MyInt xxxxxxxx = 42;
    MyString sxxxxxx = "Hello, aliases!";
    MyFloat fxxxxxx = 3.14f;

    println("MyInt: " + to_string(xxxxxxxx));
    println("MyString: " + sxxxxxx);
    println("MyFloat: " + to_string(fxxxxxx));
    println("\n=== ALL TYPE ALIAS TESTS COMPLETE ===");
    println("\n=== ENUM TESTS ===");

    // Test 1: Basic enum with integer values
    println("\n--- Test 1: Integer enum ---");
    enum HttpStatus {
        OK = 200;
        NotFound = 404;
        ServerError = 500;
    }

    HttpStatus statusCode = HttpStatus.OK;
    println("Status: 200");

    statusCode = HttpStatus.NotFound;
    println("Status: 404");

    // Test 2: String enum
    println("\n--- Test 2: String enum ---");
    enum TierLevel {
        Basic = "Basic";
        Premium = "Premium";
        Enterprise = "Enterprise";
    }

    TierLevel userTier = TierLevel.Basic;
    println("Tier: Basic");

    userTier = TierLevel.Premium;
    println("Tier: Premium");

    // Test 3: Mixed type enum
    println("\n--- Test 3: Mixed enum ---");
    enum ConfigValue {
        MaxRetries = 3;
        TimeoutMsg = "Timeout!";
        DefaultRate = 1.5;
    }

    ConfigValue retries = ConfigValue.MaxRetries;
    println("Retries: 3");

    ConfigValue msg = ConfigValue.TimeoutMsg;
    println("Message: Timeout!");

    // Test 4: Enum comparison
    println("\n--- Test 4: Comparisons ---");
    HttpStatus status1 = HttpStatus.OK;
    HttpStatus status2 = HttpStatus.OK;

    if (status1 == HttpStatus.OK) {
        println("status1 is OK ✓");
    }

    if (status1 == status2) {
        println("status1 == status2 ✓");
    }

    if (status1 != HttpStatus.NotFound) {
        println("status1 != NotFound ✓");
    }

    // Test 5: Enum reassignment
    println("\n--- Test 5: Reassignment ---");
    TierLevel currentTier = TierLevel.Basic;
    println("Started as Basic");

    currentTier = TierLevel.Enterprise;
    println("Upgraded to Enterprise");

    // Test 6: Enum in if statements
    println("\n--- Test 6: Control flow ---");
    HttpStatus responseCode = HttpStatus.NotFound;

    if (responseCode == HttpStatus.OK) {
        println("Success!");
    } else if (responseCode == HttpStatus.NotFound) {
        println("Page not found! ✓");
    } else {
        println("Server error!");
    }

    // Test 7: Enum in switch
    println("\n--- Test 7: Switch on enum ---");
    TierLevel planType = TierLevel.Premium;

    switch (planType) {
        case TierLevel.Basic:
            println("Basic plan");
            break;
        case TierLevel.Premium:
            println("Premium plan ✓");
            break;
        case TierLevel.Enterprise:
            println("Enterprise plan");
            break;
    }

    // Test 8: Extract enum to primitive
    println("\n--- Test 8: Extract to primitive ---");
    HttpStatus code = HttpStatus.ServerError;
    int numCode = code;
    println("Code as int: 500");

    TierLevel plan = TierLevel.Enterprise;
    string planName = plan;
    println("Plan as string: Enterprise");

    // Test 9: Enum in functions
    println("\n--- Test 9: Functions ---");
    HttpStatus getStatus(int errorCode) {
        if (errorCode == 0) {
            return HttpStatus.OK;
        } else if (errorCode == 1) {
            return HttpStatus.NotFound;
        } else {
            return HttpStatus.ServerError;
        }
    }

    HttpStatus result1 = getStatus(0);
    if (result1 == HttpStatus.OK) println("getStatus(0) = OK ✓");

    HttpStatus result2 = getStatus(1);
    if (result2 == HttpStatus.NotFound) println("getStatus(1) = NotFound ✓");

    // Test 10: Multi-return with enum
    println("\n--- Test 10: Multi-return ---");
    HttpStatus, string checkEndpoint() {
        return HttpStatus.OK, "Success";
    }

    HttpStatus respStatus, string respMsg = checkEndpoint();
    if (respStatus == HttpStatus.OK) {
        println("Response OK ✓");
    }
    println("Message: " + respMsg);

    // Test 11: Enum with typeof
    println("\n--- Test 11: typeof ---");
    TierLevel myPlan = TierLevel.Premium;
    string typeofPlan = typeof(myPlan);
    println("typeof(Premium): " + typeofPlan);  // Should print "string"

    HttpStatus myStatus = HttpStatus.OK;
    string statusType = typeof(myStatus);
    println("typeof(OK): " + statusType);  // Should print "int"

    // Test 12: Enum in while loop
    println("\n--- Test 12: While loop ---");
    HttpStatus loopStatus = HttpStatus.OK;
    int counter = 0;

    while (loopStatus == HttpStatus.OK && counter < 3) {
        println("Loop iteration");
        counter += 1;
    }
    println("Loop complete ✓");

    // Test 13: Enum in for loop
    println("\n--- Test 13: For loop ---");
    for (int idx = 0; idx < 2; idx += 1) {
        HttpStatus iterStatus = HttpStatus.OK;
        if (iterStatus == HttpStatus.OK) {
            println("Iteration OK");
        }
    }

    // Test 14: Unary operators on enum
    println("\n--- Test 14: Unary operators ---");
    HttpStatus negStatus = HttpStatus.ServerError;
    int negValue = -negStatus;
    println("Negated: -500");

    // Test 15: Enum equality chain
    println("\n--- Test 15: Equality chain ---");
    TierLevel tier1 = TierLevel.Basic;
    TierLevel tier2 = TierLevel.Basic;
    TierLevel tier3 = TierLevel.Premium;

    if (tier1 == tier2 && tier2 != tier3) {
        println("Equality chain works ✓");
    }

    println("\n=== ALL ENUM TESTS COMPLETE ===");
    println("\n=== BASIC CLASS TESTS ===");
    println("\n--- Test 1: Class with fields ---");
    class Dog {
        string name;
        int age;
        Dog(string name, int age) {
            this.name = name;
            this.age = age;
        }
    }

    Dog myDog = Dog("Buddy", 5);
    println("Dog name: " + myDog.name);
    println("Dog age: " + to_string(myDog.age));

    println("\n--- Test 2: Method with this ---");
    class Cat {
        string name;
        int lives;
        Cat(string name, int lives) {
            this.lives = lives;
            this.name = name;
        }
        void meow() {
            println(this.name + " says meow!");
        }
        
        void useLives(int count) {
            this.lives = this.lives - count;
            println(this.name + " has " + to_string(this.lives) + " lives left");
        }
    }

    Cat myCat = Cat("Whiskers", 9);
    myCat.meow();
    myCat.useLives(3);

    println("\n--- Test 3: Method with return ---");
    class Calculator {
        int value;
        Calculator(int value) {
            this.value = value;
        }
        int add(int x) {
            this.value = this.value + x;
            return this.value;
        }
        
        int getValue() {
            return this.value;
        }
    }

    Calculator calc = Calculator(10);
    int result = calc.add(5);
    println("After add(5): " + to_string(result));
    println("getValue(): " + to_string(calc.getValue()));

    println("\n--- Test 4: Multiple methods ---");
    class Counter {
        int count;
        Counter(int count) {
            this.count = count;
        }
        void increment() {
            this.count = this.count + 1;
        }
        
        void decrement() {
            this.count = this.count - 1;
        }
        
        void reset() {
            this.count = 0;
        }
        
        int get() {
            return this.count;
        }
    }

    Counter counter = Counter(0);
    counter.increment();
    counter.increment();
    counter.increment();
    println("Count: " + to_string(counter.get()));
    counter.decrement();
    println("After decrement: " + to_string(counter.get()));
    counter.reset();
    println("After reset: " + to_string(counter.get()));

    println("\n--- Test 5: Field modification ---");
    class Person {
        string name;
        int age;
        Person(string name, int age) {
            this.age = age;
            this.name = name;
        }
        void birthday() {
            this.age = this.age + 1;
            println(this.name + " is now " + to_string(this.age));
        }
    }

    Person alice = Person("Alice", 25);
    alice.birthday();
    alice.birthday();

    println("\n--- Test 6: Multiple calls ---");
    class Robot {
        string status;
        Robot(string status) {
            this.status = status;
        }
        void start() {
            this.status = "running";
            println("Robot started");
        }
        
        void stop() {
            this.status = "stopped";
            println("Robot stopped");
        }
        
        void getStatus() {
            println("Status: " + this.status);
        }
    }

    Robot bot = Robot("idle");
    bot.start();
    bot.getStatus();
    bot.stop();
    bot.getStatus();

    println("\n=== ALL BASIC CLASS TESTS COMPLETE ===");
    println("\n=== INHERITANCE TESTS ===");

    // Test 1: Basic inheritance
    println("\n--- Test 1: Basic inheritance ---");
    class Animal {
        string species;
        int age_years;
        
        Animal(string species, int age_years) {
            this.species = species;
            this.age_years = age_years;
        }
        
        void makeSound() {
            println(this.species + " makes a sound!");
        }
        
        void getAge() {
            println(this.species + " is " + to_string(this.age_years) + " years old");
        }
    }

    class DogInherit : Animal {
        string breed_name;
        
        DogInherit(string breed_name, int age_years) {
            this.breed_name = breed_name;
            this.species = "Dog";
            this.age_years = age_years;
        }
        
        void bark() {
            println(this.breed_name + " barks: Woof!");
        }
    }

    DogInherit myDogInherit = DogInherit("Golden Retriever", 3);
    myDogInherit.makeSound();  // Inherited method
    myDogInherit.getAge();     // Inherited method
    myDogInherit.bark();       // Own method
    println("Breed: " + myDogInherit.breed_name);
    println("Species: " + myDogInherit.species);  // Inherited field
    println("Age: " + to_string(myDogInherit.age_years));  // Inherited field

    // Test 2: Method overriding
    println("\n--- Test 2: Method overriding ---");
    class Vehicle {
        string type_name;
        int speed_mph;
        
        Vehicle(string type_name, int speed_mph) {
            this.type_name = type_name;
            this.speed_mph = speed_mph;
        }
        
        void describe() {
            println("This is a " + this.type_name);
        }
        
        void getSpeed() {
            println("Speed: " + to_string(this.speed_mph) + " mph");
        }
    }

    class CarInherit : Vehicle {
        int num_doors;
        
        CarInherit(int speed_mph, int num_doors) {
            this.num_doors = num_doors;
            this.type_name = "Car";
            this.speed_mph = speed_mph;
        }
        
        void describe() {  // Override!
            println("This is a car with " + to_string(this.num_doors) + " doors");
        }
    }

    CarInherit myCar = CarInherit(120, 4);
    myCar.describe();   // Should call CarInherit's version
    myCar.getSpeed();   // Inherited, not overridden

    // Test 3: Multi-level inheritance
    println("\n--- Test 3: Multi-level inheritance ---");
    class LivingThing {
        bool is_alive;
        
        LivingThing(bool is_alive) {
            this.is_alive = is_alive;
        }
        
        void checkLife() {
            if (this.is_alive) {
                println("It's alive!");
            } else {
                println("It's not alive");
            }
        }
    }

    class PlantLife : LivingThing {
        string plant_type;
        
        PlantLife(string plant_type) {
            this.plant_type = plant_type;
            this.is_alive = true;
        }
        
        void photosynthesize() {
            println(this.plant_type + " is photosynthesizing");
        }
    }

    class FlowerPlant : PlantLife {
        string color_name;
        
        FlowerPlant(string plant_type, string color_name) {
            this.color_name = color_name;
            this.plant_type = plant_type;
            this.is_alive = true;
        }
        
        void bloom() {
            println(this.color_name + " " + this.plant_type + " is blooming!");
        }
    }

    FlowerPlant rose = FlowerPlant("Rose", "Red");
    rose.checkLife();        // From LivingThing
    rose.photosynthesize();  // From PlantLife
    rose.bloom();            // From FlowerPlant
    println("Color: " + rose.color_name);
    println("Type: " + rose.plant_type);
    if (rose.is_alive) {
        println("Rose is alive!");
    }

    // Test 4: Access control - public
    println("\n--- Test 4: Public access ---");
    class BankAccount {
        public string account_holder;
        public int balance_dollars;
        
        BankAccount(string account_holder, int balance_dollars) {
            this.account_holder = account_holder;
            this.balance_dollars = balance_dollars;
        }
        
        public void deposit(int amount) {
            this.balance_dollars = this.balance_dollars + amount;
            println("Deposited: $" + to_string(amount));
        }
    }

    class SavingsAccount : BankAccount {
        public float interest_rate;
        
        SavingsAccount(string account_holder, int balance_dollars, float interest_rate) {
            this.interest_rate = interest_rate;
            this.account_holder = account_holder;
            this.balance_dollars = balance_dollars;
        }
        
        public void addInterest() {
            int interest_amount = to_int(this.balance_dollars * this.interest_rate);
            this.balance_dollars = this.balance_dollars + interest_amount;
            println("Added interest: $" + to_string(interest_amount));
        }
    }

    SavingsAccount savings = SavingsAccount("Alice", 1000, 0.05f);
    println("Holder: " + savings.account_holder);  // Public, accessible
    println("Balance: $" + to_string(savings.balance_dollars));  // Public
    savings.deposit(500);  // Public method
    savings.addInterest();
    println("New balance: $" + to_string(savings.balance_dollars));

    // Test 5: Access control - private
    println("\n--- Test 5: Private access ---");
    class SecureBox {
        private string secret_code;
        public bool is_locked;
        
        SecureBox(string secret_code) {
            this.secret_code = secret_code;
            this.is_locked = true;
        }
        
        public void unlock(string code_attempt) {
            if (code_attempt == this.secret_code) {  // Can access private in same class
                this.is_locked = false;
                println("Box unlocked!");
            } else {
                println("Wrong code!");
            }
        }
    }

    SecureBox box = SecureBox("1234");
    println("Is locked: " + to_string(box.is_locked));  // Public field OK
    // println(box.secret_code);  // ERROR: private field!
    box.unlock("0000");  // Wrong code
    box.unlock("1234");  // Correct code
    println("Is locked now: " + to_string(box.is_locked));

    // Test 6: Access control - protected
    println("\n--- Test 6: Protected access ---");
    class GameCharacter {
        protected int health_points;
        public string char_name;
        
        GameCharacter(string char_name, int health_points) {
            this.char_name = char_name;
            this.health_points = health_points;
        }
        
        public void takeDamage(int damage_amount) {
            this.health_points = this.health_points - damage_amount;
            println(this.char_name + " took " + to_string(damage_amount) + " damage");
        }
    }

    class Warrior : GameCharacter {
        public int armor_value;
        
        Warrior(string char_name, int health_points, int armor_value)  {
            this.armor_value = armor_value;
            this.char_name = char_name;
            this.health_points = health_points;
        }
        
        public void showHealth() {
            // Can access protected field from parent!
            println(this.char_name + " HP: " + to_string(this.health_points));
        }
        public void defend() {
            int reduced_damage = 10 - this.armor_value;
            if (reduced_damage < 0) {
                reduced_damage = 0;
            }
            this.takeDamage(reduced_damage);
        }
    }

    Warrior hero = Warrior("Conan", 100, 5);
    hero.showHealth();  // Can access protected through child method
    hero.takeDamage(20);
    hero.showHealth();
    hero.defend();
    hero.showHealth();
    // println(hero.health_points);  // ERROR: protected, not accessible outside!

    // Test 7: Field shadowing
    println("\n--- Test 7: Field shadowing ---");
    class BaseClass {
        public int value_num;
        
        BaseClass(int value_num) {
            this.value_num = value_num;
        }
        
        public void showBase() {
            println("Base value: " + to_string(this.value_num));
        }
    }

    class DerivedClass : BaseClass {
        public int value_num;  // Shadows parent field!
        
        DerivedClass(int base_val, int derived_val) {
            this.value_num = derived_val;  // Sets child's field
            this.value_num = base_val;
        }
        
        public void showDerived() {
            println("Derived value: " + to_string(this.value_num));
        }
    }

    DerivedClass derived = DerivedClass(10, 20);
    derived.showBase();     // Shows parent's value (10)
    derived.showDerived();  // Shows child's value (20)

    // Test 8: Complex inheritance chain
    println("\n--- Test 8: Complex chain ---");
    class Employee {
        public string emp_name;
        public int emp_id;
        
        Employee(string emp_name, int emp_id) {
            this.emp_name = emp_name;
            this.emp_id = emp_id;
        }
        
        public void work() {
            println(this.emp_name + " is working");
        }
    }

    class Manager : Employee {
        public int team_size;
        
        Manager(string emp_name, int emp_id, int team_size) {
            this.team_size = team_size;
            this.emp_name = emp_name;
            this.emp_id = emp_id;
        }
        
        public void manage() {
            println(this.emp_name + " is managing " + to_string(this.team_size) + " people");
        }
    }

    class Director : Manager {
        public string department_name;
        
        Director(string emp_name, int emp_id, int team_size, string department_name)  {
            this.department_name = department_name;
            this.team_size = team_size;
            this.emp_name = emp_name;
            this.emp_id = emp_id;
        }
        
        public void direct() {
            println(this.emp_name + " directs the " + this.department_name + " department");
        }
    }

    Director ceo = Director("Bob", 1, 50, "Engineering");
    ceo.work();     // From Employee
    ceo.manage();   // From Manager
    ceo.direct();   // From Director
    println("ID: " + to_string(ceo.emp_id));
    println("Team: " + to_string(ceo.team_size));
    println("Dept: " + ceo.department_name);

    // Test 9: Multiple fields from parent
    println("\n--- Test 9: Multiple inherited fields ---");
    class Rectangle2D {
        public int width_val;
        public int height_val;
        public string color_str;
        
        Rectangle2D(int width_val, int height_val, string color_str) {
            this.width_val = width_val;
            this.height_val = height_val;
            this.color_str = color_str;
        }
        
        public int area() {
            return this.width_val * this.height_val;
        }
    }

    class ColoredBox : Rectangle2D {
        public bool has_border;
        
        ColoredBox(int width_val, int height_val, string color_str, bool has_border) {
            Rectangle2D(width_val, height_val, color_str);
            this.has_border = has_border;
        }
        
        public void describe() {
            println("Box: " + to_string(this.width_val) + "x" + to_string(this.height_val));
            println("Color: " + this.color_str);
            println("Area: " + to_string(this.area()));
            if (this.has_border) {
                println("Has border");
            }
        }
    }

    ColoredBox myBox = ColoredBox(10, 20, "Blue", true);
    myBox.describe();

    // Test 10: Modifying inherited fields
    println("\n--- Test 10: Modifying inherited fields ---");
    class Counter2 {
        public int count_val;
        
        Counter2(int count_val) {
            this.count_val = count_val;
        }
        
        public void show() {
            println("Count: " + to_string(this.count_val));
        }
    }

    class DoubleCounter : Counter2 {
        DoubleCounter(int count_val) {
            this.count_val = count_val;
        }
        
        public void doubleIt() {
            this.count_val = this.count_val * 2;  // Modify parent field!
        }
    }

    DoubleCounter dc = DoubleCounter(5);
    dc.show();      // 5
    dc.doubleIt();
    dc.show();      // 10
    dc.doubleIt();
    dc.show();      // 20

    println("\n=== ALL INHERITANCE TESTS COMPLETE ===");


    println("\n=== OPERATOR OVERLOADING TESTS ===");

    class Vector2D {
        public int x_coord;
        public int y_coord;
        
        Vector2D(int x_coord, int y_coord) {
            this.x_coord = x_coord;
            this.y_coord = y_coord;
        }
        
        Vector2D operator+(Vector2D other) {
            return Vector2D(this.x_coord + other.x_coord, this.y_coord + other.y_coord);
        }
        
        bool operator==(Vector2D other) {
            return this.x_coord == other.x_coord && this.y_coord == other.y_coord;
        }
    }

    Vector2D v1 = Vector2D(1, 2);
    Vector2D v2 = Vector2D(3, 4);
    Vector2D v3 = v1 + v2;  // Uses operator+
    println("v3: (" + to_string(v3.x_coord) + ", " + to_string(v3.y_coord) + ")");

    if (v1 == v2) {
        println("Equal");
    } else {
        println("Not equal");
    }
    println("\n=== SPECIAL METHODS TESTS ===");

    class Product {
        public string name_str;
        public int price_cents;
        
        Product(string name_str, int price_cents) {
            this.name_str = name_str;
            this.price_cents = price_cents;
        }
        
        string repr() {
            return "Product(" + this.name_str + ", $" + to_string(this.price_cents) + ")";
        }
        
        void init() {
            println("Product initialized");
        }
        
        bool eval() {
            return this.price_cents > 0;
        }
    }
    Product defaultProductMess;
    Product laptop = Product("Laptop", 999);
    println(laptop);  // Calls repr()

    if (laptop) {  // Calls eval()
        println("Product is valid");
    }
    println("\n=== METHOD OVERLOADING TESTS ===");

    class MathOps {
        MathOps() {

        }
        int add(int a_val, int b_val) {
            return a_val + b_val;
        }
        
        float add(float a_val, float b_val) {
            return a_val + b_val;
        }
        
        string add(string a_val, string b_val) {
            return a_val + b_val;
        }
    }

    MathOps ops = MathOps();
    println("Int add: " + to_string(ops.add(5, 10)));
    println("Float add: " + to_string(ops.add(3.5f, 2.5f)));
    println("String add: " + ops.add("Hello", "World"));
    auto infferedarr[] = [1, 2, 3];
    list<auto> inferedlist = [1.0, 2.0];
    println(f"{typeof(infferedarr)}, {typeof(inferedlist)}");
    println(to_string(infferedarr[0]));
    return x + sum + xdddddddd + twice(22);
}