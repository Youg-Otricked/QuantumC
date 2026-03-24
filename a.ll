; ModuleID = 'qc_module'
source_filename = "qc_module"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct._ffi_type = type { i64, i16, i16, ptr }
%struct.qc_jagged_array = type { ptr, ptr, i32, i32, i32 }
%struct.qc_list = type { ptr, i32, i32, i32 }
%struct.qc_map = type { ptr, ptr, i32, i32, i32, i32 }
%struct.ffi_cif = type { i32, i32, ptr, ptr, i32, i32 }
%"UnitTest::Test" = type { i32, i32, i32, i32, ptr }
%"AdvQBool::AQB" = type { i32, i32 }
%"Math::Number" = type { i32, ptr }
%"Math::Floating" = type { i32, ptr }

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
@.str.19 = private unnamed_addr constant [2 x i8] c"{\00", align 1
@.str.20 = private unnamed_addr constant [3 x i8] c": \00", align 1
@.str.21 = private unnamed_addr constant [2 x i8] c"}\00", align 1
@ffi_type_sint32 = external global %struct._ffi_type, align 8
@ffi_type_float = external global %struct._ffi_type, align 8
@ffi_type_double = external global %struct._ffi_type, align 8
@ffi_type_sint8 = external global %struct._ffi_type, align 8
@ffi_type_uint8 = external global %struct._ffi_type, align 8
@ffi_type_pointer = external global %struct._ffi_type, align 8
@ffi_type_void = external global %struct._ffi_type, align 8
@.str.22 = private constant [34 x i8] c"=== TESTING QUANTUM C STDLIB ===\0A\00"
@.str.23 = private constant [22 x i8] c"--- Testing Utils ---\00"
@.str.24 = private constant [18 x i8] c"range(0, 10, 2): \00"
@.str.25 = private constant [3 x i8] c", \00"
@.str.26 = private constant [3 x i8] c", \00"
@.str.27 = private constant [3 x i8] c", \00"
@.str.28 = private constant [3 x i8] c", \00"
@.str.29 = private constant [26 x i8] c"range(10, 0, -1) length: \00"
@.str.30 = private constant [20 x i8] c"Testing sleep(1)...\00"
@.str.31 = private constant [13 x i8] c"Sleep done!\0A\00"
@.str.32 = private constant [21 x i8] c"--- Testing Math ---\00"
@.str.33 = private constant [14 x i8] c"Math::pi() = \00"
@.str.34 = private constant [13 x i8] c"Math::e() = \00"
@.str.35 = private constant [20 x i8] c"Math::max(5, 10) = \00"
@.str.36 = private constant [20 x i8] c"Math::min(5, 10) = \00"
@.str.37 = private constant [18 x i8] c"Math::sqrt(16) = \00"
@.str.38 = private constant [18 x i8] c"Math::abs(-42) = \00"
@.str.39 = private constant [19 x i8] c"Math::ceil(3.2) = \00"
@.str.40 = private constant [20 x i8] c"Math::floor(3.8) = \00"
@.str.41 = private constant [16 x i8] c"Math::sin(0) = \00"
@.str.42 = private constant [16 x i8] c"Math::cos(0) = \00"
@.str.43 = private constant [16 x i8] c"Math::tan(0) = \00"
@.str.44 = private constant [20 x i8] c"Math::log(2.718) = \00"
@.str.45 = private constant [2 x i8] c"\0A\00"
@.str.46 = private constant [28 x i8] c"--- Testing Collections ---\00"
@.str.47 = private constant [23 x i8] c"has([1,2,3,4,5], 3) = \00"
@.str.48 = private constant [24 x i8] c"has([1,2,3,4,5], 10) = \00"
@.str.49 = private constant [28 x i8] c"index_of([1,2,3,4,5], 3) = \00"
@.str.50 = private constant [20 x i8] c"sort([5,2,8,1,9]): \00"
@.str.51 = private constant [3 x i8] c", \00"
@.str.52 = private constant [3 x i8] c", \00"
@.str.53 = private constant [3 x i8] c", \00"
@.str.54 = private constant [3 x i8] c", \00"
@.str.55 = private constant [23 x i8] c"reverse([1,2,3,4,5]): \00"
@.str.56 = private constant [3 x i8] c", \00"
@.str.57 = private constant [3 x i8] c", \00"
@.str.58 = private constant [3 x i8] c", \00"
@.str.59 = private constant [3 x i8] c", \00"
@.str.60 = private constant [2 x i8] c"\0A\00"
@.str.61 = private constant [25 x i8] c"remove([5,4,3,2,1], 2): \00"
@.str.62 = private constant [3 x i8] c", \00"
@.str.63 = private constant [3 x i8] c", \00"
@.str.64 = private constant [3 x i8] c", \00"
@.str.65 = private constant [2 x i8] c"\0A\00"
@.str.66 = private constant [25 x i8] c"--- Testing UnitTest ---\00"
@.str.67 = private constant [1 x i8] zeroinitializer
@.str.68 = private constant [16 x i8] c"[FAIL] On call \00"
@.str.69 = private constant [12 x i8] c": Expected \00"
@.str.70 = private constant [7 x i8] c", got \00"
@.str.71 = private constant [3 x i8] c". \00"
@.str.72 = private constant [17 x i8] c"[FAIL] Expected \00"
@.str.73 = private constant [7 x i8] c", got \00"
@.str.74 = private constant [3 x i8] c". \00"
@.str.75 = private constant [1 x i8] zeroinitializer
@.str.76 = private constant [19 x i8] c"[SUCCESS] on call \00"
@.str.77 = private constant [3 x i8] c": \00"
@.str.78 = private constant [15 x i8] c" was equal to \00"
@.str.79 = private constant [11 x i8] c"[SUCCESS] \00"
@.str.80 = private constant [15 x i8] c" was equal to \00"
@.str.81 = private constant [1 x i8] zeroinitializer
@.str.82 = private constant [7 x i8] c"5 == 5\00"
@.str.83 = private constant [1 x i8] zeroinitializer
@.str.84 = private constant [10 x i8] c"10 == 5+5\00"
@.str.85 = private constant [1 x i8] zeroinitializer
@.str.86 = private constant [13 x i8] c"true is true\00"
@.str.87 = private constant [1 x i8] zeroinitializer
@.str.88 = private constant [15 x i8] c"false is false\00"
@.str.89 = private constant [1 x i8] zeroinitializer
@.str.90 = private constant [16 x i8] c"[FAIL] On call \00"
@.str.91 = private constant [12 x i8] c": Expected \00"
@.str.92 = private constant [15 x i8] c" to not equal \00"
@.str.93 = private constant [3 x i8] c". \00"
@.str.94 = private constant [17 x i8] c"[FAIL] Expected \00"
@.str.95 = private constant [15 x i8] c" to not equal \00"
@.str.96 = private constant [3 x i8] c". \00"
@.str.97 = private constant [1 x i8] zeroinitializer
@.str.98 = private constant [19 x i8] c"[SUCCESS] on call \00"
@.str.99 = private constant [3 x i8] c": \00"
@.str.100 = private constant [18 x i8] c" wasn't equal to \00"
@.str.101 = private constant [11 x i8] c"[SUCCESS] \00"
@.str.102 = private constant [18 x i8] c" wasn't equal to \00"
@.str.103 = private constant [1 x i8] zeroinitializer
@.str.104 = private constant [8 x i8] c"5 != 10\00"
@.str.105 = private constant [26 x i8] c"\0A--- Testing AdvQBool ---\00"
@.str.106 = private constant [10 x i8] c"AQB(75): \00"
@.str.107 = private constant [40 x i8] c"Testing 10 evaluations of 75% true AQB:\00"
@.str.108 = private constant [5 x i8] c"Got \00"
@.str.109 = private constant [25 x i8] c"/10 true (expected ~7-8)\00"
@.str.110 = private constant [15 x i8] c"\0AAQB && test: \00"
@.str.111 = private constant [14 x i8] c"AQB || test: \00"
@.str.112 = private constant [12 x i8] c"!AQB test: \00"
@.str.113 = private constant [35 x i8] c"\0A=== ALL STDLIB TESTS COMPLETE ===\00"
@.str.114 = private constant [31 x i8] c"==============================\00"
@.str.115 = private constant [31 x i8] c"==============================\00"
@.str.116 = private constant [9 x i8] c"Failed: \00"
@.str.117 = private constant [9 x i8] c"Passed: \00"
@.str.118 = private constant [31 x i8] c"==============================\00"
@.str.119 = private constant [7 x i8] c"[FAIL]\00"
@.str.120 = private constant [7 x i8] c"[PASS]\00"
@.str.121 = private constant [4 x i8] c": [\00"
@.str.122 = private constant [2 x i8] c"/\00"
@.str.123 = private constant [2 x i8] c"]\00"
@.str.124 = private constant [4 x i8] c": [\00"
@.str.125 = private constant [2 x i8] c"/\00"
@.str.126 = private constant [2 x i8] c"]\00"
@.str.127 = private constant [1 x i8] zeroinitializer
@.str.128 = private constant [16 x i8] c"[FAIL] On call \00"
@.str.129 = private constant [34 x i8] c": Expected condition to be true. \00"
@.str.130 = private constant [39 x i8] c"[FAIL] Expected condition to be true. \00"
@.str.131 = private constant [1 x i8] zeroinitializer
@.str.132 = private constant [19 x i8] c"[SUCCESS] on call \00"
@.str.133 = private constant [21 x i8] c": Condition was true\00"
@.str.134 = private constant [29 x i8] c"[SUCCESS] Condition was true\00"
@.str.135 = private constant [1 x i8] zeroinitializer
@.str.136 = private constant [16 x i8] c"[FAIL] On call \00"
@.str.137 = private constant [35 x i8] c": Expected condition to be false. \00"
@.str.138 = private constant [40 x i8] c"[FAIL] Expected condition to be false. \00"
@.str.139 = private constant [1 x i8] zeroinitializer
@.str.140 = private constant [19 x i8] c"[SUCCESS] on call \00"
@.str.141 = private constant [22 x i8] c": Condition was false\00"
@.str.142 = private constant [30 x i8] c"[SUCCESS] Condition was false\00"
@.str.143 = private constant [19 x i8] c"Advanced QBool is \00"
@.str.144 = private constant [11 x i8] c" true and \00"
@.str.145 = private constant [8 x i8] c" false.\00"

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

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local void @qc_list_set(ptr noundef %0, i32 noundef %1, ptr noundef %2) #0 {
  %4 = alloca ptr, align 8
  %5 = alloca i32, align 4
  %6 = alloca ptr, align 8
  %7 = alloca ptr, align 8
  %8 = alloca i32, align 4
  %9 = alloca ptr, align 8
  store ptr %0, ptr %4, align 8
  store i32 %1, ptr %5, align 4
  store ptr %2, ptr %6, align 8
  %10 = load ptr, ptr %4, align 8
  store ptr %10, ptr %7, align 8
  %11 = load i32, ptr %5, align 4
  %12 = icmp slt i32 %11, 0
  br i1 %12, label %19, label %13

13:                                               ; preds = %3
  %14 = load i32, ptr %5, align 4
  %15 = load ptr, ptr %7, align 8
  %16 = getelementptr inbounds %struct.qc_list, ptr %15, i32 0, i32 1
  %17 = load i32, ptr %16, align 8
  %18 = icmp sge i32 %14, %17
  br i1 %18, label %19, label %20

19:                                               ; preds = %13, %3
  br label %59

20:                                               ; preds = %13
  %21 = load ptr, ptr %7, align 8
  %22 = getelementptr inbounds %struct.qc_list, ptr %21, i32 0, i32 3
  %23 = load i32, ptr %22, align 8
  %24 = icmp sle i32 %23, 5
  br i1 %24, label %25, label %51

25:                                               ; preds = %20
  %26 = load ptr, ptr %7, align 8
  %27 = getelementptr inbounds %struct.qc_list, ptr %26, i32 0, i32 3
  %28 = load i32, ptr %27, align 8
  %29 = call i32 @sizeof_type(i32 noundef %28)
  store i32 %29, ptr %8, align 4
  %30 = load i32, ptr %8, align 4
  %31 = sext i32 %30 to i64
  %32 = call noalias ptr @malloc(i64 noundef %31) #10
  store ptr %32, ptr %9, align 8
  %33 = load ptr, ptr %9, align 8
  %34 = load ptr, ptr %6, align 8
  %35 = load i32, ptr %8, align 4
  %36 = sext i32 %35 to i64
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %33, ptr align 1 %34, i64 %36, i1 false)
  %37 = load ptr, ptr %7, align 8
  %38 = getelementptr inbounds %struct.qc_list, ptr %37, i32 0, i32 0
  %39 = load ptr, ptr %38, align 8
  %40 = load i32, ptr %5, align 4
  %41 = sext i32 %40 to i64
  %42 = getelementptr inbounds ptr, ptr %39, i64 %41
  %43 = load ptr, ptr %42, align 8
  call void @free(ptr noundef %43) #11
  %44 = load ptr, ptr %9, align 8
  %45 = load ptr, ptr %7, align 8
  %46 = getelementptr inbounds %struct.qc_list, ptr %45, i32 0, i32 0
  %47 = load ptr, ptr %46, align 8
  %48 = load i32, ptr %5, align 4
  %49 = sext i32 %48 to i64
  %50 = getelementptr inbounds ptr, ptr %47, i64 %49
  store ptr %44, ptr %50, align 8
  br label %59

51:                                               ; preds = %20
  %52 = load ptr, ptr %6, align 8
  %53 = load ptr, ptr %7, align 8
  %54 = getelementptr inbounds %struct.qc_list, ptr %53, i32 0, i32 0
  %55 = load ptr, ptr %54, align 8
  %56 = load i32, ptr %5, align 4
  %57 = sext i32 %56 to i64
  %58 = getelementptr inbounds ptr, ptr %55, i64 %57
  store ptr %52, ptr %58, align 8
  br label %59

59:                                               ; preds = %51, %25, %19
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local ptr @qc_list_get(ptr noundef %0, i32 noundef %1) #0 {
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
  br label %23

15:                                               ; preds = %8
  %16 = load ptr, ptr %4, align 8
  %17 = getelementptr inbounds %struct.qc_list, ptr %16, i32 0, i32 0
  %18 = load ptr, ptr %17, align 8
  %19 = load i32, ptr %5, align 4
  %20 = sext i32 %19 to i64
  %21 = getelementptr inbounds ptr, ptr %18, i64 %20
  %22 = load ptr, ptr %21, align 8
  store ptr %22, ptr %3, align 8
  br label %23

23:                                               ; preds = %15, %14
  %24 = load ptr, ptr %3, align 8
  ret ptr %24
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
  %6 = call i32 (ptr, ...) @printf(ptr noundef @.str.19)
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
  %114 = call i32 (ptr, ...) @printf(ptr noundef @.str.20)
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
  %228 = call i32 (ptr, ...) @printf(ptr noundef @.str.21)
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

define void @"UnitTest::Test_Test"(ptr %0, i32 %1) {
entry:
  %Ttl = alloca i32, align 4
  store i32 %1, ptr %Ttl, align 4
  %Ttl1 = load i32, ptr %Ttl, align 4
  %2 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 0
  store i32 %Ttl1, ptr %2, align 4
  %3 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 1
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 2
  store i32 0, ptr %4, align 4
  %5 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 3
  store i32 0, ptr %5, align 4
  ret void
}

