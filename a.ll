; ModuleID = 'qc_module'
source_filename = "qc_module"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct._ffi_type = type { i64, i16, i16, ptr }
%struct.qc_jagged_array = type { ptr, ptr, i32, i32, i32 }
%struct.qc_list = type { ptr, i32, i32, i32 }
%struct.qc_map = type { ptr, ptr, i32, i32, i32, i32 }
%struct.ffi_cif = type { i32, i32, ptr, ptr, i32, i32 }
%Product = type { ptr, i32 }
%Vector2D = type { i32, i32 }
%DoubleCounter = type { i32 }
%ColoredBox = type { i32, i32, ptr, i1 }
%Rectangle2D = type { i32, i32, ptr }
%Employee = type { ptr, i32 }
%SavingsAccount = type { ptr, i32, float }
%Warrior = type { i32, ptr, i32 }
%SecureBox = type { ptr, i1 }
%BankAccount = type { ptr, i32 }
%Cat = type { ptr, i32 }
%Director = type { ptr, i32, i32, ptr }
%PlantLife = type { i1, ptr }
%GameCharacter = type { i32, ptr }
%Counter2 = type { i32 }
%Vehicle = type { ptr, i32 }
%FlowerPlant = type { i1, ptr, ptr }
%CarInherit = type { ptr, i32, i32 }
%Dog = type { ptr, i32 }
%BaseClass = type { i32 }
%Calculator = type { i32 }
%Manager = type { ptr, i32, i32 }
%Counter = type { i32 }
%Person = type { ptr, i32 }
%Robot = type { ptr }
%LivingThing = type { i1 }
%DerivedClass = type { i32, i32 }
%Animal = type { ptr, i32 }
%DogInherit = type { ptr, i32, ptr }
%Rectangle = type { %Point, %Point }
%Point = type { i32, i32 }
%MathOps = type { i8 }
%TierLevel = type { i32, ptr }
%HttpStatus = type { i32, ptr }
%ConfigValue = type { i32, ptr }
%Response = type { i32, ptr }
%Pair = type { i32, ptr }
%Mixed = type { i32, ptr }
%Code = type { i32, ptr }
%Status = type { i32, ptr }
%Multi = type { i32, ptr }
%Value = type { i32, ptr }
%Result = type { i32, ptr }

@.str = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.2 = private unnamed_addr constant [3 x i8] c"%g\00", align 1
@.str.3 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.str.4 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.str.5 = private unnamed_addr constant [5 x i8] c"none\00", align 1
@.str.6 = private unnamed_addr constant [7 x i8] c"qfalse\00", align 1
@.str.7 = private unnamed_addr constant [6 x i8] c"qtrue\00", align 1
@.str.8 = private unnamed_addr constant [5 x i8] c"both\00", align 1
@stdout = external global ptr, align 8
@.str.9 = private unnamed_addr constant [2 x i8] c"1\00", align 1
@stderr = external global ptr, align 8
@stdin = external global ptr, align 8
@.str.10 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.11 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@.str.12 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.13 = private unnamed_addr constant [2 x i8] c"[\00", align 1
@.str.14 = private unnamed_addr constant [3 x i8] c", \00", align 1
@.str.15 = private unnamed_addr constant [2 x i8] c"]\00", align 1
@.str.16 = private unnamed_addr constant [5 x i8] c"\22%s\22\00", align 1
@.str.17 = private unnamed_addr constant [5 x i8] c"'%c'\00", align 1
@.str.18 = private unnamed_addr constant [6 x i8] c"ERROR\00", align 1
@.str.19 = private unnamed_addr constant [8 x i8] c" (\22%s\22)\00", align 1
@.str.20 = private unnamed_addr constant [2 x i8] c"{\00", align 1
@.str.21 = private unnamed_addr constant [3 x i8] c": \00", align 1
@.str.22 = private unnamed_addr constant [2 x i8] c"}\00", align 1
@ffi_type_sint32 = external global %struct._ffi_type, align 8
@ffi_type_float = external global %struct._ffi_type, align 8
@ffi_type_double = external global %struct._ffi_type, align 8
@ffi_type_sint8 = external global %struct._ffi_type, align 8
@ffi_type_uint8 = external global %struct._ffi_type, align 8
@ffi_type_pointer = external global %struct._ffi_type, align 8
@ffi_type_void = external global %struct._ffi_type, align 8
@0 = private unnamed_addr constant [11 x i8] c"Rectangle(\00", align 1
@1 = private unnamed_addr constant [9 x i8] c"topLeft=\00", align 1
@2 = private unnamed_addr constant [2 x i8] c"?\00", align 1
@3 = private unnamed_addr constant [3 x i8] c", \00", align 1
@4 = private unnamed_addr constant [13 x i8] c"bottomRight=\00", align 1
@5 = private unnamed_addr constant [2 x i8] c"?\00", align 1
@6 = private unnamed_addr constant [2 x i8] c")\00", align 1
@7 = private unnamed_addr constant [7 x i8] c"Point(\00", align 1
@8 = private unnamed_addr constant [3 x i8] c"x=\00", align 1
@9 = private unnamed_addr constant [3 x i8] c", \00", align 1
@10 = private unnamed_addr constant [3 x i8] c"y=\00", align 1
@11 = private unnamed_addr constant [2 x i8] c")\00", align 1
@.str.23 = private constant [6 x i8] c"Alice\00"
@.str.24 = private constant [5 x i8] c"test\00"
@.str.25 = private constant [2 x i8] c" \00"
@.str.26 = private constant [1 x i8] zeroinitializer
@.str.27 = private constant [14 x i8] c"Creating list\00"
@.str.28 = private constant [24 x i8] c"After creation, length:\00"
@.str.29 = private constant [8 x i8] c"answer=\00"
@.str.30 = private constant [5 x i8] c", b=\00"
@.str.31 = private constant [6 x i8] c"Alice\00"
@.str.32 = private constant [4 x i8] c"Bob\00"
@.str.33 = private constant [5 x i8] c"Luca\00"
@.str.34 = private constant [17 x i8] c"Hello, Compiler!\00"
@.str.35 = private constant [5 x i8] c"\F0\9F\94\A5\00"
@.str.36 = private constant [6 x i8] c"Hello\00"
@.str.37 = private constant [6 x i8] c"World\00"
@.str.38 = private constant [2 x i8] c"!\00"
@.str.39 = private constant [1 x i8] zeroinitializer
@.str.40 = private constant [14 x i8] c"She said \22Hi\22\00"
@.str.41 = private constant [81 x i8] c"C:\\Users\\Luca(JK its ~/C^4 becuase i dont use the disgusting windows powershell)\00"
@.str.42 = private constant [3 x i8] c"hi\00"
@.str.43 = private constant [3 x i8] c"hi\00"
@.str.44 = private constant [3 x i8] c"hi\00"
@.str.45 = private constant [4 x i8] c"bye\00"
@.str.46 = private constant [6 x i8] c"Hello\00"
@.str.47 = private constant [4 x i8] c"ell\00"
@.str.48 = private constant [4 x i8] c"Hel\00"
@.str.49 = private constant [3 x i8] c"lo\00"
@.str.50 = private constant [7 x i8] c"  hi  \00"
@.str.51 = private constant [2 x i8] c"l\00"
@.str.52 = private constant [2 x i8] c"L\00"
@.str.53 = private constant [3 x i8] c"42\00"
@.str.54 = private constant [5 x i8] c"3.14\00"
@.str.55 = private constant [7 x i8] c"Hello \00"
@.str.56 = private constant [6 x i8] c"World\00"
@.str.57 = private constant [12 x i8] c"Before grid\00"
@.str.58 = private constant [20 x i8] c"After grid creation\00"
@.str.59 = private constant [18 x i8] c"After grid access\00"
@.str.60 = private constant [26 x i8] c"After printing val + grid\00"
@.str.61 = private constant [10 x i8] c"Regular: \00"
@.str.62 = private constant [9 x i8] c"Jagged: \00"
@.str.63 = private constant [7 x i8] c"Deep: \00"
@.str.64 = private constant [2 x i8] c" \00"
@.str.65 = private constant [14 x i8] c"Array length:\00"
@.str.66 = private constant [15 x i8] c"Array foreach:\00"
@.str.67 = private constant [2 x i8] c" \00"
@.str.68 = private constant [1 x i8] zeroinitializer
@.str.69 = private constant [13 x i8] c"List length:\00"
@.str.70 = private constant [11 x i8] c"List push:\00"
@.str.71 = private constant [14 x i8] c"List foreach:\00"
@.str.72 = private constant [2 x i8] c" \00"
@.str.73 = private constant [1 x i8] zeroinitializer
@.str.74 = private constant [10 x i8] c"List pop:\00"
@.str.75 = private constant [13 x i8] c"List access:\00"
@.str.76 = private constant [2 x i8] c" \00"
@.str.77 = private constant [34 x i8] c"Test 1: Return list from function\00"
@.str.78 = private constant [13 x i8] c"List length:\00"
@.str.79 = private constant [15 x i8] c"List contents:\00"
@.str.80 = private constant [2 x i8] c" \00"
@.str.81 = private constant [1 x i8] zeroinitializer
@.str.82 = private constant [30 x i8] c"Test 2: Pass list to function\00"
@.str.83 = private constant [14 x i8] c"Doubled list:\00"
@.str.84 = private constant [2 x i8] c" \00"
@.str.85 = private constant [1 x i8] zeroinitializer
@.str.86 = private constant [31 x i8] c"Test 3: Multi-return with list\00"
@.str.87 = private constant [7 x i8] c"Count:\00"
@.str.88 = private constant [6 x i8] c"Data:\00"
@.str.89 = private constant [2 x i8] c" \00"
@.str.90 = private constant [1 x i8] zeroinitializer
@.str.91 = private constant [21 x i8] c"=== MAP CREATION ===\00"
@.str.92 = private constant [6 x i8] c"Alice\00"
@.str.93 = private constant [4 x i8] c"Bob\00"
@.str.94 = private constant [8 x i8] c"Charlie\00"
@.str.95 = private constant [19 x i8] c"=== MAP ACCESS ===\00"
@.str.96 = private constant [6 x i8] c"Alice\00"
@.str.97 = private constant [4 x i8] c"Bob\00"
@.str.98 = private constant [8 x i8] c"Charlie\00"
@.str.99 = private constant [26 x i8] c"=== MAP SET (NEW KEY) ===\00"
@.str.100 = private constant [5 x i8] c"Dave\00"
@.str.101 = private constant [25 x i8] c"=== MAP SET (UPDATE) ===\00"
@.str.102 = private constant [6 x i8] c"Alice\00"
@.str.103 = private constant [17 x i8] c"=== MAP SIZE ===\00"
@.str.104 = private constant [16 x i8] c"=== MAP HAS ===\00"
@.str.105 = private constant [6 x i8] c"Alice\00"
@.str.106 = private constant [4 x i8] c"Bob\00"
@.str.107 = private constant [4 x i8] c"Eve\00"
@.str.108 = private constant [19 x i8] c"=== MAP REMOVE ===\00"
@.str.109 = private constant [4 x i8] c"Bob\00"
@.str.110 = private constant [4 x i8] c"Bob\00"
@.str.111 = private constant [17 x i8] c"=== MAP KEYS ===\00"
@.str.112 = private constant [3 x i8] c": \00"
@.str.113 = private constant [26 x i8] c"=== MAP WITH INT KEYS ===\00"
@.str.114 = private constant [6 x i8] c"Alice\00"
@.str.115 = private constant [4 x i8] c"Bob\00"
@.str.116 = private constant [8 x i8] c"Charlie\00"
@.str.117 = private constant [5 x i8] c"Dave\00"
@.str.118 = private constant [18 x i8] c"=== EMPTY MAP ===\00"
@.str.119 = private constant [6 x i8] c"first\00"
@.str.120 = private constant [31 x i8] c"=== MAP LITERAL ASSIGNMENT ===\00"
@.str.121 = private constant [2 x i8] c"x\00"
@.str.122 = private constant [2 x i8] c"y\00"
@.str.123 = private constant [2 x i8] c"x\00"
@.str.124 = private constant [25 x i8] c"=== MAP AS PARAMETER ===\00"
@.str.125 = private constant [31 x i8] c"=== ALL MAP TESTS COMPLETE ===\00"
@.str.126 = private constant [21 x i8] c"=== SPREAD TESTS ===\00"
@.str.127 = private constant [42 x i8] c"\0A--- Test 1: Spread arrays into array ---\00"
@.str.128 = private constant [2 x i8] c" \00"
@.str.129 = private constant [1 x i8] zeroinitializer
@.str.130 = private constant [34 x i8] c"\0A--- Test 2: Spread into list ---\00"
@.str.131 = private constant [2 x i8] c" \00"
@.str.132 = private constant [1 x i8] zeroinitializer
@.str.133 = private constant [40 x i8] c"\0A--- Test 3: Spread array into list ---\00"
@.str.134 = private constant [20 x i8] c"Past array creation\00"
@.str.135 = private constant [19 x i8] c"Past list creation\00"
@.str.136 = private constant [2 x i8] c" \00"
@.str.137 = private constant [1 x i8] zeroinitializer
@.str.138 = private constant [40 x i8] c"\0A--- Test 4: Spread list into array ---\00"
@.str.139 = private constant [19 x i8] c"Past list creation\00"
@.str.140 = private constant [22 x i8] c"Past actual spreading\00"
@.str.141 = private constant [2 x i8] c" \00"
@.str.142 = private constant [1 x i8] zeroinitializer
@.str.143 = private constant [34 x i8] c"\0A--- Test 5: Multiple spreads ---\00"
@.str.144 = private constant [2 x i8] c" \00"
@.str.145 = private constant [1 x i8] zeroinitializer
@.str.146 = private constant [42 x i8] c"\0A--- Test 6: Spread in function calls ---\00"
@.str.147 = private constant [3 x i8] c"x=\00"
@.str.148 = private constant [4 x i8] c" y=\00"
@.str.149 = private constant [4 x i8] c" z=\00"
@.str.150 = private constant [36 x i8] c"\0A--- Test 7: Spread with lambda ---\00"
@.str.151 = private constant [6 x i8] c"Sum: \00"
@.str.152 = private constant [42 x i8] c"\0A--- Test 8: Mixed spread and regular ---\00"
@.str.153 = private constant [2 x i8] c" \00"
@.str.154 = private constant [2 x i8] c" \00"
@.str.155 = private constant [2 x i8] c" \00"
@.str.156 = private constant [2 x i8] c" \00"
@.str.157 = private constant [32 x i8] c"\0A--- Test 9: Spread strings ---\00"
@.str.158 = private constant [6 x i8] c"Alice\00"
@.str.159 = private constant [4 x i8] c"Bob\00"
@.str.160 = private constant [8 x i8] c"Charlie\00"
@.str.161 = private constant [5 x i8] c"Dave\00"
@.str.162 = private constant [2 x i8] c" \00"
@.str.163 = private constant [1 x i8] zeroinitializer
@.str.164 = private constant [31 x i8] c"\0A--- Test 10: Empty spread ---\00"
@12 = private unnamed_addr constant [6 x i8] c"int[]\00", align 1
@.str.165 = private constant [2 x i8] c" \00"
@.str.166 = private constant [1 x i8] zeroinitializer
@.str.167 = private constant [35 x i8] c"\0A=== ALL SPREAD TESTS COMPLETE ===\00"
@.str.168 = private constant [21 x i8] c"=== STRUCT TESTS ===\00"
@.str.169 = private constant [30 x i8] c"\0A--- Test 1: Basic struct ---\00"
@.str.170 = private constant [14 x i8] c"Point created\00"
@.str.171 = private constant [4 x i8] c"x: \00"
@.str.172 = private constant [4 x i8] c"y: \00"
@.str.173 = private constant [31 x i8] c"\0A--- Test 2: Modify fields ---\00"
@.str.174 = private constant [4 x i8] c"x: \00"
@.str.175 = private constant [4 x i8] c"y: \00"
@.str.176 = private constant [36 x i8] c"\0A--- Test 3: Function parameter ---\00"
@.str.177 = private constant [7 x i8] c"Point(\00"
@.str.178 = private constant [3 x i8] c", \00"
@.str.179 = private constant [3 x i8] c")\0A\00"
@.str.180 = private constant [33 x i8] c"\0A--- Test 4: Function return ---\00"
@.str.181 = private constant [32 x i8] c"\0A--- Test 5: Nested structs ---\00"
@.str.182 = private constant [12 x i8] c"Top-left: (\00"
@.str.183 = private constant [3 x i8] c", \00"
@.str.184 = private constant [3 x i8] c")\0A\00"
@.str.185 = private constant [16 x i8] c"Bottom-right: (\00"
@.str.186 = private constant [3 x i8] c", \00"
@.str.187 = private constant [3 x i8] c")\0A\00"
@.str.188 = private constant [35 x i8] c"\0A=== ALL STRUCT TESTS COMPLETE ===\00"
@.str.189 = private constant [21 x i8] c"\0A=== UNION TESTS ===\00"
@.str.190 = private constant [34 x i8] c"\0A--- Test 1: Literal variants ---\00"
@.str.191 = private constant [3 x i8] c"ok\00"
@.str.192 = private constant [3 x i8] c"ok\00"
@.str.193 = private constant [9 x i8] c"r1 is ok\00"
@.str.194 = private constant [6 x i8] c"error\00"
@.str.195 = private constant [6 x i8] c"error\00"
@.str.196 = private constant [12 x i8] c"r2 is error\00"
@.str.197 = private constant [9 x i8] c"r3 is 42\00"
@.str.198 = private constant [33 x i8] c"\0A--- Test 2: Type-only union ---\00"
@.str.199 = private constant [5 x i8] c"v1: \00"
@.str.200 = private constant [6 x i8] c"hello\00"
@.str.201 = private constant [5 x i8] c"v2: \00"
@.str.202 = private constant [5 x i8] c"v3: \00"
@.str.203 = private constant [29 x i8] c"\0A--- Test 3: Comparisons ---\00"
@.str.204 = private constant [16 x i8] c"v1 == 100: PASS\00"
@.str.205 = private constant [6 x i8] c"hello\00"
@.str.206 = private constant [18 x i8] c"v2 == hello: PASS\00"
@.str.207 = private constant [17 x i8] c"v3 == 3.14: PASS\00"
@.str.208 = private constant [6 x i8] c"wrong\00"
@.str.209 = private constant [18 x i8] c"v1 != wrong: PASS\00"
@.str.210 = private constant [16 x i8] c"v2 != 999: PASS\00"
@.str.211 = private constant [30 x i8] c"\0A--- Test 4: Reassignment ---\00"
@.str.212 = private constant [5 x i8] c"m = \00"
@.str.213 = private constant [8 x i8] c"changed\00"
@.str.214 = private constant [5 x i8] c"m = \00"
@.str.215 = private constant [5 x i8] c"m = \00"
@.str.216 = private constant [5 x i8] c"m = \00"
@.str.217 = private constant [30 x i8] c"\0A--- Test 5: Control flow ---\00"
@.str.218 = private constant [8 x i8] c"pending\00"
@.str.219 = private constant [8 x i8] c"pending\00"
@.str.220 = private constant [18 x i8] c"Status is pending\00"
@.str.221 = private constant [5 x i8] c"done\00"
@.str.222 = private constant [5 x i8] c"done\00"
@.str.223 = private constant [15 x i8] c"Status is done\00"
@.str.224 = private constant [34 x i8] c"\0A--- Test 6: Numeric variants ---\00"
@.str.225 = private constant [9 x i8] c"Success!\00"
@.str.226 = private constant [11 x i8] c"Not found!\00"
@.str.227 = private constant [14 x i8] c"Custom code: \00"
@.str.228 = private constant [29 x i8] c"\0A--- Test 7: Mixed types ---\00"
@.str.229 = private constant [5 x i8] c"test\00"
@.str.230 = private constant [2 x i8] c" \00"
@.str.231 = private constant [2 x i8] c" \00"
@.str.232 = private constant [2 x i8] c" \00"
@.str.233 = private constant [2 x i8] c" \00"
@.str.234 = private constant [32 x i8] c"\0A--- Test 8: Equality tests ---\00"
@.str.235 = private constant [15 x i8] c"p1 == p2: PASS\00"
@.str.236 = private constant [15 x i8] c"p1 != p3: PASS\00"
@.str.237 = private constant [5 x i8] c"same\00"
@.str.238 = private constant [5 x i8] c"same\00"
@.str.239 = private constant [10 x i8] c"different\00"
@.str.240 = private constant [15 x i8] c"p4 == p5: PASS\00"
@.str.241 = private constant [15 x i8] c"p4 != p6: PASS\00"
@.str.242 = private constant [27 x i8] c"\0A--- Test 9: Functions ---\00"
@.str.243 = private constant [8 x i8] c"success\00"
@.str.244 = private constant [8 x i8] c"failure\00"
@.str.245 = private constant [8 x i8] c"success\00"
@.str.246 = private constant [25 x i8] c"Process returned success\00"
@.str.247 = private constant [8 x i8] c"failure\00"
@.str.248 = private constant [25 x i8] c"Process returned failure\00"
@.str.249 = private constant [20 x i8] c"Process returned 42\00"
@.str.250 = private constant [34 x i8] c"\0A=== ALL UNION TESTS COMPLETE ===\00"
@.str.251 = private constant [32 x i8] c"\0A=== QIN TEST (USACO FENCE) ===\00"
@.str.252 = private constant [38 x i8] c"Type two numbers seperated by a space\00"
@.str.253 = private constant [38 x i8] c"Type two numbers seperated by a space\00"
@.str.254 = private constant [21 x i8] c"\0A=== QIN SUCCESS ===\00"
@.str.255 = private constant [24 x i8] c"\0A=== FILE I/O TESTS ===\00"
@.str.256 = private constant [31 x i8] c"\0A--- Test 1: Write to file ---\00"
@.str.257 = private constant [16 x i8] c"test_output.txt\00"
@.str.258 = private constant [2 x i8] c"w\00"
@.str.259 = private constant [23 x i8] c"Line 1: Hello from QC!\00"
@.str.260 = private constant [24 x i8] c"Line 2: File I/O works!\00"
@.str.261 = private constant [17 x i8] c"Line 3: Amazing!\00"
@.str.262 = private constant [33 x i8] c"Wrote 3 lines to test_output.txt\00"
@.str.263 = private constant [32 x i8] c"\0A--- Test 2: Read from file ---\00"
@.str.264 = private constant [16 x i8] c"test_output.txt\00"
@.str.265 = private constant [2 x i8] c"r\00"
@.str.266 = private constant [16 x i8] c"Read from file:\00"
@.str.267 = private constant [32 x i8] c"\0A--- Test 3: Append to file ---\00"
@.str.268 = private constant [16 x i8] c"test_output.txt\00"
@.str.269 = private constant [2 x i8] c"a\00"
@.str.270 = private constant [18 x i8] c"Line 4: Appended!\00"
@.str.271 = private constant [16 x i8] c"test_output.txt\00"
@.str.272 = private constant [2 x i8] c"r\00"
@.str.273 = private constant [14 x i8] c"After append:\00"
@.str.274 = private constant [1 x i8] zeroinitializer
@.str.275 = private constant [1 x i8] zeroinitializer
@.str.276 = private constant [37 x i8] c"\0A=== ALL FILE I/O TESTS COMPLETE ===\00"
@.str.277 = private constant [26 x i8] c"\0A=== TYPE ALIAS TESTS ===\00"
@.str.278 = private constant [36 x i8] c"\0A--- Test 1: Basic type aliases ---\00"
@.str.279 = private constant [16 x i8] c"Hello, aliases!\00"
@.str.280 = private constant [8 x i8] c"MyInt: \00"
@.str.281 = private constant [11 x i8] c"MyString: \00"
@.str.282 = private constant [10 x i8] c"MyFloat: \00"
@.str.283 = private constant [39 x i8] c"\0A=== ALL TYPE ALIAS TESTS COMPLETE ===\00"
@.str.284 = private constant [20 x i8] c"\0A=== ENUM TESTS ===\00"
@.str.285 = private constant [30 x i8] c"\0A--- Test 1: Integer enum ---\00"
@.str.286 = private constant [12 x i8] c"Status: 200\00"
@.str.287 = private constant [12 x i8] c"Status: 404\00"
@.str.288 = private constant [29 x i8] c"\0A--- Test 2: String enum ---\00"
@13 = private unnamed_addr constant [6 x i8] c"Basic\00", align 1
@.str.289 = private constant [12 x i8] c"Tier: Basic\00"
@14 = private unnamed_addr constant [8 x i8] c"Premium\00", align 1
@.str.290 = private constant [14 x i8] c"Tier: Premium\00"
@.str.291 = private constant [28 x i8] c"\0A--- Test 3: Mixed enum ---\00"
@.str.292 = private constant [11 x i8] c"Retries: 3\00"
@15 = private unnamed_addr constant [9 x i8] c"Timeout!\00", align 1
@.str.293 = private constant [18 x i8] c"Message: Timeout!\00"
@.str.294 = private constant [29 x i8] c"\0A--- Test 4: Comparisons ---\00"
@.str.295 = private constant [18 x i8] c"status1 is OK \E2\9C\93\00"
@.str.296 = private constant [23 x i8] c"status1 == status2 \E2\9C\93\00"
@.str.297 = private constant [24 x i8] c"status1 != NotFound \E2\9C\93\00"
@.str.298 = private constant [30 x i8] c"\0A--- Test 5: Reassignment ---\00"
@16 = private unnamed_addr constant [6 x i8] c"Basic\00", align 1
@.str.299 = private constant [17 x i8] c"Started as Basic\00"
@17 = private unnamed_addr constant [11 x i8] c"Enterprise\00", align 1
@.str.300 = private constant [23 x i8] c"Upgraded to Enterprise\00"
@.str.301 = private constant [30 x i8] c"\0A--- Test 6: Control flow ---\00"
@.str.302 = private constant [9 x i8] c"Success!\00"
@.str.303 = private constant [20 x i8] c"Page not found! \E2\9C\93\00"
@.str.304 = private constant [14 x i8] c"Server error!\00"
@.str.305 = private constant [32 x i8] c"\0A--- Test 7: Switch on enum ---\00"
@18 = private unnamed_addr constant [8 x i8] c"Premium\00", align 1
@19 = private unnamed_addr constant [6 x i8] c"Basic\00", align 1
@20 = private unnamed_addr constant [8 x i8] c"Premium\00", align 1
@21 = private unnamed_addr constant [11 x i8] c"Enterprise\00", align 1
@.str.306 = private constant [11 x i8] c"Basic plan\00"
@.str.307 = private constant [17 x i8] c"Premium plan \E2\9C\93\00"
@.str.308 = private constant [16 x i8] c"Enterprise plan\00"
@.str.309 = private constant [38 x i8] c"\0A--- Test 8: Extract to primitive ---\00"
@.str.310 = private constant [17 x i8] c"Code as int: 500\00"
@22 = private unnamed_addr constant [11 x i8] c"Enterprise\00", align 1
@.str.311 = private constant [27 x i8] c"Plan as string: Enterprise\00"
@.str.312 = private constant [27 x i8] c"\0A--- Test 9: Functions ---\00"
@.str.313 = private constant [22 x i8] c"getStatus(0) = OK \E2\9C\93\00"
@.str.314 = private constant [28 x i8] c"getStatus(1) = NotFound \E2\9C\93\00"
@.str.315 = private constant [31 x i8] c"\0A--- Test 10: Multi-return ---\00"
@.str.316 = private constant [8 x i8] c"Success\00"
@.str.317 = private constant [16 x i8] c"Response OK \E2\9C\93\00"
@.str.318 = private constant [10 x i8] c"Message: \00"
@.str.319 = private constant [25 x i8] c"\0A--- Test 11: typeof ---\00"
@23 = private unnamed_addr constant [8 x i8] c"Premium\00", align 1
@24 = private unnamed_addr constant [7 x i8] c"string\00", align 1
@25 = private unnamed_addr constant [7 x i8] c"string\00", align 1
@26 = private unnamed_addr constant [7 x i8] c"string\00", align 1
@.str.320 = private constant [18 x i8] c"typeof(Premium): \00"
@27 = private unnamed_addr constant [4 x i8] c"int\00", align 1
@28 = private unnamed_addr constant [4 x i8] c"int\00", align 1
@29 = private unnamed_addr constant [4 x i8] c"int\00", align 1
@.str.321 = private constant [13 x i8] c"typeof(OK): \00"
@.str.322 = private constant [29 x i8] c"\0A--- Test 12: While loop ---\00"
@.str.323 = private constant [15 x i8] c"Loop iteration\00"
@.str.324 = private constant [18 x i8] c"Loop complete \E2\9C\93\00"
@.str.325 = private constant [27 x i8] c"\0A--- Test 13: For loop ---\00"
@.str.326 = private constant [13 x i8] c"Iteration OK\00"
@.str.327 = private constant [34 x i8] c"\0A--- Test 14: Unary operators ---\00"
@.str.328 = private constant [14 x i8] c"Negated: -500\00"
@.str.329 = private constant [33 x i8] c"\0A--- Test 15: Equality chain ---\00"
@30 = private unnamed_addr constant [6 x i8] c"Basic\00", align 1
@31 = private unnamed_addr constant [6 x i8] c"Basic\00", align 1
@32 = private unnamed_addr constant [8 x i8] c"Premium\00", align 1
@.str.330 = private constant [25 x i8] c"Equality chain works \E2\9C\93\00"
@.str.331 = private constant [33 x i8] c"\0A=== ALL ENUM TESTS COMPLETE ===\00"
@.str.332 = private constant [27 x i8] c"\0A=== BASIC CLASS TESTS ===\00"
@.str.333 = private constant [35 x i8] c"\0A--- Test 1: Class with fields ---\00"
@.str.334 = private constant [6 x i8] c"Buddy\00"
@.str.335 = private constant [11 x i8] c"Dog name: \00"
@.str.336 = private constant [10 x i8] c"Dog age: \00"
@.str.337 = private constant [34 x i8] c"\0A--- Test 2: Method with this ---\00"
@.str.338 = private constant [9 x i8] c"Whiskers\00"
@.str.339 = private constant [36 x i8] c"\0A--- Test 3: Method with return ---\00"
@.str.340 = private constant [15 x i8] c"After add(5): \00"
@.str.341 = private constant [13 x i8] c"getValue(): \00"
@.str.342 = private constant [34 x i8] c"\0A--- Test 4: Multiple methods ---\00"
@.str.343 = private constant [8 x i8] c"Count: \00"
@.str.344 = private constant [18 x i8] c"After decrement: \00"
@.str.345 = private constant [14 x i8] c"After reset: \00"
@.str.346 = private constant [36 x i8] c"\0A--- Test 5: Field modification ---\00"
@.str.347 = private constant [6 x i8] c"Alice\00"
@.str.348 = private constant [32 x i8] c"\0A--- Test 6: Multiple calls ---\00"
@.str.349 = private constant [5 x i8] c"idle\00"
@.str.350 = private constant [40 x i8] c"\0A=== ALL BASIC CLASS TESTS COMPLETE ===\00"
@.str.351 = private constant [27 x i8] c"\0A=== INHERITANCE TESTS ===\00"
@.str.352 = private constant [35 x i8] c"\0A--- Test 1: Basic inheritance ---\00"
@.str.353 = private constant [17 x i8] c"Golden Retriever\00"
@.str.354 = private constant [8 x i8] c"Breed: \00"
@.str.355 = private constant [10 x i8] c"Species: \00"
@.str.356 = private constant [6 x i8] c"Age: \00"
@.str.357 = private constant [35 x i8] c"\0A--- Test 2: Method overriding ---\00"
@.str.358 = private constant [41 x i8] c"\0A--- Test 3: Multi-level inheritance ---\00"
@.str.359 = private constant [5 x i8] c"Rose\00"
@.str.360 = private constant [4 x i8] c"Red\00"
@.str.361 = private constant [8 x i8] c"Color: \00"
@.str.362 = private constant [7 x i8] c"Type: \00"
@.str.363 = private constant [15 x i8] c"Rose is alive!\00"
@.str.364 = private constant [31 x i8] c"\0A--- Test 4: Public access ---\00"
@.str.365 = private constant [6 x i8] c"Alice\00"
@.str.366 = private constant [9 x i8] c"Holder: \00"
@.str.367 = private constant [11 x i8] c"Balance: $\00"
@.str.368 = private constant [15 x i8] c"New balance: $\00"
@.str.369 = private constant [32 x i8] c"\0A--- Test 5: Private access ---\00"
@.str.370 = private constant [5 x i8] c"1234\00"
@.str.371 = private constant [12 x i8] c"Is locked: \00"
@.str.372 = private constant [5 x i8] c"0000\00"
@.str.373 = private constant [5 x i8] c"1234\00"
@.str.374 = private constant [16 x i8] c"Is locked now: \00"
@.str.375 = private constant [34 x i8] c"\0A--- Test 6: Protected access ---\00"
@.str.376 = private constant [6 x i8] c"Conan\00"
@.str.377 = private constant [33 x i8] c"\0A--- Test 7: Field shadowing ---\00"
@.str.378 = private constant [31 x i8] c"\0A--- Test 8: Complex chain ---\00"
@.str.379 = private constant [4 x i8] c"Bob\00"
@.str.380 = private constant [12 x i8] c"Engineering\00"
@.str.381 = private constant [5 x i8] c"ID: \00"
@.str.382 = private constant [7 x i8] c"Team: \00"
@.str.383 = private constant [7 x i8] c"Dept: \00"
@.str.384 = private constant [43 x i8] c"\0A--- Test 9: Multiple inherited fields ---\00"
@.str.385 = private constant [5 x i8] c"Blue\00"
@.str.386 = private constant [45 x i8] c"\0A--- Test 10: Modifying inherited fields ---\00"
@.str.387 = private constant [40 x i8] c"\0A=== ALL INHERITANCE TESTS COMPLETE ===\00"
@.str.388 = private constant [36 x i8] c"\0A=== OPERATOR OVERLOADING TESTS ===\00"
@.str.389 = private constant [6 x i8] c"v3: (\00"
@.str.390 = private constant [3 x i8] c", \00"
@.str.391 = private constant [2 x i8] c")\00"
@.str.392 = private constant [6 x i8] c"Equal\00"
@.str.393 = private constant [10 x i8] c"Not equal\00"
@.str.394 = private constant [31 x i8] c"\0A=== SPECIAL METHODS TESTS ===\00"
@.str.395 = private constant [7 x i8] c"Laptop\00"
@.str.396 = private constant [17 x i8] c"Product is valid\00"
@.str.397 = private constant [34 x i8] c"\0A=== METHOD OVERLOADING TESTS ===\00"
@.str.398 = private constant [10 x i8] c"Int add: \00"
@.str.399 = private constant [12 x i8] c"Float add: \00"
@.str.400 = private constant [13 x i8] c"String add: \00"
@.str.401 = private constant [6 x i8] c"Hello\00"
@.str.402 = private constant [6 x i8] c"World\00"
@.str.403 = private constant [1 x i8] zeroinitializer
@33 = private unnamed_addr constant [7 x i8] c"auto[]\00", align 1
@.str.404 = private constant [3 x i8] c", \00"
@34 = private unnamed_addr constant [11 x i8] c"list<auto>\00", align 1
@.str.405 = private constant [9 x i8] c"Product(\00"
@.str.406 = private constant [4 x i8] c", $\00"
@.str.407 = private constant [2 x i8] c")\00"
@.str.408 = private constant [20 x i8] c"Product initialized\00"
@.str.409 = private constant [6 x i8] c"Box: \00"
@.str.410 = private constant [2 x i8] c"x\00"
@.str.411 = private constant [8 x i8] c"Color: \00"
@.str.412 = private constant [7 x i8] c"Area: \00"
@.str.413 = private constant [11 x i8] c"Has border\00"
@.str.414 = private constant [12 x i8] c" is working\00"
@.str.415 = private constant [18 x i8] c"Added interest: $\00"
@.str.416 = private constant [6 x i8] c" HP: \00"
@.str.417 = private constant [14 x i8] c"Box unlocked!\00"
@.str.418 = private constant [12 x i8] c"Wrong code!\00"
@.str.419 = private constant [13 x i8] c"Deposited: $\00"
@.str.420 = private constant [12 x i8] c" says meow!\00"
@.str.421 = private constant [6 x i8] c" has \00"
@.str.422 = private constant [12 x i8] c" lives left\00"
@.str.423 = private constant [14 x i8] c" directs the \00"
@.str.424 = private constant [12 x i8] c" department\00"
@.str.425 = private constant [22 x i8] c" is photosynthesizing\00"
@.str.426 = private constant [7 x i8] c" took \00"
@.str.427 = private constant [8 x i8] c" damage\00"
@.str.428 = private constant [8 x i8] c"Count: \00"
@.str.429 = private constant [11 x i8] c"This is a \00"
@.str.430 = private constant [8 x i8] c"Speed: \00"
@.str.431 = private constant [5 x i8] c" mph\00"
@.str.432 = private constant [2 x i8] c" \00"
@.str.433 = private constant [14 x i8] c" is blooming!\00"
@.str.434 = private constant [4 x i8] c"Car\00"
@.str.435 = private constant [20 x i8] c"This is a car with \00"
@.str.436 = private constant [7 x i8] c" doors\00"
@.str.437 = private constant [13 x i8] c"Base value: \00"
@.str.438 = private constant [14 x i8] c" is managing \00"
@.str.439 = private constant [8 x i8] c" people\00"
@.str.440 = private constant [9 x i8] c" is now \00"
@.str.441 = private constant [8 x i8] c"running\00"
@.str.442 = private constant [14 x i8] c"Robot started\00"
@.str.443 = private constant [8 x i8] c"stopped\00"
@.str.444 = private constant [14 x i8] c"Robot stopped\00"
@.str.445 = private constant [9 x i8] c"Status: \00"
@.str.446 = private constant [12 x i8] c"It's alive!\00"
@.str.447 = private constant [15 x i8] c"It's not alive\00"
@.str.448 = private constant [16 x i8] c"Derived value: \00"
@.str.449 = private constant [16 x i8] c" makes a sound!\00"
@.str.450 = private constant [5 x i8] c" is \00"
@.str.451 = private constant [11 x i8] c" years old\00"
@.str.452 = private constant [4 x i8] c"Dog\00"
@.str.453 = private constant [14 x i8] c" barks: Woof!\00"

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local i32 @qc_powi_i32(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i32 %0, ptr %4, align 4
  store i32 %1, ptr %5, align 4
  %7 = load i32, ptr %5, align 4
  %8 = icmp slt i32 %7, 0
  br i1 %8, label %9, label %10

9:                                                ; preds = %2
  store i32 0, ptr %3, align 4
  br label %30

10:                                               ; preds = %2
  store i32 1, ptr %6, align 4
  br label %11

11:                                               ; preds = %22, %10
  %12 = load i32, ptr %5, align 4
  %13 = icmp sgt i32 %12, 0
  br i1 %13, label %14, label %28

14:                                               ; preds = %11
  %15 = load i32, ptr %5, align 4
  %16 = and i32 %15, 1
  %17 = icmp ne i32 %16, 0
  br i1 %17, label %18, label %22

18:                                               ; preds = %14
  %19 = load i32, ptr %4, align 4
  %20 = load i32, ptr %6, align 4
  %21 = mul nsw i32 %20, %19
  store i32 %21, ptr %6, align 4
  br label %22

22:                                               ; preds = %18, %14
  %23 = load i32, ptr %4, align 4
  %24 = load i32, ptr %4, align 4
  %25 = mul nsw i32 %24, %23
  store i32 %25, ptr %4, align 4
  %26 = load i32, ptr %5, align 4
  %27 = ashr i32 %26, 1
  store i32 %27, ptr %5, align 4
  br label %11, !llvm.loop !6

28:                                               ; preds = %11
  %29 = load i32, ptr %6, align 4
  store i32 %29, ptr %3, align 4
  br label %30

30:                                               ; preds = %28, %9
  %31 = load i32, ptr %3, align 4
  ret i32 %31
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_string_concat(ptr noundef %0, ptr noundef %1) #0 {
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca i64, align 8
  %7 = alloca i64, align 8
  %8 = alloca ptr, align 8
  store ptr %0, ptr %4, align 8
  store ptr %1, ptr %5, align 8
  %9 = load ptr, ptr %4, align 8
  %10 = icmp ne ptr %9, null
  br i1 %10, label %12, label %11

11:                                               ; preds = %2
  store ptr @.str, ptr %4, align 8
  br label %12

12:                                               ; preds = %11, %2
  %13 = load ptr, ptr %5, align 8
  %14 = icmp ne ptr %13, null
  br i1 %14, label %16, label %15

15:                                               ; preds = %12
  store ptr @.str, ptr %5, align 8
  br label %16

16:                                               ; preds = %15, %12
  %17 = load ptr, ptr %4, align 8
  %18 = call i64 @strlen(ptr noundef %17) #9
  store i64 %18, ptr %6, align 8
  %19 = load ptr, ptr %5, align 8
  %20 = call i64 @strlen(ptr noundef %19) #9
  store i64 %20, ptr %7, align 8
  %21 = load i64, ptr %6, align 8
  %22 = load i64, ptr %7, align 8
  %23 = add i64 %21, %22
  %24 = add i64 %23, 1
  %25 = call noalias ptr @malloc(i64 noundef %24) #10
  store ptr %25, ptr %8, align 8
  %26 = load ptr, ptr %8, align 8
  %27 = icmp ne ptr %26, null
  br i1 %27, label %29, label %28

28:                                               ; preds = %16
  store ptr null, ptr %3, align 8
  br label %44

29:                                               ; preds = %16
  %30 = load ptr, ptr %8, align 8
  %31 = load ptr, ptr %4, align 8
  %32 = load i64, ptr %6, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %30, ptr align 1 %31, i64 %32, i1 false)
  %33 = load ptr, ptr %8, align 8
  %34 = load i64, ptr %6, align 8
  %35 = getelementptr inbounds i8, ptr %33, i64 %34
  %36 = load ptr, ptr %5, align 8
  %37 = load i64, ptr %7, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %35, ptr align 1 %36, i64 %37, i1 false)
  %38 = load ptr, ptr %8, align 8
  %39 = load i64, ptr %6, align 8
  %40 = load i64, ptr %7, align 8
  %41 = add i64 %39, %40
  %42 = getelementptr inbounds i8, ptr %38, i64 %41
  store i8 0, ptr %42, align 1
  %43 = load ptr, ptr %8, align 8
  store ptr %43, ptr %3, align 8
  br label %44

44:                                               ; preds = %29, %28
  %45 = load ptr, ptr %3, align 8
  ret ptr %45
}

; Function Attrs: nounwind willreturn memory(read)
declare i64 @strlen(ptr noundef) #1

; Function Attrs: nounwind allocsize(0)
declare noalias ptr @malloc(i64 noundef) #2

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #3

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local zeroext i1 @qc_string_eq(ptr noundef %0, ptr noundef %1) #0 {
  %3 = alloca i1, align 1
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  store ptr %0, ptr %4, align 8
  store ptr %1, ptr %5, align 8
  %6 = load ptr, ptr %4, align 8
  %7 = icmp ne ptr %6, null
  br i1 %7, label %8, label %11

8:                                                ; preds = %2
  %9 = load ptr, ptr %5, align 8
  %10 = icmp ne ptr %9, null
  br i1 %10, label %12, label %11

11:                                               ; preds = %8, %2
  store i1 false, ptr %3, align 1
  br label %20

12:                                               ; preds = %8
  %13 = load ptr, ptr %4, align 8
  %14 = load ptr, ptr %5, align 8
  %15 = call i32 @strcmp(ptr noundef %13, ptr noundef %14) #9
  %16 = icmp eq i32 %15, 0
  %17 = zext i1 %16 to i64
  %18 = select i1 %16, i32 1, i32 0
  %19 = icmp ne i32 %18, 0
  store i1 %19, ptr %3, align 1
  br label %20

20:                                               ; preds = %12, %11
  %21 = load i1, ptr %3, align 1
  ret i1 %21
}

; Function Attrs: nounwind willreturn memory(read)
declare i32 @strcmp(ptr noundef, ptr noundef) #1

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local zeroext i8 @qc_qand(i8 noundef zeroext %0, i8 noundef zeroext %1) #0 {
  %3 = alloca i8, align 1
  %4 = alloca i8, align 1
  %5 = alloca i8, align 1
  store i8 %0, ptr %4, align 1
  store i8 %1, ptr %5, align 1
  %6 = load i8, ptr %4, align 1
  %7 = zext i8 %6 to i32
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %21, label %9

9:                                                ; preds = %2
  %10 = load i8, ptr %4, align 1
  %11 = zext i8 %10 to i32
  %12 = icmp eq i32 %11, 1
  br i1 %12, label %21, label %13

13:                                               ; preds = %9
  %14 = load i8, ptr %5, align 1
  %15 = zext i8 %14 to i32
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %21, label %17

17:                                               ; preds = %13
  %18 = load i8, ptr %5, align 1
  %19 = zext i8 %18 to i32
  %20 = icmp eq i32 %19, 1
  br i1 %20, label %21, label %22

21:                                               ; preds = %17, %13, %9, %2
  store i8 1, ptr %3, align 1
  br label %50

22:                                               ; preds = %17
  %23 = load i8, ptr %4, align 1
  %24 = zext i8 %23 to i32
  %25 = icmp eq i32 %24, 2
  br i1 %25, label %26, label %31

26:                                               ; preds = %22
  %27 = load i8, ptr %5, align 1
  %28 = zext i8 %27 to i32
  %29 = icmp eq i32 %28, 2
  br i1 %29, label %30, label %31

30:                                               ; preds = %26
  store i8 2, ptr %3, align 1
  br label %50

31:                                               ; preds = %26, %22
  %32 = load i8, ptr %4, align 1
  %33 = zext i8 %32 to i32
  %34 = icmp eq i32 %33, 2
  br i1 %34, label %35, label %40

35:                                               ; preds = %31
  %36 = load i8, ptr %5, align 1
  %37 = zext i8 %36 to i32
  %38 = icmp eq i32 %37, 3
  br i1 %38, label %39, label %40

39:                                               ; preds = %35
  store i8 3, ptr %3, align 1
  br label %50

40:                                               ; preds = %35, %31
  %41 = load i8, ptr %4, align 1
  %42 = zext i8 %41 to i32
  %43 = icmp eq i32 %42, 3
  br i1 %43, label %44, label %49

44:                                               ; preds = %40
  %45 = load i8, ptr %5, align 1
  %46 = zext i8 %45 to i32
  %47 = icmp eq i32 %46, 2
  br i1 %47, label %48, label %49

48:                                               ; preds = %44
  store i8 3, ptr %3, align 1
  br label %50

49:                                               ; preds = %44, %40
  store i8 3, ptr %3, align 1
  br label %50

50:                                               ; preds = %49, %48, %39, %30, %21
  %51 = load i8, ptr %3, align 1
  ret i8 %51
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local zeroext i8 @qc_qor(i8 noundef zeroext %0, i8 noundef zeroext %1) #0 {
  %3 = alloca i8, align 1
  %4 = alloca i8, align 1
  %5 = alloca i8, align 1
  store i8 %0, ptr %4, align 1
  store i8 %1, ptr %5, align 1
  %6 = load i8, ptr %4, align 1
  %7 = zext i8 %6 to i32
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %9, label %14

9:                                                ; preds = %2
  %10 = load i8, ptr %5, align 1
  %11 = zext i8 %10 to i32
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %13, label %14

13:                                               ; preds = %9
  store i8 0, ptr %3, align 1
  br label %69

14:                                               ; preds = %9, %2
  %15 = load i8, ptr %4, align 1
  %16 = zext i8 %15 to i32
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %18, label %23

18:                                               ; preds = %14
  %19 = load i8, ptr %5, align 1
  %20 = zext i8 %19 to i32
  %21 = icmp eq i32 %20, 1
  br i1 %21, label %22, label %23

22:                                               ; preds = %18
  store i8 1, ptr %3, align 1
  br label %69

23:                                               ; preds = %18, %14
  %24 = load i8, ptr %4, align 1
  %25 = zext i8 %24 to i32
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %27, label %32

27:                                               ; preds = %23
  %28 = load i8, ptr %5, align 1
  %29 = zext i8 %28 to i32
  %30 = icmp eq i32 %29, 2
  br i1 %30, label %31, label %32

31:                                               ; preds = %27
  store i8 2, ptr %3, align 1
  br label %69

32:                                               ; preds = %27, %23
  %33 = load i8, ptr %4, align 1
  %34 = zext i8 %33 to i32
  %35 = icmp eq i32 %34, 1
  br i1 %35, label %36, label %41

36:                                               ; preds = %32
  %37 = load i8, ptr %5, align 1
  %38 = zext i8 %37 to i32
  %39 = icmp eq i32 %38, 0
  br i1 %39, label %40, label %41

40:                                               ; preds = %36
  store i8 1, ptr %3, align 1
  br label %69

41:                                               ; preds = %36, %32
  %42 = load i8, ptr %4, align 1
  %43 = zext i8 %42 to i32
  %44 = icmp eq i32 %43, 1
  br i1 %44, label %45, label %50

45:                                               ; preds = %41
  %46 = load i8, ptr %5, align 1
  %47 = zext i8 %46 to i32
  %48 = icmp eq i32 %47, 1
  br i1 %48, label %49, label %50

49:                                               ; preds = %45
  store i8 1, ptr %3, align 1
  br label %69

50:                                               ; preds = %45, %41
  %51 = load i8, ptr %4, align 1
  %52 = zext i8 %51 to i32
  %53 = icmp eq i32 %52, 2
  br i1 %53, label %54, label %59

54:                                               ; preds = %50
  %55 = load i8, ptr %5, align 1
  %56 = zext i8 %55 to i32
  %57 = icmp eq i32 %56, 0
  br i1 %57, label %58, label %59

58:                                               ; preds = %54
  store i8 2, ptr %3, align 1
  br label %69

59:                                               ; preds = %54, %50
  %60 = load i8, ptr %4, align 1
  %61 = zext i8 %60 to i32
  %62 = icmp eq i32 %61, 2
  br i1 %62, label %63, label %68

63:                                               ; preds = %59
  %64 = load i8, ptr %5, align 1
  %65 = zext i8 %64 to i32
  %66 = icmp eq i32 %65, 2
  br i1 %66, label %67, label %68

67:                                               ; preds = %63
  store i8 2, ptr %3, align 1
  br label %69

68:                                               ; preds = %63, %59
  store i8 3, ptr %3, align 1
  br label %69

69:                                               ; preds = %68, %67, %58, %49, %40, %31, %22, %13
  %70 = load i8, ptr %3, align 1
  ret i8 %70
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local zeroext i8 @qc_qxor(i8 noundef zeroext %0, i8 noundef zeroext %1) #0 {
  %3 = alloca i8, align 1
  %4 = alloca i8, align 1
  %5 = alloca i8, align 1
  store i8 %0, ptr %4, align 1
  store i8 %1, ptr %5, align 1
  %6 = load i8, ptr %4, align 1
  %7 = zext i8 %6 to i32
  %8 = icmp sle i32 %7, 1
  br i1 %8, label %9, label %14

9:                                                ; preds = %2
  %10 = load i8, ptr %5, align 1
  %11 = zext i8 %10 to i32
  %12 = icmp sle i32 %11, 1
  br i1 %12, label %13, label %14

13:                                               ; preds = %9
  store i8 0, ptr %3, align 1
  br label %42

14:                                               ; preds = %9, %2
  %15 = load i8, ptr %4, align 1
  %16 = zext i8 %15 to i32
  %17 = icmp sle i32 %16, 1
  br i1 %17, label %18, label %23

18:                                               ; preds = %14
  %19 = load i8, ptr %5, align 1
  %20 = zext i8 %19 to i32
  %21 = icmp sge i32 %20, 2
  br i1 %21, label %22, label %23

22:                                               ; preds = %18
  store i8 3, ptr %3, align 1
  br label %42

23:                                               ; preds = %18, %14
  %24 = load i8, ptr %4, align 1
  %25 = zext i8 %24 to i32
  %26 = icmp sge i32 %25, 2
  br i1 %26, label %27, label %32

27:                                               ; preds = %23
  %28 = load i8, ptr %5, align 1
  %29 = zext i8 %28 to i32
  %30 = icmp sle i32 %29, 1
  br i1 %30, label %31, label %32

31:                                               ; preds = %27
  store i8 3, ptr %3, align 1
  br label %42

32:                                               ; preds = %27, %23
  %33 = load i8, ptr %4, align 1
  %34 = zext i8 %33 to i32
  %35 = icmp eq i32 %34, 2
  br i1 %35, label %36, label %41

36:                                               ; preds = %32
  %37 = load i8, ptr %5, align 1
  %38 = zext i8 %37 to i32
  %39 = icmp eq i32 %38, 2
  br i1 %39, label %40, label %41

40:                                               ; preds = %36
  store i8 1, ptr %3, align 1
  br label %42

41:                                               ; preds = %36, %32
  store i8 3, ptr %3, align 1
  br label %42

42:                                               ; preds = %41, %40, %31, %22, %13
  %43 = load i8, ptr %3, align 1
  ret i8 %43
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local zeroext i8 @qc_qnot(i8 noundef zeroext %0) #0 {
  %2 = alloca i8, align 1
  store i8 %0, ptr %2, align 1
  %3 = load i8, ptr %2, align 1
  %4 = zext i8 %3 to i32
  %5 = sub nsw i32 3, %4
  %6 = trunc i32 %5 to i8
  ret i8 %6
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local zeroext i1 @qc_qand_collapse(i8 noundef zeroext %0, i8 noundef zeroext %1) #0 {
  %3 = alloca i8, align 1
  %4 = alloca i8, align 1
  store i8 %0, ptr %3, align 1
  store i8 %1, ptr %4, align 1
  %5 = load i8, ptr %3, align 1
  %6 = zext i8 %5 to i32
  %7 = and i32 %6, 2
  %8 = icmp ne i32 %7, 0
  br i1 %8, label %9, label %14

9:                                                ; preds = %2
  %10 = load i8, ptr %4, align 1
  %11 = zext i8 %10 to i32
  %12 = and i32 %11, 2
  %13 = icmp ne i32 %12, 0
  br label %14

14:                                               ; preds = %9, %2
  %15 = phi i1 [ false, %2 ], [ %13, %9 ]
  ret i1 %15
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local zeroext i1 @qc_qor_collapse(i8 noundef zeroext %0, i8 noundef zeroext %1) #0 {
  %3 = alloca i8, align 1
  %4 = alloca i8, align 1
  store i8 %0, ptr %3, align 1
  store i8 %1, ptr %4, align 1
  %5 = load i8, ptr %3, align 1
  %6 = zext i8 %5 to i32
  %7 = and i32 %6, 2
  %8 = icmp ne i32 %7, 0
  br i1 %8, label %14, label %9

9:                                                ; preds = %2
  %10 = load i8, ptr %4, align 1
  %11 = zext i8 %10 to i32
  %12 = and i32 %11, 2
  %13 = icmp ne i32 %12, 0
  br label %14

14:                                               ; preds = %9, %2
  %15 = phi i1 [ true, %2 ], [ %13, %9 ]
  ret i1 %15
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_to_string_int(i32 noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  %4 = alloca [32 x i8], align 16
  %5 = alloca i32, align 4
  %6 = alloca ptr, align 8
  store i32 %0, ptr %3, align 4
  %7 = getelementptr inbounds [32 x i8], ptr %4, i64 0, i64 0
  %8 = load i32, ptr %3, align 4
  %9 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %7, i64 noundef 32, ptr noundef @.str.1, i32 noundef %8) #11
  store i32 %9, ptr %5, align 4
  %10 = load i32, ptr %5, align 4
  %11 = icmp slt i32 %10, 0
  br i1 %11, label %12, label %13

12:                                               ; preds = %1
  store ptr null, ptr %2, align 8
  br label %28

13:                                               ; preds = %1
  %14 = load i32, ptr %5, align 4
  %15 = add nsw i32 %14, 1
  %16 = sext i32 %15 to i64
  %17 = call noalias ptr @malloc(i64 noundef %16) #10
  store ptr %17, ptr %6, align 8
  %18 = load ptr, ptr %6, align 8
  %19 = icmp ne ptr %18, null
  br i1 %19, label %21, label %20

20:                                               ; preds = %13
  store ptr null, ptr %2, align 8
  br label %28

21:                                               ; preds = %13
  %22 = load ptr, ptr %6, align 8
  %23 = getelementptr inbounds [32 x i8], ptr %4, i64 0, i64 0
  %24 = load i32, ptr %5, align 4
  %25 = add nsw i32 %24, 1
  %26 = sext i32 %25 to i64
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %22, ptr align 16 %23, i64 %26, i1 false)
  %27 = load ptr, ptr %6, align 8
  store ptr %27, ptr %2, align 8
  br label %28

28:                                               ; preds = %21, %20, %12
  %29 = load ptr, ptr %2, align 8
  ret ptr %29
}

; Function Attrs: nounwind
declare i32 @snprintf(ptr noundef, i64 noundef, ptr noundef, ...) #4

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_to_string_float(float noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca float, align 4
  %4 = alloca [64 x i8], align 16
  %5 = alloca i32, align 4
  %6 = alloca ptr, align 8
  store float %0, ptr %3, align 4
  %7 = getelementptr inbounds [64 x i8], ptr %4, i64 0, i64 0
  %8 = load float, ptr %3, align 4
  %9 = fpext float %8 to double
  %10 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %7, i64 noundef 64, ptr noundef @.str.2, double noundef %9) #11
  store i32 %10, ptr %5, align 4
  %11 = load i32, ptr %5, align 4
  %12 = icmp slt i32 %11, 0
  br i1 %12, label %13, label %14

13:                                               ; preds = %1
  store ptr null, ptr %2, align 8
  br label %29

14:                                               ; preds = %1
  %15 = load i32, ptr %5, align 4
  %16 = add nsw i32 %15, 1
  %17 = sext i32 %16 to i64
  %18 = call noalias ptr @malloc(i64 noundef %17) #10
  store ptr %18, ptr %6, align 8
  %19 = load ptr, ptr %6, align 8
  %20 = icmp ne ptr %19, null
  br i1 %20, label %22, label %21

21:                                               ; preds = %14
  store ptr null, ptr %2, align 8
  br label %29

22:                                               ; preds = %14
  %23 = load ptr, ptr %6, align 8
  %24 = getelementptr inbounds [64 x i8], ptr %4, i64 0, i64 0
  %25 = load i32, ptr %5, align 4
  %26 = add nsw i32 %25, 1
  %27 = sext i32 %26 to i64
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %23, ptr align 16 %24, i64 %27, i1 false)
  %28 = load ptr, ptr %6, align 8
  store ptr %28, ptr %2, align 8
  br label %29

29:                                               ; preds = %22, %21, %13
  %30 = load ptr, ptr %2, align 8
  ret ptr %30
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local i32 @qc_to_int_from_float(float noundef %0) #0 {
  %2 = alloca float, align 4
  store float %0, ptr %2, align 4
  %3 = load float, ptr %2, align 4
  %4 = fptosi float %3 to i32
  ret i32 %4
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local i32 @qc_to_int_from_double(double noundef %0) #0 {
  %2 = alloca double, align 8
  store double %0, ptr %2, align 8
  %3 = load double, ptr %2, align 8
  %4 = fptosi double %3 to i32
  ret i32 %4
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local i32 @qc_to_int_from_char(i8 noundef signext %0) #0 {
  %2 = alloca i8, align 1
  store i8 %0, ptr %2, align 1
  %3 = load i8, ptr %2, align 1
  %4 = sext i8 %3 to i32
  ret i32 %4
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local float @qc_to_float_from_double(double noundef %0) #0 {
  %2 = alloca double, align 8
  store double %0, ptr %2, align 8
  %3 = load double, ptr %2, align 8
  %4 = fptrunc double %3 to float
  ret float %4
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local float @qc_to_float_from_bool(i1 noundef zeroext %0) #0 {
  %2 = alloca i8, align 1
  %3 = zext i1 %0 to i8
  store i8 %3, ptr %2, align 1
  %4 = load i8, ptr %2, align 1
  %5 = trunc i8 %4 to i1
  %6 = zext i1 %5 to i64
  %7 = select i1 %5, float 1.000000e+00, float 0.000000e+00
  ret float %7
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local double @qc_to_double_from_float(float noundef %0) #0 {
  %2 = alloca float, align 4
  store float %0, ptr %2, align 4
  %3 = load float, ptr %2, align 4
  %4 = fpext float %3 to double
  ret double %4
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local double @qc_to_double_from_bool(i1 noundef zeroext %0) #0 {
  %2 = alloca i8, align 1
  %3 = zext i1 %0 to i8
  store i8 %3, ptr %2, align 1
  %4 = load i8, ptr %2, align 1
  %5 = trunc i8 %4 to i1
  %6 = zext i1 %5 to i64
  %7 = select i1 %5, double 1.000000e+00, double 0.000000e+00
  ret double %7
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local zeroext i1 @qc_to_bool_from_int(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  %3 = load i32, ptr %2, align 4
  %4 = icmp ne i32 %3, 0
  ret i1 %4
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local zeroext i1 @qc_to_bool_from_float(float noundef %0) #0 {
  %2 = alloca float, align 4
  store float %0, ptr %2, align 4
  %3 = load float, ptr %2, align 4
  %4 = fcmp une float %3, 0.000000e+00
  ret i1 %4
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local zeroext i1 @qc_to_bool_from_double(double noundef %0) #0 {
  %2 = alloca double, align 8
  store double %0, ptr %2, align 8
  %3 = load double, ptr %2, align 8
  %4 = fcmp une double %3, 0.000000e+00
  ret i1 %4
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local signext i8 @qc_to_char_from_int(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  %3 = load i32, ptr %2, align 4
  %4 = trunc i32 %3 to i8
  ret i8 %4
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_to_string_double(double noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca double, align 8
  %4 = alloca [64 x i8], align 16
  %5 = alloca i32, align 4
  %6 = alloca ptr, align 8
  store double %0, ptr %3, align 8
  %7 = getelementptr inbounds [64 x i8], ptr %4, i64 0, i64 0
  %8 = load double, ptr %3, align 8
  %9 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %7, i64 noundef 64, ptr noundef @.str.2, double noundef %8) #11
  store i32 %9, ptr %5, align 4
  %10 = load i32, ptr %5, align 4
  %11 = icmp slt i32 %10, 0
  br i1 %11, label %12, label %13

12:                                               ; preds = %1
  store ptr null, ptr %2, align 8
  br label %28

13:                                               ; preds = %1
  %14 = load i32, ptr %5, align 4
  %15 = add nsw i32 %14, 1
  %16 = sext i32 %15 to i64
  %17 = call noalias ptr @malloc(i64 noundef %16) #10
  store ptr %17, ptr %6, align 8
  %18 = load ptr, ptr %6, align 8
  %19 = icmp ne ptr %18, null
  br i1 %19, label %21, label %20

20:                                               ; preds = %13
  store ptr null, ptr %2, align 8
  br label %28

21:                                               ; preds = %13
  %22 = load ptr, ptr %6, align 8
  %23 = getelementptr inbounds [64 x i8], ptr %4, i64 0, i64 0
  %24 = load i32, ptr %5, align 4
  %25 = add nsw i32 %24, 1
  %26 = sext i32 %25 to i64
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %22, ptr align 16 %23, i64 %26, i1 false)
  %27 = load ptr, ptr %6, align 8
  store ptr %27, ptr %2, align 8
  br label %28

28:                                               ; preds = %21, %20, %12
  %29 = load ptr, ptr %2, align 8
  ret ptr %29
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_to_string_bool(i1 noundef zeroext %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca i8, align 1
  %4 = alloca ptr, align 8
  %5 = alloca i64, align 8
  %6 = alloca ptr, align 8
  %7 = zext i1 %0 to i8
  store i8 %7, ptr %3, align 1
  %8 = load i8, ptr %3, align 1
  %9 = trunc i8 %8 to i1
  %10 = zext i1 %9 to i64
  %11 = select i1 %9, ptr @.str.3, ptr @.str.4
  store ptr %11, ptr %4, align 8
  %12 = load ptr, ptr %4, align 8
  %13 = call i64 @strlen(ptr noundef %12) #9
  store i64 %13, ptr %5, align 8
  %14 = load i64, ptr %5, align 8
  %15 = add i64 %14, 1
  %16 = call noalias ptr @malloc(i64 noundef %15) #10
  store ptr %16, ptr %6, align 8
  %17 = load ptr, ptr %6, align 8
  %18 = icmp ne ptr %17, null
  br i1 %18, label %20, label %19

19:                                               ; preds = %1
  store ptr null, ptr %2, align 8
  br label %26

20:                                               ; preds = %1
  %21 = load ptr, ptr %6, align 8
  %22 = load ptr, ptr %4, align 8
  %23 = load i64, ptr %5, align 8
  %24 = add i64 %23, 1
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %21, ptr align 1 %22, i64 %24, i1 false)
  %25 = load ptr, ptr %6, align 8
  store ptr %25, ptr %2, align 8
  br label %26

26:                                               ; preds = %20, %19
  %27 = load ptr, ptr %2, align 8
  ret ptr %27
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_to_string_qbool(i8 noundef zeroext %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca i8, align 1
  %4 = alloca ptr, align 8
  %5 = alloca i64, align 8
  %6 = alloca ptr, align 8
  store i8 %0, ptr %3, align 1
  %7 = load i8, ptr %3, align 1
  %8 = zext i8 %7 to i32
  %9 = and i32 %8, 3
  switch i32 %9, label %14 [
    i32 0, label %10
    i32 1, label %11
    i32 2, label %12
    i32 3, label %13
  ]

10:                                               ; preds = %1
  store ptr @.str.5, ptr %4, align 8
  br label %15

11:                                               ; preds = %1
  store ptr @.str.6, ptr %4, align 8
  br label %15

12:                                               ; preds = %1
  store ptr @.str.7, ptr %4, align 8
  br label %15

13:                                               ; preds = %1
  store ptr @.str.8, ptr %4, align 8
  br label %15

14:                                               ; preds = %1
  store ptr @.str.5, ptr %4, align 8
  br label %15

15:                                               ; preds = %14, %13, %12, %11, %10
  %16 = load ptr, ptr %4, align 8
  %17 = call i64 @strlen(ptr noundef %16) #9
  store i64 %17, ptr %5, align 8
  %18 = load i64, ptr %5, align 8
  %19 = add i64 %18, 1
  %20 = call noalias ptr @malloc(i64 noundef %19) #10
  store ptr %20, ptr %6, align 8
  %21 = load ptr, ptr %6, align 8
  %22 = icmp ne ptr %21, null
  br i1 %22, label %24, label %23

23:                                               ; preds = %15
  store ptr null, ptr %2, align 8
  br label %30

24:                                               ; preds = %15
  %25 = load ptr, ptr %6, align 8
  %26 = load ptr, ptr %4, align 8
  %27 = load i64, ptr %5, align 8
  %28 = add i64 %27, 1
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %25, ptr align 1 %26, i64 %28, i1 false)
  %29 = load ptr, ptr %6, align 8
  store ptr %29, ptr %2, align 8
  br label %30

30:                                               ; preds = %24, %23
  %31 = load ptr, ptr %2, align 8
  ret ptr %31
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_to_string_char(i8 noundef signext %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca i8, align 1
  %4 = alloca ptr, align 8
  store i8 %0, ptr %3, align 1
  %5 = call noalias ptr @malloc(i64 noundef 2) #10
  store ptr %5, ptr %4, align 8
  %6 = load ptr, ptr %4, align 8
  %7 = icmp ne ptr %6, null
  br i1 %7, label %9, label %8

8:                                                ; preds = %1
  store ptr null, ptr %2, align 8
  br label %16

9:                                                ; preds = %1
  %10 = load i8, ptr %3, align 1
  %11 = load ptr, ptr %4, align 8
  %12 = getelementptr inbounds i8, ptr %11, i64 0
  store i8 %10, ptr %12, align 1
  %13 = load ptr, ptr %4, align 8
  %14 = getelementptr inbounds i8, ptr %13, i64 1
  store i8 0, ptr %14, align 1
  %15 = load ptr, ptr %4, align 8
  store ptr %15, ptr %2, align 8
  br label %16

16:                                               ; preds = %9, %8
  %17 = load ptr, ptr %2, align 8
  ret ptr %17
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print_string(ptr noundef %0) #5 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = icmp ne ptr %3, null
  br i1 %4, label %6, label %5

5:                                                ; preds = %1
  store ptr @.str, ptr %2, align 8
  br label %6

6:                                                ; preds = %5, %1
  %7 = load ptr, ptr %2, align 8
  %8 = load ptr, ptr @stdout, align 8
  %9 = call i32 @fputs(ptr noundef %7, ptr noundef %8)
  ret void
}

declare i32 @fputs(ptr noundef, ptr noundef) #6

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print_int(i32 noundef %0) #5 {
  %2 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  %3 = load i32, ptr %2, align 4
  %4 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %3)
  ret void
}

declare i32 @printf(ptr noundef, ...) #6

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print_double(double noundef %0) #5 {
  %2 = alloca double, align 8
  store double %0, ptr %2, align 8
  %3 = load double, ptr %2, align 8
  %4 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, double noundef %3)
  ret void
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print_char(i8 noundef signext %0) #5 {
  %2 = alloca i8, align 1
  store i8 %0, ptr %2, align 1
  %3 = load i8, ptr %2, align 1
  %4 = zext i8 %3 to i32
  %5 = call i32 @putchar(i32 noundef %4)
  ret void
}

declare i32 @putchar(i32 noundef) #6

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local i32 @qc_time() #0 {
  %1 = call i64 @time(ptr noundef null) #11
  %2 = trunc i64 %1 to i32
  ret i32 %2
}

; Function Attrs: nounwind
declare i64 @time(ptr noundef) #4

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local void @qc_seed(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  %3 = load i32, ptr %2, align 4
  call void @srand(i32 noundef %3) #11
  ret void
}

; Function Attrs: nounwind
declare void @srand(i32 noundef) #4

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local float @qc_random_float() #0 {
  %1 = call i32 @rand() #11
  %2 = sitofp i32 %1 to float
  %3 = fdiv float %2, 0x41E0000000000000
  ret float %3
}

; Function Attrs: nounwind
declare i32 @rand() #4

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local i32 @qc_random_int(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  %3 = call i32 @rand() #11
  %4 = load i32, ptr %2, align 4
  %5 = srem i32 %3, %4
  ret i32 %5
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local i32 @qc_random_range(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %4, align 4
  %5 = load i32, ptr %3, align 4
  %6 = call i32 @rand() #11
  %7 = load i32, ptr %4, align 4
  %8 = load i32, ptr %3, align 4
  %9 = sub nsw i32 %7, %8
  %10 = srem i32 %6, %9
  %11 = add nsw i32 %5, %10
  ret i32 %11
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local i32 @qc_len(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = call i64 @strlen(ptr noundef %3) #9
  %5 = trunc i64 %4 to i32
  ret i32 %5
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_to_lower(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca ptr, align 8
  %4 = alloca i64, align 8
  %5 = alloca ptr, align 8
  %6 = alloca i64, align 8
  store ptr %0, ptr %3, align 8
  %7 = load ptr, ptr %3, align 8
  %8 = icmp ne ptr %7, null
  br i1 %8, label %10, label %9

9:                                                ; preds = %1
  store ptr null, ptr %2, align 8
  br label %43

10:                                               ; preds = %1
  %11 = load ptr, ptr %3, align 8
  %12 = call i64 @strlen(ptr noundef %11) #9
  store i64 %12, ptr %4, align 8
  %13 = load i64, ptr %4, align 8
  %14 = add i64 %13, 1
  %15 = call noalias ptr @malloc(i64 noundef %14) #10
  store ptr %15, ptr %5, align 8
  %16 = load ptr, ptr %5, align 8
  %17 = icmp ne ptr %16, null
  br i1 %17, label %19, label %18

18:                                               ; preds = %10
  store ptr null, ptr %2, align 8
  br label %43

19:                                               ; preds = %10
  store i64 0, ptr %6, align 8
  br label %20

20:                                               ; preds = %35, %19
  %21 = load i64, ptr %6, align 8
  %22 = load i64, ptr %4, align 8
  %23 = icmp ult i64 %21, %22
  br i1 %23, label %24, label %38

24:                                               ; preds = %20
  %25 = load ptr, ptr %3, align 8
  %26 = load i64, ptr %6, align 8
  %27 = getelementptr inbounds i8, ptr %25, i64 %26
  %28 = load i8, ptr %27, align 1
  %29 = zext i8 %28 to i32
  %30 = call i32 @tolower(i32 noundef %29) #9
  %31 = trunc i32 %30 to i8
  %32 = load ptr, ptr %5, align 8
  %33 = load i64, ptr %6, align 8
  %34 = getelementptr inbounds i8, ptr %32, i64 %33
  store i8 %31, ptr %34, align 1
  br label %35

35:                                               ; preds = %24
  %36 = load i64, ptr %6, align 8
  %37 = add i64 %36, 1
  store i64 %37, ptr %6, align 8
  br label %20, !llvm.loop !8

38:                                               ; preds = %20
  %39 = load ptr, ptr %5, align 8
  %40 = load i64, ptr %4, align 8
  %41 = getelementptr inbounds i8, ptr %39, i64 %40
  store i8 0, ptr %41, align 1
  %42 = load ptr, ptr %5, align 8
  store ptr %42, ptr %2, align 8
  br label %43

43:                                               ; preds = %38, %18, %9
  %44 = load ptr, ptr %2, align 8
  ret ptr %44
}

; Function Attrs: nounwind willreturn memory(read)
declare i32 @tolower(i32 noundef) #1

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_to_upper(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca ptr, align 8
  %4 = alloca i64, align 8
  %5 = alloca ptr, align 8
  %6 = alloca i64, align 8
  store ptr %0, ptr %3, align 8
  %7 = load ptr, ptr %3, align 8
  %8 = icmp ne ptr %7, null
  br i1 %8, label %10, label %9

9:                                                ; preds = %1
  store ptr null, ptr %2, align 8
  br label %43

10:                                               ; preds = %1
  %11 = load ptr, ptr %3, align 8
  %12 = call i64 @strlen(ptr noundef %11) #9
  store i64 %12, ptr %4, align 8
  %13 = load i64, ptr %4, align 8
  %14 = add i64 %13, 1
  %15 = call noalias ptr @malloc(i64 noundef %14) #10
  store ptr %15, ptr %5, align 8
  %16 = load ptr, ptr %5, align 8
  %17 = icmp ne ptr %16, null
  br i1 %17, label %19, label %18

18:                                               ; preds = %10
  store ptr null, ptr %2, align 8
  br label %43

19:                                               ; preds = %10
  store i64 0, ptr %6, align 8
  br label %20

20:                                               ; preds = %35, %19
  %21 = load i64, ptr %6, align 8
  %22 = load i64, ptr %4, align 8
  %23 = icmp ult i64 %21, %22
  br i1 %23, label %24, label %38

24:                                               ; preds = %20
  %25 = load ptr, ptr %3, align 8
  %26 = load i64, ptr %6, align 8
  %27 = getelementptr inbounds i8, ptr %25, i64 %26
  %28 = load i8, ptr %27, align 1
  %29 = zext i8 %28 to i32
  %30 = call i32 @toupper(i32 noundef %29) #9
  %31 = trunc i32 %30 to i8
  %32 = load ptr, ptr %5, align 8
  %33 = load i64, ptr %6, align 8
  %34 = getelementptr inbounds i8, ptr %32, i64 %33
  store i8 %31, ptr %34, align 1
  br label %35

35:                                               ; preds = %24
  %36 = load i64, ptr %6, align 8
  %37 = add i64 %36, 1
  store i64 %37, ptr %6, align 8
  br label %20, !llvm.loop !9

38:                                               ; preds = %20
  %39 = load ptr, ptr %5, align 8
  %40 = load i64, ptr %4, align 8
  %41 = getelementptr inbounds i8, ptr %39, i64 %40
  store i8 0, ptr %41, align 1
  %42 = load ptr, ptr %5, align 8
  store ptr %42, ptr %2, align 8
  br label %43

43:                                               ; preds = %38, %18, %9
  %44 = load ptr, ptr %2, align 8
  ret ptr %44
}

; Function Attrs: nounwind willreturn memory(read)
declare i32 @toupper(i32 noundef) #1

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_substring(ptr noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca ptr, align 8
  %10 = alloca ptr, align 8
  store ptr %0, ptr %5, align 8
  store i32 %1, ptr %6, align 4
  store i32 %2, ptr %7, align 4
  %11 = load ptr, ptr %5, align 8
  %12 = icmp ne ptr %11, null
  br i1 %12, label %14, label %13

13:                                               ; preds = %3
  store ptr null, ptr %4, align 8
  br label %63

14:                                               ; preds = %3
  %15 = load ptr, ptr %5, align 8
  %16 = call i64 @strlen(ptr noundef %15) #9
  %17 = trunc i64 %16 to i32
  store i32 %17, ptr %8, align 4
  %18 = load i32, ptr %6, align 4
  %19 = icmp slt i32 %18, 0
  br i1 %19, label %27, label %20

20:                                               ; preds = %14
  %21 = load i32, ptr %6, align 4
  %22 = load i32, ptr %8, align 4
  %23 = icmp sge i32 %21, %22
  br i1 %23, label %27, label %24

24:                                               ; preds = %20
  %25 = load i32, ptr %7, align 4
  %26 = icmp sle i32 %25, 0
  br i1 %26, label %27, label %32

27:                                               ; preds = %24, %20, %14
  %28 = call noalias ptr @malloc(i64 noundef 1) #10
  store ptr %28, ptr %9, align 8
  %29 = load ptr, ptr %9, align 8
  %30 = getelementptr inbounds i8, ptr %29, i64 0
  store i8 0, ptr %30, align 1
  %31 = load ptr, ptr %9, align 8
  store ptr %31, ptr %4, align 8
  br label %63

32:                                               ; preds = %24
  %33 = load i32, ptr %6, align 4
  %34 = load i32, ptr %7, align 4
  %35 = add nsw i32 %33, %34
  %36 = load i32, ptr %8, align 4
  %37 = icmp sgt i32 %35, %36
  br i1 %37, label %38, label %42

38:                                               ; preds = %32
  %39 = load i32, ptr %8, align 4
  %40 = load i32, ptr %6, align 4
  %41 = sub nsw i32 %39, %40
  store i32 %41, ptr %7, align 4
  br label %42

42:                                               ; preds = %38, %32
  %43 = load i32, ptr %7, align 4
  %44 = add nsw i32 %43, 1
  %45 = sext i32 %44 to i64
  %46 = call noalias ptr @malloc(i64 noundef %45) #10
  store ptr %46, ptr %10, align 8
  %47 = load ptr, ptr %10, align 8
  %48 = icmp ne ptr %47, null
  br i1 %48, label %50, label %49

49:                                               ; preds = %42
  store ptr null, ptr %4, align 8
  br label %63

50:                                               ; preds = %42
  %51 = load ptr, ptr %10, align 8
  %52 = load ptr, ptr %5, align 8
  %53 = load i32, ptr %6, align 4
  %54 = sext i32 %53 to i64
  %55 = getelementptr inbounds i8, ptr %52, i64 %54
  %56 = load i32, ptr %7, align 4
  %57 = sext i32 %56 to i64
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %51, ptr align 1 %55, i64 %57, i1 false)
  %58 = load ptr, ptr %10, align 8
  %59 = load i32, ptr %7, align 4
  %60 = sext i32 %59 to i64
  %61 = getelementptr inbounds i8, ptr %58, i64 %60
  store i8 0, ptr %61, align 1
  %62 = load ptr, ptr %10, align 8
  store ptr %62, ptr %4, align 8
  br label %63

63:                                               ; preds = %50, %49, %27, %13
  %64 = load ptr, ptr %4, align 8
  ret ptr %64
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local i32 @qc_contains(ptr noundef %0, ptr noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  store ptr %0, ptr %4, align 8
  store ptr %1, ptr %5, align 8
  %6 = load ptr, ptr %4, align 8
  %7 = icmp ne ptr %6, null
  br i1 %7, label %8, label %11

8:                                                ; preds = %2
  %9 = load ptr, ptr %5, align 8
  %10 = icmp ne ptr %9, null
  br i1 %10, label %12, label %11

11:                                               ; preds = %8, %2
  store i32 0, ptr %3, align 4
  br label %19

12:                                               ; preds = %8
  %13 = load ptr, ptr %4, align 8
  %14 = load ptr, ptr %5, align 8
  %15 = call noundef ptr @strstr(ptr noundef %13, ptr noundef %14) #9
  %16 = icmp ne ptr %15, null
  %17 = zext i1 %16 to i64
  %18 = select i1 %16, i32 1, i32 0
  store i32 %18, ptr %3, align 4
  br label %19

19:                                               ; preds = %12, %11
  %20 = load i32, ptr %3, align 4
  ret i32 %20
}

; Function Attrs: nounwind willreturn memory(read)
declare noundef ptr @strstr(ptr noundef, ptr noundef) #1

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local i32 @qc_startswith(ptr noundef %0, ptr noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  store ptr %0, ptr %4, align 8
  store ptr %1, ptr %5, align 8
  %6 = load ptr, ptr %4, align 8
  %7 = icmp ne ptr %6, null
  br i1 %7, label %8, label %11

8:                                                ; preds = %2
  %9 = load ptr, ptr %5, align 8
  %10 = icmp ne ptr %9, null
  br i1 %10, label %12, label %11

11:                                               ; preds = %8, %2
  store i32 0, ptr %3, align 4
  br label %21

12:                                               ; preds = %8
  %13 = load ptr, ptr %4, align 8
  %14 = load ptr, ptr %5, align 8
  %15 = load ptr, ptr %5, align 8
  %16 = call i64 @strlen(ptr noundef %15) #9
  %17 = call i32 @strncmp(ptr noundef %13, ptr noundef %14, i64 noundef %16) #9
  %18 = icmp eq i32 %17, 0
  %19 = zext i1 %18 to i64
  %20 = select i1 %18, i32 1, i32 0
  store i32 %20, ptr %3, align 4
  br label %21

21:                                               ; preds = %12, %11
  %22 = load i32, ptr %3, align 4
  ret i32 %22
}

; Function Attrs: nounwind willreturn memory(read)
declare i32 @strncmp(ptr noundef, ptr noundef, i64 noundef) #1

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local i32 @qc_endswith(ptr noundef %0, ptr noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca i64, align 8
  %7 = alloca i64, align 8
  store ptr %0, ptr %4, align 8
  store ptr %1, ptr %5, align 8
  %8 = load ptr, ptr %4, align 8
  %9 = icmp ne ptr %8, null
  br i1 %9, label %10, label %13

10:                                               ; preds = %2
  %11 = load ptr, ptr %5, align 8
  %12 = icmp ne ptr %11, null
  br i1 %12, label %14, label %13

13:                                               ; preds = %10, %2
  store i32 0, ptr %3, align 4
  br label %35

14:                                               ; preds = %10
  %15 = load ptr, ptr %4, align 8
  %16 = call i64 @strlen(ptr noundef %15) #9
  store i64 %16, ptr %6, align 8
  %17 = load ptr, ptr %5, align 8
  %18 = call i64 @strlen(ptr noundef %17) #9
  store i64 %18, ptr %7, align 8
  %19 = load i64, ptr %7, align 8
  %20 = load i64, ptr %6, align 8
  %21 = icmp ugt i64 %19, %20
  br i1 %21, label %22, label %23

22:                                               ; preds = %14
  store i32 0, ptr %3, align 4
  br label %35

23:                                               ; preds = %14
  %24 = load ptr, ptr %4, align 8
  %25 = load i64, ptr %6, align 8
  %26 = getelementptr inbounds i8, ptr %24, i64 %25
  %27 = load i64, ptr %7, align 8
  %28 = sub i64 0, %27
  %29 = getelementptr inbounds i8, ptr %26, i64 %28
  %30 = load ptr, ptr %5, align 8
  %31 = call i32 @strcmp(ptr noundef %29, ptr noundef %30) #9
  %32 = icmp eq i32 %31, 0
  %33 = zext i1 %32 to i64
  %34 = select i1 %32, i32 1, i32 0
  store i32 %34, ptr %3, align 4
  br label %35

35:                                               ; preds = %23, %22, %13
  %36 = load i32, ptr %3, align 4
  ret i32 %36
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print_float(float noundef %0) #5 {
  %2 = alloca float, align 4
  store float %0, ptr %2, align 4
  %3 = load float, ptr %2, align 4
  %4 = fpext float %3 to double
  %5 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, double noundef %4)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local zeroext i1 @qc_to_bool_from_string(ptr noundef %0) #0 {
  %2 = alloca i1, align 1
  %3 = alloca ptr, align 8
  store ptr %0, ptr %3, align 8
  %4 = load ptr, ptr %3, align 8
  %5 = icmp ne ptr %4, null
  br i1 %5, label %7, label %6

6:                                                ; preds = %1
  store i1 false, ptr %2, align 1
  br label %17

7:                                                ; preds = %1
  %8 = load ptr, ptr %3, align 8
  %9 = call i32 @strcmp(ptr noundef %8, ptr noundef @.str.3) #9
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %15, label %11

11:                                               ; preds = %7
  %12 = load ptr, ptr %3, align 8
  %13 = call i32 @strcmp(ptr noundef %12, ptr noundef @.str.9) #9
  %14 = icmp eq i32 %13, 0
  br label %15

15:                                               ; preds = %11, %7
  %16 = phi i1 [ true, %7 ], [ %14, %11 ]
  store i1 %16, ptr %2, align 1
  br label %17

17:                                               ; preds = %15, %6
  %18 = load i1, ptr %2, align 1
  ret i1 %18
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local zeroext i8 @qc_to_qbool_from_string(ptr noundef %0) #0 {
  %2 = alloca i8, align 1
  %3 = alloca ptr, align 8
  store ptr %0, ptr %3, align 8
  %4 = load ptr, ptr %3, align 8
  %5 = icmp ne ptr %4, null
  br i1 %5, label %7, label %6

6:                                                ; preds = %1
  store i8 0, ptr %2, align 1
  br label %23

7:                                                ; preds = %1
  %8 = load ptr, ptr %3, align 8
  %9 = call i32 @strcmp(ptr noundef %8, ptr noundef @.str.7) #9
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %11, label %12

11:                                               ; preds = %7
  store i8 2, ptr %2, align 1
  br label %23

12:                                               ; preds = %7
  %13 = load ptr, ptr %3, align 8
  %14 = call i32 @strcmp(ptr noundef %13, ptr noundef @.str.6) #9
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %16, label %17

16:                                               ; preds = %12
  store i8 1, ptr %2, align 1
  br label %23

17:                                               ; preds = %12
  %18 = load ptr, ptr %3, align 8
  %19 = call i32 @strcmp(ptr noundef %18, ptr noundef @.str.8) #9
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %21, label %22

21:                                               ; preds = %17
  store i8 3, ptr %2, align 1
  br label %23

22:                                               ; preds = %17
  store i8 0, ptr %2, align 1
  br label %23

23:                                               ; preds = %22, %21, %16, %11, %6
  %24 = load i8, ptr %2, align 1
  ret i8 %24
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local ptr @qc_qin() #5 {
  %1 = alloca ptr, align 8
  %2 = alloca [1024 x i8], align 16
  %3 = alloca i32, align 4
  %4 = load ptr, ptr @stdout, align 8
  %5 = call i32 @fflush(ptr noundef %4)
  %6 = load ptr, ptr @stderr, align 8
  %7 = call i32 @fflush(ptr noundef %6)
  %8 = load ptr, ptr @stdin, align 8
  %9 = call i32 @fflush(ptr noundef %8)
  %10 = getelementptr inbounds [1024 x i8], ptr %2, i64 0, i64 0
  %11 = call i32 (ptr, ...) @__isoc23_scanf(ptr noundef @.str.10, ptr noundef %10)
  store i32 %11, ptr %3, align 4
  %12 = load ptr, ptr @stderr, align 8
  %13 = call i32 @fflush(ptr noundef %12)
  %14 = load ptr, ptr @stdin, align 8
  %15 = call i32 @fflush(ptr noundef %14)
  %16 = load i32, ptr %3, align 4
  %17 = icmp eq i32 %16, 1
  br i1 %17, label %18, label %21

18:                                               ; preds = %0
  %19 = getelementptr inbounds [1024 x i8], ptr %2, i64 0, i64 0
  %20 = call noalias ptr @strdup(ptr noundef %19) #11
  store ptr %20, ptr %1, align 8
  br label %23

21:                                               ; preds = %0
  %22 = call noalias ptr @strdup(ptr noundef @.str) #11
  store ptr %22, ptr %1, align 8
  br label %23

23:                                               ; preds = %21, %18
  %24 = load ptr, ptr %1, align 8
  ret ptr %24
}

declare i32 @fflush(ptr noundef) #6

declare i32 @__isoc23_scanf(ptr noundef, ...) #6

; Function Attrs: nounwind
declare noalias ptr @strdup(ptr noundef) #4

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print_bool(i1 noundef zeroext %0) #5 {
  %2 = alloca i8, align 1
  %3 = zext i1 %0 to i8
  store i8 %3, ptr %2, align 1
  %4 = load i8, ptr %2, align 1
  %5 = trunc i8 %4 to i1
  %6 = zext i1 %5 to i64
  %7 = select i1 %5, ptr @.str.3, ptr @.str.4
  %8 = call i32 (ptr, ...) @printf(ptr noundef @.str.10, ptr noundef %7)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_trim(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca i64, align 8
  %7 = alloca ptr, align 8
  store ptr %0, ptr %3, align 8
  %8 = load ptr, ptr %3, align 8
  %9 = icmp ne ptr %8, null
  br i1 %9, label %11, label %10

10:                                               ; preds = %1
  store ptr null, ptr %2, align 8
  br label %79

11:                                               ; preds = %1
  br label %12

12:                                               ; preds = %24, %11
  %13 = load ptr, ptr %3, align 8
  %14 = load i8, ptr %13, align 1
  %15 = icmp ne i8 %14, 0
  br i1 %15, label %16, label %22

16:                                               ; preds = %12
  %17 = load ptr, ptr %3, align 8
  %18 = load i8, ptr %17, align 1
  %19 = zext i8 %18 to i32
  %20 = call i32 @isspace(i32 noundef %19) #9
  %21 = icmp ne i32 %20, 0
  br label %22

22:                                               ; preds = %16, %12
  %23 = phi i1 [ false, %12 ], [ %21, %16 ]
  br i1 %23, label %24, label %27

24:                                               ; preds = %22
  %25 = load ptr, ptr %3, align 8
  %26 = getelementptr inbounds i8, ptr %25, i32 1
  store ptr %26, ptr %3, align 8
  br label %12, !llvm.loop !10

27:                                               ; preds = %22
  %28 = load ptr, ptr %3, align 8
  %29 = load i8, ptr %28, align 1
  %30 = sext i8 %29 to i32
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %32, label %37

32:                                               ; preds = %27
  %33 = call noalias ptr @malloc(i64 noundef 1) #10
  store ptr %33, ptr %4, align 8
  %34 = load ptr, ptr %4, align 8
  %35 = getelementptr inbounds i8, ptr %34, i64 0
  store i8 0, ptr %35, align 1
  %36 = load ptr, ptr %4, align 8
  store ptr %36, ptr %2, align 8
  br label %79

37:                                               ; preds = %27
  %38 = load ptr, ptr %3, align 8
  %39 = load ptr, ptr %3, align 8
  %40 = call i64 @strlen(ptr noundef %39) #9
  %41 = getelementptr inbounds i8, ptr %38, i64 %40
  %42 = getelementptr inbounds i8, ptr %41, i64 -1
  store ptr %42, ptr %5, align 8
  br label %43

43:                                               ; preds = %55, %37
  %44 = load ptr, ptr %5, align 8
  %45 = load ptr, ptr %3, align 8
  %46 = icmp ugt ptr %44, %45
  br i1 %46, label %47, label %53

47:                                               ; preds = %43
  %48 = load ptr, ptr %5, align 8
  %49 = load i8, ptr %48, align 1
  %50 = zext i8 %49 to i32
  %51 = call i32 @isspace(i32 noundef %50) #9
  %52 = icmp ne i32 %51, 0
  br label %53

53:                                               ; preds = %47, %43
  %54 = phi i1 [ false, %43 ], [ %52, %47 ]
  br i1 %54, label %55, label %58

55:                                               ; preds = %53
  %56 = load ptr, ptr %5, align 8
  %57 = getelementptr inbounds i8, ptr %56, i32 -1
  store ptr %57, ptr %5, align 8
  br label %43, !llvm.loop !11

58:                                               ; preds = %53
  %59 = load ptr, ptr %5, align 8
  %60 = load ptr, ptr %3, align 8
  %61 = ptrtoint ptr %59 to i64
  %62 = ptrtoint ptr %60 to i64
  %63 = sub i64 %61, %62
  %64 = add nsw i64 %63, 1
  store i64 %64, ptr %6, align 8
  %65 = load i64, ptr %6, align 8
  %66 = add i64 %65, 1
  %67 = call noalias ptr @malloc(i64 noundef %66) #10
  store ptr %67, ptr %7, align 8
  %68 = load ptr, ptr %7, align 8
  %69 = icmp ne ptr %68, null
  br i1 %69, label %71, label %70

70:                                               ; preds = %58
  store ptr null, ptr %2, align 8
  br label %79

71:                                               ; preds = %58
  %72 = load ptr, ptr %7, align 8
  %73 = load ptr, ptr %3, align 8
  %74 = load i64, ptr %6, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %72, ptr align 1 %73, i64 %74, i1 false)
  %75 = load ptr, ptr %7, align 8
  %76 = load i64, ptr %6, align 8
  %77 = getelementptr inbounds i8, ptr %75, i64 %76
  store i8 0, ptr %77, align 1
  %78 = load ptr, ptr %7, align 8
  store ptr %78, ptr %2, align 8
  br label %79

79:                                               ; preds = %71, %70, %32, %10
  %80 = load ptr, ptr %2, align 8
  ret ptr %80
}

; Function Attrs: nounwind willreturn memory(read)
declare i32 @isspace(i32 noundef) #1

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_replace(ptr noundef %0, ptr noundef %1, ptr noundef %2) #0 {
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca ptr, align 8
  %8 = alloca i64, align 8
  %9 = alloca i64, align 8
  %10 = alloca ptr, align 8
  %11 = alloca i32, align 4
  %12 = alloca ptr, align 8
  %13 = alloca ptr, align 8
  %14 = alloca i64, align 8
  %15 = alloca i64, align 8
  %16 = alloca ptr, align 8
  %17 = alloca ptr, align 8
  %18 = alloca ptr, align 8
  store ptr %0, ptr %5, align 8
  store ptr %1, ptr %6, align 8
  store ptr %2, ptr %7, align 8
  %19 = load ptr, ptr %5, align 8
  %20 = icmp ne ptr %19, null
  br i1 %20, label %21, label %27

21:                                               ; preds = %3
  %22 = load ptr, ptr %6, align 8
  %23 = icmp ne ptr %22, null
  br i1 %23, label %24, label %27

24:                                               ; preds = %21
  %25 = load ptr, ptr %7, align 8
  %26 = icmp ne ptr %25, null
  br i1 %26, label %28, label %27

27:                                               ; preds = %24, %21, %3
  store ptr null, ptr %4, align 8
  br label %120

28:                                               ; preds = %24
  %29 = load ptr, ptr %6, align 8
  %30 = call i64 @strlen(ptr noundef %29) #9
  store i64 %30, ptr %8, align 8
  %31 = load ptr, ptr %7, align 8
  %32 = call i64 @strlen(ptr noundef %31) #9
  store i64 %32, ptr %9, align 8
  %33 = load i64, ptr %8, align 8
  %34 = icmp eq i64 %33, 0
  br i1 %34, label %35, label %44

35:                                               ; preds = %28
  %36 = load ptr, ptr %5, align 8
  %37 = call i64 @strlen(ptr noundef %36) #9
  %38 = add i64 %37, 1
  %39 = call noalias ptr @malloc(i64 noundef %38) #10
  store ptr %39, ptr %10, align 8
  %40 = load ptr, ptr %10, align 8
  %41 = load ptr, ptr %5, align 8
  %42 = call ptr @strcpy(ptr noundef %40, ptr noundef %41) #11
  %43 = load ptr, ptr %10, align 8
  store ptr %43, ptr %4, align 8
  br label %120

44:                                               ; preds = %28
  store i32 0, ptr %11, align 4
  %45 = load ptr, ptr %5, align 8
  store ptr %45, ptr %12, align 8
  br label %46

46:                                               ; preds = %51, %44
  %47 = load ptr, ptr %12, align 8
  %48 = load ptr, ptr %6, align 8
  %49 = call noundef ptr @strstr(ptr noundef %47, ptr noundef %48) #9
  store ptr %49, ptr %12, align 8
  %50 = icmp ne ptr %49, null
  br i1 %50, label %51, label %57

51:                                               ; preds = %46
  %52 = load i32, ptr %11, align 4
  %53 = add nsw i32 %52, 1
  store i32 %53, ptr %11, align 4
  %54 = load i64, ptr %8, align 8
  %55 = load ptr, ptr %12, align 8
  %56 = getelementptr inbounds i8, ptr %55, i64 %54
  store ptr %56, ptr %12, align 8
  br label %46, !llvm.loop !12

57:                                               ; preds = %46
  %58 = load i32, ptr %11, align 4
  %59 = icmp eq i32 %58, 0
  br i1 %59, label %60, label %69

60:                                               ; preds = %57
  %61 = load ptr, ptr %5, align 8
  %62 = call i64 @strlen(ptr noundef %61) #9
  %63 = add i64 %62, 1
  %64 = call noalias ptr @malloc(i64 noundef %63) #10
  store ptr %64, ptr %13, align 8
  %65 = load ptr, ptr %13, align 8
  %66 = load ptr, ptr %5, align 8
  %67 = call ptr @strcpy(ptr noundef %65, ptr noundef %66) #11
  %68 = load ptr, ptr %13, align 8
  store ptr %68, ptr %4, align 8
  br label %120

69:                                               ; preds = %57
  %70 = load ptr, ptr %5, align 8
  %71 = call i64 @strlen(ptr noundef %70) #9
  store i64 %71, ptr %14, align 8
  %72 = load i64, ptr %14, align 8
  %73 = load i32, ptr %11, align 4
  %74 = sext i32 %73 to i64
  %75 = load i64, ptr %9, align 8
  %76 = load i64, ptr %8, align 8
  %77 = sub i64 %75, %76
  %78 = mul i64 %74, %77
  %79 = add i64 %72, %78
  store i64 %79, ptr %15, align 8
  %80 = load i64, ptr %15, align 8
  %81 = add i64 %80, 1
  %82 = call noalias ptr @malloc(i64 noundef %81) #10
  store ptr %82, ptr %16, align 8
  %83 = load ptr, ptr %16, align 8
  %84 = icmp ne ptr %83, null
  br i1 %84, label %86, label %85

85:                                               ; preds = %69
  store ptr null, ptr %4, align 8
  br label %120

86:                                               ; preds = %69
  %87 = load ptr, ptr %16, align 8
  store ptr %87, ptr %17, align 8
  %88 = load ptr, ptr %5, align 8
  store ptr %88, ptr %12, align 8
  br label %89

89:                                               ; preds = %116, %86
  %90 = load ptr, ptr %12, align 8
  %91 = load i8, ptr %90, align 1
  %92 = icmp ne i8 %91, 0
  br i1 %92, label %93, label %117

93:                                               ; preds = %89
  %94 = load ptr, ptr %12, align 8
  %95 = load ptr, ptr %6, align 8
  %96 = call noundef ptr @strstr(ptr noundef %94, ptr noundef %95) #9
  store ptr %96, ptr %18, align 8
  %97 = load ptr, ptr %18, align 8
  %98 = load ptr, ptr %12, align 8
  %99 = icmp eq ptr %97, %98
  br i1 %99, label %100, label %110

100:                                              ; preds = %93
  %101 = load ptr, ptr %17, align 8
  %102 = load ptr, ptr %7, align 8
  %103 = load i64, ptr %9, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %101, ptr align 1 %102, i64 %103, i1 false)
  %104 = load i64, ptr %9, align 8
  %105 = load ptr, ptr %17, align 8
  %106 = getelementptr inbounds i8, ptr %105, i64 %104
  store ptr %106, ptr %17, align 8
  %107 = load i64, ptr %8, align 8
  %108 = load ptr, ptr %12, align 8
  %109 = getelementptr inbounds i8, ptr %108, i64 %107
  store ptr %109, ptr %12, align 8
  br label %116

110:                                              ; preds = %93
  %111 = load ptr, ptr %12, align 8
  %112 = getelementptr inbounds i8, ptr %111, i32 1
  store ptr %112, ptr %12, align 8
  %113 = load i8, ptr %111, align 1
  %114 = load ptr, ptr %17, align 8
  %115 = getelementptr inbounds i8, ptr %114, i32 1
  store ptr %115, ptr %17, align 8
  store i8 %113, ptr %114, align 1
  br label %116

116:                                              ; preds = %110, %100
  br label %89, !llvm.loop !13

117:                                              ; preds = %89
  %118 = load ptr, ptr %17, align 8
  store i8 0, ptr %118, align 1
  %119 = load ptr, ptr %16, align 8
  store ptr %119, ptr %4, align 8
  br label %120

120:                                              ; preds = %117, %85, %60, %35, %27
  %121 = load ptr, ptr %4, align 8
  ret ptr %121
}

; Function Attrs: nounwind
declare ptr @strcpy(ptr noundef, ptr noundef) #4

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local i32 @qc_to_int_from_string(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = icmp ne ptr %3, null
  br i1 %4, label %5, label %8

5:                                                ; preds = %1
  %6 = load ptr, ptr %2, align 8
  %7 = call i32 @atoi(ptr noundef %6) #9
  br label %9

8:                                                ; preds = %1
  br label %9

9:                                                ; preds = %8, %5
  %10 = phi i32 [ %7, %5 ], [ 0, %8 ]
  ret i32 %10
}

; Function Attrs: nounwind willreturn memory(read)
declare i32 @atoi(ptr noundef) #1

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local float @qc_to_float_from_string(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = icmp ne ptr %3, null
  br i1 %4, label %5, label %9

5:                                                ; preds = %1
  %6 = load ptr, ptr %2, align 8
  %7 = call double @atof(ptr noundef %6) #9
  %8 = fptrunc double %7 to float
  br label %10

9:                                                ; preds = %1
  br label %10

10:                                               ; preds = %9, %5
  %11 = phi float [ %8, %5 ], [ 0.000000e+00, %9 ]
  ret float %11
}

; Function Attrs: nounwind willreturn memory(read)
declare double @atof(ptr noundef) #1

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local double @qc_to_double_from_string(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = icmp ne ptr %3, null
  br i1 %4, label %5, label %8

5:                                                ; preds = %1
  %6 = load ptr, ptr %2, align 8
  %7 = call double @atof(ptr noundef %6) #9
  br label %9

8:                                                ; preds = %1
  br label %9

9:                                                ; preds = %8, %5
  %10 = phi double [ %7, %5 ], [ 0.000000e+00, %8 ]
  ret double %10
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local signext i8 @qc_to_char_from_string(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = icmp ne ptr %3, null
  br i1 %4, label %5, label %14

5:                                                ; preds = %1
  %6 = load ptr, ptr %2, align 8
  %7 = getelementptr inbounds i8, ptr %6, i64 0
  %8 = load i8, ptr %7, align 1
  %9 = icmp ne i8 %8, 0
  br i1 %9, label %10, label %14

10:                                               ; preds = %5
  %11 = load ptr, ptr %2, align 8
  %12 = getelementptr inbounds i8, ptr %11, i64 0
  %13 = load i8, ptr %12, align 1
  br label %15

14:                                               ; preds = %5, %1
  br label %15

15:                                               ; preds = %14, %10
  %16 = phi i8 [ %13, %10 ], [ 0, %14 ]
  ret i8 %16
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local i32 @qc_to_int_from_bool(i1 noundef zeroext %0) #0 {
  %2 = alloca i8, align 1
  %3 = zext i1 %0 to i8
  store i8 %3, ptr %2, align 1
  %4 = load i8, ptr %2, align 1
  %5 = trunc i8 %4 to i1
  %6 = zext i1 %5 to i64
  %7 = select i1 %5, i32 1, i32 0
  ret i32 %7
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local float @qc_to_float_from_int(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  %3 = load i32, ptr %2, align 4
  %4 = sitofp i32 %3 to float
  ret float %4
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local double @qc_to_double_from_int(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  %3 = load i32, ptr %2, align 4
  %4 = sitofp i32 %3 to double
  ret double %4
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print(ptr noundef %0) #5 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = icmp ne ptr %3, null
  br i1 %4, label %5, label %8

5:                                                ; preds = %1
  %6 = load ptr, ptr %2, align 8
  %7 = call i32 (ptr, ...) @printf(ptr noundef @.str.10, ptr noundef %6)
  br label %8

8:                                                ; preds = %5, %1
  ret void
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_println(ptr noundef %0) #5 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = icmp ne ptr %3, null
  br i1 %4, label %5, label %8

5:                                                ; preds = %1
  %6 = load ptr, ptr %2, align 8
  %7 = call i32 (ptr, ...) @printf(ptr noundef @.str.11, ptr noundef %6)
  br label %10

8:                                                ; preds = %1
  %9 = call i32 (ptr, ...) @printf(ptr noundef @.str.12)
  br label %10

10:                                               ; preds = %8, %5
  ret void
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print_array_int(ptr noundef %0, i32 noundef %1) #5 {
  %3 = alloca ptr, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store ptr %0, ptr %3, align 8
  store i32 %1, ptr %4, align 4
  %6 = call i32 (ptr, ...) @printf(ptr noundef @.str.13)
  store i32 0, ptr %5, align 4
  br label %7

7:                                                ; preds = %25, %2
  %8 = load i32, ptr %5, align 4
  %9 = load i32, ptr %4, align 4
  %10 = icmp slt i32 %8, %9
  br i1 %10, label %11, label %28

11:                                               ; preds = %7
  %12 = load ptr, ptr %3, align 8
  %13 = load i32, ptr %5, align 4
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds i32, ptr %12, i64 %14
  %16 = load i32, ptr %15, align 4
  %17 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %16)
  %18 = load i32, ptr %5, align 4
  %19 = load i32, ptr %4, align 4
  %20 = sub nsw i32 %19, 1
  %21 = icmp slt i32 %18, %20
  br i1 %21, label %22, label %24

22:                                               ; preds = %11
  %23 = call i32 (ptr, ...) @printf(ptr noundef @.str.14)
  br label %24

24:                                               ; preds = %22, %11
  br label %25

25:                                               ; preds = %24
  %26 = load i32, ptr %5, align 4
  %27 = add nsw i32 %26, 1
  store i32 %27, ptr %5, align 4
  br label %7, !llvm.loop !14

28:                                               ; preds = %7
  %29 = call i32 (ptr, ...) @printf(ptr noundef @.str.15)
  ret void
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print_array_float(ptr noundef %0, i32 noundef %1) #5 {
  %3 = alloca ptr, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store ptr %0, ptr %3, align 8
  store i32 %1, ptr %4, align 4
  %6 = call i32 (ptr, ...) @printf(ptr noundef @.str.13)
  store i32 0, ptr %5, align 4
  br label %7

7:                                                ; preds = %26, %2
  %8 = load i32, ptr %5, align 4
  %9 = load i32, ptr %4, align 4
  %10 = icmp slt i32 %8, %9
  br i1 %10, label %11, label %29

11:                                               ; preds = %7
  %12 = load ptr, ptr %3, align 8
  %13 = load i32, ptr %5, align 4
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds float, ptr %12, i64 %14
  %16 = load float, ptr %15, align 4
  %17 = fpext float %16 to double
  %18 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, double noundef %17)
  %19 = load i32, ptr %5, align 4
  %20 = load i32, ptr %4, align 4
  %21 = sub nsw i32 %20, 1
  %22 = icmp slt i32 %19, %21
  br i1 %22, label %23, label %25

23:                                               ; preds = %11
  %24 = call i32 (ptr, ...) @printf(ptr noundef @.str.14)
  br label %25

25:                                               ; preds = %23, %11
  br label %26

26:                                               ; preds = %25
  %27 = load i32, ptr %5, align 4
  %28 = add nsw i32 %27, 1
  store i32 %28, ptr %5, align 4
  br label %7, !llvm.loop !15

29:                                               ; preds = %7
  %30 = call i32 (ptr, ...) @printf(ptr noundef @.str.15)
  ret void
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print_array_double(ptr noundef %0, i32 noundef %1) #5 {
  %3 = alloca ptr, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store ptr %0, ptr %3, align 8
  store i32 %1, ptr %4, align 4
  %6 = call i32 (ptr, ...) @printf(ptr noundef @.str.13)
  store i32 0, ptr %5, align 4
  br label %7

7:                                                ; preds = %25, %2
  %8 = load i32, ptr %5, align 4
  %9 = load i32, ptr %4, align 4
  %10 = icmp slt i32 %8, %9
  br i1 %10, label %11, label %28

11:                                               ; preds = %7
  %12 = load ptr, ptr %3, align 8
  %13 = load i32, ptr %5, align 4
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds double, ptr %12, i64 %14
  %16 = load double, ptr %15, align 8
  %17 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, double noundef %16)
  %18 = load i32, ptr %5, align 4
  %19 = load i32, ptr %4, align 4
  %20 = sub nsw i32 %19, 1
  %21 = icmp slt i32 %18, %20
  br i1 %21, label %22, label %24

22:                                               ; preds = %11
  %23 = call i32 (ptr, ...) @printf(ptr noundef @.str.14)
  br label %24

24:                                               ; preds = %22, %11
  br label %25

25:                                               ; preds = %24
  %26 = load i32, ptr %5, align 4
  %27 = add nsw i32 %26, 1
  store i32 %27, ptr %5, align 4
  br label %7, !llvm.loop !16

28:                                               ; preds = %7
  %29 = call i32 (ptr, ...) @printf(ptr noundef @.str.15)
  ret void
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print_array_string(ptr noundef %0, i32 noundef %1) #5 {
  %3 = alloca ptr, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store ptr %0, ptr %3, align 8
  store i32 %1, ptr %4, align 4
  %6 = call i32 (ptr, ...) @printf(ptr noundef @.str.13)
  store i32 0, ptr %5, align 4
  br label %7

7:                                                ; preds = %25, %2
  %8 = load i32, ptr %5, align 4
  %9 = load i32, ptr %4, align 4
  %10 = icmp slt i32 %8, %9
  br i1 %10, label %11, label %28

11:                                               ; preds = %7
  %12 = load ptr, ptr %3, align 8
  %13 = load i32, ptr %5, align 4
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds ptr, ptr %12, i64 %14
  %16 = load ptr, ptr %15, align 8
  %17 = call i32 (ptr, ...) @printf(ptr noundef @.str.16, ptr noundef %16)
  %18 = load i32, ptr %5, align 4
  %19 = load i32, ptr %4, align 4
  %20 = sub nsw i32 %19, 1
  %21 = icmp slt i32 %18, %20
  br i1 %21, label %22, label %24

22:                                               ; preds = %11
  %23 = call i32 (ptr, ...) @printf(ptr noundef @.str.14)
  br label %24

24:                                               ; preds = %22, %11
  br label %25

25:                                               ; preds = %24
  %26 = load i32, ptr %5, align 4
  %27 = add nsw i32 %26, 1
  store i32 %27, ptr %5, align 4
  br label %7, !llvm.loop !17

28:                                               ; preds = %7
  %29 = call i32 (ptr, ...) @printf(ptr noundef @.str.15)
  ret void
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print_array_char(ptr noundef %0, i32 noundef %1) #5 {
  %3 = alloca ptr, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store ptr %0, ptr %3, align 8
  store i32 %1, ptr %4, align 4
  %6 = call i32 (ptr, ...) @printf(ptr noundef @.str.13)
  store i32 0, ptr %5, align 4
  br label %7

7:                                                ; preds = %26, %2
  %8 = load i32, ptr %5, align 4
  %9 = load i32, ptr %4, align 4
  %10 = icmp slt i32 %8, %9
  br i1 %10, label %11, label %29

11:                                               ; preds = %7
  %12 = load ptr, ptr %3, align 8
  %13 = load i32, ptr %5, align 4
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds i8, ptr %12, i64 %14
  %16 = load i8, ptr %15, align 1
  %17 = sext i8 %16 to i32
  %18 = call i32 (ptr, ...) @printf(ptr noundef @.str.17, i32 noundef %17)
  %19 = load i32, ptr %5, align 4
  %20 = load i32, ptr %4, align 4
  %21 = sub nsw i32 %20, 1
  %22 = icmp slt i32 %19, %21
  br i1 %22, label %23, label %25

23:                                               ; preds = %11
  %24 = call i32 (ptr, ...) @printf(ptr noundef @.str.14)
  br label %25

25:                                               ; preds = %23, %11
  br label %26

26:                                               ; preds = %25
  %27 = load i32, ptr %5, align 4
  %28 = add nsw i32 %27, 1
  store i32 %28, ptr %5, align 4
  br label %7, !llvm.loop !18

29:                                               ; preds = %7
  %30 = call i32 (ptr, ...) @printf(ptr noundef @.str.15)
  ret void
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print_array_bool(ptr noundef %0, i32 noundef %1) #5 {
  %3 = alloca ptr, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store ptr %0, ptr %3, align 8
  store i32 %1, ptr %4, align 4
  %6 = call i32 (ptr, ...) @printf(ptr noundef @.str.13)
  store i32 0, ptr %5, align 4
  br label %7

7:                                                ; preds = %28, %2
  %8 = load i32, ptr %5, align 4
  %9 = load i32, ptr %4, align 4
  %10 = icmp slt i32 %8, %9
  br i1 %10, label %11, label %31

11:                                               ; preds = %7
  %12 = load ptr, ptr %3, align 8
  %13 = load i32, ptr %5, align 4
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds i8, ptr %12, i64 %14
  %16 = load i8, ptr %15, align 1
  %17 = trunc i8 %16 to i1
  %18 = zext i1 %17 to i64
  %19 = select i1 %17, ptr @.str.3, ptr @.str.4
  %20 = call i32 (ptr, ...) @printf(ptr noundef @.str.10, ptr noundef %19)
  %21 = load i32, ptr %5, align 4
  %22 = load i32, ptr %4, align 4
  %23 = sub nsw i32 %22, 1
  %24 = icmp slt i32 %21, %23
  br i1 %24, label %25, label %27

25:                                               ; preds = %11
  %26 = call i32 (ptr, ...) @printf(ptr noundef @.str.14)
  br label %27

27:                                               ; preds = %25, %11
  br label %28

28:                                               ; preds = %27
  %29 = load i32, ptr %5, align 4
  %30 = add nsw i32 %29, 1
  store i32 %30, ptr %5, align 4
  br label %7, !llvm.loop !19

31:                                               ; preds = %7
  %32 = call i32 (ptr, ...) @printf(ptr noundef @.str.15)
  ret void
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print_array_qbool(ptr noundef %0, i32 noundef %1) #5 {
  %3 = alloca ptr, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store ptr %0, ptr %3, align 8
  store i32 %1, ptr %4, align 4
  %6 = call i32 (ptr, ...) @printf(ptr noundef @.str.13)
  store i32 0, ptr %5, align 4
  br label %7

7:                                                ; preds = %35, %2
  %8 = load i32, ptr %5, align 4
  %9 = load i32, ptr %4, align 4
  %10 = icmp slt i32 %8, %9
  br i1 %10, label %11, label %38

11:                                               ; preds = %7
  %12 = load ptr, ptr %3, align 8
  %13 = load i32, ptr %5, align 4
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds i8, ptr %12, i64 %14
  %16 = load i8, ptr %15, align 1
  %17 = zext i8 %16 to i32
  %18 = and i32 %17, 3
  switch i32 %18, label %27 [
    i32 0, label %19
    i32 1, label %21
    i32 2, label %23
    i32 3, label %25
  ]

19:                                               ; preds = %11
  %20 = call i32 (ptr, ...) @printf(ptr noundef @.str.5)
  br label %27

21:                                               ; preds = %11
  %22 = call i32 (ptr, ...) @printf(ptr noundef @.str.6)
  br label %27

23:                                               ; preds = %11
  %24 = call i32 (ptr, ...) @printf(ptr noundef @.str.7)
  br label %27

25:                                               ; preds = %11
  %26 = call i32 (ptr, ...) @printf(ptr noundef @.str.8)
  br label %27

27:                                               ; preds = %25, %23, %21, %19, %11
  %28 = load i32, ptr %5, align 4
  %29 = load i32, ptr %4, align 4
  %30 = sub nsw i32 %29, 1
  %31 = icmp slt i32 %28, %30
  br i1 %31, label %32, label %34

32:                                               ; preds = %27
  %33 = call i32 (ptr, ...) @printf(ptr noundef @.str.14)
  br label %34

34:                                               ; preds = %32, %27
  br label %35

35:                                               ; preds = %34
  %36 = load i32, ptr %5, align 4
  %37 = add nsw i32 %36, 1
  store i32 %37, ptr %5, align 4
  br label %7, !llvm.loop !20

38:                                               ; preds = %7
  %39 = call i32 (ptr, ...) @printf(ptr noundef @.str.15)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local i32 @sizeof_type(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  %4 = load i32, ptr %3, align 4
  switch i32 %4, label %12 [
    i32 0, label %5
    i32 1, label %6
    i32 2, label %7
    i32 3, label %8
    i32 4, label %9
    i32 5, label %10
    i32 6, label %11
  ]

5:                                                ; preds = %1
  store i32 4, ptr %2, align 4
  br label %13

6:                                                ; preds = %1
  store i32 4, ptr %2, align 4
  br label %13

7:                                                ; preds = %1
  store i32 8, ptr %2, align 4
  br label %13

8:                                                ; preds = %1
  store i32 1, ptr %2, align 4
  br label %13

9:                                                ; preds = %1
  store i32 1, ptr %2, align 4
  br label %13

10:                                               ; preds = %1
  store i32 1, ptr %2, align 4
  br label %13

11:                                               ; preds = %1
  store i32 8, ptr %2, align 4
  br label %13

12:                                               ; preds = %1
  store i32 4, ptr %2, align 4
  br label %13

13:                                               ; preds = %12, %11, %10, %9, %8, %7, %6, %5
  %14 = load i32, ptr %2, align 4
  ret i32 %14
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local ptr @qc_array_to_string_recursive(ptr noundef %0, i32 noundef %1, i32 noundef %2, ptr noundef %3) #5 {
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca ptr, align 8
  %10 = alloca [256 x i8], align 16
  %11 = alloca i8, align 1
  %12 = alloca ptr, align 8
  %13 = alloca ptr, align 8
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca i32, align 4
  %17 = alloca ptr, align 8
  %18 = alloca i32, align 4
  %19 = alloca ptr, align 8
  %20 = alloca ptr, align 8
  %21 = alloca ptr, align 8
  %22 = alloca i32, align 4
  store ptr %0, ptr %6, align 8
  store i32 %1, ptr %7, align 4
  store i32 %2, ptr %8, align 4
  store ptr %3, ptr %9, align 8
  %23 = load i32, ptr %8, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %25, label %99

25:                                               ; preds = %4
  %26 = load i32, ptr %7, align 4
  switch i32 %26, label %90 [
    i32 0, label %27
    i32 1, label %32
    i32 2, label %38
    i32 3, label %43
    i32 4, label %49
    i32 5, label %57
    i32 6, label %85
  ]

27:                                               ; preds = %25
  %28 = getelementptr inbounds [256 x i8], ptr %10, i64 0, i64 0
  %29 = load ptr, ptr %6, align 8
  %30 = load i32, ptr %29, align 4
  %31 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %28, i64 noundef 256, ptr noundef @.str.1, i32 noundef %30) #11
  br label %90

32:                                               ; preds = %25
  %33 = getelementptr inbounds [256 x i8], ptr %10, i64 0, i64 0
  %34 = load ptr, ptr %6, align 8
  %35 = load float, ptr %34, align 4
  %36 = fpext float %35 to double
  %37 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %33, i64 noundef 256, ptr noundef @.str.2, double noundef %36) #11
  br label %90

38:                                               ; preds = %25
  %39 = getelementptr inbounds [256 x i8], ptr %10, i64 0, i64 0
  %40 = load ptr, ptr %6, align 8
  %41 = load double, ptr %40, align 8
  %42 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %39, i64 noundef 256, ptr noundef @.str.2, double noundef %41) #11
  br label %90

43:                                               ; preds = %25
  %44 = getelementptr inbounds [256 x i8], ptr %10, i64 0, i64 0
  %45 = load ptr, ptr %6, align 8
  %46 = load i8, ptr %45, align 1
  %47 = sext i8 %46 to i32
  %48 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %44, i64 noundef 256, ptr noundef @.str.17, i32 noundef %47) #11
  br label %90

49:                                               ; preds = %25
  %50 = getelementptr inbounds [256 x i8], ptr %10, i64 0, i64 0
  %51 = load ptr, ptr %6, align 8
  %52 = load i8, ptr %51, align 1
  %53 = trunc i8 %52 to i1
  %54 = zext i1 %53 to i64
  %55 = select i1 %53, ptr @.str.3, ptr @.str.4
  %56 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %50, i64 noundef 256, ptr noundef @.str.10, ptr noundef %55) #11
  br label %90

57:                                               ; preds = %25
  %58 = load ptr, ptr %6, align 8
  %59 = load i8, ptr %58, align 1
  %60 = zext i8 %59 to i32
  %61 = and i32 %60, 3
  %62 = trunc i32 %61 to i8
  store i8 %62, ptr %11, align 1
  %63 = load i8, ptr %11, align 1
  %64 = zext i8 %63 to i32
  %65 = icmp eq i32 %64, 0
  br i1 %65, label %66, label %67

66:                                               ; preds = %57
  br label %80

67:                                               ; preds = %57
  %68 = load i8, ptr %11, align 1
  %69 = zext i8 %68 to i32
  %70 = icmp eq i32 %69, 1
  br i1 %70, label %71, label %72

71:                                               ; preds = %67
  br label %78

72:                                               ; preds = %67
  %73 = load i8, ptr %11, align 1
  %74 = zext i8 %73 to i32
  %75 = icmp eq i32 %74, 2
  %76 = zext i1 %75 to i64
  %77 = select i1 %75, ptr @.str.7, ptr @.str.8
  br label %78

78:                                               ; preds = %72, %71
  %79 = phi ptr [ @.str.6, %71 ], [ %77, %72 ]
  br label %80

80:                                               ; preds = %78, %66
  %81 = phi ptr [ @.str.5, %66 ], [ %79, %78 ]
  store ptr %81, ptr %12, align 8
  %82 = getelementptr inbounds [256 x i8], ptr %10, i64 0, i64 0
  %83 = load ptr, ptr %12, align 8
  %84 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %82, i64 noundef 256, ptr noundef @.str.10, ptr noundef %83) #11
  br label %90

85:                                               ; preds = %25
  %86 = getelementptr inbounds [256 x i8], ptr %10, i64 0, i64 0
  %87 = load ptr, ptr %6, align 8
  %88 = load ptr, ptr %87, align 8
  %89 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %86, i64 noundef 256, ptr noundef @.str.16, ptr noundef %88) #11
  br label %90

90:                                               ; preds = %85, %80, %49, %43, %38, %32, %27, %25
  %91 = getelementptr inbounds [256 x i8], ptr %10, i64 0, i64 0
  %92 = call i64 @strlen(ptr noundef %91) #9
  %93 = add i64 %92, 1
  %94 = call noalias ptr @malloc(i64 noundef %93) #10
  store ptr %94, ptr %13, align 8
  %95 = load ptr, ptr %13, align 8
  %96 = getelementptr inbounds [256 x i8], ptr %10, i64 0, i64 0
  %97 = call ptr @strcpy(ptr noundef %95, ptr noundef %96) #11
  %98 = load ptr, ptr %13, align 8
  store ptr %98, ptr %5, align 8
  br label %227

99:                                               ; preds = %4
  store i32 2, ptr %14, align 4
  %100 = load i32, ptr %7, align 4
  %101 = call i32 @sizeof_type(i32 noundef %100)
  store i32 %101, ptr %15, align 4
  store i32 1, ptr %16, align 4
  br label %102

102:                                              ; preds = %114, %99
  %103 = load i32, ptr %16, align 4
  %104 = load i32, ptr %8, align 4
  %105 = icmp slt i32 %103, %104
  br i1 %105, label %106, label %117

106:                                              ; preds = %102
  %107 = load ptr, ptr %9, align 8
  %108 = load i32, ptr %16, align 4
  %109 = sext i32 %108 to i64
  %110 = getelementptr inbounds i32, ptr %107, i64 %109
  %111 = load i32, ptr %110, align 4
  %112 = load i32, ptr %15, align 4
  %113 = mul nsw i32 %112, %111
  store i32 %113, ptr %15, align 4
  br label %114

114:                                              ; preds = %106
  %115 = load i32, ptr %16, align 4
  %116 = add nsw i32 %115, 1
  store i32 %116, ptr %16, align 4
  br label %102, !llvm.loop !21

117:                                              ; preds = %102
  %118 = load ptr, ptr %9, align 8
  %119 = getelementptr inbounds i32, ptr %118, i64 0
  %120 = load i32, ptr %119, align 4
  %121 = sext i32 %120 to i64
  %122 = mul i64 %121, 8
  %123 = call noalias ptr @malloc(i64 noundef %122) #10
  store ptr %123, ptr %17, align 8
  store i32 0, ptr %18, align 4
  br label %124

124:                                              ; preds = %168, %117
  %125 = load i32, ptr %18, align 4
  %126 = load ptr, ptr %9, align 8
  %127 = getelementptr inbounds i32, ptr %126, i64 0
  %128 = load i32, ptr %127, align 4
  %129 = icmp slt i32 %125, %128
  br i1 %129, label %130, label %171

130:                                              ; preds = %124
  %131 = load ptr, ptr %6, align 8
  %132 = load i32, ptr %18, align 4
  %133 = load i32, ptr %15, align 4
  %134 = mul nsw i32 %132, %133
  %135 = sext i32 %134 to i64
  %136 = getelementptr inbounds i8, ptr %131, i64 %135
  store ptr %136, ptr %19, align 8
  %137 = load ptr, ptr %19, align 8
  %138 = load i32, ptr %7, align 4
  %139 = load i32, ptr %8, align 4
  %140 = sub nsw i32 %139, 1
  %141 = load ptr, ptr %9, align 8
  %142 = getelementptr inbounds i32, ptr %141, i64 1
  %143 = call ptr @qc_array_to_string_recursive(ptr noundef %137, i32 noundef %138, i32 noundef %140, ptr noundef %142)
  %144 = load ptr, ptr %17, align 8
  %145 = load i32, ptr %18, align 4
  %146 = sext i32 %145 to i64
  %147 = getelementptr inbounds ptr, ptr %144, i64 %146
  store ptr %143, ptr %147, align 8
  %148 = load ptr, ptr %17, align 8
  %149 = load i32, ptr %18, align 4
  %150 = sext i32 %149 to i64
  %151 = getelementptr inbounds ptr, ptr %148, i64 %150
  %152 = load ptr, ptr %151, align 8
  %153 = call i64 @strlen(ptr noundef %152) #9
  %154 = load i32, ptr %14, align 4
  %155 = sext i32 %154 to i64
  %156 = add i64 %155, %153
  %157 = trunc i64 %156 to i32
  store i32 %157, ptr %14, align 4
  %158 = load i32, ptr %18, align 4
  %159 = load ptr, ptr %9, align 8
  %160 = getelementptr inbounds i32, ptr %159, i64 0
  %161 = load i32, ptr %160, align 4
  %162 = sub nsw i32 %161, 1
  %163 = icmp slt i32 %158, %162
  br i1 %163, label %164, label %167

164:                                              ; preds = %130
  %165 = load i32, ptr %14, align 4
  %166 = add nsw i32 %165, 2
  store i32 %166, ptr %14, align 4
  br label %167

167:                                              ; preds = %164, %130
  br label %168

168:                                              ; preds = %167
  %169 = load i32, ptr %18, align 4
  %170 = add nsw i32 %169, 1
  store i32 %170, ptr %18, align 4
  br label %124, !llvm.loop !22

171:                                              ; preds = %124
  %172 = load i32, ptr %14, align 4
  %173 = add nsw i32 %172, 1
  %174 = sext i32 %173 to i64
  %175 = call noalias ptr @malloc(i64 noundef %174) #10
  store ptr %175, ptr %20, align 8
  %176 = load ptr, ptr %20, align 8
  store ptr %176, ptr %21, align 8
  %177 = load ptr, ptr %21, align 8
  %178 = getelementptr inbounds i8, ptr %177, i32 1
  store ptr %178, ptr %21, align 8
  store i8 91, ptr %177, align 1
  store i32 0, ptr %22, align 4
  br label %179

179:                                              ; preds = %218, %171
  %180 = load i32, ptr %22, align 4
  %181 = load ptr, ptr %9, align 8
  %182 = getelementptr inbounds i32, ptr %181, i64 0
  %183 = load i32, ptr %182, align 4
  %184 = icmp slt i32 %180, %183
  br i1 %184, label %185, label %221

185:                                              ; preds = %179
  %186 = load ptr, ptr %21, align 8
  %187 = load ptr, ptr %17, align 8
  %188 = load i32, ptr %22, align 4
  %189 = sext i32 %188 to i64
  %190 = getelementptr inbounds ptr, ptr %187, i64 %189
  %191 = load ptr, ptr %190, align 8
  %192 = call ptr @strcpy(ptr noundef %186, ptr noundef %191) #11
  %193 = load ptr, ptr %17, align 8
  %194 = load i32, ptr %22, align 4
  %195 = sext i32 %194 to i64
  %196 = getelementptr inbounds ptr, ptr %193, i64 %195
  %197 = load ptr, ptr %196, align 8
  %198 = call i64 @strlen(ptr noundef %197) #9
  %199 = load ptr, ptr %21, align 8
  %200 = getelementptr inbounds i8, ptr %199, i64 %198
  store ptr %200, ptr %21, align 8
  %201 = load ptr, ptr %17, align 8
  %202 = load i32, ptr %22, align 4
  %203 = sext i32 %202 to i64
  %204 = getelementptr inbounds ptr, ptr %201, i64 %203
  %205 = load ptr, ptr %204, align 8
  call void @free(ptr noundef %205) #11
  %206 = load i32, ptr %22, align 4
  %207 = load ptr, ptr %9, align 8
  %208 = getelementptr inbounds i32, ptr %207, i64 0
  %209 = load i32, ptr %208, align 4
  %210 = sub nsw i32 %209, 1
  %211 = icmp slt i32 %206, %210
  br i1 %211, label %212, label %217

212:                                              ; preds = %185
  %213 = load ptr, ptr %21, align 8
  %214 = getelementptr inbounds i8, ptr %213, i32 1
  store ptr %214, ptr %21, align 8
  store i8 44, ptr %213, align 1
  %215 = load ptr, ptr %21, align 8
  %216 = getelementptr inbounds i8, ptr %215, i32 1
  store ptr %216, ptr %21, align 8
  store i8 32, ptr %215, align 1
  br label %217

217:                                              ; preds = %212, %185
  br label %218

218:                                              ; preds = %217
  %219 = load i32, ptr %22, align 4
  %220 = add nsw i32 %219, 1
  store i32 %220, ptr %22, align 4
  br label %179, !llvm.loop !23

221:                                              ; preds = %179
  %222 = load ptr, ptr %21, align 8
  %223 = getelementptr inbounds i8, ptr %222, i32 1
  store ptr %223, ptr %21, align 8
  store i8 93, ptr %222, align 1
  %224 = load ptr, ptr %21, align 8
  store i8 0, ptr %224, align 1
  %225 = load ptr, ptr %17, align 8
  call void @free(ptr noundef %225) #11
  %226 = load ptr, ptr %20, align 8
  store ptr %226, ptr %5, align 8
  br label %227

227:                                              ; preds = %221, %90
  %228 = load ptr, ptr %5, align 8
  ret ptr %228
}

; Function Attrs: nounwind
declare void @free(ptr noundef) #4

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print_array_recursive(ptr noundef %0, i32 noundef %1, i32 noundef %2, ptr noundef %3) #5 {
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca ptr, align 8
  %9 = alloca i8, align 1
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca ptr, align 8
  store ptr %0, ptr %5, align 8
  store i32 %1, ptr %6, align 4
  store i32 %2, ptr %7, align 4
  store ptr %3, ptr %8, align 8
  %14 = load i32, ptr %7, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %16, label %65

16:                                               ; preds = %4
  %17 = load i32, ptr %6, align 4
  switch i32 %17, label %64 [
    i32 0, label %18
    i32 1, label %22
    i32 2, label %27
    i32 3, label %31
    i32 4, label %36
    i32 5, label %43
    i32 6, label %60
  ]

18:                                               ; preds = %16
  %19 = load ptr, ptr %5, align 8
  %20 = load i32, ptr %19, align 4
  %21 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %20)
  br label %64

22:                                               ; preds = %16
  %23 = load ptr, ptr %5, align 8
  %24 = load float, ptr %23, align 4
  %25 = fpext float %24 to double
  %26 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, double noundef %25)
  br label %64

27:                                               ; preds = %16
  %28 = load ptr, ptr %5, align 8
  %29 = load double, ptr %28, align 8
  %30 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, double noundef %29)
  br label %64

31:                                               ; preds = %16
  %32 = load ptr, ptr %5, align 8
  %33 = load i8, ptr %32, align 1
  %34 = sext i8 %33 to i32
  %35 = call i32 (ptr, ...) @printf(ptr noundef @.str.17, i32 noundef %34)
  br label %64

36:                                               ; preds = %16
  %37 = load ptr, ptr %5, align 8
  %38 = load i8, ptr %37, align 1
  %39 = trunc i8 %38 to i1
  %40 = zext i1 %39 to i64
  %41 = select i1 %39, ptr @.str.3, ptr @.str.4
  %42 = call i32 (ptr, ...) @printf(ptr noundef @.str.10, ptr noundef %41)
  br label %64

43:                                               ; preds = %16
  %44 = load ptr, ptr %5, align 8
  %45 = load i8, ptr %44, align 1
  %46 = zext i8 %45 to i32
  %47 = and i32 %46, 3
  %48 = trunc i32 %47 to i8
  store i8 %48, ptr %9, align 1
  %49 = load i8, ptr %9, align 1
  %50 = zext i8 %49 to i32
  switch i32 %50, label %59 [
    i32 0, label %51
    i32 1, label %53
    i32 2, label %55
    i32 3, label %57
  ]

51:                                               ; preds = %43
  %52 = call i32 (ptr, ...) @printf(ptr noundef @.str.5)
  br label %59

53:                                               ; preds = %43
  %54 = call i32 (ptr, ...) @printf(ptr noundef @.str.6)
  br label %59

55:                                               ; preds = %43
  %56 = call i32 (ptr, ...) @printf(ptr noundef @.str.7)
  br label %59

57:                                               ; preds = %43
  %58 = call i32 (ptr, ...) @printf(ptr noundef @.str.8)
  br label %59

59:                                               ; preds = %57, %55, %53, %51, %43
  br label %64

60:                                               ; preds = %16
  %61 = load ptr, ptr %5, align 8
  %62 = load ptr, ptr %61, align 8
  %63 = call i32 (ptr, ...) @printf(ptr noundef @.str.16, ptr noundef %62)
  br label %64

64:                                               ; preds = %60, %59, %36, %31, %27, %22, %18, %16
  br label %118

65:                                               ; preds = %4
  %66 = call i32 (ptr, ...) @printf(ptr noundef @.str.13)
  %67 = load i32, ptr %6, align 4
  %68 = call i32 @sizeof_type(i32 noundef %67)
  store i32 %68, ptr %10, align 4
  store i32 1, ptr %11, align 4
  br label %69

69:                                               ; preds = %81, %65
  %70 = load i32, ptr %11, align 4
  %71 = load i32, ptr %7, align 4
  %72 = icmp slt i32 %70, %71
  br i1 %72, label %73, label %84

73:                                               ; preds = %69
  %74 = load ptr, ptr %8, align 8
  %75 = load i32, ptr %11, align 4
  %76 = sext i32 %75 to i64
  %77 = getelementptr inbounds i32, ptr %74, i64 %76
  %78 = load i32, ptr %77, align 4
  %79 = load i32, ptr %10, align 4
  %80 = mul nsw i32 %79, %78
  store i32 %80, ptr %10, align 4
  br label %81

81:                                               ; preds = %73
  %82 = load i32, ptr %11, align 4
  %83 = add nsw i32 %82, 1
  store i32 %83, ptr %11, align 4
  br label %69, !llvm.loop !24

84:                                               ; preds = %69
  store i32 0, ptr %12, align 4
  br label %85

85:                                               ; preds = %113, %84
  %86 = load i32, ptr %12, align 4
  %87 = load ptr, ptr %8, align 8
  %88 = getelementptr inbounds i32, ptr %87, i64 0
  %89 = load i32, ptr %88, align 4
  %90 = icmp slt i32 %86, %89
  br i1 %90, label %91, label %116

91:                                               ; preds = %85
  %92 = load ptr, ptr %5, align 8
  %93 = load i32, ptr %12, align 4
  %94 = load i32, ptr %10, align 4
  %95 = mul nsw i32 %93, %94
  %96 = sext i32 %95 to i64
  %97 = getelementptr inbounds i8, ptr %92, i64 %96
  store ptr %97, ptr %13, align 8
  %98 = load ptr, ptr %13, align 8
  %99 = load i32, ptr %6, align 4
  %100 = load i32, ptr %7, align 4
  %101 = sub nsw i32 %100, 1
  %102 = load ptr, ptr %8, align 8
  %103 = getelementptr inbounds i32, ptr %102, i64 1
  call void @qc_print_array_recursive(ptr noundef %98, i32 noundef %99, i32 noundef %101, ptr noundef %103)
  %104 = load i32, ptr %12, align 4
  %105 = load ptr, ptr %8, align 8
  %106 = getelementptr inbounds i32, ptr %105, i64 0
  %107 = load i32, ptr %106, align 4
  %108 = sub nsw i32 %107, 1
  %109 = icmp slt i32 %104, %108
  br i1 %109, label %110, label %112

110:                                              ; preds = %91
  %111 = call i32 (ptr, ...) @printf(ptr noundef @.str.14)
  br label %112

112:                                              ; preds = %110, %91
  br label %113

113:                                              ; preds = %112
  %114 = load i32, ptr %12, align 4
  %115 = add nsw i32 %114, 1
  store i32 %115, ptr %12, align 4
  br label %85, !llvm.loop !25

116:                                              ; preds = %85
  %117 = call i32 (ptr, ...) @printf(ptr noundef @.str.15)
  br label %118

118:                                              ; preds = %116, %64
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_create_jagged_array(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca ptr, align 8
  store i32 %0, ptr %4, align 4
  store i32 %1, ptr %5, align 4
  store i32 %2, ptr %6, align 4
  %8 = call noalias ptr @malloc(i64 noundef 32) #10
  store ptr %8, ptr %7, align 8
  %9 = load i32, ptr %4, align 4
  %10 = sext i32 %9 to i64
  %11 = mul i64 %10, 8
  %12 = call noalias ptr @malloc(i64 noundef %11) #10
  %13 = load ptr, ptr %7, align 8
  %14 = getelementptr inbounds %struct.qc_jagged_array, ptr %13, i32 0, i32 0
  store ptr %12, ptr %14, align 8
  %15 = load i32, ptr %4, align 4
  %16 = sext i32 %15 to i64
  %17 = mul i64 %16, 4
  %18 = call noalias ptr @malloc(i64 noundef %17) #10
  %19 = load ptr, ptr %7, align 8
  %20 = getelementptr inbounds %struct.qc_jagged_array, ptr %19, i32 0, i32 1
  store ptr %18, ptr %20, align 8
  %21 = load i32, ptr %4, align 4
  %22 = load ptr, ptr %7, align 8
  %23 = getelementptr inbounds %struct.qc_jagged_array, ptr %22, i32 0, i32 2
  store i32 %21, ptr %23, align 8
  %24 = load i32, ptr %5, align 4
  %25 = load ptr, ptr %7, align 8
  %26 = getelementptr inbounds %struct.qc_jagged_array, ptr %25, i32 0, i32 3
  store i32 %24, ptr %26, align 4
  %27 = load i32, ptr %6, align 4
  %28 = load ptr, ptr %7, align 8
  %29 = getelementptr inbounds %struct.qc_jagged_array, ptr %28, i32 0, i32 4
  store i32 %27, ptr %29, align 8
  %30 = load ptr, ptr %7, align 8
  ret ptr %30
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local void @qc_set_jagged_element(ptr noundef %0, i32 noundef %1, ptr noundef %2, i32 noundef %3) #0 {
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  %7 = alloca ptr, align 8
  %8 = alloca i32, align 4
  store ptr %0, ptr %5, align 8
  store i32 %1, ptr %6, align 4
  store ptr %2, ptr %7, align 8
  store i32 %3, ptr %8, align 4
  %9 = load ptr, ptr %7, align 8
  %10 = load ptr, ptr %5, align 8
  %11 = getelementptr inbounds %struct.qc_jagged_array, ptr %10, i32 0, i32 0
  %12 = load ptr, ptr %11, align 8
  %13 = load i32, ptr %6, align 4
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds ptr, ptr %12, i64 %14
  store ptr %9, ptr %15, align 8
  %16 = load i32, ptr %8, align 4
  %17 = load ptr, ptr %5, align 8
  %18 = getelementptr inbounds %struct.qc_jagged_array, ptr %17, i32 0, i32 1
  %19 = load ptr, ptr %18, align 8
  %20 = load i32, ptr %6, align 4
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds i32, ptr %19, i64 %21
  store i32 %16, ptr %22, align 4
  ret void
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_free_jagged_array(ptr noundef %0) #5 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store ptr %0, ptr %2, align 8
  %5 = load ptr, ptr %2, align 8
  %6 = getelementptr inbounds %struct.qc_jagged_array, ptr %5, i32 0, i32 4
  %7 = load i32, ptr %6, align 8
  %8 = icmp sgt i32 %7, 0
  br i1 %8, label %9, label %28

9:                                                ; preds = %1
  store i32 0, ptr %3, align 4
  br label %10

10:                                               ; preds = %24, %9
  %11 = load i32, ptr %3, align 4
  %12 = load ptr, ptr %2, align 8
  %13 = getelementptr inbounds %struct.qc_jagged_array, ptr %12, i32 0, i32 2
  %14 = load i32, ptr %13, align 8
  %15 = icmp slt i32 %11, %14
  br i1 %15, label %16, label %27

16:                                               ; preds = %10
  %17 = load ptr, ptr %2, align 8
  %18 = getelementptr inbounds %struct.qc_jagged_array, ptr %17, i32 0, i32 0
  %19 = load ptr, ptr %18, align 8
  %20 = load i32, ptr %3, align 4
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds ptr, ptr %19, i64 %21
  %23 = load ptr, ptr %22, align 8
  call void @qc_free_jagged_array(ptr noundef %23)
  br label %24

24:                                               ; preds = %16
  %25 = load i32, ptr %3, align 4
  %26 = add nsw i32 %25, 1
  store i32 %26, ptr %3, align 4
  br label %10, !llvm.loop !26

27:                                               ; preds = %10
  br label %47

28:                                               ; preds = %1
  store i32 0, ptr %4, align 4
  br label %29

29:                                               ; preds = %43, %28
  %30 = load i32, ptr %4, align 4
  %31 = load ptr, ptr %2, align 8
  %32 = getelementptr inbounds %struct.qc_jagged_array, ptr %31, i32 0, i32 2
  %33 = load i32, ptr %32, align 8
  %34 = icmp slt i32 %30, %33
  br i1 %34, label %35, label %46

35:                                               ; preds = %29
  %36 = load ptr, ptr %2, align 8
  %37 = getelementptr inbounds %struct.qc_jagged_array, ptr %36, i32 0, i32 0
  %38 = load ptr, ptr %37, align 8
  %39 = load i32, ptr %4, align 4
  %40 = sext i32 %39 to i64
  %41 = getelementptr inbounds ptr, ptr %38, i64 %40
  %42 = load ptr, ptr %41, align 8
  call void @free(ptr noundef %42) #11
  br label %43

43:                                               ; preds = %35
  %44 = load i32, ptr %4, align 4
  %45 = add nsw i32 %44, 1
  store i32 %45, ptr %4, align 4
  br label %29, !llvm.loop !27

46:                                               ; preds = %29
  br label %47

47:                                               ; preds = %46, %27
  %48 = load ptr, ptr %2, align 8
  %49 = getelementptr inbounds %struct.qc_jagged_array, ptr %48, i32 0, i32 0
  %50 = load ptr, ptr %49, align 8
  call void @free(ptr noundef %50) #11
  %51 = load ptr, ptr %2, align 8
  %52 = getelementptr inbounds %struct.qc_jagged_array, ptr %51, i32 0, i32 1
  %53 = load ptr, ptr %52, align 8
  call void @free(ptr noundef %53) #11
  %54 = load ptr, ptr %2, align 8
  call void @free(ptr noundef %54) #11
  ret void
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print_jagged_array_recursive(ptr noundef %0) #5 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  %4 = alloca ptr, align 8
  %5 = alloca i32, align 4
  %6 = alloca ptr, align 8
  %7 = alloca i8, align 1
  store ptr %0, ptr %2, align 8
  %8 = call i32 (ptr, ...) @printf(ptr noundef @.str.13)
  store i32 0, ptr %3, align 4
  br label %9

9:                                                ; preds = %152, %1
  %10 = load i32, ptr %3, align 4
  %11 = load ptr, ptr %2, align 8
  %12 = getelementptr inbounds %struct.qc_jagged_array, ptr %11, i32 0, i32 2
  %13 = load i32, ptr %12, align 8
  %14 = icmp slt i32 %10, %13
  br i1 %14, label %15, label %155

15:                                               ; preds = %9
  %16 = load ptr, ptr %2, align 8
  %17 = getelementptr inbounds %struct.qc_jagged_array, ptr %16, i32 0, i32 4
  %18 = load i32, ptr %17, align 8
  %19 = icmp sgt i32 %18, 1
  br i1 %19, label %20, label %28

20:                                               ; preds = %15
  %21 = load ptr, ptr %2, align 8
  %22 = getelementptr inbounds %struct.qc_jagged_array, ptr %21, i32 0, i32 0
  %23 = load ptr, ptr %22, align 8
  %24 = load i32, ptr %3, align 4
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds ptr, ptr %23, i64 %25
  %27 = load ptr, ptr %26, align 8
  call void @qc_print_jagged_array_recursive(ptr noundef %27)
  br label %142

28:                                               ; preds = %15
  %29 = load ptr, ptr %2, align 8
  %30 = getelementptr inbounds %struct.qc_jagged_array, ptr %29, i32 0, i32 4
  %31 = load i32, ptr %30, align 8
  %32 = icmp eq i32 %31, 1
  br i1 %32, label %33, label %139

33:                                               ; preds = %28
  %34 = load ptr, ptr %2, align 8
  %35 = getelementptr inbounds %struct.qc_jagged_array, ptr %34, i32 0, i32 0
  %36 = load ptr, ptr %35, align 8
  %37 = load i32, ptr %3, align 4
  %38 = sext i32 %37 to i64
  %39 = getelementptr inbounds ptr, ptr %36, i64 %38
  %40 = load ptr, ptr %39, align 8
  store ptr %40, ptr %4, align 8
  %41 = call i32 (ptr, ...) @printf(ptr noundef @.str.13)
  store i32 0, ptr %5, align 4
  br label %42

42:                                               ; preds = %134, %33
  %43 = load i32, ptr %5, align 4
  %44 = load ptr, ptr %2, align 8
  %45 = getelementptr inbounds %struct.qc_jagged_array, ptr %44, i32 0, i32 1
  %46 = load ptr, ptr %45, align 8
  %47 = load i32, ptr %3, align 4
  %48 = sext i32 %47 to i64
  %49 = getelementptr inbounds i32, ptr %46, i64 %48
  %50 = load i32, ptr %49, align 4
  %51 = icmp slt i32 %43, %50
  br i1 %51, label %52, label %137

52:                                               ; preds = %42
  %53 = load ptr, ptr %4, align 8
  %54 = load i32, ptr %5, align 4
  %55 = load ptr, ptr %2, align 8
  %56 = getelementptr inbounds %struct.qc_jagged_array, ptr %55, i32 0, i32 3
  %57 = load i32, ptr %56, align 4
  %58 = call i32 @sizeof_type(i32 noundef %57)
  %59 = mul nsw i32 %54, %58
  %60 = sext i32 %59 to i64
  %61 = getelementptr inbounds i8, ptr %53, i64 %60
  store ptr %61, ptr %6, align 8
  %62 = load ptr, ptr %2, align 8
  %63 = getelementptr inbounds %struct.qc_jagged_array, ptr %62, i32 0, i32 3
  %64 = load i32, ptr %63, align 4
  switch i32 %64, label %120 [
    i32 0, label %65
    i32 1, label %69
    i32 2, label %74
    i32 3, label %78
    i32 4, label %83
    i32 5, label %90
    i32 6, label %116
  ]

65:                                               ; preds = %52
  %66 = load ptr, ptr %6, align 8
  %67 = load i32, ptr %66, align 4
  %68 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %67)
  br label %120

69:                                               ; preds = %52
  %70 = load ptr, ptr %6, align 8
  %71 = load float, ptr %70, align 4
  %72 = fpext float %71 to double
  %73 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, double noundef %72)
  br label %120

74:                                               ; preds = %52
  %75 = load ptr, ptr %6, align 8
  %76 = load double, ptr %75, align 8
  %77 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, double noundef %76)
  br label %120

78:                                               ; preds = %52
  %79 = load ptr, ptr %6, align 8
  %80 = load i8, ptr %79, align 1
  %81 = sext i8 %80 to i32
  %82 = call i32 (ptr, ...) @printf(ptr noundef @.str.17, i32 noundef %81)
  br label %120

83:                                               ; preds = %52
  %84 = load ptr, ptr %6, align 8
  %85 = load i8, ptr %84, align 1
  %86 = trunc i8 %85 to i1
  %87 = zext i1 %86 to i64
  %88 = select i1 %86, ptr @.str.3, ptr @.str.4
  %89 = call i32 (ptr, ...) @printf(ptr noundef @.str.10, ptr noundef %88)
  br label %120

90:                                               ; preds = %52
  %91 = load ptr, ptr %6, align 8
  %92 = load i8, ptr %91, align 1
  %93 = zext i8 %92 to i32
  %94 = and i32 %93, 3
  %95 = trunc i32 %94 to i8
  store i8 %95, ptr %7, align 1
  %96 = load i8, ptr %7, align 1
  %97 = zext i8 %96 to i32
  %98 = icmp eq i32 %97, 0
  br i1 %98, label %99, label %100

99:                                               ; preds = %90
  br label %113

100:                                              ; preds = %90
  %101 = load i8, ptr %7, align 1
  %102 = zext i8 %101 to i32
  %103 = icmp eq i32 %102, 1
  br i1 %103, label %104, label %105

104:                                              ; preds = %100
  br label %111

105:                                              ; preds = %100
  %106 = load i8, ptr %7, align 1
  %107 = zext i8 %106 to i32
  %108 = icmp eq i32 %107, 2
  %109 = zext i1 %108 to i64
  %110 = select i1 %108, ptr @.str.7, ptr @.str.8
  br label %111

111:                                              ; preds = %105, %104
  %112 = phi ptr [ @.str.6, %104 ], [ %110, %105 ]
  br label %113

113:                                              ; preds = %111, %99
  %114 = phi ptr [ @.str.5, %99 ], [ %112, %111 ]
  %115 = call i32 (ptr, ...) @printf(ptr noundef @.str.10, ptr noundef %114)
  br label %120

116:                                              ; preds = %52
  %117 = load ptr, ptr %6, align 8
  %118 = load ptr, ptr %117, align 8
  %119 = call i32 (ptr, ...) @printf(ptr noundef @.str.16, ptr noundef %118)
  br label %120

120:                                              ; preds = %116, %113, %83, %78, %74, %69, %65, %52
  %121 = load i32, ptr %5, align 4
  %122 = load ptr, ptr %2, align 8
  %123 = getelementptr inbounds %struct.qc_jagged_array, ptr %122, i32 0, i32 1
  %124 = load ptr, ptr %123, align 8
  %125 = load i32, ptr %3, align 4
  %126 = sext i32 %125 to i64
  %127 = getelementptr inbounds i32, ptr %124, i64 %126
  %128 = load i32, ptr %127, align 4
  %129 = sub nsw i32 %128, 1
  %130 = icmp slt i32 %121, %129
  br i1 %130, label %131, label %133

131:                                              ; preds = %120
  %132 = call i32 (ptr, ...) @printf(ptr noundef @.str.14)
  br label %133

133:                                              ; preds = %131, %120
  br label %134

134:                                              ; preds = %133
  %135 = load i32, ptr %5, align 4
  %136 = add nsw i32 %135, 1
  store i32 %136, ptr %5, align 4
  br label %42, !llvm.loop !28

137:                                              ; preds = %42
  %138 = call i32 (ptr, ...) @printf(ptr noundef @.str.15)
  br label %141

139:                                              ; preds = %28
  %140 = call i32 (ptr, ...) @printf(ptr noundef @.str.18)
  br label %141

141:                                              ; preds = %139, %137
  br label %142

142:                                              ; preds = %141, %20
  %143 = load i32, ptr %3, align 4
  %144 = load ptr, ptr %2, align 8
  %145 = getelementptr inbounds %struct.qc_jagged_array, ptr %144, i32 0, i32 2
  %146 = load i32, ptr %145, align 8
  %147 = sub nsw i32 %146, 1
  %148 = icmp slt i32 %143, %147
  br i1 %148, label %149, label %151

149:                                              ; preds = %142
  %150 = call i32 (ptr, ...) @printf(ptr noundef @.str.14)
  br label %151

151:                                              ; preds = %149, %142
  br label %152

152:                                              ; preds = %151
  %153 = load i32, ptr %3, align 4
  %154 = add nsw i32 %153, 1
  store i32 %154, ptr %3, align 4
  br label %9, !llvm.loop !29

155:                                              ; preds = %9
  %156 = call i32 (ptr, ...) @printf(ptr noundef @.str.15)
  ret void
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local ptr @qc_jagged_array_get(ptr noundef %0, ptr noundef %1, i32 noundef %2) #5 {
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca ptr, align 8
  %11 = alloca ptr, align 8
  %12 = alloca i32, align 4
  %13 = alloca ptr, align 8
  store ptr %0, ptr %5, align 8
  store ptr %1, ptr %6, align 8
  store i32 %2, ptr %7, align 4
  %14 = load i32, ptr %7, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %19, label %16

16:                                               ; preds = %3
  %17 = load ptr, ptr %5, align 8
  %18 = icmp ne ptr %17, null
  br i1 %18, label %20, label %19

19:                                               ; preds = %16, %3
  store ptr null, ptr %4, align 8
  br label %145

20:                                               ; preds = %16
  %21 = load ptr, ptr %6, align 8
  %22 = getelementptr inbounds i32, ptr %21, i64 0
  %23 = load i32, ptr %22, align 4
  store i32 %23, ptr %8, align 4
  %24 = load i32, ptr %8, align 4
  %25 = icmp slt i32 %24, 0
  br i1 %25, label %32, label %26

26:                                               ; preds = %20
  %27 = load i32, ptr %8, align 4
  %28 = load ptr, ptr %5, align 8
  %29 = getelementptr inbounds %struct.qc_jagged_array, ptr %28, i32 0, i32 2
  %30 = load i32, ptr %29, align 8
  %31 = icmp sge i32 %27, %30
  br i1 %31, label %32, label %33

32:                                               ; preds = %26, %20
  store ptr null, ptr %4, align 8
  br label %145

33:                                               ; preds = %26
  %34 = load ptr, ptr %5, align 8
  %35 = getelementptr inbounds %struct.qc_jagged_array, ptr %34, i32 0, i32 4
  %36 = load i32, ptr %35, align 8
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %38, label %83

38:                                               ; preds = %33
  %39 = load i32, ptr %7, align 4
  %40 = icmp eq i32 %39, 1
  br i1 %40, label %41, label %49

41:                                               ; preds = %38
  %42 = load ptr, ptr %5, align 8
  %43 = getelementptr inbounds %struct.qc_jagged_array, ptr %42, i32 0, i32 0
  %44 = load ptr, ptr %43, align 8
  %45 = load i32, ptr %8, align 4
  %46 = sext i32 %45 to i64
  %47 = getelementptr inbounds ptr, ptr %44, i64 %46
  %48 = load ptr, ptr %47, align 8
  store ptr %48, ptr %4, align 8
  br label %145

49:                                               ; preds = %38
  %50 = load ptr, ptr %6, align 8
  %51 = getelementptr inbounds i32, ptr %50, i64 1
  %52 = load i32, ptr %51, align 4
  store i32 %52, ptr %9, align 4
  %53 = load i32, ptr %9, align 4
  %54 = icmp slt i32 %53, 0
  br i1 %54, label %65, label %55

55:                                               ; preds = %49
  %56 = load i32, ptr %9, align 4
  %57 = load ptr, ptr %5, align 8
  %58 = getelementptr inbounds %struct.qc_jagged_array, ptr %57, i32 0, i32 1
  %59 = load ptr, ptr %58, align 8
  %60 = load i32, ptr %8, align 4
  %61 = sext i32 %60 to i64
  %62 = getelementptr inbounds i32, ptr %59, i64 %61
  %63 = load i32, ptr %62, align 4
  %64 = icmp sge i32 %56, %63
  br i1 %64, label %65, label %66

65:                                               ; preds = %55, %49
  store ptr null, ptr %4, align 8
  br label %145

66:                                               ; preds = %55
  %67 = load ptr, ptr %5, align 8
  %68 = getelementptr inbounds %struct.qc_jagged_array, ptr %67, i32 0, i32 0
  %69 = load ptr, ptr %68, align 8
  %70 = load i32, ptr %8, align 4
  %71 = sext i32 %70 to i64
  %72 = getelementptr inbounds ptr, ptr %69, i64 %71
  %73 = load ptr, ptr %72, align 8
  store ptr %73, ptr %10, align 8
  %74 = load ptr, ptr %10, align 8
  %75 = load i32, ptr %9, align 4
  %76 = load ptr, ptr %5, align 8
  %77 = getelementptr inbounds %struct.qc_jagged_array, ptr %76, i32 0, i32 3
  %78 = load i32, ptr %77, align 4
  %79 = call i32 @sizeof_type(i32 noundef %78)
  %80 = mul nsw i32 %75, %79
  %81 = sext i32 %80 to i64
  %82 = getelementptr inbounds i8, ptr %74, i64 %81
  store ptr %82, ptr %4, align 8
  br label %145

83:                                               ; preds = %33
  %84 = load ptr, ptr %5, align 8
  %85 = getelementptr inbounds %struct.qc_jagged_array, ptr %84, i32 0, i32 4
  %86 = load i32, ptr %85, align 8
  %87 = icmp eq i32 %86, 1
  br i1 %87, label %88, label %127

88:                                               ; preds = %83
  %89 = load ptr, ptr %5, align 8
  %90 = getelementptr inbounds %struct.qc_jagged_array, ptr %89, i32 0, i32 0
  %91 = load ptr, ptr %90, align 8
  %92 = load i32, ptr %8, align 4
  %93 = sext i32 %92 to i64
  %94 = getelementptr inbounds ptr, ptr %91, i64 %93
  %95 = load ptr, ptr %94, align 8
  store ptr %95, ptr %11, align 8
  %96 = load i32, ptr %7, align 4
  %97 = icmp eq i32 %96, 1
  br i1 %97, label %98, label %100

98:                                               ; preds = %88
  %99 = load ptr, ptr %11, align 8
  store ptr %99, ptr %4, align 8
  br label %145

100:                                              ; preds = %88
  %101 = load ptr, ptr %6, align 8
  %102 = getelementptr inbounds i32, ptr %101, i64 1
  %103 = load i32, ptr %102, align 4
  store i32 %103, ptr %12, align 4
  %104 = load i32, ptr %12, align 4
  %105 = icmp slt i32 %104, 0
  br i1 %105, label %116, label %106

106:                                              ; preds = %100
  %107 = load i32, ptr %12, align 4
  %108 = load ptr, ptr %5, align 8
  %109 = getelementptr inbounds %struct.qc_jagged_array, ptr %108, i32 0, i32 1
  %110 = load ptr, ptr %109, align 8
  %111 = load i32, ptr %8, align 4
  %112 = sext i32 %111 to i64
  %113 = getelementptr inbounds i32, ptr %110, i64 %112
  %114 = load i32, ptr %113, align 4
  %115 = icmp sge i32 %107, %114
  br i1 %115, label %116, label %117

116:                                              ; preds = %106, %100
  store ptr null, ptr %4, align 8
  br label %145

117:                                              ; preds = %106
  %118 = load ptr, ptr %11, align 8
  %119 = load i32, ptr %12, align 4
  %120 = load ptr, ptr %5, align 8
  %121 = getelementptr inbounds %struct.qc_jagged_array, ptr %120, i32 0, i32 3
  %122 = load i32, ptr %121, align 4
  %123 = call i32 @sizeof_type(i32 noundef %122)
  %124 = mul nsw i32 %119, %123
  %125 = sext i32 %124 to i64
  %126 = getelementptr inbounds i8, ptr %118, i64 %125
  store ptr %126, ptr %4, align 8
  br label %145

127:                                              ; preds = %83
  %128 = load ptr, ptr %5, align 8
  %129 = getelementptr inbounds %struct.qc_jagged_array, ptr %128, i32 0, i32 0
  %130 = load ptr, ptr %129, align 8
  %131 = load i32, ptr %8, align 4
  %132 = sext i32 %131 to i64
  %133 = getelementptr inbounds ptr, ptr %130, i64 %132
  %134 = load ptr, ptr %133, align 8
  store ptr %134, ptr %13, align 8
  %135 = load ptr, ptr %13, align 8
  %136 = icmp ne ptr %135, null
  br i1 %136, label %138, label %137

137:                                              ; preds = %127
  store ptr null, ptr %4, align 8
  br label %145

138:                                              ; preds = %127
  %139 = load ptr, ptr %13, align 8
  %140 = load ptr, ptr %6, align 8
  %141 = getelementptr inbounds i32, ptr %140, i64 1
  %142 = load i32, ptr %7, align 4
  %143 = sub nsw i32 %142, 1
  %144 = call ptr @qc_jagged_array_get(ptr noundef %139, ptr noundef %141, i32 noundef %143)
  store ptr %144, ptr %4, align 8
  br label %145

145:                                              ; preds = %138, %137, %117, %116, %98, %66, %65, %41, %32, %19
  %146 = load ptr, ptr %4, align 8
  ret ptr %146
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_create_leaf_row(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca ptr, align 8
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %4, align 4
  %8 = load i32, ptr %4, align 4
  %9 = call i32 @sizeof_type(i32 noundef %8)
  store i32 %9, ptr %5, align 4
  %10 = load i32, ptr %3, align 4
  %11 = load i32, ptr %5, align 4
  %12 = mul nsw i32 %10, %11
  store i32 %12, ptr %6, align 4
  %13 = load i32, ptr %6, align 4
  %14 = sext i32 %13 to i64
  %15 = call noalias ptr @malloc(i64 noundef %14) #10
  store ptr %15, ptr %7, align 8
  %16 = load ptr, ptr %7, align 8
  ret ptr %16
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local void @qc_set_leaf_element(ptr noundef %0, i32 noundef %1, ptr noundef %2, i32 noundef %3) #0 {
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  %7 = alloca ptr, align 8
  %8 = alloca i32, align 4
  %9 = alloca ptr, align 8
  store ptr %0, ptr %5, align 8
  store i32 %1, ptr %6, align 4
  store ptr %2, ptr %7, align 8
  store i32 %3, ptr %8, align 4
  %10 = load ptr, ptr %5, align 8
  %11 = load i32, ptr %6, align 4
  %12 = load i32, ptr %8, align 4
  %13 = call i32 @sizeof_type(i32 noundef %12)
  %14 = mul nsw i32 %11, %13
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds i8, ptr %10, i64 %15
  store ptr %16, ptr %9, align 8
  %17 = load ptr, ptr %9, align 8
  %18 = load ptr, ptr %7, align 8
  %19 = load i32, ptr %8, align 4
  %20 = call i32 @sizeof_type(i32 noundef %19)
  %21 = sext i32 %20 to i64
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %17, ptr align 1 %18, i64 %21, i1 false)
  ret void
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local ptr @qc_jagged_to_string(ptr noundef %0) #5 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  store ptr %0, ptr %2, align 8
  store i32 1024, ptr %3, align 4
  %7 = load i32, ptr %3, align 4
  %8 = sext i32 %7 to i64
  %9 = call noalias ptr @malloc(i64 noundef %8) #10
  store ptr %9, ptr %4, align 8
  %10 = load ptr, ptr %4, align 8
  store ptr %10, ptr %5, align 8
  %11 = load i32, ptr %3, align 4
  store i32 %11, ptr %6, align 4
  %12 = load ptr, ptr %2, align 8
  call void @_ZL23stringify_jagged_helperP15qc_jagged_arrayPPcPiS3_S2_(ptr noundef %12, ptr noundef %5, ptr noundef %6, ptr noundef %3, ptr noundef %4)
  %13 = load ptr, ptr %5, align 8
  store i8 0, ptr %13, align 1
  %14 = load ptr, ptr %4, align 8
  ret ptr %14
}

; Function Attrs: mustprogress noinline optnone uwtable
define internal void @_ZL23stringify_jagged_helperP15qc_jagged_arrayPPcPiS3_S2_(ptr noundef %0, ptr noundef %1, ptr noundef %2, ptr noundef %3, ptr noundef %4) #5 {
  %6 = alloca ptr, align 8
  %7 = alloca ptr, align 8
  %8 = alloca ptr, align 8
  %9 = alloca ptr, align 8
  %10 = alloca ptr, align 8
  %11 = alloca i32, align 4
  %12 = alloca ptr, align 8
  %13 = alloca i32, align 4
  %14 = alloca ptr, align 8
  %15 = alloca [64 x i8], align 16
  %16 = alloca i8, align 1
  %17 = alloca i32, align 4
  %18 = alloca i32, align 4
  store ptr %0, ptr %6, align 8
  store ptr %1, ptr %7, align 8
  store ptr %2, ptr %8, align 8
  store ptr %3, ptr %9, align 8
  store ptr %4, ptr %10, align 8
  %19 = load ptr, ptr %7, align 8
  %20 = load ptr, ptr %19, align 8
  store i8 91, ptr %20, align 1
  %21 = load ptr, ptr %7, align 8
  %22 = load ptr, ptr %21, align 8
  %23 = getelementptr inbounds i8, ptr %22, i32 1
  store ptr %23, ptr %21, align 8
  %24 = load ptr, ptr %8, align 8
  %25 = load i32, ptr %24, align 4
  %26 = add nsw i32 %25, -1
  store i32 %26, ptr %24, align 4
  store i32 0, ptr %11, align 4
  br label %27

27:                                               ; preds = %263, %5
  %28 = load i32, ptr %11, align 4
  %29 = load ptr, ptr %6, align 8
  %30 = getelementptr inbounds %struct.qc_jagged_array, ptr %29, i32 0, i32 2
  %31 = load i32, ptr %30, align 8
  %32 = icmp slt i32 %28, %31
  br i1 %32, label %33, label %266

33:                                               ; preds = %27
  %34 = load ptr, ptr %6, align 8
  %35 = getelementptr inbounds %struct.qc_jagged_array, ptr %34, i32 0, i32 4
  %36 = load i32, ptr %35, align 8
  %37 = icmp sgt i32 %36, 0
  br i1 %37, label %38, label %50

38:                                               ; preds = %33
  %39 = load ptr, ptr %6, align 8
  %40 = getelementptr inbounds %struct.qc_jagged_array, ptr %39, i32 0, i32 0
  %41 = load ptr, ptr %40, align 8
  %42 = load i32, ptr %11, align 4
  %43 = sext i32 %42 to i64
  %44 = getelementptr inbounds ptr, ptr %41, i64 %43
  %45 = load ptr, ptr %44, align 8
  %46 = load ptr, ptr %7, align 8
  %47 = load ptr, ptr %8, align 8
  %48 = load ptr, ptr %9, align 8
  %49 = load ptr, ptr %10, align 8
  call void @_ZL23stringify_jagged_helperP15qc_jagged_arrayPPcPiS3_S2_(ptr noundef %45, ptr noundef %46, ptr noundef %47, ptr noundef %48, ptr noundef %49)
  br label %241

50:                                               ; preds = %33
  %51 = load ptr, ptr %7, align 8
  %52 = load ptr, ptr %51, align 8
  store i8 91, ptr %52, align 1
  %53 = load ptr, ptr %7, align 8
  %54 = load ptr, ptr %53, align 8
  %55 = getelementptr inbounds i8, ptr %54, i32 1
  store ptr %55, ptr %53, align 8
  %56 = load ptr, ptr %8, align 8
  %57 = load i32, ptr %56, align 4
  %58 = add nsw i32 %57, -1
  store i32 %58, ptr %56, align 4
  %59 = load ptr, ptr %6, align 8
  %60 = getelementptr inbounds %struct.qc_jagged_array, ptr %59, i32 0, i32 0
  %61 = load ptr, ptr %60, align 8
  %62 = load i32, ptr %11, align 4
  %63 = sext i32 %62 to i64
  %64 = getelementptr inbounds ptr, ptr %61, i64 %63
  %65 = load ptr, ptr %64, align 8
  store ptr %65, ptr %12, align 8
  store i32 0, ptr %13, align 4
  br label %66

66:                                               ; preds = %229, %50
  %67 = load i32, ptr %13, align 4
  %68 = load ptr, ptr %6, align 8
  %69 = getelementptr inbounds %struct.qc_jagged_array, ptr %68, i32 0, i32 1
  %70 = load ptr, ptr %69, align 8
  %71 = load i32, ptr %11, align 4
  %72 = sext i32 %71 to i64
  %73 = getelementptr inbounds i32, ptr %70, i64 %72
  %74 = load i32, ptr %73, align 4
  %75 = icmp slt i32 %67, %74
  br i1 %75, label %76, label %232

76:                                               ; preds = %66
  %77 = load ptr, ptr %12, align 8
  %78 = load i32, ptr %13, align 4
  %79 = load ptr, ptr %6, align 8
  %80 = getelementptr inbounds %struct.qc_jagged_array, ptr %79, i32 0, i32 3
  %81 = load i32, ptr %80, align 4
  %82 = call i32 @sizeof_type(i32 noundef %81)
  %83 = mul nsw i32 %78, %82
  %84 = sext i32 %83 to i64
  %85 = getelementptr inbounds i8, ptr %77, i64 %84
  store ptr %85, ptr %14, align 8
  %86 = load ptr, ptr %6, align 8
  %87 = getelementptr inbounds %struct.qc_jagged_array, ptr %86, i32 0, i32 3
  %88 = load i32, ptr %87, align 4
  switch i32 %88, label %151 [
    i32 0, label %89
    i32 1, label %94
    i32 2, label %100
    i32 3, label %105
    i32 4, label %111
    i32 5, label %119
    i32 6, label %146
  ]

89:                                               ; preds = %76
  %90 = getelementptr inbounds [64 x i8], ptr %15, i64 0, i64 0
  %91 = load ptr, ptr %14, align 8
  %92 = load i32, ptr %91, align 4
  %93 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %90, i64 noundef 64, ptr noundef @.str.1, i32 noundef %92) #11
  br label %151

94:                                               ; preds = %76
  %95 = getelementptr inbounds [64 x i8], ptr %15, i64 0, i64 0
  %96 = load ptr, ptr %14, align 8
  %97 = load float, ptr %96, align 4
  %98 = fpext float %97 to double
  %99 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %95, i64 noundef 64, ptr noundef @.str.2, double noundef %98) #11
  br label %151

100:                                              ; preds = %76
  %101 = getelementptr inbounds [64 x i8], ptr %15, i64 0, i64 0
  %102 = load ptr, ptr %14, align 8
  %103 = load double, ptr %102, align 8
  %104 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %101, i64 noundef 64, ptr noundef @.str.2, double noundef %103) #11
  br label %151

105:                                              ; preds = %76
  %106 = getelementptr inbounds [64 x i8], ptr %15, i64 0, i64 0
  %107 = load ptr, ptr %14, align 8
  %108 = load i8, ptr %107, align 1
  %109 = sext i8 %108 to i32
  %110 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %106, i64 noundef 64, ptr noundef @.str.17, i32 noundef %109) #11
  br label %151

111:                                              ; preds = %76
  %112 = getelementptr inbounds [64 x i8], ptr %15, i64 0, i64 0
  %113 = load ptr, ptr %14, align 8
  %114 = load i8, ptr %113, align 1
  %115 = trunc i8 %114 to i1
  %116 = zext i1 %115 to i64
  %117 = select i1 %115, ptr @.str.3, ptr @.str.4
  %118 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %112, i64 noundef 64, ptr noundef @.str.10, ptr noundef %117) #11
  br label %151

119:                                              ; preds = %76
  %120 = load ptr, ptr %14, align 8
  %121 = load i8, ptr %120, align 1
  %122 = zext i8 %121 to i32
  %123 = and i32 %122, 3
  %124 = trunc i32 %123 to i8
  store i8 %124, ptr %16, align 1
  %125 = getelementptr inbounds [64 x i8], ptr %15, i64 0, i64 0
  %126 = load i8, ptr %16, align 1
  %127 = zext i8 %126 to i32
  %128 = icmp eq i32 %127, 0
  br i1 %128, label %129, label %130

129:                                              ; preds = %119
  br label %143

130:                                              ; preds = %119
  %131 = load i8, ptr %16, align 1
  %132 = zext i8 %131 to i32
  %133 = icmp eq i32 %132, 1
  br i1 %133, label %134, label %135

134:                                              ; preds = %130
  br label %141

135:                                              ; preds = %130
  %136 = load i8, ptr %16, align 1
  %137 = zext i8 %136 to i32
  %138 = icmp eq i32 %137, 2
  %139 = zext i1 %138 to i64
  %140 = select i1 %138, ptr @.str.7, ptr @.str.8
  br label %141

141:                                              ; preds = %135, %134
  %142 = phi ptr [ @.str.6, %134 ], [ %140, %135 ]
  br label %143

143:                                              ; preds = %141, %129
  %144 = phi ptr [ @.str.5, %129 ], [ %142, %141 ]
  %145 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %125, i64 noundef 64, ptr noundef @.str.10, ptr noundef %144) #11
  br label %151

146:                                              ; preds = %76
  %147 = getelementptr inbounds [64 x i8], ptr %15, i64 0, i64 0
  %148 = load ptr, ptr %14, align 8
  %149 = load ptr, ptr %148, align 8
  %150 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %147, i64 noundef 64, ptr noundef @.str.16, ptr noundef %149) #11
  br label %151

151:                                              ; preds = %146, %143, %111, %105, %100, %94, %89, %76
  %152 = getelementptr inbounds [64 x i8], ptr %15, i64 0, i64 0
  %153 = call i64 @strlen(ptr noundef %152) #9
  %154 = trunc i64 %153 to i32
  store i32 %154, ptr %17, align 4
  %155 = load ptr, ptr %8, align 8
  %156 = load i32, ptr %155, align 4
  %157 = load i32, ptr %17, align 4
  %158 = add nsw i32 %157, 10
  %159 = icmp slt i32 %156, %158
  br i1 %159, label %160, label %190

160:                                              ; preds = %151
  %161 = load ptr, ptr %7, align 8
  %162 = load ptr, ptr %161, align 8
  %163 = load ptr, ptr %10, align 8
  %164 = load ptr, ptr %163, align 8
  %165 = ptrtoint ptr %162 to i64
  %166 = ptrtoint ptr %164 to i64
  %167 = sub i64 %165, %166
  %168 = trunc i64 %167 to i32
  store i32 %168, ptr %18, align 4
  %169 = load ptr, ptr %9, align 8
  %170 = load i32, ptr %169, align 4
  %171 = mul nsw i32 %170, 2
  store i32 %171, ptr %169, align 4
  %172 = load ptr, ptr %10, align 8
  %173 = load ptr, ptr %172, align 8
  %174 = load ptr, ptr %9, align 8
  %175 = load i32, ptr %174, align 4
  %176 = sext i32 %175 to i64
  %177 = call ptr @realloc(ptr noundef %173, i64 noundef %176) #12
  %178 = load ptr, ptr %10, align 8
  store ptr %177, ptr %178, align 8
  %179 = load ptr, ptr %10, align 8
  %180 = load ptr, ptr %179, align 8
  %181 = load i32, ptr %18, align 4
  %182 = sext i32 %181 to i64
  %183 = getelementptr inbounds i8, ptr %180, i64 %182
  %184 = load ptr, ptr %7, align 8
  store ptr %183, ptr %184, align 8
  %185 = load ptr, ptr %9, align 8
  %186 = load i32, ptr %185, align 4
  %187 = load i32, ptr %18, align 4
  %188 = sub nsw i32 %186, %187
  %189 = load ptr, ptr %8, align 8
  store i32 %188, ptr %189, align 4
  br label %190

190:                                              ; preds = %160, %151
  %191 = load ptr, ptr %7, align 8
  %192 = load ptr, ptr %191, align 8
  %193 = getelementptr inbounds [64 x i8], ptr %15, i64 0, i64 0
  %194 = call ptr @strcpy(ptr noundef %192, ptr noundef %193) #11
  %195 = load i32, ptr %17, align 4
  %196 = load ptr, ptr %7, align 8
  %197 = load ptr, ptr %196, align 8
  %198 = sext i32 %195 to i64
  %199 = getelementptr inbounds i8, ptr %197, i64 %198
  store ptr %199, ptr %196, align 8
  %200 = load i32, ptr %17, align 4
  %201 = load ptr, ptr %8, align 8
  %202 = load i32, ptr %201, align 4
  %203 = sub nsw i32 %202, %200
  store i32 %203, ptr %201, align 4
  %204 = load i32, ptr %13, align 4
  %205 = load ptr, ptr %6, align 8
  %206 = getelementptr inbounds %struct.qc_jagged_array, ptr %205, i32 0, i32 1
  %207 = load ptr, ptr %206, align 8
  %208 = load i32, ptr %11, align 4
  %209 = sext i32 %208 to i64
  %210 = getelementptr inbounds i32, ptr %207, i64 %209
  %211 = load i32, ptr %210, align 4
  %212 = sub nsw i32 %211, 1
  %213 = icmp slt i32 %204, %212
  br i1 %213, label %214, label %228

214:                                              ; preds = %190
  %215 = load ptr, ptr %7, align 8
  %216 = load ptr, ptr %215, align 8
  store i8 44, ptr %216, align 1
  %217 = load ptr, ptr %7, align 8
  %218 = load ptr, ptr %217, align 8
  %219 = getelementptr inbounds i8, ptr %218, i32 1
  store ptr %219, ptr %217, align 8
  %220 = load ptr, ptr %7, align 8
  %221 = load ptr, ptr %220, align 8
  store i8 32, ptr %221, align 1
  %222 = load ptr, ptr %7, align 8
  %223 = load ptr, ptr %222, align 8
  %224 = getelementptr inbounds i8, ptr %223, i32 1
  store ptr %224, ptr %222, align 8
  %225 = load ptr, ptr %8, align 8
  %226 = load i32, ptr %225, align 4
  %227 = sub nsw i32 %226, 2
  store i32 %227, ptr %225, align 4
  br label %228

228:                                              ; preds = %214, %190
  br label %229

229:                                              ; preds = %228
  %230 = load i32, ptr %13, align 4
  %231 = add nsw i32 %230, 1
  store i32 %231, ptr %13, align 4
  br label %66, !llvm.loop !30

232:                                              ; preds = %66
  %233 = load ptr, ptr %7, align 8
  %234 = load ptr, ptr %233, align 8
  store i8 93, ptr %234, align 1
  %235 = load ptr, ptr %7, align 8
  %236 = load ptr, ptr %235, align 8
  %237 = getelementptr inbounds i8, ptr %236, i32 1
  store ptr %237, ptr %235, align 8
  %238 = load ptr, ptr %8, align 8
  %239 = load i32, ptr %238, align 4
  %240 = add nsw i32 %239, -1
  store i32 %240, ptr %238, align 4
  br label %241

241:                                              ; preds = %232, %38
  %242 = load i32, ptr %11, align 4
  %243 = load ptr, ptr %6, align 8
  %244 = getelementptr inbounds %struct.qc_jagged_array, ptr %243, i32 0, i32 2
  %245 = load i32, ptr %244, align 8
  %246 = sub nsw i32 %245, 1
  %247 = icmp slt i32 %242, %246
  br i1 %247, label %248, label %262

248:                                              ; preds = %241
  %249 = load ptr, ptr %7, align 8
  %250 = load ptr, ptr %249, align 8
  store i8 44, ptr %250, align 1
  %251 = load ptr, ptr %7, align 8
  %252 = load ptr, ptr %251, align 8
  %253 = getelementptr inbounds i8, ptr %252, i32 1
  store ptr %253, ptr %251, align 8
  %254 = load ptr, ptr %7, align 8
  %255 = load ptr, ptr %254, align 8
  store i8 32, ptr %255, align 1
  %256 = load ptr, ptr %7, align 8
  %257 = load ptr, ptr %256, align 8
  %258 = getelementptr inbounds i8, ptr %257, i32 1
  store ptr %258, ptr %256, align 8
  %259 = load ptr, ptr %8, align 8
  %260 = load i32, ptr %259, align 4
  %261 = sub nsw i32 %260, 2
  store i32 %261, ptr %259, align 4
  br label %262

262:                                              ; preds = %248, %241
  br label %263

263:                                              ; preds = %262
  %264 = load i32, ptr %11, align 4
  %265 = add nsw i32 %264, 1
  store i32 %265, ptr %11, align 4
  br label %27, !llvm.loop !31

266:                                              ; preds = %27
  %267 = load ptr, ptr %7, align 8
  %268 = load ptr, ptr %267, align 8
  store i8 93, ptr %268, align 1
  %269 = load ptr, ptr %7, align 8
  %270 = load ptr, ptr %269, align 8
  %271 = getelementptr inbounds i8, ptr %270, i32 1
  store ptr %271, ptr %269, align 8
  %272 = load ptr, ptr %8, align 8
  %273 = load i32, ptr %272, align 4
  %274 = add nsw i32 %273, -1
  store i32 %274, ptr %272, align 4
  ret void
}

; Function Attrs: nounwind allocsize(1)
declare ptr @realloc(ptr noundef, i64 noundef) #7

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_create_list(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca ptr, align 8
  store i32 %0, ptr %2, align 4
  %4 = call noalias ptr @malloc(i64 noundef 24) #10
  store ptr %4, ptr %3, align 8
  %5 = load ptr, ptr %3, align 8
  %6 = getelementptr inbounds %struct.qc_list, ptr %5, i32 0, i32 2
  store i32 4, ptr %6, align 4
  %7 = load ptr, ptr %3, align 8
  %8 = getelementptr inbounds %struct.qc_list, ptr %7, i32 0, i32 1
  store i32 0, ptr %8, align 8
  %9 = load i32, ptr %2, align 4
  %10 = load ptr, ptr %3, align 8
  %11 = getelementptr inbounds %struct.qc_list, ptr %10, i32 0, i32 3
  store i32 %9, ptr %11, align 8
  %12 = load ptr, ptr %3, align 8
  %13 = getelementptr inbounds %struct.qc_list, ptr %12, i32 0, i32 2
  %14 = load i32, ptr %13, align 4
  %15 = sext i32 %14 to i64
  %16 = mul i64 %15, 8
  %17 = call noalias ptr @malloc(i64 noundef %16) #10
  %18 = load ptr, ptr %3, align 8
  %19 = getelementptr inbounds %struct.qc_list, ptr %18, i32 0, i32 0
  store ptr %17, ptr %19, align 8
  %20 = load ptr, ptr %3, align 8
  ret ptr %20
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local void @qc_list_push(ptr noundef %0, ptr noundef %1, i32 noundef %2) #0 {
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca ptr, align 8
  store ptr %0, ptr %4, align 8
  store ptr %1, ptr %5, align 8
  store i32 %2, ptr %6, align 4
  %9 = load ptr, ptr %4, align 8
  %10 = getelementptr inbounds %struct.qc_list, ptr %9, i32 0, i32 1
  %11 = load i32, ptr %10, align 8
  %12 = load ptr, ptr %4, align 8
  %13 = getelementptr inbounds %struct.qc_list, ptr %12, i32 0, i32 2
  %14 = load i32, ptr %13, align 4
  %15 = icmp sge i32 %11, %14
  br i1 %15, label %16, label %32

16:                                               ; preds = %3
  %17 = load ptr, ptr %4, align 8
  %18 = getelementptr inbounds %struct.qc_list, ptr %17, i32 0, i32 2
  %19 = load i32, ptr %18, align 4
  %20 = mul nsw i32 %19, 2
  store i32 %20, ptr %18, align 4
  %21 = load ptr, ptr %4, align 8
  %22 = getelementptr inbounds %struct.qc_list, ptr %21, i32 0, i32 0
  %23 = load ptr, ptr %22, align 8
  %24 = load ptr, ptr %4, align 8
  %25 = getelementptr inbounds %struct.qc_list, ptr %24, i32 0, i32 2
  %26 = load i32, ptr %25, align 4
  %27 = sext i32 %26 to i64
  %28 = mul i64 %27, 8
  %29 = call ptr @realloc(ptr noundef %23, i64 noundef %28) #12
  %30 = load ptr, ptr %4, align 8
  %31 = getelementptr inbounds %struct.qc_list, ptr %30, i32 0, i32 0
  store ptr %29, ptr %31, align 8
  br label %32

32:                                               ; preds = %16, %3
  %33 = load i32, ptr %6, align 4
  %34 = icmp sle i32 %33, 5
  br i1 %34, label %35, label %55

35:                                               ; preds = %32
  %36 = load i32, ptr %6, align 4
  %37 = call i32 @sizeof_type(i32 noundef %36)
  store i32 %37, ptr %7, align 4
  %38 = load i32, ptr %7, align 4
  %39 = sext i32 %38 to i64
  %40 = call noalias ptr @malloc(i64 noundef %39) #10
  store ptr %40, ptr %8, align 8
  %41 = load ptr, ptr %8, align 8
  %42 = load ptr, ptr %5, align 8
  %43 = load i32, ptr %7, align 4
  %44 = sext i32 %43 to i64
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %41, ptr align 1 %42, i64 %44, i1 false)
  %45 = load ptr, ptr %8, align 8
  %46 = load ptr, ptr %4, align 8
  %47 = getelementptr inbounds %struct.qc_list, ptr %46, i32 0, i32 0
  %48 = load ptr, ptr %47, align 8
  %49 = load ptr, ptr %4, align 8
  %50 = getelementptr inbounds %struct.qc_list, ptr %49, i32 0, i32 1
  %51 = load i32, ptr %50, align 8
  %52 = add nsw i32 %51, 1
  store i32 %52, ptr %50, align 8
  %53 = sext i32 %51 to i64
  %54 = getelementptr inbounds ptr, ptr %48, i64 %53
  store ptr %45, ptr %54, align 8
  br label %66

55:                                               ; preds = %32
  %56 = load ptr, ptr %5, align 8
  %57 = load ptr, ptr %4, align 8
  %58 = getelementptr inbounds %struct.qc_list, ptr %57, i32 0, i32 0
  %59 = load ptr, ptr %58, align 8
  %60 = load ptr, ptr %4, align 8
  %61 = getelementptr inbounds %struct.qc_list, ptr %60, i32 0, i32 1
  %62 = load i32, ptr %61, align 8
  %63 = add nsw i32 %62, 1
  store i32 %63, ptr %61, align 8
  %64 = sext i32 %62 to i64
  %65 = getelementptr inbounds ptr, ptr %59, i64 %64
  store ptr %56, ptr %65, align 8
  br label %66

66:                                               ; preds = %55, %35
  ret void
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local ptr @qc_list_get(ptr noundef %0, i32 noundef %1) #5 {
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca i32, align 4
  store ptr %0, ptr %4, align 8
  store i32 %1, ptr %5, align 4
  %6 = load i32, ptr %5, align 4
  %7 = icmp slt i32 %6, 0
  br i1 %7, label %14, label %8

8:                                                ; preds = %2
  %9 = load i32, ptr %5, align 4
  %10 = load ptr, ptr %4, align 8
  %11 = getelementptr inbounds %struct.qc_list, ptr %10, i32 0, i32 1
  %12 = load i32, ptr %11, align 8
  %13 = icmp sge i32 %9, %12
  br i1 %13, label %14, label %15

14:                                               ; preds = %8, %2
  store ptr null, ptr %3, align 8
  br label %40

15:                                               ; preds = %8
  %16 = load ptr, ptr %4, align 8
  %17 = getelementptr inbounds %struct.qc_list, ptr %16, i32 0, i32 3
  %18 = load i32, ptr %17, align 8
  %19 = icmp eq i32 %18, 6
  br i1 %19, label %20, label %29

20:                                               ; preds = %15
  %21 = load ptr, ptr %4, align 8
  %22 = getelementptr inbounds %struct.qc_list, ptr %21, i32 0, i32 0
  %23 = load ptr, ptr %22, align 8
  %24 = load i32, ptr %5, align 4
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds ptr, ptr %23, i64 %25
  %27 = load ptr, ptr %26, align 8
  %28 = call i32 (ptr, ...) @printf(ptr noundef @.str.19, ptr noundef %27)
  br label %29

29:                                               ; preds = %20, %15
  %30 = call i32 (ptr, ...) @printf(ptr noundef @.str.12)
  %31 = load ptr, ptr @stdout, align 8
  %32 = call i32 @fflush(ptr noundef %31)
  %33 = load ptr, ptr %4, align 8
  %34 = getelementptr inbounds %struct.qc_list, ptr %33, i32 0, i32 0
  %35 = load ptr, ptr %34, align 8
  %36 = load i32, ptr %5, align 4
  %37 = sext i32 %36 to i64
  %38 = getelementptr inbounds ptr, ptr %35, i64 %37
  %39 = load ptr, ptr %38, align 8
  store ptr %39, ptr %3, align 8
  br label %40

40:                                               ; preds = %29, %14
  %41 = load ptr, ptr %3, align 8
  ret ptr %41
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_list_pop(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca ptr, align 8
  store ptr %0, ptr %3, align 8
  %4 = load ptr, ptr %3, align 8
  %5 = getelementptr inbounds %struct.qc_list, ptr %4, i32 0, i32 1
  %6 = load i32, ptr %5, align 8
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %8, label %9

8:                                                ; preds = %1
  store ptr null, ptr %2, align 8
  br label %20

9:                                                ; preds = %1
  %10 = load ptr, ptr %3, align 8
  %11 = getelementptr inbounds %struct.qc_list, ptr %10, i32 0, i32 0
  %12 = load ptr, ptr %11, align 8
  %13 = load ptr, ptr %3, align 8
  %14 = getelementptr inbounds %struct.qc_list, ptr %13, i32 0, i32 1
  %15 = load i32, ptr %14, align 8
  %16 = add nsw i32 %15, -1
  store i32 %16, ptr %14, align 8
  %17 = sext i32 %16 to i64
  %18 = getelementptr inbounds ptr, ptr %12, i64 %17
  %19 = load ptr, ptr %18, align 8
  store ptr %19, ptr %2, align 8
  br label %20

20:                                               ; preds = %9, %8
  %21 = load ptr, ptr %2, align 8
  ret ptr %21
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local i32 @qc_list_length(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %struct.qc_list, ptr %3, i32 0, i32 1
  %5 = load i32, ptr %4, align 8
  ret i32 %5
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_create_map(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca ptr, align 8
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %4, align 4
  %6 = call noalias ptr @malloc(i64 noundef 32) #10
  store ptr %6, ptr %5, align 8
  %7 = load ptr, ptr %5, align 8
  %8 = getelementptr inbounds %struct.qc_map, ptr %7, i32 0, i32 3
  store i32 4, ptr %8, align 4
  %9 = load ptr, ptr %5, align 8
  %10 = getelementptr inbounds %struct.qc_map, ptr %9, i32 0, i32 2
  store i32 0, ptr %10, align 8
  %11 = load i32, ptr %3, align 4
  %12 = load ptr, ptr %5, align 8
  %13 = getelementptr inbounds %struct.qc_map, ptr %12, i32 0, i32 4
  store i32 %11, ptr %13, align 8
  %14 = load i32, ptr %4, align 4
  %15 = load ptr, ptr %5, align 8
  %16 = getelementptr inbounds %struct.qc_map, ptr %15, i32 0, i32 5
  store i32 %14, ptr %16, align 4
  %17 = load ptr, ptr %5, align 8
  %18 = getelementptr inbounds %struct.qc_map, ptr %17, i32 0, i32 3
  %19 = load i32, ptr %18, align 4
  %20 = sext i32 %19 to i64
  %21 = mul i64 %20, 8
  %22 = call noalias ptr @malloc(i64 noundef %21) #10
  %23 = load ptr, ptr %5, align 8
  %24 = getelementptr inbounds %struct.qc_map, ptr %23, i32 0, i32 0
  store ptr %22, ptr %24, align 8
  %25 = load ptr, ptr %5, align 8
  %26 = getelementptr inbounds %struct.qc_map, ptr %25, i32 0, i32 3
  %27 = load i32, ptr %26, align 4
  %28 = sext i32 %27 to i64
  %29 = mul i64 %28, 8
  %30 = call noalias ptr @malloc(i64 noundef %29) #10
  %31 = load ptr, ptr %5, align 8
  %32 = getelementptr inbounds %struct.qc_map, ptr %31, i32 0, i32 1
  store ptr %30, ptr %32, align 8
  %33 = load ptr, ptr %5, align 8
  ret ptr %33
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local zeroext i1 @qc_compare_keys(ptr noundef %0, ptr noundef %1, i32 noundef %2) #0 {
  %4 = alloca i1, align 1
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca i32, align 4
  store ptr %0, ptr %5, align 8
  store ptr %1, ptr %6, align 8
  store i32 %2, ptr %7, align 4
  %8 = load ptr, ptr %5, align 8
  %9 = icmp ne ptr %8, null
  br i1 %9, label %10, label %13

10:                                               ; preds = %3
  %11 = load ptr, ptr %6, align 8
  %12 = icmp ne ptr %11, null
  br i1 %12, label %14, label %13

13:                                               ; preds = %10, %3
  store i1 false, ptr %4, align 1
  br label %66

14:                                               ; preds = %10
  %15 = load i32, ptr %7, align 4
  switch i32 %15, label %65 [
    i32 0, label %16
    i32 1, label %22
    i32 2, label %28
    i32 3, label %34
    i32 4, label %42
    i32 5, label %52
    i32 6, label %60
  ]

16:                                               ; preds = %14
  %17 = load ptr, ptr %5, align 8
  %18 = load i32, ptr %17, align 4
  %19 = load ptr, ptr %6, align 8
  %20 = load i32, ptr %19, align 4
  %21 = icmp eq i32 %18, %20
  store i1 %21, ptr %4, align 1
  br label %66

22:                                               ; preds = %14
  %23 = load ptr, ptr %5, align 8
  %24 = load float, ptr %23, align 4
  %25 = load ptr, ptr %6, align 8
  %26 = load float, ptr %25, align 4
  %27 = fcmp oeq float %24, %26
  store i1 %27, ptr %4, align 1
  br label %66

28:                                               ; preds = %14
  %29 = load ptr, ptr %5, align 8
  %30 = load double, ptr %29, align 8
  %31 = load ptr, ptr %6, align 8
  %32 = load double, ptr %31, align 8
  %33 = fcmp oeq double %30, %32
  store i1 %33, ptr %4, align 1
  br label %66

34:                                               ; preds = %14
  %35 = load ptr, ptr %5, align 8
  %36 = load i8, ptr %35, align 1
  %37 = sext i8 %36 to i32
  %38 = load ptr, ptr %6, align 8
  %39 = load i8, ptr %38, align 1
  %40 = sext i8 %39 to i32
  %41 = icmp eq i32 %37, %40
  store i1 %41, ptr %4, align 1
  br label %66

42:                                               ; preds = %14
  %43 = load ptr, ptr %5, align 8
  %44 = load i8, ptr %43, align 1
  %45 = trunc i8 %44 to i1
  %46 = zext i1 %45 to i32
  %47 = load ptr, ptr %6, align 8
  %48 = load i8, ptr %47, align 1
  %49 = trunc i8 %48 to i1
  %50 = zext i1 %49 to i32
  %51 = icmp eq i32 %46, %50
  store i1 %51, ptr %4, align 1
  br label %66

52:                                               ; preds = %14
  %53 = load ptr, ptr %5, align 8
  %54 = load i8, ptr %53, align 1
  %55 = zext i8 %54 to i32
  %56 = load ptr, ptr %6, align 8
  %57 = load i8, ptr %56, align 1
  %58 = zext i8 %57 to i32
  %59 = icmp eq i32 %55, %58
  store i1 %59, ptr %4, align 1
  br label %66

60:                                               ; preds = %14
  %61 = load ptr, ptr %5, align 8
  %62 = load ptr, ptr %6, align 8
  %63 = call i32 @strcmp(ptr noundef %61, ptr noundef %62) #9
  %64 = icmp eq i32 %63, 0
  store i1 %64, ptr %4, align 1
  br label %66

65:                                               ; preds = %14
  store i1 false, ptr %4, align 1
  br label %66

66:                                               ; preds = %65, %60, %52, %42, %34, %28, %22, %16, %13
  %67 = load i1, ptr %4, align 1
  ret i1 %67
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local void @qc_map_set(ptr noundef %0, ptr noundef %1, ptr noundef %2) #0 {
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca ptr, align 8
  %10 = alloca i32, align 4
  %11 = alloca ptr, align 8
  %12 = alloca ptr, align 8
  %13 = alloca i32, align 4
  %14 = alloca ptr, align 8
  %15 = alloca ptr, align 8
  store ptr %0, ptr %4, align 8
  store ptr %1, ptr %5, align 8
  store ptr %2, ptr %6, align 8
  store i32 0, ptr %7, align 4
  br label %16

16:                                               ; preds = %102, %3
  %17 = load i32, ptr %7, align 4
  %18 = load ptr, ptr %4, align 8
  %19 = getelementptr inbounds %struct.qc_map, ptr %18, i32 0, i32 2
  %20 = load i32, ptr %19, align 8
  %21 = icmp slt i32 %17, %20
  br i1 %21, label %22, label %105

22:                                               ; preds = %16
  %23 = load ptr, ptr %4, align 8
  %24 = getelementptr inbounds %struct.qc_map, ptr %23, i32 0, i32 0
  %25 = load ptr, ptr %24, align 8
  %26 = load i32, ptr %7, align 4
  %27 = sext i32 %26 to i64
  %28 = getelementptr inbounds ptr, ptr %25, i64 %27
  %29 = load ptr, ptr %28, align 8
  %30 = load ptr, ptr %5, align 8
  %31 = load ptr, ptr %4, align 8
  %32 = getelementptr inbounds %struct.qc_map, ptr %31, i32 0, i32 4
  %33 = load i32, ptr %32, align 8
  %34 = call zeroext i1 @qc_compare_keys(ptr noundef %29, ptr noundef %30, i32 noundef %33)
  br i1 %34, label %35, label %101

35:                                               ; preds = %22
  %36 = load ptr, ptr %4, align 8
  %37 = getelementptr inbounds %struct.qc_map, ptr %36, i32 0, i32 5
  %38 = load i32, ptr %37, align 4
  %39 = icmp sle i32 %38, 5
  br i1 %39, label %40, label %74

40:                                               ; preds = %35
  %41 = load ptr, ptr %4, align 8
  %42 = getelementptr inbounds %struct.qc_map, ptr %41, i32 0, i32 5
  %43 = load i32, ptr %42, align 4
  %44 = call i32 @sizeof_type(i32 noundef %43)
  store i32 %44, ptr %8, align 4
  %45 = load ptr, ptr %4, align 8
  %46 = getelementptr inbounds %struct.qc_map, ptr %45, i32 0, i32 1
  %47 = load ptr, ptr %46, align 8
  %48 = load i32, ptr %7, align 4
  %49 = sext i32 %48 to i64
  %50 = getelementptr inbounds ptr, ptr %47, i64 %49
  %51 = load ptr, ptr %50, align 8
  %52 = icmp ne ptr %51, null
  br i1 %52, label %63, label %53

53:                                               ; preds = %40
  %54 = load i32, ptr %8, align 4
  %55 = sext i32 %54 to i64
  %56 = call noalias ptr @malloc(i64 noundef %55) #10
  %57 = load ptr, ptr %4, align 8
  %58 = getelementptr inbounds %struct.qc_map, ptr %57, i32 0, i32 1
  %59 = load ptr, ptr %58, align 8
  %60 = load i32, ptr %7, align 4
  %61 = sext i32 %60 to i64
  %62 = getelementptr inbounds ptr, ptr %59, i64 %61
  store ptr %56, ptr %62, align 8
  br label %63

63:                                               ; preds = %53, %40
  %64 = load ptr, ptr %4, align 8
  %65 = getelementptr inbounds %struct.qc_map, ptr %64, i32 0, i32 1
  %66 = load ptr, ptr %65, align 8
  %67 = load i32, ptr %7, align 4
  %68 = sext i32 %67 to i64
  %69 = getelementptr inbounds ptr, ptr %66, i64 %68
  %70 = load ptr, ptr %69, align 8
  %71 = load ptr, ptr %6, align 8
  %72 = load i32, ptr %8, align 4
  %73 = sext i32 %72 to i64
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %70, ptr align 1 %71, i64 %73, i1 false)
  br label %100

74:                                               ; preds = %35
  %75 = load ptr, ptr %4, align 8
  %76 = getelementptr inbounds %struct.qc_map, ptr %75, i32 0, i32 4
  %77 = load i32, ptr %76, align 8
  %78 = icmp eq i32 %77, 6
  br i1 %78, label %79, label %91

79:                                               ; preds = %74
  %80 = load ptr, ptr %5, align 8
  store ptr %80, ptr %9, align 8
  %81 = load ptr, ptr %9, align 8
  %82 = call noalias ptr @strdup(ptr noundef %81) #11
  %83 = load ptr, ptr %4, align 8
  %84 = getelementptr inbounds %struct.qc_map, ptr %83, i32 0, i32 0
  %85 = load ptr, ptr %84, align 8
  %86 = load ptr, ptr %4, align 8
  %87 = getelementptr inbounds %struct.qc_map, ptr %86, i32 0, i32 2
  %88 = load i32, ptr %87, align 8
  %89 = sext i32 %88 to i64
  %90 = getelementptr inbounds ptr, ptr %85, i64 %89
  store ptr %82, ptr %90, align 8
  br label %99

91:                                               ; preds = %74
  %92 = load ptr, ptr %6, align 8
  %93 = load ptr, ptr %4, align 8
  %94 = getelementptr inbounds %struct.qc_map, ptr %93, i32 0, i32 1
  %95 = load ptr, ptr %94, align 8
  %96 = load i32, ptr %7, align 4
  %97 = sext i32 %96 to i64
  %98 = getelementptr inbounds ptr, ptr %95, i64 %97
  store ptr %92, ptr %98, align 8
  br label %99

99:                                               ; preds = %91, %79
  br label %100

100:                                              ; preds = %99, %63
  br label %253

101:                                              ; preds = %22
  br label %102

102:                                              ; preds = %101
  %103 = load i32, ptr %7, align 4
  %104 = add nsw i32 %103, 1
  store i32 %104, ptr %7, align 4
  br label %16, !llvm.loop !32

105:                                              ; preds = %16
  %106 = load ptr, ptr %4, align 8
  %107 = getelementptr inbounds %struct.qc_map, ptr %106, i32 0, i32 2
  %108 = load i32, ptr %107, align 8
  %109 = load ptr, ptr %4, align 8
  %110 = getelementptr inbounds %struct.qc_map, ptr %109, i32 0, i32 3
  %111 = load i32, ptr %110, align 4
  %112 = icmp sge i32 %108, %111
  br i1 %112, label %113, label %140

113:                                              ; preds = %105
  %114 = load ptr, ptr %4, align 8
  %115 = getelementptr inbounds %struct.qc_map, ptr %114, i32 0, i32 3
  %116 = load i32, ptr %115, align 4
  %117 = mul nsw i32 %116, 2
  store i32 %117, ptr %115, align 4
  %118 = load ptr, ptr %4, align 8
  %119 = getelementptr inbounds %struct.qc_map, ptr %118, i32 0, i32 0
  %120 = load ptr, ptr %119, align 8
  %121 = load ptr, ptr %4, align 8
  %122 = getelementptr inbounds %struct.qc_map, ptr %121, i32 0, i32 3
  %123 = load i32, ptr %122, align 4
  %124 = sext i32 %123 to i64
  %125 = mul i64 %124, 8
  %126 = call ptr @realloc(ptr noundef %120, i64 noundef %125) #12
  %127 = load ptr, ptr %4, align 8
  %128 = getelementptr inbounds %struct.qc_map, ptr %127, i32 0, i32 0
  store ptr %126, ptr %128, align 8
  %129 = load ptr, ptr %4, align 8
  %130 = getelementptr inbounds %struct.qc_map, ptr %129, i32 0, i32 1
  %131 = load ptr, ptr %130, align 8
  %132 = load ptr, ptr %4, align 8
  %133 = getelementptr inbounds %struct.qc_map, ptr %132, i32 0, i32 3
  %134 = load i32, ptr %133, align 4
  %135 = sext i32 %134 to i64
  %136 = mul i64 %135, 8
  %137 = call ptr @realloc(ptr noundef %131, i64 noundef %136) #12
  %138 = load ptr, ptr %4, align 8
  %139 = getelementptr inbounds %struct.qc_map, ptr %138, i32 0, i32 1
  store ptr %137, ptr %139, align 8
  br label %140

140:                                              ; preds = %113, %105
  %141 = load ptr, ptr %4, align 8
  %142 = getelementptr inbounds %struct.qc_map, ptr %141, i32 0, i32 4
  %143 = load i32, ptr %142, align 8
  %144 = icmp sle i32 %143, 5
  br i1 %144, label %145, label %166

145:                                              ; preds = %140
  %146 = load ptr, ptr %4, align 8
  %147 = getelementptr inbounds %struct.qc_map, ptr %146, i32 0, i32 4
  %148 = load i32, ptr %147, align 8
  %149 = call i32 @sizeof_type(i32 noundef %148)
  store i32 %149, ptr %10, align 4
  %150 = load i32, ptr %10, align 4
  %151 = sext i32 %150 to i64
  %152 = call noalias ptr @malloc(i64 noundef %151) #10
  store ptr %152, ptr %11, align 8
  %153 = load ptr, ptr %11, align 8
  %154 = load ptr, ptr %5, align 8
  %155 = load i32, ptr %10, align 4
  %156 = sext i32 %155 to i64
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %153, ptr align 1 %154, i64 %156, i1 false)
  %157 = load ptr, ptr %11, align 8
  %158 = load ptr, ptr %4, align 8
  %159 = getelementptr inbounds %struct.qc_map, ptr %158, i32 0, i32 0
  %160 = load ptr, ptr %159, align 8
  %161 = load ptr, ptr %4, align 8
  %162 = getelementptr inbounds %struct.qc_map, ptr %161, i32 0, i32 2
  %163 = load i32, ptr %162, align 8
  %164 = sext i32 %163 to i64
  %165 = getelementptr inbounds ptr, ptr %160, i64 %164
  store ptr %157, ptr %165, align 8
  br label %194

166:                                              ; preds = %140
  %167 = load ptr, ptr %4, align 8
  %168 = getelementptr inbounds %struct.qc_map, ptr %167, i32 0, i32 4
  %169 = load i32, ptr %168, align 8
  %170 = icmp eq i32 %169, 6
  br i1 %170, label %171, label %183

171:                                              ; preds = %166
  %172 = load ptr, ptr %5, align 8
  store ptr %172, ptr %12, align 8
  %173 = load ptr, ptr %12, align 8
  %174 = call noalias ptr @strdup(ptr noundef %173) #11
  %175 = load ptr, ptr %4, align 8
  %176 = getelementptr inbounds %struct.qc_map, ptr %175, i32 0, i32 0
  %177 = load ptr, ptr %176, align 8
  %178 = load ptr, ptr %4, align 8
  %179 = getelementptr inbounds %struct.qc_map, ptr %178, i32 0, i32 2
  %180 = load i32, ptr %179, align 8
  %181 = sext i32 %180 to i64
  %182 = getelementptr inbounds ptr, ptr %177, i64 %181
  store ptr %174, ptr %182, align 8
  br label %193

183:                                              ; preds = %166
  %184 = load ptr, ptr %5, align 8
  %185 = load ptr, ptr %4, align 8
  %186 = getelementptr inbounds %struct.qc_map, ptr %185, i32 0, i32 0
  %187 = load ptr, ptr %186, align 8
  %188 = load ptr, ptr %4, align 8
  %189 = getelementptr inbounds %struct.qc_map, ptr %188, i32 0, i32 2
  %190 = load i32, ptr %189, align 8
  %191 = sext i32 %190 to i64
  %192 = getelementptr inbounds ptr, ptr %187, i64 %191
  store ptr %184, ptr %192, align 8
  br label %193

193:                                              ; preds = %183, %171
  br label %194

194:                                              ; preds = %193, %145
  %195 = load ptr, ptr %4, align 8
  %196 = getelementptr inbounds %struct.qc_map, ptr %195, i32 0, i32 5
  %197 = load i32, ptr %196, align 4
  %198 = icmp sle i32 %197, 5
  br i1 %198, label %199, label %220

199:                                              ; preds = %194
  %200 = load ptr, ptr %4, align 8
  %201 = getelementptr inbounds %struct.qc_map, ptr %200, i32 0, i32 5
  %202 = load i32, ptr %201, align 4
  %203 = call i32 @sizeof_type(i32 noundef %202)
  store i32 %203, ptr %13, align 4
  %204 = load i32, ptr %13, align 4
  %205 = sext i32 %204 to i64
  %206 = call noalias ptr @malloc(i64 noundef %205) #10
  store ptr %206, ptr %14, align 8
  %207 = load ptr, ptr %14, align 8
  %208 = load ptr, ptr %6, align 8
  %209 = load i32, ptr %13, align 4
  %210 = sext i32 %209 to i64
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %207, ptr align 1 %208, i64 %210, i1 false)
  %211 = load ptr, ptr %14, align 8
  %212 = load ptr, ptr %4, align 8
  %213 = getelementptr inbounds %struct.qc_map, ptr %212, i32 0, i32 1
  %214 = load ptr, ptr %213, align 8
  %215 = load ptr, ptr %4, align 8
  %216 = getelementptr inbounds %struct.qc_map, ptr %215, i32 0, i32 2
  %217 = load i32, ptr %216, align 8
  %218 = sext i32 %217 to i64
  %219 = getelementptr inbounds ptr, ptr %214, i64 %218
  store ptr %211, ptr %219, align 8
  br label %248

220:                                              ; preds = %194
  %221 = load ptr, ptr %4, align 8
  %222 = getelementptr inbounds %struct.qc_map, ptr %221, i32 0, i32 5
  %223 = load i32, ptr %222, align 4
  %224 = icmp eq i32 %223, 6
  br i1 %224, label %225, label %237

225:                                              ; preds = %220
  %226 = load ptr, ptr %6, align 8
  store ptr %226, ptr %15, align 8
  %227 = load ptr, ptr %15, align 8
  %228 = call noalias ptr @strdup(ptr noundef %227) #11
  %229 = load ptr, ptr %4, align 8
  %230 = getelementptr inbounds %struct.qc_map, ptr %229, i32 0, i32 1
  %231 = load ptr, ptr %230, align 8
  %232 = load ptr, ptr %4, align 8
  %233 = getelementptr inbounds %struct.qc_map, ptr %232, i32 0, i32 2
  %234 = load i32, ptr %233, align 8
  %235 = sext i32 %234 to i64
  %236 = getelementptr inbounds ptr, ptr %231, i64 %235
  store ptr %228, ptr %236, align 8
  br label %247

237:                                              ; preds = %220
  %238 = load ptr, ptr %6, align 8
  %239 = load ptr, ptr %4, align 8
  %240 = getelementptr inbounds %struct.qc_map, ptr %239, i32 0, i32 1
  %241 = load ptr, ptr %240, align 8
  %242 = load ptr, ptr %4, align 8
  %243 = getelementptr inbounds %struct.qc_map, ptr %242, i32 0, i32 2
  %244 = load i32, ptr %243, align 8
  %245 = sext i32 %244 to i64
  %246 = getelementptr inbounds ptr, ptr %241, i64 %245
  store ptr %238, ptr %246, align 8
  br label %247

247:                                              ; preds = %237, %225
  br label %248

248:                                              ; preds = %247, %199
  %249 = load ptr, ptr %4, align 8
  %250 = getelementptr inbounds %struct.qc_map, ptr %249, i32 0, i32 2
  %251 = load i32, ptr %250, align 8
  %252 = add nsw i32 %251, 1
  store i32 %252, ptr %250, align 8
  br label %253

253:                                              ; preds = %248, %100
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_map_get(ptr noundef %0, ptr noundef %1) #0 {
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  store ptr %0, ptr %4, align 8
  store ptr %1, ptr %5, align 8
  store i32 0, ptr %6, align 4
  br label %7

7:                                                ; preds = %35, %2
  %8 = load i32, ptr %6, align 4
  %9 = load ptr, ptr %4, align 8
  %10 = getelementptr inbounds %struct.qc_map, ptr %9, i32 0, i32 2
  %11 = load i32, ptr %10, align 8
  %12 = icmp slt i32 %8, %11
  br i1 %12, label %13, label %38

13:                                               ; preds = %7
  %14 = load ptr, ptr %4, align 8
  %15 = getelementptr inbounds %struct.qc_map, ptr %14, i32 0, i32 0
  %16 = load ptr, ptr %15, align 8
  %17 = load i32, ptr %6, align 4
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds ptr, ptr %16, i64 %18
  %20 = load ptr, ptr %19, align 8
  %21 = load ptr, ptr %5, align 8
  %22 = load ptr, ptr %4, align 8
  %23 = getelementptr inbounds %struct.qc_map, ptr %22, i32 0, i32 4
  %24 = load i32, ptr %23, align 8
  %25 = call zeroext i1 @qc_compare_keys(ptr noundef %20, ptr noundef %21, i32 noundef %24)
  br i1 %25, label %26, label %34

26:                                               ; preds = %13
  %27 = load ptr, ptr %4, align 8
  %28 = getelementptr inbounds %struct.qc_map, ptr %27, i32 0, i32 1
  %29 = load ptr, ptr %28, align 8
  %30 = load i32, ptr %6, align 4
  %31 = sext i32 %30 to i64
  %32 = getelementptr inbounds ptr, ptr %29, i64 %31
  %33 = load ptr, ptr %32, align 8
  store ptr %33, ptr %3, align 8
  br label %39

34:                                               ; preds = %13
  br label %35

35:                                               ; preds = %34
  %36 = load i32, ptr %6, align 4
  %37 = add nsw i32 %36, 1
  store i32 %37, ptr %6, align 4
  br label %7, !llvm.loop !33

38:                                               ; preds = %7
  store ptr null, ptr %3, align 8
  br label %39

39:                                               ; preds = %38, %26
  %40 = load ptr, ptr %3, align 8
  ret ptr %40
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local zeroext i1 @qc_map_has(ptr noundef %0, ptr noundef %1) #0 {
  %3 = alloca i1, align 1
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  store ptr %0, ptr %4, align 8
  store ptr %1, ptr %5, align 8
  store i32 0, ptr %6, align 4
  br label %7

7:                                                ; preds = %28, %2
  %8 = load i32, ptr %6, align 4
  %9 = load ptr, ptr %4, align 8
  %10 = getelementptr inbounds %struct.qc_map, ptr %9, i32 0, i32 2
  %11 = load i32, ptr %10, align 8
  %12 = icmp slt i32 %8, %11
  br i1 %12, label %13, label %31

13:                                               ; preds = %7
  %14 = load ptr, ptr %4, align 8
  %15 = getelementptr inbounds %struct.qc_map, ptr %14, i32 0, i32 0
  %16 = load ptr, ptr %15, align 8
  %17 = load i32, ptr %6, align 4
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds ptr, ptr %16, i64 %18
  %20 = load ptr, ptr %19, align 8
  %21 = load ptr, ptr %5, align 8
  %22 = load ptr, ptr %4, align 8
  %23 = getelementptr inbounds %struct.qc_map, ptr %22, i32 0, i32 4
  %24 = load i32, ptr %23, align 8
  %25 = call zeroext i1 @qc_compare_keys(ptr noundef %20, ptr noundef %21, i32 noundef %24)
  br i1 %25, label %26, label %27

26:                                               ; preds = %13
  store i1 true, ptr %3, align 1
  br label %32

27:                                               ; preds = %13
  br label %28

28:                                               ; preds = %27
  %29 = load i32, ptr %6, align 4
  %30 = add nsw i32 %29, 1
  store i32 %30, ptr %6, align 4
  br label %7, !llvm.loop !34

31:                                               ; preds = %7
  store i1 false, ptr %3, align 1
  br label %32

32:                                               ; preds = %31, %26
  %33 = load i1, ptr %3, align 1
  ret i1 %33
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local void @qc_map_remove(ptr noundef %0, ptr noundef %1) #0 {
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store ptr %0, ptr %3, align 8
  store ptr %1, ptr %4, align 8
  store i32 0, ptr %5, align 4
  br label %7

7:                                                ; preds = %73, %2
  %8 = load i32, ptr %5, align 4
  %9 = load ptr, ptr %3, align 8
  %10 = getelementptr inbounds %struct.qc_map, ptr %9, i32 0, i32 2
  %11 = load i32, ptr %10, align 8
  %12 = icmp slt i32 %8, %11
  br i1 %12, label %13, label %76

13:                                               ; preds = %7
  %14 = load ptr, ptr %3, align 8
  %15 = getelementptr inbounds %struct.qc_map, ptr %14, i32 0, i32 0
  %16 = load ptr, ptr %15, align 8
  %17 = load i32, ptr %5, align 4
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds ptr, ptr %16, i64 %18
  %20 = load ptr, ptr %19, align 8
  %21 = load ptr, ptr %4, align 8
  %22 = load ptr, ptr %3, align 8
  %23 = getelementptr inbounds %struct.qc_map, ptr %22, i32 0, i32 4
  %24 = load i32, ptr %23, align 8
  %25 = call zeroext i1 @qc_compare_keys(ptr noundef %20, ptr noundef %21, i32 noundef %24)
  br i1 %25, label %26, label %72

26:                                               ; preds = %13
  %27 = load i32, ptr %5, align 4
  store i32 %27, ptr %6, align 4
  br label %28

28:                                               ; preds = %64, %26
  %29 = load i32, ptr %6, align 4
  %30 = load ptr, ptr %3, align 8
  %31 = getelementptr inbounds %struct.qc_map, ptr %30, i32 0, i32 2
  %32 = load i32, ptr %31, align 8
  %33 = sub nsw i32 %32, 1
  %34 = icmp slt i32 %29, %33
  br i1 %34, label %35, label %67

35:                                               ; preds = %28
  %36 = load ptr, ptr %3, align 8
  %37 = getelementptr inbounds %struct.qc_map, ptr %36, i32 0, i32 0
  %38 = load ptr, ptr %37, align 8
  %39 = load i32, ptr %6, align 4
  %40 = add nsw i32 %39, 1
  %41 = sext i32 %40 to i64
  %42 = getelementptr inbounds ptr, ptr %38, i64 %41
  %43 = load ptr, ptr %42, align 8
  %44 = load ptr, ptr %3, align 8
  %45 = getelementptr inbounds %struct.qc_map, ptr %44, i32 0, i32 0
  %46 = load ptr, ptr %45, align 8
  %47 = load i32, ptr %6, align 4
  %48 = sext i32 %47 to i64
  %49 = getelementptr inbounds ptr, ptr %46, i64 %48
  store ptr %43, ptr %49, align 8
  %50 = load ptr, ptr %3, align 8
  %51 = getelementptr inbounds %struct.qc_map, ptr %50, i32 0, i32 1
  %52 = load ptr, ptr %51, align 8
  %53 = load i32, ptr %6, align 4
  %54 = add nsw i32 %53, 1
  %55 = sext i32 %54 to i64
  %56 = getelementptr inbounds ptr, ptr %52, i64 %55
  %57 = load ptr, ptr %56, align 8
  %58 = load ptr, ptr %3, align 8
  %59 = getelementptr inbounds %struct.qc_map, ptr %58, i32 0, i32 1
  %60 = load ptr, ptr %59, align 8
  %61 = load i32, ptr %6, align 4
  %62 = sext i32 %61 to i64
  %63 = getelementptr inbounds ptr, ptr %60, i64 %62
  store ptr %57, ptr %63, align 8
  br label %64

64:                                               ; preds = %35
  %65 = load i32, ptr %6, align 4
  %66 = add nsw i32 %65, 1
  store i32 %66, ptr %6, align 4
  br label %28, !llvm.loop !35

67:                                               ; preds = %28
  %68 = load ptr, ptr %3, align 8
  %69 = getelementptr inbounds %struct.qc_map, ptr %68, i32 0, i32 2
  %70 = load i32, ptr %69, align 8
  %71 = add nsw i32 %70, -1
  store i32 %71, ptr %69, align 8
  br label %76

72:                                               ; preds = %13
  br label %73

73:                                               ; preds = %72
  %74 = load i32, ptr %5, align 4
  %75 = add nsw i32 %74, 1
  store i32 %75, ptr %5, align 4
  br label %7, !llvm.loop !36

76:                                               ; preds = %67, %7
  ret void
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_print_map(ptr noundef %0) #5 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  %4 = alloca i8, align 1
  %5 = alloca i8, align 1
  store ptr %0, ptr %2, align 8
  %6 = call i32 (ptr, ...) @printf(ptr noundef @.str.20)
  store i32 0, ptr %3, align 4
  br label %7

7:                                                ; preds = %224, %1
  %8 = load i32, ptr %3, align 4
  %9 = load ptr, ptr %2, align 8
  %10 = getelementptr inbounds %struct.qc_map, ptr %9, i32 0, i32 2
  %11 = load i32, ptr %10, align 8
  %12 = icmp slt i32 %8, %11
  br i1 %12, label %13, label %227

13:                                               ; preds = %7
  %14 = load ptr, ptr %2, align 8
  %15 = getelementptr inbounds %struct.qc_map, ptr %14, i32 0, i32 4
  %16 = load i32, ptr %15, align 8
  switch i32 %16, label %113 [
    i32 0, label %17
    i32 1, label %27
    i32 2, label %38
    i32 3, label %48
    i32 4, label %59
    i32 5, label %72
    i32 6, label %104
  ]

17:                                               ; preds = %13
  %18 = load ptr, ptr %2, align 8
  %19 = getelementptr inbounds %struct.qc_map, ptr %18, i32 0, i32 0
  %20 = load ptr, ptr %19, align 8
  %21 = load i32, ptr %3, align 4
  %22 = sext i32 %21 to i64
  %23 = getelementptr inbounds ptr, ptr %20, i64 %22
  %24 = load ptr, ptr %23, align 8
  %25 = load i32, ptr %24, align 4
  %26 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %25)
  br label %113

27:                                               ; preds = %13
  %28 = load ptr, ptr %2, align 8
  %29 = getelementptr inbounds %struct.qc_map, ptr %28, i32 0, i32 0
  %30 = load ptr, ptr %29, align 8
  %31 = load i32, ptr %3, align 4
  %32 = sext i32 %31 to i64
  %33 = getelementptr inbounds ptr, ptr %30, i64 %32
  %34 = load ptr, ptr %33, align 8
  %35 = load float, ptr %34, align 4
  %36 = fpext float %35 to double
  %37 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, double noundef %36)
  br label %113

38:                                               ; preds = %13
  %39 = load ptr, ptr %2, align 8
  %40 = getelementptr inbounds %struct.qc_map, ptr %39, i32 0, i32 0
  %41 = load ptr, ptr %40, align 8
  %42 = load i32, ptr %3, align 4
  %43 = sext i32 %42 to i64
  %44 = getelementptr inbounds ptr, ptr %41, i64 %43
  %45 = load ptr, ptr %44, align 8
  %46 = load double, ptr %45, align 8
  %47 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, double noundef %46)
  br label %113

48:                                               ; preds = %13
  %49 = load ptr, ptr %2, align 8
  %50 = getelementptr inbounds %struct.qc_map, ptr %49, i32 0, i32 0
  %51 = load ptr, ptr %50, align 8
  %52 = load i32, ptr %3, align 4
  %53 = sext i32 %52 to i64
  %54 = getelementptr inbounds ptr, ptr %51, i64 %53
  %55 = load ptr, ptr %54, align 8
  %56 = load i8, ptr %55, align 1
  %57 = sext i8 %56 to i32
  %58 = call i32 (ptr, ...) @printf(ptr noundef @.str.17, i32 noundef %57)
  br label %113

59:                                               ; preds = %13
  %60 = load ptr, ptr %2, align 8
  %61 = getelementptr inbounds %struct.qc_map, ptr %60, i32 0, i32 0
  %62 = load ptr, ptr %61, align 8
  %63 = load i32, ptr %3, align 4
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds ptr, ptr %62, i64 %64
  %66 = load ptr, ptr %65, align 8
  %67 = load i8, ptr %66, align 1
  %68 = trunc i8 %67 to i1
  %69 = zext i1 %68 to i64
  %70 = select i1 %68, ptr @.str.3, ptr @.str.4
  %71 = call i32 (ptr, ...) @printf(ptr noundef @.str.10, ptr noundef %70)
  br label %113

72:                                               ; preds = %13
  %73 = load ptr, ptr %2, align 8
  %74 = getelementptr inbounds %struct.qc_map, ptr %73, i32 0, i32 0
  %75 = load ptr, ptr %74, align 8
  %76 = load i32, ptr %3, align 4
  %77 = sext i32 %76 to i64
  %78 = getelementptr inbounds ptr, ptr %75, i64 %77
  %79 = load ptr, ptr %78, align 8
  %80 = load i8, ptr %79, align 1
  %81 = zext i8 %80 to i32
  %82 = and i32 %81, 3
  %83 = trunc i32 %82 to i8
  store i8 %83, ptr %4, align 1
  %84 = load i8, ptr %4, align 1
  %85 = zext i8 %84 to i32
  %86 = icmp eq i32 %85, 0
  br i1 %86, label %87, label %88

87:                                               ; preds = %72
  br label %101

88:                                               ; preds = %72
  %89 = load i8, ptr %4, align 1
  %90 = zext i8 %89 to i32
  %91 = icmp eq i32 %90, 1
  br i1 %91, label %92, label %93

92:                                               ; preds = %88
  br label %99

93:                                               ; preds = %88
  %94 = load i8, ptr %4, align 1
  %95 = zext i8 %94 to i32
  %96 = icmp eq i32 %95, 2
  %97 = zext i1 %96 to i64
  %98 = select i1 %96, ptr @.str.7, ptr @.str.8
  br label %99

99:                                               ; preds = %93, %92
  %100 = phi ptr [ @.str.6, %92 ], [ %98, %93 ]
  br label %101

101:                                              ; preds = %99, %87
  %102 = phi ptr [ @.str.5, %87 ], [ %100, %99 ]
  %103 = call i32 (ptr, ...) @printf(ptr noundef @.str.10, ptr noundef %102)
  br label %113

104:                                              ; preds = %13
  %105 = load ptr, ptr %2, align 8
  %106 = getelementptr inbounds %struct.qc_map, ptr %105, i32 0, i32 0
  %107 = load ptr, ptr %106, align 8
  %108 = load i32, ptr %3, align 4
  %109 = sext i32 %108 to i64
  %110 = getelementptr inbounds ptr, ptr %107, i64 %109
  %111 = load ptr, ptr %110, align 8
  %112 = call i32 (ptr, ...) @printf(ptr noundef @.str.16, ptr noundef %111)
  br label %113

113:                                              ; preds = %104, %101, %59, %48, %38, %27, %17, %13
  %114 = call i32 (ptr, ...) @printf(ptr noundef @.str.21)
  %115 = load ptr, ptr %2, align 8
  %116 = getelementptr inbounds %struct.qc_map, ptr %115, i32 0, i32 5
  %117 = load i32, ptr %116, align 4
  switch i32 %117, label %214 [
    i32 0, label %118
    i32 1, label %128
    i32 2, label %139
    i32 3, label %149
    i32 4, label %160
    i32 5, label %173
    i32 6, label %205
  ]

118:                                              ; preds = %113
  %119 = load ptr, ptr %2, align 8
  %120 = getelementptr inbounds %struct.qc_map, ptr %119, i32 0, i32 1
  %121 = load ptr, ptr %120, align 8
  %122 = load i32, ptr %3, align 4
  %123 = sext i32 %122 to i64
  %124 = getelementptr inbounds ptr, ptr %121, i64 %123
  %125 = load ptr, ptr %124, align 8
  %126 = load i32, ptr %125, align 4
  %127 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %126)
  br label %214

128:                                              ; preds = %113
  %129 = load ptr, ptr %2, align 8
  %130 = getelementptr inbounds %struct.qc_map, ptr %129, i32 0, i32 1
  %131 = load ptr, ptr %130, align 8
  %132 = load i32, ptr %3, align 4
  %133 = sext i32 %132 to i64
  %134 = getelementptr inbounds ptr, ptr %131, i64 %133
  %135 = load ptr, ptr %134, align 8
  %136 = load float, ptr %135, align 4
  %137 = fpext float %136 to double
  %138 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, double noundef %137)
  br label %214

139:                                              ; preds = %113
  %140 = load ptr, ptr %2, align 8
  %141 = getelementptr inbounds %struct.qc_map, ptr %140, i32 0, i32 1
  %142 = load ptr, ptr %141, align 8
  %143 = load i32, ptr %3, align 4
  %144 = sext i32 %143 to i64
  %145 = getelementptr inbounds ptr, ptr %142, i64 %144
  %146 = load ptr, ptr %145, align 8
  %147 = load double, ptr %146, align 8
  %148 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, double noundef %147)
  br label %214

149:                                              ; preds = %113
  %150 = load ptr, ptr %2, align 8
  %151 = getelementptr inbounds %struct.qc_map, ptr %150, i32 0, i32 1
  %152 = load ptr, ptr %151, align 8
  %153 = load i32, ptr %3, align 4
  %154 = sext i32 %153 to i64
  %155 = getelementptr inbounds ptr, ptr %152, i64 %154
  %156 = load ptr, ptr %155, align 8
  %157 = load i8, ptr %156, align 1
  %158 = sext i8 %157 to i32
  %159 = call i32 (ptr, ...) @printf(ptr noundef @.str.17, i32 noundef %158)
  br label %214

160:                                              ; preds = %113
  %161 = load ptr, ptr %2, align 8
  %162 = getelementptr inbounds %struct.qc_map, ptr %161, i32 0, i32 1
  %163 = load ptr, ptr %162, align 8
  %164 = load i32, ptr %3, align 4
  %165 = sext i32 %164 to i64
  %166 = getelementptr inbounds ptr, ptr %163, i64 %165
  %167 = load ptr, ptr %166, align 8
  %168 = load i8, ptr %167, align 1
  %169 = trunc i8 %168 to i1
  %170 = zext i1 %169 to i64
  %171 = select i1 %169, ptr @.str.3, ptr @.str.4
  %172 = call i32 (ptr, ...) @printf(ptr noundef @.str.10, ptr noundef %171)
  br label %214

173:                                              ; preds = %113
  %174 = load ptr, ptr %2, align 8
  %175 = getelementptr inbounds %struct.qc_map, ptr %174, i32 0, i32 1
  %176 = load ptr, ptr %175, align 8
  %177 = load i32, ptr %3, align 4
  %178 = sext i32 %177 to i64
  %179 = getelementptr inbounds ptr, ptr %176, i64 %178
  %180 = load ptr, ptr %179, align 8
  %181 = load i8, ptr %180, align 1
  %182 = zext i8 %181 to i32
  %183 = and i32 %182, 3
  %184 = trunc i32 %183 to i8
  store i8 %184, ptr %5, align 1
  %185 = load i8, ptr %5, align 1
  %186 = zext i8 %185 to i32
  %187 = icmp eq i32 %186, 0
  br i1 %187, label %188, label %189

188:                                              ; preds = %173
  br label %202

189:                                              ; preds = %173
  %190 = load i8, ptr %5, align 1
  %191 = zext i8 %190 to i32
  %192 = icmp eq i32 %191, 1
  br i1 %192, label %193, label %194

193:                                              ; preds = %189
  br label %200

194:                                              ; preds = %189
  %195 = load i8, ptr %5, align 1
  %196 = zext i8 %195 to i32
  %197 = icmp eq i32 %196, 2
  %198 = zext i1 %197 to i64
  %199 = select i1 %197, ptr @.str.7, ptr @.str.8
  br label %200

200:                                              ; preds = %194, %193
  %201 = phi ptr [ @.str.6, %193 ], [ %199, %194 ]
  br label %202

202:                                              ; preds = %200, %188
  %203 = phi ptr [ @.str.5, %188 ], [ %201, %200 ]
  %204 = call i32 (ptr, ...) @printf(ptr noundef @.str.10, ptr noundef %203)
  br label %214

205:                                              ; preds = %113
  %206 = load ptr, ptr %2, align 8
  %207 = getelementptr inbounds %struct.qc_map, ptr %206, i32 0, i32 1
  %208 = load ptr, ptr %207, align 8
  %209 = load i32, ptr %3, align 4
  %210 = sext i32 %209 to i64
  %211 = getelementptr inbounds ptr, ptr %208, i64 %210
  %212 = load ptr, ptr %211, align 8
  %213 = call i32 (ptr, ...) @printf(ptr noundef @.str.16, ptr noundef %212)
  br label %214

214:                                              ; preds = %205, %202, %160, %149, %139, %128, %118, %113
  %215 = load i32, ptr %3, align 4
  %216 = load ptr, ptr %2, align 8
  %217 = getelementptr inbounds %struct.qc_map, ptr %216, i32 0, i32 2
  %218 = load i32, ptr %217, align 8
  %219 = sub nsw i32 %218, 1
  %220 = icmp slt i32 %215, %219
  br i1 %220, label %221, label %223

221:                                              ; preds = %214
  %222 = call i32 (ptr, ...) @printf(ptr noundef @.str.14)
  br label %223

223:                                              ; preds = %221, %214
  br label %224

224:                                              ; preds = %223
  %225 = load i32, ptr %3, align 4
  %226 = add nsw i32 %225, 1
  store i32 %226, ptr %3, align 4
  br label %7, !llvm.loop !37

227:                                              ; preds = %7
  %228 = call i32 (ptr, ...) @printf(ptr noundef @.str.22)
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_map_to_string(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca [128 x i8], align 16
  %9 = alloca i8, align 1
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i8, align 1
  %13 = alloca i32, align 4
  store ptr %0, ptr %2, align 8
  store i32 256, ptr %3, align 4
  %14 = load i32, ptr %3, align 4
  %15 = sext i32 %14 to i64
  %16 = call noalias ptr @malloc(i64 noundef %15) #10
  store ptr %16, ptr %4, align 8
  %17 = load ptr, ptr %4, align 8
  store ptr %17, ptr %5, align 8
  %18 = load i32, ptr %3, align 4
  store i32 %18, ptr %6, align 4
  %19 = load ptr, ptr %5, align 8
  %20 = getelementptr inbounds i8, ptr %19, i32 1
  store ptr %20, ptr %5, align 8
  store i8 123, ptr %19, align 1
  %21 = load i32, ptr %6, align 4
  %22 = add nsw i32 %21, -1
  store i32 %22, ptr %6, align 4
  store i32 0, ptr %7, align 4
  br label %23

23:                                               ; preds = %340, %1
  %24 = load i32, ptr %7, align 4
  %25 = load ptr, ptr %2, align 8
  %26 = getelementptr inbounds %struct.qc_map, ptr %25, i32 0, i32 2
  %27 = load i32, ptr %26, align 8
  %28 = icmp slt i32 %24, %27
  br i1 %28, label %29, label %343

29:                                               ; preds = %23
  %30 = load ptr, ptr %2, align 8
  %31 = getelementptr inbounds %struct.qc_map, ptr %30, i32 0, i32 4
  %32 = load i32, ptr %31, align 8
  switch i32 %32, label %136 [
    i32 0, label %33
    i32 1, label %44
    i32 2, label %56
    i32 3, label %67
    i32 4, label %79
    i32 5, label %93
    i32 6, label %126
  ]

33:                                               ; preds = %29
  %34 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %35 = load ptr, ptr %2, align 8
  %36 = getelementptr inbounds %struct.qc_map, ptr %35, i32 0, i32 0
  %37 = load ptr, ptr %36, align 8
  %38 = load i32, ptr %7, align 4
  %39 = sext i32 %38 to i64
  %40 = getelementptr inbounds ptr, ptr %37, i64 %39
  %41 = load ptr, ptr %40, align 8
  %42 = load i32, ptr %41, align 4
  %43 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %34, i64 noundef 128, ptr noundef @.str.1, i32 noundef %42) #11
  br label %136

44:                                               ; preds = %29
  %45 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %46 = load ptr, ptr %2, align 8
  %47 = getelementptr inbounds %struct.qc_map, ptr %46, i32 0, i32 0
  %48 = load ptr, ptr %47, align 8
  %49 = load i32, ptr %7, align 4
  %50 = sext i32 %49 to i64
  %51 = getelementptr inbounds ptr, ptr %48, i64 %50
  %52 = load ptr, ptr %51, align 8
  %53 = load float, ptr %52, align 4
  %54 = fpext float %53 to double
  %55 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %45, i64 noundef 128, ptr noundef @.str.2, double noundef %54) #11
  br label %136

56:                                               ; preds = %29
  %57 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %58 = load ptr, ptr %2, align 8
  %59 = getelementptr inbounds %struct.qc_map, ptr %58, i32 0, i32 0
  %60 = load ptr, ptr %59, align 8
  %61 = load i32, ptr %7, align 4
  %62 = sext i32 %61 to i64
  %63 = getelementptr inbounds ptr, ptr %60, i64 %62
  %64 = load ptr, ptr %63, align 8
  %65 = load double, ptr %64, align 8
  %66 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %57, i64 noundef 128, ptr noundef @.str.2, double noundef %65) #11
  br label %136

67:                                               ; preds = %29
  %68 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %69 = load ptr, ptr %2, align 8
  %70 = getelementptr inbounds %struct.qc_map, ptr %69, i32 0, i32 0
  %71 = load ptr, ptr %70, align 8
  %72 = load i32, ptr %7, align 4
  %73 = sext i32 %72 to i64
  %74 = getelementptr inbounds ptr, ptr %71, i64 %73
  %75 = load ptr, ptr %74, align 8
  %76 = load i8, ptr %75, align 1
  %77 = sext i8 %76 to i32
  %78 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %68, i64 noundef 128, ptr noundef @.str.17, i32 noundef %77) #11
  br label %136

79:                                               ; preds = %29
  %80 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %81 = load ptr, ptr %2, align 8
  %82 = getelementptr inbounds %struct.qc_map, ptr %81, i32 0, i32 0
  %83 = load ptr, ptr %82, align 8
  %84 = load i32, ptr %7, align 4
  %85 = sext i32 %84 to i64
  %86 = getelementptr inbounds ptr, ptr %83, i64 %85
  %87 = load ptr, ptr %86, align 8
  %88 = load i8, ptr %87, align 1
  %89 = trunc i8 %88 to i1
  %90 = zext i1 %89 to i64
  %91 = select i1 %89, ptr @.str.3, ptr @.str.4
  %92 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %80, i64 noundef 128, ptr noundef @.str.10, ptr noundef %91) #11
  br label %136

93:                                               ; preds = %29
  %94 = load ptr, ptr %2, align 8
  %95 = getelementptr inbounds %struct.qc_map, ptr %94, i32 0, i32 0
  %96 = load ptr, ptr %95, align 8
  %97 = load i32, ptr %7, align 4
  %98 = sext i32 %97 to i64
  %99 = getelementptr inbounds ptr, ptr %96, i64 %98
  %100 = load ptr, ptr %99, align 8
  %101 = load i8, ptr %100, align 1
  %102 = zext i8 %101 to i32
  %103 = and i32 %102, 3
  %104 = trunc i32 %103 to i8
  store i8 %104, ptr %9, align 1
  %105 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %106 = load i8, ptr %9, align 1
  %107 = zext i8 %106 to i32
  %108 = icmp eq i32 %107, 0
  br i1 %108, label %109, label %110

109:                                              ; preds = %93
  br label %123

110:                                              ; preds = %93
  %111 = load i8, ptr %9, align 1
  %112 = zext i8 %111 to i32
  %113 = icmp eq i32 %112, 1
  br i1 %113, label %114, label %115

114:                                              ; preds = %110
  br label %121

115:                                              ; preds = %110
  %116 = load i8, ptr %9, align 1
  %117 = zext i8 %116 to i32
  %118 = icmp eq i32 %117, 2
  %119 = zext i1 %118 to i64
  %120 = select i1 %118, ptr @.str.7, ptr @.str.8
  br label %121

121:                                              ; preds = %115, %114
  %122 = phi ptr [ @.str.6, %114 ], [ %120, %115 ]
  br label %123

123:                                              ; preds = %121, %109
  %124 = phi ptr [ @.str.5, %109 ], [ %122, %121 ]
  %125 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %105, i64 noundef 128, ptr noundef @.str.10, ptr noundef %124) #11
  br label %136

126:                                              ; preds = %29
  %127 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %128 = load ptr, ptr %2, align 8
  %129 = getelementptr inbounds %struct.qc_map, ptr %128, i32 0, i32 0
  %130 = load ptr, ptr %129, align 8
  %131 = load i32, ptr %7, align 4
  %132 = sext i32 %131 to i64
  %133 = getelementptr inbounds ptr, ptr %130, i64 %132
  %134 = load ptr, ptr %133, align 8
  %135 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %127, i64 noundef 128, ptr noundef @.str.16, ptr noundef %134) #11
  br label %136

136:                                              ; preds = %126, %123, %79, %67, %56, %44, %33, %29
  %137 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %138 = call i64 @strlen(ptr noundef %137) #9
  %139 = trunc i64 %138 to i32
  store i32 %139, ptr %10, align 4
  %140 = load i32, ptr %6, align 4
  %141 = load i32, ptr %10, align 4
  %142 = add nsw i32 %141, 10
  %143 = icmp slt i32 %140, %142
  br i1 %143, label %144, label %164

144:                                              ; preds = %136
  %145 = load ptr, ptr %5, align 8
  %146 = load ptr, ptr %4, align 8
  %147 = ptrtoint ptr %145 to i64
  %148 = ptrtoint ptr %146 to i64
  %149 = sub i64 %147, %148
  %150 = trunc i64 %149 to i32
  store i32 %150, ptr %11, align 4
  %151 = load i32, ptr %3, align 4
  %152 = mul nsw i32 %151, 2
  store i32 %152, ptr %3, align 4
  %153 = load ptr, ptr %4, align 8
  %154 = load i32, ptr %3, align 4
  %155 = sext i32 %154 to i64
  %156 = call ptr @realloc(ptr noundef %153, i64 noundef %155) #12
  store ptr %156, ptr %4, align 8
  %157 = load ptr, ptr %4, align 8
  %158 = load i32, ptr %11, align 4
  %159 = sext i32 %158 to i64
  %160 = getelementptr inbounds i8, ptr %157, i64 %159
  store ptr %160, ptr %5, align 8
  %161 = load i32, ptr %3, align 4
  %162 = load i32, ptr %11, align 4
  %163 = sub nsw i32 %161, %162
  store i32 %163, ptr %6, align 4
  br label %164

164:                                              ; preds = %144, %136
  %165 = load ptr, ptr %5, align 8
  %166 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %167 = call ptr @strcpy(ptr noundef %165, ptr noundef %166) #11
  %168 = load i32, ptr %10, align 4
  %169 = load ptr, ptr %5, align 8
  %170 = sext i32 %168 to i64
  %171 = getelementptr inbounds i8, ptr %169, i64 %170
  store ptr %171, ptr %5, align 8
  %172 = load i32, ptr %10, align 4
  %173 = load i32, ptr %6, align 4
  %174 = sub nsw i32 %173, %172
  store i32 %174, ptr %6, align 4
  %175 = load ptr, ptr %5, align 8
  %176 = getelementptr inbounds i8, ptr %175, i32 1
  store ptr %176, ptr %5, align 8
  store i8 58, ptr %175, align 1
  %177 = load ptr, ptr %5, align 8
  %178 = getelementptr inbounds i8, ptr %177, i32 1
  store ptr %178, ptr %5, align 8
  store i8 32, ptr %177, align 1
  %179 = load i32, ptr %6, align 4
  %180 = sub nsw i32 %179, 2
  store i32 %180, ptr %6, align 4
  %181 = load ptr, ptr %2, align 8
  %182 = getelementptr inbounds %struct.qc_map, ptr %181, i32 0, i32 5
  %183 = load i32, ptr %182, align 4
  switch i32 %183, label %287 [
    i32 0, label %184
    i32 1, label %195
    i32 2, label %207
    i32 3, label %218
    i32 4, label %230
    i32 5, label %244
    i32 6, label %277
  ]

184:                                              ; preds = %164
  %185 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %186 = load ptr, ptr %2, align 8
  %187 = getelementptr inbounds %struct.qc_map, ptr %186, i32 0, i32 1
  %188 = load ptr, ptr %187, align 8
  %189 = load i32, ptr %7, align 4
  %190 = sext i32 %189 to i64
  %191 = getelementptr inbounds ptr, ptr %188, i64 %190
  %192 = load ptr, ptr %191, align 8
  %193 = load i32, ptr %192, align 4
  %194 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %185, i64 noundef 128, ptr noundef @.str.1, i32 noundef %193) #11
  br label %287

195:                                              ; preds = %164
  %196 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %197 = load ptr, ptr %2, align 8
  %198 = getelementptr inbounds %struct.qc_map, ptr %197, i32 0, i32 1
  %199 = load ptr, ptr %198, align 8
  %200 = load i32, ptr %7, align 4
  %201 = sext i32 %200 to i64
  %202 = getelementptr inbounds ptr, ptr %199, i64 %201
  %203 = load ptr, ptr %202, align 8
  %204 = load float, ptr %203, align 4
  %205 = fpext float %204 to double
  %206 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %196, i64 noundef 128, ptr noundef @.str.2, double noundef %205) #11
  br label %287

207:                                              ; preds = %164
  %208 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %209 = load ptr, ptr %2, align 8
  %210 = getelementptr inbounds %struct.qc_map, ptr %209, i32 0, i32 1
  %211 = load ptr, ptr %210, align 8
  %212 = load i32, ptr %7, align 4
  %213 = sext i32 %212 to i64
  %214 = getelementptr inbounds ptr, ptr %211, i64 %213
  %215 = load ptr, ptr %214, align 8
  %216 = load double, ptr %215, align 8
  %217 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %208, i64 noundef 128, ptr noundef @.str.2, double noundef %216) #11
  br label %287

218:                                              ; preds = %164
  %219 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %220 = load ptr, ptr %2, align 8
  %221 = getelementptr inbounds %struct.qc_map, ptr %220, i32 0, i32 1
  %222 = load ptr, ptr %221, align 8
  %223 = load i32, ptr %7, align 4
  %224 = sext i32 %223 to i64
  %225 = getelementptr inbounds ptr, ptr %222, i64 %224
  %226 = load ptr, ptr %225, align 8
  %227 = load i8, ptr %226, align 1
  %228 = sext i8 %227 to i32
  %229 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %219, i64 noundef 128, ptr noundef @.str.17, i32 noundef %228) #11
  br label %287

230:                                              ; preds = %164
  %231 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %232 = load ptr, ptr %2, align 8
  %233 = getelementptr inbounds %struct.qc_map, ptr %232, i32 0, i32 1
  %234 = load ptr, ptr %233, align 8
  %235 = load i32, ptr %7, align 4
  %236 = sext i32 %235 to i64
  %237 = getelementptr inbounds ptr, ptr %234, i64 %236
  %238 = load ptr, ptr %237, align 8
  %239 = load i8, ptr %238, align 1
  %240 = trunc i8 %239 to i1
  %241 = zext i1 %240 to i64
  %242 = select i1 %240, ptr @.str.3, ptr @.str.4
  %243 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %231, i64 noundef 128, ptr noundef @.str.10, ptr noundef %242) #11
  br label %287

244:                                              ; preds = %164
  %245 = load ptr, ptr %2, align 8
  %246 = getelementptr inbounds %struct.qc_map, ptr %245, i32 0, i32 1
  %247 = load ptr, ptr %246, align 8
  %248 = load i32, ptr %7, align 4
  %249 = sext i32 %248 to i64
  %250 = getelementptr inbounds ptr, ptr %247, i64 %249
  %251 = load ptr, ptr %250, align 8
  %252 = load i8, ptr %251, align 1
  %253 = zext i8 %252 to i32
  %254 = and i32 %253, 3
  %255 = trunc i32 %254 to i8
  store i8 %255, ptr %12, align 1
  %256 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %257 = load i8, ptr %12, align 1
  %258 = zext i8 %257 to i32
  %259 = icmp eq i32 %258, 0
  br i1 %259, label %260, label %261

260:                                              ; preds = %244
  br label %274

261:                                              ; preds = %244
  %262 = load i8, ptr %12, align 1
  %263 = zext i8 %262 to i32
  %264 = icmp eq i32 %263, 1
  br i1 %264, label %265, label %266

265:                                              ; preds = %261
  br label %272

266:                                              ; preds = %261
  %267 = load i8, ptr %12, align 1
  %268 = zext i8 %267 to i32
  %269 = icmp eq i32 %268, 2
  %270 = zext i1 %269 to i64
  %271 = select i1 %269, ptr @.str.7, ptr @.str.8
  br label %272

272:                                              ; preds = %266, %265
  %273 = phi ptr [ @.str.6, %265 ], [ %271, %266 ]
  br label %274

274:                                              ; preds = %272, %260
  %275 = phi ptr [ @.str.5, %260 ], [ %273, %272 ]
  %276 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %256, i64 noundef 128, ptr noundef @.str.10, ptr noundef %275) #11
  br label %287

277:                                              ; preds = %164
  %278 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %279 = load ptr, ptr %2, align 8
  %280 = getelementptr inbounds %struct.qc_map, ptr %279, i32 0, i32 1
  %281 = load ptr, ptr %280, align 8
  %282 = load i32, ptr %7, align 4
  %283 = sext i32 %282 to i64
  %284 = getelementptr inbounds ptr, ptr %281, i64 %283
  %285 = load ptr, ptr %284, align 8
  %286 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %278, i64 noundef 128, ptr noundef @.str.16, ptr noundef %285) #11
  br label %287

287:                                              ; preds = %277, %274, %230, %218, %207, %195, %184, %164
  %288 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %289 = call i64 @strlen(ptr noundef %288) #9
  %290 = trunc i64 %289 to i32
  store i32 %290, ptr %10, align 4
  %291 = load i32, ptr %6, align 4
  %292 = load i32, ptr %10, align 4
  %293 = add nsw i32 %292, 10
  %294 = icmp slt i32 %291, %293
  br i1 %294, label %295, label %315

295:                                              ; preds = %287
  %296 = load ptr, ptr %5, align 8
  %297 = load ptr, ptr %4, align 8
  %298 = ptrtoint ptr %296 to i64
  %299 = ptrtoint ptr %297 to i64
  %300 = sub i64 %298, %299
  %301 = trunc i64 %300 to i32
  store i32 %301, ptr %13, align 4
  %302 = load i32, ptr %3, align 4
  %303 = mul nsw i32 %302, 2
  store i32 %303, ptr %3, align 4
  %304 = load ptr, ptr %4, align 8
  %305 = load i32, ptr %3, align 4
  %306 = sext i32 %305 to i64
  %307 = call ptr @realloc(ptr noundef %304, i64 noundef %306) #12
  store ptr %307, ptr %4, align 8
  %308 = load ptr, ptr %4, align 8
  %309 = load i32, ptr %13, align 4
  %310 = sext i32 %309 to i64
  %311 = getelementptr inbounds i8, ptr %308, i64 %310
  store ptr %311, ptr %5, align 8
  %312 = load i32, ptr %3, align 4
  %313 = load i32, ptr %13, align 4
  %314 = sub nsw i32 %312, %313
  store i32 %314, ptr %6, align 4
  br label %315

315:                                              ; preds = %295, %287
  %316 = load ptr, ptr %5, align 8
  %317 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %318 = call ptr @strcpy(ptr noundef %316, ptr noundef %317) #11
  %319 = load i32, ptr %10, align 4
  %320 = load ptr, ptr %5, align 8
  %321 = sext i32 %319 to i64
  %322 = getelementptr inbounds i8, ptr %320, i64 %321
  store ptr %322, ptr %5, align 8
  %323 = load i32, ptr %10, align 4
  %324 = load i32, ptr %6, align 4
  %325 = sub nsw i32 %324, %323
  store i32 %325, ptr %6, align 4
  %326 = load i32, ptr %7, align 4
  %327 = load ptr, ptr %2, align 8
  %328 = getelementptr inbounds %struct.qc_map, ptr %327, i32 0, i32 2
  %329 = load i32, ptr %328, align 8
  %330 = sub nsw i32 %329, 1
  %331 = icmp slt i32 %326, %330
  br i1 %331, label %332, label %339

332:                                              ; preds = %315
  %333 = load ptr, ptr %5, align 8
  %334 = getelementptr inbounds i8, ptr %333, i32 1
  store ptr %334, ptr %5, align 8
  store i8 44, ptr %333, align 1
  %335 = load ptr, ptr %5, align 8
  %336 = getelementptr inbounds i8, ptr %335, i32 1
  store ptr %336, ptr %5, align 8
  store i8 32, ptr %335, align 1
  %337 = load i32, ptr %6, align 4
  %338 = sub nsw i32 %337, 2
  store i32 %338, ptr %6, align 4
  br label %339

339:                                              ; preds = %332, %315
  br label %340

340:                                              ; preds = %339
  %341 = load i32, ptr %7, align 4
  %342 = add nsw i32 %341, 1
  store i32 %342, ptr %7, align 4
  br label %23, !llvm.loop !38

343:                                              ; preds = %23
  %344 = load ptr, ptr %5, align 8
  %345 = getelementptr inbounds i8, ptr %344, i32 1
  store ptr %345, ptr %5, align 8
  store i8 125, ptr %344, align 1
  %346 = load ptr, ptr %5, align 8
  store i8 0, ptr %346, align 1
  %347 = load ptr, ptr %4, align 8
  ret ptr %347
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local i32 @qc_map_size(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %struct.qc_map, ptr %3, i32 0, i32 2
  %5 = load i32, ptr %4, align 8
  ret i32 %5
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_map_keys(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca ptr, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %7 = load ptr, ptr %2, align 8
  %8 = getelementptr inbounds %struct.qc_map, ptr %7, i32 0, i32 4
  %9 = load i32, ptr %8, align 8
  %10 = call ptr @qc_create_list(i32 noundef %9)
  store ptr %10, ptr %3, align 8
  %11 = load ptr, ptr %2, align 8
  %12 = getelementptr inbounds %struct.qc_map, ptr %11, i32 0, i32 2
  %13 = load i32, ptr %12, align 8
  %14 = load ptr, ptr %3, align 8
  %15 = getelementptr inbounds %struct.qc_list, ptr %14, i32 0, i32 2
  %16 = load i32, ptr %15, align 4
  %17 = icmp sgt i32 %13, %16
  br i1 %17, label %18, label %35

18:                                               ; preds = %1
  %19 = load ptr, ptr %2, align 8
  %20 = getelementptr inbounds %struct.qc_map, ptr %19, i32 0, i32 2
  %21 = load i32, ptr %20, align 8
  %22 = load ptr, ptr %3, align 8
  %23 = getelementptr inbounds %struct.qc_list, ptr %22, i32 0, i32 2
  store i32 %21, ptr %23, align 4
  %24 = load ptr, ptr %3, align 8
  %25 = getelementptr inbounds %struct.qc_list, ptr %24, i32 0, i32 0
  %26 = load ptr, ptr %25, align 8
  %27 = load ptr, ptr %3, align 8
  %28 = getelementptr inbounds %struct.qc_list, ptr %27, i32 0, i32 2
  %29 = load i32, ptr %28, align 4
  %30 = sext i32 %29 to i64
  %31 = mul i64 %30, 8
  %32 = call ptr @realloc(ptr noundef %26, i64 noundef %31) #12
  %33 = load ptr, ptr %3, align 8
  %34 = getelementptr inbounds %struct.qc_list, ptr %33, i32 0, i32 0
  store ptr %32, ptr %34, align 8
  br label %35

35:                                               ; preds = %18, %1
  store i32 0, ptr %4, align 4
  br label %36

36:                                               ; preds = %108, %35
  %37 = load i32, ptr %4, align 4
  %38 = load ptr, ptr %2, align 8
  %39 = getelementptr inbounds %struct.qc_map, ptr %38, i32 0, i32 2
  %40 = load i32, ptr %39, align 8
  %41 = icmp slt i32 %37, %40
  br i1 %41, label %42, label %111

42:                                               ; preds = %36
  %43 = load ptr, ptr %2, align 8
  %44 = getelementptr inbounds %struct.qc_map, ptr %43, i32 0, i32 4
  %45 = load i32, ptr %44, align 8
  %46 = icmp sle i32 %45, 5
  br i1 %46, label %47, label %72

47:                                               ; preds = %42
  %48 = load ptr, ptr %2, align 8
  %49 = getelementptr inbounds %struct.qc_map, ptr %48, i32 0, i32 4
  %50 = load i32, ptr %49, align 8
  %51 = call i32 @sizeof_type(i32 noundef %50)
  store i32 %51, ptr %5, align 4
  %52 = load i32, ptr %5, align 4
  %53 = sext i32 %52 to i64
  %54 = call noalias ptr @malloc(i64 noundef %53) #10
  store ptr %54, ptr %6, align 8
  %55 = load ptr, ptr %6, align 8
  %56 = load ptr, ptr %2, align 8
  %57 = getelementptr inbounds %struct.qc_map, ptr %56, i32 0, i32 0
  %58 = load ptr, ptr %57, align 8
  %59 = load i32, ptr %4, align 4
  %60 = sext i32 %59 to i64
  %61 = getelementptr inbounds ptr, ptr %58, i64 %60
  %62 = load ptr, ptr %61, align 8
  %63 = load i32, ptr %5, align 4
  %64 = sext i32 %63 to i64
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %55, ptr align 1 %62, i64 %64, i1 false)
  %65 = load ptr, ptr %6, align 8
  %66 = load ptr, ptr %3, align 8
  %67 = getelementptr inbounds %struct.qc_list, ptr %66, i32 0, i32 0
  %68 = load ptr, ptr %67, align 8
  %69 = load i32, ptr %4, align 4
  %70 = sext i32 %69 to i64
  %71 = getelementptr inbounds ptr, ptr %68, i64 %70
  store ptr %65, ptr %71, align 8
  br label %107

72:                                               ; preds = %42
  %73 = load ptr, ptr %2, align 8
  %74 = getelementptr inbounds %struct.qc_map, ptr %73, i32 0, i32 4
  %75 = load i32, ptr %74, align 8
  %76 = icmp eq i32 %75, 6
  br i1 %76, label %77, label %92

77:                                               ; preds = %72
  %78 = load ptr, ptr %2, align 8
  %79 = getelementptr inbounds %struct.qc_map, ptr %78, i32 0, i32 0
  %80 = load ptr, ptr %79, align 8
  %81 = load i32, ptr %4, align 4
  %82 = sext i32 %81 to i64
  %83 = getelementptr inbounds ptr, ptr %80, i64 %82
  %84 = load ptr, ptr %83, align 8
  %85 = call noalias ptr @strdup(ptr noundef %84) #11
  %86 = load ptr, ptr %3, align 8
  %87 = getelementptr inbounds %struct.qc_list, ptr %86, i32 0, i32 0
  %88 = load ptr, ptr %87, align 8
  %89 = load i32, ptr %4, align 4
  %90 = sext i32 %89 to i64
  %91 = getelementptr inbounds ptr, ptr %88, i64 %90
  store ptr %85, ptr %91, align 8
  br label %106

92:                                               ; preds = %72
  %93 = load ptr, ptr %2, align 8
  %94 = getelementptr inbounds %struct.qc_map, ptr %93, i32 0, i32 0
  %95 = load ptr, ptr %94, align 8
  %96 = load i32, ptr %4, align 4
  %97 = sext i32 %96 to i64
  %98 = getelementptr inbounds ptr, ptr %95, i64 %97
  %99 = load ptr, ptr %98, align 8
  %100 = load ptr, ptr %3, align 8
  %101 = getelementptr inbounds %struct.qc_list, ptr %100, i32 0, i32 0
  %102 = load ptr, ptr %101, align 8
  %103 = load i32, ptr %4, align 4
  %104 = sext i32 %103 to i64
  %105 = getelementptr inbounds ptr, ptr %102, i64 %104
  store ptr %99, ptr %105, align 8
  br label %106

106:                                              ; preds = %92, %77
  br label %107

107:                                              ; preds = %106, %47
  br label %108

108:                                              ; preds = %107
  %109 = load i32, ptr %4, align 4
  %110 = add nsw i32 %109, 1
  store i32 %110, ptr %4, align 4
  br label %36, !llvm.loop !39

111:                                              ; preds = %36
  %112 = load ptr, ptr %2, align 8
  %113 = getelementptr inbounds %struct.qc_map, ptr %112, i32 0, i32 2
  %114 = load i32, ptr %113, align 8
  %115 = load ptr, ptr %3, align 8
  %116 = getelementptr inbounds %struct.qc_list, ptr %115, i32 0, i32 1
  store i32 %114, ptr %116, align 8
  %117 = load ptr, ptr %3, align 8
  ret ptr %117
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local ptr @qc_spread_call(ptr noundef %0, i32 noundef %1, ptr noundef %2, ptr noundef %3, i32 noundef %4, ptr noundef %5) #5 {
  %7 = alloca ptr, align 8
  %8 = alloca i32, align 4
  %9 = alloca ptr, align 8
  %10 = alloca ptr, align 8
  %11 = alloca i32, align 4
  %12 = alloca ptr, align 8
  %13 = alloca %struct.ffi_cif, align 8
  %14 = alloca ptr, align 8
  %15 = alloca i32, align 4
  %16 = alloca ptr, align 8
  store ptr %0, ptr %7, align 8
  store i32 %1, ptr %8, align 4
  store ptr %2, ptr %9, align 8
  store ptr %3, ptr %10, align 8
  store i32 %4, ptr %11, align 4
  store ptr %5, ptr %12, align 8
  %17 = load i32, ptr %8, align 4
  %18 = sext i32 %17 to i64
  %19 = mul i64 %18, 8
  %20 = call noalias ptr @malloc(i64 noundef %19) #10
  store ptr %20, ptr %14, align 8
  store i32 0, ptr %15, align 4
  br label %21

21:                                               ; preds = %72, %6
  %22 = load i32, ptr %15, align 4
  %23 = load i32, ptr %8, align 4
  %24 = icmp slt i32 %22, %23
  br i1 %24, label %25, label %75

25:                                               ; preds = %21
  %26 = load ptr, ptr %10, align 8
  %27 = load i32, ptr %15, align 4
  %28 = sext i32 %27 to i64
  %29 = getelementptr inbounds i32, ptr %26, i64 %28
  %30 = load i32, ptr %29, align 4
  switch i32 %30, label %66 [
    i32 0, label %31
    i32 1, label %36
    i32 2, label %41
    i32 3, label %46
    i32 4, label %51
    i32 5, label %56
    i32 6, label %61
  ]

31:                                               ; preds = %25
  %32 = load ptr, ptr %14, align 8
  %33 = load i32, ptr %15, align 4
  %34 = sext i32 %33 to i64
  %35 = getelementptr inbounds ptr, ptr %32, i64 %34
  store ptr @ffi_type_sint32, ptr %35, align 8
  br label %71

36:                                               ; preds = %25
  %37 = load ptr, ptr %14, align 8
  %38 = load i32, ptr %15, align 4
  %39 = sext i32 %38 to i64
  %40 = getelementptr inbounds ptr, ptr %37, i64 %39
  store ptr @ffi_type_float, ptr %40, align 8
  br label %71

41:                                               ; preds = %25
  %42 = load ptr, ptr %14, align 8
  %43 = load i32, ptr %15, align 4
  %44 = sext i32 %43 to i64
  %45 = getelementptr inbounds ptr, ptr %42, i64 %44
  store ptr @ffi_type_double, ptr %45, align 8
  br label %71

46:                                               ; preds = %25
  %47 = load ptr, ptr %14, align 8
  %48 = load i32, ptr %15, align 4
  %49 = sext i32 %48 to i64
  %50 = getelementptr inbounds ptr, ptr %47, i64 %49
  store ptr @ffi_type_sint8, ptr %50, align 8
  br label %71

51:                                               ; preds = %25
  %52 = load ptr, ptr %14, align 8
  %53 = load i32, ptr %15, align 4
  %54 = sext i32 %53 to i64
  %55 = getelementptr inbounds ptr, ptr %52, i64 %54
  store ptr @ffi_type_uint8, ptr %55, align 8
  br label %71

56:                                               ; preds = %25
  %57 = load ptr, ptr %14, align 8
  %58 = load i32, ptr %15, align 4
  %59 = sext i32 %58 to i64
  %60 = getelementptr inbounds ptr, ptr %57, i64 %59
  store ptr @ffi_type_uint8, ptr %60, align 8
  br label %71

61:                                               ; preds = %25
  %62 = load ptr, ptr %14, align 8
  %63 = load i32, ptr %15, align 4
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds ptr, ptr %62, i64 %64
  store ptr @ffi_type_pointer, ptr %65, align 8
  br label %71

66:                                               ; preds = %25
  %67 = load ptr, ptr %14, align 8
  %68 = load i32, ptr %15, align 4
  %69 = sext i32 %68 to i64
  %70 = getelementptr inbounds ptr, ptr %67, i64 %69
  store ptr @ffi_type_pointer, ptr %70, align 8
  br label %71

71:                                               ; preds = %66, %61, %56, %51, %46, %41, %36, %31
  br label %72

72:                                               ; preds = %71
  %73 = load i32, ptr %15, align 4
  %74 = add nsw i32 %73, 1
  store i32 %74, ptr %15, align 4
  br label %21, !llvm.loop !40

75:                                               ; preds = %21
  %76 = load i32, ptr %11, align 4
  switch i32 %76, label %85 [
    i32 -1, label %77
    i32 0, label %78
    i32 1, label %79
    i32 2, label %80
    i32 3, label %81
    i32 4, label %82
    i32 5, label %83
    i32 6, label %84
  ]

77:                                               ; preds = %75
  store ptr @ffi_type_void, ptr %16, align 8
  br label %86

78:                                               ; preds = %75
  store ptr @ffi_type_sint32, ptr %16, align 8
  br label %86

79:                                               ; preds = %75
  store ptr @ffi_type_float, ptr %16, align 8
  br label %86

80:                                               ; preds = %75
  store ptr @ffi_type_double, ptr %16, align 8
  br label %86

81:                                               ; preds = %75
  store ptr @ffi_type_sint8, ptr %16, align 8
  br label %86

82:                                               ; preds = %75
  store ptr @ffi_type_uint8, ptr %16, align 8
  br label %86

83:                                               ; preds = %75
  store ptr @ffi_type_uint8, ptr %16, align 8
  br label %86

84:                                               ; preds = %75
  store ptr @ffi_type_pointer, ptr %16, align 8
  br label %86

85:                                               ; preds = %75
  store ptr @ffi_type_pointer, ptr %16, align 8
  br label %86

86:                                               ; preds = %85, %84, %83, %82, %81, %80, %79, %78, %77
  %87 = load i32, ptr %8, align 4
  %88 = load ptr, ptr %16, align 8
  %89 = load ptr, ptr %14, align 8
  %90 = call i32 @ffi_prep_cif(ptr noundef %13, i32 noundef 2, i32 noundef %87, ptr noundef %88, ptr noundef %89)
  %91 = icmp eq i32 %90, 0
  br i1 %91, label %92, label %96

92:                                               ; preds = %86
  %93 = load ptr, ptr %7, align 8
  %94 = load ptr, ptr %12, align 8
  %95 = load ptr, ptr %9, align 8
  call void @ffi_call(ptr noundef %13, ptr noundef %93, ptr noundef %94, ptr noundef %95)
  br label %96

96:                                               ; preds = %92, %86
  %97 = load ptr, ptr %14, align 8
  call void @free(ptr noundef %97) #11
  %98 = load ptr, ptr %12, align 8
  ret ptr %98
}

declare i32 @ffi_prep_cif(ptr noundef, i32 noundef, i32 noundef, ptr noundef, ptr noundef) #6

declare void @ffi_call(ptr noundef, ptr noundef, ptr noundef, ptr noundef) #6

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_list_to_string(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca [128 x i8], align 16
  %9 = alloca i8, align 1
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  store ptr %0, ptr %2, align 8
  store i32 256, ptr %3, align 4
  %12 = load i32, ptr %3, align 4
  %13 = sext i32 %12 to i64
  %14 = call noalias ptr @malloc(i64 noundef %13) #10
  store ptr %14, ptr %4, align 8
  %15 = load ptr, ptr %4, align 8
  store ptr %15, ptr %5, align 8
  %16 = load i32, ptr %3, align 4
  store i32 %16, ptr %6, align 4
  %17 = load ptr, ptr %5, align 8
  %18 = getelementptr inbounds i8, ptr %17, i32 1
  store ptr %18, ptr %5, align 8
  store i8 91, ptr %17, align 1
  %19 = load i32, ptr %6, align 4
  %20 = add nsw i32 %19, -1
  store i32 %20, ptr %6, align 4
  store i32 0, ptr %7, align 4
  br label %21

21:                                               ; preds = %187, %1
  %22 = load i32, ptr %7, align 4
  %23 = load ptr, ptr %2, align 8
  %24 = getelementptr inbounds %struct.qc_list, ptr %23, i32 0, i32 1
  %25 = load i32, ptr %24, align 8
  %26 = icmp slt i32 %22, %25
  br i1 %26, label %27, label %190

27:                                               ; preds = %21
  %28 = load ptr, ptr %2, align 8
  %29 = getelementptr inbounds %struct.qc_list, ptr %28, i32 0, i32 3
  %30 = load i32, ptr %29, align 8
  switch i32 %30, label %134 [
    i32 0, label %31
    i32 1, label %42
    i32 2, label %54
    i32 3, label %65
    i32 4, label %77
    i32 5, label %91
    i32 6, label %124
  ]

31:                                               ; preds = %27
  %32 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %33 = load ptr, ptr %2, align 8
  %34 = getelementptr inbounds %struct.qc_list, ptr %33, i32 0, i32 0
  %35 = load ptr, ptr %34, align 8
  %36 = load i32, ptr %7, align 4
  %37 = sext i32 %36 to i64
  %38 = getelementptr inbounds ptr, ptr %35, i64 %37
  %39 = load ptr, ptr %38, align 8
  %40 = load i32, ptr %39, align 4
  %41 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %32, i64 noundef 128, ptr noundef @.str.1, i32 noundef %40) #11
  br label %134

42:                                               ; preds = %27
  %43 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %44 = load ptr, ptr %2, align 8
  %45 = getelementptr inbounds %struct.qc_list, ptr %44, i32 0, i32 0
  %46 = load ptr, ptr %45, align 8
  %47 = load i32, ptr %7, align 4
  %48 = sext i32 %47 to i64
  %49 = getelementptr inbounds ptr, ptr %46, i64 %48
  %50 = load ptr, ptr %49, align 8
  %51 = load float, ptr %50, align 4
  %52 = fpext float %51 to double
  %53 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %43, i64 noundef 128, ptr noundef @.str.2, double noundef %52) #11
  br label %134

54:                                               ; preds = %27
  %55 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %56 = load ptr, ptr %2, align 8
  %57 = getelementptr inbounds %struct.qc_list, ptr %56, i32 0, i32 0
  %58 = load ptr, ptr %57, align 8
  %59 = load i32, ptr %7, align 4
  %60 = sext i32 %59 to i64
  %61 = getelementptr inbounds ptr, ptr %58, i64 %60
  %62 = load ptr, ptr %61, align 8
  %63 = load double, ptr %62, align 8
  %64 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %55, i64 noundef 128, ptr noundef @.str.2, double noundef %63) #11
  br label %134

65:                                               ; preds = %27
  %66 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %67 = load ptr, ptr %2, align 8
  %68 = getelementptr inbounds %struct.qc_list, ptr %67, i32 0, i32 0
  %69 = load ptr, ptr %68, align 8
  %70 = load i32, ptr %7, align 4
  %71 = sext i32 %70 to i64
  %72 = getelementptr inbounds ptr, ptr %69, i64 %71
  %73 = load ptr, ptr %72, align 8
  %74 = load i8, ptr %73, align 1
  %75 = sext i8 %74 to i32
  %76 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %66, i64 noundef 128, ptr noundef @.str.17, i32 noundef %75) #11
  br label %134

77:                                               ; preds = %27
  %78 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %79 = load ptr, ptr %2, align 8
  %80 = getelementptr inbounds %struct.qc_list, ptr %79, i32 0, i32 0
  %81 = load ptr, ptr %80, align 8
  %82 = load i32, ptr %7, align 4
  %83 = sext i32 %82 to i64
  %84 = getelementptr inbounds ptr, ptr %81, i64 %83
  %85 = load ptr, ptr %84, align 8
  %86 = load i8, ptr %85, align 1
  %87 = trunc i8 %86 to i1
  %88 = zext i1 %87 to i64
  %89 = select i1 %87, ptr @.str.3, ptr @.str.4
  %90 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %78, i64 noundef 128, ptr noundef @.str.10, ptr noundef %89) #11
  br label %134

91:                                               ; preds = %27
  %92 = load ptr, ptr %2, align 8
  %93 = getelementptr inbounds %struct.qc_list, ptr %92, i32 0, i32 0
  %94 = load ptr, ptr %93, align 8
  %95 = load i32, ptr %7, align 4
  %96 = sext i32 %95 to i64
  %97 = getelementptr inbounds ptr, ptr %94, i64 %96
  %98 = load ptr, ptr %97, align 8
  %99 = load i8, ptr %98, align 1
  %100 = zext i8 %99 to i32
  %101 = and i32 %100, 3
  %102 = trunc i32 %101 to i8
  store i8 %102, ptr %9, align 1
  %103 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %104 = load i8, ptr %9, align 1
  %105 = zext i8 %104 to i32
  %106 = icmp eq i32 %105, 0
  br i1 %106, label %107, label %108

107:                                              ; preds = %91
  br label %121

108:                                              ; preds = %91
  %109 = load i8, ptr %9, align 1
  %110 = zext i8 %109 to i32
  %111 = icmp eq i32 %110, 1
  br i1 %111, label %112, label %113

112:                                              ; preds = %108
  br label %119

113:                                              ; preds = %108
  %114 = load i8, ptr %9, align 1
  %115 = zext i8 %114 to i32
  %116 = icmp eq i32 %115, 2
  %117 = zext i1 %116 to i64
  %118 = select i1 %116, ptr @.str.7, ptr @.str.8
  br label %119

119:                                              ; preds = %113, %112
  %120 = phi ptr [ @.str.6, %112 ], [ %118, %113 ]
  br label %121

121:                                              ; preds = %119, %107
  %122 = phi ptr [ @.str.5, %107 ], [ %120, %119 ]
  %123 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %103, i64 noundef 128, ptr noundef @.str.10, ptr noundef %122) #11
  br label %134

124:                                              ; preds = %27
  %125 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %126 = load ptr, ptr %2, align 8
  %127 = getelementptr inbounds %struct.qc_list, ptr %126, i32 0, i32 0
  %128 = load ptr, ptr %127, align 8
  %129 = load i32, ptr %7, align 4
  %130 = sext i32 %129 to i64
  %131 = getelementptr inbounds ptr, ptr %128, i64 %130
  %132 = load ptr, ptr %131, align 8
  %133 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef %125, i64 noundef 128, ptr noundef @.str.16, ptr noundef %132) #11
  br label %134

134:                                              ; preds = %124, %121, %77, %65, %54, %42, %31, %27
  %135 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %136 = call i64 @strlen(ptr noundef %135) #9
  %137 = trunc i64 %136 to i32
  store i32 %137, ptr %10, align 4
  %138 = load i32, ptr %6, align 4
  %139 = load i32, ptr %10, align 4
  %140 = add nsw i32 %139, 10
  %141 = icmp slt i32 %138, %140
  br i1 %141, label %142, label %162

142:                                              ; preds = %134
  %143 = load ptr, ptr %5, align 8
  %144 = load ptr, ptr %4, align 8
  %145 = ptrtoint ptr %143 to i64
  %146 = ptrtoint ptr %144 to i64
  %147 = sub i64 %145, %146
  %148 = trunc i64 %147 to i32
  store i32 %148, ptr %11, align 4
  %149 = load i32, ptr %3, align 4
  %150 = mul nsw i32 %149, 2
  store i32 %150, ptr %3, align 4
  %151 = load ptr, ptr %4, align 8
  %152 = load i32, ptr %3, align 4
  %153 = sext i32 %152 to i64
  %154 = call ptr @realloc(ptr noundef %151, i64 noundef %153) #12
  store ptr %154, ptr %4, align 8
  %155 = load ptr, ptr %4, align 8
  %156 = load i32, ptr %11, align 4
  %157 = sext i32 %156 to i64
  %158 = getelementptr inbounds i8, ptr %155, i64 %157
  store ptr %158, ptr %5, align 8
  %159 = load i32, ptr %3, align 4
  %160 = load i32, ptr %11, align 4
  %161 = sub nsw i32 %159, %160
  store i32 %161, ptr %6, align 4
  br label %162

162:                                              ; preds = %142, %134
  %163 = load ptr, ptr %5, align 8
  %164 = getelementptr inbounds [128 x i8], ptr %8, i64 0, i64 0
  %165 = call ptr @strcpy(ptr noundef %163, ptr noundef %164) #11
  %166 = load i32, ptr %10, align 4
  %167 = load ptr, ptr %5, align 8
  %168 = sext i32 %166 to i64
  %169 = getelementptr inbounds i8, ptr %167, i64 %168
  store ptr %169, ptr %5, align 8
  %170 = load i32, ptr %10, align 4
  %171 = load i32, ptr %6, align 4
  %172 = sub nsw i32 %171, %170
  store i32 %172, ptr %6, align 4
  %173 = load i32, ptr %7, align 4
  %174 = load ptr, ptr %2, align 8
  %175 = getelementptr inbounds %struct.qc_list, ptr %174, i32 0, i32 1
  %176 = load i32, ptr %175, align 8
  %177 = sub nsw i32 %176, 1
  %178 = icmp slt i32 %173, %177
  br i1 %178, label %179, label %186

179:                                              ; preds = %162
  %180 = load ptr, ptr %5, align 8
  %181 = getelementptr inbounds i8, ptr %180, i32 1
  store ptr %181, ptr %5, align 8
  store i8 44, ptr %180, align 1
  %182 = load ptr, ptr %5, align 8
  %183 = getelementptr inbounds i8, ptr %182, i32 1
  store ptr %183, ptr %5, align 8
  store i8 32, ptr %182, align 1
  %184 = load i32, ptr %6, align 4
  %185 = sub nsw i32 %184, 2
  store i32 %185, ptr %6, align 4
  br label %186

186:                                              ; preds = %179, %162
  br label %187

187:                                              ; preds = %186
  %188 = load i32, ptr %7, align 4
  %189 = add nsw i32 %188, 1
  store i32 %189, ptr %7, align 4
  br label %21, !llvm.loop !41

190:                                              ; preds = %21
  %191 = load ptr, ptr %5, align 8
  %192 = getelementptr inbounds i8, ptr %191, i32 1
  store ptr %192, ptr %5, align 8
  store i8 93, ptr %191, align 1
  %193 = load ptr, ptr %5, align 8
  store i8 0, ptr %193, align 1
  %194 = load ptr, ptr %4, align 8
  ret ptr %194
}

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local ptr @qc_fopen(ptr noundef %0, ptr noundef %1) #5 {
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  store ptr %0, ptr %3, align 8
  store ptr %1, ptr %4, align 8
  %6 = load ptr, ptr %3, align 8
  %7 = load ptr, ptr %4, align 8
  %8 = call noalias ptr @fopen(ptr noundef %6, ptr noundef %7)
  store ptr %8, ptr %5, align 8
  %9 = load ptr, ptr %5, align 8
  ret ptr %9
}

declare noalias ptr @fopen(ptr noundef, ptr noundef) #6

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_fclose(ptr noundef %0) #5 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = icmp ne ptr %3, null
  br i1 %4, label %5, label %8

5:                                                ; preds = %1
  %6 = load ptr, ptr %2, align 8
  %7 = call i32 @fclose(ptr noundef %6)
  br label %8

8:                                                ; preds = %5, %1
  ret void
}

declare i32 @fclose(ptr noundef) #6

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local ptr @qc_fread(ptr noundef %0) #5 {
  %2 = alloca ptr, align 8
  %3 = alloca ptr, align 8
  %4 = alloca [1024 x i8], align 16
  %5 = alloca i64, align 8
  store ptr %0, ptr %3, align 8
  %6 = load ptr, ptr %3, align 8
  %7 = icmp ne ptr %6, null
  br i1 %7, label %10, label %8

8:                                                ; preds = %1
  %9 = call noalias ptr @strdup(ptr noundef @.str) #11
  store ptr %9, ptr %2, align 8
  br label %36

10:                                               ; preds = %1
  %11 = getelementptr inbounds [1024 x i8], ptr %4, i64 0, i64 0
  %12 = load ptr, ptr %3, align 8
  %13 = call ptr @fgets(ptr noundef %11, i32 noundef 1024, ptr noundef %12)
  %14 = icmp ne ptr %13, null
  br i1 %14, label %15, label %34

15:                                               ; preds = %10
  %16 = getelementptr inbounds [1024 x i8], ptr %4, i64 0, i64 0
  %17 = call i64 @strlen(ptr noundef %16) #9
  store i64 %17, ptr %5, align 8
  %18 = load i64, ptr %5, align 8
  %19 = icmp ugt i64 %18, 0
  br i1 %19, label %20, label %31

20:                                               ; preds = %15
  %21 = load i64, ptr %5, align 8
  %22 = sub i64 %21, 1
  %23 = getelementptr inbounds [1024 x i8], ptr %4, i64 0, i64 %22
  %24 = load i8, ptr %23, align 1
  %25 = sext i8 %24 to i32
  %26 = icmp eq i32 %25, 10
  br i1 %26, label %27, label %31

27:                                               ; preds = %20
  %28 = load i64, ptr %5, align 8
  %29 = sub i64 %28, 1
  %30 = getelementptr inbounds [1024 x i8], ptr %4, i64 0, i64 %29
  store i8 0, ptr %30, align 1
  br label %31

31:                                               ; preds = %27, %20, %15
  %32 = getelementptr inbounds [1024 x i8], ptr %4, i64 0, i64 0
  %33 = call noalias ptr @strdup(ptr noundef %32) #11
  store ptr %33, ptr %2, align 8
  br label %36

34:                                               ; preds = %10
  %35 = call noalias ptr @strdup(ptr noundef @.str) #11
  store ptr %35, ptr %2, align 8
  br label %36

36:                                               ; preds = %34, %31, %8
  %37 = load ptr, ptr %2, align 8
  ret ptr %37
}

declare ptr @fgets(ptr noundef, i32 noundef, ptr noundef) #6

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @qc_fwrite(ptr noundef %0, ptr noundef %1) #5 {
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  store ptr %0, ptr %3, align 8
  store ptr %1, ptr %4, align 8
  %5 = load ptr, ptr %3, align 8
  %6 = icmp ne ptr %5, null
  br i1 %6, label %7, label %16

7:                                                ; preds = %2
  %8 = load ptr, ptr %4, align 8
  %9 = icmp ne ptr %8, null
  br i1 %9, label %10, label %16

10:                                               ; preds = %7
  %11 = load ptr, ptr %4, align 8
  %12 = load ptr, ptr %3, align 8
  %13 = call i32 @fputs(ptr noundef %11, ptr noundef %12)
  %14 = load ptr, ptr %3, align 8
  %15 = call i32 @fputc(i32 noundef 10, ptr noundef %14)
  br label %16

16:                                               ; preds = %10, %7, %2
  ret void
}

declare i32 @fputc(i32 noundef, ptr noundef) #6

define void @Product_Product(ptr %0, ptr %1, i32 %2) {
entry:
  %price_cents = alloca i32, align 4
  %name_str = alloca ptr, align 8
  store ptr %1, ptr %name_str, align 8
  store i32 %2, ptr %price_cents, align 4
  %name_str1 = load ptr, ptr %name_str, align 8
  %3 = getelementptr inbounds %Product, ptr %0, i32 0, i32 0
  store ptr %name_str1, ptr %3, align 8
  %price_cents2 = load i32, ptr %price_cents, align 4
  %4 = getelementptr inbounds %Product, ptr %0, i32 0, i32 1
  store i32 %price_cents2, ptr %4, align 4
  ret void
}

define ptr @Product_repr(ptr %0) {
entry:
  %1 = getelementptr inbounds %Product, ptr %0, i32 0, i32 0
  %name_str = load ptr, ptr %1, align 8
  %str_concat = call ptr @qc_string_concat(ptr @.str.405, ptr %name_str)
  %str_concat1 = call ptr @qc_string_concat(ptr %str_concat, ptr @.str.406)
  %2 = getelementptr inbounds %Product, ptr %0, i32 0, i32 1
  %price_cents = load i32, ptr %2, align 4
  %to_str = call ptr @qc_to_string_int(i32 %price_cents)
  %str_concat2 = call ptr @qc_string_concat(ptr %str_concat1, ptr %to_str)
  %str_concat3 = call ptr @qc_string_concat(ptr %str_concat2, ptr @.str.407)
  ret ptr %str_concat3
}

define i32 @Product_init(ptr %0) {
entry:
  call void @qc_println(ptr @.str.408)
  ret i32 0
}

define i1 @Product_eval(ptr %0) {
entry:
  %1 = getelementptr inbounds %Product, ptr %0, i32 0, i32 1
  %price_cents = load i32, ptr %1, align 4
  %icmpgt = icmp sgt i32 %price_cents, 0
  ret i1 %icmpgt
}

define void @Vector2D_Vector2D(ptr %0, i32 %1, i32 %2) {
entry:
  %y_coord = alloca i32, align 4
  %x_coord = alloca i32, align 4
  store i32 %1, ptr %x_coord, align 4
  store i32 %2, ptr %y_coord, align 4
  %x_coord1 = load i32, ptr %x_coord, align 4
  %3 = getelementptr inbounds %Vector2D, ptr %0, i32 0, i32 0
  store i32 %x_coord1, ptr %3, align 4
  %y_coord2 = load i32, ptr %y_coord, align 4
  %4 = getelementptr inbounds %Vector2D, ptr %0, i32 0, i32 1
  store i32 %y_coord2, ptr %4, align 4
  ret void
}

define %Vector2D @"Vector2D_operator+"(ptr %0, %Vector2D %1) {
entry:
  %ret_val = alloca %Vector2D, align 8
  %temp_obj4 = alloca %Vector2D, align 8
  %temp_obj = alloca %Vector2D, align 8
  %other = alloca %Vector2D, align 8
  store %Vector2D %1, ptr %other, align 4
  %2 = getelementptr inbounds %Vector2D, ptr %0, i32 0, i32 0
  %x_coord = load i32, ptr %2, align 4
  %other1 = load %Vector2D, ptr %other, align 4
  store %Vector2D %other1, ptr %temp_obj, align 4
  %3 = getelementptr inbounds %Vector2D, ptr %temp_obj, i32 0, i32 0
  %x_coord2 = load i32, ptr %3, align 4
  %add = add i32 %x_coord, %x_coord2
  %4 = getelementptr inbounds %Vector2D, ptr %0, i32 0, i32 1
  %y_coord = load i32, ptr %4, align 4
  %other3 = load %Vector2D, ptr %other, align 4
  store %Vector2D %other3, ptr %temp_obj4, align 4
  %5 = getelementptr inbounds %Vector2D, ptr %temp_obj4, i32 0, i32 1
  %y_coord5 = load i32, ptr %5, align 4
  %add6 = add i32 %y_coord, %y_coord5
  call void @Vector2D_Vector2D(ptr %ret_val, i32 %add, i32 %add6)
  %6 = getelementptr inbounds %Vector2D, ptr %ret_val, i32 0, i32 0
  %7 = load i32, ptr %6, align 4
  %8 = insertvalue %Vector2D undef, i32 %7, 0
  %9 = getelementptr inbounds %Vector2D, ptr %ret_val, i32 0, i32 1
  %10 = load i32, ptr %9, align 4
  %11 = insertvalue %Vector2D %8, i32 %10, 1
  ret %Vector2D %11
}

define i1 @"Vector2D_operator=="(ptr %0, %Vector2D %1) {
entry:
  %temp_obj4 = alloca %Vector2D, align 8
  %temp_obj = alloca %Vector2D, align 8
  %other = alloca %Vector2D, align 8
  store %Vector2D %1, ptr %other, align 4
  %2 = getelementptr inbounds %Vector2D, ptr %0, i32 0, i32 0
  %x_coord = load i32, ptr %2, align 4
  %other1 = load %Vector2D, ptr %other, align 4
  store %Vector2D %other1, ptr %temp_obj, align 4
  %3 = getelementptr inbounds %Vector2D, ptr %temp_obj, i32 0, i32 0
  %x_coord2 = load i32, ptr %3, align 4
  %icmpeq = icmp eq i32 %x_coord, %x_coord2
  %4 = getelementptr inbounds %Vector2D, ptr %0, i32 0, i32 1
  %y_coord = load i32, ptr %4, align 4
  %other3 = load %Vector2D, ptr %other, align 4
  store %Vector2D %other3, ptr %temp_obj4, align 4
  %5 = getelementptr inbounds %Vector2D, ptr %temp_obj4, i32 0, i32 1
  %y_coord5 = load i32, ptr %5, align 4
  %icmpeq6 = icmp eq i32 %y_coord, %y_coord5
  %and = and i1 %icmpeq, %icmpeq6
  ret i1 %and
}

define void @DoubleCounter_DoubleCounter(ptr %0, i32 %1) {
entry:
  %count_val = alloca i32, align 4
  store i32 %1, ptr %count_val, align 4
  %count_val1 = load i32, ptr %count_val, align 4
  %2 = getelementptr inbounds %DoubleCounter, ptr %0, i32 0, i32 0
  store i32 %count_val1, ptr %2, align 4
  ret void
}

define i32 @DoubleCounter_doubleIt(ptr %0) {
entry:
  %1 = getelementptr inbounds %DoubleCounter, ptr %0, i32 0, i32 0
  %count_val = load i32, ptr %1, align 4
  %mul = mul i32 %count_val, 2
  %2 = getelementptr inbounds %DoubleCounter, ptr %0, i32 0, i32 0
  store i32 %mul, ptr %2, align 4
  ret i32 0
}

define void @ColoredBox_ColoredBox(ptr %0, i32 %1, i32 %2, ptr %3, i1 %4) {
entry:
  %has_border = alloca i1, align 1
  %color_str = alloca ptr, align 8
  %height_val = alloca i32, align 4
  %width_val = alloca i32, align 4
  store i32 %1, ptr %width_val, align 4
  store i32 %2, ptr %height_val, align 4
  store ptr %3, ptr %color_str, align 8
  store i1 %4, ptr %has_border, align 1
  %width_val1 = load i32, ptr %width_val, align 4
  %height_val2 = load i32, ptr %height_val, align 4
  %color_str3 = load ptr, ptr %color_str, align 8
  call void @Rectangle2D_Rectangle2D(ptr %0, i32 %width_val1, i32 %height_val2, ptr %color_str3)
  %has_border4 = load i1, ptr %has_border, align 1
  %5 = getelementptr inbounds %ColoredBox, ptr %0, i32 0, i32 3
  store i1 %has_border4, ptr %5, align 1
  ret void
}

define i32 @ColoredBox_describe(ptr %0) {
entry:
  %1 = getelementptr inbounds %ColoredBox, ptr %0, i32 0, i32 0
  %width_val = load i32, ptr %1, align 4
  %to_str = call ptr @qc_to_string_int(i32 %width_val)
  %str_concat = call ptr @qc_string_concat(ptr @.str.409, ptr %to_str)
  %str_concat1 = call ptr @qc_string_concat(ptr %str_concat, ptr @.str.410)
  %2 = getelementptr inbounds %ColoredBox, ptr %0, i32 0, i32 1
  %height_val = load i32, ptr %2, align 4
  %to_str2 = call ptr @qc_to_string_int(i32 %height_val)
  %str_concat3 = call ptr @qc_string_concat(ptr %str_concat1, ptr %to_str2)
  call void @qc_println(ptr %str_concat3)
  %3 = getelementptr inbounds %ColoredBox, ptr %0, i32 0, i32 2
  %color_str = load ptr, ptr %3, align 8
  %str_concat4 = call ptr @qc_string_concat(ptr @.str.411, ptr %color_str)
  call void @qc_println(ptr %str_concat4)
  %area_result = call i32 @Rectangle2D_area(ptr %0)
  %to_str5 = call ptr @qc_to_string_int(i32 %area_result)
  %str_concat6 = call ptr @qc_string_concat(ptr @.str.412, ptr %to_str5)
  call void @qc_println(ptr %str_concat6)
  %4 = getelementptr inbounds %ColoredBox, ptr %0, i32 0, i32 3
  %has_border = load i1, ptr %4, align 1
  br i1 %has_border, label %then, label %ifcont

then:                                             ; preds = %entry
  call void @qc_println(ptr @.str.413)
  br label %ifcont

ifcont:                                           ; preds = %then, %entry
  ret i32 0
}

define void @Rectangle2D_Rectangle2D(ptr %0, i32 %1, i32 %2, ptr %3) {
entry:
  %color_str = alloca ptr, align 8
  %height_val = alloca i32, align 4
  %width_val = alloca i32, align 4
  store i32 %1, ptr %width_val, align 4
  store i32 %2, ptr %height_val, align 4
  store ptr %3, ptr %color_str, align 8
  %width_val1 = load i32, ptr %width_val, align 4
  %4 = getelementptr inbounds %Rectangle2D, ptr %0, i32 0, i32 0
  store i32 %width_val1, ptr %4, align 4
  %height_val2 = load i32, ptr %height_val, align 4
  %5 = getelementptr inbounds %Rectangle2D, ptr %0, i32 0, i32 1
  store i32 %height_val2, ptr %5, align 4
  %color_str3 = load ptr, ptr %color_str, align 8
  %6 = getelementptr inbounds %Rectangle2D, ptr %0, i32 0, i32 2
  store ptr %color_str3, ptr %6, align 8
  ret void
}

define i32 @Rectangle2D_area(ptr %0) {
entry:
  %1 = getelementptr inbounds %Rectangle2D, ptr %0, i32 0, i32 0
  %width_val = load i32, ptr %1, align 4
  %2 = getelementptr inbounds %Rectangle2D, ptr %0, i32 0, i32 1
  %height_val = load i32, ptr %2, align 4
  %mul = mul i32 %width_val, %height_val
  ret i32 %mul
}

define void @Employee_Employee(ptr %0, ptr %1, i32 %2) {
entry:
  %emp_id = alloca i32, align 4
  %emp_name = alloca ptr, align 8
  store ptr %1, ptr %emp_name, align 8
  store i32 %2, ptr %emp_id, align 4
  %emp_name1 = load ptr, ptr %emp_name, align 8
  %3 = getelementptr inbounds %Employee, ptr %0, i32 0, i32 0
  store ptr %emp_name1, ptr %3, align 8
  %emp_id2 = load i32, ptr %emp_id, align 4
  %4 = getelementptr inbounds %Employee, ptr %0, i32 0, i32 1
  store i32 %emp_id2, ptr %4, align 4
  ret void
}

define i32 @Employee_work(ptr %0) {
entry:
  %1 = getelementptr inbounds %Employee, ptr %0, i32 0, i32 0
  %emp_name = load ptr, ptr %1, align 8
  %str_concat = call ptr @qc_string_concat(ptr %emp_name, ptr @.str.414)
  call void @qc_println(ptr %str_concat)
  ret i32 0
}

define void @SavingsAccount_SavingsAccount(ptr %0, ptr %1, i32 %2, float %3) {
entry:
  %interest_rate = alloca float, align 4
  %balance_dollars = alloca i32, align 4
  %account_holder = alloca ptr, align 8
  store ptr %1, ptr %account_holder, align 8
  store i32 %2, ptr %balance_dollars, align 4
  store float %3, ptr %interest_rate, align 4
  %interest_rate1 = load float, ptr %interest_rate, align 4
  %4 = getelementptr inbounds %SavingsAccount, ptr %0, i32 0, i32 2
  store float %interest_rate1, ptr %4, align 4
  %account_holder2 = load ptr, ptr %account_holder, align 8
  %5 = getelementptr inbounds %SavingsAccount, ptr %0, i32 0, i32 0
  store ptr %account_holder2, ptr %5, align 8
  %balance_dollars3 = load i32, ptr %balance_dollars, align 4
  %6 = getelementptr inbounds %SavingsAccount, ptr %0, i32 0, i32 1
  store i32 %balance_dollars3, ptr %6, align 4
  ret void
}

define i32 @SavingsAccount_addInterest(ptr %0) {
entry:
  %interest_amount = alloca i32, align 4
  %1 = getelementptr inbounds %SavingsAccount, ptr %0, i32 0, i32 1
  %balance_dollars = load i32, ptr %1, align 4
  %2 = getelementptr inbounds %SavingsAccount, ptr %0, i32 0, i32 2
  %interest_rate = load float, ptr %2, align 4
  %int_to_float = sitofp i32 %balance_dollars to float
  %fmul = fmul float %int_to_float, %interest_rate
  %to_int = call i32 @qc_to_int_from_float(float %fmul)
  store i32 %to_int, ptr %interest_amount, align 4
  %3 = getelementptr inbounds %SavingsAccount, ptr %0, i32 0, i32 1
  %balance_dollars1 = load i32, ptr %3, align 4
  %interest_amount2 = load i32, ptr %interest_amount, align 4
  %add = add i32 %balance_dollars1, %interest_amount2
  %4 = getelementptr inbounds %SavingsAccount, ptr %0, i32 0, i32 1
  store i32 %add, ptr %4, align 4
  %interest_amount3 = load i32, ptr %interest_amount, align 4
  %to_str = call ptr @qc_to_string_int(i32 %interest_amount3)
  %str_concat = call ptr @qc_string_concat(ptr @.str.415, ptr %to_str)
  call void @qc_println(ptr %str_concat)
  ret i32 0
}

define void @Warrior_Warrior(ptr %0, ptr %1, i32 %2, i32 %3) {
entry:
  %armor_value = alloca i32, align 4
  %health_points = alloca i32, align 4
  %char_name = alloca ptr, align 8
  store ptr %1, ptr %char_name, align 8
  store i32 %2, ptr %health_points, align 4
  store i32 %3, ptr %armor_value, align 4
  %armor_value1 = load i32, ptr %armor_value, align 4
  %4 = getelementptr inbounds %Warrior, ptr %0, i32 0, i32 2
  store i32 %armor_value1, ptr %4, align 4
  %char_name2 = load ptr, ptr %char_name, align 8
  %5 = getelementptr inbounds %Warrior, ptr %0, i32 0, i32 1
  store ptr %char_name2, ptr %5, align 8
  %health_points3 = load i32, ptr %health_points, align 4
  %6 = getelementptr inbounds %Warrior, ptr %0, i32 0, i32 0
  store i32 %health_points3, ptr %6, align 4
  ret void
}

define i32 @Warrior_showHealth(ptr %0) {
entry:
  %1 = getelementptr inbounds %Warrior, ptr %0, i32 0, i32 1
  %char_name = load ptr, ptr %1, align 8
  %str_concat = call ptr @qc_string_concat(ptr %char_name, ptr @.str.416)
  %2 = getelementptr inbounds %Warrior, ptr %0, i32 0, i32 0
  %health_points = load i32, ptr %2, align 4
  %to_str = call ptr @qc_to_string_int(i32 %health_points)
  %str_concat1 = call ptr @qc_string_concat(ptr %str_concat, ptr %to_str)
  call void @qc_println(ptr %str_concat1)
  ret i32 0
}

define i32 @Warrior_defend(ptr %0) {
entry:
  %reduced_damage = alloca i32, align 4
  %1 = getelementptr inbounds %Warrior, ptr %0, i32 0, i32 2
  %armor_value = load i32, ptr %1, align 4
  %sub = sub i32 10, %armor_value
  store i32 %sub, ptr %reduced_damage, align 4
  %reduced_damage1 = load i32, ptr %reduced_damage, align 4
  %icmplt = icmp slt i32 %reduced_damage1, 0
  br i1 %icmplt, label %then, label %ifcont

then:                                             ; preds = %entry
  %reduced_damage2 = load i32, ptr %reduced_damage, align 4
  store i32 0, ptr %reduced_damage, align 4
  br label %ifcont

ifcont:                                           ; preds = %then, %entry
  %reduced_damage3 = load i32, ptr %reduced_damage, align 4
  %takeDamage_result = call i32 @GameCharacter_takeDamage(ptr %0, i32 %reduced_damage3)
  ret i32 0
}

define void @SecureBox_SecureBox(ptr %0, ptr %1) {
entry:
  %secret_code = alloca ptr, align 8
  store ptr %1, ptr %secret_code, align 8
  %secret_code1 = load ptr, ptr %secret_code, align 8
  %2 = getelementptr inbounds %SecureBox, ptr %0, i32 0, i32 0
  store ptr %secret_code1, ptr %2, align 8
  %3 = getelementptr inbounds %SecureBox, ptr %0, i32 0, i32 1
  store i1 true, ptr %3, align 1
  ret void
}

define i32 @SecureBox_unlock(ptr %0, ptr %1) {
entry:
  %code_attempt = alloca ptr, align 8
  store ptr %1, ptr %code_attempt, align 8
  %code_attempt1 = load ptr, ptr %code_attempt, align 8
  %2 = getelementptr inbounds %SecureBox, ptr %0, i32 0, i32 0
  %secret_code = load ptr, ptr %2, align 8
  %3 = call i1 @qc_string_eq(ptr %code_attempt1, ptr %secret_code)
  br i1 %3, label %then, label %else

then:                                             ; preds = %entry
  %4 = getelementptr inbounds %SecureBox, ptr %0, i32 0, i32 1
  store i1 false, ptr %4, align 1
  call void @qc_println(ptr @.str.417)
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  ret i32 0

else:                                             ; preds = %entry
  call void @qc_println(ptr @.str.418)
  br label %ifcont
}

define void @BankAccount_BankAccount(ptr %0, ptr %1, i32 %2) {
entry:
  %balance_dollars = alloca i32, align 4
  %account_holder = alloca ptr, align 8
  store ptr %1, ptr %account_holder, align 8
  store i32 %2, ptr %balance_dollars, align 4
  %account_holder1 = load ptr, ptr %account_holder, align 8
  %3 = getelementptr inbounds %BankAccount, ptr %0, i32 0, i32 0
  store ptr %account_holder1, ptr %3, align 8
  %balance_dollars2 = load i32, ptr %balance_dollars, align 4
  %4 = getelementptr inbounds %BankAccount, ptr %0, i32 0, i32 1
  store i32 %balance_dollars2, ptr %4, align 4
  ret void
}

define i32 @BankAccount_deposit(ptr %0, i32 %1) {
entry:
  %amount = alloca i32, align 4
  store i32 %1, ptr %amount, align 4
  %2 = getelementptr inbounds %BankAccount, ptr %0, i32 0, i32 1
  %balance_dollars = load i32, ptr %2, align 4
  %amount1 = load i32, ptr %amount, align 4
  %add = add i32 %balance_dollars, %amount1
  %3 = getelementptr inbounds %BankAccount, ptr %0, i32 0, i32 1
  store i32 %add, ptr %3, align 4
  %amount2 = load i32, ptr %amount, align 4
  %to_str = call ptr @qc_to_string_int(i32 %amount2)
  %str_concat = call ptr @qc_string_concat(ptr @.str.419, ptr %to_str)
  call void @qc_println(ptr %str_concat)
  ret i32 0
}

define void @Cat_Cat(ptr %0, ptr %1, i32 %2) {
entry:
  %lives = alloca i32, align 4
  %name = alloca ptr, align 8
  store ptr %1, ptr %name, align 8
  store i32 %2, ptr %lives, align 4
  %lives1 = load i32, ptr %lives, align 4
  %3 = getelementptr inbounds %Cat, ptr %0, i32 0, i32 1
  store i32 %lives1, ptr %3, align 4
  %name2 = load ptr, ptr %name, align 8
  %4 = getelementptr inbounds %Cat, ptr %0, i32 0, i32 0
  store ptr %name2, ptr %4, align 8
  ret void
}

define i32 @Cat_meow(ptr %0) {
entry:
  %1 = getelementptr inbounds %Cat, ptr %0, i32 0, i32 0
  %name = load ptr, ptr %1, align 8
  %str_concat = call ptr @qc_string_concat(ptr %name, ptr @.str.420)
  call void @qc_println(ptr %str_concat)
  ret i32 0
}

define i32 @Cat_useLives(ptr %0, i32 %1) {
entry:
  %count = alloca i32, align 4
  store i32 %1, ptr %count, align 4
  %2 = getelementptr inbounds %Cat, ptr %0, i32 0, i32 1
  %lives = load i32, ptr %2, align 4
  %count1 = load i32, ptr %count, align 4
  %sub = sub i32 %lives, %count1
  %3 = getelementptr inbounds %Cat, ptr %0, i32 0, i32 1
  store i32 %sub, ptr %3, align 4
  %4 = getelementptr inbounds %Cat, ptr %0, i32 0, i32 0
  %name = load ptr, ptr %4, align 8
  %str_concat = call ptr @qc_string_concat(ptr %name, ptr @.str.421)
  %5 = getelementptr inbounds %Cat, ptr %0, i32 0, i32 1
  %lives2 = load i32, ptr %5, align 4
  %to_str = call ptr @qc_to_string_int(i32 %lives2)
  %str_concat3 = call ptr @qc_string_concat(ptr %str_concat, ptr %to_str)
  %str_concat4 = call ptr @qc_string_concat(ptr %str_concat3, ptr @.str.422)
  call void @qc_println(ptr %str_concat4)
  ret i32 0
}

define void @Director_Director(ptr %0, ptr %1, i32 %2, i32 %3, ptr %4) {
entry:
  %department_name = alloca ptr, align 8
  %team_size = alloca i32, align 4
  %emp_id = alloca i32, align 4
  %emp_name = alloca ptr, align 8
  store ptr %1, ptr %emp_name, align 8
  store i32 %2, ptr %emp_id, align 4
  store i32 %3, ptr %team_size, align 4
  store ptr %4, ptr %department_name, align 8
  %department_name1 = load ptr, ptr %department_name, align 8
  %5 = getelementptr inbounds %Director, ptr %0, i32 0, i32 3
  store ptr %department_name1, ptr %5, align 8
  %team_size2 = load i32, ptr %team_size, align 4
  %6 = getelementptr inbounds %Director, ptr %0, i32 0, i32 2
  store i32 %team_size2, ptr %6, align 4
  %emp_name3 = load ptr, ptr %emp_name, align 8
  %7 = getelementptr inbounds %Director, ptr %0, i32 0, i32 0
  store ptr %emp_name3, ptr %7, align 8
  %emp_id4 = load i32, ptr %emp_id, align 4
  %8 = getelementptr inbounds %Director, ptr %0, i32 0, i32 1
  store i32 %emp_id4, ptr %8, align 4
  ret void
}

define i32 @Director_direct(ptr %0) {
entry:
  %1 = getelementptr inbounds %Director, ptr %0, i32 0, i32 0
  %emp_name = load ptr, ptr %1, align 8
  %str_concat = call ptr @qc_string_concat(ptr %emp_name, ptr @.str.423)
  %2 = getelementptr inbounds %Director, ptr %0, i32 0, i32 3
  %department_name = load ptr, ptr %2, align 8
  %str_concat1 = call ptr @qc_string_concat(ptr %str_concat, ptr %department_name)
  %str_concat2 = call ptr @qc_string_concat(ptr %str_concat1, ptr @.str.424)
  call void @qc_println(ptr %str_concat2)
  ret i32 0
}

define void @PlantLife_PlantLife(ptr %0, ptr %1) {
entry:
  %plant_type = alloca ptr, align 8
  store ptr %1, ptr %plant_type, align 8
  %plant_type1 = load ptr, ptr %plant_type, align 8
  %2 = getelementptr inbounds %PlantLife, ptr %0, i32 0, i32 1
  store ptr %plant_type1, ptr %2, align 8
  %3 = getelementptr inbounds %PlantLife, ptr %0, i32 0, i32 0
  store i1 true, ptr %3, align 1
  ret void
}

define i32 @PlantLife_photosynthesize(ptr %0) {
entry:
  %1 = getelementptr inbounds %PlantLife, ptr %0, i32 0, i32 1
  %plant_type = load ptr, ptr %1, align 8
  %str_concat = call ptr @qc_string_concat(ptr %plant_type, ptr @.str.425)
  call void @qc_println(ptr %str_concat)
  ret i32 0
}

define void @MathOps_MathOps(ptr %0) {
entry:
  ret void
}

define i32 @MathOps_add(ptr %0, i32 %1, i32 %2) {
entry:
  %b_val = alloca i32, align 4
  %a_val = alloca i32, align 4
  store i32 %1, ptr %a_val, align 4
  store i32 %2, ptr %b_val, align 4
  %a_val1 = load i32, ptr %a_val, align 4
  %b_val2 = load i32, ptr %b_val, align 4
  %add = add i32 %a_val1, %b_val2
  ret i32 %add
}

define float @MathOps_add.1(ptr %0, float %1, float %2) {
entry:
  %b_val = alloca float, align 4
  %a_val = alloca float, align 4
  store float %1, ptr %a_val, align 4
  store float %2, ptr %b_val, align 4
  %a_val1 = load float, ptr %a_val, align 4
  %b_val2 = load float, ptr %b_val, align 4
  %fadd = fadd float %a_val1, %b_val2
  ret float %fadd
}

define ptr @MathOps_add.2(ptr %0, ptr %1, ptr %2) {
entry:
  %b_val = alloca ptr, align 8
  %a_val = alloca ptr, align 8
  store ptr %1, ptr %a_val, align 8
  store ptr %2, ptr %b_val, align 8
  %a_val1 = load ptr, ptr %a_val, align 8
  %b_val2 = load ptr, ptr %b_val, align 8
  %str_concat = call ptr @qc_string_concat(ptr %a_val1, ptr %b_val2)
  ret ptr %str_concat
}

define void @GameCharacter_GameCharacter(ptr %0, ptr %1, i32 %2) {
entry:
  %health_points = alloca i32, align 4
  %char_name = alloca ptr, align 8
  store ptr %1, ptr %char_name, align 8
  store i32 %2, ptr %health_points, align 4
  %char_name1 = load ptr, ptr %char_name, align 8
  %3 = getelementptr inbounds %GameCharacter, ptr %0, i32 0, i32 1
  store ptr %char_name1, ptr %3, align 8
  %health_points2 = load i32, ptr %health_points, align 4
  %4 = getelementptr inbounds %GameCharacter, ptr %0, i32 0, i32 0
  store i32 %health_points2, ptr %4, align 4
  ret void
}

define i32 @GameCharacter_takeDamage(ptr %0, i32 %1) {
entry:
  %damage_amount = alloca i32, align 4
  store i32 %1, ptr %damage_amount, align 4
  %2 = getelementptr inbounds %GameCharacter, ptr %0, i32 0, i32 0
  %health_points = load i32, ptr %2, align 4
  %damage_amount1 = load i32, ptr %damage_amount, align 4
  %sub = sub i32 %health_points, %damage_amount1
  %3 = getelementptr inbounds %GameCharacter, ptr %0, i32 0, i32 0
  store i32 %sub, ptr %3, align 4
  %4 = getelementptr inbounds %GameCharacter, ptr %0, i32 0, i32 1
  %char_name = load ptr, ptr %4, align 8
  %str_concat = call ptr @qc_string_concat(ptr %char_name, ptr @.str.426)
  %damage_amount2 = load i32, ptr %damage_amount, align 4
  %to_str = call ptr @qc_to_string_int(i32 %damage_amount2)
  %str_concat3 = call ptr @qc_string_concat(ptr %str_concat, ptr %to_str)
  %str_concat4 = call ptr @qc_string_concat(ptr %str_concat3, ptr @.str.427)
  call void @qc_println(ptr %str_concat4)
  ret i32 0
}

define void @Counter2_Counter2(ptr %0, i32 %1) {
entry:
  %count_val = alloca i32, align 4
  store i32 %1, ptr %count_val, align 4
  %count_val1 = load i32, ptr %count_val, align 4
  %2 = getelementptr inbounds %Counter2, ptr %0, i32 0, i32 0
  store i32 %count_val1, ptr %2, align 4
  ret void
}

define i32 @Counter2_show(ptr %0) {
entry:
  %1 = getelementptr inbounds %Counter2, ptr %0, i32 0, i32 0
  %count_val = load i32, ptr %1, align 4
  %to_str = call ptr @qc_to_string_int(i32 %count_val)
  %str_concat = call ptr @qc_string_concat(ptr @.str.428, ptr %to_str)
  call void @qc_println(ptr %str_concat)
  ret i32 0
}

define void @Vehicle_Vehicle(ptr %0, ptr %1, i32 %2) {
entry:
  %speed_mph = alloca i32, align 4
  %type_name = alloca ptr, align 8
  store ptr %1, ptr %type_name, align 8
  store i32 %2, ptr %speed_mph, align 4
  %type_name1 = load ptr, ptr %type_name, align 8
  %3 = getelementptr inbounds %Vehicle, ptr %0, i32 0, i32 0
  store ptr %type_name1, ptr %3, align 8
  %speed_mph2 = load i32, ptr %speed_mph, align 4
  %4 = getelementptr inbounds %Vehicle, ptr %0, i32 0, i32 1
  store i32 %speed_mph2, ptr %4, align 4
  ret void
}

define i32 @Vehicle_describe(ptr %0) {
entry:
  %1 = getelementptr inbounds %Vehicle, ptr %0, i32 0, i32 0
  %type_name = load ptr, ptr %1, align 8
  %str_concat = call ptr @qc_string_concat(ptr @.str.429, ptr %type_name)
  call void @qc_println(ptr %str_concat)
  ret i32 0
}

define i32 @Vehicle_getSpeed(ptr %0) {
entry:
  %1 = getelementptr inbounds %Vehicle, ptr %0, i32 0, i32 1
  %speed_mph = load i32, ptr %1, align 4
  %to_str = call ptr @qc_to_string_int(i32 %speed_mph)
  %str_concat = call ptr @qc_string_concat(ptr @.str.430, ptr %to_str)
  %str_concat1 = call ptr @qc_string_concat(ptr %str_concat, ptr @.str.431)
  call void @qc_println(ptr %str_concat1)
  ret i32 0
}

define void @FlowerPlant_FlowerPlant(ptr %0, ptr %1, ptr %2) {
entry:
  %color_name = alloca ptr, align 8
  %plant_type = alloca ptr, align 8
  store ptr %1, ptr %plant_type, align 8
  store ptr %2, ptr %color_name, align 8
  %color_name1 = load ptr, ptr %color_name, align 8
  %3 = getelementptr inbounds %FlowerPlant, ptr %0, i32 0, i32 2
  store ptr %color_name1, ptr %3, align 8
  %plant_type2 = load ptr, ptr %plant_type, align 8
  %4 = getelementptr inbounds %FlowerPlant, ptr %0, i32 0, i32 1
  store ptr %plant_type2, ptr %4, align 8
  %5 = getelementptr inbounds %FlowerPlant, ptr %0, i32 0, i32 0
  store i1 true, ptr %5, align 1
  ret void
}

define i32 @FlowerPlant_bloom(ptr %0) {
entry:
  %1 = getelementptr inbounds %FlowerPlant, ptr %0, i32 0, i32 2
  %color_name = load ptr, ptr %1, align 8
  %str_concat = call ptr @qc_string_concat(ptr %color_name, ptr @.str.432)
  %2 = getelementptr inbounds %FlowerPlant, ptr %0, i32 0, i32 1
  %plant_type = load ptr, ptr %2, align 8
  %str_concat1 = call ptr @qc_string_concat(ptr %str_concat, ptr %plant_type)
  %str_concat2 = call ptr @qc_string_concat(ptr %str_concat1, ptr @.str.433)
  call void @qc_println(ptr %str_concat2)
  ret i32 0
}

define void @CarInherit_CarInherit(ptr %0, i32 %1, i32 %2) {
entry:
  %num_doors = alloca i32, align 4
  %speed_mph = alloca i32, align 4
  store i32 %1, ptr %speed_mph, align 4
  store i32 %2, ptr %num_doors, align 4
  %num_doors1 = load i32, ptr %num_doors, align 4
  %3 = getelementptr inbounds %CarInherit, ptr %0, i32 0, i32 2
  store i32 %num_doors1, ptr %3, align 4
  %4 = getelementptr inbounds %CarInherit, ptr %0, i32 0, i32 0
  store ptr @.str.434, ptr %4, align 8
  %speed_mph2 = load i32, ptr %speed_mph, align 4
  %5 = getelementptr inbounds %CarInherit, ptr %0, i32 0, i32 1
  store i32 %speed_mph2, ptr %5, align 4
  ret void
}

define i32 @CarInherit_describe(ptr %0) {
entry:
  %1 = getelementptr inbounds %CarInherit, ptr %0, i32 0, i32 2
  %num_doors = load i32, ptr %1, align 4
  %to_str = call ptr @qc_to_string_int(i32 %num_doors)
  %str_concat = call ptr @qc_string_concat(ptr @.str.435, ptr %to_str)
  %str_concat1 = call ptr @qc_string_concat(ptr %str_concat, ptr @.str.436)
  call void @qc_println(ptr %str_concat1)
  ret i32 0
}

define void @Dog_Dog(ptr %0, ptr %1, i32 %2) {
entry:
  %age = alloca i32, align 4
  %name = alloca ptr, align 8
  store ptr %1, ptr %name, align 8
  store i32 %2, ptr %age, align 4
  %name1 = load ptr, ptr %name, align 8
  %3 = getelementptr inbounds %Dog, ptr %0, i32 0, i32 0
  store ptr %name1, ptr %3, align 8
  %age2 = load i32, ptr %age, align 4
  %4 = getelementptr inbounds %Dog, ptr %0, i32 0, i32 1
  store i32 %age2, ptr %4, align 4
  ret void
}

define void @BaseClass_BaseClass(ptr %0, i32 %1) {
entry:
  %value_num = alloca i32, align 4
  store i32 %1, ptr %value_num, align 4
  %value_num1 = load i32, ptr %value_num, align 4
  %2 = getelementptr inbounds %BaseClass, ptr %0, i32 0, i32 0
  store i32 %value_num1, ptr %2, align 4
  ret void
}

define i32 @BaseClass_showBase(ptr %0) {
entry:
  %1 = getelementptr inbounds %BaseClass, ptr %0, i32 0, i32 0
  %value_num = load i32, ptr %1, align 4
  %to_str = call ptr @qc_to_string_int(i32 %value_num)
  %str_concat = call ptr @qc_string_concat(ptr @.str.437, ptr %to_str)
  call void @qc_println(ptr %str_concat)
  ret i32 0
}

define void @Calculator_Calculator(ptr %0, i32 %1) {
entry:
  %value = alloca i32, align 4
  store i32 %1, ptr %value, align 4
  %value1 = load i32, ptr %value, align 4
  %2 = getelementptr inbounds %Calculator, ptr %0, i32 0, i32 0
  store i32 %value1, ptr %2, align 4
  ret void
}

define i32 @Calculator_add(ptr %0, i32 %1) {
entry:
  %x = alloca i32, align 4
  store i32 %1, ptr %x, align 4
  %2 = getelementptr inbounds %Calculator, ptr %0, i32 0, i32 0
  %value = load i32, ptr %2, align 4
  %x1 = load i32, ptr %x, align 4
  %add = add i32 %value, %x1
  %3 = getelementptr inbounds %Calculator, ptr %0, i32 0, i32 0
  store i32 %add, ptr %3, align 4
  %4 = getelementptr inbounds %Calculator, ptr %0, i32 0, i32 0
  %value2 = load i32, ptr %4, align 4
  ret i32 %value2
}

define i32 @Calculator_getValue(ptr %0) {
entry:
  %1 = getelementptr inbounds %Calculator, ptr %0, i32 0, i32 0
  %value = load i32, ptr %1, align 4
  ret i32 %value
}

define void @Manager_Manager(ptr %0, ptr %1, i32 %2, i32 %3) {
entry:
  %team_size = alloca i32, align 4
  %emp_id = alloca i32, align 4
  %emp_name = alloca ptr, align 8
  store ptr %1, ptr %emp_name, align 8
  store i32 %2, ptr %emp_id, align 4
  store i32 %3, ptr %team_size, align 4
  %team_size1 = load i32, ptr %team_size, align 4
  %4 = getelementptr inbounds %Manager, ptr %0, i32 0, i32 2
  store i32 %team_size1, ptr %4, align 4
  %emp_name2 = load ptr, ptr %emp_name, align 8
  %5 = getelementptr inbounds %Manager, ptr %0, i32 0, i32 0
  store ptr %emp_name2, ptr %5, align 8
  %emp_id3 = load i32, ptr %emp_id, align 4
  %6 = getelementptr inbounds %Manager, ptr %0, i32 0, i32 1
  store i32 %emp_id3, ptr %6, align 4
  ret void
}

define i32 @Manager_manage(ptr %0) {
entry:
  %1 = getelementptr inbounds %Manager, ptr %0, i32 0, i32 0
  %emp_name = load ptr, ptr %1, align 8
  %str_concat = call ptr @qc_string_concat(ptr %emp_name, ptr @.str.438)
  %2 = getelementptr inbounds %Manager, ptr %0, i32 0, i32 2
  %team_size = load i32, ptr %2, align 4
  %to_str = call ptr @qc_to_string_int(i32 %team_size)
  %str_concat1 = call ptr @qc_string_concat(ptr %str_concat, ptr %to_str)
  %str_concat2 = call ptr @qc_string_concat(ptr %str_concat1, ptr @.str.439)
  call void @qc_println(ptr %str_concat2)
  ret i32 0
}

define void @Counter_Counter(ptr %0, i32 %1) {
entry:
  %count = alloca i32, align 4
  store i32 %1, ptr %count, align 4
  %count1 = load i32, ptr %count, align 4
  %2 = getelementptr inbounds %Counter, ptr %0, i32 0, i32 0
  store i32 %count1, ptr %2, align 4
  ret void
}

define i32 @Counter_increment(ptr %0) {
entry:
  %1 = getelementptr inbounds %Counter, ptr %0, i32 0, i32 0
  %count = load i32, ptr %1, align 4
  %add = add i32 %count, 1
  %2 = getelementptr inbounds %Counter, ptr %0, i32 0, i32 0
  store i32 %add, ptr %2, align 4
  ret i32 0
}

define i32 @Counter_decrement(ptr %0) {
entry:
  %1 = getelementptr inbounds %Counter, ptr %0, i32 0, i32 0
  %count = load i32, ptr %1, align 4
  %sub = sub i32 %count, 1
  %2 = getelementptr inbounds %Counter, ptr %0, i32 0, i32 0
  store i32 %sub, ptr %2, align 4
  ret i32 0
}

define i32 @Counter_reset(ptr %0) {
entry:
  %1 = getelementptr inbounds %Counter, ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  ret i32 0
}

define i32 @Counter_get(ptr %0) {
entry:
  %1 = getelementptr inbounds %Counter, ptr %0, i32 0, i32 0
  %count = load i32, ptr %1, align 4
  ret i32 %count
}

define void @Person_Person(ptr %0, ptr %1, i32 %2) {
entry:
  %age = alloca i32, align 4
  %name = alloca ptr, align 8
  store ptr %1, ptr %name, align 8
  store i32 %2, ptr %age, align 4
  %age1 = load i32, ptr %age, align 4
  %3 = getelementptr inbounds %Person, ptr %0, i32 0, i32 1
  store i32 %age1, ptr %3, align 4
  %name2 = load ptr, ptr %name, align 8
  %4 = getelementptr inbounds %Person, ptr %0, i32 0, i32 0
  store ptr %name2, ptr %4, align 8
  ret void
}

define i32 @Person_birthday(ptr %0) {
entry:
  %1 = getelementptr inbounds %Person, ptr %0, i32 0, i32 1
  %age = load i32, ptr %1, align 4
  %add = add i32 %age, 1
  %2 = getelementptr inbounds %Person, ptr %0, i32 0, i32 1
  store i32 %add, ptr %2, align 4
  %3 = getelementptr inbounds %Person, ptr %0, i32 0, i32 0
  %name = load ptr, ptr %3, align 8
  %str_concat = call ptr @qc_string_concat(ptr %name, ptr @.str.440)
  %4 = getelementptr inbounds %Person, ptr %0, i32 0, i32 1
  %age1 = load i32, ptr %4, align 4
  %to_str = call ptr @qc_to_string_int(i32 %age1)
  %str_concat2 = call ptr @qc_string_concat(ptr %str_concat, ptr %to_str)
  call void @qc_println(ptr %str_concat2)
  ret i32 0
}

define void @Robot_Robot(ptr %0, ptr %1) {
entry:
  %status = alloca ptr, align 8
  store ptr %1, ptr %status, align 8
  %status1 = load ptr, ptr %status, align 8
  %2 = getelementptr inbounds %Robot, ptr %0, i32 0, i32 0
  store ptr %status1, ptr %2, align 8
  ret void
}

define i32 @Robot_start(ptr %0) {
entry:
  %1 = getelementptr inbounds %Robot, ptr %0, i32 0, i32 0
  store ptr @.str.441, ptr %1, align 8
  call void @qc_println(ptr @.str.442)
  ret i32 0
}

define i32 @Robot_stop(ptr %0) {
entry:
  %1 = getelementptr inbounds %Robot, ptr %0, i32 0, i32 0
  store ptr @.str.443, ptr %1, align 8
  call void @qc_println(ptr @.str.444)
  ret i32 0
}

define i32 @Robot_getStatus(ptr %0) {
entry:
  %1 = getelementptr inbounds %Robot, ptr %0, i32 0, i32 0
  %status = load ptr, ptr %1, align 8
  %str_concat = call ptr @qc_string_concat(ptr @.str.445, ptr %status)
  call void @qc_println(ptr %str_concat)
  ret i32 0
}

define void @LivingThing_LivingThing(ptr %0, i1 %1) {
entry:
  %is_alive = alloca i1, align 1
  store i1 %1, ptr %is_alive, align 1
  %is_alive1 = load i1, ptr %is_alive, align 1
  %2 = getelementptr inbounds %LivingThing, ptr %0, i32 0, i32 0
  store i1 %is_alive1, ptr %2, align 1
  ret void
}

define i32 @LivingThing_checkLife(ptr %0) {
entry:
  %1 = getelementptr inbounds %LivingThing, ptr %0, i32 0, i32 0
  %is_alive = load i1, ptr %1, align 1
  br i1 %is_alive, label %then, label %else

then:                                             ; preds = %entry
  call void @qc_println(ptr @.str.446)
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  ret i32 0

else:                                             ; preds = %entry
  call void @qc_println(ptr @.str.447)
  br label %ifcont
}

define void @DerivedClass_DerivedClass(ptr %0, i32 %1, i32 %2) {
entry:
  %derived_val = alloca i32, align 4
  %base_val = alloca i32, align 4
  store i32 %1, ptr %base_val, align 4
  store i32 %2, ptr %derived_val, align 4
  %derived_val1 = load i32, ptr %derived_val, align 4
  %3 = getelementptr inbounds %DerivedClass, ptr %0, i32 0, i32 0
  store i32 %derived_val1, ptr %3, align 4
  %base_val2 = load i32, ptr %base_val, align 4
  %4 = getelementptr inbounds %DerivedClass, ptr %0, i32 0, i32 0
  store i32 %base_val2, ptr %4, align 4
  ret void
}

define i32 @DerivedClass_showDerived(ptr %0) {
entry:
  %1 = getelementptr inbounds %DerivedClass, ptr %0, i32 0, i32 0
  %value_num = load i32, ptr %1, align 4
  %to_str = call ptr @qc_to_string_int(i32 %value_num)
  %str_concat = call ptr @qc_string_concat(ptr @.str.448, ptr %to_str)
  call void @qc_println(ptr %str_concat)
  ret i32 0
}

define void @Animal_Animal(ptr %0, ptr %1, i32 %2) {
entry:
  %age_years = alloca i32, align 4
  %species = alloca ptr, align 8
  store ptr %1, ptr %species, align 8
  store i32 %2, ptr %age_years, align 4
  %species1 = load ptr, ptr %species, align 8
  %3 = getelementptr inbounds %Animal, ptr %0, i32 0, i32 0
  store ptr %species1, ptr %3, align 8
  %age_years2 = load i32, ptr %age_years, align 4
  %4 = getelementptr inbounds %Animal, ptr %0, i32 0, i32 1
  store i32 %age_years2, ptr %4, align 4
  ret void
}

define i32 @Animal_makeSound(ptr %0) {
entry:
  %1 = getelementptr inbounds %Animal, ptr %0, i32 0, i32 0
  %species = load ptr, ptr %1, align 8
  %str_concat = call ptr @qc_string_concat(ptr %species, ptr @.str.449)
  call void @qc_println(ptr %str_concat)
  ret i32 0
}

define i32 @Animal_getAge(ptr %0) {
entry:
  %1 = getelementptr inbounds %Animal, ptr %0, i32 0, i32 0
  %species = load ptr, ptr %1, align 8
  %str_concat = call ptr @qc_string_concat(ptr %species, ptr @.str.450)
  %2 = getelementptr inbounds %Animal, ptr %0, i32 0, i32 1
  %age_years = load i32, ptr %2, align 4
  %to_str = call ptr @qc_to_string_int(i32 %age_years)
  %str_concat1 = call ptr @qc_string_concat(ptr %str_concat, ptr %to_str)
  %str_concat2 = call ptr @qc_string_concat(ptr %str_concat1, ptr @.str.451)
  call void @qc_println(ptr %str_concat2)
  ret i32 0
}

define void @DogInherit_DogInherit(ptr %0, ptr %1, i32 %2) {
entry:
  %age_years = alloca i32, align 4
  %breed_name = alloca ptr, align 8
  store ptr %1, ptr %breed_name, align 8
  store i32 %2, ptr %age_years, align 4
  %breed_name1 = load ptr, ptr %breed_name, align 8
  %3 = getelementptr inbounds %DogInherit, ptr %0, i32 0, i32 2
  store ptr %breed_name1, ptr %3, align 8
  %4 = getelementptr inbounds %DogInherit, ptr %0, i32 0, i32 0
  store ptr @.str.452, ptr %4, align 8
  %age_years2 = load i32, ptr %age_years, align 4
  %5 = getelementptr inbounds %DogInherit, ptr %0, i32 0, i32 1
  store i32 %age_years2, ptr %5, align 4
  ret void
}

define i32 @DogInherit_bark(ptr %0) {
entry:
  %1 = getelementptr inbounds %DogInherit, ptr %0, i32 0, i32 2
  %breed_name = load ptr, ptr %1, align 8
  %str_concat = call ptr @qc_string_concat(ptr %breed_name, ptr @.str.453)
  call void @qc_println(ptr %str_concat)
  ret i32 0
}

define ptr @Rectangle_repr(%Rectangle %0) {
entry:
  %1 = call ptr @qc_string_concat(ptr @0, ptr @1)
  %2 = extractvalue %Rectangle %0, 0
  %3 = call ptr @qc_string_concat(ptr %1, ptr @2)
  %4 = call ptr @qc_string_concat(ptr %3, ptr @3)
  %5 = call ptr @qc_string_concat(ptr %4, ptr @4)
  %6 = extractvalue %Rectangle %0, 1
  %7 = call ptr @qc_string_concat(ptr %5, ptr @5)
  %8 = call ptr @qc_string_concat(ptr %7, ptr @6)
  ret ptr %8
}

define ptr @Point_repr(%Point %0) {
entry:
  %1 = call ptr @qc_string_concat(ptr @7, ptr @8)
  %2 = extractvalue %Point %0, 0
  %3 = call ptr @qc_to_string_int(i32 %2)
  %4 = call ptr @qc_string_concat(ptr %1, ptr %3)
  %5 = call ptr @qc_string_concat(ptr %4, ptr @9)
  %6 = call ptr @qc_string_concat(ptr %5, ptr @10)
  %7 = extractvalue %Point %0, 1
  %8 = call ptr @qc_to_string_int(i32 %7)
  %9 = call ptr @qc_string_concat(ptr %6, ptr %8)
  %10 = call ptr @qc_string_concat(ptr %9, ptr @11)
  ret ptr %10
}

define i32 @add(i32 %a, i32 %b) {
entry:
  %b2 = alloca i32, align 4
  %a1 = alloca i32, align 4
  store i32 %a, ptr %a1, align 4
  store i32 %b, ptr %b2, align 4
  %a3 = load i32, ptr %a1, align 4
  %b4 = load i32, ptr %b2, align 4
  %add = add i32 %a3, %b4
  ret i32 %add
}

define { i32, ptr } @get_user() {
entry:
  ret { i32, ptr } { i32 123, ptr @.str.23 }
}

define i32 @mul_add(i32 %a, i32 %b, i32 %c) {
entry:
  %c3 = alloca i32, align 4
  %b2 = alloca i32, align 4
  %a1 = alloca i32, align 4
  store i32 %a, ptr %a1, align 4
  store i32 %b, ptr %b2, align 4
  store i32 %c, ptr %c3, align 4
  %a4 = load i32, ptr %a1, align 4
  %b5 = load i32, ptr %b2, align 4
  %mul = mul i32 %a4, %b5
  %c6 = load i32, ptr %c3, align 4
  %add = add i32 %mul, %c6
  ret i32 %add
}

define i32 @greet(ptr %name, i32 %times) {
entry:
  %times2 = alloca i32, align 4
  %name1 = alloca ptr, align 8
  store ptr %name, ptr %name1, align 8
  store i32 %times, ptr %times2, align 4
  %name3 = load ptr, ptr %name1, align 8
  call void @qc_print_string(ptr %name3)
  ret i32 0
}

define double @square(double %x) {
entry:
  %x1 = alloca double, align 8
  store double %x, ptr %x1, align 8
  %x2 = load double, ptr %x1, align 8
  %x3 = load double, ptr %x1, align 8
  %fmul = fmul double %x2, %x3
  ret double %fmul
}

define ptr @make_array() {
entry:
  %arr = alloca ptr, align 8
  %heap_arr = call ptr @malloc(i64 12)
  store ptr %heap_arr, ptr %arr, align 8
  %heap_ptr = load ptr, ptr %arr, align 8
  %0 = getelementptr inbounds [3 x i32], ptr %heap_ptr, i32 0, i32 0
  store i32 1, ptr %0, align 4
  %heap_ptr1 = load ptr, ptr %arr, align 8
  %1 = getelementptr inbounds [3 x i32], ptr %heap_ptr1, i32 0, i32 1
  store i32 2, ptr %1, align 4
  %heap_ptr2 = load ptr, ptr %arr, align 8
  %2 = getelementptr inbounds [3 x i32], ptr %heap_ptr2, i32 0, i32 2
  store i32 3, ptr %2, align 4
  %arr3 = load ptr, ptr %arr, align 8
  ret ptr %arr3
}

define { ptr, ptr } @get_both() {
entry:
  %arr = alloca ptr, align 8
  %heap_arr = call ptr @malloc(i64 12)
  store ptr %heap_arr, ptr %arr, align 8
  %heap_ptr = load ptr, ptr %arr, align 8
  %0 = getelementptr inbounds [3 x i32], ptr %heap_ptr, i32 0, i32 0
  store i32 4, ptr %0, align 4
  %heap_ptr1 = load ptr, ptr %arr, align 8
  %1 = getelementptr inbounds [3 x i32], ptr %heap_ptr1, i32 0, i32 1
  store i32 5, ptr %1, align 4
  %heap_ptr2 = load ptr, ptr %arr, align 8
  %2 = getelementptr inbounds [3 x i32], ptr %heap_ptr2, i32 0, i32 2
  store i32 6, ptr %2, align 4
  %arr3 = load ptr, ptr %arr, align 8
  %3 = insertvalue { ptr, ptr } undef, ptr %arr3, 0
  %4 = insertvalue { ptr, ptr } %3, ptr @.str.24, 1
  ret { ptr, ptr } %4
}

define i32 @print_array(ptr %arr, i32 %size) {
entry:
  %i = alloca i32, align 4
  %size2 = alloca i32, align 4
  %arr1 = alloca ptr, align 8
  store ptr %arr, ptr %arr1, align 8
  store i32 %size, ptr %size2, align 4
  store i32 0, ptr %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %i3 = load i32, ptr %i, align 4
  %size4 = load i32, ptr %size2, align 4
  %icmplt = icmp slt i32 %i3, %size4
  br i1 %icmplt, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %arr_ptr = load ptr, ptr %arr1, align 8
  %i5 = load i32, ptr %i, align 4
  %arr_elem_ptr = getelementptr i32, ptr %arr_ptr, i32 %i5
  %arr_elem = load i32, ptr %arr_elem_ptr, align 4
  call void @qc_print_int(i32 %arr_elem)
  call void @qc_print_string(ptr @.str.25)
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %i6 = load i32, ptr %i, align 4
  %add = add i32 %i6, 1
  store i32 %add, ptr %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  call void @qc_println(ptr @.str.26)
  ret i32 0
}

define ptr @make_list() {
entry:
  %nums = alloca ptr, align 8
  %temp_elem2 = alloca i32, align 4
  %temp_elem1 = alloca i32, align 4
  %temp_elem = alloca i32, align 4
  call void @qc_println(ptr @.str.27)
  %list_ptr = call ptr @qc_create_list(i32 0)
  store i32 1, ptr %temp_elem, align 4
  call void @qc_list_push(ptr %list_ptr, ptr %temp_elem, i32 0)
  store i32 2, ptr %temp_elem1, align 4
  call void @qc_list_push(ptr %list_ptr, ptr %temp_elem1, i32 0)
  store i32 3, ptr %temp_elem2, align 4
  call void @qc_list_push(ptr %list_ptr, ptr %temp_elem2, i32 0)
  store ptr %list_ptr, ptr %nums, align 8
  call void @qc_println(ptr @.str.28)
  %nums3 = load ptr, ptr %nums, align 8
  %list_len = call i32 @qc_list_length(ptr %nums3)
  call void @qc_print_int(i32 %list_len)
  call void @qc_print_char(i8 10)
  %nums4 = load ptr, ptr %nums, align 8
  ret ptr %nums4
}

define ptr @double_list(ptr %input) {
entry:
  %push_arg = alloca i32, align 4
  %x = alloca i32, align 4
  %__foreach_i_x = alloca i32, align 4
  %result = alloca ptr, align 8
  %input1 = alloca ptr, align 8
  store ptr %input, ptr %input1, align 8
  %list_ptr = call ptr @qc_create_list(i32 0)
  store ptr %list_ptr, ptr %result, align 8
  %input2 = load ptr, ptr %input1, align 8
  %coll_len = call i32 @qc_list_length(ptr %input2)
  store i32 0, ptr %__foreach_i_x, align 4
  br label %foreach.cond

foreach.cond:                                     ; preds = %foreach.inc, %entry
  %__foreach_i_x3 = load i32, ptr %__foreach_i_x, align 4
  %foreach_cmp = icmp slt i32 %__foreach_i_x3, %coll_len
  br i1 %foreach_cmp, label %foreach.body, label %foreach.end

foreach.body:                                     ; preds = %foreach.cond
  %elem_ptr = call ptr @qc_list_get(ptr %input2, i32 %__foreach_i_x3)
  %elem = load i32, ptr %elem_ptr, align 4
  store i32 %elem, ptr %x, align 4
  %result4 = load ptr, ptr %result, align 8
  %x5 = load i32, ptr %x, align 4
  %mul = mul i32 %x5, 2
  store i32 %mul, ptr %push_arg, align 4
  call void @qc_list_push(ptr %result4, ptr %push_arg, i32 0)
  br label %foreach.inc

foreach.inc:                                      ; preds = %foreach.body
  %__foreach_i_x6 = load i32, ptr %__foreach_i_x, align 4
  %i_inc = add i32 %__foreach_i_x6, 1
  store i32 %i_inc, ptr %__foreach_i_x, align 4
  br label %foreach.cond

foreach.end:                                      ; preds = %foreach.cond
  %result7 = load ptr, ptr %result, align 8
  ret ptr %result7
}

define { ptr, i32 } @get_list_and_count() {
entry:
  %data = alloca ptr, align 8
  %temp_elem2 = alloca i32, align 4
  %temp_elem1 = alloca i32, align 4
  %temp_elem = alloca i32, align 4
  %list_ptr = call ptr @qc_create_list(i32 0)
  store i32 10, ptr %temp_elem, align 4
  call void @qc_list_push(ptr %list_ptr, ptr %temp_elem, i32 0)
  store i32 20, ptr %temp_elem1, align 4
  call void @qc_list_push(ptr %list_ptr, ptr %temp_elem1, i32 0)
  store i32 30, ptr %temp_elem2, align 4
  call void @qc_list_push(ptr %list_ptr, ptr %temp_elem2, i32 0)
  store ptr %list_ptr, ptr %data, align 8
  %data3 = load ptr, ptr %data, align 8
  %0 = insertvalue { ptr, i32 } undef, ptr %data3, 0
  %1 = insertvalue { ptr, i32 } %0, i32 3, 1
  ret { ptr, i32 } %1
}

define i32 @inc(i32 %x) {
entry:
  %x1 = alloca i32, align 4
  store i32 %x, ptr %x1, align 4
  %x2 = load i32, ptr %x1, align 4
  %add = add i32 %x2, 1
  ret i32 %add
}

define i32 @twice(i32 %x) {
entry:
  %x1 = alloca i32, align 4
  store i32 %x, ptr %x1, align 4
  %x2 = load i32, ptr %x1, align 4
  %calltmp = call i32 @inc(i32 %x2)
  %calltmp3 = call i32 @inc(i32 %calltmp)
  ret i32 %calltmp3
}

define i32 @__user_entry() {
entry:
  %inferedlist = alloca ptr, align 8
  %temp_elem1516 = alloca double, align 8
  %temp_elem1515 = alloca double, align 8
  %infferedarr = alloca ptr, align 8
  %ops = alloca %MathOps, align 8
  %temp_eval = alloca %Product, align 8
  %temp_repr = alloca %Product, align 8
  %laptop = alloca %Product, align 8
  %defaultProductMess = alloca %Product, align 8
  %temp_op_lhs1490 = alloca %Vector2D, align 8
  %temp_obj1484 = alloca %Vector2D, align 8
  %temp_obj1479 = alloca %Vector2D, align 8
  %temp_op_lhs = alloca %Vector2D, align 8
  %v31475 = alloca %Vector2D, align 8
  %v21474 = alloca %Vector2D, align 8
  %v11473 = alloca %Vector2D, align 8
  %dc = alloca %DoubleCounter, align 8
  %myBox = alloca %ColoredBox, align 8
  %temp_obj1461 = alloca %Director, align 8
  %temp_obj1457 = alloca %Director, align 8
  %temp_obj1453 = alloca %Director, align 8
  %ceo = alloca %Director, align 8
  %derived = alloca %DerivedClass, align 8
  %hero = alloca %Warrior, align 8
  %temp_obj1436 = alloca %SecureBox, align 8
  %temp_obj1429 = alloca %SecureBox, align 8
  %box = alloca %SecureBox, align 8
  %temp_obj1424 = alloca %SavingsAccount, align 8
  %temp_obj1418 = alloca %SavingsAccount, align 8
  %temp_obj1415 = alloca %SavingsAccount, align 8
  %savings = alloca %SavingsAccount, align 8
  %temp_obj1411 = alloca %FlowerPlant, align 8
  %temp_obj1408 = alloca %FlowerPlant, align 8
  %temp_obj1405 = alloca %FlowerPlant, align 8
  %rose = alloca %FlowerPlant, align 8
  %myCar = alloca %CarInherit, align 8
  %temp_obj1396 = alloca %DogInherit, align 8
  %temp_obj1393 = alloca %DogInherit, align 8
  %temp_obj1390 = alloca %DogInherit, align 8
  %myDogInherit = alloca %DogInherit, align 8
  %bot = alloca %Robot, align 8
  %alice = alloca %Person, align 8
  %counter1359 = alloca %Counter, align 8
  %calc = alloca %Calculator, align 8
  %myCat = alloca %Cat, align 8
  %temp_obj1347 = alloca %Dog, align 8
  %temp_obj = alloca %Dog, align 8
  %myDog = alloca %Dog, align 8
  %tier3 = alloca %TierLevel, align 8
  %tier2 = alloca %TierLevel, align 8
  %tier1 = alloca %TierLevel, align 8
  %negValue = alloca i32, align 4
  %enum_int1308 = alloca i32, align 4
  %negStatus = alloca %HttpStatus, align 8
  %enum_int1290 = alloca i32, align 4
  %enum_int1288 = alloca i32, align 4
  %iterStatus = alloca %HttpStatus, align 8
  %idx = alloca i32, align 4
  %enum_int1263 = alloca i32, align 4
  %counter = alloca i32, align 4
  %enum_int1258 = alloca i32, align 4
  %loopStatus = alloca %HttpStatus, align 8
  %typeof_result1252 = alloca ptr, align 8
  %statusType = alloca ptr, align 8
  %enum_int1249 = alloca i32, align 4
  %myStatus = alloca %HttpStatus, align 8
  %typeof_result = alloca ptr, align 8
  %typeofPlan = alloca ptr, align 8
  %myPlan = alloca %TierLevel, align 8
  %enum_int1226 = alloca i32, align 4
  %respMsg = alloca ptr, align 8
  %respStatus = alloca %HttpStatus, align 8
  %enum_int1208 = alloca i32, align 4
  %result21205 = alloca %HttpStatus, align 8
  %enum_int1189 = alloca i32, align 4
  %result11186 = alloca %HttpStatus, align 8
  %planName = alloca ptr, align 8
  %plan = alloca %TierLevel, align 8
  %numCode = alloca i32, align 4
  %enum_int1182 = alloca i32, align 4
  %code = alloca %HttpStatus, align 8
  %planType = alloca %TierLevel, align 8
  %enum_int1162 = alloca i32, align 4
  %enum_int1142 = alloca i32, align 4
  %enum_int1140 = alloca i32, align 4
  %responseCode = alloca %HttpStatus, align 8
  %currentTier = alloca %TierLevel, align 8
  %enum_int1124 = alloca i32, align 4
  %enum_int1091 = alloca i32, align 4
  %enum_int1089 = alloca i32, align 4
  %status2 = alloca %HttpStatus, align 8
  %enum_int1088 = alloca i32, align 4
  %status1 = alloca %HttpStatus, align 8
  %msg = alloca %ConfigValue, align 8
  %enum_int1087 = alloca i32, align 4
  %retries = alloca %ConfigValue, align 8
  %userTier = alloca %TierLevel, align 8
  %enum_int1086 = alloca i32, align 4
  %enum_int = alloca i32, align 4
  %statusCode = alloca %HttpStatus, align 8
  %fxxxxxx = alloca float, align 4
  %sxxxxxx = alloca ptr, align 8
  %xxxxxxxx = alloca i32, align 4
  %line = alloca ptr, align 8
  %readAgain = alloca ptr, align 8
  %appendFile = alloca ptr, align 8
  %line3 = alloca ptr, align 8
  %line2 = alloca ptr, align 8
  %line1 = alloca ptr, align 8
  %inFile = alloca ptr, align 8
  %outFile = alloca ptr, align 8
  %ddddd = alloca i32, align 4
  %ccccc = alloca i32, align 4
  %bbbbb = alloca i32, align 4
  %aaaaa = alloca i32, align 4
  %resp3 = alloca %Response, align 8
  %resp2 = alloca %Response, align 8
  %resp1 = alloca %Response, align 8
  %p6 = alloca %Pair, align 8
  %p5 = alloca %Pair, align 8
  %p4 = alloca %Pair, align 8
  %p3 = alloca %Pair, align 8
  %p2222 = alloca %Pair, align 8
  %p1 = alloca %Pair, align 8
  %mx5 = alloca %Mixed, align 8
  %mx4 = alloca %Mixed, align 8
  %mx3 = alloca %Mixed, align 8
  %mx2 = alloca %Mixed, align 8
  %mx1 = alloca %Mixed, align 8
  %codeValue = alloca %Code, align 8
  %srvrv = alloca %Status, align 8
  %mrv = alloca %Multi, align 8
  %vrv3 = alloca %Value, align 8
  %vrv2 = alloca %Value, align 8
  %vrv1 = alloca %Value, align 8
  %r3 = alloca %Result, align 8
  %r2 = alloca %Result, align 8
  %r1 = alloca %Result, align 8
  %rect = alloca %Rectangle, align 8
  %p2 = alloca %Point, align 8
  %p = alloca %Point, align 8
  %xccccccc = alloca i32, align 4
  %__foreach_i_xccccccc = alloca i32, align 4
  %withEmpty = alloca [2 x i32], align 4
  %empty636 = alloca ptr, align 8
  %namenamename = alloca ptr, align 8
  %__foreach_i_namenamename = alloca i32, align 4
  %allNames = alloca ptr, align 8
  %arr_lit614 = alloca [4 x ptr], align 8
  %names2 = alloca ptr, align 8
  %names1 = alloca ptr, align 8
  %spread_ret602 = alloca i32, align 4
  %arg_temp601 = alloca i32, align 4
  %arg_temp600 = alloca i32, align 4
  %arg_temp = alloca i32, align 4
  %expand_idx597 = alloca i32, align 4
  %expand_i596 = alloca i32, align 4
  %first = alloca ptr, align 8
  %spread_ret583 = alloca i32, align 4
  %expand_idx580 = alloca i32, align 4
  %expand_i579 = alloca i32, align 4
  %values = alloca ptr, align 8
  %sumsum = alloca ptr, align 8
  %spread_ret = alloca i32, align 4
  %expand_idx = alloca i32, align 4
  %expand_i = alloca i32, align 4
  %args = alloca ptr, align 8
  %xcxcxc = alloca i32, align 4
  %__foreach_i_xcxcxc = alloca i32, align 4
  %multi = alloca ptr, align 8
  %arr_lit535 = alloca [6 x i32], align 4
  %c526 = alloca ptr, align 8
  %b522 = alloca ptr, align 8
  %a518 = alloca ptr, align 8
  %xcxxc = alloca i32, align 4
  %__foreach_i_xcxxc = alloca i32, align 4
  %arrFromList = alloca ptr, align 8
  %arrFromList_size = alloca i32, align 4
  %copy_dest_idx = alloca i32, align 4
  %copy_i = alloca i32, align 4
  %ListList = alloca ptr, align 8
  %temp_elem497 = alloca i32, align 4
  %temp_elem496 = alloca i32, align 4
  %temp_elem495 = alloca i32, align 4
  %xxxdxxx = alloca i32, align 4
  %__foreach_i_xxxdxxx = alloca i32, align 4
  %fromArray = alloca ptr, align 8
  %temp_elem480 = alloca i32, align 4
  %spread_push_i479 = alloca i32, align 4
  %nums = alloca ptr, align 8
  %xdxdxdx457 = alloca i32, align 4
  %__foreach_i_xdxdxdx456 = alloca i32, align 4
  %merged = alloca ptr, align 8
  %temp_elem453 = alloca i32, align 4
  %spread_push_i452 = alloca i32, align 4
  %spread_push_i = alloca i32, align 4
  %list2 = alloca ptr, align 8
  %temp_elem443 = alloca i32, align 4
  %temp_elem442 = alloca i32, align 4
  %list1 = alloca ptr, align 8
  %temp_elem440 = alloca i32, align 4
  %temp_elem439 = alloca i32, align 4
  %xdxdxdx = alloca i32, align 4
  %__foreach_i_xdxdxdx = alloca i32, align 4
  %combined = alloca ptr, align 8
  %arr_lit = alloca [7 x i32], align 4
  %arr2 = alloca ptr, align 8
  %arr1 = alloca ptr, align 8
  %myMap = alloca ptr, align 8
  %temp_val399 = alloca i32, align 4
  %temp_val398 = alloca i32, align 4
  %map_val393 = alloca i32, align 4
  %empty_map = alloca ptr, align 8
  %map_key386 = alloca i32, align 4
  %map_key = alloca i32, align 4
  %names = alloca ptr, align 8
  %temp_key381 = alloca i32, align 4
  %temp_key380 = alloca i32, align 4
  %temp_key = alloca i32, align 4
  %key = alloca ptr, align 8
  %__foreach_i_key = alloca i32, align 4
  %map_val346 = alloca i32, align 4
  %map_val343 = alloca i32, align 4
  %ages = alloca ptr, align 8
  %temp_val333 = alloca i32, align 4
  %temp_val332 = alloca i32, align 4
  %temp_val = alloca i32, align 4
  %xyzd = alloca i32, align 4
  %__foreach_i_xyzd = alloca i32, align 4
  %countcc = alloca i32, align 4
  %datacc = alloca ptr, align 8
  %xccc305 = alloca i32, align 4
  %__foreach_i_xccc304 = alloca i32, align 4
  %doubled = alloca ptr, align 8
  %xccc = alloca i32, align 4
  %__foreach_i_xccc = alloca i32, align 4
  %listy = alloca ptr, align 8
  %y262 = alloca i32, align 4
  %__foreach_i_y = alloca i32, align 4
  %push_arg258 = alloca i32, align 4
  %push_arg = alloca i32, align 4
  %list_len = alloca i32, align 4
  %myList = alloca ptr, align 8
  %temp_elem252 = alloca i32, align 4
  %temp_elem251 = alloca i32, align 4
  %temp_elem250 = alloca i32, align 4
  %vz = alloca i32, align 4
  %__foreach_i_vz = alloca i32, align 4
  %arr_len = alloca i32, align 4
  %arr = alloca ptr, align 8
  %aList = alloca ptr, align 8
  %temp_elem232 = alloca i32, align 4
  %temp_elem231 = alloca i32, align 4
  %temp_elem230 = alloca i32, align 4
  %temp_elem229 = alloca i32, align 4
  %strnthing = alloca ptr, align 8
  %brray1 = alloca ptr, align 8
  %array1 = alloca ptr, align 8
  %indices_arr220 = alloca [2 x i32], align 4
  %val2 = alloca i32, align 4
  %indices_arr216 = alloca [2 x i32], align 4
  %val1 = alloca i32, align 4
  %deep = alloca ptr, align 8
  %temp_elem211 = alloca i32, align 4
  %temp_elem210 = alloca i32, align 4
  %temp_elem209 = alloca i32, align 4
  %temp_elem206 = alloca i32, align 4
  %temp_elem204 = alloca i32, align 4
  %temp_elem203 = alloca i32, align 4
  %jagged = alloca ptr, align 8
  %temp_elem199 = alloca i32, align 4
  %temp_elem198 = alloca i32, align 4
  %temp_elem196 = alloca i32, align 4
  %temp_elem195 = alloca i32, align 4
  %temp_elem194 = alloca i32, align 4
  %regular187 = alloca ptr, align 8
  %indices_arr = alloca [2 x i32], align 4
  %val = alloca i32, align 4
  %grid = alloca ptr, align 8
  %temp_elem183 = alloca i32, align 4
  %temp_elem182 = alloca i32, align 4
  %temp_elem180 = alloca i32, align 4
  %temp_elem179 = alloca i32, align 4
  %temp_elem = alloca i32, align 4
  %sf = alloca ptr, align 8
  %si = alloca ptr, align 8
  %replaced = alloca ptr, align 8
  %trimmed = alloca ptr, align 8
  %sub170 = alloca ptr, align 8
  %ew = alloca i1, align 1
  %sw = alloca i1, align 1
  %c = alloca i1, align 1
  %lower = alloca ptr, align 8
  %upper = alloca ptr, align 8
  %l = alloca i32, align 4
  %s = alloca ptr, align 8
  %rr = alloca i32, align 4
  %ri = alloca i32, align 4
  %r = alloca float, align 4
  %t = alloca i32, align 4
  %q7 = alloca i2, align 1
  %q6 = alloca i2, align 1
  %q5 = alloca i2, align 1
  %q4 = alloca i2, align 1
  %q3 = alloca i2, align 1
  %q2 = alloca i2, align 1
  %q1 = alloca i2, align 1
  %both_tester = alloca i2, align 1
  %not_test = alloca i1, align 1
  %xor_test = alloca i1, align 1
  %or_test = alloca i1, align 1
  %and_test = alloca i1, align 1
  %btb = alloca i1, align 1
  %ata = alloca i1, align 1
  %xyz = alloca i32, align 4
  %result = alloca i32, align 4
  %gte = alloca i1, align 1
  %lte = alloca i1, align 1
  %gt = alloca i1, align 1
  %lt = alloca i1, align 1
  %ne = alloca i1, align 1
  %eq = alloca i1, align 1
  %ydd = alloca i32, align 4
  %xdd = alloca i32, align 4
  %dresult = alloca double, align 8
  %dexp = alloca double, align 8
  %dbase = alloca double, align 8
  %fresult = alloca float, align 4
  %fexp = alloca float, align 4
  %fbase = alloca float, align 4
  %exp = alloca i32, align 4
  %base = alloca i32, align 4
  %path = alloca ptr, align 8
  %quote = alloca ptr, align 8
  %non = alloca ptr, align 8
  %exclaim = alloca ptr, align 8
  %world = alloca ptr, align 8
  %hello = alloca ptr, align 8
  %nul = alloca i2, align 1
  %dead = alloca i2, align 1
  %alive = alloca i2, align 1
  %schrodinger = alloca i2, align 1
  %no = alloca i1, align 1
  %yes = alloca i1, align 1
  %tab = alloca i8, align 1
  %newline = alloca i8, align 1
  %space = alloca i8, align 1
  %end = alloca i8, align 1
  %start = alloca i8, align 1
  %result3 = alloca i32, align 4
  %result2 = alloca i32, align 4
  %result1 = alloca double, align 8
  %d = alloca double, align 8
  %f = alloca float, align 4
  %i = alloca i32, align 4
  %fquot = alloca float, align 4
  %fprod = alloca float, align 4
  %fdiff = alloca float, align 4
  %fsum = alloca float, align 4
  %b = alloca float, align 4
  %a = alloca float, align 4
  %power = alloca i32, align 4
  %rem = alloca i32, align 4
  %quot = alloca i32, align 4
  %prod = alloca i32, align 4
  %diff = alloca i32, align 4
  %sum = alloca i32, align 4
  %y = alloca i32, align 4
  %x = alloca i32, align 4
  %emoji = alloca ptr, align 8
  %greeting = alloca ptr, align 8
  %name = alloca ptr, align 8
  %negative = alloca i2, align 1
  %empty = alloca i2, align 1
  %collapsed = alloca i2, align 1
  %superposition = alloca i2, align 1
  %isBoring = alloca i1, align 1
  %isAwesome = alloca i1, align 1
  %symbol = alloca i8, align 1
  %digit = alloca i8, align 1
  %letter = alloca i8, align 1
  %precise = alloca double, align 8
  %pi = alloca float, align 4
  %huge = alloca i64, align 8
  %tiny = alloca i16, align 2
  %regular = alloca i32, align 4
  %v3 = alloca i32, align 4
  %v2 = alloca double, align 8
  %v1 = alloca i32, align 4
  %asdfname = alloca ptr, align 8
  %idddddd = alloca i32, align 4
  %ydddddddd = alloca i32, align 4
  %adder = alloca ptr, align 8
  %xdddddddd = alloca i32, align 4
  %fstringt = alloca ptr, align 8
  %testerfloat = alloca float, align 4
  %thing = alloca ptr, align 8
  %testerf = alloca i32, align 4
  store i32 5, ptr %testerf, align 4
  %heap_arr = call ptr @malloc(i64 20)
  store ptr %heap_arr, ptr %thing, align 8
  %heap_ptr = load ptr, ptr %thing, align 8
  %0 = getelementptr inbounds [5 x i32], ptr %heap_ptr, i32 0, i32 0
  store i32 1, ptr %0, align 4
  %heap_ptr1 = load ptr, ptr %thing, align 8
  %1 = getelementptr inbounds [5 x i32], ptr %heap_ptr1, i32 0, i32 1
  store i32 2, ptr %1, align 4
  %heap_ptr2 = load ptr, ptr %thing, align 8
  %2 = getelementptr inbounds [5 x i32], ptr %heap_ptr2, i32 0, i32 2
  store i32 3, ptr %2, align 4
  %heap_ptr3 = load ptr, ptr %thing, align 8
  %3 = getelementptr inbounds [5 x i32], ptr %heap_ptr3, i32 0, i32 3
  store i32 4, ptr %3, align 4
  %heap_ptr4 = load ptr, ptr %thing, align 8
  %4 = getelementptr inbounds [5 x i32], ptr %heap_ptr4, i32 0, i32 4
  store i32 5, ptr %4, align 4
  store float 3.500000e+00, ptr %testerfloat, align 4
  %testerf5 = load i32, ptr %testerf, align 4
  %fstr_i32 = call ptr @qc_to_string_int(i32 %testerf5)
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.29, ptr %fstr_i32)
  %fstr_concat6 = call ptr @qc_string_concat(ptr %fstr_concat, ptr @.str.30)
  %testerfloat7 = load float, ptr %testerfloat, align 4
  %fstr_f32 = call ptr @qc_to_string_float(float %testerfloat7)
  %fstr_concat8 = call ptr @qc_string_concat(ptr %fstr_concat6, ptr %fstr_f32)
  store ptr %fstr_concat8, ptr %fstringt, align 8
  %fstringt9 = load ptr, ptr %fstringt, align 8
  call void @qc_print_string(ptr %fstringt9)
  call void @qc_print_char(i8 10)
  %calltmp = call i32 @add(i32 2, i32 3)
  store i32 %calltmp, ptr %xdddddddd, align 4
  store ptr @__lambda_0, ptr %adder, align 8
  %adder10 = load ptr, ptr %adder, align 8
  %calltmp11 = call i32 %adder10(i32 10, i32 20)
  store i32 %calltmp11, ptr %ydddddddd, align 4
  %calltmp12 = call { i32, ptr } @get_user()
  %5 = extractvalue { i32, ptr } %calltmp12, 0
  store i32 %5, ptr %idddddd, align 4
  %6 = extractvalue { i32, ptr } %calltmp12, 1
  store ptr %6, ptr %asdfname, align 8
  %calltmp13 = call i32 @greet()
  %calltmp14 = call i32 @greet(ptr @.str.31)
  %calltmp15 = call i32 @greet(ptr @.str.32, i32 3)
  %ydddddddd16 = load i32, ptr %ydddddddd, align 4
  call void @qc_print_int(i32 %ydddddddd16)
  call void @qc_print_char(i8 10)
  %calltmp17 = call i32 @mul_add(i32 2, i32 3, i32 4)
  store i32 %calltmp17, ptr %v1, align 4
  %calltmp18 = call double @square(double 1.500000e+00)
  store double %calltmp18, ptr %v2, align 8
  %v119 = load i32, ptr %v1, align 4
  %calltmp20 = call i32 @mul_add(i32 %v119, i32 3, i32 1)
  store i32 %calltmp20, ptr %v3, align 4
  store i32 42, ptr %regular, align 4
  store i16 100, ptr %tiny, align 2
  store i64 9999999, ptr %huge, align 8
  store float 0x40091EB860000000, ptr %pi, align 4
  store double 0x400921FB54442EEA, ptr %precise, align 8
  store i8 65, ptr %letter, align 1
  store i8 55, ptr %digit, align 1
  store i8 64, ptr %symbol, align 1
  store i1 true, ptr %isAwesome, align 1
  store i1 false, ptr %isBoring, align 1
  store i2 -1, ptr %superposition, align 1
  store i2 -2, ptr %collapsed, align 1
  store i2 0, ptr %empty, align 1
  store i2 1, ptr %negative, align 1
  store ptr @.str.33, ptr %name, align 8
  store ptr @.str.34, ptr %greeting, align 8
  store ptr @.str.35, ptr %emoji, align 8
  store i32 10, ptr %x, align 4
  store i32 3, ptr %y, align 4
  %x21 = load i32, ptr %x, align 4
  %y22 = load i32, ptr %y, align 4
  %add = add i32 %x21, %y22
  store i32 %add, ptr %sum, align 4
  %x23 = load i32, ptr %x, align 4
  %y24 = load i32, ptr %y, align 4
  %sub = sub i32 %x23, %y24
  store i32 %sub, ptr %diff, align 4
  %x25 = load i32, ptr %x, align 4
  %y26 = load i32, ptr %y, align 4
  %mul = mul i32 %x25, %y26
  store i32 %mul, ptr %prod, align 4
  %x27 = load i32, ptr %x, align 4
  %y28 = load i32, ptr %y, align 4
  %sdiv = sdiv i32 %x27, %y28
  store i32 %sdiv, ptr %quot, align 4
  %x29 = load i32, ptr %x, align 4
  %y30 = load i32, ptr %y, align 4
  %srem = srem i32 %x29, %y30
  store i32 %srem, ptr %rem, align 4
  %powi = call i32 @qc_powi_i32(i32 2, i32 8)
  store i32 %powi, ptr %power, align 4
  %x31 = load i32, ptr %x, align 4
  %add32 = add i32 %x31, 5
  store i32 %add32, ptr %x, align 4
  %x33 = load i32, ptr %x, align 4
  %sub34 = sub i32 %x33, 3
  store i32 %sub34, ptr %x, align 4
  %x35 = load i32, ptr %x, align 4
  %mul36 = mul i32 %x35, 2
  store i32 %mul36, ptr %x, align 4
  %x37 = load i32, ptr %x, align 4
  %sdiv38 = sdiv i32 %x37, 4
  store i32 %sdiv38, ptr %x, align 4
  %x39 = load i32, ptr %x, align 4
  %srem40 = srem i32 %x39, 5
  store i32 %srem40, ptr %x, align 4
  store float 1.050000e+01, ptr %a, align 4
  store float 2.500000e+00, ptr %b, align 4
  %a41 = load float, ptr %a, align 4
  %b42 = load float, ptr %b, align 4
  %fadd = fadd float %a41, %b42
  store float %fadd, ptr %fsum, align 4
  %a43 = load float, ptr %a, align 4
  %b44 = load float, ptr %b, align 4
  %fsub = fsub float %a43, %b44
  store float %fsub, ptr %fdiff, align 4
  %a45 = load float, ptr %a, align 4
  %b46 = load float, ptr %b, align 4
  %fmul = fmul float %a45, %b46
  store float %fmul, ptr %fprod, align 4
  %a47 = load float, ptr %a, align 4
  %b48 = load float, ptr %b, align 4
  %fdiv = fdiv float %a47, %b48
  store float %fdiv, ptr %fquot, align 4
  %a49 = load float, ptr %a, align 4
  %fadd50 = fadd float %a49, 1.500000e+00
  store float %fadd50, ptr %a, align 4
  %a51 = load float, ptr %a, align 4
  %fsub52 = fsub float %a51, 2.000000e+00
  store float %fsub52, ptr %a, align 4
  %a53 = load float, ptr %a, align 4
  %fmul54 = fmul float %a53, 3.000000e+00
  store float %fmul54, ptr %a, align 4
  %a55 = load float, ptr %a, align 4
  %fdiv56 = fdiv float %a55, 5.000000e+00
  store float %fdiv56, ptr %a, align 4
  store i32 10, ptr %i, align 4
  store float 0x40091EB860000000, ptr %f, align 4
  store double 2.718000e+00, ptr %d, align 8
  %f57 = load float, ptr %f, align 4
  %d58 = load double, ptr %d, align 8
  %promote_to_double = fpext float %f57 to double
  %fadd59 = fadd double %promote_to_double, %d58
  store double %fadd59, ptr %result1, align 8
  %i60 = load i32, ptr %i, align 4
  %i61 = load i32, ptr %i, align 4
  %add62 = add i32 %i60, %i61
  store i32 %add62, ptr %result2, align 4
  %i63 = load i32, ptr %i, align 4
  %mul64 = mul i32 %i63, 2
  store i32 %mul64, ptr %result3, align 4
  %i65 = load i32, ptr %i, align 4
  %add66 = add i32 %i65, 5
  store i32 %add66, ptr %i, align 4
  %f67 = load float, ptr %f, align 4
  %fadd68 = fadd float %f67, 1.500000e+00
  store float %fadd68, ptr %f, align 4
  %d69 = load double, ptr %d, align 8
  %fadd70 = fadd double %d69, 1.000000e-03
  store double %fadd70, ptr %d, align 8
  store i8 65, ptr %start, align 1
  store i8 90, ptr %end, align 1
  store i8 32, ptr %space, align 1
  store i8 10, ptr %newline, align 1
  store i8 9, ptr %tab, align 1
  %start71 = load i8, ptr %start, align 1
  store i8 66, ptr %start, align 1
  %end72 = load i8, ptr %end, align 1
  store i8 89, ptr %end, align 1
  store i1 true, ptr %yes, align 1
  store i1 false, ptr %no, align 1
  %yes73 = load i1, ptr %yes, align 1
  store i1 false, ptr %yes, align 1
  %no74 = load i1, ptr %no, align 1
  store i1 true, ptr %no, align 1
  %yes75 = load i1, ptr %yes, align 1
  store i1 true, ptr %yes, align 1
  store i2 -1, ptr %schrodinger, align 1
  store i2 -2, ptr %alive, align 1
  store i2 1, ptr %dead, align 1
  store i2 0, ptr %nul, align 1
  %schrodinger76 = load i2, ptr %schrodinger, align 1
  store i2 -2, ptr %schrodinger, align 1
  %alive77 = load i2, ptr %alive, align 1
  store i2 -1, ptr %alive, align 1
  %dead78 = load i2, ptr %dead, align 1
  store i2 0, ptr %dead, align 1
  %nul79 = load i2, ptr %nul, align 1
  store i2 1, ptr %nul, align 1
  store ptr @.str.36, ptr %hello, align 8
  store ptr @.str.37, ptr %world, align 8
  store ptr @.str.38, ptr %exclaim, align 8
  store ptr @.str.39, ptr %non, align 8
  store ptr @.str.40, ptr %quote, align 8
  store ptr @.str.41, ptr %path, align 8
  store i32 2, ptr %base, align 4
  store i32 10, ptr %exp, align 4
  store float 2.000000e+00, ptr %fbase, align 4
  store float 3.000000e+00, ptr %fexp, align 4
  %fbase80 = load float, ptr %fbase, align 4
  %fexp81 = load float, ptr %fexp, align 4
  %pow = call float @llvm.pow.f32(float %fbase80, float %fexp81)
  store float %pow, ptr %fresult, align 4
  store double 1.500000e+00, ptr %dbase, align 8
  store double 2.000000e+00, ptr %dexp, align 8
  %dbase82 = load double, ptr %dbase, align 8
  %dexp83 = load double, ptr %dexp, align 8
  %pow84 = call double @llvm.pow.f64(double %dbase82, double %dexp83)
  store double %pow84, ptr %dresult, align 8
  store i32 5, ptr %xdd, align 4
  store i32 10, ptr %ydd, align 4
  %xdd85 = load i32, ptr %xdd, align 4
  %ydd86 = load i32, ptr %ydd, align 4
  %icmpeq = icmp eq i32 %xdd85, %ydd86
  store i1 %icmpeq, ptr %eq, align 1
  %xdd87 = load i32, ptr %xdd, align 4
  %ydd88 = load i32, ptr %ydd, align 4
  %icmpne = icmp ne i32 %xdd87, %ydd88
  store i1 %icmpne, ptr %ne, align 1
  %xdd89 = load i32, ptr %xdd, align 4
  %ydd90 = load i32, ptr %ydd, align 4
  %icmplt = icmp slt i32 %xdd89, %ydd90
  store i1 %icmplt, ptr %lt, align 1
  %xdd91 = load i32, ptr %xdd, align 4
  %ydd92 = load i32, ptr %ydd, align 4
  %icmpgt = icmp sgt i32 %xdd91, %ydd92
  store i1 %icmpgt, ptr %gt, align 1
  %xdd93 = load i32, ptr %xdd, align 4
  %ydd94 = load i32, ptr %ydd, align 4
  %icmple = icmp sle i32 %xdd93, %ydd94
  store i1 %icmple, ptr %lte, align 1
  %xdd95 = load i32, ptr %xdd, align 4
  %ydd96 = load i32, ptr %ydd, align 4
  %icmpge = icmp sge i32 %xdd95, %ydd96
  store i1 %icmpge, ptr %gte, align 1
  store i32 0, ptr %result, align 4
  %xdd97 = load i32, ptr %xdd, align 4
  %icmpgt98 = icmp sgt i32 %xdd97, 3
  br i1 %icmpgt98, label %then, label %else

then:                                             ; preds = %entry
  %result99 = load i32, ptr %result, align 4
  store i32 10, ptr %result, align 4
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %i101 = load i32, ptr %i, align 4
  store i32 0, ptr %i, align 4
  %sum102 = load i32, ptr %sum, align 4
  store i32 0, ptr %sum, align 4
  br label %while.cond

else:                                             ; preds = %entry
  %result100 = load i32, ptr %result, align 4
  store i32 20, ptr %result, align 4
  br label %ifcont

while.cond:                                       ; preds = %while.body, %ifcont
  %i103 = load i32, ptr %i, align 4
  %icmplt104 = icmp slt i32 %i103, 5
  br i1 %icmplt104, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %sum105 = load i32, ptr %sum, align 4
  %i106 = load i32, ptr %i, align 4
  %add107 = add i32 %sum105, %i106
  store i32 %add107, ptr %sum, align 4
  %i108 = load i32, ptr %i, align 4
  %add109 = add i32 %i108, 1
  store i32 %add109, ptr %i, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %sum110 = load i32, ptr %sum, align 4
  store i32 0, ptr %sum, align 4
  store i32 0, ptr %xyz, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %while.end
  %xyz111 = load i32, ptr %xyz, align 4
  %icmplt112 = icmp slt i32 %xyz111, 5
  br i1 %icmplt112, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %sum113 = load i32, ptr %sum, align 4
  %xyz114 = load i32, ptr %xyz, align 4
  %add115 = add i32 %sum113, %xyz114
  store i32 %add115, ptr %sum, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %xyz116 = load i32, ptr %xyz, align 4
  %add117 = add i32 %xyz116, 1
  store i32 %add117, ptr %xyz, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  store i1 true, ptr %ata, align 1
  store i1 false, ptr %btb, align 1
  %ata118 = load i1, ptr %ata, align 1
  %btb119 = load i1, ptr %btb, align 1
  %and = and i1 %ata118, %btb119
  store i1 %and, ptr %and_test, align 1
  %ata120 = load i1, ptr %ata, align 1
  %btb121 = load i1, ptr %btb, align 1
  %or = or i1 %ata120, %btb121
  store i1 %or, ptr %or_test, align 1
  %ata122 = load i1, ptr %ata, align 1
  %btb123 = load i1, ptr %btb, align 1
  %xor = xor i1 %ata122, %btb123
  store i1 %xor, ptr %xor_test, align 1
  %ata124 = load i1, ptr %ata, align 1
  %not = xor i1 %ata124, true
  store i1 %not, ptr %not_test, align 1
  %sum125 = load i32, ptr %sum, align 4
  switch i32 %sum125, label %switch.case127 [
    i32 1, label %switch.case
    i32 5, label %switch.case126
  ]

switch.end:                                       ; preds = %switch.case127, %switch.case126, %switch.case
  store i2 -1, ptr %both_tester, align 1
  %both_tester130 = load i2, ptr %both_tester, align 1
  %7 = and i2 %both_tester130, -2
  %8 = icmp ne i2 %7, 0
  br i1 %8, label %qif.body, label %qelif.check

switch.case:                                      ; preds = %for.end
  br label %switch.end

switch.case126:                                   ; preds = %for.end
  %sum128 = load i32, ptr %sum, align 4
  store i32 2, ptr %sum, align 4
  br label %switch.end

switch.case127:                                   ; preds = %for.end
  %sum129 = load i32, ptr %sum, align 4
  store i32 0, ptr %sum, align 4
  br label %switch.end

qif.end:                                          ; preds = %qelse.body, %qelif.check, %qif.body
  %x135 = load i32, ptr %x, align 4
  store i32 0, ptr %x, align 4
  %both_tester136 = load i2, ptr %both_tester, align 1
  br label %qsw.check_true

qif.body:                                         ; preds = %switch.end
  %sum131 = load i32, ptr %sum, align 4
  %add132 = add i32 %sum131, 123
  store i32 %add132, ptr %sum, align 4
  br label %qif.end

qelif.check:                                      ; preds = %switch.end
  %9 = and i2 %both_tester130, 1
  %10 = icmp ne i2 %9, 0
  br i1 %10, label %qelse.body, label %qif.end

qelse.body:                                       ; preds = %qelif.check
  %sum133 = load i32, ptr %sum, align 4
  %add134 = add i32 %sum133, 321
  store i32 %add134, ptr %sum, align 4
  br label %qif.end

qsw.check_true:                                   ; preds = %qif.end
  %has_true = and i2 %both_tester136, -2
  %is_true = icmp ne i2 %has_true, 0
  br i1 %is_true, label %qsw.check_false, label %qsw.check_false

qsw.check_false:                                  ; preds = %qsw.check_true, %qsw.check_true
  %has_false = and i2 %both_tester136, 1
  %is_false = icmp ne i2 %has_false, 0
  %is_both = and i1 %is_true, %is_false
  %not_false = xor i1 %is_false, true
  %is_qtrue_only = and i1 %is_true, %not_false
  %not_true = xor i1 %is_true, true
  %is_qfalse_only = and i1 %not_true, %is_false
  %is_none = and i1 %not_true, %not_false
  br i1 %is_both, label %qsw.case_b, label %qsw.check_qtrue

qswitch.end:                                      ; preds = %qsw.case_b, %qsw.case_t, %qsw.check_none_final, %qsw.check_none_final, %qsw.check_qfalse
  store i2 -1, ptr %q1, align 1
  store i2 0, ptr %q2, align 1
  store i2 0, ptr %q3, align 1
  store i2 -1, ptr %q4, align 1
  store i2 -1, ptr %q5, align 1
  %11 = call i1 @qc_string_eq(ptr @.str.42, ptr @.str.43)
  %12 = zext i1 %11 to i8
  %13 = mul i8 %12, 3
  %14 = trunc i8 %13 to i2
  store i2 %14, ptr %q6, align 1
  %15 = call i1 @qc_string_eq(ptr @.str.44, ptr @.str.45)
  %16 = xor i1 %15, true
  %17 = zext i1 %16 to i8
  %18 = mul i8 %17, 3
  %19 = trunc i8 %18 to i2
  store i2 %19, ptr %q7, align 1
  %q1139 = load i2, ptr %q1, align 1
  %qout_qb_str = call ptr @qc_to_string_qbool(i2 %q1139)
  call void @qc_print_string(ptr %qout_qb_str)
  %q2140 = load i2, ptr %q2, align 1
  %qout_qb_str141 = call ptr @qc_to_string_qbool(i2 %q2140)
  call void @qc_print_string(ptr %qout_qb_str141)
  %q3142 = load i2, ptr %q3, align 1
  %qout_qb_str143 = call ptr @qc_to_string_qbool(i2 %q3142)
  call void @qc_print_string(ptr %qout_qb_str143)
  %q4144 = load i2, ptr %q4, align 1
  %qout_qb_str145 = call ptr @qc_to_string_qbool(i2 %q4144)
  call void @qc_print_string(ptr %qout_qb_str145)
  %q5146 = load i2, ptr %q5, align 1
  %qout_qb_str147 = call ptr @qc_to_string_qbool(i2 %q5146)
  call void @qc_print_string(ptr %qout_qb_str147)
  %q6148 = load i2, ptr %q6, align 1
  %qout_qb_str149 = call ptr @qc_to_string_qbool(i2 %q6148)
  call void @qc_print_string(ptr %qout_qb_str149)
  %q7150 = load i2, ptr %q7, align 1
  %qout_qb_str151 = call ptr @qc_to_string_qbool(i2 %q7150)
  call void @qc_print_string(ptr %qout_qb_str151)
  %builtin_call = call i32 @qc_time()
  store i32 %builtin_call, ptr %t, align 4
  %t152 = load i32, ptr %t, align 4
  call void @qc_seed(i32 %t152)
  %builtin_call153 = call float @qc_random_float()
  store float %builtin_call153, ptr %r, align 4
  %builtin_call154 = call i32 @qc_random_int(i32 10)
  store i32 %builtin_call154, ptr %ri, align 4
  %builtin_call155 = call i32 @qc_random_range(i32 5, i32 15)
  store i32 %builtin_call155, ptr %rr, align 4
  store ptr @.str.46, ptr %s, align 8
  %s156 = load ptr, ptr %s, align 8
  %builtin_call157 = call i32 @qc_len(ptr %s156)
  store i32 %builtin_call157, ptr %l, align 4
  %s158 = load ptr, ptr %s, align 8
  %builtin_call159 = call ptr @qc_to_upper(ptr %s158)
  store ptr %builtin_call159, ptr %upper, align 8
  %s160 = load ptr, ptr %s, align 8
  %builtin_call161 = call ptr @qc_to_lower(ptr %s160)
  store ptr %builtin_call161, ptr %lower, align 8
  %s162 = load ptr, ptr %s, align 8
  %builtin_call163 = call i32 @qc_contains(ptr %s162, ptr @.str.47)
  %trunc = trunc i32 %builtin_call163 to i1
  store i1 %trunc, ptr %c, align 1
  %s164 = load ptr, ptr %s, align 8
  %builtin_call165 = call i32 @qc_startswith(ptr %s164, ptr @.str.48)
  %trunc166 = trunc i32 %builtin_call165 to i1
  store i1 %trunc166, ptr %sw, align 1
  %s167 = load ptr, ptr %s, align 8
  %builtin_call168 = call i32 @qc_endswith(ptr %s167, ptr @.str.49)
  %trunc169 = trunc i32 %builtin_call168 to i1
  store i1 %trunc169, ptr %ew, align 1
  %s171 = load ptr, ptr %s, align 8
  %builtin_call172 = call ptr @qc_substring(ptr %s171, i32 1, i32 3)
  store ptr %builtin_call172, ptr %sub170, align 8
  %builtin_call173 = call ptr @qc_trim(ptr @.str.50)
  store ptr %builtin_call173, ptr %trimmed, align 8
  %s174 = load ptr, ptr %s, align 8
  %builtin_call175 = call ptr @qc_replace(ptr %s174, ptr @.str.51, ptr @.str.52)
  store ptr %builtin_call175, ptr %replaced, align 8
  %i176 = load i32, ptr %i, align 4
  %to_int = call i32 @qc_to_int_from_string(ptr @.str.53)
  store i32 %to_int, ptr %i, align 4
  %f177 = load float, ptr %f, align 4
  %to_float = call float @qc_to_float_from_string(ptr @.str.54)
  store float %to_float, ptr %f, align 4
  %to_str = call ptr @qc_to_string_int(i32 123)
  store ptr %to_str, ptr %si, align 8
  %to_str178 = call ptr @qc_to_string_float(float 0x40091EB860000000)
  store ptr %to_str178, ptr %sf, align 8
  call void @qc_print(ptr @.str.55)
  call void @qc_println(ptr @.str.56)
  call void @qc_println(ptr @.str.57)
  %jagged_arr = call ptr @qc_create_jagged_array(i32 2, i32 0, i32 1)
  %leaf_row = call ptr @qc_create_leaf_row(i32 3, i32 0)
  store i32 1, ptr %temp_elem, align 4
  call void @qc_set_leaf_element(ptr %leaf_row, i32 0, ptr %temp_elem, i32 0)
  store i32 2, ptr %temp_elem179, align 4
  call void @qc_set_leaf_element(ptr %leaf_row, i32 1, ptr %temp_elem179, i32 0)
  store i32 3, ptr %temp_elem180, align 4
  call void @qc_set_leaf_element(ptr %leaf_row, i32 2, ptr %temp_elem180, i32 0)
  call void @qc_set_jagged_element(ptr %jagged_arr, i32 0, ptr %leaf_row, i32 3)
  %leaf_row181 = call ptr @qc_create_leaf_row(i32 2, i32 0)
  store i32 3, ptr %temp_elem182, align 4
  call void @qc_set_leaf_element(ptr %leaf_row181, i32 0, ptr %temp_elem182, i32 0)
  store i32 4, ptr %temp_elem183, align 4
  call void @qc_set_leaf_element(ptr %leaf_row181, i32 1, ptr %temp_elem183, i32 0)
  call void @qc_set_jagged_element(ptr %jagged_arr, i32 1, ptr %leaf_row181, i32 2)
  store ptr %jagged_arr, ptr %grid, align 8
  call void @qc_println(ptr @.str.58)
  %jagged_ptr = load ptr, ptr %grid, align 8
  %20 = getelementptr inbounds [2 x i32], ptr %indices_arr, i32 0, i32 0
  store i32 0, ptr %20, align 4
  %21 = getelementptr inbounds [2 x i32], ptr %indices_arr, i32 0, i32 1
  store i32 1, ptr %21, align 4
  %22 = getelementptr inbounds [2 x i32], ptr %indices_arr, i32 0, i32 0
  %jagged_elem_ptr = call ptr @qc_jagged_array_get(ptr %jagged_ptr, ptr %22, i32 2)
  %jagged_elem = load i32, ptr %jagged_elem_ptr, align 4
  store i32 %jagged_elem, ptr %val, align 4
  call void @qc_println(ptr @.str.59)
  %val184 = load i32, ptr %val, align 4
  call void @qc_print_int(i32 %val184)
  %jagged_ptr185 = load ptr, ptr %grid, align 8
  call void @qc_print_jagged_array_recursive(ptr %jagged_ptr185)
  call void @qc_println(ptr @.str.60)
  %heap_arr186 = call ptr @malloc(i64 16)
  store ptr %heap_arr186, ptr %regular187, align 8
  %heap_ptr188 = load ptr, ptr %regular187, align 8
  %23 = getelementptr inbounds [2 x [2 x i32]], ptr %heap_ptr188, i32 0, i32 0, i32 0
  store i32 1, ptr %23, align 4
  %heap_ptr189 = load ptr, ptr %regular187, align 8
  %24 = getelementptr inbounds [2 x [2 x i32]], ptr %heap_ptr189, i32 0, i32 0, i32 1
  store i32 2, ptr %24, align 4
  %heap_ptr190 = load ptr, ptr %regular187, align 8
  %25 = getelementptr inbounds [2 x [2 x i32]], ptr %heap_ptr190, i32 0, i32 1, i32 0
  store i32 3, ptr %25, align 4
  %heap_ptr191 = load ptr, ptr %regular187, align 8
  %26 = getelementptr inbounds [2 x [2 x i32]], ptr %heap_ptr191, i32 0, i32 1, i32 1
  store i32 4, ptr %26, align 4
  %jagged_arr192 = call ptr @qc_create_jagged_array(i32 2, i32 0, i32 1)
  %leaf_row193 = call ptr @qc_create_leaf_row(i32 3, i32 0)
  store i32 1, ptr %temp_elem194, align 4
  call void @qc_set_leaf_element(ptr %leaf_row193, i32 0, ptr %temp_elem194, i32 0)
  store i32 2, ptr %temp_elem195, align 4
  call void @qc_set_leaf_element(ptr %leaf_row193, i32 1, ptr %temp_elem195, i32 0)
  store i32 3, ptr %temp_elem196, align 4
  call void @qc_set_leaf_element(ptr %leaf_row193, i32 2, ptr %temp_elem196, i32 0)
  call void @qc_set_jagged_element(ptr %jagged_arr192, i32 0, ptr %leaf_row193, i32 3)
  %leaf_row197 = call ptr @qc_create_leaf_row(i32 2, i32 0)
  store i32 4, ptr %temp_elem198, align 4
  call void @qc_set_leaf_element(ptr %leaf_row197, i32 0, ptr %temp_elem198, i32 0)
  store i32 5, ptr %temp_elem199, align 4
  call void @qc_set_leaf_element(ptr %leaf_row197, i32 1, ptr %temp_elem199, i32 0)
  call void @qc_set_jagged_element(ptr %jagged_arr192, i32 1, ptr %leaf_row197, i32 2)
  store ptr %jagged_arr192, ptr %jagged, align 8
  %jagged_arr200 = call ptr @qc_create_jagged_array(i32 2, i32 0, i32 2)
  %jagged_arr201 = call ptr @qc_create_jagged_array(i32 2, i32 0, i32 1)
  %leaf_row202 = call ptr @qc_create_leaf_row(i32 2, i32 0)
  store i32 1, ptr %temp_elem203, align 4
  call void @qc_set_leaf_element(ptr %leaf_row202, i32 0, ptr %temp_elem203, i32 0)
  store i32 2, ptr %temp_elem204, align 4
  call void @qc_set_leaf_element(ptr %leaf_row202, i32 1, ptr %temp_elem204, i32 0)
  call void @qc_set_jagged_element(ptr %jagged_arr201, i32 0, ptr %leaf_row202, i32 2)
  %leaf_row205 = call ptr @qc_create_leaf_row(i32 1, i32 0)
  store i32 3, ptr %temp_elem206, align 4
  call void @qc_set_leaf_element(ptr %leaf_row205, i32 0, ptr %temp_elem206, i32 0)
  call void @qc_set_jagged_element(ptr %jagged_arr201, i32 1, ptr %leaf_row205, i32 1)
  call void @qc_set_jagged_element(ptr %jagged_arr200, i32 0, ptr %jagged_arr201, i32 2)
  %jagged_arr207 = call ptr @qc_create_jagged_array(i32 1, i32 0, i32 1)
  %leaf_row208 = call ptr @qc_create_leaf_row(i32 3, i32 0)
  store i32 4, ptr %temp_elem209, align 4
  call void @qc_set_leaf_element(ptr %leaf_row208, i32 0, ptr %temp_elem209, i32 0)
  store i32 5, ptr %temp_elem210, align 4
  call void @qc_set_leaf_element(ptr %leaf_row208, i32 1, ptr %temp_elem210, i32 0)
  store i32 6, ptr %temp_elem211, align 4
  call void @qc_set_leaf_element(ptr %leaf_row208, i32 2, ptr %temp_elem211, i32 0)
  call void @qc_set_jagged_element(ptr %jagged_arr207, i32 0, ptr %leaf_row208, i32 3)
  call void @qc_set_jagged_element(ptr %jagged_arr200, i32 1, ptr %jagged_arr207, i32 1)
  store ptr %jagged_arr200, ptr %deep, align 8
  call void @qc_print_string(ptr @.str.61)
  %regular212 = load ptr, ptr %regular187, align 8
  call void @qc_print_string(ptr %regular212)
  call void @qc_print_char(i8 10)
  call void @qc_print_string(ptr @.str.62)
  %jagged_ptr213 = load ptr, ptr %jagged, align 8
  call void @qc_print_jagged_array_recursive(ptr %jagged_ptr213)
  call void @qc_print_char(i8 10)
  call void @qc_print_string(ptr @.str.63)
  %jagged_ptr214 = load ptr, ptr %deep, align 8
  call void @qc_print_jagged_array_recursive(ptr %jagged_ptr214)
  call void @qc_print_char(i8 10)
  %jagged_ptr215 = load ptr, ptr %jagged, align 8
  %27 = getelementptr inbounds [2 x i32], ptr %indices_arr216, i32 0, i32 0
  store i32 0, ptr %27, align 4
  %28 = getelementptr inbounds [2 x i32], ptr %indices_arr216, i32 0, i32 1
  store i32 2, ptr %28, align 4
  %29 = getelementptr inbounds [2 x i32], ptr %indices_arr216, i32 0, i32 0
  %jagged_elem_ptr217 = call ptr @qc_jagged_array_get(ptr %jagged_ptr215, ptr %29, i32 2)
  %jagged_elem218 = load i32, ptr %jagged_elem_ptr217, align 4
  store i32 %jagged_elem218, ptr %val1, align 4
  %jagged_ptr219 = load ptr, ptr %jagged, align 8
  %30 = getelementptr inbounds [2 x i32], ptr %indices_arr220, i32 0, i32 0
  store i32 1, ptr %30, align 4
  %31 = getelementptr inbounds [2 x i32], ptr %indices_arr220, i32 0, i32 1
  store i32 1, ptr %31, align 4
  %32 = getelementptr inbounds [2 x i32], ptr %indices_arr220, i32 0, i32 0
  %jagged_elem_ptr221 = call ptr @qc_jagged_array_get(ptr %jagged_ptr219, ptr %32, i32 2)
  %jagged_elem222 = load i32, ptr %jagged_elem_ptr221, align 4
  store i32 %jagged_elem222, ptr %val2, align 4
  %calltmp223 = call ptr @make_array()
  store ptr %calltmp223, ptr %array1, align 8
  %array1224 = load ptr, ptr %array1, align 8
  %calltmp225 = call i32 @print_array(ptr %array1224, i32 3)
  %calltmp226 = call { ptr, ptr } @get_both()
  %33 = extractvalue { ptr, ptr } %calltmp226, 0
  store ptr %33, ptr %brray1, align 8
  %34 = extractvalue { ptr, ptr } %calltmp226, 1
  store ptr %34, ptr %strnthing, align 8
  %val1227 = load i32, ptr %val1, align 4
  call void @qc_print_int(i32 %val1227)
  call void @qc_print_string(ptr @.str.64)
  %val2228 = load i32, ptr %val2, align 4
  call void @qc_print_int(i32 %val2228)
  call void @qc_print_char(i8 10)
  %list_ptr = call ptr @qc_create_list(i32 0)
  store i32 1, ptr %temp_elem229, align 4
  call void @qc_list_push(ptr %list_ptr, ptr %temp_elem229, i32 0)
  store i32 2, ptr %temp_elem230, align 4
  call void @qc_list_push(ptr %list_ptr, ptr %temp_elem230, i32 0)
  store i32 3, ptr %temp_elem231, align 4
  call void @qc_list_push(ptr %list_ptr, ptr %temp_elem231, i32 0)
  store i32 4, ptr %temp_elem232, align 4
  call void @qc_list_push(ptr %list_ptr, ptr %temp_elem232, i32 0)
  store ptr %list_ptr, ptr %aList, align 8
  %list_ptr233 = load ptr, ptr %aList, align 8
  %list_elem_ptr = call ptr @qc_list_get(ptr %list_ptr233, i32 0)
  %list_elem = load i32, ptr %list_elem_ptr, align 4
  call void @qc_print_int(i32 %list_elem)
  %list_ptr234 = load ptr, ptr %aList, align 8
  %list_elem_ptr235 = call ptr @qc_list_get(ptr %list_ptr234, i32 1)
  %list_elem236 = load i32, ptr %list_elem_ptr235, align 4
  call void @qc_print_int(i32 %list_elem236)
  %heap_arr237 = call ptr @malloc(i64 20)
  store ptr %heap_arr237, ptr %arr, align 8
  %heap_ptr238 = load ptr, ptr %arr, align 8
  %35 = getelementptr inbounds [5 x i32], ptr %heap_ptr238, i32 0, i32 0
  store i32 1, ptr %35, align 4
  %heap_ptr239 = load ptr, ptr %arr, align 8
  %36 = getelementptr inbounds [5 x i32], ptr %heap_ptr239, i32 0, i32 1
  store i32 2, ptr %36, align 4
  %heap_ptr240 = load ptr, ptr %arr, align 8
  %37 = getelementptr inbounds [5 x i32], ptr %heap_ptr240, i32 0, i32 2
  store i32 3, ptr %37, align 4
  %heap_ptr241 = load ptr, ptr %arr, align 8
  %38 = getelementptr inbounds [5 x i32], ptr %heap_ptr241, i32 0, i32 3
  store i32 4, ptr %38, align 4
  %heap_ptr242 = load ptr, ptr %arr, align 8
  %39 = getelementptr inbounds [5 x i32], ptr %heap_ptr242, i32 0, i32 4
  store i32 5, ptr %39, align 4
  call void @qc_println(ptr @.str.65)
  store i32 5, ptr %arr_len, align 4
  %arr_len243 = load i32, ptr %arr_len, align 4
  call void @qc_print_int(i32 %arr_len243)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.66)
  %arr244 = load ptr, ptr %arr, align 8
  store i32 0, ptr %__foreach_i_vz, align 4
  br label %foreach.cond

qsw.case_t:                                       ; preds = %qsw.check_qtrue
  %x137 = load i32, ptr %x, align 4
  store i32 2, ptr %x, align 4
  br label %qswitch.end

qsw.case_b:                                       ; preds = %qsw.check_false
  %x138 = load i32, ptr %x, align 4
  store i32 1, ptr %x, align 4
  br label %qswitch.end

qsw.check_qtrue:                                  ; preds = %qsw.check_false
  br i1 %is_qtrue_only, label %qsw.case_t, label %qsw.check_qfalse

qsw.check_qfalse:                                 ; preds = %qsw.check_qtrue
  br i1 %is_qfalse_only, label %qswitch.end, label %qsw.check_none_final

qsw.check_none_final:                             ; preds = %qsw.check_qfalse
  br i1 %is_none, label %qswitch.end, label %qswitch.end

foreach.cond:                                     ; preds = %foreach.inc, %qswitch.end
  %__foreach_i_vz245 = load i32, ptr %__foreach_i_vz, align 4
  %foreach_cmp = icmp slt i32 %__foreach_i_vz245, 5
  br i1 %foreach_cmp, label %foreach.body, label %foreach.end

foreach.body:                                     ; preds = %foreach.cond
  %heap_ptr246 = load ptr, ptr %arr, align 8
  %heap_elem_ptr = getelementptr i32, ptr %heap_ptr246, i32 %__foreach_i_vz245
  %elem = load i32, ptr %heap_elem_ptr, align 4
  store i32 %elem, ptr %vz, align 4
  %vz247 = load i32, ptr %vz, align 4
  call void @qc_print_int(i32 %vz247)
  call void @qc_print_string(ptr @.str.67)
  br label %foreach.inc

foreach.inc:                                      ; preds = %foreach.body
  %__foreach_i_vz248 = load i32, ptr %__foreach_i_vz, align 4
  %i_inc = add i32 %__foreach_i_vz248, 1
  store i32 %i_inc, ptr %__foreach_i_vz, align 4
  br label %foreach.cond

foreach.end:                                      ; preds = %foreach.cond
  call void @qc_println(ptr @.str.68)
  %list_ptr249 = call ptr @qc_create_list(i32 0)
  store i32 10, ptr %temp_elem250, align 4
  call void @qc_list_push(ptr %list_ptr249, ptr %temp_elem250, i32 0)
  store i32 20, ptr %temp_elem251, align 4
  call void @qc_list_push(ptr %list_ptr249, ptr %temp_elem251, i32 0)
  store i32 30, ptr %temp_elem252, align 4
  call void @qc_list_push(ptr %list_ptr249, ptr %temp_elem252, i32 0)
  store ptr %list_ptr249, ptr %myList, align 8
  call void @qc_println(ptr @.str.69)
  %myList253 = load ptr, ptr %myList, align 8
  %list_len254 = call i32 @qc_list_length(ptr %myList253)
  store i32 %list_len254, ptr %list_len, align 4
  %list_len255 = load i32, ptr %list_len, align 4
  call void @qc_print_int(i32 %list_len255)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.70)
  %myList256 = load ptr, ptr %myList, align 8
  store i32 40, ptr %push_arg, align 4
  call void @qc_list_push(ptr %myList256, ptr %push_arg, i32 0)
  %myList257 = load ptr, ptr %myList, align 8
  store i32 50, ptr %push_arg258, align 4
  call void @qc_list_push(ptr %myList257, ptr %push_arg258, i32 0)
  %myList259 = load ptr, ptr %myList, align 8
  %list_len260 = call i32 @qc_list_length(ptr %myList259)
  call void @qc_print_int(i32 %list_len260)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.71)
  %myList261 = load ptr, ptr %myList, align 8
  %coll_len = call i32 @qc_list_length(ptr %myList261)
  store i32 0, ptr %__foreach_i_y, align 4
  br label %foreach.cond263

foreach.cond263:                                  ; preds = %foreach.inc265, %foreach.end
  %__foreach_i_y267 = load i32, ptr %__foreach_i_y, align 4
  %foreach_cmp268 = icmp slt i32 %__foreach_i_y267, %coll_len
  br i1 %foreach_cmp268, label %foreach.body264, label %foreach.end266

foreach.body264:                                  ; preds = %foreach.cond263
  %elem_ptr = call ptr @qc_list_get(ptr %myList261, i32 %__foreach_i_y267)
  %elem269 = load i32, ptr %elem_ptr, align 4
  store i32 %elem269, ptr %y262, align 4
  %y270 = load i32, ptr %y262, align 4
  call void @qc_print_int(i32 %y270)
  call void @qc_print_string(ptr @.str.72)
  br label %foreach.inc265

foreach.inc265:                                   ; preds = %foreach.body264
  %__foreach_i_y271 = load i32, ptr %__foreach_i_y, align 4
  %i_inc272 = add i32 %__foreach_i_y271, 1
  store i32 %i_inc272, ptr %__foreach_i_y, align 4
  br label %foreach.cond263

foreach.end266:                                   ; preds = %foreach.cond263
  call void @qc_println(ptr @.str.73)
  call void @qc_println(ptr @.str.74)
  %myList273 = load ptr, ptr %myList, align 8
  %list_pop = call ptr @qc_list_pop(ptr %myList273)
  %myList274 = load ptr, ptr %myList, align 8
  %list_len275 = call i32 @qc_list_length(ptr %myList274)
  call void @qc_print_int(i32 %list_len275)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.75)
  %list_ptr276 = load ptr, ptr %myList, align 8
  %list_elem_ptr277 = call ptr @qc_list_get(ptr %list_ptr276, i32 0)
  %list_elem278 = load i32, ptr %list_elem_ptr277, align 4
  call void @qc_print_int(i32 %list_elem278)
  call void @qc_print_string(ptr @.str.76)
  %list_ptr279 = load ptr, ptr %myList, align 8
  %list_elem_ptr280 = call ptr @qc_list_get(ptr %list_ptr279, i32 1)
  %list_elem281 = load i32, ptr %list_elem_ptr280, align 4
  call void @qc_print_int(i32 %list_elem281)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.77)
  %list_ptr282 = call ptr @qc_create_list(i32 0)
  %calltmp283 = call ptr @make_list()
  store ptr %calltmp283, ptr %listy, align 8
  call void @qc_println(ptr @.str.78)
  %listy284 = load ptr, ptr %listy, align 8
  %list_len285 = call i32 @qc_list_length(ptr %listy284)
  call void @qc_print_int(i32 %list_len285)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.79)
  %listy286 = load ptr, ptr %listy, align 8
  %coll_len287 = call i32 @qc_list_length(ptr %listy286)
  store i32 0, ptr %__foreach_i_xccc, align 4
  br label %foreach.cond288

foreach.cond288:                                  ; preds = %foreach.inc290, %foreach.end266
  %__foreach_i_xccc292 = load i32, ptr %__foreach_i_xccc, align 4
  %foreach_cmp293 = icmp slt i32 %__foreach_i_xccc292, %coll_len287
  br i1 %foreach_cmp293, label %foreach.body289, label %foreach.end291

foreach.body289:                                  ; preds = %foreach.cond288
  %elem_ptr294 = call ptr @qc_list_get(ptr %listy286, i32 %__foreach_i_xccc292)
  %elem295 = load i32, ptr %elem_ptr294, align 4
  store i32 %elem295, ptr %xccc, align 4
  %xccc296 = load i32, ptr %xccc, align 4
  call void @qc_print_int(i32 %xccc296)
  call void @qc_print_string(ptr @.str.80)
  br label %foreach.inc290

foreach.inc290:                                   ; preds = %foreach.body289
  %__foreach_i_xccc297 = load i32, ptr %__foreach_i_xccc, align 4
  %i_inc298 = add i32 %__foreach_i_xccc297, 1
  store i32 %i_inc298, ptr %__foreach_i_xccc, align 4
  br label %foreach.cond288

foreach.end291:                                   ; preds = %foreach.cond288
  call void @qc_println(ptr @.str.81)
  call void @qc_println(ptr @.str.82)
  %list_ptr299 = call ptr @qc_create_list(i32 0)
  %listy300 = load ptr, ptr %listy, align 8
  %calltmp301 = call ptr @double_list(ptr %listy300)
  store ptr %calltmp301, ptr %doubled, align 8
  call void @qc_println(ptr @.str.83)
  %doubled302 = load ptr, ptr %doubled, align 8
  %coll_len303 = call i32 @qc_list_length(ptr %doubled302)
  store i32 0, ptr %__foreach_i_xccc304, align 4
  br label %foreach.cond306

foreach.cond306:                                  ; preds = %foreach.inc308, %foreach.end291
  %__foreach_i_xccc310 = load i32, ptr %__foreach_i_xccc304, align 4
  %foreach_cmp311 = icmp slt i32 %__foreach_i_xccc310, %coll_len303
  br i1 %foreach_cmp311, label %foreach.body307, label %foreach.end309

foreach.body307:                                  ; preds = %foreach.cond306
  %elem_ptr312 = call ptr @qc_list_get(ptr %doubled302, i32 %__foreach_i_xccc310)
  %elem313 = load i32, ptr %elem_ptr312, align 4
  store i32 %elem313, ptr %xccc305, align 4
  %xccc314 = load i32, ptr %xccc305, align 4
  call void @qc_print_int(i32 %xccc314)
  call void @qc_print_string(ptr @.str.84)
  br label %foreach.inc308

foreach.inc308:                                   ; preds = %foreach.body307
  %__foreach_i_xccc315 = load i32, ptr %__foreach_i_xccc304, align 4
  %i_inc316 = add i32 %__foreach_i_xccc315, 1
  store i32 %i_inc316, ptr %__foreach_i_xccc304, align 4
  br label %foreach.cond306

foreach.end309:                                   ; preds = %foreach.cond306
  call void @qc_println(ptr @.str.85)
  call void @qc_println(ptr @.str.86)
  %calltmp317 = call { ptr, i32 } @get_list_and_count()
  %40 = extractvalue { ptr, i32 } %calltmp317, 0
  store ptr %40, ptr %datacc, align 8
  %41 = extractvalue { ptr, i32 } %calltmp317, 1
  store i32 %41, ptr %countcc, align 4
  call void @qc_println(ptr @.str.87)
  %countcc318 = load i32, ptr %countcc, align 4
  call void @qc_print_int(i32 %countcc318)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.88)
  %datacc319 = load ptr, ptr %datacc, align 8
  %coll_len320 = call i32 @qc_list_length(ptr %datacc319)
  store i32 0, ptr %__foreach_i_xyzd, align 4
  br label %foreach.cond321

foreach.cond321:                                  ; preds = %foreach.inc323, %foreach.end309
  %__foreach_i_xyzd325 = load i32, ptr %__foreach_i_xyzd, align 4
  %foreach_cmp326 = icmp slt i32 %__foreach_i_xyzd325, %coll_len320
  br i1 %foreach_cmp326, label %foreach.body322, label %foreach.end324

foreach.body322:                                  ; preds = %foreach.cond321
  %elem_ptr327 = call ptr @qc_list_get(ptr %datacc319, i32 %__foreach_i_xyzd325)
  %elem328 = load i32, ptr %elem_ptr327, align 4
  store i32 %elem328, ptr %xyzd, align 4
  %xyzd329 = load i32, ptr %xyzd, align 4
  call void @qc_print_int(i32 %xyzd329)
  call void @qc_print_string(ptr @.str.89)
  br label %foreach.inc323

foreach.inc323:                                   ; preds = %foreach.body322
  %__foreach_i_xyzd330 = load i32, ptr %__foreach_i_xyzd, align 4
  %i_inc331 = add i32 %__foreach_i_xyzd330, 1
  store i32 %i_inc331, ptr %__foreach_i_xyzd, align 4
  br label %foreach.cond321

foreach.end324:                                   ; preds = %foreach.cond321
  call void @qc_println(ptr @.str.90)
  call void @qc_println(ptr @.str.91)
  %map_ptr = call ptr @qc_create_map(i32 6, i32 0)
  store i32 25, ptr %temp_val, align 4
  call void @qc_map_set(ptr %map_ptr, ptr @.str.92, ptr %temp_val)
  store i32 30, ptr %temp_val332, align 4
  call void @qc_map_set(ptr %map_ptr, ptr @.str.93, ptr %temp_val332)
  store i32 35, ptr %temp_val333, align 4
  call void @qc_map_set(ptr %map_ptr, ptr @.str.94, ptr %temp_val333)
  store ptr %map_ptr, ptr %ages, align 8
  %map_ptr334 = load ptr, ptr %ages, align 8
  call void @qc_print_map(ptr %map_ptr334)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.95)
  %map_ptr335 = load ptr, ptr %ages, align 8
  %map_val_ptr = call ptr @qc_map_get(ptr %map_ptr335, ptr @.str.96)
  %map_val = load i32, ptr %map_val_ptr, align 4
  call void @qc_print_int(i32 %map_val)
  call void @qc_print_char(i8 10)
  %map_ptr336 = load ptr, ptr %ages, align 8
  %map_val_ptr337 = call ptr @qc_map_get(ptr %map_ptr336, ptr @.str.97)
  %map_val338 = load i32, ptr %map_val_ptr337, align 4
  call void @qc_print_int(i32 %map_val338)
  call void @qc_print_char(i8 10)
  %map_ptr339 = load ptr, ptr %ages, align 8
  %map_val_ptr340 = call ptr @qc_map_get(ptr %map_ptr339, ptr @.str.98)
  %map_val341 = load i32, ptr %map_val_ptr340, align 4
  call void @qc_print_int(i32 %map_val341)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.99)
  %map_ptr342 = load ptr, ptr %ages, align 8
  store i32 40, ptr %map_val343, align 4
  call void @qc_map_set(ptr %map_ptr342, ptr @.str.100, ptr %map_val343)
  %map_ptr344 = load ptr, ptr %ages, align 8
  call void @qc_print_map(ptr %map_ptr344)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.101)
  %map_ptr345 = load ptr, ptr %ages, align 8
  store i32 26, ptr %map_val346, align 4
  call void @qc_map_set(ptr %map_ptr345, ptr @.str.102, ptr %map_val346)
  %map_ptr347 = load ptr, ptr %ages, align 8
  call void @qc_print_map(ptr %map_ptr347)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.103)
  %ages348 = load ptr, ptr %ages, align 8
  %map_size = call i32 @qc_map_size(ptr %ages348)
  call void @qc_print_int(i32 %map_size)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.104)
  %ages349 = load ptr, ptr %ages, align 8
  %map_has = call i1 @qc_map_has(ptr %ages349, ptr @.str.105)
  %qout_bool_str = call ptr @qc_to_string_bool(i1 %map_has)
  call void @qc_print_string(ptr %qout_bool_str)
  call void @qc_print_char(i8 10)
  %ages350 = load ptr, ptr %ages, align 8
  %map_has351 = call i1 @qc_map_has(ptr %ages350, ptr @.str.106)
  %qout_bool_str352 = call ptr @qc_to_string_bool(i1 %map_has351)
  call void @qc_print_string(ptr %qout_bool_str352)
  call void @qc_print_char(i8 10)
  %ages353 = load ptr, ptr %ages, align 8
  %map_has354 = call i1 @qc_map_has(ptr %ages353, ptr @.str.107)
  %qout_bool_str355 = call ptr @qc_to_string_bool(i1 %map_has354)
  call void @qc_print_string(ptr %qout_bool_str355)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.108)
  %ages356 = load ptr, ptr %ages, align 8
  call void @qc_map_remove(ptr %ages356, ptr @.str.109)
  %map_ptr357 = load ptr, ptr %ages, align 8
  call void @qc_print_map(ptr %map_ptr357)
  call void @qc_print_char(i8 10)
  %ages358 = load ptr, ptr %ages, align 8
  %map_has359 = call i1 @qc_map_has(ptr %ages358, ptr @.str.110)
  %qout_bool_str360 = call ptr @qc_to_string_bool(i1 %map_has359)
  call void @qc_print_string(ptr %qout_bool_str360)
  call void @qc_print_char(i8 10)
  %ages361 = load ptr, ptr %ages, align 8
  %map_size362 = call i32 @qc_map_size(ptr %ages361)
  call void @qc_print_int(i32 %map_size362)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.111)
  %ages363 = load ptr, ptr %ages, align 8
  %map_keys = call ptr @qc_map_keys(ptr %ages363)
  %coll_len364 = call i32 @qc_list_length(ptr %map_keys)
  store i32 0, ptr %__foreach_i_key, align 4
  br label %foreach.cond365

foreach.cond365:                                  ; preds = %foreach.inc367, %foreach.end324
  %__foreach_i_key369 = load i32, ptr %__foreach_i_key, align 4
  %foreach_cmp370 = icmp slt i32 %__foreach_i_key369, %coll_len364
  br i1 %foreach_cmp370, label %foreach.body366, label %foreach.end368

foreach.body366:                                  ; preds = %foreach.cond365
  %elem_ptr371 = call ptr @qc_list_get(ptr %map_keys, i32 %__foreach_i_key369)
  store ptr %elem_ptr371, ptr %key, align 8
  %key372 = load ptr, ptr %key, align 8
  call void @qc_print_string(ptr %key372)
  call void @qc_print_string(ptr @.str.112)
  %map_ptr373 = load ptr, ptr %ages, align 8
  %key374 = load ptr, ptr %key, align 8
  %map_val_ptr375 = call ptr @qc_map_get(ptr %map_ptr373, ptr %key374)
  %map_val376 = load i32, ptr %map_val_ptr375, align 4
  call void @qc_print_int(i32 %map_val376)
  call void @qc_print_char(i8 10)
  br label %foreach.inc367

foreach.inc367:                                   ; preds = %foreach.body366
  %__foreach_i_key377 = load i32, ptr %__foreach_i_key, align 4
  %i_inc378 = add i32 %__foreach_i_key377, 1
  store i32 %i_inc378, ptr %__foreach_i_key, align 4
  br label %foreach.cond365

foreach.end368:                                   ; preds = %foreach.cond365
  call void @qc_println(ptr @.str.113)
  %map_ptr379 = call ptr @qc_create_map(i32 0, i32 6)
  store i32 1, ptr %temp_key, align 4
  call void @qc_map_set(ptr %map_ptr379, ptr %temp_key, ptr @.str.114)
  store i32 2, ptr %temp_key380, align 4
  call void @qc_map_set(ptr %map_ptr379, ptr %temp_key380, ptr @.str.115)
  store i32 3, ptr %temp_key381, align 4
  call void @qc_map_set(ptr %map_ptr379, ptr %temp_key381, ptr @.str.116)
  store ptr %map_ptr379, ptr %names, align 8
  %map_ptr382 = load ptr, ptr %names, align 8
  call void @qc_print_map(ptr %map_ptr382)
  call void @qc_print_char(i8 10)
  %map_ptr383 = load ptr, ptr %names, align 8
  store i32 2, ptr %map_key, align 4
  %map_val_ptr384 = call ptr @qc_map_get(ptr %map_ptr383, ptr %map_key)
  call void @qc_print_string(ptr %map_val_ptr384)
  call void @qc_print_char(i8 10)
  %map_ptr385 = load ptr, ptr %names, align 8
  store i32 4, ptr %map_key386, align 4
  call void @qc_map_set(ptr %map_ptr385, ptr %map_key386, ptr @.str.117)
  %map_ptr387 = load ptr, ptr %names, align 8
  call void @qc_print_map(ptr %map_ptr387)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.118)
  %map_ptr388 = call ptr @qc_create_map(i32 6, i32 0)
  store ptr %map_ptr388, ptr %empty_map, align 8
  %map_ptr389 = load ptr, ptr %empty_map, align 8
  call void @qc_print_map(ptr %map_ptr389)
  call void @qc_print_char(i8 10)
  %empty_map390 = load ptr, ptr %empty_map, align 8
  %map_size391 = call i32 @qc_map_size(ptr %empty_map390)
  call void @qc_print_int(i32 %map_size391)
  call void @qc_print_char(i8 10)
  %map_ptr392 = load ptr, ptr %empty_map, align 8
  store i32 1, ptr %map_val393, align 4
  call void @qc_map_set(ptr %map_ptr392, ptr @.str.119, ptr %map_val393)
  %map_ptr394 = load ptr, ptr %empty_map, align 8
  call void @qc_print_map(ptr %map_ptr394)
  call void @qc_print_char(i8 10)
  %empty_map395 = load ptr, ptr %empty_map, align 8
  %map_size396 = call i32 @qc_map_size(ptr %empty_map395)
  call void @qc_print_int(i32 %map_size396)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.120)
  %map_ptr397 = call ptr @qc_create_map(i32 6, i32 0)
  store i32 10, ptr %temp_val398, align 4
  call void @qc_map_set(ptr %map_ptr397, ptr @.str.121, ptr %temp_val398)
  store i32 20, ptr %temp_val399, align 4
  call void @qc_map_set(ptr %map_ptr397, ptr @.str.122, ptr %temp_val399)
  store ptr %map_ptr397, ptr %myMap, align 8
  %map_ptr400 = load ptr, ptr %myMap, align 8
  call void @qc_print_map(ptr %map_ptr400)
  call void @qc_print_char(i8 10)
  %map_ptr401 = load ptr, ptr %myMap, align 8
  %map_val_ptr402 = call ptr @qc_map_get(ptr %map_ptr401, ptr @.str.123)
  %map_val403 = load i32, ptr %map_val_ptr402, align 4
  call void @qc_print_int(i32 %map_val403)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.124)
  %ages404 = load ptr, ptr %ages, align 8
  %calltmp405 = call i32 @print_map_size(ptr %ages404)
  call void @qc_println(ptr @.str.125)
  call void @qc_println(ptr @.str.126)
  call void @qc_println(ptr @.str.127)
  %heap_arr406 = call ptr @malloc(i64 12)
  store ptr %heap_arr406, ptr %arr1, align 8
  %heap_ptr407 = load ptr, ptr %arr1, align 8
  %42 = getelementptr inbounds [3 x i32], ptr %heap_ptr407, i32 0, i32 0
  store i32 1, ptr %42, align 4
  %heap_ptr408 = load ptr, ptr %arr1, align 8
  %43 = getelementptr inbounds [3 x i32], ptr %heap_ptr408, i32 0, i32 1
  store i32 2, ptr %43, align 4
  %heap_ptr409 = load ptr, ptr %arr1, align 8
  %44 = getelementptr inbounds [3 x i32], ptr %heap_ptr409, i32 0, i32 2
  store i32 3, ptr %44, align 4
  %heap_arr410 = call ptr @malloc(i64 8)
  store ptr %heap_arr410, ptr %arr2, align 8
  %heap_ptr411 = load ptr, ptr %arr2, align 8
  %45 = getelementptr inbounds [2 x i32], ptr %heap_ptr411, i32 0, i32 0
  store i32 4, ptr %45, align 4
  %heap_ptr412 = load ptr, ptr %arr2, align 8
  %46 = getelementptr inbounds [2 x i32], ptr %heap_ptr412, i32 0, i32 1
  store i32 5, ptr %46, align 4
  %arr1413 = load ptr, ptr %arr1, align 8
  %arr2414 = load ptr, ptr %arr2, align 8
  %arr1415 = load ptr, ptr %arr1, align 8
  %47 = getelementptr i32, ptr %arr1415, i32 0
  %48 = load i32, ptr %47, align 4
  %49 = getelementptr i32, ptr %arr1415, i32 1
  %50 = load i32, ptr %49, align 4
  %51 = getelementptr i32, ptr %arr1415, i32 2
  %52 = load i32, ptr %51, align 4
  %arr2416 = load ptr, ptr %arr2, align 8
  %53 = getelementptr i32, ptr %arr2416, i32 0
  %54 = load i32, ptr %53, align 4
  %55 = getelementptr i32, ptr %arr2416, i32 1
  %56 = load i32, ptr %55, align 4
  %arr_elem_ptr = getelementptr inbounds [7 x i32], ptr %arr_lit, i32 0, i32 0
  store i32 %48, ptr %arr_elem_ptr, align 4
  %arr_elem_ptr417 = getelementptr inbounds [7 x i32], ptr %arr_lit, i32 0, i32 1
  store i32 %50, ptr %arr_elem_ptr417, align 4
  %arr_elem_ptr418 = getelementptr inbounds [7 x i32], ptr %arr_lit, i32 0, i32 2
  store i32 %52, ptr %arr_elem_ptr418, align 4
  %arr_elem_ptr419 = getelementptr inbounds [7 x i32], ptr %arr_lit, i32 0, i32 3
  store i32 %54, ptr %arr_elem_ptr419, align 4
  %arr_elem_ptr420 = getelementptr inbounds [7 x i32], ptr %arr_lit, i32 0, i32 4
  store i32 %56, ptr %arr_elem_ptr420, align 4
  %arr_elem_ptr421 = getelementptr inbounds [7 x i32], ptr %arr_lit, i32 0, i32 5
  store i32 6, ptr %arr_elem_ptr421, align 4
  %arr_elem_ptr422 = getelementptr inbounds [7 x i32], ptr %arr_lit, i32 0, i32 6
  store i32 7, ptr %arr_elem_ptr422, align 4
  %arr_ptr = getelementptr inbounds [7 x i32], ptr %arr_lit, i32 0, i32 0
  %arr1423 = load ptr, ptr %arr1, align 8
  %arr2424 = load ptr, ptr %arr2, align 8
  store ptr %arr_ptr, ptr %combined, align 8
  %combined425 = load ptr, ptr %combined, align 8
  store i32 0, ptr %__foreach_i_xdxdxdx, align 4
  br label %foreach.cond426

foreach.cond426:                                  ; preds = %foreach.inc428, %foreach.end368
  %__foreach_i_xdxdxdx430 = load i32, ptr %__foreach_i_xdxdxdx, align 4
  %foreach_cmp431 = icmp slt i32 %__foreach_i_xdxdxdx430, 7
  br i1 %foreach_cmp431, label %foreach.body427, label %foreach.end429

foreach.body427:                                  ; preds = %foreach.cond426
  %heap_ptr432 = load ptr, ptr %combined, align 8
  %heap_elem_ptr433 = getelementptr i32, ptr %heap_ptr432, i32 %__foreach_i_xdxdxdx430
  %elem434 = load i32, ptr %heap_elem_ptr433, align 4
  store i32 %elem434, ptr %xdxdxdx, align 4
  %xdxdxdx435 = load i32, ptr %xdxdxdx, align 4
  call void @qc_print_int(i32 %xdxdxdx435)
  call void @qc_print_string(ptr @.str.128)
  br label %foreach.inc428

foreach.inc428:                                   ; preds = %foreach.body427
  %__foreach_i_xdxdxdx436 = load i32, ptr %__foreach_i_xdxdxdx, align 4
  %i_inc437 = add i32 %__foreach_i_xdxdxdx436, 1
  store i32 %i_inc437, ptr %__foreach_i_xdxdxdx, align 4
  br label %foreach.cond426

foreach.end429:                                   ; preds = %foreach.cond426
  call void @qc_println(ptr @.str.129)
  call void @qc_println(ptr @.str.130)
  %list_ptr438 = call ptr @qc_create_list(i32 0)
  store i32 10, ptr %temp_elem439, align 4
  call void @qc_list_push(ptr %list_ptr438, ptr %temp_elem439, i32 0)
  store i32 20, ptr %temp_elem440, align 4
  call void @qc_list_push(ptr %list_ptr438, ptr %temp_elem440, i32 0)
  store ptr %list_ptr438, ptr %list1, align 8
  %list_ptr441 = call ptr @qc_create_list(i32 0)
  store i32 30, ptr %temp_elem442, align 4
  call void @qc_list_push(ptr %list_ptr441, ptr %temp_elem442, i32 0)
  store i32 40, ptr %temp_elem443, align 4
  call void @qc_list_push(ptr %list_ptr441, ptr %temp_elem443, i32 0)
  store ptr %list_ptr441, ptr %list2, align 8
  %list_ptr444 = call ptr @qc_create_list(i32 0)
  %list1445 = load ptr, ptr %list1, align 8
  %list_len446 = call i32 @qc_list_length(ptr %list1445)
  store i32 0, ptr %spread_push_i, align 4
  br label %spread_push_loop

spread_push_loop:                                 ; preds = %spread_push_body, %foreach.end429
  %57 = load i32, ptr %spread_push_i, align 4
  %58 = icmp slt i32 %57, %list_len446
  br i1 %58, label %spread_push_body, label %spread_push_end

spread_push_body:                                 ; preds = %spread_push_loop
  %59 = call ptr @qc_list_get(ptr %list1445, i32 %57)
  call void @qc_list_push(ptr %list_ptr444, ptr %59, i32 0)
  %60 = add i32 %57, 1
  store i32 %60, ptr %spread_push_i, align 4
  br label %spread_push_loop

spread_push_end:                                  ; preds = %spread_push_loop
  %list2447 = load ptr, ptr %list2, align 8
  %list_len448 = call i32 @qc_list_length(ptr %list2447)
  store i32 0, ptr %spread_push_i452, align 4
  br label %spread_push_loop449

spread_push_loop449:                              ; preds = %spread_push_body450, %spread_push_end
  %61 = load i32, ptr %spread_push_i452, align 4
  %62 = icmp slt i32 %61, %list_len448
  br i1 %62, label %spread_push_body450, label %spread_push_end451

spread_push_body450:                              ; preds = %spread_push_loop449
  %63 = call ptr @qc_list_get(ptr %list2447, i32 %61)
  call void @qc_list_push(ptr %list_ptr444, ptr %63, i32 0)
  %64 = add i32 %61, 1
  store i32 %64, ptr %spread_push_i452, align 4
  br label %spread_push_loop449

spread_push_end451:                               ; preds = %spread_push_loop449
  store i32 50, ptr %temp_elem453, align 4
  call void @qc_list_push(ptr %list_ptr444, ptr %temp_elem453, i32 0)
  store ptr %list_ptr444, ptr %merged, align 8
  %merged454 = load ptr, ptr %merged, align 8
  %coll_len455 = call i32 @qc_list_length(ptr %merged454)
  store i32 0, ptr %__foreach_i_xdxdxdx456, align 4
  br label %foreach.cond458

foreach.cond458:                                  ; preds = %foreach.inc460, %spread_push_end451
  %__foreach_i_xdxdxdx462 = load i32, ptr %__foreach_i_xdxdxdx456, align 4
  %foreach_cmp463 = icmp slt i32 %__foreach_i_xdxdxdx462, %coll_len455
  br i1 %foreach_cmp463, label %foreach.body459, label %foreach.end461

foreach.body459:                                  ; preds = %foreach.cond458
  %elem_ptr464 = call ptr @qc_list_get(ptr %merged454, i32 %__foreach_i_xdxdxdx462)
  %elem465 = load i32, ptr %elem_ptr464, align 4
  store i32 %elem465, ptr %xdxdxdx457, align 4
  %xdxdxdx466 = load i32, ptr %xdxdxdx457, align 4
  call void @qc_print_int(i32 %xdxdxdx466)
  call void @qc_print_string(ptr @.str.131)
  br label %foreach.inc460

foreach.inc460:                                   ; preds = %foreach.body459
  %__foreach_i_xdxdxdx467 = load i32, ptr %__foreach_i_xdxdxdx456, align 4
  %i_inc468 = add i32 %__foreach_i_xdxdxdx467, 1
  store i32 %i_inc468, ptr %__foreach_i_xdxdxdx456, align 4
  br label %foreach.cond458

foreach.end461:                                   ; preds = %foreach.cond458
  call void @qc_println(ptr @.str.132)
  call void @qc_println(ptr @.str.133)
  %heap_arr469 = call ptr @malloc(i64 12)
  store ptr %heap_arr469, ptr %nums, align 8
  %heap_ptr470 = load ptr, ptr %nums, align 8
  %65 = getelementptr inbounds [3 x i32], ptr %heap_ptr470, i32 0, i32 0
  store i32 100, ptr %65, align 4
  %heap_ptr471 = load ptr, ptr %nums, align 8
  %66 = getelementptr inbounds [3 x i32], ptr %heap_ptr471, i32 0, i32 1
  store i32 200, ptr %66, align 4
  %heap_ptr472 = load ptr, ptr %nums, align 8
  %67 = getelementptr inbounds [3 x i32], ptr %heap_ptr472, i32 0, i32 2
  store i32 300, ptr %67, align 4
  call void @qc_println(ptr @.str.134)
  %list_ptr473 = call ptr @qc_create_list(i32 0)
  %nums474 = load ptr, ptr %nums, align 8
  %arr_ptr475 = load ptr, ptr %nums, align 8
  store i32 0, ptr %spread_push_i479, align 4
  br label %spread_push_loop476

spread_push_loop476:                              ; preds = %spread_push_body477, %foreach.end461
  %68 = load i32, ptr %spread_push_i479, align 4
  %69 = icmp slt i32 %68, 3
  br i1 %69, label %spread_push_body477, label %spread_push_end478

spread_push_body477:                              ; preds = %spread_push_loop476
  %70 = getelementptr i32, ptr %arr_ptr475, i32 %68
  call void @qc_list_push(ptr %list_ptr473, ptr %70, i32 0)
  %71 = add i32 %68, 1
  store i32 %71, ptr %spread_push_i479, align 4
  br label %spread_push_loop476

spread_push_end478:                               ; preds = %spread_push_loop476
  store i32 400, ptr %temp_elem480, align 4
  call void @qc_list_push(ptr %list_ptr473, ptr %temp_elem480, i32 0)
  store ptr %list_ptr473, ptr %fromArray, align 8
  call void @qc_println(ptr @.str.135)
  %fromArray481 = load ptr, ptr %fromArray, align 8
  %coll_len482 = call i32 @qc_list_length(ptr %fromArray481)
  store i32 0, ptr %__foreach_i_xxxdxxx, align 4
  br label %foreach.cond483

foreach.cond483:                                  ; preds = %foreach.inc485, %spread_push_end478
  %__foreach_i_xxxdxxx487 = load i32, ptr %__foreach_i_xxxdxxx, align 4
  %foreach_cmp488 = icmp slt i32 %__foreach_i_xxxdxxx487, %coll_len482
  br i1 %foreach_cmp488, label %foreach.body484, label %foreach.end486

foreach.body484:                                  ; preds = %foreach.cond483
  %elem_ptr489 = call ptr @qc_list_get(ptr %fromArray481, i32 %__foreach_i_xxxdxxx487)
  %elem490 = load i32, ptr %elem_ptr489, align 4
  store i32 %elem490, ptr %xxxdxxx, align 4
  %xxxdxxx491 = load i32, ptr %xxxdxxx, align 4
  call void @qc_print_int(i32 %xxxdxxx491)
  call void @qc_print_string(ptr @.str.136)
  br label %foreach.inc485

foreach.inc485:                                   ; preds = %foreach.body484
  %__foreach_i_xxxdxxx492 = load i32, ptr %__foreach_i_xxxdxxx, align 4
  %i_inc493 = add i32 %__foreach_i_xxxdxxx492, 1
  store i32 %i_inc493, ptr %__foreach_i_xxxdxxx, align 4
  br label %foreach.cond483

foreach.end486:                                   ; preds = %foreach.cond483
  call void @qc_println(ptr @.str.137)
  call void @qc_println(ptr @.str.138)
  %list_ptr494 = call ptr @qc_create_list(i32 0)
  store i32 5, ptr %temp_elem495, align 4
  call void @qc_list_push(ptr %list_ptr494, ptr %temp_elem495, i32 0)
  store i32 6, ptr %temp_elem496, align 4
  call void @qc_list_push(ptr %list_ptr494, ptr %temp_elem496, i32 0)
  store i32 7, ptr %temp_elem497, align 4
  call void @qc_list_push(ptr %list_ptr494, ptr %temp_elem497, i32 0)
  store ptr %list_ptr494, ptr %ListList, align 8
  call void @qc_println(ptr @.str.139)
  %ListList498 = load ptr, ptr %ListList, align 8
  %list_len499 = call i32 @qc_list_length(ptr %ListList498)
  %72 = add i32 2, %list_len499
  %73 = add i32 %72, 1
  %74 = zext i32 %73 to i64
  %75 = mul i64 %74, 4
  %runtime_arr = call ptr @malloc(i64 %75)
  %76 = getelementptr i32, ptr %runtime_arr, i32 0
  store i32 1, ptr %76, align 4
  %77 = getelementptr i32, ptr %runtime_arr, i32 1
  store i32 2, ptr %77, align 4
  %ListList500 = load ptr, ptr %ListList, align 8
  %list_len501 = call i32 @qc_list_length(ptr %ListList500)
  store i32 0, ptr %copy_i, align 4
  store i32 2, ptr %copy_dest_idx, align 4
  br label %copy_loop

copy_loop:                                        ; preds = %copy_body, %foreach.end486
  %78 = load i32, ptr %copy_i, align 4
  %79 = icmp slt i32 %78, %list_len501
  br i1 %79, label %copy_body, label %copy_end

copy_body:                                        ; preds = %copy_loop
  %80 = load i32, ptr %copy_dest_idx, align 4
  %81 = call ptr @qc_list_get(ptr %ListList500, i32 %78)
  %82 = load i32, ptr %81, align 4
  %83 = getelementptr i32, ptr %runtime_arr, i32 %80
  store i32 %82, ptr %83, align 4
  %84 = add i32 %78, 1
  store i32 %84, ptr %copy_i, align 4
  %85 = add i32 %80, 1
  store i32 %85, ptr %copy_dest_idx, align 4
  br label %copy_loop

copy_end:                                         ; preds = %copy_loop
  %86 = load i32, ptr %copy_dest_idx, align 4
  %87 = getelementptr i32, ptr %runtime_arr, i32 %86
  store i32 8, ptr %87, align 4
  %88 = add i32 %86, 1
  %ListList502 = load ptr, ptr %ListList, align 8
  %list_len503 = call i32 @qc_list_length(ptr %ListList502)
  %89 = add i32 2, %list_len503
  %90 = add i32 %89, 1
  store i32 %90, ptr %arrFromList_size, align 4
  store ptr %runtime_arr, ptr %arrFromList, align 8
  call void @qc_println(ptr @.str.140)
  %arrFromList504 = load ptr, ptr %arrFromList, align 8
  %runtime_len = load i32, ptr %arrFromList_size, align 4
  store i32 0, ptr %__foreach_i_xcxxc, align 4
  br label %foreach.cond505

foreach.cond505:                                  ; preds = %foreach.inc507, %copy_end
  %__foreach_i_xcxxc509 = load i32, ptr %__foreach_i_xcxxc, align 4
  %foreach_cmp510 = icmp slt i32 %__foreach_i_xcxxc509, %runtime_len
  br i1 %foreach_cmp510, label %foreach.body506, label %foreach.end508

foreach.body506:                                  ; preds = %foreach.cond505
  %heap_ptr511 = load ptr, ptr %arrFromList, align 8
  %heap_elem_ptr512 = getelementptr i32, ptr %heap_ptr511, i32 %__foreach_i_xcxxc509
  %elem513 = load i32, ptr %heap_elem_ptr512, align 4
  store i32 %elem513, ptr %xcxxc, align 4
  %xcxxc514 = load i32, ptr %xcxxc, align 4
  call void @qc_print_int(i32 %xcxxc514)
  call void @qc_print_string(ptr @.str.141)
  br label %foreach.inc507

foreach.inc507:                                   ; preds = %foreach.body506
  %__foreach_i_xcxxc515 = load i32, ptr %__foreach_i_xcxxc, align 4
  %i_inc516 = add i32 %__foreach_i_xcxxc515, 1
  store i32 %i_inc516, ptr %__foreach_i_xcxxc, align 4
  br label %foreach.cond505

foreach.end508:                                   ; preds = %foreach.cond505
  call void @qc_println(ptr @.str.142)
  call void @qc_println(ptr @.str.143)
  %heap_arr517 = call ptr @malloc(i64 8)
  store ptr %heap_arr517, ptr %a518, align 8
  %heap_ptr519 = load ptr, ptr %a518, align 8
  %91 = getelementptr inbounds [2 x i32], ptr %heap_ptr519, i32 0, i32 0
  store i32 1, ptr %91, align 4
  %heap_ptr520 = load ptr, ptr %a518, align 8
  %92 = getelementptr inbounds [2 x i32], ptr %heap_ptr520, i32 0, i32 1
  store i32 2, ptr %92, align 4
  %heap_arr521 = call ptr @malloc(i64 8)
  store ptr %heap_arr521, ptr %b522, align 8
  %heap_ptr523 = load ptr, ptr %b522, align 8
  %93 = getelementptr inbounds [2 x i32], ptr %heap_ptr523, i32 0, i32 0
  store i32 3, ptr %93, align 4
  %heap_ptr524 = load ptr, ptr %b522, align 8
  %94 = getelementptr inbounds [2 x i32], ptr %heap_ptr524, i32 0, i32 1
  store i32 4, ptr %94, align 4
  %heap_arr525 = call ptr @malloc(i64 8)
  store ptr %heap_arr525, ptr %c526, align 8
  %heap_ptr527 = load ptr, ptr %c526, align 8
  %95 = getelementptr inbounds [2 x i32], ptr %heap_ptr527, i32 0, i32 0
  store i32 5, ptr %95, align 4
  %heap_ptr528 = load ptr, ptr %c526, align 8
  %96 = getelementptr inbounds [2 x i32], ptr %heap_ptr528, i32 0, i32 1
  store i32 6, ptr %96, align 4
  %a529 = load ptr, ptr %a518, align 8
  %b530 = load ptr, ptr %b522, align 8
  %c531 = load ptr, ptr %c526, align 8
  %a532 = load ptr, ptr %a518, align 8
  %97 = getelementptr i32, ptr %a532, i32 0
  %98 = load i32, ptr %97, align 4
  %99 = getelementptr i32, ptr %a532, i32 1
  %100 = load i32, ptr %99, align 4
  %b533 = load ptr, ptr %b522, align 8
  %101 = getelementptr i32, ptr %b533, i32 0
  %102 = load i32, ptr %101, align 4
  %103 = getelementptr i32, ptr %b533, i32 1
  %104 = load i32, ptr %103, align 4
  %c534 = load ptr, ptr %c526, align 8
  %105 = getelementptr i32, ptr %c534, i32 0
  %106 = load i32, ptr %105, align 4
  %107 = getelementptr i32, ptr %c534, i32 1
  %108 = load i32, ptr %107, align 4
  %arr_elem_ptr536 = getelementptr inbounds [6 x i32], ptr %arr_lit535, i32 0, i32 0
  store i32 %98, ptr %arr_elem_ptr536, align 4
  %arr_elem_ptr537 = getelementptr inbounds [6 x i32], ptr %arr_lit535, i32 0, i32 1
  store i32 %100, ptr %arr_elem_ptr537, align 4
  %arr_elem_ptr538 = getelementptr inbounds [6 x i32], ptr %arr_lit535, i32 0, i32 2
  store i32 %102, ptr %arr_elem_ptr538, align 4
  %arr_elem_ptr539 = getelementptr inbounds [6 x i32], ptr %arr_lit535, i32 0, i32 3
  store i32 %104, ptr %arr_elem_ptr539, align 4
  %arr_elem_ptr540 = getelementptr inbounds [6 x i32], ptr %arr_lit535, i32 0, i32 4
  store i32 %106, ptr %arr_elem_ptr540, align 4
  %arr_elem_ptr541 = getelementptr inbounds [6 x i32], ptr %arr_lit535, i32 0, i32 5
  store i32 %108, ptr %arr_elem_ptr541, align 4
  %arr_ptr542 = getelementptr inbounds [6 x i32], ptr %arr_lit535, i32 0, i32 0
  %a543 = load ptr, ptr %a518, align 8
  %b544 = load ptr, ptr %b522, align 8
  %c545 = load ptr, ptr %c526, align 8
  store ptr %arr_ptr542, ptr %multi, align 8
  %multi546 = load ptr, ptr %multi, align 8
  store i32 0, ptr %__foreach_i_xcxcxc, align 4
  br label %foreach.cond547

foreach.cond547:                                  ; preds = %foreach.inc549, %foreach.end508
  %__foreach_i_xcxcxc551 = load i32, ptr %__foreach_i_xcxcxc, align 4
  %foreach_cmp552 = icmp slt i32 %__foreach_i_xcxcxc551, 6
  br i1 %foreach_cmp552, label %foreach.body548, label %foreach.end550

foreach.body548:                                  ; preds = %foreach.cond547
  %heap_ptr553 = load ptr, ptr %multi, align 8
  %heap_elem_ptr554 = getelementptr i32, ptr %heap_ptr553, i32 %__foreach_i_xcxcxc551
  %elem555 = load i32, ptr %heap_elem_ptr554, align 4
  store i32 %elem555, ptr %xcxcxc, align 4
  %xcxcxc556 = load i32, ptr %xcxcxc, align 4
  call void @qc_print_int(i32 %xcxcxc556)
  call void @qc_print_string(ptr @.str.144)
  br label %foreach.inc549

foreach.inc549:                                   ; preds = %foreach.body548
  %__foreach_i_xcxcxc557 = load i32, ptr %__foreach_i_xcxcxc, align 4
  %i_inc558 = add i32 %__foreach_i_xcxcxc557, 1
  store i32 %i_inc558, ptr %__foreach_i_xcxcxc, align 4
  br label %foreach.cond547

foreach.end550:                                   ; preds = %foreach.cond547
  call void @qc_println(ptr @.str.145)
  call void @qc_println(ptr @.str.146)
  %heap_arr559 = call ptr @malloc(i64 12)
  store ptr %heap_arr559, ptr %args, align 8
  %heap_ptr560 = load ptr, ptr %args, align 8
  %109 = getelementptr inbounds [3 x i32], ptr %heap_ptr560, i32 0, i32 0
  store i32 10, ptr %109, align 4
  %heap_ptr561 = load ptr, ptr %args, align 8
  %110 = getelementptr inbounds [3 x i32], ptr %heap_ptr561, i32 0, i32 1
  store i32 20, ptr %110, align 4
  %heap_ptr562 = load ptr, ptr %args, align 8
  %111 = getelementptr inbounds [3 x i32], ptr %heap_ptr562, i32 0, i32 2
  store i32 30, ptr %111, align 4
  %args563 = load ptr, ptr %args, align 8
  %spread_args_array = alloca ptr, i32 3, align 8
  %spread_types_array = alloca i32, i32 3, align 4
  %args564 = load ptr, ptr %args, align 8
  store i32 0, ptr %expand_i, align 4
  store i32 0, ptr %expand_idx, align 4
  br label %expand_loop

expand_loop:                                      ; preds = %expand_body, %foreach.end550
  %112 = load i32, ptr %expand_i, align 4
  %113 = icmp slt i32 %112, 3
  br i1 %113, label %expand_body, label %expand_end

expand_body:                                      ; preds = %expand_loop
  %114 = load i32, ptr %expand_idx, align 4
  %arr_ptr565 = load ptr, ptr %args, align 8
  %arr_elem_ptr566 = getelementptr i32, ptr %arr_ptr565, i32 %112
  %115 = getelementptr ptr, ptr %spread_args_array, i32 %114
  store ptr %arr_elem_ptr566, ptr %115, align 8
  %116 = getelementptr i32, ptr %spread_types_array, i32 %114
  store i32 0, ptr %116, align 4
  %117 = add i32 %112, 1
  store i32 %117, ptr %expand_i, align 4
  %118 = add i32 %114, 1
  store i32 %118, ptr %expand_idx, align 4
  br label %expand_loop

expand_end:                                       ; preds = %expand_loop
  %119 = load i32, ptr %expand_idx, align 4
  %120 = call ptr @qc_spread_call(ptr @print_three, i32 3, ptr %spread_args_array, ptr %spread_types_array, i32 0, ptr %spread_ret)
  %spread_result = load i32, ptr %spread_ret, align 4
  call void @qc_println(ptr @.str.150)
  store ptr @__lambda_1, ptr %sumsum, align 8
  %heap_arr567 = call ptr @malloc(i64 12)
  store ptr %heap_arr567, ptr %values, align 8
  %heap_ptr568 = load ptr, ptr %values, align 8
  %121 = getelementptr inbounds [3 x i32], ptr %heap_ptr568, i32 0, i32 0
  store i32 5, ptr %121, align 4
  %heap_ptr569 = load ptr, ptr %values, align 8
  %122 = getelementptr inbounds [3 x i32], ptr %heap_ptr569, i32 0, i32 1
  store i32 10, ptr %122, align 4
  %heap_ptr570 = load ptr, ptr %values, align 8
  %123 = getelementptr inbounds [3 x i32], ptr %heap_ptr570, i32 0, i32 2
  store i32 15, ptr %123, align 4
  %sumsum571 = load ptr, ptr %sumsum, align 8
  %values572 = load ptr, ptr %values, align 8
  %spread_args_array573 = alloca ptr, i32 3, align 8
  %spread_types_array574 = alloca i32, i32 3, align 4
  %values575 = load ptr, ptr %values, align 8
  store i32 0, ptr %expand_i579, align 4
  store i32 0, ptr %expand_idx580, align 4
  br label %expand_loop576

expand_loop576:                                   ; preds = %expand_body577, %expand_end
  %124 = load i32, ptr %expand_i579, align 4
  %125 = icmp slt i32 %124, 3
  br i1 %125, label %expand_body577, label %expand_end578

expand_body577:                                   ; preds = %expand_loop576
  %126 = load i32, ptr %expand_idx580, align 4
  %arr_ptr581 = load ptr, ptr %values, align 8
  %arr_elem_ptr582 = getelementptr i32, ptr %arr_ptr581, i32 %124
  %127 = getelementptr ptr, ptr %spread_args_array573, i32 %126
  store ptr %arr_elem_ptr582, ptr %127, align 8
  %128 = getelementptr i32, ptr %spread_types_array574, i32 %126
  store i32 0, ptr %128, align 4
  %129 = add i32 %124, 1
  store i32 %129, ptr %expand_i579, align 4
  %130 = add i32 %126, 1
  store i32 %130, ptr %expand_idx580, align 4
  br label %expand_loop576

expand_end578:                                    ; preds = %expand_loop576
  %131 = load i32, ptr %expand_idx580, align 4
  %132 = call ptr @qc_spread_call(ptr %sumsum571, i32 3, ptr %spread_args_array573, ptr %spread_types_array574, i32 0, ptr %spread_ret583)
  %spread_result584 = load i32, ptr %spread_ret583, align 4
  store i32 %spread_result584, ptr %result, align 4
  call void @qc_print_string(ptr @.str.151)
  %result585 = load i32, ptr %result, align 4
  call void @qc_print_int(i32 %result585)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.152)
  %heap_arr586 = call ptr @malloc(i64 8)
  store ptr %heap_arr586, ptr %first, align 8
  %heap_ptr587 = load ptr, ptr %first, align 8
  %133 = getelementptr inbounds [2 x i32], ptr %heap_ptr587, i32 0, i32 0
  store i32 1, ptr %133, align 4
  %heap_ptr588 = load ptr, ptr %first, align 8
  %134 = getelementptr inbounds [2 x i32], ptr %heap_ptr588, i32 0, i32 1
  store i32 2, ptr %134, align 4
  %first589 = load ptr, ptr %first, align 8
  %spread_args_array590 = alloca ptr, i32 5, align 8
  %spread_types_array591 = alloca i32, i32 5, align 4
  %first592 = load ptr, ptr %first, align 8
  store i32 0, ptr %expand_i596, align 4
  store i32 0, ptr %expand_idx597, align 4
  br label %expand_loop593

expand_loop593:                                   ; preds = %expand_body594, %expand_end578
  %135 = load i32, ptr %expand_i596, align 4
  %136 = icmp slt i32 %135, 2
  br i1 %136, label %expand_body594, label %expand_end595

expand_body594:                                   ; preds = %expand_loop593
  %137 = load i32, ptr %expand_idx597, align 4
  %arr_ptr598 = load ptr, ptr %first, align 8
  %arr_elem_ptr599 = getelementptr i32, ptr %arr_ptr598, i32 %135
  %138 = getelementptr ptr, ptr %spread_args_array590, i32 %137
  store ptr %arr_elem_ptr599, ptr %138, align 8
  %139 = getelementptr i32, ptr %spread_types_array591, i32 %137
  store i32 0, ptr %139, align 4
  %140 = add i32 %135, 1
  store i32 %140, ptr %expand_i596, align 4
  %141 = add i32 %137, 1
  store i32 %141, ptr %expand_idx597, align 4
  br label %expand_loop593

expand_end595:                                    ; preds = %expand_loop593
  %142 = load i32, ptr %expand_idx597, align 4
  store i32 3, ptr %arg_temp, align 4
  %143 = getelementptr ptr, ptr %spread_args_array590, i32 %142
  store ptr %arg_temp, ptr %143, align 8
  %144 = getelementptr i32, ptr %spread_types_array591, i32 %142
  store i32 0, ptr %144, align 4
  %145 = add i32 %142, 1
  store i32 4, ptr %arg_temp600, align 4
  %146 = getelementptr ptr, ptr %spread_args_array590, i32 %145
  store ptr %arg_temp600, ptr %146, align 8
  %147 = getelementptr i32, ptr %spread_types_array591, i32 %145
  store i32 0, ptr %147, align 4
  %148 = add i32 %145, 1
  store i32 5, ptr %arg_temp601, align 4
  %149 = getelementptr ptr, ptr %spread_args_array590, i32 %148
  store ptr %arg_temp601, ptr %149, align 8
  %150 = getelementptr i32, ptr %spread_types_array591, i32 %148
  store i32 0, ptr %150, align 4
  %151 = add i32 %148, 1
  %152 = call ptr @qc_spread_call(ptr @print_five, i32 5, ptr %spread_args_array590, ptr %spread_types_array591, i32 0, ptr %spread_ret602)
  %spread_result603 = load i32, ptr %spread_ret602, align 4
  call void @qc_println(ptr @.str.157)
  %heap_arr604 = call ptr @malloc(i64 16)
  store ptr %heap_arr604, ptr %names1, align 8
  %heap_ptr605 = load ptr, ptr %names1, align 8
  %153 = getelementptr inbounds [2 x ptr], ptr %heap_ptr605, i32 0, i32 0
  store ptr @.str.158, ptr %153, align 8
  %heap_ptr606 = load ptr, ptr %names1, align 8
  %154 = getelementptr inbounds [2 x ptr], ptr %heap_ptr606, i32 0, i32 1
  store ptr @.str.159, ptr %154, align 8
  %heap_arr607 = call ptr @malloc(i64 16)
  store ptr %heap_arr607, ptr %names2, align 8
  %heap_ptr608 = load ptr, ptr %names2, align 8
  %155 = getelementptr inbounds [2 x ptr], ptr %heap_ptr608, i32 0, i32 0
  store ptr @.str.160, ptr %155, align 8
  %heap_ptr609 = load ptr, ptr %names2, align 8
  %156 = getelementptr inbounds [2 x ptr], ptr %heap_ptr609, i32 0, i32 1
  store ptr @.str.161, ptr %156, align 8
  %names1610 = load ptr, ptr %names1, align 8
  %names2611 = load ptr, ptr %names2, align 8
  %names1612 = load ptr, ptr %names1, align 8
  %157 = getelementptr ptr, ptr %names1612, i32 0
  %158 = load ptr, ptr %157, align 8
  %159 = getelementptr ptr, ptr %names1612, i32 1
  %160 = load ptr, ptr %159, align 8
  %names2613 = load ptr, ptr %names2, align 8
  %161 = getelementptr ptr, ptr %names2613, i32 0
  %162 = load ptr, ptr %161, align 8
  %163 = getelementptr ptr, ptr %names2613, i32 1
  %164 = load ptr, ptr %163, align 8
  %arr_elem_ptr615 = getelementptr inbounds [4 x ptr], ptr %arr_lit614, i32 0, i32 0
  store ptr %158, ptr %arr_elem_ptr615, align 8
  %arr_elem_ptr616 = getelementptr inbounds [4 x ptr], ptr %arr_lit614, i32 0, i32 1
  store ptr %160, ptr %arr_elem_ptr616, align 8
  %arr_elem_ptr617 = getelementptr inbounds [4 x ptr], ptr %arr_lit614, i32 0, i32 2
  store ptr %162, ptr %arr_elem_ptr617, align 8
  %arr_elem_ptr618 = getelementptr inbounds [4 x ptr], ptr %arr_lit614, i32 0, i32 3
  store ptr %164, ptr %arr_elem_ptr618, align 8
  %arr_ptr619 = getelementptr inbounds [4 x ptr], ptr %arr_lit614, i32 0, i32 0
  %names1620 = load ptr, ptr %names1, align 8
  %names2621 = load ptr, ptr %names2, align 8
  store ptr %arr_ptr619, ptr %allNames, align 8
  %allNames622 = load ptr, ptr %allNames, align 8
  store i32 0, ptr %__foreach_i_namenamename, align 4
  br label %foreach.cond623

foreach.cond623:                                  ; preds = %foreach.inc625, %expand_end595
  %__foreach_i_namenamename627 = load i32, ptr %__foreach_i_namenamename, align 4
  %foreach_cmp628 = icmp slt i32 %__foreach_i_namenamename627, 4
  br i1 %foreach_cmp628, label %foreach.body624, label %foreach.end626

foreach.body624:                                  ; preds = %foreach.cond623
  %heap_ptr629 = load ptr, ptr %allNames, align 8
  %heap_elem_ptr630 = getelementptr ptr, ptr %heap_ptr629, i32 %__foreach_i_namenamename627
  %elem631 = load ptr, ptr %heap_elem_ptr630, align 8
  store ptr %elem631, ptr %namenamename, align 8
  %namenamename632 = load ptr, ptr %namenamename, align 8
  call void @qc_print_string(ptr %namenamename632)
  call void @qc_print_string(ptr @.str.162)
  br label %foreach.inc625

foreach.inc625:                                   ; preds = %foreach.body624
  %__foreach_i_namenamename633 = load i32, ptr %__foreach_i_namenamename, align 4
  %i_inc634 = add i32 %__foreach_i_namenamename633, 1
  store i32 %i_inc634, ptr %__foreach_i_namenamename, align 4
  br label %foreach.cond623

foreach.end626:                                   ; preds = %foreach.cond623
  call void @qc_println(ptr @.str.163)
  call void @qc_println(ptr @.str.164)
  %heap_arr635 = call ptr @malloc(i64 0)
  store ptr %heap_arr635, ptr %empty636, align 8
  %empty637 = load ptr, ptr %empty636, align 8
  %empty638 = load ptr, ptr %empty636, align 8
  %empty639 = load ptr, ptr %empty636, align 8
  store [2 x i32] [i32 1, i32 2], ptr %withEmpty, align 4
  %empty640 = load ptr, ptr %empty636, align 8
  call void @qc_println(ptr @12)
  %withEmpty641 = load [2 x i32], ptr %withEmpty, align 4
  store i32 0, ptr %__foreach_i_xccccccc, align 4
  br label %foreach.cond642

foreach.cond642:                                  ; preds = %foreach.inc644, %foreach.end626
  %__foreach_i_xccccccc646 = load i32, ptr %__foreach_i_xccccccc, align 4
  %foreach_cmp647 = icmp slt i32 %__foreach_i_xccccccc646, 2
  br i1 %foreach_cmp647, label %foreach.body643, label %foreach.end645

foreach.body643:                                  ; preds = %foreach.cond642
  %elem_ptr648 = getelementptr inbounds [2 x i32], ptr %withEmpty, i32 0, i32 %__foreach_i_xccccccc646
  %elem649 = load i32, ptr %elem_ptr648, align 4
  store i32 %elem649, ptr %xccccccc, align 4
  %xccccccc650 = load i32, ptr %xccccccc, align 4
  call void @qc_print_int(i32 %xccccccc650)
  call void @qc_print_string(ptr @.str.165)
  br label %foreach.inc644

foreach.inc644:                                   ; preds = %foreach.body643
  %__foreach_i_xccccccc651 = load i32, ptr %__foreach_i_xccccccc, align 4
  %i_inc652 = add i32 %__foreach_i_xccccccc651, 1
  store i32 %i_inc652, ptr %__foreach_i_xccccccc, align 4
  br label %foreach.cond642

foreach.end645:                                   ; preds = %foreach.cond642
  call void @qc_println(ptr @.str.166)
  call void @qc_println(ptr @.str.167)
  call void @qc_println(ptr @.str.168)
  call void @qc_println(ptr @.str.169)
  store %Point { i32 10, i32 20 }, ptr %p, align 4
  call void @qc_println(ptr @.str.170)
  call void @qc_print_string(ptr @.str.171)
  %p653 = load %Point, ptr %p, align 4
  %x654 = extractvalue %Point %p653, 0
  call void @qc_print_int(i32 %x654)
  call void @qc_print_char(i8 10)
  call void @qc_print_string(ptr @.str.172)
  %p655 = load %Point, ptr %p, align 4
  %y656 = extractvalue %Point %p655, 1
  call void @qc_print_int(i32 %y656)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.173)
  %x_ptr = getelementptr inbounds %Point, ptr %p, i32 0, i32 0
  store i32 30, ptr %x_ptr, align 4
  %y_ptr = getelementptr inbounds %Point, ptr %p, i32 0, i32 1
  store i32 40, ptr %y_ptr, align 4
  call void @qc_print_string(ptr @.str.174)
  %p657 = load %Point, ptr %p, align 4
  %x658 = extractvalue %Point %p657, 0
  call void @qc_print_int(i32 %x658)
  call void @qc_print_char(i8 10)
  call void @qc_print_string(ptr @.str.175)
  %p659 = load %Point, ptr %p, align 4
  %y660 = extractvalue %Point %p659, 1
  call void @qc_print_int(i32 %y660)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.176)
  %p661 = load %Point, ptr %p, align 4
  %calltmp662 = call i32 @printPoint(%Point %p661)
  call void @qc_println(ptr @.str.180)
  %calltmp663 = call %Point @makePoint(i32 50, i32 60)
  store %Point %calltmp663, ptr %p2, align 4
  %p2664 = load %Point, ptr %p2, align 4
  %calltmp665 = call i32 @printPoint(%Point %p2664)
  call void @qc_println(ptr @.str.181)
  store %Rectangle { %Point zeroinitializer, %Point { i32 100, i32 100 } }, ptr %rect, align 4
  call void @qc_print_string(ptr @.str.182)
  %rect666 = load %Rectangle, ptr %rect, align 4
  %topLeft = extractvalue %Rectangle %rect666, 0
  %x667 = extractvalue %Point %topLeft, 0
  call void @qc_print_int(i32 %x667)
  call void @qc_print_string(ptr @.str.183)
  %rect668 = load %Rectangle, ptr %rect, align 4
  %topLeft669 = extractvalue %Rectangle %rect668, 0
  %y670 = extractvalue %Point %topLeft669, 1
  call void @qc_print_int(i32 %y670)
  call void @qc_print_string(ptr @.str.184)
  call void @qc_print_string(ptr @.str.185)
  %rect671 = load %Rectangle, ptr %rect, align 4
  %bottomRight = extractvalue %Rectangle %rect671, 1
  %x672 = extractvalue %Point %bottomRight, 0
  call void @qc_print_int(i32 %x672)
  call void @qc_print_string(ptr @.str.186)
  %rect673 = load %Rectangle, ptr %rect, align 4
  %bottomRight674 = extractvalue %Rectangle %rect673, 1
  %y675 = extractvalue %Point %bottomRight674, 1
  call void @qc_print_int(i32 %y675)
  call void @qc_print_string(ptr @.str.187)
  call void @qc_println(ptr @.str.188)
  call void @qc_println(ptr @.str.189)
  call void @qc_println(ptr @.str.190)
  store %Result { i32 0, ptr @.str.191 }, ptr %r1, align 8
  %r1676 = load %Result, ptr %r1, align 8
  %union_tag = extractvalue %Result %r1676, 0
  %union_data = extractvalue %Result %r1676, 1
  %union_tag_match = icmp eq i32 %union_tag, 0
  br i1 %union_tag_match, label %tag_matches, label %tag_mismatch

tag_matches:                                      ; preds = %foreach.end645
  br label %cmp_end

tag_mismatch:                                     ; preds = %foreach.end645
  br label %cmp_end

cmp_end:                                          ; preds = %tag_mismatch, %tag_matches
  %cmp_result = phi i1 [ true, %tag_matches ], [ false, %tag_mismatch ]
  br i1 %cmp_result, label %then677, label %ifcont678

then677:                                          ; preds = %cmp_end
  call void @qc_println(ptr @.str.193)
  br label %ifcont678

ifcont678:                                        ; preds = %then677, %cmp_end
  store %Result { i32 1, ptr @.str.194 }, ptr %r2, align 8
  %r2679 = load %Result, ptr %r2, align 8
  %union_tag680 = extractvalue %Result %r2679, 0
  %union_data681 = extractvalue %Result %r2679, 1
  %union_tag_match682 = icmp eq i32 %union_tag680, 1
  br i1 %union_tag_match682, label %tag_matches683, label %tag_mismatch684

tag_matches683:                                   ; preds = %ifcont678
  br label %cmp_end685

tag_mismatch684:                                  ; preds = %ifcont678
  br label %cmp_end685

cmp_end685:                                       ; preds = %tag_mismatch684, %tag_matches683
  %cmp_result686 = phi i1 [ true, %tag_matches683 ], [ false, %tag_mismatch684 ]
  br i1 %cmp_result686, label %then687, label %ifcont688

then687:                                          ; preds = %cmp_end685
  call void @qc_println(ptr @.str.196)
  br label %ifcont688

ifcont688:                                        ; preds = %then687, %cmp_end685
  %union_heap = call ptr @malloc(i64 4)
  store i32 42, ptr %union_heap, align 4
  %165 = insertvalue %Result { i32 2, ptr undef }, ptr %union_heap, 1
  store %Result %165, ptr %r3, align 8
  %r3689 = load %Result, ptr %r3, align 8
  %union_tag690 = extractvalue %Result %r3689, 0
  %union_data691 = extractvalue %Result %r3689, 1
  %union_tag_match692 = icmp eq i32 %union_tag690, 2
  br i1 %union_tag_match692, label %tag_matches693, label %tag_mismatch694

tag_matches693:                                   ; preds = %ifcont688
  %union_payload = load i32, ptr %union_data691, align 4
  %union_int_eq = icmp eq i32 %union_payload, 42
  br label %cmp_end695

tag_mismatch694:                                  ; preds = %ifcont688
  br label %cmp_end695

cmp_end695:                                       ; preds = %tag_mismatch694, %tag_matches693
  %cmp_result696 = phi i1 [ %union_int_eq, %tag_matches693 ], [ false, %tag_mismatch694 ]
  br i1 %cmp_result696, label %then697, label %ifcont698

then697:                                          ; preds = %cmp_end695
  call void @qc_println(ptr @.str.197)
  br label %ifcont698

ifcont698:                                        ; preds = %then697, %cmp_end695
  call void @qc_println(ptr @.str.198)
  %union_heap699 = call ptr @malloc(i64 4)
  store i32 100, ptr %union_heap699, align 4
  %166 = insertvalue %Value { i32 0, ptr undef }, ptr %union_heap699, 1
  store %Value %166, ptr %vrv1, align 8
  call void @qc_print_string(ptr @.str.199)
  %vrv1700 = load %Value, ptr %vrv1, align 8
  %union_tag701 = extractvalue %Value %vrv1700, 0
  %union_payload702 = extractvalue %Value %vrv1700, 1
  switch i32 %union_tag701, label %print_union_end [
    i32 0, label %print_case_0
    i32 1, label %print_case_1
    i32 2, label %print_case_2
  ]

print_union_end:                                  ; preds = %print_case_2, %print_case_1, %print_case_0, %ifcont698
  call void @qc_print_char(i8 10)
  store %Value { i32 1, ptr @.str.200 }, ptr %vrv2, align 8
  call void @qc_print_string(ptr @.str.201)
  %vrv2703 = load %Value, ptr %vrv2, align 8
  %union_tag704 = extractvalue %Value %vrv2703, 0
  %union_payload705 = extractvalue %Value %vrv2703, 1
  switch i32 %union_tag704, label %print_union_end706 [
    i32 0, label %print_case_0707
    i32 1, label %print_case_1708
    i32 2, label %print_case_2709
  ]

print_case_0:                                     ; preds = %ifcont698
  %167 = load i32, ptr %union_payload702, align 4
  call void @qc_print_int(i32 %167)
  br label %print_union_end

print_case_1:                                     ; preds = %ifcont698
  %168 = load ptr, ptr %union_payload702, align 8
  call void @qc_print_string(ptr %union_payload702)
  br label %print_union_end

print_case_2:                                     ; preds = %ifcont698
  %169 = load float, ptr %union_payload702, align 4
  call void @qc_print_float(float %169)
  br label %print_union_end

print_union_end706:                               ; preds = %print_case_2709, %print_case_1708, %print_case_0707, %print_union_end
  call void @qc_print_char(i8 10)
  %union_heap710 = call ptr @malloc(i64 4)
  store float 0x40091EB860000000, ptr %union_heap710, align 4
  %170 = insertvalue %Value { i32 2, ptr undef }, ptr %union_heap710, 1
  store %Value %170, ptr %vrv3, align 8
  call void @qc_print_string(ptr @.str.202)
  %vrv3711 = load %Value, ptr %vrv3, align 8
  %union_tag712 = extractvalue %Value %vrv3711, 0
  %union_payload713 = extractvalue %Value %vrv3711, 1
  switch i32 %union_tag712, label %print_union_end714 [
    i32 0, label %print_case_0715
    i32 1, label %print_case_1716
    i32 2, label %print_case_2717
  ]

print_case_0707:                                  ; preds = %print_union_end
  %171 = load i32, ptr %union_payload705, align 4
  call void @qc_print_int(i32 %171)
  br label %print_union_end706

print_case_1708:                                  ; preds = %print_union_end
  %172 = load ptr, ptr %union_payload705, align 8
  call void @qc_print_string(ptr %union_payload705)
  br label %print_union_end706

print_case_2709:                                  ; preds = %print_union_end
  %173 = load float, ptr %union_payload705, align 4
  call void @qc_print_float(float %173)
  br label %print_union_end706

print_union_end714:                               ; preds = %print_case_2717, %print_case_1716, %print_case_0715, %print_union_end706
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.203)
  %vrv1718 = load %Value, ptr %vrv1, align 8
  %union_tag719 = extractvalue %Value %vrv1718, 0
  %union_data720 = extractvalue %Value %vrv1718, 1
  %union_tag_match721 = icmp eq i32 %union_tag719, 0
  br i1 %union_tag_match721, label %tag_matches722, label %tag_mismatch723

print_case_0715:                                  ; preds = %print_union_end706
  %174 = load i32, ptr %union_payload713, align 4
  call void @qc_print_int(i32 %174)
  br label %print_union_end714

print_case_1716:                                  ; preds = %print_union_end706
  %175 = load ptr, ptr %union_payload713, align 8
  call void @qc_print_string(ptr %union_payload713)
  br label %print_union_end714

print_case_2717:                                  ; preds = %print_union_end706
  %176 = load float, ptr %union_payload713, align 4
  call void @qc_print_float(float %176)
  br label %print_union_end714

tag_matches722:                                   ; preds = %print_union_end714
  %union_payload725 = load i32, ptr %union_data720, align 4
  %union_int_eq726 = icmp eq i32 %union_payload725, 100
  br label %cmp_end724

tag_mismatch723:                                  ; preds = %print_union_end714
  br label %cmp_end724

cmp_end724:                                       ; preds = %tag_mismatch723, %tag_matches722
  %cmp_result727 = phi i1 [ %union_int_eq726, %tag_matches722 ], [ false, %tag_mismatch723 ]
  br i1 %cmp_result727, label %then728, label %ifcont729

then728:                                          ; preds = %cmp_end724
  call void @qc_println(ptr @.str.204)
  br label %ifcont729

ifcont729:                                        ; preds = %then728, %cmp_end724
  %vrv2730 = load %Value, ptr %vrv2, align 8
  %union_tag731 = extractvalue %Value %vrv2730, 0
  %union_data732 = extractvalue %Value %vrv2730, 1
  %union_tag_match733 = icmp eq i32 %union_tag731, 1
  br i1 %union_tag_match733, label %tag_matches734, label %tag_mismatch735

tag_matches734:                                   ; preds = %ifcont729
  %payload_str_eq = call i1 @qc_string_eq(ptr %union_data732, ptr @.str.205)
  br label %cmp_end736

tag_mismatch735:                                  ; preds = %ifcont729
  br label %cmp_end736

cmp_end736:                                       ; preds = %tag_mismatch735, %tag_matches734
  %cmp_result737 = phi i1 [ %payload_str_eq, %tag_matches734 ], [ false, %tag_mismatch735 ]
  br i1 %cmp_result737, label %then738, label %ifcont739

then738:                                          ; preds = %cmp_end736
  call void @qc_println(ptr @.str.206)
  br label %ifcont739

ifcont739:                                        ; preds = %then738, %cmp_end736
  %vrv3740 = load %Value, ptr %vrv3, align 8
  %union_tag741 = extractvalue %Value %vrv3740, 0
  %union_data742 = extractvalue %Value %vrv3740, 1
  %union_tag_match743 = icmp eq i32 %union_tag741, 2
  br i1 %union_tag_match743, label %tag_matches744, label %tag_mismatch745

tag_matches744:                                   ; preds = %ifcont739
  %union_payload747 = load float, ptr %union_data742, align 4
  %union_fp_eq = fcmp oeq float %union_payload747, 0x40091EB860000000
  br label %cmp_end746

tag_mismatch745:                                  ; preds = %ifcont739
  br label %cmp_end746

cmp_end746:                                       ; preds = %tag_mismatch745, %tag_matches744
  %cmp_result748 = phi i1 [ %union_fp_eq, %tag_matches744 ], [ false, %tag_mismatch745 ]
  br i1 %cmp_result748, label %then749, label %ifcont750

then749:                                          ; preds = %cmp_end746
  call void @qc_println(ptr @.str.207)
  br label %ifcont750

ifcont750:                                        ; preds = %then749, %cmp_end746
  %vrv1751 = load %Value, ptr %vrv1, align 8
  %union_tag752 = extractvalue %Value %vrv1751, 0
  %union_data753 = extractvalue %Value %vrv1751, 1
  %union_tag_match754 = icmp eq i32 %union_tag752, 1
  br i1 %union_tag_match754, label %tag_matches755, label %tag_mismatch756

tag_matches755:                                   ; preds = %ifcont750
  %payload_str_eq758 = call i1 @qc_string_eq(ptr %union_data753, ptr @.str.208)
  br label %cmp_end757

tag_mismatch756:                                  ; preds = %ifcont750
  br label %cmp_end757

cmp_end757:                                       ; preds = %tag_mismatch756, %tag_matches755
  %cmp_result759 = phi i1 [ %payload_str_eq758, %tag_matches755 ], [ false, %tag_mismatch756 ]
  %177 = xor i1 %cmp_result759, true
  br i1 %177, label %then760, label %ifcont761

then760:                                          ; preds = %cmp_end757
  call void @qc_println(ptr @.str.209)
  br label %ifcont761

ifcont761:                                        ; preds = %then760, %cmp_end757
  %vrv2762 = load %Value, ptr %vrv2, align 8
  %union_tag763 = extractvalue %Value %vrv2762, 0
  %union_data764 = extractvalue %Value %vrv2762, 1
  %union_tag_match765 = icmp eq i32 %union_tag763, 0
  br i1 %union_tag_match765, label %tag_matches766, label %tag_mismatch767

tag_matches766:                                   ; preds = %ifcont761
  %union_payload769 = load i32, ptr %union_data764, align 4
  %union_int_eq770 = icmp eq i32 %union_payload769, 999
  br label %cmp_end768

tag_mismatch767:                                  ; preds = %ifcont761
  br label %cmp_end768

cmp_end768:                                       ; preds = %tag_mismatch767, %tag_matches766
  %cmp_result771 = phi i1 [ %union_int_eq770, %tag_matches766 ], [ false, %tag_mismatch767 ]
  %178 = xor i1 %cmp_result771, true
  br i1 %178, label %then772, label %ifcont773

then772:                                          ; preds = %cmp_end768
  call void @qc_println(ptr @.str.210)
  br label %ifcont773

ifcont773:                                        ; preds = %then772, %cmp_end768
  call void @qc_println(ptr @.str.211)
  %union_heap774 = call ptr @malloc(i64 4)
  store i32 1, ptr %union_heap774, align 4
  %179 = insertvalue %Multi { i32 0, ptr undef }, ptr %union_heap774, 1
  store %Multi %179, ptr %mrv, align 8
  call void @qc_print_string(ptr @.str.212)
  %mrv775 = load %Multi, ptr %mrv, align 8
  %union_tag776 = extractvalue %Multi %mrv775, 0
  %union_payload777 = extractvalue %Multi %mrv775, 1
  switch i32 %union_tag776, label %print_union_end778 [
    i32 0, label %print_case_0779
    i32 1, label %print_case_1780
    i32 2, label %print_case_2781
    i32 3, label %print_case_3
    i32 4, label %print_case_4
  ]

print_union_end778:                               ; preds = %print_case_4, %print_case_3, %print_case_2781, %print_case_1780, %print_case_0779, %ifcont773
  call void @qc_print_char(i8 10)
  store %Multi { i32 3, ptr @.str.213 }, ptr %mrv, align 8
  call void @qc_print_string(ptr @.str.214)
  %mrv782 = load %Multi, ptr %mrv, align 8
  %union_tag783 = extractvalue %Multi %mrv782, 0
  %union_payload784 = extractvalue %Multi %mrv782, 1
  switch i32 %union_tag783, label %print_union_end785 [
    i32 0, label %print_case_0786
    i32 1, label %print_case_1787
    i32 2, label %print_case_2788
    i32 3, label %print_case_3789
    i32 4, label %print_case_4790
  ]

print_case_0779:                                  ; preds = %ifcont773
  %180 = load i32, ptr %union_payload777, align 4
  call void @qc_print_int(i32 %180)
  br label %print_union_end778

print_case_1780:                                  ; preds = %ifcont773
  %181 = load i32, ptr %union_payload777, align 4
  call void @qc_print_int(i32 %181)
  br label %print_union_end778

print_case_2781:                                  ; preds = %ifcont773
  %182 = load i32, ptr %union_payload777, align 4
  call void @qc_print_int(i32 %182)
  br label %print_union_end778

print_case_3:                                     ; preds = %ifcont773
  %183 = load ptr, ptr %union_payload777, align 8
  call void @qc_print_string(ptr %union_payload777)
  br label %print_union_end778

print_case_4:                                     ; preds = %ifcont773
  %184 = load i1, ptr %union_payload777, align 1
  call void @qc_print_bool(i1 %184)
  br label %print_union_end778

print_union_end785:                               ; preds = %print_case_4790, %print_case_3789, %print_case_2788, %print_case_1787, %print_case_0786, %print_union_end778
  call void @qc_print_char(i8 10)
  %union_heap791 = call ptr @malloc(i64 1)
  store i1 true, ptr %union_heap791, align 1
  %185 = insertvalue %Multi { i32 4, ptr undef }, ptr %union_heap791, 1
  store %Multi %185, ptr %mrv, align 8
  call void @qc_print_string(ptr @.str.215)
  %mrv792 = load %Multi, ptr %mrv, align 8
  %union_tag793 = extractvalue %Multi %mrv792, 0
  %union_payload794 = extractvalue %Multi %mrv792, 1
  switch i32 %union_tag793, label %print_union_end795 [
    i32 0, label %print_case_0796
    i32 1, label %print_case_1797
    i32 2, label %print_case_2798
    i32 3, label %print_case_3799
    i32 4, label %print_case_4800
  ]

print_case_0786:                                  ; preds = %print_union_end778
  %186 = load i32, ptr %union_payload784, align 4
  call void @qc_print_int(i32 %186)
  br label %print_union_end785

print_case_1787:                                  ; preds = %print_union_end778
  %187 = load i32, ptr %union_payload784, align 4
  call void @qc_print_int(i32 %187)
  br label %print_union_end785

print_case_2788:                                  ; preds = %print_union_end778
  %188 = load i32, ptr %union_payload784, align 4
  call void @qc_print_int(i32 %188)
  br label %print_union_end785

print_case_3789:                                  ; preds = %print_union_end778
  %189 = load ptr, ptr %union_payload784, align 8
  call void @qc_print_string(ptr %union_payload784)
  br label %print_union_end785

print_case_4790:                                  ; preds = %print_union_end778
  %190 = load i1, ptr %union_payload784, align 1
  call void @qc_print_bool(i1 %190)
  br label %print_union_end785

print_union_end795:                               ; preds = %print_case_4800, %print_case_3799, %print_case_2798, %print_case_1797, %print_case_0796, %print_union_end785
  call void @qc_print_char(i8 10)
  %union_heap801 = call ptr @malloc(i64 4)
  store i32 3, ptr %union_heap801, align 4
  %191 = insertvalue %Multi { i32 2, ptr undef }, ptr %union_heap801, 1
  store %Multi %191, ptr %mrv, align 8
  call void @qc_print_string(ptr @.str.216)
  %mrv802 = load %Multi, ptr %mrv, align 8
  %union_tag803 = extractvalue %Multi %mrv802, 0
  %union_payload804 = extractvalue %Multi %mrv802, 1
  switch i32 %union_tag803, label %print_union_end805 [
    i32 0, label %print_case_0806
    i32 1, label %print_case_1807
    i32 2, label %print_case_2808
    i32 3, label %print_case_3809
    i32 4, label %print_case_4810
  ]

print_case_0796:                                  ; preds = %print_union_end785
  %192 = load i32, ptr %union_payload794, align 4
  call void @qc_print_int(i32 %192)
  br label %print_union_end795

print_case_1797:                                  ; preds = %print_union_end785
  %193 = load i32, ptr %union_payload794, align 4
  call void @qc_print_int(i32 %193)
  br label %print_union_end795

print_case_2798:                                  ; preds = %print_union_end785
  %194 = load i32, ptr %union_payload794, align 4
  call void @qc_print_int(i32 %194)
  br label %print_union_end795

print_case_3799:                                  ; preds = %print_union_end785
  %195 = load ptr, ptr %union_payload794, align 8
  call void @qc_print_string(ptr %union_payload794)
  br label %print_union_end795

print_case_4800:                                  ; preds = %print_union_end785
  %196 = load i1, ptr %union_payload794, align 1
  call void @qc_print_bool(i1 %196)
  br label %print_union_end795

print_union_end805:                               ; preds = %print_case_4810, %print_case_3809, %print_case_2808, %print_case_1807, %print_case_0806, %print_union_end795
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.217)
  store %Status { i32 0, ptr @.str.218 }, ptr %srvrv, align 8
  %srvrv811 = load %Status, ptr %srvrv, align 8
  %union_tag812 = extractvalue %Status %srvrv811, 0
  %union_data813 = extractvalue %Status %srvrv811, 1
  %union_tag_match814 = icmp eq i32 %union_tag812, 0
  br i1 %union_tag_match814, label %tag_matches815, label %tag_mismatch816

print_case_0806:                                  ; preds = %print_union_end795
  %197 = load i32, ptr %union_payload804, align 4
  call void @qc_print_int(i32 %197)
  br label %print_union_end805

print_case_1807:                                  ; preds = %print_union_end795
  %198 = load i32, ptr %union_payload804, align 4
  call void @qc_print_int(i32 %198)
  br label %print_union_end805

print_case_2808:                                  ; preds = %print_union_end795
  %199 = load i32, ptr %union_payload804, align 4
  call void @qc_print_int(i32 %199)
  br label %print_union_end805

print_case_3809:                                  ; preds = %print_union_end795
  %200 = load ptr, ptr %union_payload804, align 8
  call void @qc_print_string(ptr %union_payload804)
  br label %print_union_end805

print_case_4810:                                  ; preds = %print_union_end795
  %201 = load i1, ptr %union_payload804, align 1
  call void @qc_print_bool(i1 %201)
  br label %print_union_end805

tag_matches815:                                   ; preds = %print_union_end805
  br label %cmp_end817

tag_mismatch816:                                  ; preds = %print_union_end805
  br label %cmp_end817

cmp_end817:                                       ; preds = %tag_mismatch816, %tag_matches815
  %cmp_result818 = phi i1 [ true, %tag_matches815 ], [ false, %tag_mismatch816 ]
  br i1 %cmp_result818, label %then819, label %ifcont820

then819:                                          ; preds = %cmp_end817
  call void @qc_println(ptr @.str.220)
  store %Status { i32 1, ptr @.str.221 }, ptr %srvrv, align 8
  br label %ifcont820

ifcont820:                                        ; preds = %then819, %cmp_end817
  %srvrv821 = load %Status, ptr %srvrv, align 8
  %union_tag822 = extractvalue %Status %srvrv821, 0
  %union_data823 = extractvalue %Status %srvrv821, 1
  %union_tag_match824 = icmp eq i32 %union_tag822, 1
  br i1 %union_tag_match824, label %tag_matches825, label %tag_mismatch826

tag_matches825:                                   ; preds = %ifcont820
  br label %cmp_end827

tag_mismatch826:                                  ; preds = %ifcont820
  br label %cmp_end827

cmp_end827:                                       ; preds = %tag_mismatch826, %tag_matches825
  %cmp_result828 = phi i1 [ true, %tag_matches825 ], [ false, %tag_mismatch826 ]
  br i1 %cmp_result828, label %then829, label %ifcont830

then829:                                          ; preds = %cmp_end827
  call void @qc_println(ptr @.str.223)
  br label %ifcont830

ifcont830:                                        ; preds = %then829, %cmp_end827
  call void @qc_println(ptr @.str.224)
  %union_heap831 = call ptr @malloc(i64 4)
  store i32 200, ptr %union_heap831, align 4
  %202 = insertvalue %Code { i32 0, ptr undef }, ptr %union_heap831, 1
  store %Code %202, ptr %codeValue, align 8
  %codeValue832 = load %Code, ptr %codeValue, align 8
  %union_tag833 = extractvalue %Code %codeValue832, 0
  %union_data834 = extractvalue %Code %codeValue832, 1
  %union_tag_match835 = icmp eq i32 %union_tag833, 0
  br i1 %union_tag_match835, label %tag_matches836, label %tag_mismatch837

tag_matches836:                                   ; preds = %ifcont830
  br label %cmp_end838

tag_mismatch837:                                  ; preds = %ifcont830
  br label %cmp_end838

cmp_end838:                                       ; preds = %tag_mismatch837, %tag_matches836
  %cmp_result839 = phi i1 [ true, %tag_matches836 ], [ false, %tag_mismatch837 ]
  br i1 %cmp_result839, label %then840, label %ifcont841

then840:                                          ; preds = %cmp_end838
  call void @qc_println(ptr @.str.225)
  br label %ifcont841

ifcont841:                                        ; preds = %then840, %cmp_end838
  %union_heap842 = call ptr @malloc(i64 4)
  store i32 404, ptr %union_heap842, align 4
  %203 = insertvalue %Code { i32 1, ptr undef }, ptr %union_heap842, 1
  store %Code %203, ptr %codeValue, align 8
  %codeValue843 = load %Code, ptr %codeValue, align 8
  %union_tag844 = extractvalue %Code %codeValue843, 0
  %union_data845 = extractvalue %Code %codeValue843, 1
  %union_tag_match846 = icmp eq i32 %union_tag844, 1
  br i1 %union_tag_match846, label %tag_matches847, label %tag_mismatch848

tag_matches847:                                   ; preds = %ifcont841
  br label %cmp_end849

tag_mismatch848:                                  ; preds = %ifcont841
  br label %cmp_end849

cmp_end849:                                       ; preds = %tag_mismatch848, %tag_matches847
  %cmp_result850 = phi i1 [ true, %tag_matches847 ], [ false, %tag_mismatch848 ]
  br i1 %cmp_result850, label %then851, label %ifcont852

then851:                                          ; preds = %cmp_end849
  call void @qc_println(ptr @.str.226)
  br label %ifcont852

ifcont852:                                        ; preds = %then851, %cmp_end849
  %union_heap853 = call ptr @malloc(i64 4)
  store i32 999, ptr %union_heap853, align 4
  %204 = insertvalue %Code { i32 3, ptr undef }, ptr %union_heap853, 1
  store %Code %204, ptr %codeValue, align 8
  call void @qc_print_string(ptr @.str.227)
  %c854 = load ptr, ptr %c526, align 8
  call void @qc_print_string(ptr %c854)
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.228)
  %union_heap855 = call ptr @malloc(i64 4)
  store i32 42, ptr %union_heap855, align 4
  %205 = insertvalue %Mixed { i32 0, ptr undef }, ptr %union_heap855, 1
  store %Mixed %205, ptr %mx1, align 8
  %union_heap856 = call ptr @malloc(i64 4)
  store float 0x40091EB860000000, ptr %union_heap856, align 4
  %206 = insertvalue %Mixed { i32 1, ptr undef }, ptr %union_heap856, 1
  store %Mixed %206, ptr %mx2, align 8
  store %Mixed { i32 2, ptr @.str.229 }, ptr %mx3, align 8
  %union_heap857 = call ptr @malloc(i64 1)
  store i1 true, ptr %union_heap857, align 1
  %207 = insertvalue %Mixed { i32 3, ptr undef }, ptr %union_heap857, 1
  store %Mixed %207, ptr %mx4, align 8
  %union_heap858 = call ptr @malloc(i64 1)
  store i8 65, ptr %union_heap858, align 1
  %208 = insertvalue %Mixed { i32 4, ptr undef }, ptr %union_heap858, 1
  store %Mixed %208, ptr %mx5, align 8
  %mx1859 = load %Mixed, ptr %mx1, align 8
  %union_tag860 = extractvalue %Mixed %mx1859, 0
  %union_payload861 = extractvalue %Mixed %mx1859, 1
  switch i32 %union_tag860, label %print_union_end862 [
    i32 0, label %print_case_0863
    i32 1, label %print_case_1864
    i32 2, label %print_case_2865
    i32 3, label %print_case_3866
    i32 4, label %print_case_4867
  ]

print_union_end862:                               ; preds = %print_case_4867, %print_case_3866, %print_case_2865, %print_case_1864, %print_case_0863, %ifcont852
  call void @qc_print_string(ptr @.str.230)
  %mx2868 = load %Mixed, ptr %mx2, align 8
  %union_tag869 = extractvalue %Mixed %mx2868, 0
  %union_payload870 = extractvalue %Mixed %mx2868, 1
  switch i32 %union_tag869, label %print_union_end871 [
    i32 0, label %print_case_0872
    i32 1, label %print_case_1873
    i32 2, label %print_case_2874
    i32 3, label %print_case_3875
    i32 4, label %print_case_4876
  ]

print_case_0863:                                  ; preds = %ifcont852
  %209 = load i32, ptr %union_payload861, align 4
  call void @qc_print_int(i32 %209)
  br label %print_union_end862

print_case_1864:                                  ; preds = %ifcont852
  %210 = load float, ptr %union_payload861, align 4
  call void @qc_print_float(float %210)
  br label %print_union_end862

print_case_2865:                                  ; preds = %ifcont852
  %211 = load ptr, ptr %union_payload861, align 8
  call void @qc_print_string(ptr %union_payload861)
  br label %print_union_end862

print_case_3866:                                  ; preds = %ifcont852
  %212 = load i1, ptr %union_payload861, align 1
  call void @qc_print_bool(i1 %212)
  br label %print_union_end862

print_case_4867:                                  ; preds = %ifcont852
  %213 = load i8, ptr %union_payload861, align 1
  call void @qc_print_char(i8 %213)
  br label %print_union_end862

print_union_end871:                               ; preds = %print_case_4876, %print_case_3875, %print_case_2874, %print_case_1873, %print_case_0872, %print_union_end862
  call void @qc_print_string(ptr @.str.231)
  %mx3877 = load %Mixed, ptr %mx3, align 8
  %union_tag878 = extractvalue %Mixed %mx3877, 0
  %union_payload879 = extractvalue %Mixed %mx3877, 1
  switch i32 %union_tag878, label %print_union_end880 [
    i32 0, label %print_case_0881
    i32 1, label %print_case_1882
    i32 2, label %print_case_2883
    i32 3, label %print_case_3884
    i32 4, label %print_case_4885
  ]

print_case_0872:                                  ; preds = %print_union_end862
  %214 = load i32, ptr %union_payload870, align 4
  call void @qc_print_int(i32 %214)
  br label %print_union_end871

print_case_1873:                                  ; preds = %print_union_end862
  %215 = load float, ptr %union_payload870, align 4
  call void @qc_print_float(float %215)
  br label %print_union_end871

print_case_2874:                                  ; preds = %print_union_end862
  %216 = load ptr, ptr %union_payload870, align 8
  call void @qc_print_string(ptr %union_payload870)
  br label %print_union_end871

print_case_3875:                                  ; preds = %print_union_end862
  %217 = load i1, ptr %union_payload870, align 1
  call void @qc_print_bool(i1 %217)
  br label %print_union_end871

print_case_4876:                                  ; preds = %print_union_end862
  %218 = load i8, ptr %union_payload870, align 1
  call void @qc_print_char(i8 %218)
  br label %print_union_end871

print_union_end880:                               ; preds = %print_case_4885, %print_case_3884, %print_case_2883, %print_case_1882, %print_case_0881, %print_union_end871
  call void @qc_print_string(ptr @.str.232)
  %mx4886 = load %Mixed, ptr %mx4, align 8
  %union_tag887 = extractvalue %Mixed %mx4886, 0
  %union_payload888 = extractvalue %Mixed %mx4886, 1
  switch i32 %union_tag887, label %print_union_end889 [
    i32 0, label %print_case_0890
    i32 1, label %print_case_1891
    i32 2, label %print_case_2892
    i32 3, label %print_case_3893
    i32 4, label %print_case_4894
  ]

print_case_0881:                                  ; preds = %print_union_end871
  %219 = load i32, ptr %union_payload879, align 4
  call void @qc_print_int(i32 %219)
  br label %print_union_end880

print_case_1882:                                  ; preds = %print_union_end871
  %220 = load float, ptr %union_payload879, align 4
  call void @qc_print_float(float %220)
  br label %print_union_end880

print_case_2883:                                  ; preds = %print_union_end871
  %221 = load ptr, ptr %union_payload879, align 8
  call void @qc_print_string(ptr %union_payload879)
  br label %print_union_end880

print_case_3884:                                  ; preds = %print_union_end871
  %222 = load i1, ptr %union_payload879, align 1
  call void @qc_print_bool(i1 %222)
  br label %print_union_end880

print_case_4885:                                  ; preds = %print_union_end871
  %223 = load i8, ptr %union_payload879, align 1
  call void @qc_print_char(i8 %223)
  br label %print_union_end880

print_union_end889:                               ; preds = %print_case_4894, %print_case_3893, %print_case_2892, %print_case_1891, %print_case_0890, %print_union_end880
  call void @qc_print_string(ptr @.str.233)
  %mx5895 = load %Mixed, ptr %mx5, align 8
  %union_tag896 = extractvalue %Mixed %mx5895, 0
  %union_payload897 = extractvalue %Mixed %mx5895, 1
  switch i32 %union_tag896, label %print_union_end898 [
    i32 0, label %print_case_0899
    i32 1, label %print_case_1900
    i32 2, label %print_case_2901
    i32 3, label %print_case_3902
    i32 4, label %print_case_4903
  ]

print_case_0890:                                  ; preds = %print_union_end880
  %224 = load i32, ptr %union_payload888, align 4
  call void @qc_print_int(i32 %224)
  br label %print_union_end889

print_case_1891:                                  ; preds = %print_union_end880
  %225 = load float, ptr %union_payload888, align 4
  call void @qc_print_float(float %225)
  br label %print_union_end889

print_case_2892:                                  ; preds = %print_union_end880
  %226 = load ptr, ptr %union_payload888, align 8
  call void @qc_print_string(ptr %union_payload888)
  br label %print_union_end889

print_case_3893:                                  ; preds = %print_union_end880
  %227 = load i1, ptr %union_payload888, align 1
  call void @qc_print_bool(i1 %227)
  br label %print_union_end889

print_case_4894:                                  ; preds = %print_union_end880
  %228 = load i8, ptr %union_payload888, align 1
  call void @qc_print_char(i8 %228)
  br label %print_union_end889

print_union_end898:                               ; preds = %print_case_4903, %print_case_3902, %print_case_2901, %print_case_1900, %print_case_0899, %print_union_end889
  call void @qc_print_char(i8 10)
  call void @qc_println(ptr @.str.234)
  %union_heap904 = call ptr @malloc(i64 4)
  store i32 10, ptr %union_heap904, align 4
  %229 = insertvalue %Pair { i32 0, ptr undef }, ptr %union_heap904, 1
  store %Pair %229, ptr %p1, align 8
  %union_heap905 = call ptr @malloc(i64 4)
  store i32 10, ptr %union_heap905, align 4
  %230 = insertvalue %Pair { i32 0, ptr undef }, ptr %union_heap905, 1
  store %Pair %230, ptr %p2222, align 8
  %union_heap906 = call ptr @malloc(i64 4)
  store i32 20, ptr %union_heap906, align 4
  %231 = insertvalue %Pair { i32 0, ptr undef }, ptr %union_heap906, 1
  store %Pair %231, ptr %p3, align 8
  %p1907 = load %Pair, ptr %p1, align 8
  %p2222908 = load %Pair, ptr %p2222, align 8
  %lhs_tag = extractvalue %Pair %p1907, 0
  %rhs_tag = extractvalue %Pair %p2222908, 0
  %tags_equal = icmp eq i32 %lhs_tag, %rhs_tag
  br i1 %tags_equal, label %tags_match, label %tags_mismatch

print_case_0899:                                  ; preds = %print_union_end889
  %232 = load i32, ptr %union_payload897, align 4
  call void @qc_print_int(i32 %232)
  br label %print_union_end898

print_case_1900:                                  ; preds = %print_union_end889
  %233 = load float, ptr %union_payload897, align 4
  call void @qc_print_float(float %233)
  br label %print_union_end898

print_case_2901:                                  ; preds = %print_union_end889
  %234 = load ptr, ptr %union_payload897, align 8
  call void @qc_print_string(ptr %union_payload897)
  br label %print_union_end898

print_case_3902:                                  ; preds = %print_union_end889
  %235 = load i1, ptr %union_payload897, align 1
  call void @qc_print_bool(i1 %235)
  br label %print_union_end898

print_case_4903:                                  ; preds = %print_union_end889
  %236 = load i8, ptr %union_payload897, align 1
  call void @qc_print_char(i8 %236)
  br label %print_union_end898

tags_match:                                       ; preds = %print_union_end898
  %lhs_payload = extractvalue %Pair %p1907, 1
  %rhs_payload = extractvalue %Pair %p2222908, 1
  switch i32 %lhs_tag, label %cmp_default [
    i32 0, label %cmp_case_0
    i32 1, label %cmp_case_1
  ]

tags_mismatch:                                    ; preds = %print_union_end898
  br label %union_cmp_end

union_cmp_end:                                    ; preds = %tags_mismatch, %payload_cmp_end
  %237 = phi i1 [ %238, %payload_cmp_end ], [ false, %tags_mismatch ]
  br i1 %237, label %then909, label %ifcont910

payload_cmp_end:                                  ; preds = %cmp_default, %cmp_case_1, %cmp_case_0
  %238 = phi i1 [ %241, %cmp_case_0 ], [ %242, %cmp_case_1 ], [ false, %cmp_default ]
  br label %union_cmp_end

cmp_default:                                      ; preds = %tags_match
  br label %payload_cmp_end

cmp_case_0:                                       ; preds = %tags_match
  %239 = load i32, ptr %lhs_payload, align 4
  %240 = load i32, ptr %rhs_payload, align 4
  %241 = icmp eq i32 %239, %240
  br label %payload_cmp_end

cmp_case_1:                                       ; preds = %tags_match
  %242 = call i1 @qc_string_eq(ptr %lhs_payload, ptr %rhs_payload)
  br label %payload_cmp_end

then909:                                          ; preds = %union_cmp_end
  call void @qc_println(ptr @.str.235)
  br label %ifcont910

ifcont910:                                        ; preds = %then909, %union_cmp_end
  %p1911 = load %Pair, ptr %p1, align 8
  %p3912 = load %Pair, ptr %p3, align 8
  %lhs_tag913 = extractvalue %Pair %p1911, 0
  %rhs_tag914 = extractvalue %Pair %p3912, 0
  %tags_equal915 = icmp eq i32 %lhs_tag913, %rhs_tag914
  br i1 %tags_equal915, label %tags_match916, label %tags_mismatch917

tags_match916:                                    ; preds = %ifcont910
  %lhs_payload919 = extractvalue %Pair %p1911, 1
  %rhs_payload920 = extractvalue %Pair %p3912, 1
  switch i32 %lhs_tag913, label %cmp_default922 [
    i32 0, label %cmp_case_0923
    i32 1, label %cmp_case_1924
  ]

tags_mismatch917:                                 ; preds = %ifcont910
  br label %union_cmp_end918

union_cmp_end918:                                 ; preds = %tags_mismatch917, %payload_cmp_end921
  %243 = phi i1 [ %245, %payload_cmp_end921 ], [ false, %tags_mismatch917 ]
  %244 = xor i1 %243, true
  br i1 %244, label %then925, label %ifcont926

payload_cmp_end921:                               ; preds = %cmp_default922, %cmp_case_1924, %cmp_case_0923
  %245 = phi i1 [ %248, %cmp_case_0923 ], [ %249, %cmp_case_1924 ], [ false, %cmp_default922 ]
  br label %union_cmp_end918

cmp_default922:                                   ; preds = %tags_match916
  br label %payload_cmp_end921

cmp_case_0923:                                    ; preds = %tags_match916
  %246 = load i32, ptr %lhs_payload919, align 4
  %247 = load i32, ptr %rhs_payload920, align 4
  %248 = icmp eq i32 %246, %247
  br label %payload_cmp_end921

cmp_case_1924:                                    ; preds = %tags_match916
  %249 = call i1 @qc_string_eq(ptr %lhs_payload919, ptr %rhs_payload920)
  br label %payload_cmp_end921

then925:                                          ; preds = %union_cmp_end918
  call void @qc_println(ptr @.str.236)
  br label %ifcont926

ifcont926:                                        ; preds = %then925, %union_cmp_end918
  store %Pair { i32 1, ptr @.str.237 }, ptr %p4, align 8
  store %Pair { i32 1, ptr @.str.238 }, ptr %p5, align 8
  store %Pair { i32 1, ptr @.str.239 }, ptr %p6, align 8
  %p4927 = load %Pair, ptr %p4, align 8
  %p5928 = load %Pair, ptr %p5, align 8
  %lhs_tag929 = extractvalue %Pair %p4927, 0
  %rhs_tag930 = extractvalue %Pair %p5928, 0
  %tags_equal931 = icmp eq i32 %lhs_tag929, %rhs_tag930
  br i1 %tags_equal931, label %tags_match932, label %tags_mismatch933

tags_match932:                                    ; preds = %ifcont926
  %lhs_payload935 = extractvalue %Pair %p4927, 1
  %rhs_payload936 = extractvalue %Pair %p5928, 1
  switch i32 %lhs_tag929, label %cmp_default938 [
    i32 0, label %cmp_case_0939
    i32 1, label %cmp_case_1940
  ]

tags_mismatch933:                                 ; preds = %ifcont926
  br label %union_cmp_end934

union_cmp_end934:                                 ; preds = %tags_mismatch933, %payload_cmp_end937
  %250 = phi i1 [ %251, %payload_cmp_end937 ], [ false, %tags_mismatch933 ]
  br i1 %250, label %then941, label %ifcont942

payload_cmp_end937:                               ; preds = %cmp_default938, %cmp_case_1940, %cmp_case_0939
  %251 = phi i1 [ %254, %cmp_case_0939 ], [ %255, %cmp_case_1940 ], [ false, %cmp_default938 ]
  br label %union_cmp_end934

cmp_default938:                                   ; preds = %tags_match932
  br label %payload_cmp_end937

cmp_case_0939:                                    ; preds = %tags_match932
  %252 = load i32, ptr %lhs_payload935, align 4
  %253 = load i32, ptr %rhs_payload936, align 4
  %254 = icmp eq i32 %252, %253
  br label %payload_cmp_end937

cmp_case_1940:                                    ; preds = %tags_match932
  %255 = call i1 @qc_string_eq(ptr %lhs_payload935, ptr %rhs_payload936)
  br label %payload_cmp_end937

then941:                                          ; preds = %union_cmp_end934
  call void @qc_println(ptr @.str.240)
  br label %ifcont942

ifcont942:                                        ; preds = %then941, %union_cmp_end934
  %p4943 = load %Pair, ptr %p4, align 8
  %p6944 = load %Pair, ptr %p6, align 8
  %lhs_tag945 = extractvalue %Pair %p4943, 0
  %rhs_tag946 = extractvalue %Pair %p6944, 0
  %tags_equal947 = icmp eq i32 %lhs_tag945, %rhs_tag946
  br i1 %tags_equal947, label %tags_match948, label %tags_mismatch949

tags_match948:                                    ; preds = %ifcont942
  %lhs_payload951 = extractvalue %Pair %p4943, 1
  %rhs_payload952 = extractvalue %Pair %p6944, 1
  switch i32 %lhs_tag945, label %cmp_default954 [
    i32 0, label %cmp_case_0955
    i32 1, label %cmp_case_1956
  ]

tags_mismatch949:                                 ; preds = %ifcont942
  br label %union_cmp_end950

union_cmp_end950:                                 ; preds = %tags_mismatch949, %payload_cmp_end953
  %256 = phi i1 [ %258, %payload_cmp_end953 ], [ false, %tags_mismatch949 ]
  %257 = xor i1 %256, true
  br i1 %257, label %then957, label %ifcont958

payload_cmp_end953:                               ; preds = %cmp_default954, %cmp_case_1956, %cmp_case_0955
  %258 = phi i1 [ %261, %cmp_case_0955 ], [ %262, %cmp_case_1956 ], [ false, %cmp_default954 ]
  br label %union_cmp_end950

cmp_default954:                                   ; preds = %tags_match948
  br label %payload_cmp_end953

cmp_case_0955:                                    ; preds = %tags_match948
  %259 = load i32, ptr %lhs_payload951, align 4
  %260 = load i32, ptr %rhs_payload952, align 4
  %261 = icmp eq i32 %259, %260
  br label %payload_cmp_end953

cmp_case_1956:                                    ; preds = %tags_match948
  %262 = call i1 @qc_string_eq(ptr %lhs_payload951, ptr %rhs_payload952)
  br label %payload_cmp_end953

then957:                                          ; preds = %union_cmp_end950
  call void @qc_println(ptr @.str.241)
  br label %ifcont958

ifcont958:                                        ; preds = %then957, %union_cmp_end950
  call void @qc_println(ptr @.str.242)
  %calltmp959 = call %Response @process(i32 0)
  store %Response %calltmp959, ptr %resp1, align 8
  %resp1960 = load %Response, ptr %resp1, align 8
  %union_tag961 = extractvalue %Response %resp1960, 0
  %union_data962 = extractvalue %Response %resp1960, 1
  %union_tag_match963 = icmp eq i32 %union_tag961, 0
  br i1 %union_tag_match963, label %tag_matches964, label %tag_mismatch965

tag_matches964:                                   ; preds = %ifcont958
  br label %cmp_end966

tag_mismatch965:                                  ; preds = %ifcont958
  br label %cmp_end966

cmp_end966:                                       ; preds = %tag_mismatch965, %tag_matches964
  %cmp_result967 = phi i1 [ true, %tag_matches964 ], [ false, %tag_mismatch965 ]
  br i1 %cmp_result967, label %then968, label %ifcont969

then968:                                          ; preds = %cmp_end966
  call void @qc_println(ptr @.str.246)
  br label %ifcont969

ifcont969:                                        ; preds = %then968, %cmp_end966
  %calltmp970 = call %Response @process(i32 1)
  store %Response %calltmp970, ptr %resp2, align 8
  %resp2971 = load %Response, ptr %resp2, align 8
  %union_tag972 = extractvalue %Response %resp2971, 0
  %union_data973 = extractvalue %Response %resp2971, 1
  %union_tag_match974 = icmp eq i32 %union_tag972, 1
  br i1 %union_tag_match974, label %tag_matches975, label %tag_mismatch976

tag_matches975:                                   ; preds = %ifcont969
  br label %cmp_end977

tag_mismatch976:                                  ; preds = %ifcont969
  br label %cmp_end977

cmp_end977:                                       ; preds = %tag_mismatch976, %tag_matches975
  %cmp_result978 = phi i1 [ true, %tag_matches975 ], [ false, %tag_mismatch976 ]
  br i1 %cmp_result978, label %then979, label %ifcont980

then979:                                          ; preds = %cmp_end977
  call void @qc_println(ptr @.str.248)
  br label %ifcont980

ifcont980:                                        ; preds = %then979, %cmp_end977
  %calltmp981 = call %Response @process(i32 42)
  store %Response %calltmp981, ptr %resp3, align 8
  %resp3982 = load %Response, ptr %resp3, align 8
  %union_tag983 = extractvalue %Response %resp3982, 0
  %union_data984 = extractvalue %Response %resp3982, 1
  %union_tag_match985 = icmp eq i32 %union_tag983, 2
  br i1 %union_tag_match985, label %tag_matches986, label %tag_mismatch987

tag_matches986:                                   ; preds = %ifcont980
  %union_payload989 = load i32, ptr %union_data984, align 4
  %union_int_eq990 = icmp eq i32 %union_payload989, 42
  br label %cmp_end988

tag_mismatch987:                                  ; preds = %ifcont980
  br label %cmp_end988

cmp_end988:                                       ; preds = %tag_mismatch987, %tag_matches986
  %cmp_result991 = phi i1 [ %union_int_eq990, %tag_matches986 ], [ false, %tag_mismatch987 ]
  br i1 %cmp_result991, label %then992, label %ifcont993

then992:                                          ; preds = %cmp_end988
  call void @qc_println(ptr @.str.249)
  br label %ifcont993

ifcont993:                                        ; preds = %then992, %cmp_end988
  call void @qc_println(ptr @.str.250)
  call void @qc_println(ptr @.str.251)
  store i32 0, ptr %aaaaa, align 4
  store i32 0, ptr %bbbbb, align 4
  store i32 0, ptr %ccccc, align 4
  store i32 0, ptr %ddddd, align 4
  call void @qc_print_string(ptr @.str.252)
  %qin_input = call ptr @qc_qin()
  %263 = call i32 @qc_to_int_from_string(ptr %qin_input)
  store i32 %263, ptr %aaaaa, align 4
  %qin_input994 = call ptr @qc_qin()
  %264 = call i32 @qc_to_int_from_string(ptr %qin_input994)
  store i32 %264, ptr %bbbbb, align 4
  call void @qc_print_string(ptr @.str.253)
  %qin_input995 = call ptr @qc_qin()
  %265 = call i32 @qc_to_int_from_string(ptr %qin_input995)
  store i32 %265, ptr %ccccc, align 4
  %qin_input996 = call ptr @qc_qin()
  %266 = call i32 @qc_to_int_from_string(ptr %qin_input996)
  store i32 %266, ptr %ddddd, align 4
  %aaaaa997 = load i32, ptr %aaaaa, align 4
  %ccccc998 = load i32, ptr %ccccc, align 4
  %icmplt999 = icmp slt i32 %aaaaa997, %ccccc998
  %bbbbb1000 = load i32, ptr %bbbbb, align 4
  %ccccc1001 = load i32, ptr %ccccc, align 4
  %icmplt1002 = icmp slt i32 %bbbbb1000, %ccccc1001
  %and1003 = and i1 %icmplt999, %icmplt1002
  %ccccc1004 = load i32, ptr %ccccc, align 4
  %aaaaa1005 = load i32, ptr %aaaaa, align 4
  %icmplt1006 = icmp slt i32 %ccccc1004, %aaaaa1005
  %ddddd1007 = load i32, ptr %ddddd, align 4
  %aaaaa1008 = load i32, ptr %aaaaa, align 4
  %icmplt1009 = icmp slt i32 %ddddd1007, %aaaaa1008
  %and1010 = and i1 %icmplt1006, %icmplt1009
  %or1011 = or i1 %and1003, %and1010
  br i1 %or1011, label %then1012, label %elif.cond

then1012:                                         ; preds = %ifcont993
  %bbbbb1015 = load i32, ptr %bbbbb, align 4
  %aaaaa1016 = load i32, ptr %aaaaa, align 4
  %sub1017 = sub i32 %bbbbb1015, %aaaaa1016
  %ddddd1018 = load i32, ptr %ddddd, align 4
  %add1019 = add i32 %sub1017, %ddddd1018
  %ccccc1020 = load i32, ptr %ccccc, align 4
  %sub1021 = sub i32 %add1019, %ccccc1020
  call void @qc_print_int(i32 %sub1021)
  br label %ifcont1013

ifcont1013:                                       ; preds = %ifcont1041, %ifcont1029, %then1012
  call void @qc_println(ptr @.str.254)
  call void @qc_println(ptr @.str.255)
  call void @qc_println(ptr @.str.256)
  %fopen_result = call ptr @qc_fopen(ptr @.str.257, ptr @.str.258)
  store ptr %fopen_result, ptr %outFile, align 8
  %outFile1049 = load ptr, ptr %outFile, align 8
  call void @qc_fwrite(ptr %outFile1049, ptr @.str.259)
  %outFile1050 = load ptr, ptr %outFile, align 8
  call void @qc_fwrite(ptr %outFile1050, ptr @.str.260)
  %outFile1051 = load ptr, ptr %outFile, align 8
  call void @qc_fwrite(ptr %outFile1051, ptr @.str.261)
  %outFile1052 = load ptr, ptr %outFile, align 8
  call void @qc_fclose(ptr %outFile1052)
  call void @qc_println(ptr @.str.262)
  call void @qc_println(ptr @.str.263)
  %fopen_result1053 = call ptr @qc_fopen(ptr @.str.264, ptr @.str.265)
  store ptr %fopen_result1053, ptr %inFile, align 8
  %inFile1054 = load ptr, ptr %inFile, align 8
  %fread_result = call ptr @qc_fread(ptr %inFile1054)
  store ptr %fread_result, ptr %line1, align 8
  %inFile1055 = load ptr, ptr %inFile, align 8
  %fread_result1056 = call ptr @qc_fread(ptr %inFile1055)
  store ptr %fread_result1056, ptr %line2, align 8
  %inFile1057 = load ptr, ptr %inFile, align 8
  %fread_result1058 = call ptr @qc_fread(ptr %inFile1057)
  store ptr %fread_result1058, ptr %line3, align 8
  %inFile1059 = load ptr, ptr %inFile, align 8
  call void @qc_fclose(ptr %inFile1059)
  call void @qc_println(ptr @.str.266)
  %line11060 = load ptr, ptr %line1, align 8
  call void @qc_println(ptr %line11060)
  %line21061 = load ptr, ptr %line2, align 8
  call void @qc_println(ptr %line21061)
  %line31062 = load ptr, ptr %line3, align 8
  call void @qc_println(ptr %line31062)
  call void @qc_println(ptr @.str.267)
  %fopen_result1063 = call ptr @qc_fopen(ptr @.str.268, ptr @.str.269)
  store ptr %fopen_result1063, ptr %appendFile, align 8
  %appendFile1064 = load ptr, ptr %appendFile, align 8
  call void @qc_fwrite(ptr %appendFile1064, ptr @.str.270)
  %appendFile1065 = load ptr, ptr %appendFile, align 8
  call void @qc_fclose(ptr %appendFile1065)
  %fopen_result1066 = call ptr @qc_fopen(ptr @.str.271, ptr @.str.272)
  store ptr %fopen_result1066, ptr %readAgain, align 8
  call void @qc_println(ptr @.str.273)
  store ptr @.str.274, ptr %line, align 8
  %line1067 = load ptr, ptr %line, align 8
  %readAgain1068 = load ptr, ptr %readAgain, align 8
  %fread_result1069 = call ptr @qc_fread(ptr %readAgain1068)
  store ptr %fread_result1069, ptr %line, align 8
  br label %while.cond1070

elif.cond:                                        ; preds = %ifcont993
  %aaaaa1022 = load i32, ptr %aaaaa, align 4
  %ccccc1023 = load i32, ptr %ccccc, align 4
  %icmplt1024 = icmp slt i32 %aaaaa1022, %ccccc1023
  br i1 %icmplt1024, label %elif.body, label %else1014

elif.body:                                        ; preds = %elif.cond
  %bbbbb1025 = load i32, ptr %bbbbb, align 4
  %ddddd1026 = load i32, ptr %ddddd, align 4
  %icmplt1027 = icmp slt i32 %bbbbb1025, %ddddd1026
  br i1 %icmplt1027, label %then1028, label %else1030

else1014:                                         ; preds = %elif.cond
  %bbbbb1037 = load i32, ptr %bbbbb, align 4
  %ddddd1038 = load i32, ptr %ddddd, align 4
  %icmplt1039 = icmp slt i32 %bbbbb1037, %ddddd1038
  br i1 %icmplt1039, label %then1040, label %else1042

then1028:                                         ; preds = %elif.body
  %ddddd1031 = load i32, ptr %ddddd, align 4
  %aaaaa1032 = load i32, ptr %aaaaa, align 4
  %sub1033 = sub i32 %ddddd1031, %aaaaa1032
  call void @qc_print_int(i32 %sub1033)
  br label %ifcont1029

ifcont1029:                                       ; preds = %else1030, %then1028
  br label %ifcont1013

else1030:                                         ; preds = %elif.body
  %bbbbb1034 = load i32, ptr %bbbbb, align 4
  %aaaaa1035 = load i32, ptr %aaaaa, align 4
  %sub1036 = sub i32 %bbbbb1034, %aaaaa1035
  call void @qc_print_int(i32 %sub1036)
  br label %ifcont1029

then1040:                                         ; preds = %else1014
  %ddddd1043 = load i32, ptr %ddddd, align 4
  %ccccc1044 = load i32, ptr %ccccc, align 4
  %sub1045 = sub i32 %ddddd1043, %ccccc1044
  call void @qc_print_int(i32 %sub1045)
  br label %ifcont1041

ifcont1041:                                       ; preds = %else1042, %then1040
  br label %ifcont1013

else1042:                                         ; preds = %else1014
  %bbbbb1046 = load i32, ptr %bbbbb, align 4
  %ccccc1047 = load i32, ptr %ccccc, align 4
  %sub1048 = sub i32 %bbbbb1046, %ccccc1047
  call void @qc_print_int(i32 %sub1048)
  br label %ifcont1041

while.cond1070:                                   ; preds = %while.body1071, %ifcont1013
  %line1073 = load ptr, ptr %line, align 8
  %267 = call i1 @qc_string_eq(ptr %line1073, ptr @.str.275)
  %268 = xor i1 %267, true
  br i1 %268, label %while.body1071, label %while.end1072

while.body1071:                                   ; preds = %while.cond1070
  %line1074 = load ptr, ptr %line, align 8
  call void @qc_println(ptr %line1074)
  %line1075 = load ptr, ptr %line, align 8
  %readAgain1076 = load ptr, ptr %readAgain, align 8
  %fread_result1077 = call ptr @qc_fread(ptr %readAgain1076)
  store ptr %fread_result1077, ptr %line, align 8
  br label %while.cond1070

while.end1072:                                    ; preds = %while.cond1070
  %readAgain1078 = load ptr, ptr %readAgain, align 8
  call void @qc_fclose(ptr %readAgain1078)
  call void @qc_println(ptr @.str.276)
  call void @qc_println(ptr @.str.277)
  call void @qc_println(ptr @.str.278)
  store i32 42, ptr %xxxxxxxx, align 4
  store ptr @.str.279, ptr %sxxxxxx, align 8
  store float 0x40091EB860000000, ptr %fxxxxxx, align 4
  %xxxxxxxx1079 = load i32, ptr %xxxxxxxx, align 4
  %to_str1080 = call ptr @qc_to_string_int(i32 %xxxxxxxx1079)
  %str_concat = call ptr @qc_string_concat(ptr @.str.280, ptr %to_str1080)
  call void @qc_println(ptr %str_concat)
  %sxxxxxx1081 = load ptr, ptr %sxxxxxx, align 8
  %str_concat1082 = call ptr @qc_string_concat(ptr @.str.281, ptr %sxxxxxx1081)
  call void @qc_println(ptr %str_concat1082)
  %fxxxxxx1083 = load float, ptr %fxxxxxx, align 4
  %to_str1084 = call ptr @qc_to_string_float(float %fxxxxxx1083)
  %str_concat1085 = call ptr @qc_string_concat(ptr @.str.282, ptr %to_str1084)
  call void @qc_println(ptr %str_concat1085)
  call void @qc_println(ptr @.str.283)
  call void @qc_println(ptr @.str.284)
  call void @qc_println(ptr @.str.285)
  store i32 200, ptr %enum_int, align 4
  %269 = insertvalue %HttpStatus { i32 0, ptr undef }, ptr %enum_int, 1
  store %HttpStatus %269, ptr %statusCode, align 8
  call void @qc_println(ptr @.str.286)
  store i32 404, ptr %enum_int1086, align 4
  %270 = insertvalue %HttpStatus { i32 1, ptr undef }, ptr %enum_int1086, 1
  store %HttpStatus %270, ptr %statusCode, align 8
  call void @qc_println(ptr @.str.287)
  call void @qc_println(ptr @.str.288)
  store %TierLevel { i32 0, ptr @13 }, ptr %userTier, align 8
  call void @qc_println(ptr @.str.289)
  store %TierLevel { i32 1, ptr @14 }, ptr %userTier, align 8
  call void @qc_println(ptr @.str.290)
  call void @qc_println(ptr @.str.291)
  store i32 3, ptr %enum_int1087, align 4
  %271 = insertvalue %ConfigValue { i32 0, ptr undef }, ptr %enum_int1087, 1
  store %ConfigValue %271, ptr %retries, align 8
  call void @qc_println(ptr @.str.292)
  store %ConfigValue { i32 1, ptr @15 }, ptr %msg, align 8
  call void @qc_println(ptr @.str.293)
  call void @qc_println(ptr @.str.294)
  store i32 200, ptr %enum_int1088, align 4
  %272 = insertvalue %HttpStatus { i32 0, ptr undef }, ptr %enum_int1088, 1
  store %HttpStatus %272, ptr %status1, align 8
  store i32 200, ptr %enum_int1089, align 4
  %273 = insertvalue %HttpStatus { i32 0, ptr undef }, ptr %enum_int1089, 1
  store %HttpStatus %273, ptr %status2, align 8
  %status11090 = load %HttpStatus, ptr %status1, align 8
  store i32 200, ptr %enum_int1091, align 4
  %274 = insertvalue %HttpStatus { i32 0, ptr undef }, ptr %enum_int1091, 1
  %lhs_tag1092 = extractvalue %HttpStatus %status11090, 0
  %rhs_tag1093 = extractvalue %HttpStatus %274, 0
  %tags_equal1094 = icmp eq i32 %lhs_tag1092, %rhs_tag1093
  br i1 %tags_equal1094, label %tags_match1095, label %tags_mismatch1096

tags_match1095:                                   ; preds = %while.end1072
  %lhs_payload1098 = extractvalue %HttpStatus %status11090, 1
  %rhs_payload1099 = extractvalue %HttpStatus %274, 1
  switch i32 %lhs_tag1092, label %cmp_default1101 [
    i32 0, label %cmp_case_01102
    i32 1, label %cmp_case_11103
    i32 2, label %cmp_case_2
  ]

tags_mismatch1096:                                ; preds = %while.end1072
  br label %union_cmp_end1097

union_cmp_end1097:                                ; preds = %tags_mismatch1096, %payload_cmp_end1100
  %275 = phi i1 [ %276, %payload_cmp_end1100 ], [ false, %tags_mismatch1096 ]
  br i1 %275, label %then1104, label %ifcont1105

payload_cmp_end1100:                              ; preds = %cmp_default1101, %cmp_case_2, %cmp_case_11103, %cmp_case_01102
  %276 = phi i1 [ %279, %cmp_case_01102 ], [ %282, %cmp_case_11103 ], [ %285, %cmp_case_2 ], [ false, %cmp_default1101 ]
  br label %union_cmp_end1097

cmp_default1101:                                  ; preds = %tags_match1095
  br label %payload_cmp_end1100

cmp_case_01102:                                   ; preds = %tags_match1095
  %277 = load i32, ptr %lhs_payload1098, align 4
  %278 = load i32, ptr %rhs_payload1099, align 4
  %279 = icmp eq i32 %277, %278
  br label %payload_cmp_end1100

cmp_case_11103:                                   ; preds = %tags_match1095
  %280 = load i32, ptr %lhs_payload1098, align 4
  %281 = load i32, ptr %rhs_payload1099, align 4
  %282 = icmp eq i32 %280, %281
  br label %payload_cmp_end1100

cmp_case_2:                                       ; preds = %tags_match1095
  %283 = load i32, ptr %lhs_payload1098, align 4
  %284 = load i32, ptr %rhs_payload1099, align 4
  %285 = icmp eq i32 %283, %284
  br label %payload_cmp_end1100

then1104:                                         ; preds = %union_cmp_end1097
  call void @qc_println(ptr @.str.295)
  br label %ifcont1105

ifcont1105:                                       ; preds = %then1104, %union_cmp_end1097
  %status11106 = load %HttpStatus, ptr %status1, align 8
  %status21107 = load %HttpStatus, ptr %status2, align 8
  %lhs_tag1108 = extractvalue %HttpStatus %status11106, 0
  %rhs_tag1109 = extractvalue %HttpStatus %status21107, 0
  %tags_equal1110 = icmp eq i32 %lhs_tag1108, %rhs_tag1109
  br i1 %tags_equal1110, label %tags_match1111, label %tags_mismatch1112

tags_match1111:                                   ; preds = %ifcont1105
  %lhs_payload1114 = extractvalue %HttpStatus %status11106, 1
  %rhs_payload1115 = extractvalue %HttpStatus %status21107, 1
  switch i32 %lhs_tag1108, label %cmp_default1117 [
    i32 0, label %cmp_case_01118
    i32 1, label %cmp_case_11119
    i32 2, label %cmp_case_21120
  ]

tags_mismatch1112:                                ; preds = %ifcont1105
  br label %union_cmp_end1113

union_cmp_end1113:                                ; preds = %tags_mismatch1112, %payload_cmp_end1116
  %286 = phi i1 [ %287, %payload_cmp_end1116 ], [ false, %tags_mismatch1112 ]
  br i1 %286, label %then1121, label %ifcont1122

payload_cmp_end1116:                              ; preds = %cmp_default1117, %cmp_case_21120, %cmp_case_11119, %cmp_case_01118
  %287 = phi i1 [ %290, %cmp_case_01118 ], [ %293, %cmp_case_11119 ], [ %296, %cmp_case_21120 ], [ false, %cmp_default1117 ]
  br label %union_cmp_end1113

cmp_default1117:                                  ; preds = %tags_match1111
  br label %payload_cmp_end1116

cmp_case_01118:                                   ; preds = %tags_match1111
  %288 = load i32, ptr %lhs_payload1114, align 4
  %289 = load i32, ptr %rhs_payload1115, align 4
  %290 = icmp eq i32 %288, %289
  br label %payload_cmp_end1116

cmp_case_11119:                                   ; preds = %tags_match1111
  %291 = load i32, ptr %lhs_payload1114, align 4
  %292 = load i32, ptr %rhs_payload1115, align 4
  %293 = icmp eq i32 %291, %292
  br label %payload_cmp_end1116

cmp_case_21120:                                   ; preds = %tags_match1111
  %294 = load i32, ptr %lhs_payload1114, align 4
  %295 = load i32, ptr %rhs_payload1115, align 4
  %296 = icmp eq i32 %294, %295
  br label %payload_cmp_end1116

then1121:                                         ; preds = %union_cmp_end1113
  call void @qc_println(ptr @.str.296)
  br label %ifcont1122

ifcont1122:                                       ; preds = %then1121, %union_cmp_end1113
  %status11123 = load %HttpStatus, ptr %status1, align 8
  store i32 404, ptr %enum_int1124, align 4
  %297 = insertvalue %HttpStatus { i32 1, ptr undef }, ptr %enum_int1124, 1
  %lhs_tag1125 = extractvalue %HttpStatus %status11123, 0
  %rhs_tag1126 = extractvalue %HttpStatus %297, 0
  %tags_equal1127 = icmp eq i32 %lhs_tag1125, %rhs_tag1126
  br i1 %tags_equal1127, label %tags_match1128, label %tags_mismatch1129

tags_match1128:                                   ; preds = %ifcont1122
  %lhs_payload1131 = extractvalue %HttpStatus %status11123, 1
  %rhs_payload1132 = extractvalue %HttpStatus %297, 1
  switch i32 %lhs_tag1125, label %cmp_default1134 [
    i32 0, label %cmp_case_01135
    i32 1, label %cmp_case_11136
    i32 2, label %cmp_case_21137
  ]

tags_mismatch1129:                                ; preds = %ifcont1122
  br label %union_cmp_end1130

union_cmp_end1130:                                ; preds = %tags_mismatch1129, %payload_cmp_end1133
  %298 = phi i1 [ %300, %payload_cmp_end1133 ], [ false, %tags_mismatch1129 ]
  %299 = xor i1 %298, true
  br i1 %299, label %then1138, label %ifcont1139

payload_cmp_end1133:                              ; preds = %cmp_default1134, %cmp_case_21137, %cmp_case_11136, %cmp_case_01135
  %300 = phi i1 [ %303, %cmp_case_01135 ], [ %306, %cmp_case_11136 ], [ %309, %cmp_case_21137 ], [ false, %cmp_default1134 ]
  br label %union_cmp_end1130

cmp_default1134:                                  ; preds = %tags_match1128
  br label %payload_cmp_end1133

cmp_case_01135:                                   ; preds = %tags_match1128
  %301 = load i32, ptr %lhs_payload1131, align 4
  %302 = load i32, ptr %rhs_payload1132, align 4
  %303 = icmp eq i32 %301, %302
  br label %payload_cmp_end1133

cmp_case_11136:                                   ; preds = %tags_match1128
  %304 = load i32, ptr %lhs_payload1131, align 4
  %305 = load i32, ptr %rhs_payload1132, align 4
  %306 = icmp eq i32 %304, %305
  br label %payload_cmp_end1133

cmp_case_21137:                                   ; preds = %tags_match1128
  %307 = load i32, ptr %lhs_payload1131, align 4
  %308 = load i32, ptr %rhs_payload1132, align 4
  %309 = icmp eq i32 %307, %308
  br label %payload_cmp_end1133

then1138:                                         ; preds = %union_cmp_end1130
  call void @qc_println(ptr @.str.297)
  br label %ifcont1139

ifcont1139:                                       ; preds = %then1138, %union_cmp_end1130
  call void @qc_println(ptr @.str.298)
  store %TierLevel { i32 0, ptr @16 }, ptr %currentTier, align 8
  call void @qc_println(ptr @.str.299)
  store %TierLevel { i32 2, ptr @17 }, ptr %currentTier, align 8
  call void @qc_println(ptr @.str.300)
  call void @qc_println(ptr @.str.301)
  store i32 404, ptr %enum_int1140, align 4
  %310 = insertvalue %HttpStatus { i32 1, ptr undef }, ptr %enum_int1140, 1
  store %HttpStatus %310, ptr %responseCode, align 8
  %responseCode1141 = load %HttpStatus, ptr %responseCode, align 8
  store i32 200, ptr %enum_int1142, align 4
  %311 = insertvalue %HttpStatus { i32 0, ptr undef }, ptr %enum_int1142, 1
  %lhs_tag1143 = extractvalue %HttpStatus %responseCode1141, 0
  %rhs_tag1144 = extractvalue %HttpStatus %311, 0
  %tags_equal1145 = icmp eq i32 %lhs_tag1143, %rhs_tag1144
  br i1 %tags_equal1145, label %tags_match1146, label %tags_mismatch1147

tags_match1146:                                   ; preds = %ifcont1139
  %lhs_payload1149 = extractvalue %HttpStatus %responseCode1141, 1
  %rhs_payload1150 = extractvalue %HttpStatus %311, 1
  switch i32 %lhs_tag1143, label %cmp_default1152 [
    i32 0, label %cmp_case_01153
    i32 1, label %cmp_case_11154
    i32 2, label %cmp_case_21155
  ]

tags_mismatch1147:                                ; preds = %ifcont1139
  br label %union_cmp_end1148

union_cmp_end1148:                                ; preds = %tags_mismatch1147, %payload_cmp_end1151
  %312 = phi i1 [ %313, %payload_cmp_end1151 ], [ false, %tags_mismatch1147 ]
  br i1 %312, label %then1156, label %elif.cond1158

payload_cmp_end1151:                              ; preds = %cmp_default1152, %cmp_case_21155, %cmp_case_11154, %cmp_case_01153
  %313 = phi i1 [ %316, %cmp_case_01153 ], [ %319, %cmp_case_11154 ], [ %322, %cmp_case_21155 ], [ false, %cmp_default1152 ]
  br label %union_cmp_end1148

cmp_default1152:                                  ; preds = %tags_match1146
  br label %payload_cmp_end1151

cmp_case_01153:                                   ; preds = %tags_match1146
  %314 = load i32, ptr %lhs_payload1149, align 4
  %315 = load i32, ptr %rhs_payload1150, align 4
  %316 = icmp eq i32 %314, %315
  br label %payload_cmp_end1151

cmp_case_11154:                                   ; preds = %tags_match1146
  %317 = load i32, ptr %lhs_payload1149, align 4
  %318 = load i32, ptr %rhs_payload1150, align 4
  %319 = icmp eq i32 %317, %318
  br label %payload_cmp_end1151

cmp_case_21155:                                   ; preds = %tags_match1146
  %320 = load i32, ptr %lhs_payload1149, align 4
  %321 = load i32, ptr %rhs_payload1150, align 4
  %322 = icmp eq i32 %320, %321
  br label %payload_cmp_end1151

then1156:                                         ; preds = %union_cmp_end1148
  call void @qc_println(ptr @.str.302)
  br label %ifcont1157

ifcont1157:                                       ; preds = %else1160, %elif.body1159, %then1156
  call void @qc_println(ptr @.str.305)
  store %TierLevel { i32 1, ptr @18 }, ptr %planType, align 8
  %planType1176 = load %TierLevel, ptr %planType, align 8
  %323 = extractvalue %TierLevel %planType1176, 0
  %324 = icmp eq i32 %323, 0
  %325 = extractvalue %TierLevel %planType1176, 1
  %326 = icmp eq ptr %325, @19
  %327 = and i1 %324, %326
  br i1 %327, label %switch.case1178, label %switch.check

elif.cond1158:                                    ; preds = %union_cmp_end1148
  %responseCode1161 = load %HttpStatus, ptr %responseCode, align 8
  store i32 404, ptr %enum_int1162, align 4
  %328 = insertvalue %HttpStatus { i32 1, ptr undef }, ptr %enum_int1162, 1
  %lhs_tag1163 = extractvalue %HttpStatus %responseCode1161, 0
  %rhs_tag1164 = extractvalue %HttpStatus %328, 0
  %tags_equal1165 = icmp eq i32 %lhs_tag1163, %rhs_tag1164
  br i1 %tags_equal1165, label %tags_match1166, label %tags_mismatch1167

elif.body1159:                                    ; preds = %union_cmp_end1168
  call void @qc_println(ptr @.str.303)
  br label %ifcont1157

else1160:                                         ; preds = %union_cmp_end1168
  call void @qc_println(ptr @.str.304)
  br label %ifcont1157

tags_match1166:                                   ; preds = %elif.cond1158
  %lhs_payload1169 = extractvalue %HttpStatus %responseCode1161, 1
  %rhs_payload1170 = extractvalue %HttpStatus %328, 1
  switch i32 %lhs_tag1163, label %cmp_default1172 [
    i32 0, label %cmp_case_01173
    i32 1, label %cmp_case_11174
    i32 2, label %cmp_case_21175
  ]

tags_mismatch1167:                                ; preds = %elif.cond1158
  br label %union_cmp_end1168

union_cmp_end1168:                                ; preds = %tags_mismatch1167, %payload_cmp_end1171
  %329 = phi i1 [ %330, %payload_cmp_end1171 ], [ false, %tags_mismatch1167 ]
  br i1 %329, label %elif.body1159, label %else1160

payload_cmp_end1171:                              ; preds = %cmp_default1172, %cmp_case_21175, %cmp_case_11174, %cmp_case_01173
  %330 = phi i1 [ %333, %cmp_case_01173 ], [ %336, %cmp_case_11174 ], [ %339, %cmp_case_21175 ], [ false, %cmp_default1172 ]
  br label %union_cmp_end1168

cmp_default1172:                                  ; preds = %tags_match1166
  br label %payload_cmp_end1171

cmp_case_01173:                                   ; preds = %tags_match1166
  %331 = load i32, ptr %lhs_payload1169, align 4
  %332 = load i32, ptr %rhs_payload1170, align 4
  %333 = icmp eq i32 %331, %332
  br label %payload_cmp_end1171

cmp_case_11174:                                   ; preds = %tags_match1166
  %334 = load i32, ptr %lhs_payload1169, align 4
  %335 = load i32, ptr %rhs_payload1170, align 4
  %336 = icmp eq i32 %334, %335
  br label %payload_cmp_end1171

cmp_case_21175:                                   ; preds = %tags_match1166
  %337 = load i32, ptr %lhs_payload1169, align 4
  %338 = load i32, ptr %rhs_payload1170, align 4
  %339 = icmp eq i32 %337, %338
  br label %payload_cmp_end1171

switch.end1177:                                   ; preds = %switch.case1180, %switch.case1179, %switch.case1178, %switch.check1181
  call void @qc_println(ptr @.str.309)
  store i32 500, ptr %enum_int1182, align 4
  %340 = insertvalue %HttpStatus { i32 2, ptr undef }, ptr %enum_int1182, 1
  store %HttpStatus %340, ptr %code, align 8
  %code1183 = load %HttpStatus, ptr %code, align 8
  %enum_data = extractvalue %HttpStatus %code1183, 1
  %341 = load i32, ptr %enum_data, align 4
  store i32 %341, ptr %numCode, align 4
  call void @qc_println(ptr @.str.310)
  store %TierLevel { i32 2, ptr @22 }, ptr %plan, align 8
  %plan1184 = load %TierLevel, ptr %plan, align 8
  %enum_data1185 = extractvalue %TierLevel %plan1184, 1
  store ptr %enum_data1185, ptr %planName, align 8
  call void @qc_println(ptr @.str.311)
  call void @qc_println(ptr @.str.312)
  %calltmp1187 = call %HttpStatus @getStatus(i32 0)
  store %HttpStatus %calltmp1187, ptr %result11186, align 8
  %result11188 = load %HttpStatus, ptr %result11186, align 8
  store i32 200, ptr %enum_int1189, align 4
  %342 = insertvalue %HttpStatus { i32 0, ptr undef }, ptr %enum_int1189, 1
  %lhs_tag1190 = extractvalue %HttpStatus %result11188, 0
  %rhs_tag1191 = extractvalue %HttpStatus %342, 0
  %tags_equal1192 = icmp eq i32 %lhs_tag1190, %rhs_tag1191
  br i1 %tags_equal1192, label %tags_match1193, label %tags_mismatch1194

switch.case1178:                                  ; preds = %ifcont1157
  call void @qc_println(ptr @.str.306)
  br label %switch.end1177

switch.case1179:                                  ; preds = %switch.check
  call void @qc_println(ptr @.str.307)
  br label %switch.end1177

switch.case1180:                                  ; preds = %switch.check1181
  call void @qc_println(ptr @.str.308)
  br label %switch.end1177

switch.check:                                     ; preds = %ifcont1157
  %343 = extractvalue %TierLevel %planType1176, 0
  %344 = icmp eq i32 %343, 1
  %345 = extractvalue %TierLevel %planType1176, 1
  %346 = icmp eq ptr %345, @20
  %347 = and i1 %344, %346
  br i1 %347, label %switch.case1179, label %switch.check1181

switch.check1181:                                 ; preds = %switch.check
  %348 = extractvalue %TierLevel %planType1176, 0
  %349 = icmp eq i32 %348, 2
  %350 = extractvalue %TierLevel %planType1176, 1
  %351 = icmp eq ptr %350, @21
  %352 = and i1 %349, %351
  br i1 %352, label %switch.case1180, label %switch.end1177

tags_match1193:                                   ; preds = %switch.end1177
  %lhs_payload1196 = extractvalue %HttpStatus %result11188, 1
  %rhs_payload1197 = extractvalue %HttpStatus %342, 1
  switch i32 %lhs_tag1190, label %cmp_default1199 [
    i32 0, label %cmp_case_01200
    i32 1, label %cmp_case_11201
    i32 2, label %cmp_case_21202
  ]

tags_mismatch1194:                                ; preds = %switch.end1177
  br label %union_cmp_end1195

union_cmp_end1195:                                ; preds = %tags_mismatch1194, %payload_cmp_end1198
  %353 = phi i1 [ %354, %payload_cmp_end1198 ], [ false, %tags_mismatch1194 ]
  br i1 %353, label %then1203, label %ifcont1204

payload_cmp_end1198:                              ; preds = %cmp_default1199, %cmp_case_21202, %cmp_case_11201, %cmp_case_01200
  %354 = phi i1 [ %357, %cmp_case_01200 ], [ %360, %cmp_case_11201 ], [ %363, %cmp_case_21202 ], [ false, %cmp_default1199 ]
  br label %union_cmp_end1195

cmp_default1199:                                  ; preds = %tags_match1193
  br label %payload_cmp_end1198

cmp_case_01200:                                   ; preds = %tags_match1193
  %355 = load i32, ptr %lhs_payload1196, align 4
  %356 = load i32, ptr %rhs_payload1197, align 4
  %357 = icmp eq i32 %355, %356
  br label %payload_cmp_end1198

cmp_case_11201:                                   ; preds = %tags_match1193
  %358 = load i32, ptr %lhs_payload1196, align 4
  %359 = load i32, ptr %rhs_payload1197, align 4
  %360 = icmp eq i32 %358, %359
  br label %payload_cmp_end1198

cmp_case_21202:                                   ; preds = %tags_match1193
  %361 = load i32, ptr %lhs_payload1196, align 4
  %362 = load i32, ptr %rhs_payload1197, align 4
  %363 = icmp eq i32 %361, %362
  br label %payload_cmp_end1198

then1203:                                         ; preds = %union_cmp_end1195
  call void @qc_println(ptr @.str.313)
  br label %ifcont1204

ifcont1204:                                       ; preds = %then1203, %union_cmp_end1195
  %calltmp1206 = call %HttpStatus @getStatus(i32 1)
  store %HttpStatus %calltmp1206, ptr %result21205, align 8
  %result21207 = load %HttpStatus, ptr %result21205, align 8
  store i32 404, ptr %enum_int1208, align 4
  %364 = insertvalue %HttpStatus { i32 1, ptr undef }, ptr %enum_int1208, 1
  %lhs_tag1209 = extractvalue %HttpStatus %result21207, 0
  %rhs_tag1210 = extractvalue %HttpStatus %364, 0
  %tags_equal1211 = icmp eq i32 %lhs_tag1209, %rhs_tag1210
  br i1 %tags_equal1211, label %tags_match1212, label %tags_mismatch1213

tags_match1212:                                   ; preds = %ifcont1204
  %lhs_payload1215 = extractvalue %HttpStatus %result21207, 1
  %rhs_payload1216 = extractvalue %HttpStatus %364, 1
  switch i32 %lhs_tag1209, label %cmp_default1218 [
    i32 0, label %cmp_case_01219
    i32 1, label %cmp_case_11220
    i32 2, label %cmp_case_21221
  ]

tags_mismatch1213:                                ; preds = %ifcont1204
  br label %union_cmp_end1214

union_cmp_end1214:                                ; preds = %tags_mismatch1213, %payload_cmp_end1217
  %365 = phi i1 [ %366, %payload_cmp_end1217 ], [ false, %tags_mismatch1213 ]
  br i1 %365, label %then1222, label %ifcont1223

payload_cmp_end1217:                              ; preds = %cmp_default1218, %cmp_case_21221, %cmp_case_11220, %cmp_case_01219
  %366 = phi i1 [ %369, %cmp_case_01219 ], [ %372, %cmp_case_11220 ], [ %375, %cmp_case_21221 ], [ false, %cmp_default1218 ]
  br label %union_cmp_end1214

cmp_default1218:                                  ; preds = %tags_match1212
  br label %payload_cmp_end1217

cmp_case_01219:                                   ; preds = %tags_match1212
  %367 = load i32, ptr %lhs_payload1215, align 4
  %368 = load i32, ptr %rhs_payload1216, align 4
  %369 = icmp eq i32 %367, %368
  br label %payload_cmp_end1217

cmp_case_11220:                                   ; preds = %tags_match1212
  %370 = load i32, ptr %lhs_payload1215, align 4
  %371 = load i32, ptr %rhs_payload1216, align 4
  %372 = icmp eq i32 %370, %371
  br label %payload_cmp_end1217

cmp_case_21221:                                   ; preds = %tags_match1212
  %373 = load i32, ptr %lhs_payload1215, align 4
  %374 = load i32, ptr %rhs_payload1216, align 4
  %375 = icmp eq i32 %373, %374
  br label %payload_cmp_end1217

then1222:                                         ; preds = %union_cmp_end1214
  call void @qc_println(ptr @.str.314)
  br label %ifcont1223

ifcont1223:                                       ; preds = %then1222, %union_cmp_end1214
  call void @qc_println(ptr @.str.315)
  %calltmp1224 = call { %HttpStatus, ptr } @checkEndpoint()
  %376 = extractvalue { %HttpStatus, ptr } %calltmp1224, 0
  store %HttpStatus %376, ptr %respStatus, align 8
  %377 = extractvalue { %HttpStatus, ptr } %calltmp1224, 1
  store ptr %377, ptr %respMsg, align 8
  %respStatus1225 = load %HttpStatus, ptr %respStatus, align 8
  store i32 200, ptr %enum_int1226, align 4
  %378 = insertvalue %HttpStatus { i32 0, ptr undef }, ptr %enum_int1226, 1
  %lhs_tag1227 = extractvalue %HttpStatus %respStatus1225, 0
  %rhs_tag1228 = extractvalue %HttpStatus %378, 0
  %tags_equal1229 = icmp eq i32 %lhs_tag1227, %rhs_tag1228
  br i1 %tags_equal1229, label %tags_match1230, label %tags_mismatch1231

tags_match1230:                                   ; preds = %ifcont1223
  %lhs_payload1233 = extractvalue %HttpStatus %respStatus1225, 1
  %rhs_payload1234 = extractvalue %HttpStatus %378, 1
  switch i32 %lhs_tag1227, label %cmp_default1236 [
    i32 0, label %cmp_case_01237
    i32 1, label %cmp_case_11238
    i32 2, label %cmp_case_21239
  ]

tags_mismatch1231:                                ; preds = %ifcont1223
  br label %union_cmp_end1232

union_cmp_end1232:                                ; preds = %tags_mismatch1231, %payload_cmp_end1235
  %379 = phi i1 [ %380, %payload_cmp_end1235 ], [ false, %tags_mismatch1231 ]
  br i1 %379, label %then1240, label %ifcont1241

payload_cmp_end1235:                              ; preds = %cmp_default1236, %cmp_case_21239, %cmp_case_11238, %cmp_case_01237
  %380 = phi i1 [ %383, %cmp_case_01237 ], [ %386, %cmp_case_11238 ], [ %389, %cmp_case_21239 ], [ false, %cmp_default1236 ]
  br label %union_cmp_end1232

cmp_default1236:                                  ; preds = %tags_match1230
  br label %payload_cmp_end1235

cmp_case_01237:                                   ; preds = %tags_match1230
  %381 = load i32, ptr %lhs_payload1233, align 4
  %382 = load i32, ptr %rhs_payload1234, align 4
  %383 = icmp eq i32 %381, %382
  br label %payload_cmp_end1235

cmp_case_11238:                                   ; preds = %tags_match1230
  %384 = load i32, ptr %lhs_payload1233, align 4
  %385 = load i32, ptr %rhs_payload1234, align 4
  %386 = icmp eq i32 %384, %385
  br label %payload_cmp_end1235

cmp_case_21239:                                   ; preds = %tags_match1230
  %387 = load i32, ptr %lhs_payload1233, align 4
  %388 = load i32, ptr %rhs_payload1234, align 4
  %389 = icmp eq i32 %387, %388
  br label %payload_cmp_end1235

then1240:                                         ; preds = %union_cmp_end1232
  call void @qc_println(ptr @.str.317)
  br label %ifcont1241

ifcont1241:                                       ; preds = %then1240, %union_cmp_end1232
  %respMsg1242 = load ptr, ptr %respMsg, align 8
  %str_concat1243 = call ptr @qc_string_concat(ptr @.str.318, ptr %respMsg1242)
  call void @qc_println(ptr %str_concat1243)
  call void @qc_println(ptr @.str.319)
  store %TierLevel { i32 1, ptr @23 }, ptr %myPlan, align 8
  %myPlan1244 = load %TierLevel, ptr %myPlan, align 8
  %390 = extractvalue %TierLevel %myPlan1244, 0
  switch i32 %390, label %typeof_end [
    i32 0, label %case
    i32 1, label %case1245
    i32 2, label %case1246
  ]

typeof_end:                                       ; preds = %case1246, %case1245, %case, %ifcont1241
  %391 = load ptr, ptr %typeof_result, align 8
  store ptr %391, ptr %typeofPlan, align 8
  %typeofPlan1247 = load ptr, ptr %typeofPlan, align 8
  %str_concat1248 = call ptr @qc_string_concat(ptr @.str.320, ptr %typeofPlan1247)
  call void @qc_println(ptr %str_concat1248)
  store i32 200, ptr %enum_int1249, align 4
  %392 = insertvalue %HttpStatus { i32 0, ptr undef }, ptr %enum_int1249, 1
  store %HttpStatus %392, ptr %myStatus, align 8
  %myStatus1250 = load %HttpStatus, ptr %myStatus, align 8
  %393 = extractvalue %HttpStatus %myStatus1250, 0
  switch i32 %393, label %typeof_end1251 [
    i32 0, label %case1253
    i32 1, label %case1254
    i32 2, label %case1255
  ]

case:                                             ; preds = %ifcont1241
  store ptr @24, ptr %typeof_result, align 8
  br label %typeof_end

case1245:                                         ; preds = %ifcont1241
  store ptr @25, ptr %typeof_result, align 8
  br label %typeof_end

case1246:                                         ; preds = %ifcont1241
  store ptr @26, ptr %typeof_result, align 8
  br label %typeof_end

typeof_end1251:                                   ; preds = %case1255, %case1254, %case1253, %typeof_end
  %394 = load ptr, ptr %typeof_result1252, align 8
  store ptr %394, ptr %statusType, align 8
  %statusType1256 = load ptr, ptr %statusType, align 8
  %str_concat1257 = call ptr @qc_string_concat(ptr @.str.321, ptr %statusType1256)
  call void @qc_println(ptr %str_concat1257)
  call void @qc_println(ptr @.str.322)
  store i32 200, ptr %enum_int1258, align 4
  %395 = insertvalue %HttpStatus { i32 0, ptr undef }, ptr %enum_int1258, 1
  store %HttpStatus %395, ptr %loopStatus, align 8
  store i32 0, ptr %counter, align 4
  br label %while.cond1259

case1253:                                         ; preds = %typeof_end
  store ptr @27, ptr %typeof_result1252, align 8
  br label %typeof_end1251

case1254:                                         ; preds = %typeof_end
  store ptr @28, ptr %typeof_result1252, align 8
  br label %typeof_end1251

case1255:                                         ; preds = %typeof_end
  store ptr @29, ptr %typeof_result1252, align 8
  br label %typeof_end1251

while.cond1259:                                   ; preds = %while.body1260, %typeof_end1251
  %loopStatus1262 = load %HttpStatus, ptr %loopStatus, align 8
  store i32 200, ptr %enum_int1263, align 4
  %396 = insertvalue %HttpStatus { i32 0, ptr undef }, ptr %enum_int1263, 1
  %lhs_tag1264 = extractvalue %HttpStatus %loopStatus1262, 0
  %rhs_tag1265 = extractvalue %HttpStatus %396, 0
  %tags_equal1266 = icmp eq i32 %lhs_tag1264, %rhs_tag1265
  br i1 %tags_equal1266, label %tags_match1267, label %tags_mismatch1268

while.body1260:                                   ; preds = %union_cmp_end1269
  call void @qc_println(ptr @.str.323)
  %counter1280 = load i32, ptr %counter, align 4
  %add1281 = add i32 %counter1280, 1
  store i32 %add1281, ptr %counter, align 4
  br label %while.cond1259

while.end1261:                                    ; preds = %union_cmp_end1269
  call void @qc_println(ptr @.str.324)
  call void @qc_println(ptr @.str.325)
  store i32 0, ptr %idx, align 4
  br label %for.cond1282

tags_match1267:                                   ; preds = %while.cond1259
  %lhs_payload1270 = extractvalue %HttpStatus %loopStatus1262, 1
  %rhs_payload1271 = extractvalue %HttpStatus %396, 1
  switch i32 %lhs_tag1264, label %cmp_default1273 [
    i32 0, label %cmp_case_01274
    i32 1, label %cmp_case_11275
    i32 2, label %cmp_case_21276
  ]

tags_mismatch1268:                                ; preds = %while.cond1259
  br label %union_cmp_end1269

union_cmp_end1269:                                ; preds = %tags_mismatch1268, %payload_cmp_end1272
  %397 = phi i1 [ %398, %payload_cmp_end1272 ], [ false, %tags_mismatch1268 ]
  %counter1277 = load i32, ptr %counter, align 4
  %icmplt1278 = icmp slt i32 %counter1277, 3
  %and1279 = and i1 %397, %icmplt1278
  br i1 %and1279, label %while.body1260, label %while.end1261

payload_cmp_end1272:                              ; preds = %cmp_default1273, %cmp_case_21276, %cmp_case_11275, %cmp_case_01274
  %398 = phi i1 [ %401, %cmp_case_01274 ], [ %404, %cmp_case_11275 ], [ %407, %cmp_case_21276 ], [ false, %cmp_default1273 ]
  br label %union_cmp_end1269

cmp_default1273:                                  ; preds = %tags_match1267
  br label %payload_cmp_end1272

cmp_case_01274:                                   ; preds = %tags_match1267
  %399 = load i32, ptr %lhs_payload1270, align 4
  %400 = load i32, ptr %rhs_payload1271, align 4
  %401 = icmp eq i32 %399, %400
  br label %payload_cmp_end1272

cmp_case_11275:                                   ; preds = %tags_match1267
  %402 = load i32, ptr %lhs_payload1270, align 4
  %403 = load i32, ptr %rhs_payload1271, align 4
  %404 = icmp eq i32 %402, %403
  br label %payload_cmp_end1272

cmp_case_21276:                                   ; preds = %tags_match1267
  %405 = load i32, ptr %lhs_payload1270, align 4
  %406 = load i32, ptr %rhs_payload1271, align 4
  %407 = icmp eq i32 %405, %406
  br label %payload_cmp_end1272

for.cond1282:                                     ; preds = %for.inc1284, %while.end1261
  %idx1286 = load i32, ptr %idx, align 4
  %icmplt1287 = icmp slt i32 %idx1286, 2
  br i1 %icmplt1287, label %for.body1283, label %for.end1285

for.body1283:                                     ; preds = %for.cond1282
  store i32 200, ptr %enum_int1288, align 4
  %408 = insertvalue %HttpStatus { i32 0, ptr undef }, ptr %enum_int1288, 1
  store %HttpStatus %408, ptr %iterStatus, align 8
  %iterStatus1289 = load %HttpStatus, ptr %iterStatus, align 8
  store i32 200, ptr %enum_int1290, align 4
  %409 = insertvalue %HttpStatus { i32 0, ptr undef }, ptr %enum_int1290, 1
  %lhs_tag1291 = extractvalue %HttpStatus %iterStatus1289, 0
  %rhs_tag1292 = extractvalue %HttpStatus %409, 0
  %tags_equal1293 = icmp eq i32 %lhs_tag1291, %rhs_tag1292
  br i1 %tags_equal1293, label %tags_match1294, label %tags_mismatch1295

for.inc1284:                                      ; preds = %ifcont1305
  %idx1306 = load i32, ptr %idx, align 4
  %add1307 = add i32 %idx1306, 1
  store i32 %add1307, ptr %idx, align 4
  br label %for.cond1282

for.end1285:                                      ; preds = %for.cond1282
  call void @qc_println(ptr @.str.327)
  store i32 500, ptr %enum_int1308, align 4
  %410 = insertvalue %HttpStatus { i32 2, ptr undef }, ptr %enum_int1308, 1
  store %HttpStatus %410, ptr %negStatus, align 8
  %negStatus1309 = load %HttpStatus, ptr %negStatus, align 8
  %411 = extractvalue %HttpStatus %negStatus1309, 1
  %412 = load i32, ptr %411, align 4
  %neg = sub i32 0, %412
  store i32 %neg, ptr %negValue, align 4
  call void @qc_println(ptr @.str.328)
  call void @qc_println(ptr @.str.329)
  store %TierLevel { i32 0, ptr @30 }, ptr %tier1, align 8
  store %TierLevel { i32 0, ptr @31 }, ptr %tier2, align 8
  store %TierLevel { i32 1, ptr @32 }, ptr %tier3, align 8
  %tier11310 = load %TierLevel, ptr %tier1, align 8
  %tier21311 = load %TierLevel, ptr %tier2, align 8
  %lhs_tag1312 = extractvalue %TierLevel %tier11310, 0
  %rhs_tag1313 = extractvalue %TierLevel %tier21311, 0
  %tags_equal1314 = icmp eq i32 %lhs_tag1312, %rhs_tag1313
  br i1 %tags_equal1314, label %tags_match1315, label %tags_mismatch1316

tags_match1294:                                   ; preds = %for.body1283
  %lhs_payload1297 = extractvalue %HttpStatus %iterStatus1289, 1
  %rhs_payload1298 = extractvalue %HttpStatus %409, 1
  switch i32 %lhs_tag1291, label %cmp_default1300 [
    i32 0, label %cmp_case_01301
    i32 1, label %cmp_case_11302
    i32 2, label %cmp_case_21303
  ]

tags_mismatch1295:                                ; preds = %for.body1283
  br label %union_cmp_end1296

union_cmp_end1296:                                ; preds = %tags_mismatch1295, %payload_cmp_end1299
  %413 = phi i1 [ %414, %payload_cmp_end1299 ], [ false, %tags_mismatch1295 ]
  br i1 %413, label %then1304, label %ifcont1305

payload_cmp_end1299:                              ; preds = %cmp_default1300, %cmp_case_21303, %cmp_case_11302, %cmp_case_01301
  %414 = phi i1 [ %417, %cmp_case_01301 ], [ %420, %cmp_case_11302 ], [ %423, %cmp_case_21303 ], [ false, %cmp_default1300 ]
  br label %union_cmp_end1296

cmp_default1300:                                  ; preds = %tags_match1294
  br label %payload_cmp_end1299

cmp_case_01301:                                   ; preds = %tags_match1294
  %415 = load i32, ptr %lhs_payload1297, align 4
  %416 = load i32, ptr %rhs_payload1298, align 4
  %417 = icmp eq i32 %415, %416
  br label %payload_cmp_end1299

cmp_case_11302:                                   ; preds = %tags_match1294
  %418 = load i32, ptr %lhs_payload1297, align 4
  %419 = load i32, ptr %rhs_payload1298, align 4
  %420 = icmp eq i32 %418, %419
  br label %payload_cmp_end1299

cmp_case_21303:                                   ; preds = %tags_match1294
  %421 = load i32, ptr %lhs_payload1297, align 4
  %422 = load i32, ptr %rhs_payload1298, align 4
  %423 = icmp eq i32 %421, %422
  br label %payload_cmp_end1299

then1304:                                         ; preds = %union_cmp_end1296
  call void @qc_println(ptr @.str.326)
  br label %ifcont1305

ifcont1305:                                       ; preds = %then1304, %union_cmp_end1296
  br label %for.inc1284

tags_match1315:                                   ; preds = %for.end1285
  %lhs_payload1318 = extractvalue %TierLevel %tier11310, 1
  %rhs_payload1319 = extractvalue %TierLevel %tier21311, 1
  switch i32 %lhs_tag1312, label %cmp_default1321 [
    i32 0, label %cmp_case_01322
    i32 1, label %cmp_case_11323
    i32 2, label %cmp_case_21324
  ]

tags_mismatch1316:                                ; preds = %for.end1285
  br label %union_cmp_end1317

union_cmp_end1317:                                ; preds = %tags_mismatch1316, %payload_cmp_end1320
  %424 = phi i1 [ %425, %payload_cmp_end1320 ], [ false, %tags_mismatch1316 ]
  %tier21325 = load %TierLevel, ptr %tier2, align 8
  %tier31326 = load %TierLevel, ptr %tier3, align 8
  %lhs_tag1327 = extractvalue %TierLevel %tier21325, 0
  %rhs_tag1328 = extractvalue %TierLevel %tier31326, 0
  %tags_equal1329 = icmp eq i32 %lhs_tag1327, %rhs_tag1328
  br i1 %tags_equal1329, label %tags_match1330, label %tags_mismatch1331

payload_cmp_end1320:                              ; preds = %cmp_default1321, %cmp_case_21324, %cmp_case_11323, %cmp_case_01322
  %425 = phi i1 [ %426, %cmp_case_01322 ], [ %427, %cmp_case_11323 ], [ %428, %cmp_case_21324 ], [ false, %cmp_default1321 ]
  br label %union_cmp_end1317

cmp_default1321:                                  ; preds = %tags_match1315
  br label %payload_cmp_end1320

cmp_case_01322:                                   ; preds = %tags_match1315
  %426 = call i1 @qc_string_eq(ptr %lhs_payload1318, ptr %rhs_payload1319)
  br label %payload_cmp_end1320

cmp_case_11323:                                   ; preds = %tags_match1315
  %427 = call i1 @qc_string_eq(ptr %lhs_payload1318, ptr %rhs_payload1319)
  br label %payload_cmp_end1320

cmp_case_21324:                                   ; preds = %tags_match1315
  %428 = call i1 @qc_string_eq(ptr %lhs_payload1318, ptr %rhs_payload1319)
  br label %payload_cmp_end1320

tags_match1330:                                   ; preds = %union_cmp_end1317
  %lhs_payload1333 = extractvalue %TierLevel %tier21325, 1
  %rhs_payload1334 = extractvalue %TierLevel %tier31326, 1
  switch i32 %lhs_tag1327, label %cmp_default1336 [
    i32 0, label %cmp_case_01337
    i32 1, label %cmp_case_11338
    i32 2, label %cmp_case_21339
  ]

tags_mismatch1331:                                ; preds = %union_cmp_end1317
  br label %union_cmp_end1332

union_cmp_end1332:                                ; preds = %tags_mismatch1331, %payload_cmp_end1335
  %429 = phi i1 [ %431, %payload_cmp_end1335 ], [ false, %tags_mismatch1331 ]
  %430 = xor i1 %429, true
  %and1340 = and i1 %424, %430
  br i1 %and1340, label %then1341, label %ifcont1342

payload_cmp_end1335:                              ; preds = %cmp_default1336, %cmp_case_21339, %cmp_case_11338, %cmp_case_01337
  %431 = phi i1 [ %432, %cmp_case_01337 ], [ %433, %cmp_case_11338 ], [ %434, %cmp_case_21339 ], [ false, %cmp_default1336 ]
  br label %union_cmp_end1332

cmp_default1336:                                  ; preds = %tags_match1330
  br label %payload_cmp_end1335

cmp_case_01337:                                   ; preds = %tags_match1330
  %432 = call i1 @qc_string_eq(ptr %lhs_payload1333, ptr %rhs_payload1334)
  br label %payload_cmp_end1335

cmp_case_11338:                                   ; preds = %tags_match1330
  %433 = call i1 @qc_string_eq(ptr %lhs_payload1333, ptr %rhs_payload1334)
  br label %payload_cmp_end1335

cmp_case_21339:                                   ; preds = %tags_match1330
  %434 = call i1 @qc_string_eq(ptr %lhs_payload1333, ptr %rhs_payload1334)
  br label %payload_cmp_end1335

then1341:                                         ; preds = %union_cmp_end1332
  call void @qc_println(ptr @.str.330)
  br label %ifcont1342

ifcont1342:                                       ; preds = %then1341, %union_cmp_end1332
  call void @qc_println(ptr @.str.331)
  call void @qc_println(ptr @.str.332)
  call void @qc_println(ptr @.str.333)
  call void @Dog_Dog(ptr %myDog, ptr @.str.334, i32 5)
  %myDog1343 = load %Dog, ptr %myDog, align 8
  store %Dog %myDog1343, ptr %temp_obj, align 8
  %435 = getelementptr inbounds %Dog, ptr %temp_obj, i32 0, i32 0
  %name1344 = load ptr, ptr %435, align 8
  %str_concat1345 = call ptr @qc_string_concat(ptr @.str.335, ptr %name1344)
  call void @qc_println(ptr %str_concat1345)
  %myDog1346 = load %Dog, ptr %myDog, align 8
  store %Dog %myDog1346, ptr %temp_obj1347, align 8
  %436 = getelementptr inbounds %Dog, ptr %temp_obj1347, i32 0, i32 1
  %age = load i32, ptr %436, align 4
  %to_str1348 = call ptr @qc_to_string_int(i32 %age)
  %str_concat1349 = call ptr @qc_string_concat(ptr @.str.336, ptr %to_str1348)
  call void @qc_println(ptr %str_concat1349)
  call void @qc_println(ptr @.str.337)
  call void @Cat_Cat(ptr %myCat, ptr @.str.338, i32 9)
  %myCat1350 = load %Cat, ptr %myCat, align 8
  %meow_result = call i32 @Cat_meow(ptr %myCat)
  %myCat1351 = load %Cat, ptr %myCat, align 8
  %useLives_result = call i32 @Cat_useLives(ptr %myCat, i32 3)
  call void @qc_println(ptr @.str.339)
  call void @Calculator_Calculator(ptr %calc, i32 10)
  %calc1352 = load %Calculator, ptr %calc, align 4
  %add_result = call i32 @Calculator_add(ptr %calc, i32 5)
  store i32 %add_result, ptr %result, align 4
  %result1353 = load i32, ptr %result, align 4
  %to_str1354 = call ptr @qc_to_string_int(i32 %result1353)
  %str_concat1355 = call ptr @qc_string_concat(ptr @.str.340, ptr %to_str1354)
  call void @qc_println(ptr %str_concat1355)
  %calc1356 = load %Calculator, ptr %calc, align 4
  %getValue_result = call i32 @Calculator_getValue(ptr %calc)
  %to_str1357 = call ptr @qc_to_string_int(i32 %getValue_result)
  %str_concat1358 = call ptr @qc_string_concat(ptr @.str.341, ptr %to_str1357)
  call void @qc_println(ptr %str_concat1358)
  call void @qc_println(ptr @.str.342)
  call void @Counter_Counter(ptr %counter1359, i32 0)
  %counter1360 = load %Counter, ptr %counter1359, align 4
  %increment_result = call i32 @Counter_increment(ptr %counter1359)
  %counter1361 = load %Counter, ptr %counter1359, align 4
  %increment_result1362 = call i32 @Counter_increment(ptr %counter1359)
  %counter1363 = load %Counter, ptr %counter1359, align 4
  %increment_result1364 = call i32 @Counter_increment(ptr %counter1359)
  %counter1365 = load %Counter, ptr %counter1359, align 4
  %get_result = call i32 @Counter_get(ptr %counter1359)
  %to_str1366 = call ptr @qc_to_string_int(i32 %get_result)
  %str_concat1367 = call ptr @qc_string_concat(ptr @.str.343, ptr %to_str1366)
  call void @qc_println(ptr %str_concat1367)
  %counter1368 = load %Counter, ptr %counter1359, align 4
  %decrement_result = call i32 @Counter_decrement(ptr %counter1359)
  %counter1369 = load %Counter, ptr %counter1359, align 4
  %get_result1370 = call i32 @Counter_get(ptr %counter1359)
  %to_str1371 = call ptr @qc_to_string_int(i32 %get_result1370)
  %str_concat1372 = call ptr @qc_string_concat(ptr @.str.344, ptr %to_str1371)
  call void @qc_println(ptr %str_concat1372)
  %counter1373 = load %Counter, ptr %counter1359, align 4
  %reset_result = call i32 @Counter_reset(ptr %counter1359)
  %counter1374 = load %Counter, ptr %counter1359, align 4
  %get_result1375 = call i32 @Counter_get(ptr %counter1359)
  %to_str1376 = call ptr @qc_to_string_int(i32 %get_result1375)
  %str_concat1377 = call ptr @qc_string_concat(ptr @.str.345, ptr %to_str1376)
  call void @qc_println(ptr %str_concat1377)
  call void @qc_println(ptr @.str.346)
  call void @Person_Person(ptr %alice, ptr @.str.347, i32 25)
  %alice1378 = load %Person, ptr %alice, align 8
  %birthday_result = call i32 @Person_birthday(ptr %alice)
  %alice1379 = load %Person, ptr %alice, align 8
  %birthday_result1380 = call i32 @Person_birthday(ptr %alice)
  call void @qc_println(ptr @.str.348)
  call void @Robot_Robot(ptr %bot, ptr @.str.349)
  %bot1381 = load %Robot, ptr %bot, align 8
  %start_result = call i32 @Robot_start(ptr %bot)
  %bot1382 = load %Robot, ptr %bot, align 8
  %getStatus_result = call i32 @Robot_getStatus(ptr %bot)
  %bot1383 = load %Robot, ptr %bot, align 8
  %stop_result = call i32 @Robot_stop(ptr %bot)
  %bot1384 = load %Robot, ptr %bot, align 8
  %getStatus_result1385 = call i32 @Robot_getStatus(ptr %bot)
  call void @qc_println(ptr @.str.350)
  call void @qc_println(ptr @.str.351)
  call void @qc_println(ptr @.str.352)
  call void @DogInherit_DogInherit(ptr %myDogInherit, ptr @.str.353, i32 3)
  %myDogInherit1386 = load %DogInherit, ptr %myDogInherit, align 8
  %makeSound_result = call i32 @Animal_makeSound(ptr %myDogInherit)
  %myDogInherit1387 = load %DogInherit, ptr %myDogInherit, align 8
  %getAge_result = call i32 @Animal_getAge(ptr %myDogInherit)
  %myDogInherit1388 = load %DogInherit, ptr %myDogInherit, align 8
  %bark_result = call i32 @DogInherit_bark(ptr %myDogInherit)
  %myDogInherit1389 = load %DogInherit, ptr %myDogInherit, align 8
  store %DogInherit %myDogInherit1389, ptr %temp_obj1390, align 8
  %437 = getelementptr inbounds %DogInherit, ptr %temp_obj1390, i32 0, i32 2
  %breed_name = load ptr, ptr %437, align 8
  %str_concat1391 = call ptr @qc_string_concat(ptr @.str.354, ptr %breed_name)
  call void @qc_println(ptr %str_concat1391)
  %myDogInherit1392 = load %DogInherit, ptr %myDogInherit, align 8
  store %DogInherit %myDogInherit1392, ptr %temp_obj1393, align 8
  %438 = getelementptr inbounds %DogInherit, ptr %temp_obj1393, i32 0, i32 0
  %species = load ptr, ptr %438, align 8
  %str_concat1394 = call ptr @qc_string_concat(ptr @.str.355, ptr %species)
  call void @qc_println(ptr %str_concat1394)
  %myDogInherit1395 = load %DogInherit, ptr %myDogInherit, align 8
  store %DogInherit %myDogInherit1395, ptr %temp_obj1396, align 8
  %439 = getelementptr inbounds %DogInherit, ptr %temp_obj1396, i32 0, i32 1
  %age_years = load i32, ptr %439, align 4
  %to_str1397 = call ptr @qc_to_string_int(i32 %age_years)
  %str_concat1398 = call ptr @qc_string_concat(ptr @.str.356, ptr %to_str1397)
  call void @qc_println(ptr %str_concat1398)
  call void @qc_println(ptr @.str.357)
  call void @CarInherit_CarInherit(ptr %myCar, i32 120, i32 4)
  %myCar1399 = load %CarInherit, ptr %myCar, align 8
  %describe_result = call i32 @CarInherit_describe(ptr %myCar)
  %myCar1400 = load %CarInherit, ptr %myCar, align 8
  %getSpeed_result = call i32 @Vehicle_getSpeed(ptr %myCar)
  call void @qc_println(ptr @.str.358)
  call void @FlowerPlant_FlowerPlant(ptr %rose, ptr @.str.359, ptr @.str.360)
  %rose1401 = load %FlowerPlant, ptr %rose, align 8
  %checkLife_result = call i32 @LivingThing_checkLife(ptr %rose)
  %rose1402 = load %FlowerPlant, ptr %rose, align 8
  %photosynthesize_result = call i32 @PlantLife_photosynthesize(ptr %rose)
  %rose1403 = load %FlowerPlant, ptr %rose, align 8
  %bloom_result = call i32 @FlowerPlant_bloom(ptr %rose)
  %rose1404 = load %FlowerPlant, ptr %rose, align 8
  store %FlowerPlant %rose1404, ptr %temp_obj1405, align 8
  %440 = getelementptr inbounds %FlowerPlant, ptr %temp_obj1405, i32 0, i32 2
  %color_name = load ptr, ptr %440, align 8
  %str_concat1406 = call ptr @qc_string_concat(ptr @.str.361, ptr %color_name)
  call void @qc_println(ptr %str_concat1406)
  %rose1407 = load %FlowerPlant, ptr %rose, align 8
  store %FlowerPlant %rose1407, ptr %temp_obj1408, align 8
  %441 = getelementptr inbounds %FlowerPlant, ptr %temp_obj1408, i32 0, i32 1
  %plant_type = load ptr, ptr %441, align 8
  %str_concat1409 = call ptr @qc_string_concat(ptr @.str.362, ptr %plant_type)
  call void @qc_println(ptr %str_concat1409)
  %rose1410 = load %FlowerPlant, ptr %rose, align 8
  store %FlowerPlant %rose1410, ptr %temp_obj1411, align 8
  %442 = getelementptr inbounds %FlowerPlant, ptr %temp_obj1411, i32 0, i32 0
  %is_alive = load i1, ptr %442, align 1
  br i1 %is_alive, label %then1412, label %ifcont1413

then1412:                                         ; preds = %ifcont1342
  call void @qc_println(ptr @.str.363)
  br label %ifcont1413

ifcont1413:                                       ; preds = %then1412, %ifcont1342
  call void @qc_println(ptr @.str.364)
  call void @SavingsAccount_SavingsAccount(ptr %savings, ptr @.str.365, i32 1000, float 0x3FA99999A0000000)
  %savings1414 = load %SavingsAccount, ptr %savings, align 8
  store %SavingsAccount %savings1414, ptr %temp_obj1415, align 8
  %443 = getelementptr inbounds %SavingsAccount, ptr %temp_obj1415, i32 0, i32 0
  %account_holder = load ptr, ptr %443, align 8
  %str_concat1416 = call ptr @qc_string_concat(ptr @.str.366, ptr %account_holder)
  call void @qc_println(ptr %str_concat1416)
  %savings1417 = load %SavingsAccount, ptr %savings, align 8
  store %SavingsAccount %savings1417, ptr %temp_obj1418, align 8
  %444 = getelementptr inbounds %SavingsAccount, ptr %temp_obj1418, i32 0, i32 1
  %balance_dollars = load i32, ptr %444, align 4
  %to_str1419 = call ptr @qc_to_string_int(i32 %balance_dollars)
  %str_concat1420 = call ptr @qc_string_concat(ptr @.str.367, ptr %to_str1419)
  call void @qc_println(ptr %str_concat1420)
  %savings1421 = load %SavingsAccount, ptr %savings, align 8
  %deposit_result = call i32 @BankAccount_deposit(ptr %savings, i32 500)
  %savings1422 = load %SavingsAccount, ptr %savings, align 8
  %addInterest_result = call i32 @SavingsAccount_addInterest(ptr %savings)
  %savings1423 = load %SavingsAccount, ptr %savings, align 8
  store %SavingsAccount %savings1423, ptr %temp_obj1424, align 8
  %445 = getelementptr inbounds %SavingsAccount, ptr %temp_obj1424, i32 0, i32 1
  %balance_dollars1425 = load i32, ptr %445, align 4
  %to_str1426 = call ptr @qc_to_string_int(i32 %balance_dollars1425)
  %str_concat1427 = call ptr @qc_string_concat(ptr @.str.368, ptr %to_str1426)
  call void @qc_println(ptr %str_concat1427)
  call void @qc_println(ptr @.str.369)
  call void @SecureBox_SecureBox(ptr %box, ptr @.str.370)
  %box1428 = load %SecureBox, ptr %box, align 8
  store %SecureBox %box1428, ptr %temp_obj1429, align 8
  %446 = getelementptr inbounds %SecureBox, ptr %temp_obj1429, i32 0, i32 1
  %is_locked = load i1, ptr %446, align 1
  %to_str1430 = call ptr @qc_to_string_bool(i1 %is_locked)
  %str_concat1431 = call ptr @qc_string_concat(ptr @.str.371, ptr %to_str1430)
  call void @qc_println(ptr %str_concat1431)
  %box1432 = load %SecureBox, ptr %box, align 8
  %unlock_result = call i32 @SecureBox_unlock(ptr %box, ptr @.str.372)
  %box1433 = load %SecureBox, ptr %box, align 8
  %unlock_result1434 = call i32 @SecureBox_unlock(ptr %box, ptr @.str.373)
  %box1435 = load %SecureBox, ptr %box, align 8
  store %SecureBox %box1435, ptr %temp_obj1436, align 8
  %447 = getelementptr inbounds %SecureBox, ptr %temp_obj1436, i32 0, i32 1
  %is_locked1437 = load i1, ptr %447, align 1
  %to_str1438 = call ptr @qc_to_string_bool(i1 %is_locked1437)
  %str_concat1439 = call ptr @qc_string_concat(ptr @.str.374, ptr %to_str1438)
  call void @qc_println(ptr %str_concat1439)
  call void @qc_println(ptr @.str.375)
  call void @Warrior_Warrior(ptr %hero, ptr @.str.376, i32 100, i32 5)
  %hero1440 = load %Warrior, ptr %hero, align 8
  %showHealth_result = call i32 @Warrior_showHealth(ptr %hero)
  %hero1441 = load %Warrior, ptr %hero, align 8
  %takeDamage_result = call i32 @GameCharacter_takeDamage(ptr %hero, i32 20)
  %hero1442 = load %Warrior, ptr %hero, align 8
  %showHealth_result1443 = call i32 @Warrior_showHealth(ptr %hero)
  %hero1444 = load %Warrior, ptr %hero, align 8
  %defend_result = call i32 @Warrior_defend(ptr %hero)
  %hero1445 = load %Warrior, ptr %hero, align 8
  %showHealth_result1446 = call i32 @Warrior_showHealth(ptr %hero)
  call void @qc_println(ptr @.str.377)
  call void @DerivedClass_DerivedClass(ptr %derived, i32 10, i32 20)
  %derived1447 = load %DerivedClass, ptr %derived, align 4
  %showBase_result = call i32 @BaseClass_showBase(ptr %derived)
  %derived1448 = load %DerivedClass, ptr %derived, align 4
  %showDerived_result = call i32 @DerivedClass_showDerived(ptr %derived)
  call void @qc_println(ptr @.str.378)
  call void @Director_Director(ptr %ceo, ptr @.str.379, i32 1, i32 50, ptr @.str.380)
  %ceo1449 = load %Director, ptr %ceo, align 8
  %work_result = call i32 @Employee_work(ptr %ceo)
  %ceo1450 = load %Director, ptr %ceo, align 8
  %manage_result = call i32 @Manager_manage(ptr %ceo)
  %ceo1451 = load %Director, ptr %ceo, align 8
  %direct_result = call i32 @Director_direct(ptr %ceo)
  %ceo1452 = load %Director, ptr %ceo, align 8
  store %Director %ceo1452, ptr %temp_obj1453, align 8
  %448 = getelementptr inbounds %Director, ptr %temp_obj1453, i32 0, i32 1
  %emp_id = load i32, ptr %448, align 4
  %to_str1454 = call ptr @qc_to_string_int(i32 %emp_id)
  %str_concat1455 = call ptr @qc_string_concat(ptr @.str.381, ptr %to_str1454)
  call void @qc_println(ptr %str_concat1455)
  %ceo1456 = load %Director, ptr %ceo, align 8
  store %Director %ceo1456, ptr %temp_obj1457, align 8
  %449 = getelementptr inbounds %Director, ptr %temp_obj1457, i32 0, i32 2
  %team_size = load i32, ptr %449, align 4
  %to_str1458 = call ptr @qc_to_string_int(i32 %team_size)
  %str_concat1459 = call ptr @qc_string_concat(ptr @.str.382, ptr %to_str1458)
  call void @qc_println(ptr %str_concat1459)
  %ceo1460 = load %Director, ptr %ceo, align 8
  store %Director %ceo1460, ptr %temp_obj1461, align 8
  %450 = getelementptr inbounds %Director, ptr %temp_obj1461, i32 0, i32 3
  %department_name = load ptr, ptr %450, align 8
  %str_concat1462 = call ptr @qc_string_concat(ptr @.str.383, ptr %department_name)
  call void @qc_println(ptr %str_concat1462)
  call void @qc_println(ptr @.str.384)
  call void @ColoredBox_ColoredBox(ptr %myBox, i32 10, i32 20, ptr @.str.385, i1 true)
  %myBox1463 = load %ColoredBox, ptr %myBox, align 8
  %describe_result1464 = call i32 @ColoredBox_describe(ptr %myBox)
  call void @qc_println(ptr @.str.386)
  call void @DoubleCounter_DoubleCounter(ptr %dc, i32 5)
  %dc1465 = load %DoubleCounter, ptr %dc, align 4
  %show_result = call i32 @Counter2_show(ptr %dc)
  %dc1466 = load %DoubleCounter, ptr %dc, align 4
  %doubleIt_result = call i32 @DoubleCounter_doubleIt(ptr %dc)
  %dc1467 = load %DoubleCounter, ptr %dc, align 4
  %show_result1468 = call i32 @Counter2_show(ptr %dc)
  %dc1469 = load %DoubleCounter, ptr %dc, align 4
  %doubleIt_result1470 = call i32 @DoubleCounter_doubleIt(ptr %dc)
  %dc1471 = load %DoubleCounter, ptr %dc, align 4
  %show_result1472 = call i32 @Counter2_show(ptr %dc)
  call void @qc_println(ptr @.str.387)
  call void @qc_println(ptr @.str.388)
  call void @Vector2D_Vector2D(ptr %v11473, i32 1, i32 2)
  call void @Vector2D_Vector2D(ptr %v21474, i32 3, i32 4)
  %v11476 = load %Vector2D, ptr %v11473, align 4
  %v21477 = load %Vector2D, ptr %v21474, align 4
  store %Vector2D %v11476, ptr %temp_op_lhs, align 4
  %op_result = call %Vector2D @"Vector2D_operator+"(ptr %temp_op_lhs, %Vector2D %v21477)
  store %Vector2D %op_result, ptr %v31475, align 4
  %v31478 = load %Vector2D, ptr %v31475, align 4
  store %Vector2D %v31478, ptr %temp_obj1479, align 4
  %451 = getelementptr inbounds %Vector2D, ptr %temp_obj1479, i32 0, i32 0
  %x_coord = load i32, ptr %451, align 4
  %to_str1480 = call ptr @qc_to_string_int(i32 %x_coord)
  %str_concat1481 = call ptr @qc_string_concat(ptr @.str.389, ptr %to_str1480)
  %str_concat1482 = call ptr @qc_string_concat(ptr %str_concat1481, ptr @.str.390)
  %v31483 = load %Vector2D, ptr %v31475, align 4
  store %Vector2D %v31483, ptr %temp_obj1484, align 4
  %452 = getelementptr inbounds %Vector2D, ptr %temp_obj1484, i32 0, i32 1
  %y_coord = load i32, ptr %452, align 4
  %to_str1485 = call ptr @qc_to_string_int(i32 %y_coord)
  %str_concat1486 = call ptr @qc_string_concat(ptr %str_concat1482, ptr %to_str1485)
  %str_concat1487 = call ptr @qc_string_concat(ptr %str_concat1486, ptr @.str.391)
  call void @qc_println(ptr %str_concat1487)
  %v11488 = load %Vector2D, ptr %v11473, align 4
  %v21489 = load %Vector2D, ptr %v21474, align 4
  store %Vector2D %v11488, ptr %temp_op_lhs1490, align 4
  %op_result1491 = call i1 @"Vector2D_operator=="(ptr %temp_op_lhs1490, %Vector2D %v21489)
  br i1 %op_result1491, label %then1492, label %else1494

then1492:                                         ; preds = %ifcont1413
  call void @qc_println(ptr @.str.392)
  br label %ifcont1493

ifcont1493:                                       ; preds = %else1494, %then1492
  call void @qc_println(ptr @.str.394)
  %453 = call i32 @Product_init(ptr %defaultProductMess)
  call void @Product_Product(ptr %laptop, ptr @.str.395, i32 999)
  %laptop1495 = load %Product, ptr %laptop, align 8
  store %Product %laptop1495, ptr %temp_repr, align 8
  %repr_result = call ptr @Product_repr(ptr %temp_repr)
  call void @qc_println(ptr %repr_result)
  %laptop1496 = load %Product, ptr %laptop, align 8
  store %Product %laptop1496, ptr %temp_eval, align 8
  %454 = call i1 @Product_eval(ptr %temp_eval)
  br i1 %454, label %then1497, label %ifcont1498

else1494:                                         ; preds = %ifcont1413
  call void @qc_println(ptr @.str.393)
  br label %ifcont1493

then1497:                                         ; preds = %ifcont1493
  call void @qc_println(ptr @.str.396)
  br label %ifcont1498

ifcont1498:                                       ; preds = %then1497, %ifcont1493
  call void @qc_println(ptr @.str.397)
  call void @MathOps_MathOps(ptr %ops)
  %ops1499 = load %MathOps, ptr %ops, align 1
  %add_result1500 = call i32 @MathOps_add(ptr %ops, i32 5, i32 10)
  %to_str1501 = call ptr @qc_to_string_int(i32 %add_result1500)
  %str_concat1502 = call ptr @qc_string_concat(ptr @.str.398, ptr %to_str1501)
  call void @qc_println(ptr %str_concat1502)
  %ops1503 = load %MathOps, ptr %ops, align 1
  %add_result1504 = call float @MathOps_add.1(ptr %ops, float 3.500000e+00, float 2.500000e+00)
  %to_str1505 = call ptr @qc_to_string_float(float %add_result1504)
  %str_concat1506 = call ptr @qc_string_concat(ptr @.str.399, ptr %to_str1505)
  call void @qc_println(ptr %str_concat1506)
  %ops1507 = load %MathOps, ptr %ops, align 1
  %add_result1508 = call ptr @MathOps_add.2(ptr %ops, ptr @.str.401, ptr @.str.402)
  %str_concat1509 = call ptr @qc_string_concat(ptr @.str.400, ptr %add_result1508)
  call void @qc_println(ptr %str_concat1509)
  %heap_arr1510 = call ptr @malloc(i64 12)
  store ptr %heap_arr1510, ptr %infferedarr, align 8
  %heap_ptr1511 = load ptr, ptr %infferedarr, align 8
  %455 = getelementptr inbounds [3 x i32], ptr %heap_ptr1511, i32 0, i32 0
  store i32 1, ptr %455, align 4
  %heap_ptr1512 = load ptr, ptr %infferedarr, align 8
  %456 = getelementptr inbounds [3 x i32], ptr %heap_ptr1512, i32 0, i32 1
  store i32 2, ptr %456, align 4
  %heap_ptr1513 = load ptr, ptr %infferedarr, align 8
  %457 = getelementptr inbounds [3 x i32], ptr %heap_ptr1513, i32 0, i32 2
  store i32 3, ptr %457, align 4
  %list_ptr1514 = call ptr @qc_create_list(i32 -1)
  store double 1.000000e+00, ptr %temp_elem1515, align 8
  call void @qc_list_push(ptr %list_ptr1514, ptr %temp_elem1515, i32 -1)
  store double 2.000000e+00, ptr %temp_elem1516, align 8
  call void @qc_list_push(ptr %list_ptr1514, ptr %temp_elem1516, i32 -1)
  store ptr %list_ptr1514, ptr %inferedlist, align 8
  %infferedarr1517 = load ptr, ptr %infferedarr, align 8
  %fstr_concat1518 = call ptr @qc_string_concat(ptr @.str.403, ptr @33)
  %fstr_concat1519 = call ptr @qc_string_concat(ptr %fstr_concat1518, ptr @.str.404)
  %inferedlist1520 = load ptr, ptr %inferedlist, align 8
  %fstr_concat1521 = call ptr @qc_string_concat(ptr %fstr_concat1519, ptr @34)
  call void @qc_println(ptr %fstr_concat1521)
  %arr_ptr1522 = load ptr, ptr %infferedarr, align 8
  %arr_elem_ptr1523 = getelementptr i32, ptr %arr_ptr1522, i32 0
  %arr_elem = load i32, ptr %arr_elem_ptr1523, align 4
  %to_str1524 = call ptr @qc_to_string_int(i32 %arr_elem)
  call void @qc_println(ptr %to_str1524)
  %x1525 = load i32, ptr %x, align 4
  %sum1526 = load i32, ptr %sum, align 4
  %add1527 = add i32 %x1525, %sum1526
  %xdddddddd1528 = load i32, ptr %xdddddddd, align 4
  %add1529 = add i32 %add1527, %xdddddddd1528
  %calltmp1530 = call i32 @twice(i32 22)
  %add1531 = add i32 %add1529, %calltmp1530
  ret i32 %add1531
}

define i32 @__lambda_0(i32 %a, i32 %b) {
entry:
  %b2 = alloca i32, align 4
  %a1 = alloca i32, align 4
  store i32 %a, ptr %a1, align 4
  store i32 %b, ptr %b2, align 4
  %a3 = load i32, ptr %a1, align 4
  %b4 = load i32, ptr %b2, align 4
  %add = add i32 %a3, %b4
  ret i32 %add
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare float @llvm.pow.f32(float, float) #8

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare double @llvm.pow.f64(double, double) #8

define i32 @print_map_size(ptr %m) {
entry:
  %m1 = alloca ptr, align 8
  store ptr %m, ptr %m1, align 8
  %m2 = load ptr, ptr %m1, align 8
  %map_size = call i32 @qc_map_size(ptr %m2)
  call void @qc_print_int(i32 %map_size)
  call void @qc_print_char(i8 10)
  ret i32 0
}

define i32 @print_three(i32 %x, i32 %y, i32 %z) {
entry:
  %z3 = alloca i32, align 4
  %y2 = alloca i32, align 4
  %x1 = alloca i32, align 4
  store i32 %x, ptr %x1, align 4
  store i32 %y, ptr %y2, align 4
  store i32 %z, ptr %z3, align 4
  call void @qc_print_string(ptr @.str.147)
  %x4 = load i32, ptr %x1, align 4
  call void @qc_print_int(i32 %x4)
  call void @qc_print_string(ptr @.str.148)
  %y5 = load i32, ptr %y2, align 4
  call void @qc_print_int(i32 %y5)
  call void @qc_print_string(ptr @.str.149)
  %z6 = load i32, ptr %z3, align 4
  call void @qc_print_int(i32 %z6)
  call void @qc_print_char(i8 10)
  ret i32 0
}

define i32 @__lambda_1(i32 %a, i32 %b, i32 %c) {
entry:
  %c3 = alloca i32, align 4
  %b2 = alloca i32, align 4
  %a1 = alloca i32, align 4
  store i32 %a, ptr %a1, align 4
  store i32 %b, ptr %b2, align 4
  store i32 %c, ptr %c3, align 4
  %a4 = load i32, ptr %a1, align 4
  %b5 = load i32, ptr %b2, align 4
  %add = add i32 %a4, %b5
  %c6 = load i32, ptr %c3, align 4
  %add7 = add i32 %add, %c6
  ret i32 %add7
}

define i32 @print_five(i32 %a, i32 %b, i32 %c, i32 %d, i32 %e) {
entry:
  %e5 = alloca i32, align 4
  %d4 = alloca i32, align 4
  %c3 = alloca i32, align 4
  %b2 = alloca i32, align 4
  %a1 = alloca i32, align 4
  store i32 %a, ptr %a1, align 4
  store i32 %b, ptr %b2, align 4
  store i32 %c, ptr %c3, align 4
  store i32 %d, ptr %d4, align 4
  store i32 %e, ptr %e5, align 4
  %a6 = load i32, ptr %a1, align 4
  call void @qc_print_int(i32 %a6)
  call void @qc_print_string(ptr @.str.153)
  %b7 = load i32, ptr %b2, align 4
  call void @qc_print_int(i32 %b7)
  call void @qc_print_string(ptr @.str.154)
  %c8 = load i32, ptr %c3, align 4
  call void @qc_print_int(i32 %c8)
  call void @qc_print_string(ptr @.str.155)
  %d9 = load i32, ptr %d4, align 4
  call void @qc_print_int(i32 %d9)
  call void @qc_print_string(ptr @.str.156)
  %e10 = load i32, ptr %e5, align 4
  call void @qc_print_int(i32 %e10)
  call void @qc_print_char(i8 10)
  ret i32 0
}

define i32 @printPoint(%Point %pt) {
entry:
  %pt1 = alloca %Point, align 8
  store %Point %pt, ptr %pt1, align 4
  call void @qc_print_string(ptr @.str.177)
  %pt2 = load %Point, ptr %pt1, align 4
  %x = extractvalue %Point %pt2, 0
  call void @qc_print_int(i32 %x)
  call void @qc_print_string(ptr @.str.178)
  %pt3 = load %Point, ptr %pt1, align 4
  %y = extractvalue %Point %pt3, 1
  call void @qc_print_int(i32 %y)
  call void @qc_print_string(ptr @.str.179)
  ret i32 0
}

define %Point @makePoint(i32 %x, i32 %y) {
entry:
  %result = alloca %Point, align 8
  %y2 = alloca i32, align 4
  %x1 = alloca i32, align 4
  store i32 %x, ptr %x1, align 4
  store i32 %y, ptr %y2, align 4
  %x3 = load i32, ptr %x1, align 4
  %0 = insertvalue %Point undef, i32 %x3, 0
  %y4 = load i32, ptr %y2, align 4
  %1 = insertvalue %Point %0, i32 %y4, 1
  store %Point %1, ptr %result, align 4
  %result5 = load %Point, ptr %result, align 4
  ret %Point %result5
}

define %Response @process(i32 %code) {
entry:
  %code1 = alloca i32, align 4
  store i32 %code, ptr %code1, align 4
  %code2 = load i32, ptr %code1, align 4
  %icmpeq = icmp eq i32 %code2, 0
  br i1 %icmpeq, label %then, label %elif.cond

then:                                             ; preds = %entry
  ret %Response { i32 0, ptr @.str.243 }

ifcont:                                           ; No predecessors!
  ret %Response undef

elif.cond:                                        ; preds = %entry
  %code3 = load i32, ptr %code1, align 4
  %icmpeq4 = icmp eq i32 %code3, 1
  br i1 %icmpeq4, label %elif.body, label %else

elif.body:                                        ; preds = %elif.cond
  ret %Response { i32 1, ptr @.str.244 }

else:                                             ; preds = %elif.cond
  %code5 = load i32, ptr %code1, align 4
  %union_heap = call ptr @malloc(i64 4)
  store i32 %code5, ptr %union_heap, align 4
  %0 = insertvalue %Response { i32 2, ptr undef }, ptr %union_heap, 1
  ret %Response %0
}

define %HttpStatus @getStatus(i32 %errorCode) {
entry:
  %enum_int6 = alloca i32, align 4
  %enum_int5 = alloca i32, align 4
  %enum_int = alloca i32, align 4
  %errorCode1 = alloca i32, align 4
  store i32 %errorCode, ptr %errorCode1, align 4
  %errorCode2 = load i32, ptr %errorCode1, align 4
  %icmpeq = icmp eq i32 %errorCode2, 0
  br i1 %icmpeq, label %then, label %elif.cond

then:                                             ; preds = %entry
  store i32 200, ptr %enum_int, align 4
  %0 = insertvalue %HttpStatus { i32 0, ptr undef }, ptr %enum_int, 1
  ret %HttpStatus %0

ifcont:                                           ; No predecessors!
  ret %HttpStatus undef

elif.cond:                                        ; preds = %entry
  %errorCode3 = load i32, ptr %errorCode1, align 4
  %icmpeq4 = icmp eq i32 %errorCode3, 1
  br i1 %icmpeq4, label %elif.body, label %else

elif.body:                                        ; preds = %elif.cond
  store i32 404, ptr %enum_int5, align 4
  %1 = insertvalue %HttpStatus { i32 1, ptr undef }, ptr %enum_int5, 1
  ret %HttpStatus %1

else:                                             ; preds = %elif.cond
  store i32 500, ptr %enum_int6, align 4
  %2 = insertvalue %HttpStatus { i32 2, ptr undef }, ptr %enum_int6, 1
  ret %HttpStatus %2
}

define { %HttpStatus, ptr } @checkEndpoint() {
entry:
  %enum_int = alloca i32, align 4
  store i32 200, ptr %enum_int, align 4
  %0 = insertvalue %HttpStatus { i32 0, ptr undef }, ptr %enum_int, 1
  %1 = insertvalue { %HttpStatus, ptr } undef, %HttpStatus %0, 0
  %2 = insertvalue { %HttpStatus, ptr } %1, ptr @.str.316, 1
  ret { %HttpStatus, ptr } %2
}

define i32 @main() {
entry:
  %entry_result = call i32 @__user_entry()
  ret i32 %entry_result
}

attributes #0 = { mustprogress noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind willreturn memory(read) "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nounwind allocsize(0) "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #4 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { mustprogress noinline optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #7 = { nounwind allocsize(1) "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #8 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #9 = { nounwind willreturn memory(read) }
attributes #10 = { nounwind allocsize(0) }
attributes #11 = { nounwind }
attributes #12 = { nounwind allocsize(1) }

!llvm.ident = !{!0}
!llvm.module.flags = !{!1, !2, !3, !4, !5}

!0 = !{!"Ubuntu clang version 18.1.3 (1ubuntu1)"}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 2}
!5 = !{i32 7, !"frame-pointer", i32 2}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}
!11 = distinct !{!11, !7}
!12 = distinct !{!12, !7}
!13 = distinct !{!13, !7}
!14 = distinct !{!14, !7}
!15 = distinct !{!15, !7}
!16 = distinct !{!16, !7}
!17 = distinct !{!17, !7}
!18 = distinct !{!18, !7}
!19 = distinct !{!19, !7}
!20 = distinct !{!20, !7}
!21 = distinct !{!21, !7}
!22 = distinct !{!22, !7}
!23 = distinct !{!23, !7}
!24 = distinct !{!24, !7}
!25 = distinct !{!25, !7}
!26 = distinct !{!26, !7}
!27 = distinct !{!27, !7}
!28 = distinct !{!28, !7}
!29 = distinct !{!29, !7}
!30 = distinct !{!30, !7}
!31 = distinct !{!31, !7}
!32 = distinct !{!32, !7}
!33 = distinct !{!33, !7}
!34 = distinct !{!34, !7}
!35 = distinct !{!35, !7}
!36 = distinct !{!36, !7}
!37 = distinct !{!37, !7}
!38 = distinct !{!38, !7}
!39 = distinct !{!39, !7}
!40 = distinct !{!40, !7}
!41 = distinct !{!41, !7}
