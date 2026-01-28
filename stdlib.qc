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
            if (truth > 100 || truth < 0) {
                throw("Cannot make a advanced qbool more than 100 percent true or more than 100% false.");
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
        void init() {
            this.TruthLevel = 50;
            this.FalseLevel = 50;
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
    void sleep(long int crr) {
        crr += time();
        while (time() < crr) {
            for (int i = 0; i < 5000; i++) {}
        }
    }
}
namespace Math {
    double e() {
        return 2.71828182845904523536;
    }
    
    double pi() {
        return 3.14159265358979323846;
    }
    type Number = int | float | double;
    Number max(Number a, Number b) {
        if (a > b) {
            return a;
        }
        return b;
    }
    Number min(Number a, Number b) {
        if (a > b) {
            return b;
        }
        return a;
    }
    Number sqrt(Number val) {
        return to_double(val) ** 0.5;
    }
    Number root(Number val, Number power) {
        double base = to_double(val);
        double exp  = 1.0 / to_double(power);
        return base ** exp;
    }
    type Floating = float | double;
    int ceil(Floating a) {
        double d = to_double(a);
        int i = to_int(d);
        if (d == to_double(i)) {
            return i;
        } else if (d > 0) {
            return i + 1;
        } else {
            return i;
        }
    }
    int floor(Floating a) {
        double d = to_double(a);
        int i = to_int(d);
        if (d >= 0) {
            return i;
        } else {
            if (d == to_double(i)) {
                return i;
            } else {
                return i - 1;
            }
        }
    }
    Number abs(Number a) {
        if (a < 0) {
            return a * -1;
        }
        return a;
    }
    double sin(double x) {
        double pi = 3.14159265358979323846;
        while (x > pi) { x -= 2 * pi; }
        while (x < -pi) { x += 2 * pi; }
        
        double result = 0.0;
        double term = x;
        int n = 1;
        for (int i = 0; i < 10; i++) {
            result += term;
            term *= -1.0 * x * x / ((2 * n) * (2 * n + 1));
            n++;
        }
        
        return result;
    }
    double cos(double x) {
        
        double pi = 3.14159265358979323846;
        while (x > pi) { x -= 2 * pi; }
        while (x < -pi) { x += 2 * pi; }
        
        double result = 0.0;
        double term = 1.0;
        int n = 1;
        
        for (int i = 0; i < 10; i++) {
            result += term;
            term *= -1.0 * x * x / ((2 * n - 1) * (2 * n));
            n++;
        }
        
        return result;
    }
    double tan(double x) {
        return sin(x) / cos(x);
    }
    double log(double x) {
        if (x <= 0) {
            throw("log: x must be positive");
        }
        double log2 = 0.693147180559945309417;
        int n = 0;
        
        while (x > 2.0) {
            x /= 2.0;
            n++;
        }
        while (x < 0.5) {
            x *= 2.0;
            n--;
        }
        double y = x - 1.0;
        double result = 0.0;
        double term = y;
        
        for (int i = 1; i <= 20; i++) {
            result += term / to_double(i);
            term *= -y;
        }
        
        return result + n * log2;
    }
}
namespace UnitTest {
    class Test {
        int Total;
        int Ran;
        int Passed;
        int Failed;
        string[] Messages;
        Test(int Ttl) {
            this.Total = Ttl;
            this.Ran = 0;
            this.Passed = 0;
            this.Failed = 0;
        }
        void Check() {
            if (this.Ran >= this.Total) {
                if (this.Messages.length > 0) {
                    foreach(string message in this.Messages) {
                        std::qout << "==============================" << '\n';
                        std::qout << message << '\n';
                    }
                    std::qout << "==============================" << '\n';
                }
                
                std::qout << f"Failed: {this.Failed}" << '\n';
                std::qout << f"Passed: {this.Passed}" << '\n';

                std::qout << "==============================" << '\n';
                if (this.Failed > 0) {
                    std::qout << "[FAIL]" << '\n';
                } else {
                    std::qout << "[PASS]" << '\n';
                }
            }
        }
        void Success(string message = "[SUCCESS]") {
            this.Ran += 1;
            this.Passed += 1;
            this.Messages.push(message + f": [{this.Ran}/{this.Total}]");
            this.Check();
        }
        void Fail(string message = "[FAIL]") {
            this.Ran += 1;
            this.Failed += 1;
            this.Messages.push(message + f": [{this.Ran}/{this.Total}]");
            this.Check();
        }
        void AssertEqual(auto expected, auto result, string FailMessage = "", string Call = "") {
            if (expected != result) {
                if (Call != "") {
                    this.Fail(f"[FAIL] On call {Call}: Expected {expected}, got {result}. {FailMessage}");
                } else {
                    this.Fail(f"[FAIL] Expected {expected}, got {result}. {FailMessage}");
                }
            } else {
                if (Call != "") {
                    this.Success(f"[SUCCESS] on call {Call}: {result} was equal to {expected}");
                } else {
                    this.Success(f"[SUCCESS] {result} was equal to {expected}");
                }
            }
        }
        void AssertTrue(bool cond, string FailMessage = "", string Call = "") {
            if (!cond) {
                if (Call != "") {
                    this.Fail(f"[FAIL] On call {Call}: Expected condition to be true. {FailMessage}");
                } else {
                    this.Fail(f"[FAIL] Expected condition to be true. {FailMessage}");
                }
            } else {
                if (Call != "") {
                    this.Success(f"[SUCCESS] on call {Call}: Condition was true");
                } else {
                    this.Success(f"[SUCCESS] Condition was true");
                }
            }
        }

        void AssertFalse(bool cond, string FailMessage = "", string Call = "") {
            if (cond) {
                if (Call != "") {
                    this.Fail(f"[FAIL] On call {Call}: Expected condition to be false. {FailMessage}");
                } else {
                    this.Fail(f"[FAIL] Expected condition to be false. {FailMessage}");
                }
            } else {
                if (Call != "") {
                    this.Success(f"[SUCCESS] on call {Call}: Condition was false");
                } else {
                    this.Success(f"[SUCCESS] Condition was false");
                }
            }
        }

        void AssertNotEqual(auto notExpected, auto result, string FailMessage = "", string Call = "") {
            if (notExpected == result) {
                if (Call != "") {
                    this.Fail(f"[FAIL] On call {Call}: Expected {result} to not equal {notExpected}. {FailMessage}");
                } else {
                    this.Fail(f"[FAIL] Expected {result} to not equal {notExpected}. {FailMessage}");
                }
            } else {
                if (Call != "") {
                    this.Success(f"[SUCCESS] on call {Call}: {result} wasn't equal to {notExpected}");
                } else {
                    this.Success(f"[SUCCESS] {result} wasn't equal to {notExpected}");
                }
            }
        }
    }
}
namespace Collections {
    bool has(auto collection, auto value) {
        foreach (auto val in collection) {
            if (val == value) {
                return true;
            }
        }
        return false;
    }
    int index_of(auto collection, auto value) {
        for (int i = 0; i < collection.length; i++) {
            if (collection[i] == value) {
                return i;
            }
        }
        return -1;
    }
    list<int> sort(list<int> collection) {
        bool swapped = true;
        int n = collection.length;
        while(swapped) {
            swapped = false;
            for (int i = 0; i < n - 1; i++) {
                if (collection[i] > collection[i + 1]) {
                    int iv = collection[i];
                    collection[i] = collection[i + 1];
                    collection[i + 1] = iv;
                    swapped = true;
                }
            }
            n -= 1;
        }
        return collection;
    }
    list<auto> remove(list<auto> collection, auto value) {
        int index = index_of(collection, value);
        if (index != -1) {
            for (int i = index; i < collection.length - 1; i++) {
                collection[i] = collection[i + 1];
            }
            collection.pop();
        }
        return collection;
    }
    list<auto> reverse(list<auto> collection) {
        int n = collection.length;
        for (int i = 0; i < n / 2; i++) {
            auto temp = collection[i];
            collection[i] = collection[n - 1 - i];
            collection[n - 1 - i] = temp;
        }
        return collection;
    }
}