define i32 @"UnitTest::Test_Check"(ptr %0) {
entry:
  %message = alloca ptr, align 8
  %__foreach_i_message = alloca i32, align 4
  %1 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 1
  %Ran = load i32, ptr %1, align 4
  %2 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 0
  %Total = load i32, ptr %2, align 4
  %icmpge = icmp sge i32 %Ran, %Total
  br i1 %icmpge, label %then, label %ifcont

then:                                             ; preds = %entry
  %3 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 1
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 4
  %Messages = load ptr, ptr %4, align 8
  %list_len = call i32 @qc_list_length(ptr %Messages)
  %icmpgt = icmp sgt i32 %list_len, 0
  br i1 %icmpgt, label %then1, label %ifcont2

ifcont:                                           ; preds = %ifcont12, %entry
  ret i32 0

then1:                                            ; preds = %then
  %5 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 4
  %Messages3 = load ptr, ptr %5, align 8
  %coll_len = call i32 @qc_list_length(ptr %Messages3)
  store i32 0, ptr %__foreach_i_message, align 4
  br label %foreach.cond

ifcont2:                                          ; preds = %foreach.end, %then
  %6 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 3
  %Failed = load i32, ptr %6, align 4
  %fstr_i32 = call ptr @qc_to_string_int(i32 %Failed)
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.116, ptr %fstr_i32)
  call void @qc_print_string(ptr %fstr_concat)
  call void @qc_print_char(i8 10)
  %7 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 2
  %Passed = load i32, ptr %7, align 4
  %fstr_i327 = call ptr @qc_to_string_int(i32 %Passed)
  %fstr_concat8 = call ptr @qc_string_concat(ptr @.str.117, ptr %fstr_i327)
  call void @qc_print_string(ptr %fstr_concat8)
  call void @qc_print_char(i8 10)
  call void @qc_print_string(ptr @.str.118)
  call void @qc_print_char(i8 10)
  %8 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 3
  %Failed9 = load i32, ptr %8, align 4
  %icmpgt10 = icmp sgt i32 %Failed9, 0
  br i1 %icmpgt10, label %then11, label %else

foreach.cond:                                     ; preds = %foreach.inc, %then1
  %__foreach_i_message4 = load i32, ptr %__foreach_i_message, align 4
  %foreach_cmp = icmp slt i32 %__foreach_i_message4, %coll_len
  br i1 %foreach_cmp, label %foreach.body, label %foreach.end

foreach.body:                                     ; preds = %foreach.cond
  %elem_ptr = call ptr @qc_list_get(ptr %Messages3, i32 %__foreach_i_message4)
  store ptr %elem_ptr, ptr %message, align 8
  call void @qc_print_string(ptr @.str.114)
  call void @qc_print_char(i8 10)
  %message5 = load ptr, ptr %message, align 8
  call void @qc_print_string(ptr %message5)
  call void @qc_print_char(i8 10)
  br label %foreach.inc

foreach.inc:                                      ; preds = %foreach.body
  %__foreach_i_message6 = load i32, ptr %__foreach_i_message, align 4
  %i_inc = add i32 %__foreach_i_message6, 1
  store i32 %i_inc, ptr %__foreach_i_message, align 4
  br label %foreach.cond

foreach.end:                                      ; preds = %foreach.cond
  call void @qc_print_string(ptr @.str.115)
  call void @qc_print_char(i8 10)
  br label %ifcont2

then11:                                           ; preds = %ifcont2
  call void @qc_print_string(ptr @.str.119)
  call void @qc_print_char(i8 10)
  br label %ifcont12

ifcont12:                                         ; preds = %else, %then11
  br label %ifcont

else:                                             ; preds = %ifcont2
  call void @qc_print_string(ptr @.str.120)
  call void @qc_print_char(i8 10)
  br label %ifcont12
}

define i32 @"UnitTest::Test_Success"(ptr %0, ptr %1) {
entry:
  %push_arg = alloca ptr, align 8
  %message = alloca ptr, align 8
  store ptr %1, ptr %message, align 8
  %2 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 1
  %Ran = load i32, ptr %2, align 4
  %add = add i32 %Ran, 1
  %3 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 1
  store i32 %add, ptr %3, align 4
  %4 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 2
  %Passed = load i32, ptr %4, align 4
  %add1 = add i32 %Passed, 1
  %5 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 2
  store i32 %add1, ptr %5, align 4
  %6 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 4
  %Messages = load ptr, ptr %6, align 8
  %message2 = load ptr, ptr %message, align 8
  %7 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 1
  %Ran3 = load i32, ptr %7, align 4
  %fstr_i32 = call ptr @qc_to_string_int(i32 %Ran3)
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.121, ptr %fstr_i32)
  %fstr_concat4 = call ptr @qc_string_concat(ptr %fstr_concat, ptr @.str.122)
  %8 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 0
  %Total = load i32, ptr %8, align 4
  %fstr_i325 = call ptr @qc_to_string_int(i32 %Total)
  %fstr_concat6 = call ptr @qc_string_concat(ptr %fstr_concat4, ptr %fstr_i325)
  %fstr_concat7 = call ptr @qc_string_concat(ptr %fstr_concat6, ptr @.str.123)
  %str_concat = call ptr @qc_string_concat(ptr %message2, ptr %fstr_concat7)
  store ptr %str_concat, ptr %push_arg, align 8
  call void @qc_list_push(ptr %Messages, ptr %push_arg, i32 6)
  %Check_result = call i32 @"UnitTest::Test_Check"(ptr %0)
  ret i32 0
}

define i32 @"UnitTest::Test_Fail"(ptr %0, ptr %1) {
entry:
  %push_arg = alloca ptr, align 8
  %message = alloca ptr, align 8
  store ptr %1, ptr %message, align 8
  %2 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 1
  %Ran = load i32, ptr %2, align 4
  %add = add i32 %Ran, 1
  %3 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 1
  store i32 %add, ptr %3, align 4
  %4 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 3
  %Failed = load i32, ptr %4, align 4
  %add1 = add i32 %Failed, 1
  %5 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 3
  store i32 %add1, ptr %5, align 4
  %6 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 4
  %Messages = load ptr, ptr %6, align 8
  %message2 = load ptr, ptr %message, align 8
  %7 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 1
  %Ran3 = load i32, ptr %7, align 4
  %fstr_i32 = call ptr @qc_to_string_int(i32 %Ran3)
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.124, ptr %fstr_i32)
  %fstr_concat4 = call ptr @qc_string_concat(ptr %fstr_concat, ptr @.str.125)
  %8 = getelementptr inbounds %"UnitTest::Test", ptr %0, i32 0, i32 0
  %Total = load i32, ptr %8, align 4
  %fstr_i325 = call ptr @qc_to_string_int(i32 %Total)
  %fstr_concat6 = call ptr @qc_string_concat(ptr %fstr_concat4, ptr %fstr_i325)
  %fstr_concat7 = call ptr @qc_string_concat(ptr %fstr_concat6, ptr @.str.126)
  %str_concat = call ptr @qc_string_concat(ptr %message2, ptr %fstr_concat7)
  store ptr %str_concat, ptr %push_arg, align 8
  call void @qc_list_push(ptr %Messages, ptr %push_arg, i32 6)
  %Check_result = call i32 @"UnitTest::Test_Check"(ptr %0)
  ret i32 0
}

declare i32 @"UnitTest::Test_AssertEqual"(ptr, i32, i32, ptr, ptr)

define i32 @"UnitTest::Test_AssertTrue"(ptr %0, i1 %1, ptr %2, ptr %3) {
entry:
  %Call = alloca ptr, align 8
  %FailMessage = alloca ptr, align 8
  %cond = alloca i1, align 1
  store i1 %1, ptr %cond, align 1
  store ptr %2, ptr %FailMessage, align 8
  store ptr %3, ptr %Call, align 8
  %cond1 = load i1, ptr %cond, align 1
  %not = xor i1 %cond1, true
  br i1 %not, label %then, label %else

then:                                             ; preds = %entry
  %Call2 = load ptr, ptr %Call, align 8
  %4 = call i1 @qc_string_eq(ptr %Call2, ptr @.str.127)
  %5 = xor i1 %4, true
  br i1 %5, label %then3, label %else5

ifcont:                                           ; preds = %ifcont15, %ifcont4
  ret i32 0

else:                                             ; preds = %entry
  %Call13 = load ptr, ptr %Call, align 8
  %6 = call i1 @qc_string_eq(ptr %Call13, ptr @.str.131)
  %7 = xor i1 %6, true
  br i1 %7, label %then14, label %else16

then3:                                            ; preds = %then
  %Call6 = load ptr, ptr %Call, align 8
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.128, ptr %Call6)
  %fstr_concat7 = call ptr @qc_string_concat(ptr %fstr_concat, ptr @.str.129)
  %FailMessage8 = load ptr, ptr %FailMessage, align 8
  %fstr_concat9 = call ptr @qc_string_concat(ptr %fstr_concat7, ptr %FailMessage8)
  %Fail_result = call i32 @"UnitTest::Test_Fail"(ptr %0, ptr %fstr_concat9)
  br label %ifcont4

ifcont4:                                          ; preds = %else5, %then3
  br label %ifcont

else5:                                            ; preds = %then
  %FailMessage10 = load ptr, ptr %FailMessage, align 8
  %fstr_concat11 = call ptr @qc_string_concat(ptr @.str.130, ptr %FailMessage10)
  %Fail_result12 = call i32 @"UnitTest::Test_Fail"(ptr %0, ptr %fstr_concat11)
  br label %ifcont4

then14:                                           ; preds = %else
  %Call17 = load ptr, ptr %Call, align 8
  %fstr_concat18 = call ptr @qc_string_concat(ptr @.str.132, ptr %Call17)
  %fstr_concat19 = call ptr @qc_string_concat(ptr %fstr_concat18, ptr @.str.133)
  %Success_result = call i32 @"UnitTest::Test_Success"(ptr %0, ptr %fstr_concat19)
  br label %ifcont15

ifcont15:                                         ; preds = %else16, %then14
  br label %ifcont

else16:                                           ; preds = %else
  %Success_result20 = call i32 @"UnitTest::Test_Success"(ptr %0, ptr @.str.134)
  br label %ifcont15
}

define i32 @"UnitTest::Test_AssertFalse"(ptr %0, i1 %1, ptr %2, ptr %3) {
entry:
  %Call = alloca ptr, align 8
  %FailMessage = alloca ptr, align 8
  %cond = alloca i1, align 1
  store i1 %1, ptr %cond, align 1
  store ptr %2, ptr %FailMessage, align 8
  store ptr %3, ptr %Call, align 8
  %cond1 = load i1, ptr %cond, align 1
  br i1 %cond1, label %then, label %else

then:                                             ; preds = %entry
  %Call2 = load ptr, ptr %Call, align 8
  %4 = call i1 @qc_string_eq(ptr %Call2, ptr @.str.135)
  %5 = xor i1 %4, true
  br i1 %5, label %then3, label %else5

ifcont:                                           ; preds = %ifcont15, %ifcont4
  ret i32 0

else:                                             ; preds = %entry
  %Call13 = load ptr, ptr %Call, align 8
  %6 = call i1 @qc_string_eq(ptr %Call13, ptr @.str.139)
  %7 = xor i1 %6, true
  br i1 %7, label %then14, label %else16

then3:                                            ; preds = %then
  %Call6 = load ptr, ptr %Call, align 8
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.136, ptr %Call6)
  %fstr_concat7 = call ptr @qc_string_concat(ptr %fstr_concat, ptr @.str.137)
  %FailMessage8 = load ptr, ptr %FailMessage, align 8
  %fstr_concat9 = call ptr @qc_string_concat(ptr %fstr_concat7, ptr %FailMessage8)
  %Fail_result = call i32 @"UnitTest::Test_Fail"(ptr %0, ptr %fstr_concat9)
  br label %ifcont4

ifcont4:                                          ; preds = %else5, %then3
  br label %ifcont

else5:                                            ; preds = %then
  %FailMessage10 = load ptr, ptr %FailMessage, align 8
  %fstr_concat11 = call ptr @qc_string_concat(ptr @.str.138, ptr %FailMessage10)
  %Fail_result12 = call i32 @"UnitTest::Test_Fail"(ptr %0, ptr %fstr_concat11)
  br label %ifcont4

then14:                                           ; preds = %else
  %Call17 = load ptr, ptr %Call, align 8
  %fstr_concat18 = call ptr @qc_string_concat(ptr @.str.140, ptr %Call17)
  %fstr_concat19 = call ptr @qc_string_concat(ptr %fstr_concat18, ptr @.str.141)
  %Success_result = call i32 @"UnitTest::Test_Success"(ptr %0, ptr %fstr_concat19)
  br label %ifcont15

ifcont15:                                         ; preds = %else16, %then14
  br label %ifcont

else16:                                           ; preds = %else
  %Success_result20 = call i32 @"UnitTest::Test_Success"(ptr %0, ptr @.str.142)
  br label %ifcont15
}

declare i32 @"UnitTest::Test_AssertNotEqual"(ptr, i32, i32, ptr, ptr)

define void @"AdvQBool::AQB_AQB"(ptr %0, i32 %1) {
entry:
  %truth = alloca i32, align 4
  store i32 %1, ptr %truth, align 4
  %truth1 = load i32, ptr %truth, align 4
  %icmpgt = icmp sgt i32 %truth1, 100
  %truth2 = load i32, ptr %truth, align 4
  %icmplt = icmp slt i32 %truth2, 0
  %or = or i1 %icmpgt, %icmplt
  br i1 %or, label %then, label %ifcont

then:                                             ; preds = %entry
  %truth3 = load i32, ptr %truth, align 4
  %icmpgt4 = icmp sgt i32 %truth3, 100
  br i1 %icmpgt4, label %then5, label %else

ifcont:                                           ; preds = %ifcont6, %entry
  %truth9 = load i32, ptr %truth, align 4
  %2 = getelementptr inbounds %"AdvQBool::AQB", ptr %0, i32 0, i32 0
  store i32 %truth9, ptr %2, align 4
  %truth10 = load i32, ptr %truth, align 4
  %sub = sub i32 100, %truth10
  %3 = getelementptr inbounds %"AdvQBool::AQB", ptr %0, i32 0, i32 1
  store i32 %sub, ptr %3, align 4
  ret void

then5:                                            ; preds = %then
  %truth7 = load i32, ptr %truth, align 4
  store i32 100, ptr %truth, align 4
  br label %ifcont6

ifcont6:                                          ; preds = %else, %then5
  br label %ifcont

else:                                             ; preds = %then
  %truth8 = load i32, ptr %truth, align 4
  store i32 0, ptr %truth, align 4
  br label %ifcont6
}

define i32 @"AdvQBool::AQB_operator="(ptr %0, i32 %1) {
entry:
  %other = alloca i32, align 4
  store i32 %1, ptr %other, align 4
  %other1 = load i32, ptr %other, align 4
  %icmpgt = icmp sgt i32 %other1, 100
  %other2 = load i32, ptr %other, align 4
  %icmplt = icmp slt i32 %other2, 0
  %or = or i1 %icmpgt, %icmplt
  br i1 %or, label %then, label %ifcont

then:                                             ; preds = %entry
  %other3 = load i32, ptr %other, align 4
  %icmpgt4 = icmp sgt i32 %other3, 100
  br i1 %icmpgt4, label %then5, label %else

ifcont:                                           ; preds = %ifcont6, %entry
  %other9 = load i32, ptr %other, align 4
  %2 = getelementptr inbounds %"AdvQBool::AQB", ptr %0, i32 0, i32 0
  store i32 %other9, ptr %2, align 4
  %other10 = load i32, ptr %other, align 4
  %sub = sub i32 100, %other10
  %3 = getelementptr inbounds %"AdvQBool::AQB", ptr %0, i32 0, i32 1
  store i32 %sub, ptr %3, align 4
  ret i32 0

then5:                                            ; preds = %then
  %other7 = load i32, ptr %other, align 4
  store i32 100, ptr %other, align 4
  br label %ifcont6

ifcont6:                                          ; preds = %else, %then5
  br label %ifcont

else:                                             ; preds = %then
  %other8 = load i32, ptr %other, align 4
  store i32 0, ptr %other, align 4
  br label %ifcont6
}

declare i1 @"AdvQBool::AQB_operator&&"(ptr, i32)

declare i1 @"AdvQBool::AQB_operator||"(ptr, i32)

declare i1 @"AdvQBool::AQB_operator^"(ptr, i32)

