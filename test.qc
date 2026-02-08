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
    
    auto sumsum = fn(int a, int b, int c) -> int {
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
    
    foreach (int xccccccc in withEmpty) {
        std::qout << xccccccc << " ";
    }
    println("");  // Expected: 1 2
    println("\n=== ALL SPREAD TESTS COMPLETE ===");
    return x + sum + xdddddddd + twice(22);
}