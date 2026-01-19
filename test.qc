abstract class Base {
  int x;
  int y;
}
class Vec2 : Base {
    Vec2(int x, int y) {
        this.x = x;
        this.y = y;
    }

    Vec2 operator+(Vec2 other) {
        Vec2 r = Vec2(0, 0);
        r.x = this.x + other.x;
        r.y = this.y + other.y;
        return r;
    }

    bool operator==(Vec2 other) {
        return this.x == other.x && this.y == other.y;
    }
    bool eval() {
      return true;
    }
    string repr() {
      return f"Dimentions: {this.x} x {this.y}";
    }
}

int main() {
    Vec2 a = Vec2(1, 2);
    Vec2 b = Vec2(3, 4);
    Vec2 c = a + b;

    Vec2 d = Vec2(4, 6);
    bool eq1 = (c == d);
    bool eq2 = (a == b);

    int result = 0;
    if (eq1) {
        result += 10;
    }
    if (eq2) {
        result += 1;
    }
    if (a) {
      std::qout << "Eval works" << '\n';
    }
    std::qout << a << '\n';
    std::qout << "c.x=" << c.x << " c.y=" << c.y << "\n";
    std::qout << "eq1=" << eq1 << " eq2=" << eq2 << "\n";

    return result;
}