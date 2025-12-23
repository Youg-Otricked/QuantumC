////////////////////////////////////////////////////////////////////////////////
// QUANTUM C 2025 ULTIMATE TORTURE TEST (300+ LINES)
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
// bool b1 = true;
// bool b2 = false;
// b1 && b2;               // false
// b1 || b2;               // true
// !b1;                    // false

// SECTION 14: MIXED FLOAT & INT OPERATIONS
// --------------------------------------------------
int start = 10;
float end = start / 4.0f;   // 2.5
double big_end = end * 1000000;
big_end;

// SECTION 15: COMMENT STRESS
// Single line comment
/* Multi-line
   comment across
   several lines */
int after_comment = 1; // Code after comment

// END OF TEST
// Expected: full success — every valid expression should produce correct value or throw the right error.