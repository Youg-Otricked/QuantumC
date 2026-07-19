type AAlias<T> = T[];
type AUnion<T> = T | int;
int main() {
    AAlias<int> x = nullptr;
    AUnion<string> y = 123;
    __qc_changes();
    return 0;
}
