int inc_by_ref(int& x, int amount) {
    x += amount;
    return x;
}

int main() {
    int a = 5;
    int r = inc_by_ref(a, 10);
    println(a);
    println(r);
    return 0;
}