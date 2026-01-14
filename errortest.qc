// mega_runtime_hell.qc
int main() {

    print("=== Mega Runtime Hell Test ===\n");

    // ================================
    // 1. Type mismatches
    // ================================
    string s = "hello";
    // int x = 10 / 0; // fatal: divide by zero
    int y = s + 42;            // string + int
    string z = 123 + s;        // int + string
    qbool qb = both;
    qbool r = !qb;             // invalid unary
    //qb = qb + qtrue;           // invalid binary
    //qb = !qtrue + qb;          // invalid complex

    // ================================
    // 2. List/array issues
    // ================================
    int arr[] = [1,2,3];
    // int oob = arr[5];       // fatal: out-of-bounds
    arr.push("oops");          // type mismatch
    arr.push([4,5]);           // type mismatch array -> list<int>
    arr.pop();
    arr.pop();
    arr.pop();
    arr.pop();
    arr.pop();
    arr.pop();
    arr.pop();              // fatal: pop empty list

    int jagged[][] = [[1,2],[3,4,5],[6]];
    // int v1 = jagged[2][1];  // fatal: out-of-bounds
    // int v2 = jagged[3][0];  // fatal: out-of-bounds

    // ================================
    // 3. Map errors
    // ================================
    map<string,int> ages = {"Alice":25,"Bob":30};
    //int val = ages["Charlie"];     // key not found
    ages[123] = 42;                // type mismatch key
    ages["Dave"] = "forty";        // type mismatch value
    //string val2 = ages["Eve"];     // key not found

    // ================================
    // 4. Invalid lambda calls
    // ================================
    auto fn1 = fn(int x) -> int { return x + 1; };
    int bad = fn1("oops");         // type mismatch: string -> int

    auto fn2 = fn(string s) -> string { return s + "!"; };
    string bad2 = fn2(123);        // type mismatch: int -> string

    // ================================
    // 5. Multi-return mismatches
    // ================================
    int, string get_user() { return 123, "Alice"; }
    int a1, int b1 = get_user();       // type mismatch
    string s1, int i1 = get_user();    // type mismatch

    // ================================
    // 6. Method calls on primitives
    // ================================
    int n = 42;
    n.someMethod();                   // cannot call method on int
    string t = "hi";
    t.uppercase();                    // cannot call method on string (if not implemented)

    // ================================
    // 7. Array arithmetic errors
    // ================================
    int nums[] = [1,2,3];
    int sum = nums + 4;               // cannot add array + int
    int prod = 4 * nums;              // cannot multiply int * array

    // ================================
    // 8. QBool logic errors
    // ================================
    qbool q1 = none;
    qbool q2 = both;
    qbool q3 = q1 &&& q2;             // invalid QBool logic
    qbool q4 = q1 ||| q2;             // invalid QBool logic
    qbool q5 = q1 &|& q2;             // invalid QBool logic

    // ================================
    // 9. Nested array/list errors
    // ================================
    int arr2d[][] = [[1,2],[3,4]];
    // int out = arr2d[0][2];          // fatal: out-of-bounds
    int arr3[] = [1,2];
    arr3.push(arr2d);                  // type mismatch: push array to list<int>

    // ================================
    // 10. Spread operator misuse
    // ================================
    int a[] = [1,2];
    int b[] = [3,4];
    int c[] = [5,6];
    int all[] = [@a, @b, "oops"];     // type mismatch: string -> list<int>
    int flat[] = [@arr2d, @arr3];     // type mismatch: nested array -> flat list

    // ================================
    // 11. Final message
    // ================================
    print("=== Mega Runtime Hell Test Complete ===\n");
}
