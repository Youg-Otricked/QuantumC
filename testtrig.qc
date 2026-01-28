namespace Exported {
    #include <UnitTest, ./stdlib.qc>
    #include <Math, ./stdlib.qc>
}

int main() {
    UnitTest::Test t = UnitTest::Test(13);
    
    double pi = 3.14159265358979;
    t.AssertTrue(Math::abs(Math::sin(0.0)) < 0.001, "", "sin(0) ≈ 0");
    t.AssertTrue(Math::abs(Math::sin(pi / 2) - 1.0) < 0.001, "", "sin(π/2) ≈ 1");
    t.AssertTrue(Math::abs(Math::sin(pi)) < 0.001, "", "sin(π) ≈ 0");
    t.AssertTrue(Math::abs(Math::cos(0.0) - 1.0) < 0.001, "", "cos(0) ≈ 1");
    t.AssertTrue(Math::abs(Math::cos(pi / 2)) < 0.001, "", "cos(π/2) ≈ 0");
    t.AssertTrue(Math::abs(Math::cos(pi) + 1.0) < 0.001, "", "cos(π) ≈ -1");
    t.AssertTrue(Math::abs(Math::tan(0.0)) < 0.001, "", "tan(0) ≈ 0");
    t.AssertTrue(Math::abs(Math::tan(pi / 4) - 1.0) < 0.001, "", "tan(π/4) ≈ 1");
    t.AssertTrue(Math::abs(Math::log(Math::e()) - 1.0) < 0.001, "", "log(e) ≈ 1");
    t.AssertTrue(Math::abs(Math::log(1.0)) < 0.001, "", "log(1) ≈ 0");
    t.AssertTrue(Math::log(10.0) > 2.3 && Math::log(10.0) < 2.4, "", "log(10) ≈ 2.3");
    double r = random();
    t.AssertTrue(r >= 0.0 && r <= 1.0, "", "rand() in [0, 1]");
    
    int ri = random(1, 10);
    t.AssertTrue(ri >= 1 && ri <= 10, "", "rand(1, 10) in range");
}