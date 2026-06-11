foreign:
int c_sum(int count, ...);
:foreign

int main() {
    qout("%i", c_sum(4, 123, 82, 1, 39));
    return 0;
}