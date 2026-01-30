namespace Exported {
    #include <UnitTest, std>
}

int inc_by_ref(int& x, int amount) {
    x = x + amount;
    return x;
}
void swap_ints(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}
void ref_chain(int& a, int& b, int& c) {
    a = a + 1;
    b = b + 2;
    c = c + 3;
}


int main() {
    UnitTest::Test t = UnitTest::Test(8);
    int ad = 10;
    int r = inc_by_ref(ad, 5);
    t.AssertEqual(15, ad, "x should be incremented via ref", "inc_by_ref(x, 5)");
    t.AssertEqual(15, r, "return should match new x", "inc_by_ref(x, 5)");
    int adx = 1;
    int bdx = 2;
    swap_ints(adx, bdx);
    t.AssertEqual(2, adx, "swap should put b into a", "swap_ints(a, b)");
    t.AssertEqual(1, bdx, "swap should put a into b", "swap_ints(a, b)");
    int x = 0;
    int y = 0;
    int z = 0;
    ref_chain(x, y, z);
    t.AssertEqual(1, x, "x incremented by 1", "ref_chain(x, y, z)");
    t.AssertEqual(2, y, "y incremented by 2", "ref_chain(x, y, z)");
    t.AssertEqual(3, z, "z incremented by 3", "ref_chain(x, y, z)");
    int x = 5;
    int& r = x;
    inc_by_ref(r, 10);
    t.AssertEqual(15, x, "inc_by_ref(r, 10) should affect x", "inc_by_ref(r, 10)");
    return 0;
}
/* works
int main() {
    int x = 5;
    int& ref = x;
    ref = 10;
    println(x);
}
*/