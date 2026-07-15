int main() {
    qout("--- Starting Bitwise & Rotation Gauntlet ---\n");
    int a = 5;
    int b = 3;
    qout("%s\n", f"AND: 5 & 3 = {a & b}");
    qout("%s\n", f"OR:  5 | 3 = {a | b}");
    qout("%s\n", f"XOR: 5 $ 3 = {a $ b}");
    qout("%s\n", f"NOT: ~0    = {~0}");
    int current = 3;
    int next = current + 1 << 3; 
    qout("%s\n", f"Precedence Test (3 + 1 << 3): {next}"); 
    addr_t val = -8;
    qout("%s\n", f"Arithmetic |>: {val |> 1}");
    qout("%s\n", f"Logical    :>: {val :> 1}");
    addr_t top_bit = 2147483648;
    qout("%s\n", f"Rotate Left:  {top_bit <<< 1}");
    addr_t one = 1;
    qout("%s\n", f"Rotate Right: {one |>> 1}");
    addr_t ptr = 1031;
    addr_t aligned = ptr & ~7;
    qout("%s\n", f"Alignment (1031 & ~7): {aligned}");
    qout("--- Gauntlet Complete ---\n");
    addr_t address = to_address(&a);
    qout("The address of a is %x\n", address);
    flush();
    int* ptr_to_addr = mapped_ptr(address);
    *ptr_to_addr = 5;
    string str = "Hello, World!";
    inline(R"(
    mov rax, 1
    mov rdi, 1
    mov rsi, $0r
    mov edx, $1r
    syscall
    )", str, len(str), "~{rax}~{rsi}~{rdi}");
    return 0;
}
