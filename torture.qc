
int main() {

////////////////////////////////////////////////////////////////////////////////
// 1️ ARITHMETIC & OPERATOR HELL
////////////////////////////////////////////////////////////////////////////////
int a = 2;
int b = 3; 
int c = 4;
float f = -2.5f;
double d = 1.5;

println((a + b) * c ** 2 - (a - b) ** (b + 1)); // Complex precedence
println(-(-(-a)));                               // Triple negative
println(0 ** 0);                                 // Edge
println(2 ** 3 ** 2 ** 2);                       // Deep right-associativity
println((f + 1) * d - 0.5);                      // Mixed float/double

// Chained assignments and compound operators
int x = 10; x += 5; x *= 2; x /= 3; x -= 1; println(x); // Check final value

////////////////////////////////////////////////////////////////////////////////
// 2️ VARIABLE & TYPE EDGE CASES
////////////////////////////////////////////////////////////////////////////////
int unset;
string empty;
bool flag = false;
char ch;
float fl;
println(unset, empty, flag, ch, fl);   // Expect 0, "", false, '\0', 0.0

println(x);

string s1 = "123";
string s2 = "abc";
println(s1 + s2);    

////////////////////////////////////////////////////////////////////////////////
// 3️ ARRAYS & LISTS MADNESS
////////////////////////////////////////////////////////////////////////////////
int jagged[][] = [[1,2], [3,4,5]];
int cube[][][] = [[[1],[2,3]], [[4,5],[6]]];

println(cube, jagged);        // Spread

int[] alias1 = [1,2];                     
int[] alias2 = alias1;                    
alias2.push(3);                           
println(alias1, alias2);                  // Alias test

int[] empty_list = [];
//empty_list.pop();                    
println(empty_list);

////////////////////////////////////////////////////////////////////////////////
// 4️ CONTROL FLOW TORTURE
////////////////////////////////////////////////////////////////////////////////
int i = 0;
while(i < 5) {
    i += 1;
    if(i == 2) continue;
    if(i == 4) break;
    println(i);                           // 1,3
}

// Inline init in if
int j = 10;
if(int temp = j * 2; temp > 15) { println(temp); } else { println("Nope"); }

// Nested else-if
int score = 75;
string grade = "";
if(score > 90) grade = "A";
else if(score > 80) grade = "B";
else if(score > 70) grade = "C";
else grade = "F";
println(grade);                           // C

////////////////////////////////////////////////////////////////////////////////
// 5️⃣ FUNCTIONS & LAMBDAS CHAOS
////////////////////////////////////////////////////////////////////////////////
auto factorial = fn(int n) -> int { 
    if(n <= 1) return 1;
    return n * factorial(n - 1);
};

auto double_it = fn(int x) { return x * 2; };
println(double_it(factorial(5)));         // 240
int, string get_user() {
    return 123, "Alice";
}
int a1, string b1 = get_user();
println(a1, b1);                           // 123, Alice

void call_twice(auto f, int v) { f(v); f(v); }
call_twice(fn(int x){ println(x*x); }, 3); // 9 printed twice

auto immediate = fn(int a,int b)->int{return a+b;}(5,7);
println(immediate);                         // 12

////////////////////////////////////////////////////////////////////////////////
// 6️ F-STRINGS & PRINT
////////////////////////////////////////////////////////////////////////////////
int val = 10;
string msg = f"Value {val}, squared {val**2}";
println(msg);

////////////////////////////////////////////////////////////////////////////////
// 7️ QUANTUM BOOL HELL
////////////////////////////////////////////////////////////////////////////////
qbool qb = both;
qif(qb) { println("Superposed True"); } qelse { println("Superposed False"); }

qswitch(qb){
    case t: println("t"); break;
    case f: println("f"); break;
    case b: println("b"); break;
    case n: println("n"); break;
}

qbool a2 = qtrue;
qbool b2 = both;
std::qout << (a2 &&& b2);
std::qout << (a2 ||| b2);
std::qout << (!!b2);


////////////////////////////////////////////////////////////////////////////////
// 8 ARRAY, LIST & SPREAD COMBO
////////////////////////////////////////////////////////////////////////////////
int[] x1 = [1,2];
int[] x2 = [3,4];
int[] x3 = [@x1, @x2, 5];
println(x3);

void print_three(int a,int b,int c){ println(a,b,c); }
int args[] = [10,20,30];
print_three(@args);

////////////////////////////////////////////////////////////////////////////////
// 10️ MULTI-RETURN FUNCTION TEST
////////////////////////////////////////////////////////////////////////////////
int id, string name = get_user();
println(id, name);
////////////////////////////////////////////////////////////////////////////////
// 11️ ARRAY/LIST FUNCTION RETURNS
////////////////////////////////////////////////////////////////////////////////
int[] list_maker() { return [1,2,3]; }
int[] l1 = list_maker();
println(l1);

////////////////////////////////////////////////////////////////////////////////
// 12️ FOREACH LOOP
////////////////////////////////////////////////////////////////////////////////
foreach(int x in [1,2,3,4,5]) { println(x); }

////////////////////////////////////////////////////////////////////////////////
// 13️ FINAL CHECK: DEEP COMBINATION
////////////////////////////////////////////////////////////////////////////////
qbool final_qb = both;
int final_arr[][][] = [[[1,2],[3,4]],[[5,6],[7,8]]];
auto final_lambda = fn(int x){ return x*2 + factorial(3); };
println(final_lambda(final_arr[1][1][1])); // Combination of arrays + lambda + factorial
std::qout << final_qb &&& qb;

////////////////////////////////////////////////////////////////////////////////
return 0;
}