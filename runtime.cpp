#include <cctype>
#include <cinttypes>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <unistd.h>
extern "C" {
const char* __qc_version() { // self hosted
    return "x0.18.3";
}
int __qc_llvm_ver() { // self hosted
    return 21;
}
void __qc_release_notes() { // self hosted
    printf("Added generic functions & methods, deprecated `auto` functions");
}
void* qc_malloc(size_t size) {
    return malloc(size);
}
void qc_free(void* ptr) {
    free(ptr);
}
void* qc_realloc(void* ptr, size_t size) {
    return realloc(ptr, size);
}
void* qc_calloc(size_t num, size_t size) {
    return calloc(num, size);
}
void qc_flush() {
    fflush(NULL);
}
char* qc_fmt_int(intptr_t v, int width, int precision, bool zero_pad) {
    char fmt[32];
    if (precision >= 0) {
        if (width > 0)
            snprintf(fmt, sizeof(fmt), "%%%s%d.%dd", zero_pad ? "0" : "", width, precision);
        else
            snprintf(fmt, sizeof(fmt), "%%.%dd", precision);
    } else {
        if (width > 0)
            snprintf(fmt, sizeof(fmt), "%%%s%dd", zero_pad ? "0" : "", width);
        else
            snprintf(fmt, sizeof(fmt), "%%d");
    }
    int len = snprintf(nullptr, 0, fmt, v);
    char* out = (char*)malloc(len + 1);
    if (!out) return nullptr;
    snprintf(out, len + 1, fmt, v);
    return out;
}
char* qc_fmt_unsigned_int(size_t v, bool zero_pad) {
    char fmt[32];
    if (zero_pad) {
        snprintf(fmt, sizeof(fmt), "%%010" PRIuPTR);
    } else {
        snprintf(fmt, sizeof(fmt), "%%" PRIuPTR);
    }
    int len = snprintf(nullptr, 0, fmt, (uintptr_t)v);
    if (len < 0) return nullptr;
    char* out = (char*)malloc(len + 1);
    if (!out) return nullptr;
    snprintf(out, len + 1, fmt, (uintptr_t)v);
    return out;
}

char* qc_fmt_float(double v, int width, int precision, bool zero_pad) {
    char fmt[32];
    if (precision >= 0) {
        if (width > 0) {
            snprintf(fmt, sizeof(fmt), "%%%s%d.%df", zero_pad ? "0" : "", width, precision);
        } else {
            snprintf(fmt, sizeof(fmt), "%%.%df", precision);
        }
    } else {
        if (width > 0) {
            snprintf(fmt, sizeof(fmt), "%%%s%df", zero_pad ? "0" : "", width);
        } else {
            snprintf(fmt, sizeof(fmt), "%%f");
        }
    }
    int len = snprintf(NULL, 0, fmt, v);
    if (len < 0) return NULL;
    char* out = (char*)malloc((size_t)len + 1);
    if (!out) return NULL;
    snprintf(out, (size_t)len + 1, fmt, v);
    return out;
}

char* qc_fmt_double(double v, int width, int precision, bool zero_pad) {
    return qc_fmt_float(v, width, precision, zero_pad);
}
char* qc_fmt_scientific(double v, int width, int precision, bool zero_pad) {
    char fmt[32];
    if (precision >= 0) {
        if (width > 0) {
            snprintf(fmt, sizeof(fmt), "%%%s%d.%de", zero_pad ? "0" : "", width, precision);
        } else {
            snprintf(fmt, sizeof(fmt), "%%.%de", precision);
        }
    } else {
        if (width > 0) {
            snprintf(fmt, sizeof(fmt), "%%%s%de", zero_pad ? "0" : "", width);
        } else {
            snprintf(fmt, sizeof(fmt), "%%e");
        }
    }
    int len = snprintf(nullptr, 0, fmt, v);
    if (len < 0) return nullptr;
    char* out = (char*)malloc(len + 1);
    if (!out) return nullptr;
    snprintf(out, len + 1, fmt, v);
    return out;
}
char* qc_fmt_char(char c, int width, bool zero_pad) {
    char fmt[16];
    if (width > 0) {
        snprintf(fmt, sizeof(fmt), "%%%s%dc", zero_pad ? "0" : "", width);
    } else {
        snprintf(fmt, sizeof(fmt), "%%c");
    }
    int len = snprintf(nullptr, 0, fmt, c);
    if (len < 0) return nullptr;
    char* out = (char*)malloc(len + 1);
    if (!out) return nullptr;
    snprintf(out, len + 1, fmt, c);
    return out;
}

char* qc_fmt_string(const char* s, int width, bool zero_pad) {
    if (!s) s = "";
    char fmt[16];
    if (width > 0) {
        snprintf(fmt, sizeof(fmt), "%%%s%ds", zero_pad ? "0" : "", width);
    } else {
        snprintf(fmt, sizeof(fmt), "%%s");
    }
    int len = snprintf(nullptr, 0, fmt, s);
    if (len < 0) return nullptr;
    char* out = (char*)malloc(len + 1);
    if (!out) return nullptr;
    snprintf(out, len + 1, fmt, s);
    return out;
}

char* qc_fmt_hex(intptr_t v, int width, bool zero_pad) {
    char fmt[32];
    if (width > 0)
        snprintf(fmt, sizeof(fmt), "%%%s%dx", zero_pad ? "0" : "", width);
    else
        snprintf(fmt, sizeof(fmt), "%%x");
    int len = snprintf(nullptr, 0, fmt, v);
    char* out = (char*)malloc(len + 1);
    if (!out) return nullptr;
    snprintf(out, len + 1, fmt, v);
    return out;
}
char* qc_fmt_octal(intptr_t v, int width, bool zero_pad) {
    char fmt[32];
    if (width > 0)
        snprintf(fmt, sizeof(fmt), "%%%s%do", zero_pad ? "0" : "", width);
    else
        snprintf(fmt, sizeof(fmt), "%%o");
    int len = snprintf(nullptr, 0, fmt, v);
    char* out = (char*)malloc(len + 1);
    if (!out) return nullptr;
    snprintf(out, len + 1, fmt, v);
    return out;
}
char* qc_fmt_bool(bool v, int width, bool zero_pad) {
    const char* s = v ? "true" : "false";
    return qc_fmt_string(s, width, zero_pad);
}

char* qc_fmt_qbool(uint8_t q, int width, bool zero_pad) {
    const char* s;
    switch (q & 0x3) {
    case 0: s = "none"; break;
    case 1: s = "qfalse"; break;
    case 2: s = "qtrue"; break;
    default: s = "both"; break;
    }
    return qc_fmt_string(s, width, zero_pad);
}

char* qc_fmt_ptr(void* p, int width, bool zero_pad) {
    char buf[64];
    if (zero_pad && width > 0)
        snprintf(buf, sizeof(buf), "0x%0*jx", width, (uintmax_t)(size_t)p);
    else if (width > 0)
        snprintf(buf, sizeof(buf), "%*p", width, p);
    else
        snprintf(buf, sizeof(buf), "%p", p);
    return strdup(buf);
}
int qc_powi_i32(int base, int exp) {
    if (exp < 0) return 0;
    int result = 1;
    while (exp > 0) {
        if (exp & 1) result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
} // self hosted
char* qc_string_concat(const char* a, const char* b) {
    if (!a) a = "";
    if (!b) b = "";

    size_t len_a = strlen(a);
    size_t len_b = strlen(b);

    char* result = (char*)malloc(len_a + len_b + 1);
    if (!result) return nullptr;

    memcpy(result, a, len_a);
    memcpy(result + len_a, b, len_b);
    result[len_a + len_b] = '\0';

    return result;
} // self hosted
bool qc_string_eq(const char* a, const char* b) {
    if (!a || !b) return 0;
    return strcmp(a, b) == 0 ? 1 : 0;
} // self hosted
uint8_t qc_qand(uint8_t a, uint8_t b) { // self hosted
    if (a == 0 || a == 1 || b == 0 || b == 1) return 1;
    if (a == 2 && b == 2) return 2;
    if (a == 2 && b == 3) return 3;
    if (a == 3 && b == 2) return 3;
    return 3;
}

uint8_t qc_qor(uint8_t a, uint8_t b) { // self hosted
    if (a == 0 && b == 0) return 0;
    if (a == 0 && b == 1) return 1;
    if (a == 0 && b == 2) return 2;
    if (a == 1 && b == 0) return 1;
    if (a == 1 && b == 1) return 1;
    if (a == 2 && b == 0) return 2;
    if (a == 2 && b == 2) return 2;
    return 3;
}

uint8_t qc_qxor(uint8_t a, uint8_t b) { // self hosted
    if (a <= 1 && b <= 1) return 0;
    if (a <= 1 && b >= 2) return 3;
    if (a >= 2 && b <= 1) return 3;
    if (a == 2 && b == 2) return 1;
    return 3;
}

uint8_t qc_qnot(uint8_t a) { // self hosted
    return 3 - a;
}

bool qc_qand_collapse(uint8_t a, uint8_t b) { // self hosted
    return (a & 0b10) && (b & 0b10);
}

bool qc_qor_collapse(uint8_t a, uint8_t b) { // self hosted
    return (a & 0b10) || (b & 0b10);
}
char* qc_to_string_int(int x) {
    char buf[32];
    int n = snprintf(buf, sizeof(buf), "%d", x);
    if (n < 0) return nullptr;
    char* out = (char*)malloc(n + 1);
    if (!out) return nullptr;
    memcpy(out, buf, n + 1);
    return out;
}

char* qc_to_string_float(float x) {
    char buf[64];
    int n = snprintf(buf, sizeof(buf), "%g", (double)x);
    if (n < 0) return nullptr;
    char* out = (char*)malloc(n + 1);
    if (!out) return nullptr;
    memcpy(out, buf, n + 1);
    return out;
}
char* qc_to_string_long_int(intptr_t x) {
    char buf[32];
    int n = snprintf(buf, sizeof(buf), "%" PRIdPTR, x);
    if (n < 0) return nullptr;
    char* out = (char*)malloc(n + 1);
    if (!out) return nullptr;
    memcpy(out, buf, n + 1);
    return out;
}
char* qc_to_string_short_int(short x) {
    char buf[64];
    int n = snprintf(buf, sizeof(buf), "%hd", x);
    if (n < 0) return nullptr;
    char* out = (char*)malloc(n + 1);
    if (!out) return nullptr;
    memcpy(out, buf, n + 1);
    return out;
}
char* qc_to_string_double(double x) {
    char buf[64];
    int n = snprintf(buf, sizeof(buf), "%g", x);
    if (n < 0) return nullptr;
    char* out = (char*)malloc(n + 1);
    if (!out) return nullptr;
    memcpy(out, buf, n + 1);
    return out;
}

char* qc_to_string_bool(bool b) {
    const char* s = b ? "true" : "false";
    size_t len = strlen(s);
    char* out = (char*)malloc(len + 1);
    if (!out) return nullptr;
    memcpy(out, s, len + 1);
    return out;
}
char* qc_to_string_qbool(uint8_t q) {
    const char* s;
    switch (q & 0x3) {
    case 0: s = "none"; break;
    case 1: s = "qfalse"; break;
    case 2: s = "qtrue"; break;
    case 3: s = "both"; break;
    default: s = "none"; break;
    }
    size_t len = strlen(s);
    char* out = (char*)malloc(len + 1);
    if (!out) return nullptr;
    memcpy(out, s, len + 1);
    return out;
}

char* qc_to_string_char(char c) {
    char* out = (char*)malloc(2);
    if (!out) return nullptr;
    out[0] = c;
    out[1] = '\0';
    return out;
}

void qc_print_string(const char* s) {
    if (!s) s = "";
    fputs(s, stdout);
}
int qc_time() {
    return (int)time(NULL);
}

void qc_seed(int seed) {
    srand(seed);
}

float qc_random_float() {
    return (float)rand() / (float)RAND_MAX;
}

int qc_random_int(int max) {
    return rand() % max;
}

int qc_random_range(int min, int max) {
    return min + (rand() % (max - min));
}
int qc_len(const char* str) { // self hosted
    return strlen(str);
}

char* qc_to_lower(const char* str) {
    if (!str) return nullptr;
    size_t len = strlen(str);
    char* result = (char*)malloc(len + 1);
    if (!result) return nullptr;
    for (size_t i = 0; i < len; i++) { result[i] = tolower((unsigned char)str[i]); }
    result[len] = '\0';
    return result;
} // self hosted
char* qc_to_upper(const char* str) {
    if (!str) return nullptr;
    size_t len = strlen(str);
    char* result = (char*)malloc(len + 1);
    if (!result) return nullptr;
    for (size_t i = 0; i < len; i++) { result[i] = toupper((unsigned char)str[i]); }
    result[len] = '\0';
    return result;
} // self hosted

char* qc_substring(const char* str, int start, int length) {
    if (!str) return nullptr;
    int len = strlen(str);
    if (start < 0 || start >= len || length <= 0) {
        char* empty = (char*)malloc(1);
        empty[0] = '\0';
        return empty;
    }
    if (start + length > len) { length = len - start; }
    char* result = (char*)malloc(length + 1);
    if (!result) return nullptr;
    memcpy(result, str + start, length);
    result[length] = '\0';
    return result;
} // self hosted

int qc_contains(const char* str, const char* substr) {
    if (!str || !substr) return 0;
    return strstr(str, substr) != nullptr ? 1 : 0;
} // self hosted

int qc_startswith(const char* str, const char* prefix) {
    if (!str || !prefix) return 0;
    return strncmp(str, prefix, strlen(prefix)) == 0 ? 1 : 0;
} // self hosted

int qc_endswith(const char* str, const char* suffix) {
    if (!str || !suffix) return 0;
    size_t str_len = strlen(str);
    size_t suf_len = strlen(suffix);
    if (suf_len > str_len) return 0;
    return strcmp(str + str_len - suf_len, suffix) == 0 ? 1 : 0;
} // self hosted
bool qc_to_bool_from_string(const char* str) {
    if (!str) return false;
    return strcmp(str, "true") == 0 || strcmp(str, "1") == 0;
}

uint8_t qc_to_qbool_from_string(const char* str) {
    if (!str) return 0;
    if (strcmp(str, "qtrue") == 0) return 2;
    if (strcmp(str, "qfalse") == 0) return 1;
    if (strcmp(str, "both") == 0) return 3;
    return 0; // none
}
char* qc_qin() {
    fflush(stdout);
    fflush(stderr);
    fflush(stdin);
    char buffer[1024];
    int result = scanf("%s", buffer);
    fflush(stderr);
    fflush(stdin);
    if (result == 1) { return strdup(buffer); }
    return strdup("");
}
char* qc_trim(const char* str) {
    if (!str) return nullptr;

    while (*str && isspace((unsigned char)*str)) str++;

    if (*str == '\0') {
        char* empty = (char*)malloc(1);
        empty[0] = '\0';
        return empty;
    }

    const char* end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    size_t len = end - str + 1;
    char* result = (char*)malloc(len + 1);
    if (!result) return nullptr;
    memcpy(result, str, len);
    result[len] = '\0';
    return result;
} // self hosted

char* qc_replace(const char* str, const char* find, const char* replace) {
    if (!str || !find || !replace) return nullptr;

    size_t find_len = strlen(find);
    size_t replace_len = strlen(replace);

    if (find_len == 0) {
        char* dup = (char*)malloc(strlen(str) + 1);
        strcpy(dup, str);
        return dup;
    }
    int count = 0;
    const char* p = str;
    while ((p = strstr(p, find)) != nullptr) {
        count++;
        p += find_len;
    }

    if (count == 0) {
        char* dup = (char*)malloc(strlen(str) + 1);
        strcpy(dup, str);
        return dup;
    }
    size_t str_len = strlen(str);
    size_t result_len = str_len + count * (replace_len - find_len);
    char* result = (char*)malloc(result_len + 1);
    if (!result) return nullptr;
    char* dst = result;
    p = str;
    while (*p) {
        const char* match = strstr(p, find);
        if (match == p) {
            memcpy(dst, replace, replace_len);
            dst += replace_len;
            p += find_len;
        } else {
            *dst++ = *p++;
        }
    }
    *dst = '\0';

    return result;
} // self hosted

int qc_to_int_from_string(const char* str) {
    return str ? atoi(str) : 0;
}
short qc_to_short_int_from_string(const char* str) {
    long val = str ? strtol(str, nullptr, 10) : 0;
    return static_cast<short>(val);
}
intptr_t qc_to_long_int_from_string(const char* str) {
    return str ? strtoll(str, nullptr, 10) : 0;
}
size_t qc_to_addr_t_from_string(const char* str) {
    return str ? static_cast<size_t>(strtoull(str, nullptr, 10)) : 0;
}
float qc_to_float_from_string(const char* str) {
    return str ? (float)atof(str) : 0.0f;
}

double qc_to_double_from_string(const char* str) {
    return str ? atof(str) : 0.0;
}

char qc_to_char_from_string(const char* str) {
    return (str && str[0]) ? str[0] : '\0';
}
int qc_sizeof_type(int elem_type) {
    switch (elem_type) {
    case 0: return sizeof(int);
    case 1: return sizeof(float);
    case 2: return sizeof(double);
    case 3: return sizeof(char);
    case 4: return sizeof(bool);
    case 5: return sizeof(uint8_t);
    case 6: return sizeof(char*);
    default: return 4;
    }
}
char* qc_array_to_string_recursive(void* arr, int elem_type, int ndims, int* dims) {
    if (ndims == 0) {
        char buf[256];
        switch (elem_type) {
        case 0: snprintf(buf, sizeof(buf), "%d", *(int*)arr); break;
        case 1: snprintf(buf, sizeof(buf), "%g", *(float*)arr); break;
        case 2: snprintf(buf, sizeof(buf), "%g", *(double*)arr); break;
        case 3: snprintf(buf, sizeof(buf), "'%c'", *(char*)arr); break;
        case 4: snprintf(buf, sizeof(buf), "%s", *(bool*)arr ? "true" : "false"); break;
        case 5: {
            uint8_t q = *(uint8_t*)arr & 0x3;
            const char* s = (q == 0) ? "none" : (q == 1) ? "qfalse" : (q == 2) ? "qtrue" : "both";
            snprintf(buf, sizeof(buf), "%s", s);
            break;
        }
        case 6: snprintf(buf, sizeof(buf), "\"%s\"", *(char**)arr); break;
        }
        char* result = (char*)malloc(strlen(buf) + 1);
        strcpy(result, buf);
        return result;
    }
    int total_len = 2;
    int elem_size = qc_sizeof_type(elem_type);
    for (int i = 1; i < ndims; i++) { elem_size *= dims[i]; }

    char** parts = (char**)malloc(dims[0] * sizeof(char*));
    for (int i = 0; i < dims[0]; i++) {
        void* elem_ptr = (char*)arr + (i * elem_size);
        parts[i] = qc_array_to_string_recursive(elem_ptr, elem_type, ndims - 1, dims + 1);
        total_len += strlen(parts[i]);
        if (i < dims[0] - 1) total_len += 2;
    }

    char* result = (char*)malloc(total_len + 1);
    char* p = result;
    *p++ = '[';
    for (int i = 0; i < dims[0]; i++) {
        strcpy(p, parts[i]);
        p += strlen(parts[i]);
        free(parts[i]);
        if (i < dims[0] - 1) {
            *p++ = ',';
            *p++ = ' ';
        }
    }
    *p++ = ']';
    *p = '\0';
    free(parts);

    return result;
}
struct qc_jagged_array {
    void** data;
    int* sizes;
    int count;
    int elem_type;
    int depth;
};

qc_jagged_array* qc_create_jagged_array(int count, int elem_type, int depth) {
    qc_jagged_array* arr = (qc_jagged_array*)malloc(sizeof(qc_jagged_array));
    arr->data = (void**)malloc(count * sizeof(void*));
    arr->sizes = (int*)malloc(count * sizeof(int));
    arr->count = count;
    arr->elem_type = elem_type;
    arr->depth = depth;
    return arr;
}

void qc_set_jagged_element(qc_jagged_array* arr, int idx, void* elem, int size) {
    arr->data[idx] = elem;
    arr->sizes[idx] = size;
}
void qc_free_jagged_array(qc_jagged_array* arr) {
    if (arr->depth > 0) {
        for (int i = 0; i < arr->count; i++) { qc_free_jagged_array((qc_jagged_array*)arr->data[i]); }
    } else {
        for (int i = 0; i < arr->count; i++) { free(arr->data[i]); }
    }
    free(arr->data);
    free(arr->sizes);
    free(arr);
}
void* qc_jagged_array_get(qc_jagged_array* arr, int* indices, int num_indices) {
    if (num_indices == 0 || !arr) { return nullptr; }

    int idx = indices[0];
    if (idx < 0 || idx >= arr->count) { return nullptr; }

    if (arr->depth == 0) {
        if (num_indices == 1) {
            return arr->data[idx];
        } else {
            int elem_idx = indices[1];
            if (elem_idx < 0 || elem_idx >= arr->sizes[idx]) { return nullptr; }
            void* row = arr->data[idx];
            return (char*)row + (elem_idx * qc_sizeof_type(arr->elem_type));
        }
    } else if (arr->depth == 1) {
        void* row = arr->data[idx];

        if (num_indices == 1) {
            return row;
        } else {
            int elem_idx = indices[1];
            if (elem_idx < 0 || elem_idx >= arr->sizes[idx]) { return nullptr; }
            return (char*)row + (elem_idx * qc_sizeof_type(arr->elem_type));
        }
    } else {
        qc_jagged_array* sub = (qc_jagged_array*)arr->data[idx];
        if (!sub) return nullptr;

        return qc_jagged_array_get(sub, indices + 1, num_indices - 1);
    }
}
void* qc_create_leaf_row(int size, int elem_type) {
    int elem_size = qc_sizeof_type(elem_type);
    int total = size * elem_size;
    void* row = malloc(total);
    return row;
}
void qc_set_leaf_element(void* row, int idx, void* value, int elem_type) {
    void* dest = (char*)row + (idx * qc_sizeof_type(elem_type));
    memcpy(dest, value, qc_sizeof_type(elem_type));
}
void qc_stringify_jagged_helper(qc_jagged_array* arr, char** p, int* remaining, int* est_size, char** result) {
    **p = '[';
    (*p)++;
    (*remaining)--;

    for (int i = 0; i < arr->count; i++) {
        if (arr->depth > 0) {
            qc_stringify_jagged_helper((qc_jagged_array*)arr->data[i], p, remaining, est_size, result);
        } else {
            **p = '[';
            (*p)++;
            (*remaining)--;
            void* row = arr->data[i];

            for (int j = 0; j < arr->sizes[i]; j++) {
                void* elem_ptr = (char*)row + (j * qc_sizeof_type(arr->elem_type));

                char buf[64];
                switch (arr->elem_type) {
                case 0: snprintf(buf, 64, "%d", *(int*)elem_ptr); break;
                case 1: snprintf(buf, 64, "%g", *(float*)elem_ptr); break;
                case 2: snprintf(buf, 64, "%g", *(double*)elem_ptr); break;
                case 3: snprintf(buf, 64, "'%c'", *(char*)elem_ptr); break;
                case 4: snprintf(buf, 64, "%s", *(bool*)elem_ptr ? "true" : "false"); break;
                case 5: {
                    uint8_t q = *(uint8_t*)elem_ptr & 0x3;
                    snprintf(buf, 64, "%s", (q == 0) ? "none" : (q == 1) ? "qfalse" : (q == 2) ? "qtrue" : "both");
                    break;
                }
                case 6: snprintf(buf, 64, "\"%s\"", *(char**)elem_ptr); break;
                }

                int len = strlen(buf);
                if (*remaining < len + 10) {
                    int offset = *p - *result;
                    *est_size *= 2;
                    *result = (char*)realloc(*result, *est_size);
                    *p = *result + offset;
                    *remaining = *est_size - offset;
                }

                strcpy(*p, buf);
                *p += len;
                *remaining -= len;

                if (j < arr->sizes[i] - 1) {
                    **p = ',';
                    (*p)++;
                    **p = ' ';
                    (*p)++;
                    *remaining -= 2;
                }
            }
            **p = ']';
            (*p)++;
            (*remaining)--;
        }

        if (i < arr->count - 1) {
            **p = ',';
            (*p)++;
            **p = ' ';
            (*p)++;
            *remaining -= 2;
        }
    }

    **p = ']';
    (*p)++;
    (*remaining)--;
}

char* qc_jagged_to_string(qc_jagged_array* arr) {
    int est_size = 1024;
    char* result = (char*)malloc(est_size);
    char* p = result;
    int remaining = est_size;

    qc_stringify_jagged_helper(arr, &p, &remaining, &est_size, &result);
    *p = '\0';

    return result;
}
int qc_open(const char* path, const char* mode) {
    FILE* f = fopen(path, mode);
    if (f == nullptr) return -1;
    return fileno(f);
} // self hosted
void qc_close(int fd) {
    close(fd);
} // self hosted

char* qc_read(int fd) {
    char buffer[1024];

    ssize_t n = read(fd, buffer, sizeof(buffer) - 1);
    if (n <= 0) return strdup("");

    buffer[n] = '\0';
    return strdup(buffer);
} // self hosted

void qc_write(int fd, const char* data) {
    if (data) write(fd, data, strlen(data));
} // self hosted
typedef struct {
    void** items;
    int count;
    int current_index;
} qc_variadic; // self hosted
bool qc_variadic_is_empty(qc_variadic* variadic) {
    return variadic->current_index >= variadic->count; // self hosted
}
void* qc_variadic_next(qc_variadic* variadic) { // self hosted
    if (qc_variadic_is_empty(variadic)) { return nullptr; }
    void* data = variadic->items[variadic->current_index];
    variadic->current_index++;
    return data;
}
}
