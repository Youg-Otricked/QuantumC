namespace Exported {
    #include<Utils, std>
}
void mega_test<T, U>(
    out int *restrict dst,
    inout float* *restrict matrix,
    out T *restrict generic_out,
    inout U** *nested,
    int *restrict normal_restrict,
    function callback,
    out char* *restrict text,
    inout bool *flags
) {
    return;
}
volatile void test_volatile() {
    int x = 10;
    int y = x + 20;
    return;
}
int main() {
    mega_test<int, string>(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    test_volatile();
    Utils::sleep(500);
    return 0;
}