define i1 @"AdvQBool::AQB_operator!"(ptr %0) {
entry:
  %eval_result = call i1 @"AdvQBool::AQB_eval"(ptr %0)
  %not = xor i1 %eval_result, true
  ret i1 %not
}

define i1 @"AdvQBool::AQB_eval"(ptr %0) {
entry:
  %builtin_call = call i32 @qc_random_range(i32 0, i32 100)
  %1 = getelementptr inbounds %"AdvQBool::AQB", ptr %0, i32 0, i32 1
  %FalseLevel = load i32, ptr %1, align 4
  %icmplt = icmp slt i32 %builtin_call, %FalseLevel
  br i1 %icmplt, label %then, label %else

then:                                             ; preds = %entry
  ret i1 false

ifcont:                                           ; No predecessors!
  ret i1 false

else:                                             ; preds = %entry
  ret i1 true
}

define i32 @"AdvQBool::AQB_init"(ptr %0) {
entry:
  %1 = getelementptr inbounds %"AdvQBool::AQB", ptr %0, i32 0, i32 0
  store i32 50, ptr %1, align 4
  %2 = getelementptr inbounds %"AdvQBool::AQB", ptr %0, i32 0, i32 1
  store i32 50, ptr %2, align 4
  ret i32 0
}

define ptr @"AdvQBool::AQB_repr"(ptr %0) {
entry:
  %1 = getelementptr inbounds %"AdvQBool::AQB", ptr %0, i32 0, i32 0
  %TruthLevel = load i32, ptr %1, align 4
  %fstr_i32 = call ptr @qc_to_string_int(i32 %TruthLevel)
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.143, ptr %fstr_i32)
  %fstr_concat1 = call ptr @qc_string_concat(ptr %fstr_concat, ptr @.str.144)
  %2 = getelementptr inbounds %"AdvQBool::AQB", ptr %0, i32 0, i32 1
  %FalseLevel = load i32, ptr %2, align 4
  %fstr_i322 = call ptr @qc_to_string_int(i32 %FalseLevel)
  %fstr_concat3 = call ptr @qc_string_concat(ptr %fstr_concat1, ptr %fstr_i322)
  %fstr_concat4 = call ptr @qc_string_concat(ptr %fstr_concat3, ptr @.str.145)
  ret ptr %fstr_concat4
}

define ptr @"Utils::range"(i32 %start, i32 %stop, i32 %step) {
entry:
  %copy_dest_idx = alloca i32, align 4
  %copy_i = alloca i32, align 4
  %push_arg27 = alloca i32, align 4
  %push_arg = alloca i32, align 4
  %fin = alloca ptr, align 8
  %step3 = alloca i32, align 4
  %stop2 = alloca i32, align 4
  %start1 = alloca i32, align 4
  store i32 %start, ptr %start1, align 4
  store i32 %stop, ptr %stop2, align 4
  store i32 %step, ptr %step3, align 4
  %list_ptr = call ptr @qc_create_list(i32 0)
  store ptr %list_ptr, ptr %fin, align 8
  %step4 = load i32, ptr %step3, align 4
  %icmpgt = icmp sgt i32 %step4, 0
  %start5 = load i32, ptr %start1, align 4
  %stop6 = load i32, ptr %stop2, align 4
  %icmple = icmp sle i32 %start5, %stop6
  %and = and i1 %icmpgt, %icmple
  br i1 %and, label %then, label %elif.cond

then:                                             ; preds = %entry
  br label %for.cond

ifcont:                                           ; preds = %for.end21, %for.end
  %fin31 = load ptr, ptr %fin, align 8
  %list_len = call i32 @qc_list_length(ptr %fin31)
  %0 = add i32 0, %list_len
  %1 = zext i32 %0 to i64
  %2 = mul i64 %1, 4
  %runtime_arr = call ptr @malloc(i64 %2)
  %fin32 = load ptr, ptr %fin, align 8
  %list_len33 = call i32 @qc_list_length(ptr %fin32)
  store i32 0, ptr %copy_i, align 4
  store i32 0, ptr %copy_dest_idx, align 4
  br label %copy_loop

elif.cond:                                        ; preds = %entry
  %step13 = load i32, ptr %step3, align 4
  %icmplt14 = icmp slt i32 %step13, 0
  %start15 = load i32, ptr %start1, align 4
  %stop16 = load i32, ptr %stop2, align 4
  %icmpge = icmp sge i32 %start15, %stop16
  %and17 = and i1 %icmplt14, %icmpge
  br i1 %and17, label %elif.body, label %else

elif.body:                                        ; preds = %elif.cond
  br label %for.cond18

else:                                             ; preds = %elif.cond
  %empty_arr = call ptr @malloc(i64 0)
  ret ptr %empty_arr

for.cond:                                         ; preds = %for.inc, %then
  %start7 = load i32, ptr %start1, align 4
  %stop8 = load i32, ptr %stop2, align 4
  %icmplt = icmp slt i32 %start7, %stop8
  br i1 %icmplt, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %fin9 = load ptr, ptr %fin, align 8
  %start10 = load i32, ptr %start1, align 4
  store i32 %start10, ptr %push_arg, align 4
  call void @qc_list_push(ptr %fin9, ptr %push_arg, i32 0)
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %start11 = load i32, ptr %start1, align 4
  %step12 = load i32, ptr %step3, align 4
  %add = add i32 %start11, %step12
  store i32 %add, ptr %start1, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  br label %ifcont

for.cond18:                                       ; preds = %for.inc20, %elif.body
  %start22 = load i32, ptr %start1, align 4
  %stop23 = load i32, ptr %stop2, align 4
  %icmpgt24 = icmp sgt i32 %start22, %stop23
  br i1 %icmpgt24, label %for.body19, label %for.end21

for.body19:                                       ; preds = %for.cond18
  %fin25 = load ptr, ptr %fin, align 8
  %start26 = load i32, ptr %start1, align 4
  store i32 %start26, ptr %push_arg27, align 4
  call void @qc_list_push(ptr %fin25, ptr %push_arg27, i32 0)
  br label %for.inc20

for.inc20:                                        ; preds = %for.body19
  %start28 = load i32, ptr %start1, align 4
  %step29 = load i32, ptr %step3, align 4
  %add30 = add i32 %start28, %step29
  store i32 %add30, ptr %start1, align 4
  br label %for.cond18

for.end21:                                        ; preds = %for.cond18
  br label %ifcont

copy_loop:                                        ; preds = %copy_body, %ifcont
  %3 = load i32, ptr %copy_i, align 4
  %4 = icmp slt i32 %3, %list_len33
  br i1 %4, label %copy_body, label %copy_end

copy_body:                                        ; preds = %copy_loop
  %5 = load i32, ptr %copy_dest_idx, align 4
  %6 = getelementptr i32, ptr %fin32, i32 %3
  %7 = load i32, ptr %6, align 4
  %8 = getelementptr i32, ptr %runtime_arr, i32 %5
  store i32 %7, ptr %8, align 4
  %9 = add i32 %3, 1
  store i32 %9, ptr %copy_i, align 4
  %10 = add i32 %5, 1
  store i32 %10, ptr %copy_dest_idx, align 4
  br label %copy_loop

copy_end:                                         ; preds = %copy_loop
  %11 = load i32, ptr %copy_dest_idx, align 4
  ret ptr %runtime_arr
}

define i32 @"Utils::sleep"(i64 %crr) {
entry:
  %"Utils::i" = alloca i32, align 4
  %crr1 = alloca i64, align 8
  store i64 %crr, ptr %crr1, align 8
  %crr2 = load i64, ptr %crr1, align 8
  %builtin_call = call i32 @qc_time()
  %sext = sext i32 %builtin_call to i64
  %add = add i64 %crr2, %sext
  store i64 %add, ptr %crr1, align 8
  br label %while.cond

while.cond:                                       ; preds = %for.end, %entry
  %builtin_call3 = call i32 @qc_time()
  %crr4 = load i64, ptr %crr1, align 8
  %promote_int = sext i32 %builtin_call3 to i64
  %icmplt = icmp slt i64 %promote_int, %crr4
  br i1 %icmplt, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  store i32 0, ptr %"Utils::i", align 4
  br label %for.cond

while.end:                                        ; preds = %while.cond
  ret i32 0

for.cond:                                         ; preds = %for.inc, %while.body
  %i = load i32, ptr %"Utils::i", align 4
  %icmplt5 = icmp slt i32 %i, 5000
  br i1 %icmplt5, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %i6 = load i32, ptr %"Utils::i", align 4
  %i7 = load i32, ptr %"Utils::i", align 4
  %i8 = load i32, ptr %"Utils::i", align 4
  %inc = add i32 %i8, 1
  store i32 %inc, ptr %"Utils::i", align 4
  store i32 %inc, ptr %"Utils::i", align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  br label %while.cond
}

define ptr @"Collections::sort"(ptr %collection) {
entry:
  %"Collections::iv" = alloca i32, align 4
  %"Collections::i" = alloca i32, align 4
  %"Collections::n" = alloca i32, align 4
  %"Collections::swapped" = alloca i1, align 1
  %collection1 = alloca ptr, align 8
  store ptr %collection, ptr %collection1, align 8
  store i1 true, ptr %"Collections::swapped", align 1
  %collection2 = load ptr, ptr %collection1, align 8
  %list_len = call i32 @qc_list_length(ptr %collection2)
  store i32 %list_len, ptr %"Collections::n", align 4
  br label %while.cond

while.cond:                                       ; preds = %for.end, %entry
  %swapped = load i1, ptr %"Collections::swapped", align 1
  br i1 %swapped, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %swapped3 = load i1, ptr %"Collections::swapped", align 1
  store i1 false, ptr %"Collections::swapped", align 1
  store i32 0, ptr %"Collections::i", align 4
  br label %for.cond

while.end:                                        ; preds = %while.cond
  %collection31 = load ptr, ptr %collection1, align 8
  ret ptr %collection31

for.cond:                                         ; preds = %for.inc, %while.body
  %i = load i32, ptr %"Collections::i", align 4
  %n = load i32, ptr %"Collections::n", align 4
  %sub = sub i32 %n, 1
  %icmplt = icmp slt i32 %i, %sub
  br i1 %icmplt, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %arr_ptr = load ptr, ptr %collection1, align 8
  %i4 = load i32, ptr %"Collections::i", align 4
  %arr_elem_ptr = getelementptr i32, ptr %arr_ptr, i32 %i4
  %arr_elem = load i32, ptr %arr_elem_ptr, align 4
  %arr_ptr5 = load ptr, ptr %collection1, align 8
  %i6 = load i32, ptr %"Collections::i", align 4
  %add = add i32 %i6, 1
  %arr_elem_ptr7 = getelementptr i32, ptr %arr_ptr5, i32 %add
  %arr_elem8 = load i32, ptr %arr_elem_ptr7, align 4
  %icmpgt = icmp sgt i32 %arr_elem, %arr_elem8
  br i1 %icmpgt, label %then, label %ifcont

for.inc:                                          ; preds = %ifcont
  %i26 = load i32, ptr %"Collections::i", align 4
  %i27 = load i32, ptr %"Collections::i", align 4
  %i28 = load i32, ptr %"Collections::i", align 4
  %inc = add i32 %i28, 1
  store i32 %inc, ptr %"Collections::i", align 4
  store i32 %inc, ptr %"Collections::i", align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %n29 = load i32, ptr %"Collections::n", align 4
  %sub30 = sub i32 %n29, 1
  store i32 %sub30, ptr %"Collections::n", align 4
  br label %while.cond

then:                                             ; preds = %for.body
  %arr_ptr9 = load ptr, ptr %collection1, align 8
  %i10 = load i32, ptr %"Collections::i", align 4
  %arr_elem_ptr11 = getelementptr i32, ptr %arr_ptr9, i32 %i10
  %arr_elem12 = load i32, ptr %arr_elem_ptr11, align 4
  store i32 %arr_elem12, ptr %"Collections::iv", align 4
  %i13 = load i32, ptr %"Collections::i", align 4
  %arr_ptr14 = load ptr, ptr %collection1, align 8
  %i15 = load i32, ptr %"Collections::i", align 4
  %add16 = add i32 %i15, 1
  %arr_elem_ptr17 = getelementptr i32, ptr %arr_ptr14, i32 %add16
  %arr_elem18 = load i32, ptr %arr_elem_ptr17, align 4
  %arr_ptr19 = load ptr, ptr %collection1, align 8
  %arr_elem_ptr20 = getelementptr i32, ptr %arr_ptr19, i32 %i13
  store i32 %arr_elem18, ptr %arr_elem_ptr20, align 4
  %i21 = load i32, ptr %"Collections::i", align 4
  %add22 = add i32 %i21, 1
  %iv = load i32, ptr %"Collections::iv", align 4
  %arr_ptr23 = load ptr, ptr %collection1, align 8
  %arr_elem_ptr24 = getelementptr i32, ptr %arr_ptr23, i32 %add22
  store i32 %iv, ptr %arr_elem_ptr24, align 4
  %swapped25 = load i1, ptr %"Collections::swapped", align 1
  store i1 true, ptr %"Collections::swapped", align 1
  br label %ifcont

ifcont:                                           ; preds = %then, %for.body
  br label %for.inc
}

define double @"Math::e"() {
entry:
  ret double 0x4005BF0A8B145769
}

define double @"Math::pi"() {
entry:
  ret double 0x400921FB54442D18
}

define %"Math::Number" @"Math::max"(%"Math::Number" %a, %"Math::Number" %b) {
entry:
  %union_op_result = alloca i1, align 1
  %b2 = alloca %"Math::Number", align 8
  %a1 = alloca %"Math::Number", align 8
  store %"Math::Number" %a, ptr %a1, align 8
  store %"Math::Number" %b, ptr %b2, align 8
  %a3 = load %"Math::Number", ptr %a1, align 8
  %b4 = load %"Math::Number", ptr %b2, align 8
  %ltag = extractvalue %"Math::Number" %a3, 0
  %lpayload = extractvalue %"Math::Number" %a3, 1
  %rpayload = extractvalue %"Math::Number" %b4, 1
  switch i32 %ltag, label %union_op_end [
    i32 0, label %union_op_case_0
    i32 1, label %union_op_case_1
    i32 2, label %union_op_case_2
  ]

union_op_end:                                     ; preds = %union_op_case_2, %union_op_case_1, %union_op_case_0, %entry
  %union_op_result9 = load i1, ptr %union_op_result, align 1
  br i1 %union_op_result9, label %then, label %ifcont

union_op_case_0:                                  ; preds = %entry
  %lmember = load i32, ptr %lpayload, align 4
  %rmember = load i32, ptr %rpayload, align 4
  %0 = icmp sgt i32 %lmember, %rmember
  store i1 %0, ptr %union_op_result, align 1
  br label %union_op_end

union_op_case_1:                                  ; preds = %entry
  %lmember5 = load float, ptr %lpayload, align 4
  %rmember6 = load float, ptr %rpayload, align 4
  %1 = fcmp ogt float %lmember5, %rmember6
  store i1 %1, ptr %union_op_result, align 1
  br label %union_op_end

union_op_case_2:                                  ; preds = %entry
  %lmember7 = load double, ptr %lpayload, align 8
  %rmember8 = load double, ptr %rpayload, align 8
  %2 = fcmp ogt double %lmember7, %rmember8
  store i1 %2, ptr %union_op_result, align 1
  br label %union_op_end

then:                                             ; preds = %union_op_end
  %a10 = load %"Math::Number", ptr %a1, align 8
  ret %"Math::Number" %a10

ifcont:                                           ; preds = %union_op_end
  %b11 = load %"Math::Number", ptr %b2, align 8
  ret %"Math::Number" %b11
}

