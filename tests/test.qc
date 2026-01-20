int main() {
    // ========================================
    // to_* conversion tests
    // ========================================
    println("=== to_qbool / to_bool ===");
    bool b1 = true;
    qbool qb1 = to_qbool(b1);
    println(qb1);           // expect qtrue

    qbool qb2 = both;
    qbool qb3 = to_qbool(qb2);
    println(qb3);           // expect both

    qbool qb4 = to_qbool("qfalse");
    println(qb4);           // expect qfalse

    bool b2 = to_bool(qb2); // both -> true (tval)
    println(b2);

    bool b3 = to_bool("true");
    println(b3);            // true

    println("=== to_int ===");
    int i1 = to_int(3.7f);
    println(i1);            // 3

    int i2 = to_int("42");
    println(i2);            // 42

    qbool qb_none = none;
    println(to_int(qb_none));   // 0
    println(to_int(qtrue));     // 2
    println(to_int(qfalse));    // 1
    println(to_int(both));      // 3

    println(to_int(true));      // 1
    println(to_int(false));     // 0

    println("=== to_float / to_double ===");
    float f1 = to_float(10);
    println(f1);                // 10.0

    float f2 = to_float("2.5");
    println(f2);                // 2.5

    double d1 = to_double(5);
    println(d1);                // 5.0

    double d2 = to_double("3.14159");
    println(d2);                // 3.14159-ish

    println("=== to_char ===");
    char c1 = to_char("Hello");
    println(c1);                // 'H'

    char c2 = to_char(c1);
    println(c2);                // 'H' again

    println("=== to_string ===");
    println(to_string(123));        // "123"
    println(to_string(3.5f));       // "3.5..." (whatever std::to_string does)
    println(to_string(2.0));        // "2.0..."
    println(to_string("hi"));       // "hi"
    println(to_string(qtrue));      // "qtrue"
    println(to_string(false));      // "false"
}