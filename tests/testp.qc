namespace Exported {
    #include <Vector, List, Array, AdvQBool, Utils, Math, UnitTest, OSInterop, ../stdlib.qc>
}

int main() {
    qout("=== TESTING QUANTUM C STDLIB ===\n\n");
    
    // ✅ TEST UTILS
    qout("--- Testing Utils ---\n");
    Vector::Vec<int> r1 = Utils::range(0, 10, 2);
    qout("%i\n", r1.size);
    qout("%s", f"range(0, 10, 2): {r1[0]}, {r1[1]}, {r1[2]}, {r1[3]}, {r1[4]}\n");  // 0, 2, 4, 6, 8
    
    qout("Testing sleep(1)...\n");
    Utils::sleep(1);
    qout("Sleep done!\n\n");
    
    // ✅ TEST MATH
    qout("--- Testing Math ---\n");
    qout("%s", f"Math::pi() = {Math::pi()}\n");
    qout("%s", f"Math::e() = {Math::e()}\n");
    qout("%s", f"Math::max(5, 10) = {Math::max(5, 10)}\n");  // 10
    qout("%s", f"Math::min(5, 10) = {Math::min(5, 10)}\n");  // 5
    qout("%s", f"Math::sqrt(16) = {Math::sqrt(16)}\n");  // 4
    qout("%s", f"Math::abs(-42) = {Math::abs(-42)}\n");  // 42
    qout("%s", f"Math::ceil(3.2) = {Math::ceil(3.2)}\n");  // 4
    qout("%s", f"Math::floor(3.8) = {Math::floor(3.8)}\n");  // 3
    qout("%s", f"Math::sin(0) = {Math::sin(0.0)}\n");  // 0
    qout("%s", f"Math::cos(0) = {Math::cos(0.0)}\n");  // 1
    qout("%s", f"Math::tan(0) = {Math::tan(0.0)}\n");  // 0
    qout("%s", f"Math::log(2.718) = {Math::log(2.718)}\n\n");  // ~1
    // ✅ TEST UNITTEST
    qout("--- Testing UnitTest ---\n");
    UnitTest::Test test = UnitTest::Test(5);
    test.AssertEqual(5, 5, "", "5 == 5\n");
    test.AssertEqual(10, 5 + 5, "", "10 == 5+5\n");
    test.AssertTrue(true, "", "true is true\n");
    test.AssertFalse(false, "", "false is false\n");
    test.AssertNotEqual(5, 10, "", "5 != 10\n");
    
    // ✅ TEST ADVQBOOL
    qout("\n--- Testing AdvQBool ---\n");
    AdvQBool::AQB aqb = AdvQBool::AQB(75);  // 75% true
    qout("%s", f"AQB(75): {aqb.repr()}\n");
    
    qout("Testing 10 evaluations of 75%% true AQB:\n");
    int trueCount = 0;
    for (int i = 0; i < 10; i++) {
        if (aqb.eval()) {
            trueCount++;
        }
    }
    qout("%s", f"Got {trueCount}/10 true (expected ~7-8)\n");
    
    AdvQBool::AQB aqb2 = AdvQBool::AQB(50);
    qout("%s", f"\nAQB && test: {aqb.eval() && aqb2.eval()}\n");
    qout("%s", f"AQB || test: {aqb.eval() || aqb2.eval()}\n");
    qout("%s", f"!AQB test: {!aqb.eval()}\n");
    // TEST OS
    OSInterop::system("ls -la");
    qout("\n=== ALL STDLIB TESTS COMPLETE ===\n");
    
    return 0;
}
