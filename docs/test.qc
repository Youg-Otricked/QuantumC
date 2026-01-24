class Vector2 {
    int x;
    int y;
    Vector2(int x, int y) {
        this.x = x;
        this.y = y;
    }
    void init() {
        this.x = 0;
        this.y = 0;
    }
    string repr() {
        return f"X: {this.x}, Y: {this.y}";
    }
    bool eval() {
        return true;
    }
    Vector2 operator+(Vector2 other) {
        Vector2 r = Vector2(0, 0);
        r.x = this.x + other.x;
        r.y = this.y + other.y;
        return r;
    }
    void operator=(Vector2 other) {
        this.x = other.x;
        this.y = other.y;
    }
}
int main() {
    
    Vector2 a;
    Vector2 b = Vector2(12, -33);
    a.x = 123;
    a.y = 321;
    println(a);
    println(f"{a}, {b}");
    std::qout << a << ", " << b << '\n';
    a += b;
}