define %"Math::Number" @"Math::min"(%"Math::Number" %a, %"Math::Number" %b) {
entry:
  %union_op_result = alloca i1, align 1
  %b2 = alloca %"Math::Number", align 8
  %a1 = alloca %"Math::Number", align 8
  store %"Math::Number" %a, ptr %a1, align 8
  store %"Math::Number" %b, ptr %b2, align 8
  %a3 = load %"Math::Number", ptr %a1, align 8
  %b4 = load %"Math::Number", ptr %b2, align 8
  %ltag = extractvalue %"Math::Number" %a3, 0
  %lpayload = extractvalue %"Math::Number" %a3, 1
  %rpayload = extractvalue %"Math::Number" %b4, 1
  switch i32 %ltag, label %union_op_end [
    i32 0, label %union_op_case_0
    i32 1, label %union_op_case_1
    i32 2, label %union_op_case_2
  ]

union_op_end:                                     ; preds = %union_op_case_2, %union_op_case_1, %union_op_case_0, %entry
  %union_op_result9 = load i1, ptr %union_op_result, align 1
  br i1 %union_op_result9, label %then, label %ifcont

union_op_case_0:                                  ; preds = %entry
  %lmember = load i32, ptr %lpayload, align 4
  %rmember = load i32, ptr %rpayload, align 4
  %0 = icmp sgt i32 %lmember, %rmember
  store i1 %0, ptr %union_op_result, align 1
  br label %union_op_end

union_op_case_1:                                  ; preds = %entry
  %lmember5 = load float, ptr %lpayload, align 4
  %rmember6 = load float, ptr %rpayload, align 4
  %1 = fcmp ogt float %lmember5, %rmember6
  store i1 %1, ptr %union_op_result, align 1
  br label %union_op_end

union_op_case_2:                                  ; preds = %entry
  %lmember7 = load double, ptr %lpayload, align 8
  %rmember8 = load double, ptr %rpayload, align 8
  %2 = fcmp ogt double %lmember7, %rmember8
  store i1 %2, ptr %union_op_result, align 1
  br label %union_op_end

then:                                             ; preds = %union_op_end
  %b10 = load %"Math::Number", ptr %b2, align 8
  ret %"Math::Number" %b10

ifcont:                                           ; preds = %union_op_end
  %a11 = load %"Math::Number", ptr %a1, align 8
  ret %"Math::Number" %a11
}

