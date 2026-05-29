namespace Exported {
    #include <UnitTest, ./stdlib.qc>
}
int main() {
    UnitTest::Test test = UnitTest::Test(2);
    int x = 0;
    int& rx = x;
    rx = 12345;
    test.AssertEqual(rx, 12345, "expected rx to equal 12345", "rx == 12345");
    test.AssertEqual(x, 12345, "expected x to equal 12345", "rx = 12345; x == 12345");
    return 0;
}