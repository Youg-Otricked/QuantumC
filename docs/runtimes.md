<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Custom Runtimes

[Back to Home](./index.md)

You may be thinking "This language has a lot of intrinsics. That must mean its going to fill my binary with bloat!".

That is incorrect. Not only does the runtime only link libc and a file of 96 small helpers/wrappers, it also can be excluded from your file.

By passing the `-nrt` or `--no-runtime` flag to the compiler, you can tell the compiler not to link the runtime `.ll`. This will disable

1. String Concatenation
2. All intrinsics other than `` `ternary ``, `` `to_address``, `` `mapped_ptr``, `` `inline ``, and `` `typeof ``
3. String equality
4. All qbool operations
5. Struct printing
6. Variadics
7. Jagged Arrays
8. f strings
9. qin (input)
10. Power (`#^`) operator on integers

If you get a undefined function error starting in `qc_`, its most likely a unallowed feature.

However, you may think "Why would anybody do that?". The answe is simple. _Custom runtimes_.

The runtime is just 94 functions and 2 structs. Its really simple to make your own. Reference the following table to see what functions you need to make per feature.
1. String Concatenation
    - `string qc_string_concat(string a, string b)`
2. Power on ints
    - `int qc_powi_i32(int base, int exp)`
3. Variadics
    - ```qc
    struct qc_variadic {
        void* *items;
        int count;
        int current_index;
    };
    ```
    - `bool qc_variadic_is_empty(qc_variadic *variadic)`
    - `void* qc_variadic_next(qc_variadic *variadic)`

4. String Equality
    - `bool qc_string_eq(string a, string b)`

5. All qbool operations
    - `int qc_qand(int a, int b)` 
    - `int qc_qor(int a, int b)`
    - `int qc_qxor(int a, int b)`
    - `int qc_not(int a)`
    - `bool qc_qand_collapse(int a, int b)`
    - `bool qc_qor_collapse(int a, int b)`
6. Jagged Arrays
    - ```qc
    struct qc_jagged_array {
        void* *data;
        int *sizes;
        int count;
        int elem_type;
        int depth;
    }
    ```
    - `qc_jagged_array* qc_create_jagged_array(int count, int elem_type, int depth)`
    - `void qc_set_jagged_element(qc_jagged_array *arr, int idx, void *elem, int size)`
    - `void qc_free_jagged_array(qc_jagged_array *arr)`
    - `void* qc_jagged_array_get(qc_jagged_array *arr, int *indices, int num_indices)`
    - `void* qc_create_leaf_row(int size, int elem_type)`
    - `void qc_set_leaf_element(void *row, int idx, void *value, int elem_type)`
    - `string qc_jagged_to_string(qc_jagged_array *arr)`
7. qin
    - `string qc_qin()`
    - all of the stringify helpers below.
8. fstrings
    - all of the stringify helpers below.
9. qout
    - fmt helpers
```
string qc_fmt_int(long int v, int width, int precision, bool zero_pad)
string qc_fmt_unsigned_int(addr_t v, bool zero_pad)
string qc_fmt_float(double v, int width, int precision, bool zero_pad)
string qc_fmt_double(double v, int width, int precision, bool zero_pad)
string qc_fmt_scientific(double v, int width, int precision, bool zero_pad)
string qc_fmt_char(char c, int width, bool zero_pad)
string qc_fmt_string(string s, int width, bool zero_pad)
string qc_fmt_hex(addr_t v, int width, bool zero_pad)
string qc_fmt_octal(addr_t v, int width, bool zero_pad)
string qc_fmt_bool(bool v, int width, bool zero_pad)
string qc_fmt_qbool(int q, int width, bool zero_pad)
string qc_fmt_ptr(void *p, int width, bool zero_pad)
```
    - stringify helpers
```
string qc_to_string_int(int x)
string qc_to_string_float(float x)
string qc_to_string_long_int(long int x)
string qc_to_string_short_int(short x)
string qc_to_string_double(double x)
string qc_to_string_bool(bool b)
string qc_to_string_qbool(int q)
string qc_to_string_char(char c)
string qc_array_to_string_recursive(void *arr, int elem_type, int ndims, int *dims) (optional, only used by fstring)
```
    - `void qc_print_string(string s)`
10. The Rest of the intrinsics:
    - the functions below (mix and match for various intrinsics)
```qc
void* qc_malloc(addr_t size) {
void qc_free(void* ptr) {
void* qc_realloc(void* ptr, addr_t size) {
void* qc_calloc(addr_t num, addr_t size) {
void qc_flush() {
int qc_to_int_from_float(float x) {
int qc_to_int_from_double(double x) {
int qc_to_int_from_char(char c) {
float qc_to_float_from_double(double x) {
float qc_to_float_from_bool(bool b) {
double qc_to_double_from_float(float x) {
double qc_to_double_from_bool(bool b) {
bool qc_to_bool_from_int(int x) {
bool qc_to_bool_from_float(float x) {
bool qc_to_bool_from_double(double x) {
char qc_to_char_from_int(int x) {
int qc_time() {
void qc_seed(int seed) {
float qc_random_float() {
int qc_random_int(int max) {
int qc_random_range(int min, int max) {
int qc_len(string str) {
string qc_to_lower(string str) {
string qc_to_upper(string str) {
string qc_substring(string str, int start, int length) {
int qc_contains(string str, string substr) {
int qc_startswith(string str, string prefix) {
int qc_endswith(string str, string suffix) {
bool qc_to_bool_from_string(string str) {
int qc_to_qbool_from_string(string str) {
string qc_trim(string str) {
string qc_replace(string str, string find, string replace) {
int qc_to_int_from_string(string str) {
short qc_to_short_int_from_string(string str) {
long int qc_to_long_int_from_string(string str) {
addr_t qc_to_addr_t_from_string(string str) {
float qc_to_float_from_string(string str) {
double qc_to_double_from_string(string str) {
char qc_to_char_from_string(string str) {
int qc_to_int_from_bool(bool b) {
float qc_to_float_from_int(int x) {
double qc_to_double_from_int(int x) {
int qc_open(string path, string mode) {
void qc_close(int fd) {
void qc_write(int fd, string data) {
```
