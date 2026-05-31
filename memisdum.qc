namespace Exported {
    #include <UnitTest, ./stdlib.qc>
}
void add(int& x, int y) {
    x += y;
}
void aAutoReturn(int& x, auto y) {
    if (typeof(y) == "int") {
        x += y;
    }
}
class Refs {
    int x;
    Refs(int x) {
        this.x = x;
    }
    void getX(int& y) {
        y = this.x;
    }
    void setXp1(int& t) {
        t += 1;
        this.x = t;
    }
    void autoRet(int& x, auto y) {
        if (typeof(y) == "int") {
            x += y;
        }
    }
    Refs& operator=(Refs other) {
        this.x = other.x;
        return this;
    }
}
int main() {
    UnitTest::Test test = UnitTest::Test(5);
    int y = 0;
    int& rx = y;
    rx = 12345;
    test.AssertEqual(12345, rx, "expected rx to equal 12345", "rx == 12345");
    test.AssertEqual(12345, y, "expected x to equal 12345", "x = 12345; x == 12345");
    int n = 1234;
    add(y, n);
    test.AssertEqual(13579, y, "expected x to equal 13579", "x == 13579");
    Refs r = Refs(12345);
    Refs z = Refs(321);
    Refs x = Refs(21);
    x = z = r;
    x.getX(y);
    test.AssertEqual(12345, y, "expected x = 12345", "x == 12345");
    x.setXp1(y);
    aAutoReturn(y, n);
    x.autoRet(y, n);
    test.AssertEqual(14814, y, "expected x = 14814", "x == 14814");
    return 0;
}