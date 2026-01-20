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