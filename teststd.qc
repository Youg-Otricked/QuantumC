namespace Exported {
    #include <AdvQBool, std>
    #include <Utils, std>
    #include <UnitTest, ./stdlib.qc>
    #include <Math, std>
}

int main() {
    AdvQBool::AQB test = AdvQBool::AQB(70);
    if (test) {
        println(test);
    }
    if (test) {
        println(test);
    }
    if (test && true) {
        println(test);
    }
    if (!test) {
        println(test);
    }
    if (test || false) {
        println(test);
    }
    test = 50;
    if (test) {
        println(test);
    }
    if (test ^ true) {
        println(test);
    }
    if (test) {
        println(test);
    }
    foreach (int i in Utils::range(1, 10, 1)) {
        std::qout << i << '\n';
    }
    std::qout << Math::ceil(0.5) << '\n';
    std::qout << Math::sqrt(4) << '\n';
    std::qout << Math::root(27, 3) << '\n';
    std::qout << Math::max(100, 1) << '\n' << Math::min(100, 1) << '\n';
    UnitTest::Test tst = UnitTest::Test(2);
    tst.AssertEqual(2, Math::max(1,2), "", "max(1,2)");
    tst.AssertEqual(1, Math::min(1,2), "", "min(1,2)");
    return 0;
}