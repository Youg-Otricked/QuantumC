#nomain
extern:
///////////////////
// METADATA //////
/////////////////
string __qc_version() {
    return "x0.18.3";
}
int __qc_llvm_ver() {
    return 21;
}
void __qc_release_notes() {
    inline(R"(
    mov rax, 1
    mov rdi, 1
    mov rsi, $0r
    mov rdx, 62
    )", "Added generic functions & methods, deprecated `auto` functions\n", "~{rax}~{rdi}~{rsi}~{rdx}");
}
///////////////////
// VARIADICS /////
/////////////////
struct qc_variadic {
    void** items;
    int count;
    int current_index;
};
bool qc_variadic_is_empty(qc_variadic* variadic) {
    return variadic->current_index >= variadic->count;
}
void* qc_variadic_next(qc_variadic* variadic) {
    if (qc_variadic_is_empty(variadic)) { return nullptr; }
    void* data = variadic->items[variadic->current_index];
    variadic->current_index++;
    return data;
}
///////////////////
// Q LOGICAL /////
/////////////////

int qc_qand(int a, int b) {
    if (a == 0 || a == 1 || b == 0 || b == 1) return 1;
    if (a == 2 && b == 2) return 2;
    if (a == 2 && b == 3) return 3;
    if (a == 3 && b == 2) return 3;
    return 3;
}

int qc_qor(int a, int b) {
    if (a == 0 && b == 0) return 0;
    if (a == 0 && b == 1) return 1;
    if (a == 0 && b == 2) return 2;
    if (a == 1 && b == 0) return 1;
    if (a == 1 && b == 1) return 1;
    if (a == 2 && b == 0) return 2;
    if (a == 2 && b == 2) return 2;
    return 3;
}

int qc_qxor(int a, int b) {
    if (a <= 1 && b <= 1) return 0;
    if (a <= 1 && b >= 2) return 3;
    if (a >= 2 && b <= 1) return 3;
    if (a == 2 && b == 2) return 1;
    return 3;
}

int qc_qnot(int a) {
    return 3 - a;
}

bool qc_qand_collapse(int a, int b) {
    return (a & 0b10) && (b & 0b10);
}

bool qc_qor_collapse(int a, int b) {
    return (a & 0b10) || (b & 0b10);
}
///////////////////
// STRING ////////
/////////////////

int qc_len(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        ++i;
    }
    return i;
}
///////////////////
// INTEGER ///////
/////////////////

int qc_powi_i32(int base, int exp) {
    if (exp < 0) return 0;
    int result = 1;
    while (exp > 0) {
        if (exp & 1) result *= base;
        base *= base;
        exp = exp |> 1;
    }
    return result;
}

:extern
