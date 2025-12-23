////////////////////////////////////////////////////////////////////////////////
// QUANTUM C ULTIMATE TORTURE TEST
// ==========================================================

// SECTION 1: BASIC ARITHMETIC & OPERATOR PRECEDENCE
// --------------------------------------------------
2 + 3;                    // 5
10 - 5;                   // 5
4 * 6;                    // 24
20 / 4;                   // 5
1 + 2 * 3;                // 7 (precedence)
(1 + 2) * 3;              // 9
10 - 2 - 2;               // 6 (left‑assoc)
20 / 5 / 2;               // 2
100 / (2 * 5);            // 10

// SECTION 2: POWER OPERATOR (RIGHT‑ASSOCIATIVE)
// --------------------------------------------------
2 ** 3;                   // 8
2 ** 3 ** 2;              // 512 (2 ** (3**2))
(2 ** 3) ** 2;            // 64
2 ** (1 + 2);             // 8
3 ** 2 ** 1;              // 9
2 ** 2 ** 2 ** 2;         // 65536

// SECTION 3: UNARY OPERATORS & NEGATION
// --------------------------------------------------
-5;                       // -5
+10;                      // 10
--5;                      // 6 (increment)
--(-5);                   // -6
-(-10);                   // 10
---10;                    // -10
-2 ** 4;                  // -16 for - (2**4)
(-2) ** 4;                // 16
2 ** -2;                  // 0.25 (float)

// SECTION 4: FLOATING POINT & PRECISION
// --------------------------------------------------
float f1 = 2.5f;
float f2 = 3.5f;
f1 + f2;                  // ~6.0
10.0 / 3.0;               // ~3.333333
double d1 = 1.23456789;
d1 * 2;                   // ~2.46913578
0.1 + 0.2;                // 0.30000000000000004
2.5 ** 2;                 // 6.25
1.5 ** 0.5;               // ~1.2247

// SECTION 5: VARIABLE DECLARATION & SCOPE PERSISTENCE
// --------------------------------------------------
int a = 10;
int b = 20;
int c = a + b;            // 30
c = c * 2;                // 60
a = b = c;                // chain assignment
a;                        // 60
b;                        // 60

// Empty declarations
int empty_int;
empty_int;                // 0
string empty_str;
empty_str;                // ""

// SECTION 6: STATIC TYPING TORTURE
// --------------------------------------------------
int my_int = 100;
// my_int = "fail";       // SHOULD THROW: type mismatch
string my_str = "QC";
my_str = "2025";          // ok
// float my_float = 5;    // decide: error or cast to 5.0

// SECTION 7: STRING TESTS
// --------------------------------------------------
string s1 = "Hello";
string s2 = " World";
string s3 = s1 + s2;      // "Hello World"
string s4 = "Line1\nLine2";
string s5 = "Quote: \"Testing\"";
string s6 = "Path: C:\\Users\\Dev";
s3 + " " + "2025";        // "Hello World 2025"

// SECTION 8: COMPLEX NESTED EXPRESSIONS
// --------------------------------------------------
int result = ((5 + 3) * (10 / 2) ** 2 - (100 / 4)) / 5;
// ((8 * 25) - 25) / 5 = (200 - 25) / 5 = 35
result;

int boss = -2 ** 3 ** 2 + (5 - 3) * 4 ** 2 / 2 - --7 + (10 * (5 + 3) - 20) / 4;
// -512 + 16 - 6 + (10*8 - 20)/4 => -512 + 16 - 6 + (80-20)/4 = -512+16-6+15 = -487
boss;

// SECTION 9: EDGE CASES
// --------------------------------------------------
// 1 / 0;                  // SHOULD THROW: division by zero
0 / 1;                    // 0
0 ** 0;                   // 1
5 ** 0;                   // 1
0 ** 5;                   // 0
// Large overflow arithmetic tests can be checked if supported

// SECTION 10: DEEP NESTING & LONG CHAINS
// --------------------------------------------------
((((((((((1+1))))))))));  // 2
1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1; // 20
2 ** (2 ** (2 ** (2 ** 0)));            // 16

// SECTION 11: REASSIGNMENT PERSISTENCE
// --------------------------------------------------
int counter = 0;
counter = ++counter;      // 1
counter = ++counter;      // 2
counter = ++counter;      // 3
counter = counter * counter; // 9
int final_val;
final_val = counter ** 2; // 81
final_val;

// SECTION 12: CHARACTER TESTS
// --------------------------------------------------
char c1 = 'A';
char c2 = '\n';
char c3 = '\'';           // escaped single quote
c1;
c2;
c3;
// int char_math = c1 + 1; // If char is numeric 65+1 => 66

