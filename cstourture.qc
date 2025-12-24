////////////////////////////////////////////////////////////////////////////////
// CHAR & STRING LITERAL ULTIMATE TORTURE SUITE
// Designed to push every edge case of char/string parsing

// SECTION A — Simple Char Literals
// --------------------------------
'A';           // 65
'Z';           // 90
'0';           // 48

// SECTION B — Escape Sequences in Char Literals
// ---------------------------------------------
'\n';          // newline (10)
'\t';          // tab (9)
'\r';          // carriage return (13)
'\\';          // backslash
'\'';          // single quote

// SECTION C — Invalid Char Literals (should error)
// -----------------------------------------------
// '';         // empty char literal
// 'AB';       // more than one character
// '\x';       // incomplete escape

// SECTION D — Simple String Literals
// ----------------------------------
"";            // empty string
"Hello";       // simple
"World!";      // another simple

// SECTION E — Escape Sequences in Strings
// ---------------------------------------
"Line1\nLine2";             // contains newline
"Tabbed\tText";             // contains a tab
"Quote: \"";                // contains a double quote
"Backslash: \\";            // contains a backslash
"Mix: A\\B\\C\nEnd";        // mix sequences

// SECTION G — Complex Expressions Involving Char/String
// ------------------------------------------------------
string s1 = "Hello";
string s2 = " World";
string s3 = s1 + s2;        // should be "Hello World"
s3 + " " + "QC";            // "Hello World QC"

char c1 = 'A';
char c2 = 'B';
c1;                         // 65
c2;                         // 66

// SECTION H — Mixed Numeric & Char Expressions
// ---------------------------------------------
c1 + 1;                     // numeric addition: 65 + 1 = 66
c2 - 'A';                   // 66 - 65 = 1
'A' + 'B';                  // 65 + 66 = 131

// SECTION I — Strings with lots of escapes (LTS test)
// ---------------------------------------------------
"\\\\\\\\\\\\\\\\\\\\\\\\\\";   // many backslashes
"\\n\\t\\r\\'\\\"";              // literal backslash + letters

// SECTION J — Combined Char + String
// ----------------------------------
string combo = "Line:\n" + " ' " + " chars"; // multiple components

// SECTION K — Edge / Error Cases
// -------------------------------
// unterminated string literal:
// "Unfinished
// Invalid escape:
// "Bad:\q"
// unterminated char
// 'X
