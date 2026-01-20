/* Quantum C – Simplified Full Demo
   Covers all major features in ~300 lines for easy reading
*/

int main() {

    // ========================================
    // VARIABLES & TYPES
    // ========================================
    int age = 13;
    float pi = 3.14f;
    double precise = 3.14159265359;
    string name = "Quantum C";
    char initial = 'Q';
    bool cool = true;

    // Reassignment
    age = 14;

    // ========================================
    // ARITHMETIC
    // ========================================
    9 + 10;
    10 % 3;
    2 ** 3;           // 8, power operator
    2 ** 3 ** 2;      // 512, right-associative
    -2 ** 3;          // -8

    // ========================================
    // STRING OPERATIONS
    // ========================================
    string first = "Quantum";
    string last = "C";
    string full = first + " " + last;
    string greet = f"Hello, {name}, age {age}";

    // ========================================
    // CONTROL FLOW
    // ========================================
    if (age >= 18) {
        println("Adult");
    } else if (age >= 13) {
        println("Teen");
    } else {
        println("Child");
    }

    int score = 85;
    string grade = "";
    if (score >= 90) grade = "A";
    else if (score >= 80) grade = "B";
    else grade = "F";

    switch (score) {
        case 100: println("Perfect"); break;
        default: println("Not perfect");
    }

    // Loops
    int i = 0;
    while (i < 5) { i += 1; }
    for (int j = 0; j < 5; j = j + 1) { }

    foreach (int x in [1,2,3]) { println(x); }

    // ========================================
    // FUNCTIONS & LAMBDAS
    // ========================================
    int add(int a, int b) { return a + b; }
    void greet_user(string who = "world") { println("Hello, " + who); }

    auto sum = fn(int a, int b) -> int { return a + b; };
    auto prod = fn(int a, int b) -> int { return a*b; }(3,4);

    int r = add(2,3);
    println(r);
    greet_user();
    greet_user("Alice");
    println(sum(10,20));
    println(prod);

    auto factorial = fn(int n) -> int {
        if (n <= 1) return 1;
        return n * factorial(n-1);
    };
    println(factorial(5)); // 120

    // ========================================
    // ARRAYS & LISTS
    // ========================================
    int nums[] = [1,2,3];
    // nums.push(4);
    // nums.pop(); ERROR: cannot push or pop to a array

    int grid[][] = [
        [1,2],
        [3,4]
    ];
    println(grid[0][1]); // 2

    int[] flat = [@nums, 5, 6];
    println(flat);

    // ========================================
    // STRUCTS
    // ========================================
    struct Vec2 { float x; float y; }
    struct Inventory { int[] bag; string slots[]; }
    struct Ply { string name; int hp; Vec2 pos; Inventory inv; }

    Ply p = {
        "Alice",
        100,
        {1.0, 2.0},
        { [1,2,3], ["head"] }
    };

    println(p.name);
    println(p.inv.bag[0]);
    p.inv.bag.push(4);
    println(p.inv.bag.length);

    Ply q = p;
    q.name = "Bob";
    q.hp = 50;
    q.pos.x = 9.0;
    println(q.name);

    // ========================================
    // QUANTUM BOOLEANS
    // ========================================
    qbool qb = none;
    qb = qtrue; qb = qfalse; qb = both;
    qif (qb) { println("QTrue branch"); } qelse { println("QFalse branch"); }
    qswitch (qb) {
        case t: println("True"); break;
        case f: println("False"); break;
        case n: println("None"); break;
        case b: println("Both"); break;
    }

    // ========================================
    // MAPS / DICTIONARIES
    // ========================================
    map<string,int> ages = { "Alice":25, "Bob":30 };
    ages["Charlie"] = 35;
    ages.remove("Bob");
    println(ages.has("Alice"));
    foreach (string k in ages.keys()) { println(k + ": " + f"{ages[k]}"); }

    // ========================================
    // RANDOM & SEEDING
    // ========================================
    seed(time());
    println(random());       // 0.0-1.0
    println(random(10));     // 0-9
    println(random(5,15));   // 5-14

    // ========================================
    // MULTI-RETURN FUNCTIONS
    // ========================================
    int, string get_user() { return 123, "Alice"; }
    int id, string uname = get_user();
    println(id); println(uname);

    // ========================================
    // F-STRINGS
    // ========================================
    string msg = f"User {uname} has id {id}";
    println(msg);

    // ========================================
    // FULL COLLECTION TESTS
    // ========================================
    int[] a = [1,2,3];
    int[] b = a;
    b.push(4);
    println(a); println(b);

    int cube[][][] = [
        [[1,2],[3,4]],
        [[5,6],[7,8]]
    ];
    println(cube[1][1][1]); // 8

    int tesseract[][][][] = [
        [[[1,2],[3,4]], [[5,6],[7,8]]],
        [[[9,10],[11,12]], [[13,14],[15,16]]]
    ];
    println(tesseract[1][1][1][1]); // 16
    // ========================================
    // STRUCT
    // ========================================
    struct Player {
        string name;
        int hp;
        map<string,int> inventory; // map inside struct
    }

    // Create a player
    Player p = {
        "Alice",
        100,
        { "potion": 3, "gold": 50 } // initialize map
    };

    // Access fields
    println(p.name);          // Alice
    println(p.hp);            // 100
    println(p.inventory["potion"]); // 3

    // Update map values
    p.inventory["potion"] = 5;
    p.inventory["elixir"] = 2; // add new key

    // Check updates
    println(p.inventory["potion"]); // 5
    println(p.inventory["elixir"]); // 2

    // Iterate over the map
    foreach (string key in p.inventory.keys()) {
        println(key + ": " + f"{p.inventory[key]}");
    }



    // ========================================
    // END DEMO
    // ========================================
    println("All features demonstrated!");
    return 0;
}