// SECTION 13: BOOLEAN & LOGIC (if supported)
// --------------------------------------------------
bool b1 = true;
bool b2 = false;
b1 && b2;               // false
b1 || b2;               // true
!b1;                    // false
// SECTION 14: MIXED FLOAT & INT OPERATIONS
// --------------------------------------------------
int start = 10;
int end = start * 10;
double big_end = end * 1000000.0;
big_end;

// SECTION 15: COMMENT STRESS
// Single line comment
/* Multi-line
   comment across
   several lines */
int after_comment = 1; // Code after comment
////////////////////////////////////////////////////////////////////////////////
// SECTION 14: COMPARISON OPERATORS
////////////////////////////////////////////////////////////////////////////////
5 == 5;         // true
5 != 3;         // true
10 > 5;         // true
5 < 10;         // true
5 >= 5;         // true
5 <= 5;         // true
3 > 10;         // false
10 < 5;         // false

// With variables
int a = 10;
int b = 20;
a == b;         // false
a != b;         // true
a < b;          // true
b > a;          // true
a <= 10;        // true
b >= 20;        // true

// Chained comparisons
5 < 10;         // true
10 > 5;         // true

////////////////////////////////////////////////////////////////////////////////
// SECTION 15: LOGICAL OPERATORS (AND, OR, NOT)
////////////////////////////////////////////////////////////////////////////////
bool t = true;
bool f = false;

// AND operator
t && t;         // true
t && f;         // false
f && t;         // false
f && f;         // false

// OR operator
t || t;         // true
t || f;         // true
f || t;         // true
f || f;         // false

// NOT operator
!t;             // false
!f;             // true
!!t;            // true
!!!t;           // false

////////////////////////////////////////////////////////////////////////////////
// SECTION 16: COMPLEX BOOLEAN EXPRESSIONS
////////////////////////////////////////////////////////////////////////////////
t && t || f;            // true (AND before OR)
t || f && f;            // true
(t || f) && f;          // false (parens override)
!t || !f;               // true
!(t && f);              // true
!(t || f);              // false

// With comparisons
5 > 3 && 10 < 20;       // true
5 > 10 || 3 < 5;        // true
!(5 == 5);              // false
5 != 3 && 10 >= 10;     // true

// With variables
int x = 15;
int y = 20;
x > 10 && y < 30;       // true
x == 15 || y == 15;     // true
!(x > y);               // true
x < y && x > 0;         // true

////////////////////////////////////////////////////////////////////////////////
// SECTION 17: TRUTHINESS (Non-boolean values in logic)
////////////////////////////////////////////////////////////////////////////////
int zero = 0;
int nonzero = 42;
!zero;                  // true (0 is falsy)
!nonzero;               // false (42 is truthy)

string empty = "";
string full = "hello";
!empty;                 // true (empty string is falsy)
!full;                  // false (non-empty is truthy)

////////////////////////////////////////////////////////////////////////////////
// SECTION 18: SHORT-CIRCUIT EVALUATION
////////////////////////////////////////////////////////////////////////////////
// These should short-circuit (not evaluate right side if not needed)
bool result1 = f && t;  // false (doesn't evaluate right)
bool result2 = t || f;  // true (doesn't evaluate right)

// Complex short-circuit
int val = 5;
val > 10 && val < 20;   // false (second part not evaluated)
val < 10 || val > 20;   // true (second part not evaluated)

////////////////////////////////////////////////////////////////////////////////
// SECTION 19: MIXED COMPARISONS AND LOGIC
////////////////////////////////////////////////////////////////////////////////
int score = 85;
bool passed = score >= 60;
bool excellent = score >= 90;
bool good = score >= 70 && score < 90;

passed;                 // true
excellent;              // false
good;                   // true

// Grade calculation
bool a_grade = score >= 90;
bool b_grade = score >= 80 && score < 90;
bool c_grade = score >= 70 && score < 80;
bool failing = score < 60;

a_grade;                // false
b_grade;                // true
c_grade;                // false
failing;                // false

////////////////////////////////////////////////////////////////////////////////
// SECTION 20: EDGE CASES
////////////////////////////////////////////////////////////////////////////////
// Double negation
!!true;                 // true
!!false;                // false
!!5;                    // true (5 is truthy)
!!0;                    // false (0 is falsy)

// Complex nesting
(5 > 3 && 10 < 20) || (3 > 5 && 20 < 10);  // true
!(5 > 3) && !(10 < 20);                     // false
(true && false) || (false && true);         // false
(true || false) && (false || true);         // true

// Comparison chains
5 < 10;                 // true
10 < 20;                // true
5 < 10;                 // true

// END OF LOGIC TESTS