define %"Math::Number" @"Math::sqrt"(%"Math::Number" %val) {
entry:
  %val1 = alloca %"Math::Number", align 8
  store %"Math::Number" %val, ptr %val1, align 8
  %val2 = load %"Math::Number", ptr %val1, align 8
  %tag = extractvalue %"Math::Number" %val2, 0
  %payload = extractvalue %"Math::Number" %val2, 1
  %union_normalized = load i32, ptr %payload, align 4
  %to_double = call double @qc_to_double_from_int(i32 %union_normalized)
  %pow = call double @llvm.pow.f64(double %to_double, double 5.000000e-01)
  %union_heap = call ptr @malloc(i64 8)
  store double %pow, ptr %union_heap, align 8
  %0 = insertvalue %"Math::Number" { i32 2, ptr undef }, ptr %union_heap, 1
  ret %"Math::Number" %0
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare double @llvm.pow.f64(double, double) #8

define %"Math::Number" @"Math::root"(%"Math::Number" %val, %"Math::Number" %power) {
entry:
  %"Math::exp" = alloca double, align 8
  %"Math::base" = alloca double, align 8
  %power2 = alloca %"Math::Number", align 8
  %val1 = alloca %"Math::Number", align 8
  store %"Math::Number" %val, ptr %val1, align 8
  store %"Math::Number" %power, ptr %power2, align 8
  %val3 = load %"Math::Number", ptr %val1, align 8
  %tag = extractvalue %"Math::Number" %val3, 0
  %payload = extractvalue %"Math::Number" %val3, 1
  %union_normalized = load i32, ptr %payload, align 4
  %to_double = call double @qc_to_double_from_int(i32 %union_normalized)
  store double %to_double, ptr %"Math::base", align 8
  %power4 = load %"Math::Number", ptr %power2, align 8
  %tag5 = extractvalue %"Math::Number" %power4, 0
  %payload6 = extractvalue %"Math::Number" %power4, 1
  %union_normalized7 = load i32, ptr %payload6, align 4
  %to_double8 = call double @qc_to_double_from_int(i32 %union_normalized7)
  %fdiv = fdiv double 1.000000e+00, %to_double8
  store double %fdiv, ptr %"Math::exp", align 8
  %base = load double, ptr %"Math::base", align 8
  %exp = load double, ptr %"Math::exp", align 8
  %pow = call double @llvm.pow.f64(double %base, double %exp)
  %union_heap = call ptr @malloc(i64 8)
  store double %pow, ptr %union_heap, align 8
  %0 = insertvalue %"Math::Number" { i32 2, ptr undef }, ptr %union_heap, 1
  ret %"Math::Number" %0
}

define i32 @"Math::ceil"(%"Math::Floating" %a) {
entry:
  %"Math::i" = alloca i32, align 4
  %"Math::d" = alloca double, align 8
  %a1 = alloca %"Math::Floating", align 8
  store %"Math::Floating" %a, ptr %a1, align 8
  %a2 = load %"Math::Floating", ptr %a1, align 8
  %tag = extractvalue %"Math::Floating" %a2, 0
  %payload = extractvalue %"Math::Floating" %a2, 1
  %union_normalized = load float, ptr %payload, align 4
  %to_double = call double @qc_to_double_from_float(float %union_normalized)
  store double %to_double, ptr %"Math::d", align 8
  %d = load double, ptr %"Math::d", align 8
  %to_int = call i32 @qc_to_int_from_double(double %d)
  store i32 %to_int, ptr %"Math::i", align 4
  %d3 = load double, ptr %"Math::d", align 8
  %i = load i32, ptr %"Math::i", align 4
  %to_double4 = call double @qc_to_double_from_int(i32 %i)
  %fcmpeq = fcmp oeq double %d3, %to_double4
  br i1 %fcmpeq, label %then, label %elif.cond

then:                                             ; preds = %entry
  %i5 = load i32, ptr %"Math::i", align 4
  ret i32 %i5

ifcont:                                           ; No predecessors!
  ret i32 0

elif.cond:                                        ; preds = %entry
  %d6 = load double, ptr %"Math::d", align 8
  %fcmpgt = fcmp ogt double %d6, 0.000000e+00
  br i1 %fcmpgt, label %elif.body, label %else

elif.body:                                        ; preds = %elif.cond
  %i7 = load i32, ptr %"Math::i", align 4
  %add = add i32 %i7, 1
  ret i32 %add

else:                                             ; preds = %elif.cond
  %i8 = load i32, ptr %"Math::i", align 4
  ret i32 %i8
}

define i32 @"Math::floor"(%"Math::Floating" %a) {
entry:
  %"Math::i" = alloca i32, align 4
  %"Math::d" = alloca double, align 8
  %a1 = alloca %"Math::Floating", align 8
  store %"Math::Floating" %a, ptr %a1, align 8
  %a2 = load %"Math::Floating", ptr %a1, align 8
  %tag = extractvalue %"Math::Floating" %a2, 0
  %payload = extractvalue %"Math::Floating" %a2, 1
  %union_normalized = load float, ptr %payload, align 4
  %to_double = call double @qc_to_double_from_float(float %union_normalized)
  store double %to_double, ptr %"Math::d", align 8
  %d = load double, ptr %"Math::d", align 8
  %to_int = call i32 @qc_to_int_from_double(double %d)
  store i32 %to_int, ptr %"Math::i", align 4
  %d3 = load double, ptr %"Math::d", align 8
  %fcmpge = fcmp oge double %d3, 0.000000e+00
  br i1 %fcmpge, label %then, label %else

then:                                             ; preds = %entry
  %i = load i32, ptr %"Math::i", align 4
  ret i32 %i

ifcont:                                           ; preds = %ifcont8
  ret i32 0

else:                                             ; preds = %entry
  %d4 = load double, ptr %"Math::d", align 8
  %i5 = load i32, ptr %"Math::i", align 4
  %to_double6 = call double @qc_to_double_from_int(i32 %i5)
  %fcmpeq = fcmp oeq double %d4, %to_double6
  br i1 %fcmpeq, label %then7, label %else9

then7:                                            ; preds = %else
  %i10 = load i32, ptr %"Math::i", align 4
  ret i32 %i10

ifcont8:                                          ; No predecessors!
  br label %ifcont

else9:                                            ; preds = %else
  %i11 = load i32, ptr %"Math::i", align 4
  %sub = sub i32 %i11, 1
  ret i32 %sub
}

define %"Math::Number" @"Math::abs"(%"Math::Number" %a) {
entry:
  %union_op_result10 = alloca double, align 8
  %union_op_result = alloca i1, align 1
  %a1 = alloca %"Math::Number", align 8
  store %"Math::Number" %a, ptr %a1, align 8
  %a2 = load %"Math::Number", ptr %a1, align 8
  %tag = extractvalue %"Math::Number" %a2, 0
  %payload = extractvalue %"Math::Number" %a2, 1
  switch i32 %tag, label %union_op_end [
    i32 0, label %union_op_case_0
    i32 1, label %union_op_case_1
    i32 2, label %union_op_case_2
  ]

union_op_end:                                     ; preds = %union_op_case_2, %union_op_case_1, %union_op_case_0, %entry
  %union_op_result5 = load i1, ptr %union_op_result, align 1
  br i1 %union_op_result5, label %then, label %ifcont

union_op_case_0:                                  ; preds = %entry
  %member = load i32, ptr %payload, align 4
  %0 = icmp slt i32 %member, 0
  store i1 %0, ptr %union_op_result, align 1
  br label %union_op_end

union_op_case_1:                                  ; preds = %entry
  %member3 = load float, ptr %payload, align 4
  %1 = fcmp olt float %member3, 0.000000e+00
  store i1 %1, ptr %union_op_result, align 1
  br label %union_op_end

union_op_case_2:                                  ; preds = %entry
  %member4 = load double, ptr %payload, align 8
  %2 = fcmp olt double %member4, 0.000000e+00
  store i1 %2, ptr %union_op_result, align 1
  br label %union_op_end

then:                                             ; preds = %union_op_end
  %a6 = load %"Math::Number", ptr %a1, align 8
  %tag7 = extractvalue %"Math::Number" %a6, 0
  %payload8 = extractvalue %"Math::Number" %a6, 1
  switch i32 %tag7, label %union_op_end9 [
    i32 0, label %union_op_case_011
    i32 1, label %union_op_case_113
    i32 2, label %union_op_case_215
  ]

ifcont:                                           ; preds = %union_op_end
  %a18 = load %"Math::Number", ptr %a1, align 8
  ret %"Math::Number" %a18

union_op_end9:                                    ; preds = %union_op_case_215, %union_op_case_113, %union_op_case_011, %then
  %union_op_result17 = load double, ptr %union_op_result10, align 8
  %union_heap = call ptr @malloc(i64 8)
  store double %union_op_result17, ptr %union_heap, align 8
  %3 = insertvalue %"Math::Number" { i32 2, ptr undef }, ptr %union_heap, 1
  ret %"Math::Number" %3

union_op_case_011:                                ; preds = %then
  %member12 = load i32, ptr %payload8, align 4
  %4 = mul i32 %member12, -1
  %5 = sitofp i32 %4 to double
  store double %5, ptr %union_op_result10, align 8
  br label %union_op_end9

union_op_case_113:                                ; preds = %then
  %member14 = load float, ptr %payload8, align 4
  %6 = fmul float %member14, -1.000000e+00
  %7 = fpext float %6 to double
  store double %7, ptr %union_op_result10, align 8
  br label %union_op_end9

union_op_case_215:                                ; preds = %then
  %member16 = load double, ptr %payload8, align 8
  %8 = fmul double %member16, -1.000000e+00
  store double %8, ptr %union_op_result10, align 8
  br label %union_op_end9
}

define double @"Math::sin"(double %x) {
entry:
  %"Math::i" = alloca i32, align 4
  %"Math::n" = alloca i32, align 4
  %"Math::term" = alloca double, align 8
  %"Math::result" = alloca double, align 8
  %"Math::pi" = alloca double, align 8
  %x1 = alloca double, align 8
  store double %x, ptr %x1, align 8
  store double 0x400921FB54442D18, ptr %"Math::pi", align 8
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %x2 = load double, ptr %x1, align 8
  %pi = load double, ptr %"Math::pi", align 8
  %fcmpgt = fcmp ogt double %x2, %pi
  br i1 %fcmpgt, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %x3 = load double, ptr %x1, align 8
  %pi4 = load double, ptr %"Math::pi", align 8
  %fmul = fmul double 2.000000e+00, %pi4
  %fsub = fsub double %x3, %fmul
  store double %fsub, ptr %x1, align 8
  br label %while.cond

while.end:                                        ; preds = %while.cond
  br label %while.cond5

while.cond5:                                      ; preds = %while.body6, %while.end
  %x8 = load double, ptr %x1, align 8
  %pi9 = load double, ptr %"Math::pi", align 8
  %fneg = fneg double %pi9
  %fcmplt = fcmp olt double %x8, %fneg
  br i1 %fcmplt, label %while.body6, label %while.end7

while.body6:                                      ; preds = %while.cond5
  %x10 = load double, ptr %x1, align 8
  %pi11 = load double, ptr %"Math::pi", align 8
  %fmul12 = fmul double 2.000000e+00, %pi11
  %fadd = fadd double %x10, %fmul12
  store double %fadd, ptr %x1, align 8
  br label %while.cond5

while.end7:                                       ; preds = %while.cond5
  store double 0.000000e+00, ptr %"Math::result", align 8
  %x13 = load double, ptr %x1, align 8
  store double %x13, ptr %"Math::term", align 8
  store i32 1, ptr %"Math::n", align 4
  store i32 0, ptr %"Math::i", align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %while.end7
  %i = load i32, ptr %"Math::i", align 4
  %icmplt = icmp slt i32 %i, 10
  br i1 %icmplt, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %result = load double, ptr %"Math::result", align 8
  %term = load double, ptr %"Math::term", align 8
  %fadd14 = fadd double %result, %term
  store double %fadd14, ptr %"Math::result", align 8
  %term15 = load double, ptr %"Math::term", align 8
  %x16 = load double, ptr %x1, align 8
  %fmul17 = fmul double -1.000000e+00, %x16
  %x18 = load double, ptr %x1, align 8
  %fmul19 = fmul double %fmul17, %x18
  %n = load i32, ptr %"Math::n", align 4
  %mul = mul i32 2, %n
  %n20 = load i32, ptr %"Math::n", align 4
  %mul21 = mul i32 2, %n20
  %add = add i32 %mul21, 1
  %mul22 = mul i32 %mul, %add
  %int_to_float = sitofp i32 %mul22 to double
  %fdiv = fdiv double %fmul19, %int_to_float
  %fmul23 = fmul double %term15, %fdiv
  store double %fmul23, ptr %"Math::term", align 8
  %n24 = load i32, ptr %"Math::n", align 4
  %n25 = load i32, ptr %"Math::n", align 4
  %n26 = load i32, ptr %"Math::n", align 4
  %inc = add i32 %n26, 1
  store i32 %inc, ptr %"Math::n", align 4
  store i32 %inc, ptr %"Math::n", align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %i27 = load i32, ptr %"Math::i", align 4
  %i28 = load i32, ptr %"Math::i", align 4
  %i29 = load i32, ptr %"Math::i", align 4
  %inc30 = add i32 %i29, 1
  store i32 %inc30, ptr %"Math::i", align 4
  store i32 %inc30, ptr %"Math::i", align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %result31 = load double, ptr %"Math::result", align 8
  ret double %result31
}

define double @"Math::cos"(double %x) {
entry:
  %"Math::i" = alloca i32, align 4
  %"Math::n" = alloca i32, align 4
  %"Math::term" = alloca double, align 8
  %"Math::result" = alloca double, align 8
  %"Math::pi" = alloca double, align 8
  %x1 = alloca double, align 8
  store double %x, ptr %x1, align 8
  store double 0x400921FB54442D18, ptr %"Math::pi", align 8
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %x2 = load double, ptr %x1, align 8
  %pi = load double, ptr %"Math::pi", align 8
  %fcmpgt = fcmp ogt double %x2, %pi
  br i1 %fcmpgt, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %x3 = load double, ptr %x1, align 8
  %pi4 = load double, ptr %"Math::pi", align 8
  %fmul = fmul double 2.000000e+00, %pi4
  %fsub = fsub double %x3, %fmul
  store double %fsub, ptr %x1, align 8
  br label %while.cond

while.end:                                        ; preds = %while.cond
  br label %while.cond5

while.cond5:                                      ; preds = %while.body6, %while.end
  %x8 = load double, ptr %x1, align 8
  %pi9 = load double, ptr %"Math::pi", align 8
  %fneg = fneg double %pi9
  %fcmplt = fcmp olt double %x8, %fneg
  br i1 %fcmplt, label %while.body6, label %while.end7

while.body6:                                      ; preds = %while.cond5
  %x10 = load double, ptr %x1, align 8
  %pi11 = load double, ptr %"Math::pi", align 8
  %fmul12 = fmul double 2.000000e+00, %pi11
  %fadd = fadd double %x10, %fmul12
  store double %fadd, ptr %x1, align 8
  br label %while.cond5

while.end7:                                       ; preds = %while.cond5
  store double 0.000000e+00, ptr %"Math::result", align 8
  store double 1.000000e+00, ptr %"Math::term", align 8
  store i32 1, ptr %"Math::n", align 4
  store i32 0, ptr %"Math::i", align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %while.end7
  %i = load i32, ptr %"Math::i", align 4
  %icmplt = icmp slt i32 %i, 10
  br i1 %icmplt, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %result = load double, ptr %"Math::result", align 8
  %term = load double, ptr %"Math::term", align 8
  %fadd13 = fadd double %result, %term
  store double %fadd13, ptr %"Math::result", align 8
  %term14 = load double, ptr %"Math::term", align 8
  %x15 = load double, ptr %x1, align 8
  %fmul16 = fmul double -1.000000e+00, %x15
  %x17 = load double, ptr %x1, align 8
  %fmul18 = fmul double %fmul16, %x17
  %n = load i32, ptr %"Math::n", align 4
  %mul = mul i32 2, %n
  %sub = sub i32 %mul, 1
  %n19 = load i32, ptr %"Math::n", align 4
  %mul20 = mul i32 2, %n19
  %mul21 = mul i32 %sub, %mul20
  %int_to_float = sitofp i32 %mul21 to double
  %fdiv = fdiv double %fmul18, %int_to_float
  %fmul22 = fmul double %term14, %fdiv
  store double %fmul22, ptr %"Math::term", align 8
  %n23 = load i32, ptr %"Math::n", align 4
  %n24 = load i32, ptr %"Math::n", align 4
  %n25 = load i32, ptr %"Math::n", align 4
  %inc = add i32 %n25, 1
  store i32 %inc, ptr %"Math::n", align 4
  store i32 %inc, ptr %"Math::n", align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %i26 = load i32, ptr %"Math::i", align 4
  %i27 = load i32, ptr %"Math::i", align 4
  %i28 = load i32, ptr %"Math::i", align 4
  %inc29 = add i32 %i28, 1
  store i32 %inc29, ptr %"Math::i", align 4
  store i32 %inc29, ptr %"Math::i", align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %result30 = load double, ptr %"Math::result", align 8
  ret double %result30
}

define double @"Math::tan"(double %x) {
entry:
  %x1 = alloca double, align 8
  store double %x, ptr %x1, align 8
  %x2 = load double, ptr %x1, align 8
  %calltmp = call double @"Math::sin"(double %x2)
  %x3 = load double, ptr %x1, align 8
  %calltmp4 = call double @"Math::cos"(double %x3)
  %fdiv = fdiv double %calltmp, %calltmp4
  ret double %fdiv
}

define double @"Math::log"(double %x) {
entry:
  %"Math::i" = alloca i32, align 4
  %"Math::term" = alloca double, align 8
  %"Math::result" = alloca double, align 8
  %"Math::y" = alloca double, align 8
  %"Math::n" = alloca i32, align 4
  %"Math::log2" = alloca double, align 8
  %x1 = alloca double, align 8
  store double %x, ptr %x1, align 8
  %x2 = load double, ptr %x1, align 8
  %fcmple = fcmp ole double %x2, 0.000000e+00
  br i1 %fcmple, label %then, label %ifcont

then:                                             ; preds = %entry
  ret double 0.000000e+00

ifcont:                                           ; preds = %entry
  store double 0x3FE62E42FEFA39EF, ptr %"Math::log2", align 8
  store i32 0, ptr %"Math::n", align 4
  br label %while.cond

while.cond:                                       ; preds = %while.body, %ifcont
  %x3 = load double, ptr %x1, align 8
  %fcmpgt = fcmp ogt double %x3, 2.000000e+00
  br i1 %fcmpgt, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %x4 = load double, ptr %x1, align 8
  %fdiv = fdiv double %x4, 2.000000e+00
  store double %fdiv, ptr %x1, align 8
  %n = load i32, ptr %"Math::n", align 4
  %n5 = load i32, ptr %"Math::n", align 4
  %n6 = load i32, ptr %"Math::n", align 4
  %inc = add i32 %n6, 1
  store i32 %inc, ptr %"Math::n", align 4
  store i32 %inc, ptr %"Math::n", align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  br label %while.cond7

while.cond7:                                      ; preds = %while.body8, %while.end
  %x10 = load double, ptr %x1, align 8
  %fcmplt = fcmp olt double %x10, 5.000000e-01
  br i1 %fcmplt, label %while.body8, label %while.end9

while.body8:                                      ; preds = %while.cond7
  %x11 = load double, ptr %x1, align 8
  %fmul = fmul double %x11, 2.000000e+00
  store double %fmul, ptr %x1, align 8
  %n12 = load i32, ptr %"Math::n", align 4
  %n13 = load i32, ptr %"Math::n", align 4
  %n14 = load i32, ptr %"Math::n", align 4
  %dec = sub i32 %n14, 1
  store i32 %dec, ptr %"Math::n", align 4
  store i32 %dec, ptr %"Math::n", align 4
  br label %while.cond7

while.end9:                                       ; preds = %while.cond7
  %x15 = load double, ptr %x1, align 8
  %fsub = fsub double %x15, 1.000000e+00
  store double %fsub, ptr %"Math::y", align 8
  store double 0.000000e+00, ptr %"Math::result", align 8
  %y = load double, ptr %"Math::y", align 8
  store double %y, ptr %"Math::term", align 8
  store i32 1, ptr %"Math::i", align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %while.end9
  %i = load i32, ptr %"Math::i", align 4
  %icmple = icmp sle i32 %i, 20
  br i1 %icmple, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %result = load double, ptr %"Math::result", align 8
  %term = load double, ptr %"Math::term", align 8
  %i16 = load i32, ptr %"Math::i", align 4
  %to_double = call double @qc_to_double_from_int(i32 %i16)
  %fdiv17 = fdiv double %term, %to_double
  %fadd = fadd double %result, %fdiv17
  store double %fadd, ptr %"Math::result", align 8
  %term18 = load double, ptr %"Math::term", align 8
  %y19 = load double, ptr %"Math::y", align 8
  %fneg = fneg double %y19
  %fmul20 = fmul double %term18, %fneg
  store double %fmul20, ptr %"Math::term", align 8
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %i21 = load i32, ptr %"Math::i", align 4
  %i22 = load i32, ptr %"Math::i", align 4
  %i23 = load i32, ptr %"Math::i", align 4
  %inc24 = add i32 %i23, 1
  store i32 %inc24, ptr %"Math::i", align 4
  store i32 %inc24, ptr %"Math::i", align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %result25 = load double, ptr %"Math::result", align 8
  %n26 = load i32, ptr %"Math::n", align 4
  %log2 = load double, ptr %"Math::log2", align 8
  %int_to_float = sitofp i32 %n26 to double
  %fmul27 = fmul double %int_to_float, %log2
  %fadd28 = fadd double %result25, %fmul27
  ret double %fadd28
}

define i32 @__user_entry() {
entry:
  %aqb2 = alloca %"AdvQBool::AQB", align 8
  %i = alloca i32, align 4
  %trueCount = alloca i32, align 4
  %aqb = alloca %"AdvQBool::AQB", align 8
  %test = alloca %"UnitTest::Test", align 8
  %reversed = alloca ptr, align 8
  %toReverse = alloca ptr, align 8
  %temp_elem164 = alloca i32, align 4
  %temp_elem163 = alloca i32, align 4
  %temp_elem162 = alloca i32, align 4
  %temp_elem161 = alloca i32, align 4
  %temp_elem160 = alloca i32, align 4
  %sorted = alloca ptr, align 8
  %unsorted = alloca ptr, align 8
  %temp_elem128 = alloca i32, align 4
  %temp_elem127 = alloca i32, align 4
  %temp_elem126 = alloca i32, align 4
  %temp_elem125 = alloca i32, align 4
  %temp_elem124 = alloca i32, align 4
  %nums = alloca ptr, align 8
  %temp_elem114 = alloca i32, align 4
  %temp_elem113 = alloca i32, align 4
  %temp_elem112 = alloca i32, align 4
  %temp_elem111 = alloca i32, align 4
  %temp_elem = alloca i32, align 4
  %fstr_union_result80 = alloca ptr, align 8
  %fstr_union_result64 = alloca ptr, align 8
  %fstr_union_result48 = alloca ptr, align 8
  %fstr_union_result = alloca ptr, align 8
  %r2 = alloca ptr, align 8
  %r1 = alloca ptr, align 8
  call void @qc_println(ptr @.str.22)
  call void @qc_println(ptr @.str.23)
  %calltmp = call ptr @"Utils::range"(i32 0, i32 10, i32 2)
  store ptr %calltmp, ptr %r1, align 8
  %r11 = load ptr, ptr %r1, align 8
  %list_len = call i32 @qc_list_length(ptr %r11)
  %to_str = call ptr @qc_to_string_int(i32 %list_len)
  call void @qc_println(ptr %to_str)
  %arr_ptr = load ptr, ptr %r1, align 8
  %arr_elem_ptr = getelementptr i32, ptr %arr_ptr, i32 0
  %arr_elem = load i32, ptr %arr_elem_ptr, align 4
  %fstr_i32 = call ptr @qc_to_string_int(i32 %arr_elem)
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.24, ptr %fstr_i32)
  %fstr_concat2 = call ptr @qc_string_concat(ptr %fstr_concat, ptr @.str.25)
  %arr_ptr3 = load ptr, ptr %r1, align 8
  %arr_elem_ptr4 = getelementptr i32, ptr %arr_ptr3, i32 1
  %arr_elem5 = load i32, ptr %arr_elem_ptr4, align 4
  %fstr_i326 = call ptr @qc_to_string_int(i32 %arr_elem5)
  %fstr_concat7 = call ptr @qc_string_concat(ptr %fstr_concat2, ptr %fstr_i326)
  %fstr_concat8 = call ptr @qc_string_concat(ptr %fstr_concat7, ptr @.str.26)
  %arr_ptr9 = load ptr, ptr %r1, align 8
  %arr_elem_ptr10 = getelementptr i32, ptr %arr_ptr9, i32 2
  %arr_elem11 = load i32, ptr %arr_elem_ptr10, align 4
  %fstr_i3212 = call ptr @qc_to_string_int(i32 %arr_elem11)
  %fstr_concat13 = call ptr @qc_string_concat(ptr %fstr_concat8, ptr %fstr_i3212)
  %fstr_concat14 = call ptr @qc_string_concat(ptr %fstr_concat13, ptr @.str.27)
  %arr_ptr15 = load ptr, ptr %r1, align 8
  %arr_elem_ptr16 = getelementptr i32, ptr %arr_ptr15, i32 3
  %arr_elem17 = load i32, ptr %arr_elem_ptr16, align 4
  %fstr_i3218 = call ptr @qc_to_string_int(i32 %arr_elem17)
  %fstr_concat19 = call ptr @qc_string_concat(ptr %fstr_concat14, ptr %fstr_i3218)
  %fstr_concat20 = call ptr @qc_string_concat(ptr %fstr_concat19, ptr @.str.28)
  %arr_ptr21 = load ptr, ptr %r1, align 8
  %arr_elem_ptr22 = getelementptr i32, ptr %arr_ptr21, i32 4
  %arr_elem23 = load i32, ptr %arr_elem_ptr22, align 4
  %fstr_i3224 = call ptr @qc_to_string_int(i32 %arr_elem23)
  %fstr_concat25 = call ptr @qc_string_concat(ptr %fstr_concat20, ptr %fstr_i3224)
  call void @qc_println(ptr %fstr_concat25)
  %calltmp26 = call ptr @"Utils::range"(i32 10, i32 0, i32 -1)
  store ptr %calltmp26, ptr %r2, align 8
  %r227 = load ptr, ptr %r2, align 8
  %list_len28 = call i32 @qc_list_length(ptr %r227)
  %fstr_i3229 = call ptr @qc_to_string_int(i32 %list_len28)
  %fstr_concat30 = call ptr @qc_string_concat(ptr @.str.29, ptr %fstr_i3229)
  call void @qc_println(ptr %fstr_concat30)
  call void @qc_println(ptr @.str.30)
  %calltmp31 = call i32 @"Utils::sleep"(i32 1)
  call void @qc_println(ptr @.str.31)
  call void @qc_println(ptr @.str.32)
  %calltmp32 = call double @"Math::pi"()
  %fstr_f64 = call ptr @qc_to_string_double(double %calltmp32)
  %fstr_concat33 = call ptr @qc_string_concat(ptr @.str.33, ptr %fstr_f64)
  call void @qc_println(ptr %fstr_concat33)
  %calltmp34 = call double @"Math::e"()
  %fstr_f6435 = call ptr @qc_to_string_double(double %calltmp34)
  %fstr_concat36 = call ptr @qc_string_concat(ptr @.str.34, ptr %fstr_f6435)
  call void @qc_println(ptr %fstr_concat36)
  %calltmp37 = call %"Math::Number" @"Math::max"(i32 5, i32 10)
  %union_tag = extractvalue %"Math::Number" %calltmp37, 0
  %union_payload = extractvalue %"Math::Number" %calltmp37, 1
  switch i32 %union_tag, label %fstr_union_end [
    i32 0, label %fstr_union_case_0
    i32 1, label %fstr_union_case_1
    i32 2, label %fstr_union_case_2
  ]

fstr_union_end:                                   ; preds = %fstr_union_case_2, %fstr_union_case_1, %fstr_union_case_0, %entry
  %fstr_union_result42 = load ptr, ptr %fstr_union_result, align 8
  %fstr_concat43 = call ptr @qc_string_concat(ptr @.str.35, ptr %fstr_union_result42)
  call void @qc_println(ptr %fstr_concat43)
  %calltmp44 = call %"Math::Number" @"Math::min"(i32 5, i32 10)
  %union_tag45 = extractvalue %"Math::Number" %calltmp44, 0
  %union_payload46 = extractvalue %"Math::Number" %calltmp44, 1
  switch i32 %union_tag45, label %fstr_union_end47 [
    i32 0, label %fstr_union_case_049
    i32 1, label %fstr_union_case_152
    i32 2, label %fstr_union_case_255
  ]

fstr_union_case_0:                                ; preds = %entry
  %union_member = load i32, ptr %union_payload, align 4
  %fstr_i3238 = call ptr @qc_to_string_int(i32 %union_member)
  store ptr %fstr_i3238, ptr %fstr_union_result, align 8
  br label %fstr_union_end

fstr_union_case_1:                                ; preds = %entry
  %union_member39 = load float, ptr %union_payload, align 4
  %fstr_f32 = call ptr @qc_to_string_float(float %union_member39)
  store ptr %fstr_f32, ptr %fstr_union_result, align 8
  br label %fstr_union_end

fstr_union_case_2:                                ; preds = %entry
  %union_member40 = load double, ptr %union_payload, align 8
  %fstr_f6441 = call ptr @qc_to_string_double(double %union_member40)
  store ptr %fstr_f6441, ptr %fstr_union_result, align 8
  br label %fstr_union_end

fstr_union_end47:                                 ; preds = %fstr_union_case_255, %fstr_union_case_152, %fstr_union_case_049, %fstr_union_end
  %fstr_union_result58 = load ptr, ptr %fstr_union_result48, align 8
  %fstr_concat59 = call ptr @qc_string_concat(ptr @.str.36, ptr %fstr_union_result58)
  call void @qc_println(ptr %fstr_concat59)
  %calltmp60 = call %"Math::Number" @"Math::sqrt"(i32 16)
  %union_tag61 = extractvalue %"Math::Number" %calltmp60, 0
  %union_payload62 = extractvalue %"Math::Number" %calltmp60, 1
  switch i32 %union_tag61, label %fstr_union_end63 [
    i32 0, label %fstr_union_case_065
    i32 1, label %fstr_union_case_168
    i32 2, label %fstr_union_case_271
  ]

fstr_union_case_049:                              ; preds = %fstr_union_end
  %union_member50 = load i32, ptr %union_payload46, align 4
  %fstr_i3251 = call ptr @qc_to_string_int(i32 %union_member50)
  store ptr %fstr_i3251, ptr %fstr_union_result48, align 8
  br label %fstr_union_end47

fstr_union_case_152:                              ; preds = %fstr_union_end
  %union_member53 = load float, ptr %union_payload46, align 4
  %fstr_f3254 = call ptr @qc_to_string_float(float %union_member53)
  store ptr %fstr_f3254, ptr %fstr_union_result48, align 8
  br label %fstr_union_end47

fstr_union_case_255:                              ; preds = %fstr_union_end
  %union_member56 = load double, ptr %union_payload46, align 8
  %fstr_f6457 = call ptr @qc_to_string_double(double %union_member56)
  store ptr %fstr_f6457, ptr %fstr_union_result48, align 8
  br label %fstr_union_end47

fstr_union_end63:                                 ; preds = %fstr_union_case_271, %fstr_union_case_168, %fstr_union_case_065, %fstr_union_end47
  %fstr_union_result74 = load ptr, ptr %fstr_union_result64, align 8
  %fstr_concat75 = call ptr @qc_string_concat(ptr @.str.37, ptr %fstr_union_result74)
  call void @qc_println(ptr %fstr_concat75)
  %calltmp76 = call %"Math::Number" @"Math::abs"(i32 -42)
  %union_tag77 = extractvalue %"Math::Number" %calltmp76, 0
  %union_payload78 = extractvalue %"Math::Number" %calltmp76, 1
  switch i32 %union_tag77, label %fstr_union_end79 [
    i32 0, label %fstr_union_case_081
    i32 1, label %fstr_union_case_184
    i32 2, label %fstr_union_case_287
  ]

fstr_union_case_065:                              ; preds = %fstr_union_end47
  %union_member66 = load i32, ptr %union_payload62, align 4
  %fstr_i3267 = call ptr @qc_to_string_int(i32 %union_member66)
  store ptr %fstr_i3267, ptr %fstr_union_result64, align 8
  br label %fstr_union_end63

fstr_union_case_168:                              ; preds = %fstr_union_end47
  %union_member69 = load float, ptr %union_payload62, align 4
  %fstr_f3270 = call ptr @qc_to_string_float(float %union_member69)
  store ptr %fstr_f3270, ptr %fstr_union_result64, align 8
  br label %fstr_union_end63

fstr_union_case_271:                              ; preds = %fstr_union_end47
  %union_member72 = load double, ptr %union_payload62, align 8
  %fstr_f6473 = call ptr @qc_to_string_double(double %union_member72)
  store ptr %fstr_f6473, ptr %fstr_union_result64, align 8
  br label %fstr_union_end63

fstr_union_end79:                                 ; preds = %fstr_union_case_287, %fstr_union_case_184, %fstr_union_case_081, %fstr_union_end63
  %fstr_union_result90 = load ptr, ptr %fstr_union_result80, align 8
  %fstr_concat91 = call ptr @qc_string_concat(ptr @.str.38, ptr %fstr_union_result90)
  call void @qc_println(ptr %fstr_concat91)
  %calltmp92 = call i32 @"Math::ceil"(double 3.200000e+00)
  %fstr_i3293 = call ptr @qc_to_string_int(i32 %calltmp92)
  %fstr_concat94 = call ptr @qc_string_concat(ptr @.str.39, ptr %fstr_i3293)
  call void @qc_println(ptr %fstr_concat94)
  %calltmp95 = call i32 @"Math::floor"(double 3.800000e+00)
  %fstr_i3296 = call ptr @qc_to_string_int(i32 %calltmp95)
  %fstr_concat97 = call ptr @qc_string_concat(ptr @.str.40, ptr %fstr_i3296)
  call void @qc_println(ptr %fstr_concat97)
  %calltmp98 = call double @"Math::sin"(double 0.000000e+00)
  %fstr_f6499 = call ptr @qc_to_string_double(double %calltmp98)
  %fstr_concat100 = call ptr @qc_string_concat(ptr @.str.41, ptr %fstr_f6499)
  call void @qc_println(ptr %fstr_concat100)
  %calltmp101 = call double @"Math::cos"(double 0.000000e+00)
  %fstr_f64102 = call ptr @qc_to_string_double(double %calltmp101)
  %fstr_concat103 = call ptr @qc_string_concat(ptr @.str.42, ptr %fstr_f64102)
  call void @qc_println(ptr %fstr_concat103)
  %calltmp104 = call double @"Math::tan"(double 0.000000e+00)
  %fstr_f64105 = call ptr @qc_to_string_double(double %calltmp104)
  %fstr_concat106 = call ptr @qc_string_concat(ptr @.str.43, ptr %fstr_f64105)
  call void @qc_println(ptr %fstr_concat106)
  %calltmp107 = call double @"Math::log"(double 2.718000e+00)
  %fstr_f64108 = call ptr @qc_to_string_double(double %calltmp107)
  %fstr_concat109 = call ptr @qc_string_concat(ptr @.str.44, ptr %fstr_f64108)
  %fstr_concat110 = call ptr @qc_string_concat(ptr %fstr_concat109, ptr @.str.45)
  call void @qc_println(ptr %fstr_concat110)
  call void @qc_println(ptr @.str.46)
  %list_ptr = call ptr @qc_create_list(i32 0)
  store i32 1, ptr %temp_elem, align 4
  call void @qc_list_push(ptr %list_ptr, ptr %temp_elem, i32 0)
  store i32 2, ptr %temp_elem111, align 4
  call void @qc_list_push(ptr %list_ptr, ptr %temp_elem111, i32 0)
  store i32 3, ptr %temp_elem112, align 4
  call void @qc_list_push(ptr %list_ptr, ptr %temp_elem112, i32 0)
  store i32 4, ptr %temp_elem113, align 4
  call void @qc_list_push(ptr %list_ptr, ptr %temp_elem113, i32 0)
  store i32 5, ptr %temp_elem114, align 4
  call void @qc_list_push(ptr %list_ptr, ptr %temp_elem114, i32 0)
  store ptr %list_ptr, ptr %nums, align 8
  %nums115 = load ptr, ptr %nums, align 8
  %0 = call i1 @"Collections::has_list<int>_int"(ptr %nums115, i32 3)
  %fstr_bool = call ptr @qc_to_string_bool(i1 %0)
  %fstr_concat116 = call ptr @qc_string_concat(ptr @.str.47, ptr %fstr_bool)
  call void @qc_println(ptr %fstr_concat116)
  %nums117 = load ptr, ptr %nums, align 8
  %1 = call i1 @"Collections::has_list<int>_int"(ptr %nums117, i32 10)
  %fstr_bool118 = call ptr @qc_to_string_bool(i1 %1)
  %fstr_concat119 = call ptr @qc_string_concat(ptr @.str.48, ptr %fstr_bool118)
  call void @qc_println(ptr %fstr_concat119)
  %nums120 = load ptr, ptr %nums, align 8
  %2 = call i32 @"Collections::index_of_list<int>_int"(ptr %nums120, i32 3)
  %fstr_i32121 = call ptr @qc_to_string_int(i32 %2)
  %fstr_concat122 = call ptr @qc_string_concat(ptr @.str.49, ptr %fstr_i32121)
  call void @qc_println(ptr %fstr_concat122)
  %list_ptr123 = call ptr @qc_create_list(i32 0)
  store i32 5, ptr %temp_elem124, align 4
  call void @qc_list_push(ptr %list_ptr123, ptr %temp_elem124, i32 0)
  store i32 2, ptr %temp_elem125, align 4
  call void @qc_list_push(ptr %list_ptr123, ptr %temp_elem125, i32 0)
  store i32 8, ptr %temp_elem126, align 4
  call void @qc_list_push(ptr %list_ptr123, ptr %temp_elem126, i32 0)
  store i32 1, ptr %temp_elem127, align 4
  call void @qc_list_push(ptr %list_ptr123, ptr %temp_elem127, i32 0)
  store i32 9, ptr %temp_elem128, align 4
  call void @qc_list_push(ptr %list_ptr123, ptr %temp_elem128, i32 0)
  store ptr %list_ptr123, ptr %unsorted, align 8
  %list_ptr129 = call ptr @qc_create_list(i32 0)
  %unsorted130 = load ptr, ptr %unsorted, align 8
  %calltmp131 = call ptr @"Collections::sort"(ptr %unsorted130)
  store ptr %calltmp131, ptr %sorted, align 8
  %list_ptr132 = load ptr, ptr %sorted, align 8
  %list_elem_ptr = call ptr @qc_list_get(ptr %list_ptr132, i32 0)
  %list_elem = load i32, ptr %list_elem_ptr, align 4
  %fstr_i32133 = call ptr @qc_to_string_int(i32 %list_elem)
  %fstr_concat134 = call ptr @qc_string_concat(ptr @.str.50, ptr %fstr_i32133)
  %fstr_concat135 = call ptr @qc_string_concat(ptr %fstr_concat134, ptr @.str.51)
  %list_ptr136 = load ptr, ptr %sorted, align 8
  %list_elem_ptr137 = call ptr @qc_list_get(ptr %list_ptr136, i32 1)
  %list_elem138 = load i32, ptr %list_elem_ptr137, align 4
  %fstr_i32139 = call ptr @qc_to_string_int(i32 %list_elem138)
  %fstr_concat140 = call ptr @qc_string_concat(ptr %fstr_concat135, ptr %fstr_i32139)
  %fstr_concat141 = call ptr @qc_string_concat(ptr %fstr_concat140, ptr @.str.52)
  %list_ptr142 = load ptr, ptr %sorted, align 8
  %list_elem_ptr143 = call ptr @qc_list_get(ptr %list_ptr142, i32 2)
  %list_elem144 = load i32, ptr %list_elem_ptr143, align 4
  %fstr_i32145 = call ptr @qc_to_string_int(i32 %list_elem144)
  %fstr_concat146 = call ptr @qc_string_concat(ptr %fstr_concat141, ptr %fstr_i32145)
  %fstr_concat147 = call ptr @qc_string_concat(ptr %fstr_concat146, ptr @.str.53)
  %list_ptr148 = load ptr, ptr %sorted, align 8
  %list_elem_ptr149 = call ptr @qc_list_get(ptr %list_ptr148, i32 3)
  %list_elem150 = load i32, ptr %list_elem_ptr149, align 4
  %fstr_i32151 = call ptr @qc_to_string_int(i32 %list_elem150)
  %fstr_concat152 = call ptr @qc_string_concat(ptr %fstr_concat147, ptr %fstr_i32151)
  %fstr_concat153 = call ptr @qc_string_concat(ptr %fstr_concat152, ptr @.str.54)
  %list_ptr154 = load ptr, ptr %sorted, align 8
  %list_elem_ptr155 = call ptr @qc_list_get(ptr %list_ptr154, i32 4)
  %list_elem156 = load i32, ptr %list_elem_ptr155, align 4
  %fstr_i32157 = call ptr @qc_to_string_int(i32 %list_elem156)
  %fstr_concat158 = call ptr @qc_string_concat(ptr %fstr_concat153, ptr %fstr_i32157)
  call void @qc_println(ptr %fstr_concat158)
  %list_ptr159 = call ptr @qc_create_list(i32 0)
  store i32 1, ptr %temp_elem160, align 4
  call void @qc_list_push(ptr %list_ptr159, ptr %temp_elem160, i32 0)
  store i32 2, ptr %temp_elem161, align 4
  call void @qc_list_push(ptr %list_ptr159, ptr %temp_elem161, i32 0)
  store i32 3, ptr %temp_elem162, align 4
  call void @qc_list_push(ptr %list_ptr159, ptr %temp_elem162, i32 0)
  store i32 4, ptr %temp_elem163, align 4
  call void @qc_list_push(ptr %list_ptr159, ptr %temp_elem163, i32 0)
  store i32 5, ptr %temp_elem164, align 4
  call void @qc_list_push(ptr %list_ptr159, ptr %temp_elem164, i32 0)
  store ptr %list_ptr159, ptr %toReverse, align 8
  %list_ptr165 = call ptr @qc_create_list(i32 0)
  %toReverse166 = load ptr, ptr %toReverse, align 8
  %3 = call ptr @"Collections::reverse_list<int>"(ptr %toReverse166)
  store ptr %3, ptr %reversed, align 8
  %list_ptr167 = load ptr, ptr %reversed, align 8
  %list_elem_ptr168 = call ptr @qc_list_get(ptr %list_ptr167, i32 0)
  %list_elem169 = load i32, ptr %list_elem_ptr168, align 4
  %fstr_i32170 = call ptr @qc_to_string_int(i32 %list_elem169)
  %fstr_concat171 = call ptr @qc_string_concat(ptr @.str.55, ptr %fstr_i32170)
  %fstr_concat172 = call ptr @qc_string_concat(ptr %fstr_concat171, ptr @.str.56)
  %list_ptr173 = load ptr, ptr %reversed, align 8
  %list_elem_ptr174 = call ptr @qc_list_get(ptr %list_ptr173, i32 1)
  %list_elem175 = load i32, ptr %list_elem_ptr174, align 4
  %fstr_i32176 = call ptr @qc_to_string_int(i32 %list_elem175)
  %fstr_concat177 = call ptr @qc_string_concat(ptr %fstr_concat172, ptr %fstr_i32176)
  %fstr_concat178 = call ptr @qc_string_concat(ptr %fstr_concat177, ptr @.str.57)
  %list_ptr179 = load ptr, ptr %reversed, align 8
  %list_elem_ptr180 = call ptr @qc_list_get(ptr %list_ptr179, i32 2)
  %list_elem181 = load i32, ptr %list_elem_ptr180, align 4
  %fstr_i32182 = call ptr @qc_to_string_int(i32 %list_elem181)
  %fstr_concat183 = call ptr @qc_string_concat(ptr %fstr_concat178, ptr %fstr_i32182)
  %fstr_concat184 = call ptr @qc_string_concat(ptr %fstr_concat183, ptr @.str.58)
  %list_ptr185 = load ptr, ptr %reversed, align 8
  %list_elem_ptr186 = call ptr @qc_list_get(ptr %list_ptr185, i32 3)
  %list_elem187 = load i32, ptr %list_elem_ptr186, align 4
  %fstr_i32188 = call ptr @qc_to_string_int(i32 %list_elem187)
  %fstr_concat189 = call ptr @qc_string_concat(ptr %fstr_concat184, ptr %fstr_i32188)
  %fstr_concat190 = call ptr @qc_string_concat(ptr %fstr_concat189, ptr @.str.59)
  %list_ptr191 = load ptr, ptr %reversed, align 8
  %list_elem_ptr192 = call ptr @qc_list_get(ptr %list_ptr191, i32 4)
  %list_elem193 = load i32, ptr %list_elem_ptr192, align 4
  %fstr_i32194 = call ptr @qc_to_string_int(i32 %list_elem193)
  %fstr_concat195 = call ptr @qc_string_concat(ptr %fstr_concat190, ptr %fstr_i32194)
  %fstr_concat196 = call ptr @qc_string_concat(ptr %fstr_concat195, ptr @.str.60)
  call void @qc_println(ptr %fstr_concat196)
  %reversed197 = load ptr, ptr %reversed, align 8
  %reversed198 = load ptr, ptr %reversed, align 8
  %4 = call ptr @"Collections::remove_list<int>_int"(ptr %reversed198, i32 2)
  store ptr %4, ptr %reversed, align 8
  %list_ptr199 = load ptr, ptr %reversed, align 8
  %list_elem_ptr200 = call ptr @qc_list_get(ptr %list_ptr199, i32 0)
  %list_elem201 = load i32, ptr %list_elem_ptr200, align 4
  %fstr_i32202 = call ptr @qc_to_string_int(i32 %list_elem201)
  %fstr_concat203 = call ptr @qc_string_concat(ptr @.str.61, ptr %fstr_i32202)
  %fstr_concat204 = call ptr @qc_string_concat(ptr %fstr_concat203, ptr @.str.62)
  %list_ptr205 = load ptr, ptr %reversed, align 8
  %list_elem_ptr206 = call ptr @qc_list_get(ptr %list_ptr205, i32 1)
  %list_elem207 = load i32, ptr %list_elem_ptr206, align 4
  %fstr_i32208 = call ptr @qc_to_string_int(i32 %list_elem207)
  %fstr_concat209 = call ptr @qc_string_concat(ptr %fstr_concat204, ptr %fstr_i32208)
  %fstr_concat210 = call ptr @qc_string_concat(ptr %fstr_concat209, ptr @.str.63)
  %list_ptr211 = load ptr, ptr %reversed, align 8
  %list_elem_ptr212 = call ptr @qc_list_get(ptr %list_ptr211, i32 2)
  %list_elem213 = load i32, ptr %list_elem_ptr212, align 4
  %fstr_i32214 = call ptr @qc_to_string_int(i32 %list_elem213)
  %fstr_concat215 = call ptr @qc_string_concat(ptr %fstr_concat210, ptr %fstr_i32214)
  %fstr_concat216 = call ptr @qc_string_concat(ptr %fstr_concat215, ptr @.str.64)
  %list_ptr217 = load ptr, ptr %reversed, align 8
  %list_elem_ptr218 = call ptr @qc_list_get(ptr %list_ptr217, i32 3)
  %list_elem219 = load i32, ptr %list_elem_ptr218, align 4
  %fstr_i32220 = call ptr @qc_to_string_int(i32 %list_elem219)
  %fstr_concat221 = call ptr @qc_string_concat(ptr %fstr_concat216, ptr %fstr_i32220)
  %fstr_concat222 = call ptr @qc_string_concat(ptr %fstr_concat221, ptr @.str.65)
  call void @qc_println(ptr %fstr_concat222)
  call void @qc_println(ptr @.str.66)
  call void @"UnitTest::Test_Test"(ptr %test, i32 5)
  %test223 = load %"UnitTest::Test", ptr %test, align 8
  %AssertEqual_result = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %test, i32 5, i32 5, ptr @.str.81, ptr @.str.82)
  %test224 = load %"UnitTest::Test", ptr %test, align 8
  %AssertEqual_result225 = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %test, i32 10, i32 10, ptr @.str.83, ptr @.str.84)
  %test226 = load %"UnitTest::Test", ptr %test, align 8
  %AssertTrue_result = call i32 @"UnitTest::Test_AssertTrue"(ptr %test, i1 true, ptr @.str.85, ptr @.str.86)
  %test227 = load %"UnitTest::Test", ptr %test, align 8
  %AssertFalse_result = call i32 @"UnitTest::Test_AssertFalse"(ptr %test, i1 false, ptr @.str.87, ptr @.str.88)
  %test228 = load %"UnitTest::Test", ptr %test, align 8
  %AssertNotEqual_result = call i32 @"UnitTest::Test_AssertNotEqual_int_int_string_string"(ptr %test, i32 5, i32 10, ptr @.str.103, ptr @.str.104)
  call void @qc_println(ptr @.str.105)
  call void @"AdvQBool::AQB_AQB"(ptr %aqb, i32 75)
  %aqb229 = load %"AdvQBool::AQB", ptr %aqb, align 4
  %repr_result = call ptr @"AdvQBool::AQB_repr"(ptr %aqb)
  %fstr_concat230 = call ptr @qc_string_concat(ptr @.str.106, ptr %repr_result)
  call void @qc_println(ptr %fstr_concat230)
  call void @qc_println(ptr @.str.107)
  store i32 0, ptr %trueCount, align 4
  store i32 0, ptr %i, align 4
  br label %for.cond

