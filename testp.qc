namespace Exported {
    #include <AdvQBool, ./stdlib.qc>
    #include <Utils, ./stdlib.qc>
    #include <Collections, ./stdlib.qc>
    #include <Math, ./stdlib.qc>
    #include <UnitTest, ./stdlib.qc>
}

int main() {
    qout("=== TESTING QUANTUM C STDLIB ===\n\n");
    
    // ✅ TEST UTILS
    qout("--- Testing Utils ---\n");
    list<int> r1[] = Utils::range(0, 10, 2);
    qout("%i\n", r1.length);
    qout("%s", f"range(0, 10, 2): {r1[0]}, {r1[1]}, {r1[2]}, {r1[3]}, {r1[4]}\n");  // 0, 2, 4, 6, 8
    list<int> r2 = Utils::range(10, 0, -1);
    qout("%s", f"range(10, 0, -1) length: {r2.length}\n");  // 10
    
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
    
    // ✅ TEST COLLECTIONS
    qout("--- Testing Collections ---\n");
    list<int> nums = [1, 2, 3, 4, 5];
    qout("%s", f"has([1,2,3,4,5], 3) = {Collections::has(nums, 3)}\n");  // true
    qout("%s", f"has([1,2,3,4,5], 10) = {Collections::has(nums, 10)}\n");  // false
    qout("%s", f"index_of([1,2,3,4,5], 3) = {Collections::index_of(nums, 3)}\n");  // 2
    
    list<int> unsorted = [5, 2, 8, 1, 9]; 
    list<int> sorted = Collections::sort(unsorted);
    qout("%s", f"sort([5,2,8,1,9]): {sorted[0]}, {sorted[1]}, {sorted[2]}, {sorted[3]}, {sorted[4]}\n");  // 1, 2, 5, 8, 9
    
    list<int> toReverse = [1, 2, 3, 4, 5];
    list<int> reversed = Collections::reverse(toReverse);
    qout("%s", f"reverse([1,2,3,4,5]): {reversed[0]}, {reversed[1]}, {reversed[2]}, {reversed[3]}, {reversed[4]}\n\n");  // 5, 4, 3, 2, 1
    reversed = Collections::remove(reversed, 2);
    qout("%s", f"remove([5,4,3,2,1], 2): {reversed[0]}, {reversed[1]}, {reversed[2]}, {reversed[3]}\n\n");  // 5, 4, 3, 1
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
    
    qout("Testing 10 evaluations of 75% true AQB:\n");
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
    
    qout("\n=== ALL STDLIB TESTS COMPLETE ===\n");
    
    return 0;
}