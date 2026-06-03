// bitwise_test.qc

int main() {
    qout("--- Starting Bitwise & Rotation Gauntlet ---\n");

    // 1. Basic Bitwise Logic
    int a = 5;  // 0101
    int b = 3;  // 0011
    
    qout("%s\n", f"AND: 5 & 3 = {a & b}"); // Expected: 1 (0001)
    qout("%s\n", f"OR:  5 | 3 = {a | b}"); // Expected: 7 (0111)
    qout("%s\n", f"XOR: 5 $ 3 = {a $ b}"); // Expected: 6 (0110)
    qout("%s\n", f"NOT: ~0    = {~0}");    // Expected: -1 (Two's complement)

    // 2. Shifts (Testing your custom precedence)
    // current + 1 << 3 should be 11 (3 + 8) if shift is higher than +
    int current = 3;
    int next = current + 1 << 3; 
    qout("%s\n", f"Precedence Test (3 + 1 << 3): {next}"); 

    // 3. Logical vs Arithmetic Right Shift
    // -8 in binary (64-bit) starts with many 1s.
    // >> should keep it negative. :> should make it a huge positive number.
    addr_t val = -8; 
    qout("%s\n", f"Arithmetic >>: {val >> 1}");   // Expected: -4
    qout("%s\n", f"Logical    :>: {val :> 1}");   // Expected: A very large positive addr_t

    // 4. Rotations
    // 0x80000000 rotated left 1 should be 1
    addr_t top_bit = 2147483648; // 2^31
    qout("%s\n", f"Rotate Left:  {top_bit <<< 1}"); // Expected: 1
    
    // 1 rotated right 1 should be 0x80000000
    addr_t one = 1;
    qout("%s\n", f"Rotate Right: {one >>> 1}");    // Expected: 2147483648

    // 5. Compound Test: Alignment
    // Aligning an address to 8-byte boundary
    addr_t ptr = 1031; // Not 8-byte aligned
    addr_t aligned = ptr & ~7;
    qout("%s\n", f"Alignment (1031 & ~7): {aligned}");
    qout("--- Gauntlet Complete ---\n");
    return 0;
}