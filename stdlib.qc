// This is the Quantum C Standerd Library
// Bro why u readin this do i need to make my docs beter?

int main() {
    std::qout << "Quantum C Standerd Lib. Don't run this file. include from it" << '\n';
    return 0;
}
namespace Exported {
}
namespace AdvQBool {
    type AlTypes = qbool | bool | AQB;
    class AQB {
        int TruthLevel;
        int FalseLevel;
        AQB(int truth) {
            if (truth > 100) {
                throw("Cannot make a advanced qbool more than 100 percent true.");
            }
            this.TruthLevel = truth;
            this.FalseLevel = 100 - truth;
        }
        void operator=(int other) {
            if (other > 100) {
                throw("Cannot make a advanced qbool more than 100 percent true.");
            }
            this.TruthLevel = other;
            this.FalseLevel = 100 - other;
        }
        bool operator&&(AlTypes other) {
            if (typeof(other) == "AdvQBool::AQB") {
                return this.eval() && other.eval();
            } else {
                return this.eval() && other;
            }
        }
        bool operator||(AlTypes other) {
            if (typeof(other) == "AdvQBool::AQB") {
                return this.eval() || other.eval();
            } else {
                return this.eval() || other;
            }
        }
        bool operator^(AlTypes other) {
            if (typeof(other) == "AdvQBool::AQB") {
                return this.eval() ^ other.eval();
            } else {
                return this.eval() ^ other;
            }
        }
        bool operator!() {
            return !this.eval();
        }
        bool eval() {
            if (random(0, 100) < this.FalseLevel) {
                return false;
            } else {
                return true;
            }
        }
        string repr() {
            return f"Advanced QBool is {this.TruthLevel} true and {this.FalseLevel} false.";
        }
    }
}
namespace Utils {
    int[] range(int start, int stop, int step = 1) {
        int[] fin = [];
        if (step > 0 && start <= stop) {
            for (; start < stop; start += step) {
                fin.push(start);
            }
        }
        else if (step < 0 && start >= stop) {
            for (; start > stop; start += step) {
                fin.push(start);
            }
        }
        else {
            return [];
        }
        return [@fin];
    }
}
namespace Math {
    type Number = int | float | double;
    Number max(Number a, Number b) {
        if (a > b) {
            return a;
        }
        if (a == b) {
            return 0;
        }
        return b;
    }
    Number min(Number a, Number b) {
        if (a > b) {
            return b;
        }
        if (a == b) {
            return 0;
        }
        return a;
    }
    Number sqrt(Number val) {
        return to_double(val) ** 0.5;
    }
    Number root(Number val, Number power) {
        return to_double(val) ** 1 / power;
    }
    type Floating = float | double;
    int ceil(Floating a) {
        double d = to_double(a);
        int i = to_int(d);
        if (d == i) {
            return i;
        } else if (d > 0) {
            return i + 1;
        } else {
            return i;
        }
    }
}