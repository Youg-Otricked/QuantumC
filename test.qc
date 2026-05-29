namespace ComplexTest {
    int sections = 0;
    int passed = 0;
    int failed = 0;
    void section(string name, fn() -> void block) {
        sections++;
        qout("Section %s\n", name);
        block();
    }
    class Result {
        int value;
        Result(int value) {
            this.value = value;
        }
        void toBe(int val) {
            if (this.value == val) {
                qout("        PASS\n");
                passed++;
            } else {
                qout("        FAIL\n");
                failed++;
            }
        }
    }
    Result check(string call, int val) {
        qout("    %s\n", call);
        return Result(val);
    }
    int finished() {
        qout("In %i sections with %i total tests, %i tests passed and %i failed.", sections, failed + passed, passed, failed);
        if (failed != 0) {
            return 1;
        }   
        return 0;
    }
}
int add(int a, int b) {
    return a + b;
}
int main() {
    add(3, 4);
    ComplexTest::section("Add", fn() -> void {
        ComplexTest::check("add(123, 321);", add(123, 321)).toBe(444);
        ComplexTest::check("add(-12, -3);", add(-12, -3)).toBe(-15);
    });
    return ComplexTest::finished();
}