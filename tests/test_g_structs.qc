struct Pair<K, V> {
    K first;
    V second;
}
int main() {
    Pair<int, string> x = {1, "Hello"};
    qout("%st", x);
    return 0;
}
