int main() {
    println("Test 1");
    int arr1[] = [1, 2, 3];
    int arr2[] = [4, 5];
    int combined[] = [@arr1, @arr2];
    
    println("Created combined");
    std::qout << combined.length << '\n';
    foreach (int x in combined) {
        std::qout << x << " ";
    }
    
    println("Done");
    return 0;
}