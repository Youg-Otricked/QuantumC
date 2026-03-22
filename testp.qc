namespace Exported {
    #include <AdvQBool, ./stdlib.qc>
    #include <Utils, ./stdlib.qc>
    #include <Collections, ./stdlib.qc>
    #include <Math, ./stdlib.qc>
    #include <UnitTest, ./stdlib.qc>
}

int main() {
    println("=== TESTING QUANTUM C STDLIB ===\n");
    
    // ✅ TEST UTILS
    println("--- Testing Utils ---");
    int r1[] = Utils::range(0, 10, 2);
    println(r1.length);
    println(f"range(0, 10, 2): {r1[0]}, {r1[1]}, {r1[2]}, {r1[3]}, {r1[4]}");  // 0, 2, 4, 6, 8
    
    int r2[] = Utils::range(10, 0, -1);
    println(f"range(10, 0, -1) length: {r2.length}");  // 10
    
    println("Testing sleep(1)...");
    Utils::sleep(1);
    println("Sleep done!\n");
    
    // ✅ TEST MATH
    println("--- Testing Math ---");
    println(f"Math::pi() = {Math::pi()}");
    println(f"Math::e() = {Math::e()}");
    println(f"Math::max(5, 10) = {Math::max(5, 10)}");  // 10
    println(f"Math::min(5, 10) = {Math::min(5, 10)}");  // 5
    println(f"Math::sqrt(16) = {Math::sqrt(16)}");  // 4
    println(f"Math::abs(-42) = {Math::abs(-42)}");  // 42
    println(f"Math::ceil(3.2) = {Math::ceil(3.2)}");  // 4
    println(f"Math::floor(3.8) = {Math::floor(3.8)}");  // 3
    println(f"Math::sin(0) = {Math::sin(0.0)}");  // 0
    println(f"Math::cos(0) = {Math::cos(0.0)}");  // 1
    println(f"Math::tan(0) = {Math::tan(0.0)}");  // 0
    println(f"Math::log(2.718) = {Math::log(2.718)}\n");  // ~1
    
    // ✅ TEST COLLECTIONS
    println("--- Testing Collections ---");
    list<int> nums = [1, 2, 3, 4, 5];
    println(f"has([1,2,3,4,5], 3) = {Collections::has(nums, 3)}");  // true
    println(f"has([1,2,3,4,5], 10) = {Collections::has(nums, 10)}");  // false
    println(f"index_of([1,2,3,4,5], 3) = {Collections::index_of(nums, 3)}");  // 2
    
    list<int> unsorted = [5, 2, 8, 1, 9];
    list<int> sorted = Collections::sort(unsorted);
    println(f"sort([5,2,8,1,9]): {sorted[0]}, {sorted[1]}, {sorted[2]}, {sorted[3]}, {sorted[4]}");  // 1, 2, 5, 8, 9
    
    list<int> toReverse = [1, 2, 3, 4, 5];
    list<int> reversed = Collections::reverse(toReverse);
    println(f"reverse([1,2,3,4,5]): {reversed[0]}, {reversed[1]}, {reversed[2]}, {reversed[3]}, {reversed[4]}\n");  // 5, 4, 3, 2, 1
    
    // ✅ TEST UNITTEST
    println("--- Testing UnitTest ---");
    UnitTest::Test test = UnitTest::Test(5);
    
    test.AssertEqual(5, 5, "", "5 == 5");
    test.AssertEqual(10, 5 + 5, "", "10 == 5+5");
    test.AssertTrue(true, "", "true is true");
    test.AssertFalse(false, "", "false is false");
    test.AssertNotEqual(5, 10, "", "5 != 10");
    
    // ✅ TEST ADVQBOOL
    println("\n--- Testing AdvQBool ---");
    AdvQBool::AQB aqb = AdvQBool::AQB(75);  // 75% true
    println(f"AQB(75): {aqb.repr()}");
    
    println("Testing 10 evaluations of 75% true AQB:");
    int trueCount = 0;
    for (int i = 0; i < 10; i++) {
        if (aqb.eval()) {
            trueCount++;
        }
    }
    println(f"Got {trueCount}/10 true (expected ~7-8)");
    
    AdvQBool::AQB aqb2 = AdvQBool::AQB(50);
    println(f"\nAQB && test: {aqb.eval() && aqb2.eval()}");
    println(f"AQB || test: {aqb.eval() || aqb2.eval()}");
    println(f"!AQB test: {!aqb.eval()}");
    
    println("\n=== ALL STDLIB TESTS COMPLETE ===");
    
    return 0;
}