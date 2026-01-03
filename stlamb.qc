
int main() {
    int x = 5;
    int y = 10;
    auto add = fn(int x, int y) -> int {
        return x + y;
    };

    auto swap = fn(int a, int b) -> int, int {
        return b, a;
    };
    y = add(x, y);
    
    int store, int store2 = swap(y, x);
    std::qout << f"X and Y were {store} and {store2} but now are {x} and {y}";
}