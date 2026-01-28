namespace Exported {
    #include <UnitTest, ./stdlib.qc>
    #include <Math, ./stdlib.qc>
}

int main() {
    UnitTest::Test t = UnitTest::Test(22);
    t.AssertEqual(Math::max(5, 3), 5, "", "max(5, 3)");
    t.AssertEqual(Math::max(-5, -3), -3, "", "max(-5, -3)");
    t.AssertEqual(Math::max(0, 0), 0, "", "max(0, 0)");
    t.AssertEqual(Math::min(5, 3), 3, "", "min(5, 3)");
    t.AssertEqual(Math::min(-5, -3), -5, "", "min(-5, -3)");
    t.AssertEqual(Math::min(0, 0), 0, "", "min(0, 0)");
    t.AssertEqual(Math::sqrt(4), 2.0, "", "sqrt(4)");
    t.AssertEqual(Math::sqrt(9), 3.0, "", "sqrt(9)");
    t.AssertTrue(Math::sqrt(2) > 1.41 && Math::sqrt(2) < 1.42, "", "sqrt(2)");
    t.AssertEqual(Math::root(8, 3), 2.0, "", "root(8, 3) - cube root");
    t.AssertEqual(Math::root(16, 4), 2.0, "", "root(16, 4) - 4th root");
    t.AssertEqual(Math::ceil(3.1), 4, "", "ceil(3.1)");
    t.AssertEqual(Math::ceil(3.9), 4, "", "ceil(3.9)");
    t.AssertEqual(Math::ceil(-3.1), -3, "", "ceil(-3.1)");
    t.AssertEqual(Math::ceil(5.0), 5, "", "ceil(5.0)");
    t.AssertEqual(Math::floor(3.1), 3, "", "floor(3.1)");
    t.AssertEqual(Math::floor(3.9), 3, "", "floor(3.9)");
    t.AssertEqual(Math::floor(-3.1), -4, "", "floor(-3.1)");
    t.AssertEqual(Math::floor(5.0), 5, "", "floor(5.0)");
    t.AssertEqual(Math::abs(5), 5, "", "abs(5)");
    t.AssertEqual(Math::abs(-5), 5, "", "abs(-5)");
    t.AssertEqual(Math::abs(0), 0, "", "abs(0)");
}