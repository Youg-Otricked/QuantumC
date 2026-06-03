
int main() {
    addr_t size = sizeof "int";
    qout("Size of int: %u\n", size);
    addr_t total_bytes = size * 5;
    int* p = malloc(total_bytes);

    if (p == nullptr) {
        qout("Allocation failed!\n");
        return 1;
    }
    qout("Allocated 5 ints at: %p\n", p);
    free(p);
    qout("Memory freed.\n");
    int* a_mapped_ptr = mapped_ptr(0x7ffe5367e044);
    return 0;
}