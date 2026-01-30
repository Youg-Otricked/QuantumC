namespace Exported {
    #include <UnitTest, std>
}

class Point {
    int x;
    int y;
    Point(int nx, int ny) {
        this.x = nx;
        this.y = ny;
    }
    void init() {
        this.x = 0;
        this.y = 0;
    }
}

int main() {
    UnitTest::Test t = UnitTest::Test(28);

    // 1. & and * on int
    int x = 5;
    int* p = &x;
    t.AssertEqual("int*", typeof(p), "typeof(p) should be int*", "typeof(p)");
    t.AssertEqual(5, *p, "*p reads x", "*p");

    *p = 10;
    t.AssertEqual(10, x, "*p = 10 should change x", "*p = 10");

    // 2. Multi-level pointers
    int* pp_base = &x;
    int** pp = &pp_base;
    int*** ppp = &pp;

    t.AssertEqual("int**", typeof(pp), "typeof(pp) should be int**", "typeof(pp)");
    t.AssertEqual("int***", typeof(ppp), "typeof(ppp) should be int***", "typeof(ppp)");

    **pp = 20;
    t.AssertEqual(20, x, "**pp = 20 should change x", "**pp = 20");

    ***ppp = 30;
    t.AssertEqual(30, x, "***ppp = 30 should change x", "***ppp = 30");

    // 3. nullptr and reassignment
    int* q = nullptr;

    q = &x;
    *q = 40;
    t.AssertEqual(40, x, "*q = 40 should change x", "*q = 40");

    q = nullptr;

    // 4. pointer reassignment between vars
    int a = 1;
    int b = 2;
    int* r = &a;

    *r = 100;
    t.AssertEqual(100, a, "*r = 100 should change a", "*r = 100");

    r = &b;
    *r = 200;
    t.AssertEqual(200, b, "*r = 200 should change b", "*r = 200");
    t.AssertEqual(100, a, "a should remain 100", "a unchanged");
    *r += 3;   // b = 203
    *r -= 3;   // b = 200
    *r *= 2;   // b = 400
    *r /= 4;   // b = 100

    t.AssertEqual(100, b, "compound ops on *r should work", "*r compound");

    // 5. struct pointer and ->
    Point pt = Point(3, 4);
    Point* ppt = &pt;

    t.AssertEqual(3, ppt->x, "ppt->x should read pt.x", "ppt->x");
    t.AssertEqual(4, ppt->y, "ppt->y should read pt.y", "ppt->y");

    ppt->x = 7;
    ppt->y = 9;
    t.AssertEqual(7, pt.x, "ppt->x = 7 should change pt.x", "ppt->x = 7");
    t.AssertEqual(9, pt.y, "ppt->y = 9 should change pt.y", "ppt->y = 9");

    (*ppt).x = 11;
    (*ppt).y = 13;
    t.AssertEqual(11, pt.x, "(*ppt).x = 11 should change pt.x", "(*ppt).x = 11");
    t.AssertEqual(13, pt.y, "(*ppt).y = 13 should change pt.y", "(*ppt).y = 13");

    // 6. invalid address-of and nullptr deref
    try {
        auto bad = &(x + a);
        t.Fail("Expected &(x + a) to be rejected");
    } catch (string e) {
        t.Success("[SUCCESS] &(x + a) correctly rejected");
    }

    try {
        int* np = nullptr;
        *np = 5;
        t.Fail("Expected *nullptr assignment to be rejected");
    } catch (string e) {
        t.Success("[SUCCESS] *nullptr correctly rejected");
    }

    // 7. sizeof tests (type names)
    println(sizeof("int"));        // 4
    println(sizeof("double"));     // 8
    println(sizeof("char"));       // 1
    println(sizeof("int*"));       // 8
    println(sizeof("int**"));      // 8

    int y = 5;
    println(sizeof(typeof(y)));    // 4

    int* py = &y;
    println(sizeof(typeof(py)));   // 8

    Point pt2 = Point(1, 2);
    println(sizeof(typeof(pt2)));  // sum of field sizes

    // 8. heap malloc/calloc tests (using type names, not sizeof yet)

    // malloc one int, default 0
    int* hp = malloc("int");
    t.AssertEqual(0, *hp, "malloc(\"int\") should init to 0", "*hp after malloc");

    *hp = 42;
    t.AssertEqual(42, *hp, "write through hp should change heap value", "*hp after write");
    free(hp);

    // calloc 5 ints
    int* harr = calloc(5, "int");
    t.AssertEqual(0, harr[0], "harr[0] default 0", "harr[0]");
    t.AssertEqual(0, harr[4], "harr[4] default 0", "harr[4]");

    harr[0] = 10;
    harr[1] = 20;
    harr[4] = 50;
    t.AssertEqual(10, harr[0], "harr[0] write/read", "harr[0] = 10");
    t.AssertEqual(20, harr[1], "harr[1] write/read", "harr[1] = 20");
    t.AssertEqual(50, harr[4], "harr[4] write/read", "harr[4] = 50");

    // realloc on scalar malloc block
    int* rq = malloc("int");
    *rq = 7;
    rq = realloc(rq, sizeof("int"));   // or just some positive size
    t.AssertEqual(7, *rq, "realloc on scalar keeps value", "*rq after realloc");

    return 0;
}