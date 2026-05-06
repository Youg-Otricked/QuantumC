namespace UnitTest {
    #include <UnitTest, ./stdlib.qc>
}

int main() {
    println("BEFORE TEST");
    UnitTest::Test t = UnitTest::Test(5);
    println("AFTER TEST");
    
    println("BEFORE ASSERT");
    t.AssertEqual(5, 5, "test", "test");
    println("AFTER ASSERT");
    
    return 0;
}