fstr_union_case_081:                              ; preds = %fstr_union_end63
  %union_member82 = load i32, ptr %union_payload78, align 4
  %fstr_i3283 = call ptr @qc_to_string_int(i32 %union_member82)
  store ptr %fstr_i3283, ptr %fstr_union_result80, align 8
  br label %fstr_union_end79

fstr_union_case_184:                              ; preds = %fstr_union_end63
  %union_member85 = load float, ptr %union_payload78, align 4
  %fstr_f3286 = call ptr @qc_to_string_float(float %union_member85)
  store ptr %fstr_f3286, ptr %fstr_union_result80, align 8
  br label %fstr_union_end79

fstr_union_case_287:                              ; preds = %fstr_union_end63
  %union_member88 = load double, ptr %union_payload78, align 8
  %fstr_f6489 = call ptr @qc_to_string_double(double %union_member88)
  store ptr %fstr_f6489, ptr %fstr_union_result80, align 8
  br label %fstr_union_end79

for.cond:                                         ; preds = %for.inc, %fstr_union_end79
  %i231 = load i32, ptr %i, align 4
  %icmplt = icmp slt i32 %i231, 10
  br i1 %icmplt, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %aqb232 = load %"AdvQBool::AQB", ptr %aqb, align 4
  %eval_result = call i1 @"AdvQBool::AQB_eval"(ptr %aqb)
  br i1 %eval_result, label %then, label %ifcont

