int main() {
    int arr[] = [1, 2, 3];
    println(arr[0]);
    
    int matrix[][] = [[1, 2], [3, 4]];
    println(matrix[0][1]);  // 2
    
    int jagged[][] = [[1, 2], [3, 4, 5], [6]];
    println(jagged[0][0]);  // 1
    println(jagged[1][2]);  // 5
    println(jagged[2][0]);  // 6
    
    int cube[][][] = [[[1, 2], [3, 4]], [[5, 6], [7, 8]]];
    println(cube[1][0][1]);  // 6
    
    return 0;
}