////////////////////////////////////////////////////////////////////////////////
// SECTION X: IF / ELSE / ELSE IF (CONTROL FLOW) - TORTURE TEST
////////////////////////////////////////////////////////////////////////////////

// Basic if/else
int v = 5;
if (v > 10) {
    v = 100;
} else if (v > 3) {
    v = v + 1;
} else {
    v = 0;
}
v;                      // expect 6

// Single-statement if (no braces) - allowed
int s = 0;
if (v == 6) s = 1;
s;                      // expect 1

// Nested if/else
if (v > 0) {
    if (v % 2 == 0) {
        v = v / 2;
    } else {
        v = v * 2;
    }
}
v;                      // if v==6 -> 3

// Multi-branch else-if chain
int score_if = 85;
string grade = "";
if (score_if >= 90) {
    grade = "A";
} else if (score_if >= 80) {
    grade = "B";
} else if (score_if >= 70) {
    grade = "C";
} else {
    grade = "F";
}
grade;                  // expect "B"

// Truthiness in conditions (strings and numbers)
string maybe = "";
int flag = 0;
if (maybe) {
    flag = 1;
} else {
    flag = 2;
}
flag;                   // expect 2 (empty string falsy)

// else with only a single statement
int x_if = 2;
if (x_if > 10) {
    x_if = 10;
} else x_if = x_if + 3;
x_if;                   // expect 5

// Edge: if with boolean values
bool b_if = true;
if (b_if) {
    b_if = false;
} else {
    b_if = true;
}
b_if;                   // expect false

// Complex nested chains
int nested = 0;
if (v > 10) {
    nested = 100;
} else if (v > 2) {
    if (v % 3 == 0) {
        nested = 30;
    } else {
        nested = 20;
    }
} else {
    nested = 5;
}

////////////////////////////////////////////////////////////////////////////////
// IF-WITH-INIT TESTS
////////////////////////////////////////////////////////////////////////////////

// 1) Simple declaration init: init variable visible in condition & branch, not after
if (int a = 5; a < 10) {
    a;              // expect 5 (inside branch)
}
//a;                  // expect runtime error: Undefined variable 'a'

// 2) Declaration init without initializer for non-const (default value)
if (int b; b == 0) {
    b = 7;
    b;              // expect 7
}
//b;                  // expect runtime error: Undefined variable 'b'

// 3) const declaration init must require initializer
// should be a syntax error (const requires initializer)
//if (const int c; c == 0) {
  ///  c;
//}

// 4) Expression-style init (assignment): modifies outer variable if present
int outer = 1;
if (outer = outer + 2; outer < 10) {
    outer;          // expect 3 (assignment happened in init and persists)
}
outer;              // expect 3 (outer variable was updated)

// 5) Expression init that uses a temporary and does not declare
int y = 0;
if (y = 4; y > 2) {
    y;              // expect 4
}
y;                  // expect 4 (assignment changed outer y)

// 6) Declaration init shadows outer variable (inner scope)
int shadow = 10;
if (int shadow = 2; shadow == 2) {
    shadow;         // expect 2 (inner shadow)
}
shadow;             // expect 10 (outer value unchanged)

// 7) Nested if-with-init: each init has its own scope and dies after its if
if (int i = 1; i < 5) {
    if (int j = i + 1; j < 5) {
        j;          // expect 2 (inner j)
    }
    // j is not visible here
    // j;            // would be undefined
    i;              // expect 1 (i is visible here)
}
// i and j undefined here

// 8) Init as complex expression (function-call-style if available)
// if (int a = some_call(); a > 0) { ... }
// (example only; replace some_call() with actual expr if you have functions)

// 9) Multi-branch with init (init applies to the whole if/elif/else)
if (int s = 2; s == 1) {
    s;
} else if (s == 2) {
    s = s + 10;
    s;              // expect 12
} else {
    s;
}
// s is undefined here

// 10) Ensure semicolon required between init and condition (syntax error)
//if (int z = 3 z < 10) {
 //   z;
//}

// 11) Using init for boolean/test truthiness
if (int t = 0; t) {
    t;
} else {
    1;              // expect else to run, value 1
}

// 12) Init with compound assignment expression
int cx = 2;
if (cx += 3; cx == 5) {
    cx;             // expect 5
}
cx;                 // expect 5

// 13) Confirm RAII/exception-safety 
// if (int thrower = may_throw(); thrower > 0) { ... }   // should pop init scope on error

////////////////////////////////////////////////////////////////////////////////
// END: IF-WITH-INIT TEST BLOCK
////////////////////////////////////////////////////////////////////////////////      
// END OF TEST
// Expected: full success — every valid expression should produce correct value or throw the right error.