for.inc:                                          ; preds = %ifcont
  %i236 = load i32, ptr %i, align 4
  %i237 = load i32, ptr %i, align 4
  %i238 = load i32, ptr %i, align 4
  %inc239 = add i32 %i238, 1
  store i32 %inc239, ptr %i, align 4
  store i32 %inc239, ptr %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %trueCount240 = load i32, ptr %trueCount, align 4
  %fstr_i32241 = call ptr @qc_to_string_int(i32 %trueCount240)
  %fstr_concat242 = call ptr @qc_string_concat(ptr @.str.108, ptr %fstr_i32241)
  %fstr_concat243 = call ptr @qc_string_concat(ptr %fstr_concat242, ptr @.str.109)
  call void @qc_println(ptr %fstr_concat243)
  call void @"AdvQBool::AQB_AQB"(ptr %aqb2, i32 50)
  %aqb244 = load %"AdvQBool::AQB", ptr %aqb, align 4
  %eval_result245 = call i1 @"AdvQBool::AQB_eval"(ptr %aqb)
  %aqb2246 = load %"AdvQBool::AQB", ptr %aqb2, align 4
  %eval_result247 = call i1 @"AdvQBool::AQB_eval"(ptr %aqb2)
  %and = and i1 %eval_result245, %eval_result247
  %fstr_bool248 = call ptr @qc_to_string_bool(i1 %and)
  %fstr_concat249 = call ptr @qc_string_concat(ptr @.str.110, ptr %fstr_bool248)
  call void @qc_println(ptr %fstr_concat249)
  %aqb250 = load %"AdvQBool::AQB", ptr %aqb, align 4
  %eval_result251 = call i1 @"AdvQBool::AQB_eval"(ptr %aqb)
  %aqb2252 = load %"AdvQBool::AQB", ptr %aqb2, align 4
  %eval_result253 = call i1 @"AdvQBool::AQB_eval"(ptr %aqb2)
  %or = or i1 %eval_result251, %eval_result253
  %fstr_bool254 = call ptr @qc_to_string_bool(i1 %or)
  %fstr_concat255 = call ptr @qc_string_concat(ptr @.str.111, ptr %fstr_bool254)
  call void @qc_println(ptr %fstr_concat255)
  %aqb256 = load %"AdvQBool::AQB", ptr %aqb, align 4
  %eval_result257 = call i1 @"AdvQBool::AQB_eval"(ptr %aqb)
  %not = xor i1 %eval_result257, true
  %fstr_bool258 = call ptr @qc_to_string_bool(i1 %not)
  %fstr_concat259 = call ptr @qc_string_concat(ptr @.str.112, ptr %fstr_bool258)
  call void @qc_println(ptr %fstr_concat259)
  call void @qc_println(ptr @.str.113)
  ret i32 0

then:                                             ; preds = %for.body
  %trueCount233 = load i32, ptr %trueCount, align 4
  %trueCount234 = load i32, ptr %trueCount, align 4
  %trueCount235 = load i32, ptr %trueCount, align 4
  %inc = add i32 %trueCount235, 1
  store i32 %inc, ptr %trueCount, align 4
  store i32 %inc, ptr %trueCount, align 4
  br label %ifcont

ifcont:                                           ; preds = %then, %for.body
  br label %for.inc
}

define i1 @"Collections::has_list<int>_int"(ptr %collection1, i32 %value2) {
entry:
  %val = alloca i32, align 4
  %__foreach_i_val = alloca i32, align 4
  %value = alloca i32, align 4
  %collection = alloca ptr, align 8
  store ptr %collection1, ptr %collection, align 8
  store i32 %value2, ptr %value, align 4
  %collection3 = load ptr, ptr %collection, align 8
  %coll_len = call i32 @qc_list_length(ptr %collection3)
  store i32 0, ptr %__foreach_i_val, align 4
  br label %foreach.cond

foreach.cond:                                     ; preds = %foreach.inc, %entry
  %__foreach_i_val4 = load i32, ptr %__foreach_i_val, align 4
  %foreach_cmp = icmp slt i32 %__foreach_i_val4, %coll_len
  br i1 %foreach_cmp, label %foreach.body, label %foreach.end

foreach.body:                                     ; preds = %foreach.cond
  %elem_ptr = call ptr @qc_list_get(ptr %collection3, i32 %__foreach_i_val4)
  %elem = load i32, ptr %elem_ptr, align 4
  store i32 %elem, ptr %val, align 4
  %val5 = load i32, ptr %val, align 4
  %value6 = load i32, ptr %value, align 4
  %icmpeq = icmp eq i32 %val5, %value6
  br i1 %icmpeq, label %then, label %ifcont

foreach.inc:                                      ; preds = %ifcont
  %__foreach_i_val7 = load i32, ptr %__foreach_i_val, align 4
  %i_inc = add i32 %__foreach_i_val7, 1
  store i32 %i_inc, ptr %__foreach_i_val, align 4
  br label %foreach.cond

foreach.end:                                      ; preds = %foreach.cond
  ret i1 false

then:                                             ; preds = %foreach.body
  ret i1 true

ifcont:                                           ; preds = %foreach.body
  br label %foreach.inc
}

define i32 @"Collections::index_of_list<int>_int"(ptr %collection1, i32 %value2) {
entry:
  %"Collections::i" = alloca i32, align 4
  %value = alloca i32, align 4
  %collection = alloca ptr, align 8
  store ptr %collection1, ptr %collection, align 8
  store i32 %value2, ptr %value, align 4
  store i32 0, ptr %"Collections::i", align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %i = load i32, ptr %"Collections::i", align 4
  %collection3 = load ptr, ptr %collection, align 8
  %list_len = call i32 @qc_list_length(ptr %collection3)
  %icmplt = icmp slt i32 %i, %list_len
  br i1 %icmplt, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %list_ptr = load ptr, ptr %collection, align 8
  %i4 = load i32, ptr %"Collections::i", align 4
  %list_elem_ptr = call ptr @qc_list_get(ptr %list_ptr, i32 %i4)
  %list_elem = load i32, ptr %list_elem_ptr, align 4
  %value5 = load i32, ptr %value, align 4
  %icmpeq = icmp eq i32 %list_elem, %value5
  br i1 %icmpeq, label %then, label %ifcont

for.inc:                                          ; preds = %ifcont
  %i7 = load i32, ptr %"Collections::i", align 4
  %i8 = load i32, ptr %"Collections::i", align 4
  %i9 = load i32, ptr %"Collections::i", align 4
  %inc = add i32 %i9, 1
  store i32 %inc, ptr %"Collections::i", align 4
  store i32 %inc, ptr %"Collections::i", align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret i32 -1

then:                                             ; preds = %for.body
  %i6 = load i32, ptr %"Collections::i", align 4
  ret i32 %i6

ifcont:                                           ; preds = %for.body
  br label %for.inc
}

define ptr @"Collections::reverse_list<int>"(ptr %collection1) {
entry:
  %list_set_val18 = alloca i32, align 4
  %list_set_val = alloca i32, align 4
  %temp = alloca i32, align 4
  %"Collections::i" = alloca i32, align 4
  %"Collections::n" = alloca i32, align 4
  %collection = alloca ptr, align 8
  store ptr %collection1, ptr %collection, align 8
  %collection2 = load ptr, ptr %collection, align 8
  %list_len = call i32 @qc_list_length(ptr %collection2)
  store i32 %list_len, ptr %"Collections::n", align 4
  store i32 0, ptr %"Collections::i", align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %i = load i32, ptr %"Collections::i", align 4
  %n = load i32, ptr %"Collections::n", align 4
  %sdiv = sdiv i32 %n, 2
  %icmplt = icmp slt i32 %i, %sdiv
  br i1 %icmplt, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %list_ptr = load ptr, ptr %collection, align 8
  %i3 = load i32, ptr %"Collections::i", align 4
  %list_elem_ptr = call ptr @qc_list_get(ptr %list_ptr, i32 %i3)
  %list_elem = load i32, ptr %list_elem_ptr, align 4
  store i32 %list_elem, ptr %temp, align 4
  %list_ptr4 = load ptr, ptr %collection, align 8
  %i5 = load i32, ptr %"Collections::i", align 4
  %list_ptr6 = load ptr, ptr %collection, align 8
  %n7 = load i32, ptr %"Collections::n", align 4
  %sub = sub i32 %n7, 1
  %i8 = load i32, ptr %"Collections::i", align 4
  %sub9 = sub i32 %sub, %i8
  %list_elem_ptr10 = call ptr @qc_list_get(ptr %list_ptr6, i32 %sub9)
  %list_elem11 = load i32, ptr %list_elem_ptr10, align 4
  store i32 %list_elem11, ptr %list_set_val, align 4
  call void @qc_list_set(ptr %list_ptr4, i32 %i5, ptr %list_set_val)
  %list_ptr12 = load ptr, ptr %collection, align 8
  %n13 = load i32, ptr %"Collections::n", align 4
  %sub14 = sub i32 %n13, 1
  %i15 = load i32, ptr %"Collections::i", align 4
  %sub16 = sub i32 %sub14, %i15
  %temp17 = load i32, ptr %temp, align 4
  store i32 %temp17, ptr %list_set_val18, align 4
  call void @qc_list_set(ptr %list_ptr12, i32 %sub16, ptr %list_set_val18)
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %i19 = load i32, ptr %"Collections::i", align 4
  %i20 = load i32, ptr %"Collections::i", align 4
  %i21 = load i32, ptr %"Collections::i", align 4
  %inc = add i32 %i21, 1
  store i32 %inc, ptr %"Collections::i", align 4
  store i32 %inc, ptr %"Collections::i", align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %collection22 = load ptr, ptr %collection, align 8
  ret ptr %collection22
}

