int main() {
    try {
        throw("Error message");
    } catch (string e) {
        println(e);
    }
    try {
        throw(404);
    } catch (auto e) {
        println(e);
    }
    try {
        int[] arr = [1, 2, 3];
        int x = arr[100];
    } catch (string e) {
        println("Fatal: " + e);
    }
    int divide(int a, int b) {
        if (b == 0) {
            throw("Division by zero");
        }
        return a / b;
    }

    try {
        int result = divide(10, 0);
    } catch (string e) {
        println("Error: " + e);
    }
}