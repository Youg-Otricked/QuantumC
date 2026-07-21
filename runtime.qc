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
    `inline(R"(
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
bool qc_string_eq(string a, string b) {
    if (a == nullptr || b == nullptr)
        return a == b;
    addr_t i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i])
            return false;
        i++;
    }
    return a[i] == b[i];
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
///////////////////
// TEMP MEM STUF /
/////////////////
struct AllocBlock {
    char *memory;
    addr_t used;
    addr_t capacity;
    AllocBlock *next;
};
AllocBlock *blocks = nullptr;
void *__qc_malloc(addr_t size) {
    size = (size + 7) & ~7;
    AllocBlock *block = blocks;
    while (block) {
        if (block->used + size <= block->capacity)
            break;
        block = block->next;
    }
    if (block == nullptr) {
        addr_t header = sizeof "AllocBlock";
        addr_t new_size = 4096;
        if (size + header > new_size)
            new_size = size + header;
        void *mem = nullptr;

        `inline(R"(
            mov rax, 9
            mov rdi, 0
            mov rsi, $1r
            mov rdx, 3
            mov r10, 34
            mov r8, -1
            mov r9, 0
            syscall
            mov $0=r, rax
        )", mem, new_size, "~{rax}~{rdi}~{rsi}~{rdx}~{r10}~{r8}~{r9}");

        if (mem == `mapped_ptr(-1l))
            return nullptr;
        AllocBlock *new_block = mem;
        char *memc = mem;
        new_block->memory = memc + sizeof "AllocBlock";
        new_block->used = 0;
        new_block->capacity = new_size - sizeof "AllocBlock";
        new_block->next = blocks;
        blocks = new_block;
        block = new_block;
    }
    void *result = block->memory + block->used;
    block->used += size;
    return result;
}
void *__qc_memcpy(void *dst, void *src, addr_t size) {
    char *d = dst;
    char *s = src;
    while (size && (`to_address(d) & 7)) {
        *d = *s;
        d = d + 1;
        s = s + 1;
        size--;
    }
    addr_t *dw = d;
    addr_t *sw = s;
    while (size >= 8) {
        *dw = *sw;
        dw = dw + 1;
        sw = sw + 1;
        size -= 8;
    }
    d = dw;
    s = sw;
    while (size) {
        *d = *s;
        d = d + 1;
        s = s + 1;
        size--;
    }
    return dst;
}
string __qc_strdup(string src) {
    if (src == nullptr) {
        return nullptr;
    }
    addr_t len = `len(src) + 1; 
    char *dst = __qc_malloc(len); 
    if (dst == nullptr) {
        return nullptr; 
    }
    return __qc_memcpy(dst, src, len); 
}
//////////////////
// FILES ////////
////////////////
const int O_WRONLY = 1;
const int O_CREAT = 64;
const int O_TRUNC = 512;
const int O_APPEND = 1024;
const int O_RDWR = 2;
const int O_RDONLY = 0;

int qc_open(string path, string permission) {
    int fgs = 0;
    if (permission == "r") {
        fgs = O_RDONLY;
    } else if (permission == "w") {
        fgs = O_WRONLY | O_CREAT | O_TRUNC;
    } else if (permission == "a") {
        fgs = O_WRONLY | O_CREAT | O_APPEND;
    } else if (permission == "rw") {
        fgs = O_RDWR;
    } else if (permission == "r+") {
        fgs = O_RDWR;
    } else if (permission == "w+") {
        fgs = O_RDWR | O_CREAT | O_TRUNC;
    } else if (permission == "a+") {
        fgs = O_RDWR | O_CREAT | O_APPEND;
    } else {
        return -1;
    }
    int res = 0;
    `inline(R"(
    mov rax, 257
    mov rdi, -100
    mov rsi, $1r
    mov edx, $2r
    mov r10d, $3r
    syscall
    mov $0=r, eax
    )", res, path, fgs, `ternary(fgs < 3, 0, 0644), "~{rax}~{rdi}~{rsi}~{rdx}~{r10}");
    if (res < 0) {
        return -1;
    }
    return res;
}
void qc_close(int fd) {
    `inline(R"(
    mov rax, 3
    mov edi, $0r
    syscall
    )", fd, "~{rax}~{rdi}");
}

char *qc_read(int fd) {
    char buffer[1024];
    long int n = 0;
    `inline(R"(
    mov rax, 0
    mov edi, $1r
    mov sil, $2r
    mov rdx, 1023
    syscall
    mov $0=r, rax)", n, fd, buffer, "~{rax}~{rdi}~{rsi}~{rdx}");
    if (n <= 0)
        return __qc_strdup("");
    buffer[n] = '\0';
    return __qc_strdup(buffer);
}
void qc_write(int fd, string data) {
    if (data)
        `inline(R"(
        mov rax, 1
        mov edi, $0r
        mov rsi, $1r
        mov edx, $2r
        syscall
        )", fd, data, `len(data), "~{rax}~{rdi}~{rsi}~{rdx}");
}
:extern