define ptr @"Collections::remove_list<int>_int"(ptr %collection1, i32 %value2) {
entry:
  %list_set_val = alloca i32, align 4
  %"Collections::i" = alloca i32, align 4
  %"Collections::index" = alloca i32, align 4
  %value = alloca i32, align 4
  %collection = alloca ptr, align 8
  store ptr %collection1, ptr %collection, align 8
  store i32 %value2, ptr %value, align 4
  %collection3 = load ptr, ptr %collection, align 8
  %value4 = load i32, ptr %value, align 4
  %0 = call i32 @"Collections::index_of_list<int>_unknown"(ptr %collection3, i32 %value4)
  store i32 %0, ptr %"Collections::index", align 4
  %index = load i32, ptr %"Collections::index", align 4
  %icmpne = icmp ne i32 %index, -1
  br i1 %icmpne, label %then, label %ifcont

then:                                             ; preds = %entry
  %index5 = load i32, ptr %"Collections::index", align 4
  store i32 %index5, ptr %"Collections::i", align 4
  br label %for.cond

ifcont:                                           ; preds = %for.end, %entry
  %collection14 = load ptr, ptr %collection, align 8
  ret ptr %collection14

for.cond:                                         ; preds = %for.inc, %then
  %i = load i32, ptr %"Collections::i", align 4
  %collection6 = load ptr, ptr %collection, align 8
  %list_len = call i32 @qc_list_length(ptr %collection6)
  %sub = sub i32 %list_len, 1
  %icmplt = icmp slt i32 %i, %sub
  br i1 %icmplt, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %list_ptr = load ptr, ptr %collection, align 8
  %i7 = load i32, ptr %"Collections::i", align 4
  %list_ptr8 = load ptr, ptr %collection, align 8
  %i9 = load i32, ptr %"Collections::i", align 4
  %add = add i32 %i9, 1
  %list_elem_ptr = call ptr @qc_list_get(ptr %list_ptr8, i32 %add)
  %list_elem = load i32, ptr %list_elem_ptr, align 4
  store i32 %list_elem, ptr %list_set_val, align 4
  call void @qc_list_set(ptr %list_ptr, i32 %i7, ptr %list_set_val)
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %i10 = load i32, ptr %"Collections::i", align 4
  %i11 = load i32, ptr %"Collections::i", align 4
  %i12 = load i32, ptr %"Collections::i", align 4
  %inc = add i32 %i12, 1
  store i32 %inc, ptr %"Collections::i", align 4
  store i32 %inc, ptr %"Collections::i", align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %collection13 = load ptr, ptr %collection, align 8
  %list_pop = call ptr @qc_list_pop(ptr %collection13)
  br label %ifcont
}

define i32 @"Collections::index_of_list<int>_unknown"(ptr %collection1, i32 %value2) {
entry:
  %"Collections::i" = alloca i32, align 4
  %value = alloca i32, align 4
  %collection = alloca ptr, align 8
  store ptr %collection1, ptr %collection, align 8
  store i32 %value2, ptr %value, align 4
  store i32 0, ptr %"Collections::i", align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %i = load i32, ptr %"Collections::i", align 4
  %collection3 = load ptr, ptr %collection, align 8
  %list_len = call i32 @qc_list_length(ptr %collection3)
  %icmplt = icmp slt i32 %i, %list_len
  br i1 %icmplt, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %list_ptr = load ptr, ptr %collection, align 8
  %i4 = load i32, ptr %"Collections::i", align 4
  %list_elem_ptr = call ptr @qc_list_get(ptr %list_ptr, i32 %i4)
  %list_elem = load i32, ptr %list_elem_ptr, align 4
  %value5 = load i32, ptr %value, align 4
  %icmpeq = icmp eq i32 %list_elem, %value5
  br i1 %icmpeq, label %then, label %ifcont

for.inc:                                          ; preds = %ifcont
  %i7 = load i32, ptr %"Collections::i", align 4
  %i8 = load i32, ptr %"Collections::i", align 4
  %i9 = load i32, ptr %"Collections::i", align 4
  %inc = add i32 %i9, 1
  store i32 %inc, ptr %"Collections::i", align 4
  store i32 %inc, ptr %"Collections::i", align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret i32 -1

then:                                             ; preds = %for.body
  %i6 = load i32, ptr %"Collections::i", align 4
  ret i32 %i6

ifcont:                                           ; preds = %for.body
  br label %for.inc
}

define i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %0, i32 %expected1, i32 %result2, ptr %FailMessage3, ptr %Call4) {
entry:
  %Call = alloca ptr, align 8
  %FailMessage = alloca ptr, align 8
  %result = alloca i32, align 4
  %expected = alloca i32, align 4
  store i32 %expected1, ptr %expected, align 4
  store i32 %result2, ptr %result, align 4
  store ptr %FailMessage3, ptr %FailMessage, align 8
  store ptr %Call4, ptr %Call, align 8
  %expected5 = load i32, ptr %expected, align 4
  %result6 = load i32, ptr %result, align 4
  %icmpne = icmp ne i32 %expected5, %result6
  br i1 %icmpne, label %then, label %else

then:                                             ; preds = %entry
  %Call7 = load ptr, ptr %Call, align 8
  %1 = call i1 @qc_string_eq(ptr %Call7, ptr @.str.67)
  %2 = xor i1 %1, true
  br i1 %2, label %then8, label %else10

ifcont:                                           ; preds = %ifcont35, %ifcont9
  ret i32 0

else:                                             ; preds = %entry
  %Call33 = load ptr, ptr %Call, align 8
  %3 = call i1 @qc_string_eq(ptr %Call33, ptr @.str.75)
  %4 = xor i1 %3, true
  br i1 %4, label %then34, label %else36

then8:                                            ; preds = %then
  %Call11 = load ptr, ptr %Call, align 8
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.68, ptr %Call11)
  %fstr_concat12 = call ptr @qc_string_concat(ptr %fstr_concat, ptr @.str.69)
  %expected13 = load i32, ptr %expected, align 4
  %fstr_i32 = call ptr @qc_to_string_int(i32 %expected13)
  %fstr_concat14 = call ptr @qc_string_concat(ptr %fstr_concat12, ptr %fstr_i32)
  %fstr_concat15 = call ptr @qc_string_concat(ptr %fstr_concat14, ptr @.str.70)
  %result16 = load i32, ptr %result, align 4
  %fstr_i3217 = call ptr @qc_to_string_int(i32 %result16)
  %fstr_concat18 = call ptr @qc_string_concat(ptr %fstr_concat15, ptr %fstr_i3217)
  %fstr_concat19 = call ptr @qc_string_concat(ptr %fstr_concat18, ptr @.str.71)
  %FailMessage20 = load ptr, ptr %FailMessage, align 8
  %fstr_concat21 = call ptr @qc_string_concat(ptr %fstr_concat19, ptr %FailMessage20)
  %Fail_result = call i32 @"UnitTest::Test_Fail"(ptr %0, ptr %fstr_concat21)
  br label %ifcont9

ifcont9:                                          ; preds = %else10, %then8
  br label %ifcont

else10:                                           ; preds = %then
  %expected22 = load i32, ptr %expected, align 4
  %fstr_i3223 = call ptr @qc_to_string_int(i32 %expected22)
  %fstr_concat24 = call ptr @qc_string_concat(ptr @.str.72, ptr %fstr_i3223)
  %fstr_concat25 = call ptr @qc_string_concat(ptr %fstr_concat24, ptr @.str.73)
  %result26 = load i32, ptr %result, align 4
  %fstr_i3227 = call ptr @qc_to_string_int(i32 %result26)
  %fstr_concat28 = call ptr @qc_string_concat(ptr %fstr_concat25, ptr %fstr_i3227)
  %fstr_concat29 = call ptr @qc_string_concat(ptr %fstr_concat28, ptr @.str.74)
  %FailMessage30 = load ptr, ptr %FailMessage, align 8
  %fstr_concat31 = call ptr @qc_string_concat(ptr %fstr_concat29, ptr %FailMessage30)
  %Fail_result32 = call i32 @"UnitTest::Test_Fail"(ptr %0, ptr %fstr_concat31)
  br label %ifcont9

then34:                                           ; preds = %else
  %Call37 = load ptr, ptr %Call, align 8
  %fstr_concat38 = call ptr @qc_string_concat(ptr @.str.76, ptr %Call37)
  %fstr_concat39 = call ptr @qc_string_concat(ptr %fstr_concat38, ptr @.str.77)
  %result40 = load i32, ptr %result, align 4
  %fstr_i3241 = call ptr @qc_to_string_int(i32 %result40)
  %fstr_concat42 = call ptr @qc_string_concat(ptr %fstr_concat39, ptr %fstr_i3241)
  %fstr_concat43 = call ptr @qc_string_concat(ptr %fstr_concat42, ptr @.str.78)
  %expected44 = load i32, ptr %expected, align 4
  %fstr_i3245 = call ptr @qc_to_string_int(i32 %expected44)
  %fstr_concat46 = call ptr @qc_string_concat(ptr %fstr_concat43, ptr %fstr_i3245)
  %Success_result = call i32 @"UnitTest::Test_Success"(ptr %0, ptr %fstr_concat46)
  br label %ifcont35

ifcont35:                                         ; preds = %else36, %then34
  br label %ifcont

else36:                                           ; preds = %else
  %result47 = load i32, ptr %result, align 4
  %fstr_i3248 = call ptr @qc_to_string_int(i32 %result47)
  %fstr_concat49 = call ptr @qc_string_concat(ptr @.str.79, ptr %fstr_i3248)
  %fstr_concat50 = call ptr @qc_string_concat(ptr %fstr_concat49, ptr @.str.80)
  %expected51 = load i32, ptr %expected, align 4
  %fstr_i3252 = call ptr @qc_to_string_int(i32 %expected51)
  %fstr_concat53 = call ptr @qc_string_concat(ptr %fstr_concat50, ptr %fstr_i3252)
  %Success_result54 = call i32 @"UnitTest::Test_Success"(ptr %0, ptr %fstr_concat53)
  br label %ifcont35
}

define i32 @"UnitTest::Test_AssertNotEqual_int_int_string_string"(ptr %0, i32 %notExpected1, i32 %result2, ptr %FailMessage3, ptr %Call4) {
entry:
  %Call = alloca ptr, align 8
  %FailMessage = alloca ptr, align 8
  %result = alloca i32, align 4
  %notExpected = alloca i32, align 4
  store i32 %notExpected1, ptr %notExpected, align 4
  store i32 %result2, ptr %result, align 4
  store ptr %FailMessage3, ptr %FailMessage, align 8
  store ptr %Call4, ptr %Call, align 8
  %notExpected5 = load i32, ptr %notExpected, align 4
  %result6 = load i32, ptr %result, align 4
  %icmpeq = icmp eq i32 %notExpected5, %result6
  br i1 %icmpeq, label %then, label %else

then:                                             ; preds = %entry
  %Call7 = load ptr, ptr %Call, align 8
  %1 = call i1 @qc_string_eq(ptr %Call7, ptr @.str.89)
  %2 = xor i1 %1, true
  br i1 %2, label %then8, label %else10

ifcont:                                           ; preds = %ifcont35, %ifcont9
  ret i32 0

else:                                             ; preds = %entry
  %Call33 = load ptr, ptr %Call, align 8
  %3 = call i1 @qc_string_eq(ptr %Call33, ptr @.str.97)
  %4 = xor i1 %3, true
  br i1 %4, label %then34, label %else36

then8:                                            ; preds = %then
  %Call11 = load ptr, ptr %Call, align 8
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.90, ptr %Call11)
  %fstr_concat12 = call ptr @qc_string_concat(ptr %fstr_concat, ptr @.str.91)
  %result13 = load i32, ptr %result, align 4
  %fstr_i32 = call ptr @qc_to_string_int(i32 %result13)
  %fstr_concat14 = call ptr @qc_string_concat(ptr %fstr_concat12, ptr %fstr_i32)
  %fstr_concat15 = call ptr @qc_string_concat(ptr %fstr_concat14, ptr @.str.92)
  %notExpected16 = load i32, ptr %notExpected, align 4
  %fstr_i3217 = call ptr @qc_to_string_int(i32 %notExpected16)
  %fstr_concat18 = call ptr @qc_string_concat(ptr %fstr_concat15, ptr %fstr_i3217)
  %fstr_concat19 = call ptr @qc_string_concat(ptr %fstr_concat18, ptr @.str.93)
  %FailMessage20 = load ptr, ptr %FailMessage, align 8
  %fstr_concat21 = call ptr @qc_string_concat(ptr %fstr_concat19, ptr %FailMessage20)
  %Fail_result = call i32 @"UnitTest::Test_Fail"(ptr %0, ptr %fstr_concat21)
  br label %ifcont9

ifcont9:                                          ; preds = %else10, %then8
  br label %ifcont

else10:                                           ; preds = %then
  %result22 = load i32, ptr %result, align 4
  %fstr_i3223 = call ptr @qc_to_string_int(i32 %result22)
  %fstr_concat24 = call ptr @qc_string_concat(ptr @.str.94, ptr %fstr_i3223)
  %fstr_concat25 = call ptr @qc_string_concat(ptr %fstr_concat24, ptr @.str.95)
  %notExpected26 = load i32, ptr %notExpected, align 4
  %fstr_i3227 = call ptr @qc_to_string_int(i32 %notExpected26)
  %fstr_concat28 = call ptr @qc_string_concat(ptr %fstr_concat25, ptr %fstr_i3227)
  %fstr_concat29 = call ptr @qc_string_concat(ptr %fstr_concat28, ptr @.str.96)
  %FailMessage30 = load ptr, ptr %FailMessage, align 8
  %fstr_concat31 = call ptr @qc_string_concat(ptr %fstr_concat29, ptr %FailMessage30)
  %Fail_result32 = call i32 @"UnitTest::Test_Fail"(ptr %0, ptr %fstr_concat31)
  br label %ifcont9

then34:                                           ; preds = %else
  %Call37 = load ptr, ptr %Call, align 8
  %fstr_concat38 = call ptr @qc_string_concat(ptr @.str.98, ptr %Call37)
  %fstr_concat39 = call ptr @qc_string_concat(ptr %fstr_concat38, ptr @.str.99)
  %result40 = load i32, ptr %result, align 4
  %fstr_i3241 = call ptr @qc_to_string_int(i32 %result40)
  %fstr_concat42 = call ptr @qc_string_concat(ptr %fstr_concat39, ptr %fstr_i3241)
  %fstr_concat43 = call ptr @qc_string_concat(ptr %fstr_concat42, ptr @.str.100)
  %notExpected44 = load i32, ptr %notExpected, align 4
  %fstr_i3245 = call ptr @qc_to_string_int(i32 %notExpected44)
  %fstr_concat46 = call ptr @qc_string_concat(ptr %fstr_concat43, ptr %fstr_i3245)
  %Success_result = call i32 @"UnitTest::Test_Success"(ptr %0, ptr %fstr_concat46)
  br label %ifcont35

ifcont35:                                         ; preds = %else36, %then34
  br label %ifcont

else36:                                           ; preds = %else
  %result47 = load i32, ptr %result, align 4
  %fstr_i3248 = call ptr @qc_to_string_int(i32 %result47)
  %fstr_concat49 = call ptr @qc_string_concat(ptr @.str.101, ptr %fstr_i3248)
  %fstr_concat50 = call ptr @qc_string_concat(ptr %fstr_concat49, ptr @.str.102)
  %notExpected51 = load i32, ptr %notExpected, align 4
  %fstr_i3252 = call ptr @qc_to_string_int(i32 %notExpected51)
  %fstr_concat53 = call ptr @qc_string_concat(ptr %fstr_concat50, ptr %fstr_i3252)
  %Success_result54 = call i32 @"UnitTest::Test_Success"(ptr %0, ptr %fstr_concat53)
  br label %ifcont35
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
