class simple {
    int x;
    simple(int x) {
        this.x = x;
    }
    string repr() {
        return f"simple({this.x})";
    }
}
struct test {
    int x;
    int y;
}
int main() {
    int x = 12;
    string s = "Hello, World!";
    bool b = true;
    float f = 0.12345f;
    double d = 0.12345678910;
    char c = '\t';
    qbool q = both;
    test tst = { 1, 123 };
    tst.x = 1;
    simple simp = simple(123);
    qout("x = %010i, s = %s, f = %.3f, d = %d, c = %c, simp = %cs, b = %b, q = %q, tst = %st, hex x = %02x, octal x = %03o, scientific f = %e, addr of d = %p\n", x, s, f, d, c, simp, b, q, tst, x, x, f, &d);
    
    return 0;
}