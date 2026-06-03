
int main() {
    int* ptr = malloc(sizeof "int");
    *ptr = 42;
    qout("%p", ptr); 
    free(ptr);
}