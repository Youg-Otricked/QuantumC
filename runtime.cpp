#include <cstring>
#include <cstdlib>
#include <limits>
#include <cstdint>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <ffi.h>

extern "C" {
    void* qc_malloc(uintptr_t size) {
        return malloc(size);
    }
    void qc_free(void* ptr) {
        free(ptr);
    }
    void* qc_realloc(void* ptr, uintptr_t size) {
        return realloc(ptr, size);
    }
    void* qc_calloc(uintptr_t num, uintptr_t size) {
        return calloc(num, size);
    }
    char* qc_fmt_int(long long v, int width, int precision, int zero_pad) {
        char fmt[32];
        if (precision >= 0) {
            if (width > 0) snprintf(fmt, sizeof(fmt), "%%%s%d.%dd", zero_pad ? "0" : "", width, precision);
            else snprintf(fmt, sizeof(fmt), "%%.%dd", precision);
        } else {
            if (width > 0) snprintf(fmt, sizeof(fmt), "%%%s%dd", zero_pad ? "0" : "", width);
            else snprintf(fmt, sizeof(fmt), "%%d");
        }
        int len = snprintf(nullptr, 0, fmt, v);
        char* out = (char*)malloc(len + 1);
        if (!out) return nullptr;
        snprintf(out, len + 1, fmt, v);
        return out;
    }
    void qc_flush() {
        fflush(NULL);
    }
    char* qc_fmt_unsigned_int(uintptr_t v, int zero_pad) {
        char fmt[32];
        if (zero_pad) {
            snprintf(fmt, sizeof(fmt), "%%llu"); 
        } else {
            snprintf(fmt, sizeof(fmt), "%%llu");
        }
        int len = snprintf(nullptr, 0, fmt, (unsigned long long)v);
        if (len < 0) return nullptr;
        char* out = (char*)malloc(len + 1);
        if (!out) return nullptr;
        snprintf(out, len + 1, fmt, (unsigned long long)v);
        
        return out;
    }


    char* qc_fmt_float(double v, int width, int precision, int zero_pad) {
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

    char* qc_fmt_double(double v, int width, int precision, int zero_pad) {
        return qc_fmt_float(v, width, precision, zero_pad);
    }
    char* qc_fmt_scientific(double v, int width, int precision, int zero_pad) {
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
    char* qc_fmt_char(char c, int width, int zero_pad) {
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

    char* qc_fmt_string(const char* s, int width, int zero_pad) {
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

    char* qc_fmt_hex(long long v, int width, int zero_pad) {
        char fmt[32];
        if (width > 0) snprintf(fmt, sizeof(fmt), "%%%s%dx", zero_pad ? "0" : "", width);
        else snprintf(fmt, sizeof(fmt), "%%x");
        int len = snprintf(nullptr, 0, fmt, v);
        char* out = (char*)malloc(len + 1);
        if (!out) return nullptr;
        snprintf(out, len + 1, fmt, v);
        return out;
    }
    char* qc_fmt_octal(long long v, int width, int zero_pad) {
        char fmt[32];
        if (width > 0) snprintf(fmt, sizeof(fmt), "%%%s%do", zero_pad ? "0" : "", width);
        else snprintf(fmt, sizeof(fmt), "%%o");
        int len = snprintf(nullptr, 0, fmt, v);
        char* out = (char*)malloc(len + 1);
        if (!out) return nullptr;
        snprintf(out, len + 1, fmt, v);
        return out;
    }
    char* qc_fmt_bool(bool v, int width, int zero_pad) {
        const char* s = v ? "true" : "false";
        return qc_fmt_string(s, width, zero_pad);
    }

    char* qc_fmt_qbool(uint8_t q, int width, int zero_pad) {
        const char* s;
        switch (q & 0x3) {
            case 0: s = "none"; break;
            case 1: s = "qfalse"; break;
            case 2: s = "qtrue"; break;
            default: s = "both"; break;
        }
        return qc_fmt_string(s, width, zero_pad);
    }

    char* qc_fmt_ptr(void* p, int width, int zero_pad) {
        char buf[64];
        if (zero_pad && width > 0) snprintf(buf, sizeof(buf), "0x%0*jx", width, (uintmax_t)(uintptr_t)p);
        else if (width > 0) snprintf(buf, sizeof(buf), "%*p", width, p);
        else snprintf(buf, sizeof(buf), "%p", p);
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
    }
    void qc_print_ptr(void* p) {
        printf("%p\n", p);
    }
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
    }
    bool qc_string_eq(const char* a, const char* b) {
        if (!a || !b) return 0;
        return strcmp(a, b) == 0 ? 1 : 0;
    }
    uint8_t qc_qand(uint8_t a, uint8_t b) {
        if (a == 0 || a == 1 || b == 0 || b == 1) return 1;
        if (a == 2 && b == 2) return 2;
        if (a == 2 && b == 3) return 3;
        if (a == 3 && b == 2) return 3;
        return 3;
    }
    
    uint8_t qc_qor(uint8_t a, uint8_t b) {
        if (a == 0 && b == 0) return 0;
        if (a == 0 && b == 1) return 1;
        if (a == 0 && b == 2) return 2;
        if (a == 1 && b == 0) return 1;
        if (a == 1 && b == 1) return 1;
        if (a == 2 && b == 0) return 2;
        if (a == 2 && b == 2) return 2;
        return 3;
    }
    
    uint8_t qc_qxor(uint8_t a, uint8_t b) {
        if (a <= 1 && b <= 1) return 0;
        if (a <= 1 && b >= 2) return 3;
        if (a >= 2 && b <= 1) return 3;
        if (a == 2 && b == 2) return 1;
        return 3;
    }
    
    uint8_t qc_qnot(uint8_t a) {
        return 3 - a;
    }
    
    bool qc_qand_collapse(uint8_t a, uint8_t b) {
        return (a & 0b10) && (b & 0b10);
    }
    
    bool qc_qor_collapse(uint8_t a, uint8_t b) {
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
    char* qc_to_string_long_int(long long x) {
        char buf[32];
        int n = snprintf(buf, sizeof(buf), "%lld", x);
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
    int qc_to_int_from_float(float x) { return (int)x; }
    int qc_to_int_from_double(double x) { return (int)x; }
    int qc_to_int_from_char(char c) { return (int)c; }

    float qc_to_float_from_double(double x) { return (float)x; }
    float qc_to_float_from_bool(bool b) { return b ? 1.0f : 0.0f; }

    double qc_to_double_from_float(float x) { return (double)x; }
    double qc_to_double_from_bool(bool b) { return b ? 1.0 : 0.0; }

    bool qc_to_bool_from_int(int x) { return x != 0; }
    bool qc_to_bool_from_float(float x) { return x != 0.0f; }
    bool qc_to_bool_from_double(double x) { return x != 0.0; }

    char qc_to_char_from_int(int x) { return (char)x; }
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
            case 0: s = "none";   break;
            case 1: s = "qfalse"; break;
            case 2: s = "qtrue";  break;
            case 3: s = "both";   break;
            default: s = "none";  break;
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

    void qc_print_int(int x) {
        printf("%d", x);
    }

    void qc_print_double(double x) {
        printf("%g", x);
    }

    void qc_print_char(char c) {
        putchar(static_cast<unsigned char>(c));
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
    int qc_len(const char* str) {
        return strlen(str);
    }

     char* qc_to_lower(const char* str) {
        if (!str) return nullptr;
        size_t len = strlen(str);
        char* result = (char*)malloc(len + 1);
        if (!result) return nullptr;
        for (size_t i = 0; i < len; i++) {
            result[i] = tolower((unsigned char)str[i]);
        }
        result[len] = '\0';
        return result;
    }

    char* qc_to_upper(const char* str) {
        if (!str) return nullptr;
        size_t len = strlen(str);
        char* result = (char*)malloc(len + 1);
        if (!result) return nullptr;
        for (size_t i = 0; i < len; i++) {
            result[i] = toupper((unsigned char)str[i]);
        }
        result[len] = '\0';
        return result;
    }
    
    char* qc_substring(const char* str, int start, int length) {
        if (!str) return nullptr;
        int len = strlen(str);
        if (start < 0 || start >= len || length <= 0) {
            char* empty = (char*)malloc(1);
            empty[0] = '\0';
            return empty;
        }
        if (start + length > len) {
            length = len - start;
        }
        char* result = (char*)malloc(length + 1);
        if (!result) return nullptr;
        memcpy(result, str + start, length);
        result[length] = '\0';
        return result;
    }
    
    int qc_contains(const char* str, const char* substr) {
        if (!str || !substr) return 0;
        return strstr(str, substr) != nullptr ? 1 : 0;
    }
    
    int qc_startswith(const char* str, const char* prefix) {
        if (!str || !prefix) return 0;
        return strncmp(str, prefix, strlen(prefix)) == 0 ? 1 : 0;
    }
    
    int qc_endswith(const char* str, const char* suffix) {
        if (!str || !suffix) return 0;
        size_t str_len = strlen(str);
        size_t suf_len = strlen(suffix);
        if (suf_len > str_len) return 0;
        return strcmp(str + str_len - suf_len, suffix) == 0 ? 1 : 0;
    }
    void qc_print_float(float x) { 
        printf("%g", x); 
    }
    bool qc_to_bool_from_string(const char* str) {
        if (!str) return false;
        return strcmp(str, "true") == 0 || strcmp(str, "1") == 0;
    }

    uint8_t qc_to_qbool_from_string(const char* str) {
        if (!str) return 0;
        if (strcmp(str, "qtrue") == 0) return 2;
        if (strcmp(str, "qfalse") == 0) return 1;
        if (strcmp(str, "both") == 0) return 3;
        return 0;  // none
    }
    char* qc_qin() {
        fflush(stdout);
        fflush(stderr);
        fflush(stdin);
        char buffer[1024];
        int result = scanf("%s", buffer);
        fflush(stderr);
        fflush(stdin);
        if (result == 1) {
            return strdup(buffer);
        }
        return strdup("");
    }
    void qc_print_bool(bool b) { 
        printf("%s", b ? "true" : "false"); 
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
    }
    
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
    }
    
    int qc_to_int_from_string(const char* str) {
        return str ? atoi(str) : 0;
    }
    short qc_to_short_int_from_string(const char* str) {
        long val = str ? strtol(str, nullptr, 10) : 0;
        return static_cast<short>(val);
    }
    long long qc_to_long_int_from_string(const char* str) {
        return str ? strtoll(str, nullptr, 10) : 0;
    }
    uintptr_t qc_to_addr_t_from_string(const char* str) {
        return str ? static_cast<uintptr_t>(strtoull(str, nullptr, 10)) : 0;
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
    
    int qc_to_int_from_bool(bool b) {
        return b ? 1 : 0;
    }
    
    float qc_to_float_from_int(int x) {
        return (float)x;
    }
    
    double qc_to_double_from_int(int x) {
        return (double)x;
    }
    
    void qc_print(const char* s) {
        if (s) printf("%s", s);
    }
    
    void qc_println(const char* s) {
        if (s) printf("%s\n", s);
        else printf("\n");
    }
    void qc_print_array_int(int* arr, int size) {
        printf("[");
        for (int i = 0; i < size; i++) {
            printf("%d", arr[i]);
            if (i < size - 1) printf(", ");
        }
        printf("]");
    }
    
    void qc_print_array_float(float* arr, int size) {
        printf("[");
        for (int i = 0; i < size; i++) {
            printf("%g", arr[i]);
            if (i < size - 1) printf(", ");
        }
        printf("]");
    }
    void qc_print_array_double(double* arr, int size) {
        printf("[");
        for (int i = 0; i < size; i++) {
            printf("%g", arr[i]);
            if (i < size - 1) printf(", ");
        }
        printf("]");
    }
    void qc_print_array_string(char** arr, int size) {
        printf("[");
        for (int i = 0; i < size; i++) {
            printf("\"%s\"", arr[i]);
            if (i < size - 1) printf(", ");
        }
        printf("]");
    }
    void qc_print_array_char(char* arr, int size) {
        printf("[");
        for (int i = 0; i < size; i++) {
            printf("'%c'", arr[i]);
            if (i < size - 1) printf(", ");
        }
        printf("]");
    }
    
    void qc_print_array_bool(bool* arr, int size) {
        printf("[");
        for (int i = 0; i < size; i++) {
            printf("%s", arr[i] ? "true" : "false");
            if (i < size - 1) printf(", ");
        }
        printf("]");
    }
    
    void qc_print_array_qbool(uint8_t* arr, int size) {
        printf("[");
        for (int i = 0; i < size; i++) {
            switch (arr[i] & 0x3) {
                case 0: printf("none"); break;
                case 1: printf("qfalse"); break;
                case 2: printf("qtrue"); break;
                case 3: printf("both"); break;
            }
            if (i < size - 1) printf(", ");
        }
        printf("]");
    }
    int sizeof_type(int elem_type) {
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
        int elem_size = sizeof_type(elem_type);
        for (int i = 1; i < ndims; i++) {
            elem_size *= dims[i];
        }
        
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
    
    
    void qc_print_array_recursive(void* arr, int elem_type, int ndims, int* dims) {
        if (ndims == 0) {
            switch (elem_type) {
                case 0: printf("%d", *(int*)arr); break;
                case 1: printf("%g", *(float*)arr); break;
                case 2: printf("%g", *(double*)arr); break;
                case 3: printf("'%c'", *(char*)arr); break;
                case 4: printf("%s", *(bool*)arr ? "true" : "false"); break;
                case 5: {
                    uint8_t q = *(uint8_t*)arr & 0x3;
                    switch (q) {
                        case 0: printf("none"); break;
                        case 1: printf("qfalse"); break;
                        case 2: printf("qtrue"); break;
                        case 3: printf("both"); break;
                    }
                    break;
                }
                case 6: printf("\"%s\"", *(char**)arr); break;
            }
            return;
        }
        printf("[");
        int elem_size = sizeof_type(elem_type);
        for (int i = 1; i < ndims; i++) {
            elem_size *= dims[i];
        }
        
        for (int i = 0; i < dims[0]; i++) {
            void* elem_ptr = (char*)arr + (i * elem_size);
            qc_print_array_recursive(elem_ptr, elem_type, ndims - 1, dims + 1);
            if (i < dims[0] - 1) printf(", ");
        }
        printf("]");
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
            for (int i = 0; i < arr->count; i++) {
                qc_free_jagged_array((qc_jagged_array*)arr->data[i]);
            }
        } else {
            for (int i = 0; i < arr->count; i++) {
                free(arr->data[i]);
            }
        }
        free(arr->data);
        free(arr->sizes);
        free(arr);
    }
    
    void qc_print_jagged_array_recursive(qc_jagged_array* arr) {
        printf("[");
        for (int i = 0; i < arr->count; i++) {
            if (arr->depth > 1) {
                qc_print_jagged_array_recursive((qc_jagged_array*)arr->data[i]);
            } else if (arr->depth == 1) {
                void* row = arr->data[i];
                printf("[");
                for (int j = 0; j < arr->sizes[i]; j++) {
                    void* elem_ptr = (char*)row + (j * sizeof_type(arr->elem_type));
                    
                    switch (arr->elem_type) {
                        case 0: printf("%d", *(int*)elem_ptr); break;
                        case 1: printf("%g", *(float*)elem_ptr); break;
                        case 2: printf("%g", *(double*)elem_ptr); break;
                        case 3: printf("'%c'", *(char*)elem_ptr); break;
                        case 4: printf("%s", *(bool*)elem_ptr ? "true" : "false"); break;
                        case 5: {
                            uint8_t q = *(uint8_t*)elem_ptr & 0x3;
                            printf("%s", (q == 0) ? "none" : (q == 1) ? "qfalse" : (q == 2) ? "qtrue" : "both");
                            break;
                        }
                        case 6: printf("\"%s\"", *(char**)elem_ptr); break;
                    }
                    
                    if (j < arr->sizes[i] - 1) printf(", ");
                }
                printf("]");
            } else {
                printf("ERROR");
            }
            
            if (i < arr->count - 1) printf(", ");
        }
        printf("]");
    }
    void* qc_jagged_array_get(qc_jagged_array* arr, int* indices, int num_indices) {
        if (num_indices == 0 || !arr) {
            return nullptr;
        }
        
        int idx = indices[0];
        if (idx < 0 || idx >= arr->count) {
            return nullptr;
        }
        
        if (arr->depth == 0) {
            if (num_indices == 1) {
                return arr->data[idx];
            } else {
                int elem_idx = indices[1];
                if (elem_idx < 0 || elem_idx >= arr->sizes[idx]) {
                    return nullptr;
                }
                void* row = arr->data[idx];
                return (char*)row + (elem_idx * sizeof_type(arr->elem_type));
            }
        } else if (arr->depth == 1) {
            void* row = arr->data[idx];
            
            if (num_indices == 1) {
                return row;
            } else {
                int elem_idx = indices[1];
                if (elem_idx < 0 || elem_idx >= arr->sizes[idx]) {
                    return nullptr;
                }
                return (char*)row + (elem_idx * sizeof_type(arr->elem_type));
            }
        } else {
            qc_jagged_array* sub = (qc_jagged_array*)arr->data[idx];
            if (!sub) return nullptr;
            
            return qc_jagged_array_get(sub, indices + 1, num_indices - 1);
        }
    }
    void* qc_create_leaf_row(int size, int elem_type) {
        int elem_size = sizeof_type(elem_type);
        int total = size * elem_size;
        void* row = malloc(total);
        return row;
    }
    void qc_set_leaf_element(void* row, int idx, void* value, int elem_type) {
        void* dest = (char*)row + (idx * sizeof_type(elem_type));
        memcpy(dest, value, sizeof_type(elem_type));
    }
    void stringify_jagged_helper(qc_jagged_array* arr, char** p, int* remaining, int* est_size, char** result) {
        **p = '['; (*p)++; (*remaining)--;
        
        for (int i = 0; i < arr->count; i++) {
            if (arr->depth > 0) {
                stringify_jagged_helper((qc_jagged_array*)arr->data[i], p, remaining, est_size, result);
            } else {
                **p = '['; (*p)++; (*remaining)--;
                void* row = arr->data[i];
                
                for (int j = 0; j < arr->sizes[i]; j++) {
                    void* elem_ptr = (char*)row + (j * sizeof_type(arr->elem_type));
                    
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
                        **p = ','; (*p)++; **p = ' '; (*p)++;
                        *remaining -= 2;
                    }
                }
                **p = ']'; (*p)++; (*remaining)--;
            }
            
            if (i < arr->count - 1) {
                **p = ','; (*p)++; **p = ' '; (*p)++;
                *remaining -= 2;
            }
        }
        
        **p = ']'; (*p)++; (*remaining)--;
    }

    char* qc_jagged_to_string(qc_jagged_array* arr) {
        int est_size = 1024;
        char* result = (char*)malloc(est_size);
        char* p = result;
        int remaining = est_size;
        
        stringify_jagged_helper(arr, &p, &remaining, &est_size, &result);
        *p = '\0';
        
        return result;
    }
    typedef struct {
        void** data;
        int size;
        int capacity;
        int elem_type;
    } qc_list;

    qc_list* qc_create_list(int elem_type) {
        qc_list* list = (qc_list*)malloc(sizeof(qc_list));
        list->capacity = 4;
        list->size = 0;
        list->elem_type = elem_type;
        list->data = (void**)malloc(list->capacity * sizeof(void*));
        return list;
    }

    void qc_list_push(qc_list* list, void* elem, int elem_type) {
        if (list->size >= list->capacity) {
            list->capacity *= 2;
            list->data = (void**)realloc(list->data, list->capacity * sizeof(void*));
        }

        if (elem_type <= 5) {
            int size = sizeof_type(elem_type);
            void* copy = malloc(size);
            memcpy(copy, elem, size);
            list->data[list->size++] = copy;
        } else {
            list->data[list->size++] = *(void**)elem;
        }
    }

    void qc_list_set(void* list_ptr, int index, void* value) {
        qc_list* list = (qc_list*)list_ptr;
        if (index < 0 || index >= list->size) return;

        if (list->elem_type <= 5) {
            int size = sizeof_type(list->elem_type);
            void* copy = malloc(size);
            memcpy(copy, value, size);
            free(list->data[index]);
            list->data[index] = copy;
        } else {
            list->data[index] = *(void**)value;
        }
    }
    void* qc_list_get(qc_list* list, int index) {
        
        if (index < 0 || index >= list->size) {
            return nullptr;
        }
        return list->data[index];
    }

    void* qc_list_pop(qc_list* list) {
        if (list->size == 0) return nullptr;
        return list->data[--list->size];
    }

    int qc_list_length(qc_list* list) {
        return list->size;
    }
    typedef struct {
        void** keys;
        void** values;
        int size;
        int capacity;
        int key_type;
        int value_type;
    } qc_map;

    qc_map* qc_create_map(int key_type, int value_type) {
        qc_map* map = (qc_map*)malloc(sizeof(qc_map));
        map->capacity = 4;
        map->size = 0;
        map->key_type = key_type;
        map->value_type = value_type;
        map->keys = (void**)malloc(map->capacity * sizeof(void*));
        map->values = (void**)malloc(map->capacity * sizeof(void*));
        return map;
    }
    bool qc_compare_keys(void* k1, void* k2, int type) {
        if (!k1 || !k2) return false;
        
        switch (type) {
            case 0: return *(int*)k1 == *(int*)k2;
            case 1: return *(float*)k1 == *(float*)k2;
            case 2: return *(double*)k1 == *(double*)k2;
            case 3: return *(char*)k1 == *(char*)k2;
            case 4: return *(bool*)k1 == *(bool*)k2;
            case 5: return *(uint8_t*)k1 == *(uint8_t*)k2;
            case 6: return strcmp((char*)k1, (char*)k2) == 0;
            default: return false;
        }
    }
    void qc_map_set(qc_map* map, void* key, void* value) {
        for (int i = 0; i < map->size; i++) {
            if (qc_compare_keys(map->keys[i], key, map->key_type)) {
                if (map->value_type <= 5) {
                    int size = sizeof_type(map->value_type);
                    if (!map->values[i]) {
                        map->values[i] = malloc(size);
                    }
                    memcpy(map->values[i], value, size);
                } else if (map->key_type == 6) {
                    char* str = (char*)key;
                    map->keys[map->size] = (void*)strdup(str);
                } else {
                    map->values[i] = value;
                }
                return;
            }
        }
        
        if (map->size >= map->capacity) {
            map->capacity *= 2;
            map->keys = (void**)realloc(map->keys, map->capacity * sizeof(void*));
            map->values = (void**)realloc(map->values, map->capacity * sizeof(void*));
        }
        if (map->key_type <= 5) {
            int size = sizeof_type(map->key_type);
            void* key_copy = malloc(size);
            memcpy(key_copy, key, size);
            map->keys[map->size] = key_copy;
        } else if (map->key_type == 6) {
            char* str = (char*)key;
            map->keys[map->size] = (void*)strdup(str);
        } else {
            map->keys[map->size] = key;
        }
        
        if (map->value_type <= 5) {
            int size = sizeof_type(map->value_type);
            void* val_copy = malloc(size);
            memcpy(val_copy, value, size);
            map->values[map->size] = val_copy;
        } else if (map->value_type == 6) {
            char* str = (char*)value;
            map->values[map->size] = (void*)strdup(str);
        } else {
            map->values[map->size] = value;
        }
        
        map->size++;
    }

    void* qc_map_get(qc_map* map, void* key) {
        for (int i = 0; i < map->size; i++) {
            if (qc_compare_keys(map->keys[i], key, map->key_type)) {
                return map->values[i];
            }
        }
        return nullptr;
    }

    bool qc_map_has(qc_map* map, void* key) {
        for (int i = 0; i < map->size; i++) {
            if (qc_compare_keys(map->keys[i], key, map->key_type)) {
                return true;
            }
        }
        return false;
    }

    void qc_map_remove(qc_map* map, void* key) {
        for (int i = 0; i < map->size; i++) {
            if (qc_compare_keys(map->keys[i], key, map->key_type)) {
                for (int j = i; j < map->size - 1; j++) {
                    map->keys[j] = map->keys[j + 1];
                    map->values[j] = map->values[j + 1];
                }
                map->size--;
                return;
            }
        }
    }
    void qc_print_map(qc_map* map) {
        printf("{");
        for (int i = 0; i < map->size; i++) {
            switch (map->key_type) {
                case 0: printf("%d", *(int*)map->keys[i]); break;
                case 1: printf("%g", *(float*)map->keys[i]); break;
                case 2: printf("%g", *(double*)map->keys[i]); break;
                case 3: printf("'%c'", *(char*)map->keys[i]); break;
                case 4: printf("%s", *(bool*)map->keys[i] ? "true" : "false"); break;
                case 5: {
                    uint8_t q = *(uint8_t*)map->keys[i] & 0x3;
                    printf("%s", (q == 0) ? "none" : (q == 1) ? "qfalse" : (q == 2) ? "qtrue" : "both");
                    break;
                }
                case 6: printf("\"%s\"", (char*)map->keys[i]); break;
            }
            
            printf(": ");
            
            switch (map->value_type) {
                case 0: printf("%d", *(int*)map->values[i]); break;
                case 1: printf("%g", *(float*)map->values[i]); break;
                case 2: printf("%g", *(double*)map->values[i]); break;
                case 3: printf("'%c'", *(char*)map->values[i]); break;
                case 4: printf("%s", *(bool*)map->values[i] ? "true" : "false"); break;
                case 5: {
                    uint8_t q = *(uint8_t*)map->values[i] & 0x3;
                    printf("%s", (q == 0) ? "none" : (q == 1) ? "qfalse" : (q == 2) ? "qtrue" : "both");
                    break;
                }
                case 6: printf("\"%s\"", (char*)map->values[i]); break;
            }
            
            if (i < map->size - 1) printf(", ");
        }
        printf("}");
    }

    char* qc_map_to_string(qc_map* map) {
        int est_size = 256;
        char* result = (char*)malloc(est_size);
        char* p = result;
        int remaining = est_size;
        
        *p++ = '{'; remaining--;
        
        for (int i = 0; i < map->size; i++) {
            char buf[128];
            
            switch (map->key_type) {
                case 0: snprintf(buf, 128, "%d", *(int*)map->keys[i]); break;
                case 1: snprintf(buf, 128, "%g", *(float*)map->keys[i]); break;
                case 2: snprintf(buf, 128, "%g", *(double*)map->keys[i]); break;
                case 3: snprintf(buf, 128, "'%c'", *(char*)map->keys[i]); break;
                case 4: snprintf(buf, 128, "%s", *(bool*)map->keys[i] ? "true" : "false"); break;
                case 5: {
                    uint8_t q = *(uint8_t*)map->keys[i] & 0x3;
                    snprintf(buf, 128, "%s", (q == 0) ? "none" : (q == 1) ? "qfalse" : (q == 2) ? "qtrue" : "both");
                    break;
                }
                case 6: snprintf(buf, 128, "\"%s\"", (char*)map->keys[i]); break;
            }
            
            int len = strlen(buf);
            if (remaining < len + 10) {
                int offset = p - result;
                est_size *= 2;
                result = (char*)realloc(result, est_size);
                p = result + offset;
                remaining = est_size - offset;
            }
            
            strcpy(p, buf);
            p += len;
            remaining -= len;
            
            *p++ = ':'; *p++ = ' '; remaining -= 2;
            
            switch (map->value_type) {
                case 0: snprintf(buf, 128, "%d", *(int*)map->values[i]); break;
                case 1: snprintf(buf, 128, "%g", *(float*)map->values[i]); break;
                case 2: snprintf(buf, 128, "%g", *(double*)map->values[i]); break;
                case 3: snprintf(buf, 128, "'%c'", *(char*)map->values[i]); break;
                case 4: snprintf(buf, 128, "%s", *(bool*)map->values[i] ? "true" : "false"); break;
                case 5: {
                    uint8_t q = *(uint8_t*)map->values[i] & 0x3;
                    snprintf(buf, 128, "%s", (q == 0) ? "none" : (q == 1) ? "qfalse" : (q == 2) ? "qtrue" : "both");
                    break;
                }
                case 6: snprintf(buf, 128, "\"%s\"", (char*)map->values[i]); break;
            }
            
            len = strlen(buf);
            if (remaining < len + 10) {
                int offset = p - result;
                est_size *= 2;
                result = (char*)realloc(result, est_size);
                p = result + offset;
                remaining = est_size - offset;
            }
            
            strcpy(p, buf);
            p += len;
            remaining -= len;
            
            if (i < map->size - 1) {
                *p++ = ','; *p++ = ' '; remaining -= 2;
            }
        }
        
        *p++ = '}';
        *p = '\0';
        
        return result;
    }
    int qc_map_size(qc_map* map) {
        return map->size;
    }

    qc_list* qc_map_keys(qc_map* map) {
        qc_list* list = qc_create_list(map->key_type);
        
        if (map->size > list->capacity) {
            list->capacity = map->size;
            list->data = (void**)realloc(list->data, list->capacity * sizeof(void*));
        }
        
        for (int i = 0; i < map->size; i++) {
            
            if (map->key_type <= 5) {
                int size = sizeof_type(map->key_type);
                void* copy = malloc(size);
                memcpy(copy, map->keys[i], size);
                list->data[i] = copy;
            } else if (map->key_type == 6) {
                list->data[i] = (void*)strdup((char*)map->keys[i]);
            } else {
                list->data[i] = map->keys[i];
            }
        }
        list->size = map->size;
        return list;
    }
    void* qc_spread_call(
        void* func_ptr,
        int arg_count,
        void** args,
        int* arg_types,
        int return_type,
        void* return_buffer
    ) {
        ffi_cif cif;
        ffi_type** ffi_args = (ffi_type**)malloc(arg_count * sizeof(ffi_type*));
        
        for (int i = 0; i < arg_count; i++) {
            switch (arg_types[i]) {
                case 0: ffi_args[i] = &ffi_type_sint32; break;
                case 1: ffi_args[i] = &ffi_type_float; break;
                case 2: ffi_args[i] = &ffi_type_double; break;
                case 3: ffi_args[i] = &ffi_type_sint8; break;
                case 4: ffi_args[i] = &ffi_type_uint8; break;
                case 5: ffi_args[i] = &ffi_type_uint8; break;
                case 6: ffi_args[i] = &ffi_type_pointer; break;
                default: ffi_args[i] = &ffi_type_pointer; break;
            }
        }
        
        ffi_type* ret_type;
        switch (return_type) {
            case -1: ret_type = &ffi_type_void; break;
            case 0:  ret_type = &ffi_type_sint32; break;
            case 1:  ret_type = &ffi_type_float; break;
            case 2:  ret_type = &ffi_type_double; break;
            case 3:  ret_type = &ffi_type_sint8; break;
            case 4:  ret_type = &ffi_type_uint8; break;
            case 5:  ret_type = &ffi_type_uint8; break;
            case 6:  ret_type = &ffi_type_pointer; break;
            default: ret_type = &ffi_type_pointer; break;
        }
        
        if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, arg_count, ret_type, ffi_args) == FFI_OK) {
            ffi_call(&cif, FFI_FN(func_ptr), return_buffer, args);
        }
        
        free(ffi_args);
        return return_buffer;
    }
    char* qc_list_to_string(qc_list* list) {
        int est_size = 256;
        char* result = (char*)malloc(est_size);
        char* p = result;
        int remaining = est_size;
        
        *p++ = '['; remaining--;
        
        for (int i = 0; i < list->size; i++) {
            char buf[128];
            
            switch (list->elem_type) {
                case 0: snprintf(buf, 128, "%d", *(int*)list->data[i]); break;
                case 1: snprintf(buf, 128, "%g", *(float*)list->data[i]); break;
                case 2: snprintf(buf, 128, "%g", *(double*)list->data[i]); break;
                case 3: snprintf(buf, 128, "'%c'", *(char*)list->data[i]); break;
                case 4: snprintf(buf, 128, "%s", *(bool*)list->data[i] ? "true" : "false"); break;
                case 5: {
                    uint8_t q = *(uint8_t*)list->data[i] & 0x3;
                    snprintf(buf, 128, "%s", (q == 0) ? "none" : (q == 1) ? "qfalse" : (q == 2) ? "qtrue" : "both");
                    break;
                }
                case 6: snprintf(buf, 128, "\"%s\"", (char*)list->data[i]); break;
            }
            
            int len = strlen(buf);
            if (remaining < len + 10) {
                int offset = p - result;
                est_size *= 2;
                result = (char*)realloc(result, est_size);
                p = result + offset;
                remaining = est_size - offset;
            }
            
            strcpy(p, buf);
            p += len;
            remaining -= len;
            
            if (i < list->size - 1) {
                *p++ = ','; *p++ = ' '; remaining -= 2;
            }
        }
        
        *p++ = ']';
        *p = '\0';
        
        return result;
    }
    void* qc_fopen(const char* path, const char* mode) {
        FILE* f = fopen(path, mode);
        return (void*)f;
    }
    
    void qc_fclose(void* file) {
        if (file) fclose((FILE*)file);
    }
    
    char* qc_fread(void* file) {
        if (!file) return strdup("");
        
        char buffer[1024];
        if (fgets(buffer, sizeof(buffer), (FILE*)file)) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len-1] == '\n') {
                buffer[len-1] = '\0';
            }
            return strdup(buffer);
        }
        return strdup("");
    }
    
    void qc_fwrite(void* file, const char* data) {
        if (file && data) {
            fputs(data, (FILE*)file);
            fputc('\n', (FILE*)file);
        }
    }
    typedef struct {
        void** items;
        int count;
        int current_index;
    } qc_variadic;
    bool qc_variadic_is_empty(qc_variadic* variadic) {
        return variadic->current_index >= variadic->count;
    }
    void* qc_variadic_next(qc_variadic* variadic) {
        if (qc_variadic_is_empty(variadic)) {
            return nullptr;
        }
        void* data = variadic->items[variadic->current_index];
        variadic->current_index++;
        return data;
    }
}