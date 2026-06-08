; ModuleID = 'qc_module'
source_filename = "qc_module"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct._ffi_type = type { i64, i16, i16, ptr }
%struct.ffi_cif = type { i32, i32, ptr, ptr, i32, i32 }
%Warrior = type { i32 }
%Node2 = type { i32, ptr }
%Node = type { i32, ptr }
%Refs = type { i32 }
%"UnitTest::Test" = type { i32, i32, i32, i32, ptr }
%Point = type { i32, i32 }

@.str = private unnamed_addr constant [11 x i8] c"%%%s%d.%dd\00", align 1
@.str.1 = private unnamed_addr constant [2 x i8] c"0\00", align 1
@.str.2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.3 = private unnamed_addr constant [7 x i8] c"%%.%dd\00", align 1
@.str.4 = private unnamed_addr constant [8 x i8] c"%%%s%dd\00", align 1
@.str.5 = private unnamed_addr constant [4 x i8] c"%%d\00", align 1
@.str.6 = private unnamed_addr constant [6 x i8] c"%%llu\00", align 1
@.str.7 = private unnamed_addr constant [11 x i8] c"%%%s%d.%df\00", align 1
@.str.8 = private unnamed_addr constant [7 x i8] c"%%.%df\00", align 1
@.str.9 = private unnamed_addr constant [8 x i8] c"%%%s%df\00", align 1
@.str.10 = private unnamed_addr constant [4 x i8] c"%%f\00", align 1
@.str.11 = private unnamed_addr constant [11 x i8] c"%%%s%d.%de\00", align 1
@.str.12 = private unnamed_addr constant [7 x i8] c"%%.%de\00", align 1
@.str.13 = private unnamed_addr constant [8 x i8] c"%%%s%de\00", align 1
@.str.14 = private unnamed_addr constant [4 x i8] c"%%e\00", align 1
@.str.15 = private unnamed_addr constant [8 x i8] c"%%%s%dc\00", align 1
@.str.16 = private unnamed_addr constant [4 x i8] c"%%c\00", align 1
@.str.17 = private unnamed_addr constant [8 x i8] c"%%%s%ds\00", align 1
@.str.18 = private unnamed_addr constant [4 x i8] c"%%s\00", align 1
@.str.19 = private unnamed_addr constant [8 x i8] c"%%%s%dx\00", align 1
@.str.20 = private unnamed_addr constant [4 x i8] c"%%x\00", align 1
@.str.21 = private unnamed_addr constant [8 x i8] c"%%%s%do\00", align 1
@.str.22 = private unnamed_addr constant [4 x i8] c"%%o\00", align 1
@.str.23 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.str.24 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.str.25 = private unnamed_addr constant [5 x i8] c"none\00", align 1
@.str.26 = private unnamed_addr constant [7 x i8] c"qfalse\00", align 1
@.str.27 = private unnamed_addr constant [6 x i8] c"qtrue\00", align 1
@.str.28 = private unnamed_addr constant [5 x i8] c"both\00", align 1
@.str.29 = private unnamed_addr constant [8 x i8] c"0x%0*jx\00", align 1
@.str.30 = private unnamed_addr constant [4 x i8] c"%*p\00", align 1
@.str.31 = private unnamed_addr constant [3 x i8] c"%p\00", align 1
@.str.32 = private unnamed_addr constant [4 x i8] c"%p\0A\00", align 1
@.str.33 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.34 = private unnamed_addr constant [3 x i8] c"%g\00", align 1
@.str.35 = private unnamed_addr constant [5 x i8] c"%lld\00", align 1
@.str.36 = private unnamed_addr constant [4 x i8] c"%hd\00", align 1
@stdout = external local_unnamed_addr global ptr, align 8
@stderr = external local_unnamed_addr global ptr, align 8
@stdin = external local_unnamed_addr global ptr, align 8
@.str.38 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.42 = private unnamed_addr constant [3 x i8] c", \00", align 1
@.str.44 = private unnamed_addr constant [5 x i8] c"\22%s\22\00", align 1
@.str.45 = private unnamed_addr constant [5 x i8] c"'%c'\00", align 1
@.str.46 = private unnamed_addr constant [6 x i8] c"ERROR\00", align 1
@.str.48 = private unnamed_addr constant [3 x i8] c": \00", align 1
@ffi_type_sint32 = external global %struct._ffi_type, align 8
@ffi_type_float = external global %struct._ffi_type, align 8
@ffi_type_double = external global %struct._ffi_type, align 8
@ffi_type_sint8 = external global %struct._ffi_type, align 8
@ffi_type_uint8 = external global %struct._ffi_type, align 8
@ffi_type_pointer = external global %struct._ffi_type, align 8
@ffi_type_void = external global %struct._ffi_type, align 8
@switch.table.qc_print_array_qbool = private unnamed_addr constant [4 x ptr] [ptr @.str.25, ptr @.str.26, ptr @.str.27, ptr @.str.28], align 8
@switch.table.qc_set_leaf_element.51 = private unnamed_addr constant [5 x i64] [i64 8, i64 1, i64 1, i64 1, i64 8], align 8
@switch.table.stringify_jagged_helper = private unnamed_addr constant [5 x i32] [i32 8, i32 1, i32 1, i32 1, i32 8], align 4
@switch.table.qc_map_set.53 = private unnamed_addr constant [4 x i64] [i64 8, i64 1, i64 1, i64 1], align 8
@switch.table.qc_spread_call = private unnamed_addr constant [7 x ptr] [ptr @ffi_type_void, ptr @ffi_type_sint32, ptr @ffi_type_float, ptr @ffi_type_double, ptr @ffi_type_sint8, ptr @ffi_type_uint8, ptr @ffi_type_uint8], align 8
@switch.table.qc_spread_call.54 = private unnamed_addr constant [6 x ptr] [ptr @ffi_type_sint32, ptr @ffi_type_float, ptr @ffi_type_double, ptr @ffi_type_sint8, ptr @ffi_type_uint8, ptr @ffi_type_uint8], align 8
@0 = private unnamed_addr constant [7 x i8] c"Point(\00", align 1
@1 = private unnamed_addr constant [3 x i8] c"x=\00", align 1
@2 = private unnamed_addr constant [3 x i8] c", \00", align 1
@3 = private unnamed_addr constant [3 x i8] c"y=\00", align 1
@4 = private unnamed_addr constant [2 x i8] c")\00", align 1
@.str.37 = private constant [1 x i8] zeroinitializer
@.str.39 = private constant [16 x i8] c"[FAIL] On call \00"
@.str.40 = private constant [12 x i8] c": Expected \00"
@.str.41 = private constant [7 x i8] c", got \00"
@.str.43 = private constant [3 x i8] c". \00"
@.str.47 = private constant [17 x i8] c"[FAIL] Expected \00"
@.str.49 = private constant [7 x i8] c", got \00"
@.str.50 = private constant [3 x i8] c". \00"
@.str.51 = private constant [1 x i8] zeroinitializer
@.str.52 = private constant [19 x i8] c"[SUCCESS] on call \00"
@.str.53 = private constant [3 x i8] c": \00"
@.str.54 = private constant [15 x i8] c" was equal to \00"
@.str.55 = private constant [11 x i8] c"[SUCCESS] \00"
@.str.56 = private constant [15 x i8] c" was equal to \00"
@.str.57 = private constant [20 x i8] c"ptr param increment\00"
@.str.58 = private constant [10 x i8] c"val == 11\00"
@.str.59 = private constant [11 x i8] c"ref swap x\00"
@.str.60 = private constant [7 x i8] c"x == 2\00"
@.str.61 = private constant [11 x i8] c"ref swap y\00"
@.str.62 = private constant [7 x i8] c"y == 1\00"
@.str.63 = private constant [18 x i8] c"auto ptr doubling\00"
@.str.64 = private constant [13 x i8] c"magic == 100\00"
@.str.65 = private constant [24 x i8] c"pointer property access\00"
@.str.66 = private constant [23 x i8] c"(*n1.next).value == 20\00"
@.str.67 = private constant [24 x i8] c"pointer property update\00"
@.str.68 = private constant [15 x i8] c"n2.value == 42\00"
@.str.69 = private constant [15 x i8] c"%p, %p, %p, %i\00"
@5 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@6 = private unnamed_addr constant [3 x i8] c", \00", align 1
@7 = private unnamed_addr constant [3 x i8] c", \00", align 1
@8 = private unnamed_addr constant [3 x i8] c", \00", align 1
@9 = private unnamed_addr constant [2 x i8] zeroinitializer, align 1
@.str.70 = private constant [19 x i8] c"Success: n is null\00"
@10 = private unnamed_addr constant [20 x i8] c"Success: n is null\00\00", align 1
@.str.71 = private constant [23 x i8] c"Fail: n is not nullptr\00"
@11 = private unnamed_addr constant [24 x i8] c"Fail: n is not nullptr\00\00", align 1
@.str.72 = private constant [31 x i8] c"Success: real_node is not null\00"
@12 = private unnamed_addr constant [32 x i8] c"Success: real_node is not null\00\00", align 1
@.str.73 = private constant [20 x i8] c"Success: p[0] is 10\00"
@13 = private unnamed_addr constant [21 x i8] c"Success: p[0] is 10\00\00", align 1
@.str.74 = private constant [34 x i8] c"Success: Offset assignment worked\00"
@14 = private unnamed_addr constant [35 x i8] c"Success: Offset assignment worked\00\00", align 1
@.str.75 = private constant [31 x i8] c"Success: Pointer distance is 5\00"
@15 = private unnamed_addr constant [32 x i8] c"Success: Pointer distance is 5\00\00", align 1
@.str.76 = private constant [34 x i8] c"Success: nullptr + 10 is not null\00"
@16 = private unnamed_addr constant [35 x i8] c"Success: nullptr + 10 is not null\00\00", align 1
@.str.77 = private constant [30 x i8] c"Success: Loop indexing worked\00"
@17 = private unnamed_addr constant [31 x i8] c"Success: Loop indexing worked\00\00", align 1
@.str.78 = private constant [46 x i8] c"Value is %i, and after getting that, it is %s\00"
@18 = private unnamed_addr constant [10 x i8] c"Value is \00", align 1
@.str.79 = private constant [6 x i8] c"empty\00"
@.str.80 = private constant [10 x i8] c"not empty\00"
@19 = private unnamed_addr constant [33 x i8] c", and after getting that, it is \00", align 1
@20 = private unnamed_addr constant [2 x i8] zeroinitializer, align 1
@.str.81 = private constant [27 x i8] c"expected rx to equal 12345\00"
@.str.82 = private constant [12 x i8] c"rx == 12345\00"
@.str.83 = private constant [26 x i8] c"expected x to equal 12345\00"
@.str.84 = private constant [22 x i8] c"x = 12345; x == 12345\00"
@.str.85 = private constant [26 x i8] c"expected x to equal 13579\00"
@.str.86 = private constant [11 x i8] c"x == 13579\00"
@.str.87 = private constant [19 x i8] c"expected x = 12345\00"
@.str.88 = private constant [11 x i8] c"x == 12345\00"
@21 = private unnamed_addr constant [4 x i8] c"int\00", align 1
@.str.89 = private constant [4 x i8] c"int\00"
@22 = private unnamed_addr constant [4 x i8] c"int\00", align 1
@.str.90 = private constant [4 x i8] c"int\00"
@.str.91 = private constant [19 x i8] c"expected x = 14814\00"
@.str.92 = private constant [11 x i8] c"x == 14814\00"
@.str.93 = private constant [24 x i8] c"expected pnt.x to be 22\00"
@.str.94 = private constant [12 x i8] c"pnt.x == 22\00"
@.str.95 = private constant [31 x i8] c"expected ptr_deref to be 14814\00"
@.str.96 = private constant [19 x i8] c"ptr_deref == 14814\00"
@.str.97 = private constant [25 x i8] c"expected *py to be 14937\00"
@.str.98 = private constant [19 x i8] c"ptr_deref == 14814\00"
@.str.99 = private constant [3 x i8] c"%i\00"
@23 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@24 = private unnamed_addr constant [2 x i8] zeroinitializer, align 1
@.str.100 = private constant [32 x i8] c"==============================\0A\00"
@25 = private unnamed_addr constant [33 x i8] c"==============================\0A\00\00", align 1
@.str.101 = private constant [4 x i8] c"%s\0A\00"
@26 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@27 = private unnamed_addr constant [3 x i8] c"\0A\00\00", align 1
@.str.102 = private constant [32 x i8] c"==============================\0A\00"
@28 = private unnamed_addr constant [33 x i8] c"==============================\0A\00\00", align 1
@.str.103 = private constant [3 x i8] c"%s\00"
@.str.104 = private constant [9 x i8] c"Failed: \00"
@.str.105 = private constant [2 x i8] c"\0A\00"
@29 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@30 = private unnamed_addr constant [2 x i8] zeroinitializer, align 1
@.str.106 = private constant [3 x i8] c"%s\00"
@.str.107 = private constant [9 x i8] c"Passed: \00"
@.str.108 = private constant [2 x i8] c"\0A\00"
@31 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@32 = private unnamed_addr constant [2 x i8] zeroinitializer, align 1
@.str.109 = private constant [32 x i8] c"==============================\0A\00"
@33 = private unnamed_addr constant [33 x i8] c"==============================\0A\00\00", align 1
@.str.110 = private constant [8 x i8] c"[FAIL]\0A\00"
@34 = private unnamed_addr constant [9 x i8] c"[FAIL]\0A\00\00", align 1
@.str.111 = private constant [8 x i8] c"[PASS]\0A\00"
@35 = private unnamed_addr constant [9 x i8] c"[PASS]\0A\00\00", align 1
@.str.112 = private constant [4 x i8] c": [\00"
@.str.113 = private constant [2 x i8] c"/\00"
@.str.114 = private constant [2 x i8] c"]\00"
@.str.115 = private constant [4 x i8] c": [\00"
@.str.116 = private constant [2 x i8] c"/\00"
@.str.117 = private constant [2 x i8] c"]\00"
@.str.118 = private constant [1 x i8] zeroinitializer
@.str.119 = private constant [16 x i8] c"[FAIL] On call \00"
@.str.120 = private constant [34 x i8] c": Expected condition to be true. \00"
@.str.121 = private constant [39 x i8] c"[FAIL] Expected condition to be true. \00"
@.str.122 = private constant [1 x i8] zeroinitializer
@.str.123 = private constant [19 x i8] c"[SUCCESS] on call \00"
@.str.124 = private constant [21 x i8] c": Condition was true\00"
@.str.125 = private constant [29 x i8] c"[SUCCESS] Condition was true\00"
@.str.126 = private constant [1 x i8] zeroinitializer
@.str.127 = private constant [16 x i8] c"[FAIL] On call \00"
@.str.128 = private constant [35 x i8] c": Expected condition to be false. \00"
@.str.129 = private constant [40 x i8] c"[FAIL] Expected condition to be false. \00"
@.str.130 = private constant [1 x i8] zeroinitializer
@.str.131 = private constant [19 x i8] c"[SUCCESS] on call \00"
@.str.132 = private constant [22 x i8] c": Condition was false\00"
@.str.133 = private constant [30 x i8] c"[SUCCESS] Condition was false\00"

; Function Attrs: mustprogress nofree nounwind willreturn memory(inaccessiblemem: readwrite) uwtable
define dso_local noalias noundef ptr @qc_malloc(i64 noundef %0) local_unnamed_addr #0 {
  %2 = tail call noalias ptr @malloc(i64 noundef %0) #36
  ret ptr %2
}

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite)
declare noalias noundef ptr @malloc(i64 noundef) local_unnamed_addr #1

; Function Attrs: mustprogress nounwind willreturn memory(argmem: readwrite, inaccessiblemem: readwrite) uwtable
define dso_local void @qc_free(ptr noundef captures(none) %0) local_unnamed_addr #2 {
  tail call void @free(ptr noundef %0) #37
  ret void
}

; Function Attrs: mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite)
declare void @free(ptr allocptr noundef captures(none)) local_unnamed_addr #3

; Function Attrs: mustprogress nounwind willreturn memory(argmem: readwrite, inaccessiblemem: readwrite) uwtable
define dso_local noalias noundef ptr @qc_realloc(ptr noundef captures(none) %0, i64 noundef %1) local_unnamed_addr #2 {
  %3 = tail call ptr @realloc(ptr noundef %0, i64 noundef %1) #38
  ret ptr %3
}

; Function Attrs: mustprogress nounwind willreturn allockind("realloc") allocsize(1) memory(argmem: readwrite, inaccessiblemem: readwrite)
declare noalias noundef ptr @realloc(ptr allocptr noundef captures(none), i64 noundef) local_unnamed_addr #4

; Function Attrs: mustprogress nofree nounwind willreturn memory(inaccessiblemem: readwrite) uwtable
define dso_local noalias noundef ptr @qc_calloc(i64 noundef %0, i64 noundef %1) local_unnamed_addr #0 {
  %3 = tail call noalias ptr @calloc(i64 noundef %0, i64 noundef %1) #39
  ret ptr %3
}

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,zeroed") allocsize(0,1) memory(inaccessiblemem: readwrite)
declare noalias noundef ptr @calloc(i64 noundef, i64 noundef) local_unnamed_addr #5

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_fmt_int(i64 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #6 {
  %5 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %5) #37
  %6 = icmp sgt i32 %2, -1
  %7 = icmp sgt i32 %1, 0
  br i1 %6, label %8, label %15

8:                                                ; preds = %4
  br i1 %7, label %9, label %13

9:                                                ; preds = %8
  %10 = icmp eq i32 %3, 0
  %11 = select i1 %10, ptr @.str.2, ptr @.str.1
  %12 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str, ptr noundef nonnull %11, i32 noundef %1, i32 noundef %2) #37
  br label %22

13:                                               ; preds = %8
  %14 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.3, i32 noundef %2) #37
  br label %22

15:                                               ; preds = %4
  br i1 %7, label %16, label %20

16:                                               ; preds = %15
  %17 = icmp eq i32 %3, 0
  %18 = select i1 %17, ptr @.str.2, ptr @.str.1
  %19 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.4, ptr noundef nonnull %18, i32 noundef %1) #37
  br label %22

20:                                               ; preds = %15
  %21 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.5) #37
  br label %22

22:                                               ; preds = %20, %16, %13, %9
  %23 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %5, i64 noundef %0) #37
  %24 = add nsw i32 %23, 1
  %25 = sext i32 %24 to i64
  %26 = tail call noalias ptr @malloc(i64 noundef %25) #36
  %27 = icmp eq ptr %26, null
  br i1 %27, label %30, label %28

28:                                               ; preds = %22
  %29 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull %26, i64 noundef %25, ptr noundef nonnull %5, i64 noundef %0) #37
  br label %30

30:                                               ; preds = %28, %22
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %5) #37
  ret ptr %26
}

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr captures(none)) #7

; Function Attrs: nofree nounwind
declare noundef i32 @snprintf(ptr noalias noundef writeonly captures(none), i64 noundef, ptr noundef readonly captures(none), ...) local_unnamed_addr #8

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr captures(none)) #7

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_flush() local_unnamed_addr #6 {
  %1 = tail call i32 @fflush(ptr noundef null)
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @fflush(ptr noundef captures(none)) local_unnamed_addr #8

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_fmt_unsigned_int(i64 noundef %0, i32 noundef %1) local_unnamed_addr #6 {
  %3 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %3) #37
  %4 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %3, i64 noundef 32, ptr noundef nonnull @.str.6) #37
  %5 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %3, i64 noundef %0) #37
  %6 = icmp slt i32 %5, 0
  br i1 %6, label %14, label %7

7:                                                ; preds = %2
  %8 = add nuw nsw i32 %5, 1
  %9 = zext nneg i32 %8 to i64
  %10 = tail call noalias ptr @malloc(i64 noundef %9) #36
  %11 = icmp eq ptr %10, null
  br i1 %11, label %14, label %12

12:                                               ; preds = %7
  %13 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %10, i64 noundef %9, ptr noundef nonnull %3, i64 noundef %0) #37
  br label %14

14:                                               ; preds = %12, %7, %2
  %15 = phi ptr [ null, %2 ], [ %10, %12 ], [ null, %7 ]
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %3) #37
  ret ptr %15
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_fmt_float(double noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #6 {
  %5 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %5) #37
  %6 = icmp sgt i32 %2, -1
  %7 = icmp sgt i32 %1, 0
  br i1 %6, label %8, label %15

8:                                                ; preds = %4
  br i1 %7, label %9, label %13

9:                                                ; preds = %8
  %10 = icmp eq i32 %3, 0
  %11 = select i1 %10, ptr @.str.2, ptr @.str.1
  %12 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.7, ptr noundef nonnull %11, i32 noundef %1, i32 noundef %2) #37
  br label %22

13:                                               ; preds = %8
  %14 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.8, i32 noundef %2) #37
  br label %22

15:                                               ; preds = %4
  br i1 %7, label %16, label %20

16:                                               ; preds = %15
  %17 = icmp eq i32 %3, 0
  %18 = select i1 %17, ptr @.str.2, ptr @.str.1
  %19 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.9, ptr noundef nonnull %18, i32 noundef %1) #37
  br label %22

20:                                               ; preds = %15
  %21 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.10) #37
  br label %22

22:                                               ; preds = %20, %16, %13, %9
  %23 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %5, double noundef %0) #37
  %24 = icmp slt i32 %23, 0
  br i1 %24, label %32, label %25

25:                                               ; preds = %22
  %26 = add nuw i32 %23, 1
  %27 = zext i32 %26 to i64
  %28 = tail call noalias ptr @malloc(i64 noundef %27) #36
  %29 = icmp eq ptr %28, null
  br i1 %29, label %32, label %30

30:                                               ; preds = %25
  %31 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %28, i64 noundef %27, ptr noundef nonnull %5, double noundef %0) #37
  br label %32

32:                                               ; preds = %30, %25, %22
  %33 = phi ptr [ null, %22 ], [ %28, %30 ], [ null, %25 ]
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %5) #37
  ret ptr %33
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_fmt_double(double noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #6 {
  %5 = tail call ptr @qc_fmt_float(double noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3)
  ret ptr %5
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_fmt_scientific(double noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #6 {
  %5 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %5) #37
  %6 = icmp sgt i32 %2, -1
  %7 = icmp sgt i32 %1, 0
  br i1 %6, label %8, label %15

8:                                                ; preds = %4
  br i1 %7, label %9, label %13

9:                                                ; preds = %8
  %10 = icmp eq i32 %3, 0
  %11 = select i1 %10, ptr @.str.2, ptr @.str.1
  %12 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.11, ptr noundef nonnull %11, i32 noundef %1, i32 noundef %2) #37
  br label %22

13:                                               ; preds = %8
  %14 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.12, i32 noundef %2) #37
  br label %22

15:                                               ; preds = %4
  br i1 %7, label %16, label %20

16:                                               ; preds = %15
  %17 = icmp eq i32 %3, 0
  %18 = select i1 %17, ptr @.str.2, ptr @.str.1
  %19 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.13, ptr noundef nonnull %18, i32 noundef %1) #37
  br label %22

20:                                               ; preds = %15
  %21 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.14) #37
  br label %22

22:                                               ; preds = %20, %16, %13, %9
  %23 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %5, double noundef %0) #37
  %24 = icmp slt i32 %23, 0
  br i1 %24, label %32, label %25

25:                                               ; preds = %22
  %26 = add nuw nsw i32 %23, 1
  %27 = zext nneg i32 %26 to i64
  %28 = tail call noalias ptr @malloc(i64 noundef %27) #36
  %29 = icmp eq ptr %28, null
  br i1 %29, label %32, label %30

30:                                               ; preds = %25
  %31 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %28, i64 noundef %27, ptr noundef nonnull %5, double noundef %0) #37
  br label %32

32:                                               ; preds = %30, %25, %22
  %33 = phi ptr [ null, %22 ], [ %28, %30 ], [ null, %25 ]
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %5) #37
  ret ptr %33
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_fmt_char(i8 noundef signext %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #6 {
  %4 = alloca [16 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 16, ptr nonnull %4) #37
  %5 = icmp sgt i32 %1, 0
  br i1 %5, label %6, label %10

6:                                                ; preds = %3
  %7 = icmp eq i32 %2, 0
  %8 = select i1 %7, ptr @.str.2, ptr @.str.1
  %9 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 16, ptr noundef nonnull @.str.15, ptr noundef nonnull %8, i32 noundef %1) #37
  br label %12

10:                                               ; preds = %3
  %11 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 16, ptr noundef nonnull @.str.16) #37
  br label %12

12:                                               ; preds = %10, %6
  %13 = sext i8 %0 to i32
  %14 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %4, i32 noundef %13) #37
  %15 = icmp slt i32 %14, 0
  br i1 %15, label %23, label %16

16:                                               ; preds = %12
  %17 = add nuw nsw i32 %14, 1
  %18 = zext nneg i32 %17 to i64
  %19 = tail call noalias ptr @malloc(i64 noundef %18) #36
  %20 = icmp eq ptr %19, null
  br i1 %20, label %23, label %21

21:                                               ; preds = %16
  %22 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %19, i64 noundef %18, ptr noundef nonnull %4, i32 noundef %13) #37
  br label %23

23:                                               ; preds = %21, %16, %12
  %24 = phi ptr [ null, %12 ], [ %19, %21 ], [ null, %16 ]
  call void @llvm.lifetime.end.p0(i64 16, ptr nonnull %4) #37
  ret ptr %24
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_fmt_string(ptr noundef %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #6 {
  %4 = alloca [16 x i8], align 16
  %5 = icmp eq ptr %0, null
  %6 = select i1 %5, ptr @.str.2, ptr %0
  call void @llvm.lifetime.start.p0(i64 16, ptr nonnull %4) #37
  %7 = icmp sgt i32 %1, 0
  br i1 %7, label %8, label %12

8:                                                ; preds = %3
  %9 = icmp eq i32 %2, 0
  %10 = select i1 %9, ptr @.str.2, ptr @.str.1
  %11 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 16, ptr noundef nonnull @.str.17, ptr noundef nonnull %10, i32 noundef %1) #37
  br label %14

12:                                               ; preds = %3
  %13 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 16, ptr noundef nonnull @.str.18) #37
  br label %14

14:                                               ; preds = %12, %8
  %15 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %4, ptr noundef nonnull %6) #37
  %16 = icmp slt i32 %15, 0
  br i1 %16, label %24, label %17

17:                                               ; preds = %14
  %18 = add nuw nsw i32 %15, 1
  %19 = zext nneg i32 %18 to i64
  %20 = tail call noalias ptr @malloc(i64 noundef %19) #36
  %21 = icmp eq ptr %20, null
  br i1 %21, label %24, label %22

22:                                               ; preds = %17
  %23 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %20, i64 noundef %19, ptr noundef nonnull %4, ptr noundef nonnull %6) #37
  br label %24

24:                                               ; preds = %22, %17, %14
  %25 = phi ptr [ null, %14 ], [ %20, %22 ], [ null, %17 ]
  call void @llvm.lifetime.end.p0(i64 16, ptr nonnull %4) #37
  ret ptr %25
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_fmt_hex(i64 noundef %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #6 {
  %4 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %4) #37
  %5 = icmp sgt i32 %1, 0
  br i1 %5, label %6, label %10

6:                                                ; preds = %3
  %7 = icmp eq i32 %2, 0
  %8 = select i1 %7, ptr @.str.2, ptr @.str.1
  %9 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 32, ptr noundef nonnull @.str.19, ptr noundef nonnull %8, i32 noundef %1) #37
  br label %12

10:                                               ; preds = %3
  %11 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 32, ptr noundef nonnull @.str.20) #37
  br label %12

12:                                               ; preds = %10, %6
  %13 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %4, i64 noundef %0) #37
  %14 = add nsw i32 %13, 1
  %15 = sext i32 %14 to i64
  %16 = tail call noalias ptr @malloc(i64 noundef %15) #36
  %17 = icmp eq ptr %16, null
  br i1 %17, label %20, label %18

18:                                               ; preds = %12
  %19 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull %16, i64 noundef %15, ptr noundef nonnull %4, i64 noundef %0) #37
  br label %20

20:                                               ; preds = %18, %12
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %4) #37
  ret ptr %16
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_fmt_octal(i64 noundef %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #6 {
  %4 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %4) #37
  %5 = icmp sgt i32 %1, 0
  br i1 %5, label %6, label %10

6:                                                ; preds = %3
  %7 = icmp eq i32 %2, 0
  %8 = select i1 %7, ptr @.str.2, ptr @.str.1
  %9 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 32, ptr noundef nonnull @.str.21, ptr noundef nonnull %8, i32 noundef %1) #37
  br label %12

10:                                               ; preds = %3
  %11 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 32, ptr noundef nonnull @.str.22) #37
  br label %12

12:                                               ; preds = %10, %6
  %13 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %4, i64 noundef %0) #37
  %14 = add nsw i32 %13, 1
  %15 = sext i32 %14 to i64
  %16 = tail call noalias ptr @malloc(i64 noundef %15) #36
  %17 = icmp eq ptr %16, null
  br i1 %17, label %20, label %18

18:                                               ; preds = %12
  %19 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull %16, i64 noundef %15, ptr noundef nonnull %4, i64 noundef %0) #37
  br label %20

20:                                               ; preds = %18, %12
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %4) #37
  ret ptr %16
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_fmt_bool(i1 noundef zeroext %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #6 {
  %4 = alloca [16 x i8], align 16
  %5 = select i1 %0, ptr @.str.23, ptr @.str.24
  call void @llvm.lifetime.start.p0(i64 16, ptr nonnull %4) #37
  %6 = icmp sgt i32 %1, 0
  br i1 %6, label %7, label %11

7:                                                ; preds = %3
  %8 = icmp eq i32 %2, 0
  %9 = select i1 %8, ptr @.str.2, ptr @.str.1
  %10 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 16, ptr noundef nonnull @.str.17, ptr noundef nonnull %9, i32 noundef %1) #37
  br label %13

11:                                               ; preds = %3
  %12 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 16, ptr noundef nonnull @.str.18) #37
  br label %13

13:                                               ; preds = %11, %7
  %14 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %4, ptr noundef nonnull %5) #37
  %15 = icmp slt i32 %14, 0
  br i1 %15, label %23, label %16

16:                                               ; preds = %13
  %17 = add nuw nsw i32 %14, 1
  %18 = zext nneg i32 %17 to i64
  %19 = tail call noalias ptr @malloc(i64 noundef %18) #36
  %20 = icmp eq ptr %19, null
  br i1 %20, label %23, label %21

21:                                               ; preds = %16
  %22 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %19, i64 noundef %18, ptr noundef nonnull %4, ptr noundef nonnull %5) #37
  br label %23

23:                                               ; preds = %21, %16, %13
  %24 = phi ptr [ null, %13 ], [ %19, %21 ], [ null, %16 ]
  call void @llvm.lifetime.end.p0(i64 16, ptr nonnull %4) #37
  ret ptr %24
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_fmt_qbool(i8 noundef zeroext %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #6 {
  %4 = alloca [16 x i8], align 16
  %5 = and i8 %0, 3
  %6 = zext nneg i8 %5 to i64
  %7 = getelementptr inbounds nuw [4 x ptr], ptr @switch.table.qc_print_array_qbool, i64 0, i64 %6
  %8 = load ptr, ptr %7, align 8
  call void @llvm.lifetime.start.p0(i64 16, ptr nonnull %4) #37
  %9 = icmp sgt i32 %1, 0
  br i1 %9, label %10, label %14

10:                                               ; preds = %3
  %11 = icmp eq i32 %2, 0
  %12 = select i1 %11, ptr @.str.2, ptr @.str.1
  %13 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 16, ptr noundef nonnull @.str.17, ptr noundef nonnull %12, i32 noundef %1) #37
  br label %16

14:                                               ; preds = %3
  %15 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 16, ptr noundef nonnull @.str.18) #37
  br label %16

16:                                               ; preds = %14, %10
  %17 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %4, ptr noundef nonnull %8) #37
  %18 = icmp slt i32 %17, 0
  br i1 %18, label %26, label %19

19:                                               ; preds = %16
  %20 = add nuw nsw i32 %17, 1
  %21 = zext nneg i32 %20 to i64
  %22 = tail call noalias ptr @malloc(i64 noundef %21) #36
  %23 = icmp eq ptr %22, null
  br i1 %23, label %26, label %24

24:                                               ; preds = %19
  %25 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %22, i64 noundef %21, ptr noundef nonnull %4, ptr noundef nonnull %8) #37
  br label %26

26:                                               ; preds = %24, %19, %16
  %27 = phi ptr [ null, %16 ], [ %22, %24 ], [ null, %19 ]
  call void @llvm.lifetime.end.p0(i64 16, ptr nonnull %4) #37
  ret ptr %27
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias ptr @qc_fmt_ptr(ptr noundef %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #6 {
  %4 = alloca [64 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 64, ptr nonnull %4) #37
  %5 = icmp ne i32 %2, 0
  %6 = icmp sgt i32 %1, 0
  %7 = and i1 %6, %5
  br i1 %7, label %8, label %11

8:                                                ; preds = %3
  %9 = ptrtoint ptr %0 to i64
  %10 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 64, ptr noundef nonnull @.str.29, i32 noundef %1, i64 noundef %9) #37
  br label %16

11:                                               ; preds = %3
  br i1 %6, label %12, label %14

12:                                               ; preds = %11
  %13 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 64, ptr noundef nonnull @.str.30, i32 noundef %1, ptr noundef %0) #37
  br label %16

14:                                               ; preds = %11
  %15 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 64, ptr noundef nonnull @.str.31, ptr noundef %0) #37
  br label %16

16:                                               ; preds = %14, %12, %8
  %17 = call noalias ptr @strdup(ptr noundef nonnull %4) #37
  call void @llvm.lifetime.end.p0(i64 64, ptr nonnull %4) #37
  ret ptr %17
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(argmem: readwrite, inaccessiblemem: readwrite)
declare noalias ptr @strdup(ptr noundef readonly captures(none)) local_unnamed_addr #9

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local i32 @qc_powi_i32(i32 noundef %0, i32 noundef %1) local_unnamed_addr #10 {
  %3 = icmp slt i32 %1, 0
  br i1 %3, label %17, label %4

4:                                                ; preds = %2
  %5 = icmp eq i32 %1, 0
  br i1 %5, label %17, label %6

6:                                                ; preds = %6, %4
  %7 = phi i32 [ %13, %6 ], [ 1, %4 ]
  %8 = phi i32 [ %15, %6 ], [ %1, %4 ]
  %9 = phi i32 [ %14, %6 ], [ %0, %4 ]
  %10 = and i32 %8, 1
  %11 = icmp eq i32 %10, 0
  %12 = select i1 %11, i32 1, i32 %9
  %13 = mul nsw i32 %12, %7
  %14 = mul nsw i32 %9, %9
  %15 = lshr i32 %8, 1
  %16 = icmp ult i32 %8, 2
  br i1 %16, label %17, label %6, !llvm.loop !5

17:                                               ; preds = %6, %4, %2
  %18 = phi i32 [ 0, %2 ], [ 1, %4 ], [ %13, %6 ]
  ret i32 %18
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_ptr(ptr noundef %0) local_unnamed_addr #6 {
  %2 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.32, ptr noundef %0)
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @printf(ptr noundef readonly captures(none), ...) local_unnamed_addr #8

; Function Attrs: mustprogress nofree nounwind willreturn uwtable
define dso_local noalias noundef ptr @qc_string_concat(ptr noundef readonly captures(address_is_null) %0, ptr noundef readonly captures(address_is_null) %1) local_unnamed_addr #11 {
  %3 = icmp eq ptr %0, null
  %4 = select i1 %3, ptr @.str.2, ptr %0
  %5 = icmp eq ptr %1, null
  %6 = select i1 %5, ptr @.str.2, ptr %1
  %7 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %4) #40
  %8 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %6) #40
  %9 = add i64 %8, %7
  %10 = add i64 %9, 1
  %11 = tail call noalias ptr @malloc(i64 noundef %10) #36
  %12 = icmp eq ptr %11, null
  br i1 %12, label %16, label %13

13:                                               ; preds = %2
  tail call void @llvm.memcpy.p0.p0.i64(ptr nonnull align 1 %11, ptr nonnull align 1 %4, i64 %7, i1 false)
  %14 = getelementptr inbounds nuw i8, ptr %11, i64 %7
  tail call void @llvm.memcpy.p0.p0.i64(ptr nonnull align 1 %14, ptr nonnull align 1 %6, i64 %8, i1 false)
  %15 = getelementptr inbounds nuw i8, ptr %11, i64 %9
  store i8 0, ptr %15, align 1, !tbaa !7
  br label %16

16:                                               ; preds = %13, %2
  ret ptr %11
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(argmem: read)
declare i64 @strlen(ptr noundef captures(none)) local_unnamed_addr #12

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias writeonly captures(none), ptr noalias readonly captures(none), i64, i1 immarg) #13

; Function Attrs: mustprogress nofree norecurse nounwind willreturn memory(argmem: read) uwtable
define dso_local zeroext i1 @qc_string_eq(ptr noundef readonly captures(address_is_null) %0, ptr noundef readonly captures(address_is_null) %1) local_unnamed_addr #14 {
  %3 = icmp ne ptr %0, null
  %4 = icmp ne ptr %1, null
  %5 = and i1 %3, %4
  br i1 %5, label %6, label %9

6:                                                ; preds = %2
  %7 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(1) %1) #40
  %8 = icmp eq i32 %7, 0
  br label %9

9:                                                ; preds = %6, %2
  %10 = phi i1 [ %8, %6 ], [ false, %2 ]
  ret i1 %10
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(argmem: read)
declare i32 @strcmp(ptr noundef captures(none), ptr noundef captures(none)) local_unnamed_addr #12

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext range(i8 1, 4) i8 @qc_qand(i8 noundef zeroext %0, i8 noundef zeroext %1) local_unnamed_addr #10 {
  %3 = icmp ult i8 %0, 2
  %4 = icmp ult i8 %1, 2
  %5 = or i1 %3, %4
  %6 = icmp eq i8 %0, 2
  %7 = icmp eq i8 %1, 2
  %8 = and i1 %6, %7
  %9 = select i1 %8, i8 2, i8 3
  %10 = select i1 %5, i8 1, i8 %9
  ret i8 %10
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local zeroext range(i8 0, 4) i8 @qc_qor(i8 noundef zeroext %0, i8 noundef zeroext %1) local_unnamed_addr #10 {
  %3 = icmp eq i8 %0, 0
  %4 = icmp eq i8 %1, 0
  %5 = or i8 %1, %0
  %6 = icmp eq i8 %5, 0
  br i1 %6, label %23, label %7

7:                                                ; preds = %2
  %8 = icmp eq i8 %1, 1
  %9 = and i1 %3, %8
  br i1 %9, label %23, label %10

10:                                               ; preds = %7
  %11 = icmp eq i8 %1, 2
  %12 = and i1 %3, %11
  br i1 %12, label %23, label %13

13:                                               ; preds = %10
  %14 = icmp eq i8 %0, 1
  %15 = icmp ult i8 %1, 2
  %16 = and i1 %14, %15
  br i1 %16, label %23, label %17

17:                                               ; preds = %13
  %18 = icmp eq i8 %0, 2
  %19 = and i1 %18, %4
  br i1 %19, label %23, label %20

20:                                               ; preds = %17
  %21 = and i1 %18, %11
  %22 = select i1 %21, i8 2, i8 3
  br label %23

23:                                               ; preds = %20, %17, %13, %10, %7, %2
  %24 = phi i8 [ 0, %2 ], [ 1, %7 ], [ 2, %10 ], [ 1, %13 ], [ 2, %17 ], [ %22, %20 ]
  ret i8 %24
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local zeroext range(i8 0, 4) i8 @qc_qxor(i8 noundef zeroext %0, i8 noundef zeroext %1) local_unnamed_addr #10 {
  %3 = or i8 %1, %0
  %4 = icmp ult i8 %3, 2
  br i1 %4, label %14, label %5

5:                                                ; preds = %2
  %6 = icmp ult i8 %1, 2
  %7 = icmp ult i8 %0, 2
  %8 = xor i1 %7, %6
  br i1 %8, label %14, label %9

9:                                                ; preds = %5
  %10 = icmp eq i8 %0, 2
  %11 = icmp eq i8 %1, 2
  %12 = and i1 %10, %11
  %13 = select i1 %12, i8 1, i8 3
  br label %14

14:                                               ; preds = %9, %5, %2
  %15 = phi i8 [ 0, %2 ], [ 3, %5 ], [ %13, %9 ]
  ret i8 %15
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i8 @qc_qnot(i8 noundef zeroext %0) local_unnamed_addr #10 {
  %2 = sub i8 3, %0
  ret i8 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @qc_qand_collapse(i8 noundef zeroext %0, i8 noundef zeroext %1) local_unnamed_addr #10 {
  %3 = and i8 %0, 2
  %4 = and i8 %3, %1
  %5 = icmp ne i8 %4, 0
  ret i1 %5
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @qc_qor_collapse(i8 noundef zeroext %0, i8 noundef zeroext %1) local_unnamed_addr #10 {
  %3 = or i8 %1, %0
  %4 = and i8 %3, 2
  %5 = icmp ne i8 %4, 0
  ret i1 %5
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_to_string_int(i32 noundef %0) local_unnamed_addr #6 {
  %2 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %2) #37
  %3 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 32, ptr noundef nonnull @.str.33, i32 noundef %0) #37
  %4 = icmp slt i32 %3, 0
  br i1 %4, label %11, label %5

5:                                                ; preds = %1
  %6 = add nuw nsw i32 %3, 1
  %7 = zext nneg i32 %6 to i64
  %8 = tail call noalias ptr @malloc(i64 noundef %7) #36
  %9 = icmp eq ptr %8, null
  br i1 %9, label %11, label %10

10:                                               ; preds = %5
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %8, ptr noundef nonnull align 16 dereferenceable(1) %2, i64 %7, i1 false)
  br label %11

11:                                               ; preds = %10, %5, %1
  %12 = phi ptr [ null, %1 ], [ %8, %10 ], [ null, %5 ]
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %2) #37
  ret ptr %12
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_to_string_float(float noundef %0) local_unnamed_addr #6 {
  %2 = alloca [64 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 64, ptr nonnull %2) #37
  %3 = fpext float %0 to double
  %4 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 64, ptr noundef nonnull @.str.34, double noundef %3) #37
  %5 = icmp slt i32 %4, 0
  br i1 %5, label %12, label %6

6:                                                ; preds = %1
  %7 = add nuw nsw i32 %4, 1
  %8 = zext nneg i32 %7 to i64
  %9 = tail call noalias ptr @malloc(i64 noundef %8) #36
  %10 = icmp eq ptr %9, null
  br i1 %10, label %12, label %11

11:                                               ; preds = %6
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %9, ptr noundef nonnull align 16 dereferenceable(1) %2, i64 %8, i1 false)
  br label %12

12:                                               ; preds = %11, %6, %1
  %13 = phi ptr [ null, %1 ], [ %9, %11 ], [ null, %6 ]
  call void @llvm.lifetime.end.p0(i64 64, ptr nonnull %2) #37
  ret ptr %13
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_to_string_long_int(i64 noundef %0) local_unnamed_addr #6 {
  %2 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %2) #37
  %3 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 32, ptr noundef nonnull @.str.35, i64 noundef %0) #37
  %4 = icmp slt i32 %3, 0
  br i1 %4, label %11, label %5

5:                                                ; preds = %1
  %6 = add nuw nsw i32 %3, 1
  %7 = zext nneg i32 %6 to i64
  %8 = tail call noalias ptr @malloc(i64 noundef %7) #36
  %9 = icmp eq ptr %8, null
  br i1 %9, label %11, label %10

10:                                               ; preds = %5
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %8, ptr noundef nonnull align 16 dereferenceable(1) %2, i64 %7, i1 false)
  br label %11

11:                                               ; preds = %10, %5, %1
  %12 = phi ptr [ null, %1 ], [ %8, %10 ], [ null, %5 ]
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %2) #37
  ret ptr %12
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_to_string_short_int(i16 noundef signext %0) local_unnamed_addr #6 {
  %2 = alloca [64 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 64, ptr nonnull %2) #37
  %3 = sext i16 %0 to i32
  %4 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 64, ptr noundef nonnull @.str.36, i32 noundef %3) #37
  %5 = icmp slt i32 %4, 0
  br i1 %5, label %12, label %6

6:                                                ; preds = %1
  %7 = add nuw nsw i32 %4, 1
  %8 = zext nneg i32 %7 to i64
  %9 = tail call noalias ptr @malloc(i64 noundef %8) #36
  %10 = icmp eq ptr %9, null
  br i1 %10, label %12, label %11

11:                                               ; preds = %6
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %9, ptr noundef nonnull align 16 dereferenceable(1) %2, i64 %8, i1 false)
  br label %12

12:                                               ; preds = %11, %6, %1
  %13 = phi ptr [ null, %1 ], [ %9, %11 ], [ null, %6 ]
  call void @llvm.lifetime.end.p0(i64 64, ptr nonnull %2) #37
  ret ptr %13
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local i32 @qc_to_int_from_float(float noundef %0) local_unnamed_addr #10 {
  %2 = fptosi float %0 to i32
  ret i32 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local i32 @qc_to_int_from_double(double noundef %0) local_unnamed_addr #10 {
  %2 = fptosi double %0 to i32
  ret i32 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local range(i32 -128, 128) i32 @qc_to_int_from_char(i8 noundef signext %0) local_unnamed_addr #10 {
  %2 = sext i8 %0 to i32
  ret i32 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef float @qc_to_float_from_double(double noundef %0) local_unnamed_addr #10 {
  %2 = fptrunc double %0 to float
  ret float %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef float @qc_to_float_from_bool(i1 noundef zeroext %0) local_unnamed_addr #10 {
  %2 = select i1 %0, float 1.000000e+00, float 0.000000e+00
  ret float %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef double @qc_to_double_from_float(float noundef %0) local_unnamed_addr #10 {
  %2 = fpext float %0 to double
  ret double %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef double @qc_to_double_from_bool(i1 noundef zeroext %0) local_unnamed_addr #10 {
  %2 = select i1 %0, double 1.000000e+00, double 0.000000e+00
  ret double %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @qc_to_bool_from_int(i32 noundef %0) local_unnamed_addr #10 {
  %2 = icmp ne i32 %0, 0
  ret i1 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @qc_to_bool_from_float(float noundef %0) local_unnamed_addr #10 {
  %2 = fcmp une float %0, 0.000000e+00
  ret i1 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @qc_to_bool_from_double(double noundef %0) local_unnamed_addr #10 {
  %2 = fcmp une double %0, 0.000000e+00
  ret i1 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef signext i8 @qc_to_char_from_int(i32 noundef %0) local_unnamed_addr #10 {
  %2 = trunc i32 %0 to i8
  ret i8 %2
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_to_string_double(double noundef %0) local_unnamed_addr #6 {
  %2 = alloca [64 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 64, ptr nonnull %2) #37
  %3 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 64, ptr noundef nonnull @.str.34, double noundef %0) #37
  %4 = icmp slt i32 %3, 0
  br i1 %4, label %11, label %5

5:                                                ; preds = %1
  %6 = add nuw nsw i32 %3, 1
  %7 = zext nneg i32 %6 to i64
  %8 = tail call noalias ptr @malloc(i64 noundef %7) #36
  %9 = icmp eq ptr %8, null
  br i1 %9, label %11, label %10

10:                                               ; preds = %5
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %8, ptr noundef nonnull align 16 dereferenceable(1) %2, i64 %7, i1 false)
  br label %11

11:                                               ; preds = %10, %5, %1
  %12 = phi ptr [ null, %1 ], [ %8, %10 ], [ null, %5 ]
  call void @llvm.lifetime.end.p0(i64 64, ptr nonnull %2) #37
  ret ptr %12
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(readwrite, argmem: none) uwtable
define dso_local noalias noundef ptr @qc_to_string_bool(i1 noundef zeroext %0) local_unnamed_addr #15 {
  %2 = select i1 %0, i64 5, i64 6
  %3 = tail call noalias ptr @malloc(i64 noundef %2) #36
  %4 = icmp eq ptr %3, null
  br i1 %4, label %7, label %5

5:                                                ; preds = %1
  %6 = select i1 %0, ptr @.str.23, ptr @.str.24
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(5) %3, ptr noundef nonnull align 1 dereferenceable(5) %6, i64 %2, i1 false)
  br label %7

7:                                                ; preds = %5, %1
  ret ptr %3
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(readwrite, argmem: none) uwtable
define dso_local noalias noundef ptr @qc_to_string_qbool(i8 noundef zeroext %0) local_unnamed_addr #15 {
  %2 = and i8 %0, 3
  %3 = zext nneg i8 %2 to i64
  %4 = getelementptr inbounds nuw [4 x ptr], ptr @switch.table.qc_print_array_qbool, i64 0, i64 %3
  %5 = load ptr, ptr %4, align 8
  %6 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %5) #40
  %7 = add i64 %6, 1
  %8 = tail call noalias ptr @malloc(i64 noundef %7) #36
  %9 = icmp eq ptr %8, null
  br i1 %9, label %11, label %10

10:                                               ; preds = %1
  tail call void @llvm.memcpy.p0.p0.i64(ptr nonnull align 1 %8, ptr nonnull align 1 %5, i64 %7, i1 false)
  br label %11

11:                                               ; preds = %10, %1
  ret ptr %8
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(write, argmem: none, inaccessiblemem: readwrite) uwtable
define dso_local noalias noundef ptr @qc_to_string_char(i8 noundef signext %0) local_unnamed_addr #16 {
  %2 = tail call noalias dereferenceable_or_null(2) ptr @malloc(i64 noundef 2) #36
  %3 = icmp eq ptr %2, null
  br i1 %3, label %6, label %4

4:                                                ; preds = %1
  store i8 %0, ptr %2, align 1, !tbaa !7
  %5 = getelementptr inbounds nuw i8, ptr %2, i64 1
  store i8 0, ptr %5, align 1, !tbaa !7
  br label %6

6:                                                ; preds = %4, %1
  ret ptr %2
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_string(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #6 {
  %2 = icmp eq ptr %0, null
  %3 = select i1 %2, ptr @.str.2, ptr %0
  %4 = load ptr, ptr @stdout, align 8, !tbaa !10
  %5 = tail call i32 @fputs(ptr noundef nonnull %3, ptr noundef %4)
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @fputs(ptr noundef readonly captures(none), ptr noundef captures(none)) local_unnamed_addr #8

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_int(i32 noundef %0) local_unnamed_addr #6 {
  %2 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.33, i32 noundef %0)
  ret void
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_double(double noundef %0) local_unnamed_addr #6 {
  %2 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, double noundef %0)
  ret void
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_char(i8 noundef signext %0) local_unnamed_addr #6 {
  %2 = zext i8 %0 to i32
  %3 = load ptr, ptr @stdout, align 8, !tbaa !10
  %4 = tail call noundef i32 @putc(i32 noundef %2, ptr noundef %3)
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @putc(i32 noundef, ptr noundef captures(none)) local_unnamed_addr #8

; Function Attrs: mustprogress nounwind uwtable
define dso_local i32 @qc_time() local_unnamed_addr #17 {
  %1 = tail call i64 @time(ptr noundef null) #37
  %2 = trunc i64 %1 to i32
  ret i32 %2
}

; Function Attrs: nounwind
declare i64 @time(ptr noundef) local_unnamed_addr #18

; Function Attrs: mustprogress nounwind uwtable
define dso_local void @qc_seed(i32 noundef %0) local_unnamed_addr #17 {
  tail call void @srand(i32 noundef %0) #37
  ret void
}

; Function Attrs: nounwind
declare void @srand(i32 noundef) local_unnamed_addr #18

; Function Attrs: mustprogress nounwind uwtable
define dso_local float @qc_random_float() local_unnamed_addr #17 {
  %1 = tail call i32 @rand() #37
  %2 = sitofp i32 %1 to float
  %3 = fmul float %2, 0x3E00000000000000
  ret float %3
}

; Function Attrs: nounwind
declare i32 @rand() local_unnamed_addr #18

; Function Attrs: mustprogress nounwind uwtable
define dso_local range(i32 -2147483647, -2147483648) i32 @qc_random_int(i32 noundef %0) local_unnamed_addr #17 {
  %2 = tail call i32 @rand() #37
  %3 = srem i32 %2, %0
  ret i32 %3
}

; Function Attrs: mustprogress nounwind uwtable
define dso_local i32 @qc_random_range(i32 noundef %0, i32 noundef %1) local_unnamed_addr #17 {
  %3 = tail call i32 @rand() #37
  %4 = sub nsw i32 %1, %0
  %5 = srem i32 %3, %4
  %6 = add nsw i32 %5, %0
  ret i32 %6
}

; Function Attrs: mustprogress nofree norecurse nounwind willreturn memory(argmem: read) uwtable
define dso_local i32 @qc_len(ptr noundef readonly captures(none) %0) local_unnamed_addr #14 {
  %2 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #40
  %3 = trunc i64 %2 to i32
  ret i32 %3
}

; Function Attrs: mustprogress nofree nounwind memory(readwrite, argmem: read) uwtable
define dso_local noalias noundef ptr @qc_to_lower(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #19 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %22, label %3

3:                                                ; preds = %1
  %4 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #40
  %5 = add i64 %4, 1
  %6 = tail call noalias ptr @malloc(i64 noundef %5) #36
  %7 = icmp eq ptr %6, null
  br i1 %7, label %22, label %8

8:                                                ; preds = %3
  %9 = icmp eq i64 %4, 0
  br i1 %9, label %10, label %12

10:                                               ; preds = %12, %8
  %11 = getelementptr inbounds nuw i8, ptr %6, i64 %4
  store i8 0, ptr %11, align 1, !tbaa !7
  br label %22

12:                                               ; preds = %12, %8
  %13 = phi i64 [ %20, %12 ], [ 0, %8 ]
  %14 = getelementptr inbounds nuw i8, ptr %0, i64 %13
  %15 = load i8, ptr %14, align 1, !tbaa !7
  %16 = zext i8 %15 to i32
  %17 = tail call i32 @tolower(i32 noundef %16) #40
  %18 = trunc i32 %17 to i8
  %19 = getelementptr inbounds nuw i8, ptr %6, i64 %13
  store i8 %18, ptr %19, align 1, !tbaa !7
  %20 = add nuw i64 %13, 1
  %21 = icmp eq i64 %20, %4
  br i1 %21, label %10, label %12, !llvm.loop !13

22:                                               ; preds = %10, %3, %1
  %23 = phi ptr [ null, %1 ], [ %6, %10 ], [ null, %3 ]
  ret ptr %23
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(read)
declare i32 @tolower(i32 noundef) local_unnamed_addr #20

; Function Attrs: mustprogress nofree nounwind memory(readwrite, argmem: read) uwtable
define dso_local noalias noundef ptr @qc_to_upper(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #19 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %22, label %3

3:                                                ; preds = %1
  %4 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #40
  %5 = add i64 %4, 1
  %6 = tail call noalias ptr @malloc(i64 noundef %5) #36
  %7 = icmp eq ptr %6, null
  br i1 %7, label %22, label %8

8:                                                ; preds = %3
  %9 = icmp eq i64 %4, 0
  br i1 %9, label %10, label %12

10:                                               ; preds = %12, %8
  %11 = getelementptr inbounds nuw i8, ptr %6, i64 %4
  store i8 0, ptr %11, align 1, !tbaa !7
  br label %22

12:                                               ; preds = %12, %8
  %13 = phi i64 [ %20, %12 ], [ 0, %8 ]
  %14 = getelementptr inbounds nuw i8, ptr %0, i64 %13
  %15 = load i8, ptr %14, align 1, !tbaa !7
  %16 = zext i8 %15 to i32
  %17 = tail call i32 @toupper(i32 noundef %16) #40
  %18 = trunc i32 %17 to i8
  %19 = getelementptr inbounds nuw i8, ptr %6, i64 %13
  store i8 %18, ptr %19, align 1, !tbaa !7
  %20 = add nuw i64 %13, 1
  %21 = icmp eq i64 %20, %4
  br i1 %21, label %10, label %12, !llvm.loop !14

22:                                               ; preds = %10, %3, %1
  %23 = phi ptr [ null, %1 ], [ %6, %10 ], [ null, %3 ]
  ret ptr %23
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(read)
declare i32 @toupper(i32 noundef) local_unnamed_addr #20

; Function Attrs: mustprogress nofree nounwind willreturn uwtable
define dso_local noalias noundef ptr @qc_substring(ptr noundef readonly captures(address_is_null) %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #11 {
  %4 = icmp eq ptr %0, null
  br i1 %4, label %29, label %5

5:                                                ; preds = %3
  %6 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #40
  %7 = trunc i64 %6 to i32
  %8 = icmp slt i32 %1, 0
  br i1 %8, label %13, label %9

9:                                                ; preds = %5
  %10 = icmp sge i32 %1, %7
  %11 = icmp slt i32 %2, 1
  %12 = or i1 %11, %10
  br i1 %12, label %13, label %15

13:                                               ; preds = %9, %5
  %14 = tail call noalias dereferenceable_or_null(1) ptr @malloc(i64 noundef 1) #36
  store i8 0, ptr %14, align 1, !tbaa !7
  br label %29

15:                                               ; preds = %9
  %16 = add nuw nsw i32 %2, %1
  %17 = icmp samesign ugt i32 %16, %7
  %18 = sub nsw i32 %7, %1
  %19 = select i1 %17, i32 %18, i32 %2
  %20 = add nuw nsw i32 %19, 1
  %21 = zext nneg i32 %20 to i64
  %22 = tail call noalias ptr @malloc(i64 noundef %21) #36
  %23 = icmp eq ptr %22, null
  br i1 %23, label %29, label %24

24:                                               ; preds = %15
  %25 = zext nneg i32 %1 to i64
  %26 = getelementptr inbounds nuw i8, ptr %0, i64 %25
  %27 = sext i32 %19 to i64
  tail call void @llvm.memcpy.p0.p0.i64(ptr nonnull align 1 %22, ptr nonnull align 1 %26, i64 %27, i1 false)
  %28 = getelementptr inbounds i8, ptr %22, i64 %27
  store i8 0, ptr %28, align 1, !tbaa !7
  br label %29

29:                                               ; preds = %24, %15, %13, %3
  %30 = phi ptr [ null, %3 ], [ %14, %13 ], [ %22, %24 ], [ null, %15 ]
  ret ptr %30
}

; Function Attrs: mustprogress nofree norecurse nounwind willreturn memory(argmem: read) uwtable
define dso_local range(i32 0, 2) i32 @qc_contains(ptr noundef readonly %0, ptr noundef readonly captures(address_is_null) %1) local_unnamed_addr #14 {
  %3 = icmp ne ptr %0, null
  %4 = icmp ne ptr %1, null
  %5 = and i1 %3, %4
  br i1 %5, label %6, label %10

6:                                                ; preds = %2
  %7 = tail call noundef ptr @strstr(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(1) %1) #40
  %8 = icmp ne ptr %7, null
  %9 = zext i1 %8 to i32
  br label %10

10:                                               ; preds = %6, %2
  %11 = phi i32 [ %9, %6 ], [ 0, %2 ]
  ret i32 %11
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(argmem: read)
declare noundef ptr @strstr(ptr noundef, ptr noundef captures(none)) local_unnamed_addr #12

; Function Attrs: mustprogress nofree norecurse nounwind willreturn memory(argmem: read) uwtable
define dso_local range(i32 0, 2) i32 @qc_startswith(ptr noundef readonly captures(address_is_null) %0, ptr noundef readonly captures(address_is_null) %1) local_unnamed_addr #14 {
  %3 = icmp ne ptr %0, null
  %4 = icmp ne ptr %1, null
  %5 = and i1 %3, %4
  br i1 %5, label %6, label %11

6:                                                ; preds = %2
  %7 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %1) #40
  %8 = tail call i32 @strncmp(ptr noundef nonnull %0, ptr noundef nonnull %1, i64 noundef %7) #40
  %9 = icmp eq i32 %8, 0
  %10 = zext i1 %9 to i32
  br label %11

11:                                               ; preds = %6, %2
  %12 = phi i32 [ %10, %6 ], [ 0, %2 ]
  ret i32 %12
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(argmem: read)
declare i32 @strncmp(ptr noundef captures(none), ptr noundef captures(none), i64 noundef) local_unnamed_addr #12

; Function Attrs: mustprogress nofree norecurse nounwind willreturn memory(argmem: read) uwtable
define dso_local range(i32 0, 2) i32 @qc_endswith(ptr noundef readonly captures(address_is_null) %0, ptr noundef readonly captures(address_is_null) %1) local_unnamed_addr #14 {
  %3 = icmp ne ptr %0, null
  %4 = icmp ne ptr %1, null
  %5 = and i1 %3, %4
  br i1 %5, label %6, label %17

6:                                                ; preds = %2
  %7 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #40
  %8 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %1) #40
  %9 = icmp ugt i64 %8, %7
  br i1 %9, label %17, label %10

10:                                               ; preds = %6
  %11 = getelementptr inbounds nuw i8, ptr %0, i64 %7
  %12 = sub i64 0, %8
  %13 = getelementptr inbounds i8, ptr %11, i64 %12
  %14 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %13, ptr noundef nonnull dereferenceable(1) %1) #40
  %15 = icmp eq i32 %14, 0
  %16 = zext i1 %15 to i32
  br label %17

17:                                               ; preds = %10, %6, %2
  %18 = phi i32 [ 0, %2 ], [ %16, %10 ], [ 0, %6 ]
  ret i32 %18
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_float(float noundef %0) local_unnamed_addr #6 {
  %2 = fpext float %0 to double
  %3 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, double noundef %2)
  ret void
}

; Function Attrs: mustprogress nofree norecurse nounwind willreturn memory(argmem: read) uwtable
define dso_local zeroext i1 @qc_to_bool_from_string(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #14 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %13, label %3

3:                                                ; preds = %1
  %4 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(5) @.str.23) #40
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %13, label %6

6:                                                ; preds = %3
  %7 = load i8, ptr %0, align 1
  %8 = icmp eq i8 %7, 49
  br i1 %8, label %9, label %13

9:                                                ; preds = %6
  %10 = getelementptr inbounds nuw i8, ptr %0, i64 1
  %11 = load i8, ptr %10, align 1
  %12 = icmp eq i8 %11, 0
  br label %13

13:                                               ; preds = %9, %6, %3, %1
  %14 = phi i1 [ false, %1 ], [ true, %3 ], [ false, %6 ], [ %12, %9 ]
  ret i1 %14
}

; Function Attrs: mustprogress nofree norecurse nounwind willreturn memory(argmem: read) uwtable
define dso_local zeroext range(i8 0, 4) i8 @qc_to_qbool_from_string(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #14 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %13, label %3

3:                                                ; preds = %1
  %4 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(6) @.str.27) #40
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %13, label %6

6:                                                ; preds = %3
  %7 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(7) @.str.26) #40
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %13, label %9

9:                                                ; preds = %6
  %10 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(5) @.str.28) #40
  %11 = icmp eq i32 %10, 0
  %12 = select i1 %11, i8 3, i8 0
  br label %13

13:                                               ; preds = %9, %6, %3, %1
  %14 = phi i8 [ 0, %1 ], [ 2, %3 ], [ 1, %6 ], [ %12, %9 ]
  ret i8 %14
}

; Function Attrs: mustprogress uwtable
define dso_local noalias ptr @qc_qin() local_unnamed_addr #21 {
  %1 = alloca [1024 x i8], align 16
  %2 = load ptr, ptr @stdout, align 8, !tbaa !10
  %3 = tail call i32 @fflush(ptr noundef %2)
  %4 = load ptr, ptr @stderr, align 8, !tbaa !10
  %5 = tail call i32 @fflush(ptr noundef %4)
  %6 = load ptr, ptr @stdin, align 8, !tbaa !10
  %7 = tail call i32 @fflush(ptr noundef %6)
  call void @llvm.lifetime.start.p0(i64 1024, ptr nonnull %1) #37
  %8 = call i32 (ptr, ...) @__isoc23_scanf(ptr noundef nonnull @.str.38, ptr noundef nonnull %1)
  %9 = load ptr, ptr @stderr, align 8, !tbaa !10
  %10 = call i32 @fflush(ptr noundef %9)
  %11 = load ptr, ptr @stdin, align 8, !tbaa !10
  %12 = call i32 @fflush(ptr noundef %11)
  %13 = icmp eq i32 %8, 1
  %14 = select i1 %13, ptr %1, ptr @.str.2
  %15 = call noalias ptr @strdup(ptr noundef nonnull %14) #37
  call void @llvm.lifetime.end.p0(i64 1024, ptr nonnull %1) #37
  ret ptr %15
}

declare i32 @__isoc23_scanf(ptr noundef, ...) local_unnamed_addr #22

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_bool(i1 noundef zeroext %0) local_unnamed_addr #6 {
  %2 = select i1 %0, ptr @.str.23, ptr @.str.24
  %3 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.38, ptr noundef nonnull %2)
  ret void
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_trim(ptr noundef %0) local_unnamed_addr #6 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %40, label %3

3:                                                ; preds = %1
  %4 = load i8, ptr %0, align 1, !tbaa !7
  %5 = icmp eq i8 %4, 0
  br i1 %5, label %16, label %6

6:                                                ; preds = %12, %3
  %7 = phi i8 [ %14, %12 ], [ %4, %3 ]
  %8 = phi ptr [ %13, %12 ], [ %0, %3 ]
  %9 = zext i8 %7 to i32
  %10 = tail call i32 @isspace(i32 noundef %9) #40
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %18, label %12

12:                                               ; preds = %6
  %13 = getelementptr inbounds nuw i8, ptr %8, i64 1
  %14 = load i8, ptr %13, align 1, !tbaa !7
  %15 = icmp eq i8 %14, 0
  br i1 %15, label %16, label %6, !llvm.loop !15

16:                                               ; preds = %12, %3
  %17 = tail call noalias dereferenceable_or_null(1) ptr @malloc(i64 noundef 1) #36
  store i8 0, ptr %17, align 1, !tbaa !7
  br label %40

18:                                               ; preds = %6
  %19 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %8) #40
  %20 = getelementptr inbounds nuw i8, ptr %8, i64 %19
  br label %21

21:                                               ; preds = %25, %18
  %22 = phi ptr [ %20, %18 ], [ %23, %25 ]
  %23 = getelementptr inbounds i8, ptr %22, i64 -1
  %24 = icmp ugt ptr %23, %8
  br i1 %24, label %25, label %30

25:                                               ; preds = %21
  %26 = load i8, ptr %23, align 1, !tbaa !7
  %27 = zext i8 %26 to i32
  %28 = tail call i32 @isspace(i32 noundef %27) #40
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %30, label %21, !llvm.loop !16

30:                                               ; preds = %25, %21
  %31 = ptrtoint ptr %23 to i64
  %32 = ptrtoint ptr %8 to i64
  %33 = sub i64 %31, %32
  %34 = add i64 %33, 2
  %35 = tail call noalias ptr @malloc(i64 noundef %34) #36
  %36 = icmp eq ptr %35, null
  br i1 %36, label %40, label %37

37:                                               ; preds = %30
  %38 = add nsw i64 %33, 1
  tail call void @llvm.memcpy.p0.p0.i64(ptr nonnull align 1 %35, ptr nonnull align 1 %8, i64 %38, i1 false)
  %39 = getelementptr inbounds nuw i8, ptr %35, i64 %38
  store i8 0, ptr %39, align 1, !tbaa !7
  br label %40

40:                                               ; preds = %37, %30, %16, %1
  %41 = phi ptr [ %17, %16 ], [ null, %1 ], [ %35, %37 ], [ null, %30 ]
  ret ptr %41
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(read)
declare i32 @isspace(i32 noundef) local_unnamed_addr #20

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noundef ptr @qc_replace(ptr noundef readonly %0, ptr noundef readonly captures(address_is_null) %1, ptr noundef readonly captures(address_is_null) %2) local_unnamed_addr #6 {
  %4 = icmp ne ptr %0, null
  %5 = icmp ne ptr %1, null
  %6 = and i1 %4, %5
  %7 = icmp ne ptr %2, null
  %8 = and i1 %6, %7
  br i1 %8, label %9, label %65

9:                                                ; preds = %3
  %10 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %1) #40
  %11 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %2) #40
  %12 = icmp eq i64 %10, 0
  br i1 %12, label %16, label %13

13:                                               ; preds = %9
  %14 = tail call noundef ptr @strstr(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(1) %1) #40
  %15 = icmp eq ptr %14, null
  br i1 %15, label %28, label %21

16:                                               ; preds = %9
  %17 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #40
  %18 = add i64 %17, 1
  %19 = tail call noalias ptr @malloc(i64 noundef %18) #36
  %20 = tail call ptr @strcpy(ptr noundef nonnull dereferenceable(1) %19, ptr noundef nonnull dereferenceable(1) %0) #37
  br label %65

21:                                               ; preds = %21, %13
  %22 = phi ptr [ %26, %21 ], [ %14, %13 ]
  %23 = phi i32 [ %24, %21 ], [ 0, %13 ]
  %24 = add nuw nsw i32 %23, 1
  %25 = getelementptr inbounds nuw i8, ptr %22, i64 %10
  %26 = tail call noundef ptr @strstr(ptr noundef nonnull dereferenceable(1) %25, ptr noundef nonnull dereferenceable(1) %1) #40
  %27 = icmp eq ptr %26, null
  br i1 %27, label %33, label %21, !llvm.loop !17

28:                                               ; preds = %13
  %29 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #40
  %30 = add i64 %29, 1
  %31 = tail call noalias ptr @malloc(i64 noundef %30) #36
  %32 = tail call ptr @strcpy(ptr noundef nonnull dereferenceable(1) %31, ptr noundef nonnull dereferenceable(1) %0) #37
  br label %65

33:                                               ; preds = %21
  %34 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #40
  %35 = zext nneg i32 %24 to i64
  %36 = sub i64 %11, %10
  %37 = mul i64 %36, %35
  %38 = add i64 %37, 1
  %39 = add i64 %38, %34
  %40 = tail call noalias ptr @malloc(i64 noundef %39) #36
  %41 = icmp eq ptr %40, null
  br i1 %41, label %65, label %42

42:                                               ; preds = %33
  %43 = load i8, ptr %0, align 1, !tbaa !7
  %44 = icmp eq i8 %43, 0
  br i1 %44, label %63, label %45

45:                                               ; preds = %58, %42
  %46 = phi i8 [ %61, %58 ], [ %43, %42 ]
  %47 = phi ptr [ %60, %58 ], [ %40, %42 ]
  %48 = phi ptr [ %59, %58 ], [ %0, %42 ]
  %49 = tail call i64 @strlen(ptr nonnull dereferenceable(1) %1)
  %50 = tail call i32 @strncmp(ptr nonnull %48, ptr nonnull %1, i64 %49)
  %51 = icmp eq i32 %50, 0
  br i1 %51, label %52, label %55

52:                                               ; preds = %45
  tail call void @llvm.memcpy.p0.p0.i64(ptr align 1 %47, ptr nonnull align 1 %2, i64 %11, i1 false)
  %53 = getelementptr inbounds nuw i8, ptr %47, i64 %11
  %54 = getelementptr inbounds nuw i8, ptr %48, i64 %10
  br label %58

55:                                               ; preds = %45
  %56 = getelementptr inbounds nuw i8, ptr %48, i64 1
  %57 = getelementptr inbounds nuw i8, ptr %47, i64 1
  store i8 %46, ptr %47, align 1, !tbaa !7
  br label %58

58:                                               ; preds = %55, %52
  %59 = phi ptr [ %54, %52 ], [ %56, %55 ]
  %60 = phi ptr [ %53, %52 ], [ %57, %55 ]
  %61 = load i8, ptr %59, align 1, !tbaa !7
  %62 = icmp eq i8 %61, 0
  br i1 %62, label %63, label %45, !llvm.loop !18

63:                                               ; preds = %58, %42
  %64 = phi ptr [ %40, %42 ], [ %60, %58 ]
  store i8 0, ptr %64, align 1, !tbaa !7
  br label %65

65:                                               ; preds = %63, %33, %28, %16, %3
  %66 = phi ptr [ null, %3 ], [ %19, %16 ], [ %31, %28 ], [ %40, %63 ], [ null, %33 ]
  ret ptr %66
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(argmem: readwrite)
declare ptr @strcpy(ptr noalias noundef returned writeonly, ptr noalias noundef readonly captures(none)) local_unnamed_addr #23

; Function Attrs: mustprogress nounwind uwtable
define dso_local i32 @qc_to_int_from_string(ptr noundef %0) local_unnamed_addr #17 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %6, label %3

3:                                                ; preds = %1
  %4 = tail call i64 @__isoc23_strtol(ptr noundef nonnull %0, ptr noundef null, i32 noundef 10) #37
  %5 = trunc i64 %4 to i32
  br label %6

6:                                                ; preds = %3, %1
  %7 = phi i32 [ %5, %3 ], [ 0, %1 ]
  ret i32 %7
}

; Function Attrs: nounwind
declare i64 @__isoc23_strtol(ptr noundef, ptr noundef, i32 noundef) local_unnamed_addr #18

; Function Attrs: mustprogress nounwind uwtable
define dso_local signext i16 @qc_to_short_int_from_string(ptr noundef %0) local_unnamed_addr #17 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %6, label %3

3:                                                ; preds = %1
  %4 = tail call i64 @__isoc23_strtol(ptr noundef nonnull %0, ptr noundef null, i32 noundef 10) #37
  %5 = trunc i64 %4 to i16
  br label %6

6:                                                ; preds = %3, %1
  %7 = phi i16 [ %5, %3 ], [ 0, %1 ]
  ret i16 %7
}

; Function Attrs: mustprogress nounwind uwtable
define dso_local i64 @qc_to_long_int_from_string(ptr noundef %0) local_unnamed_addr #17 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %5, label %3

3:                                                ; preds = %1
  %4 = tail call i64 @__isoc23_strtoll(ptr noundef nonnull %0, ptr noundef null, i32 noundef 10) #37
  br label %5

5:                                                ; preds = %3, %1
  %6 = phi i64 [ %4, %3 ], [ 0, %1 ]
  ret i64 %6
}

; Function Attrs: nounwind
declare i64 @__isoc23_strtoll(ptr noundef, ptr noundef, i32 noundef) local_unnamed_addr #18

; Function Attrs: mustprogress nounwind uwtable
define dso_local i64 @qc_to_addr_t_from_string(ptr noundef %0) local_unnamed_addr #17 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %5, label %3

3:                                                ; preds = %1
  %4 = tail call i64 @__isoc23_strtoull(ptr noundef nonnull %0, ptr noundef null, i32 noundef 10) #37
  br label %5

5:                                                ; preds = %3, %1
  %6 = phi i64 [ %4, %3 ], [ 0, %1 ]
  ret i64 %6
}

; Function Attrs: nounwind
declare i64 @__isoc23_strtoull(ptr noundef, ptr noundef, i32 noundef) local_unnamed_addr #18

; Function Attrs: mustprogress nofree norecurse nounwind willreturn uwtable
define dso_local float @qc_to_float_from_string(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #24 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %6, label %3

3:                                                ; preds = %1
  %4 = tail call double @strtod(ptr noundef nonnull captures(none) %0, ptr noundef null) #37
  %5 = fptrunc double %4 to float
  br label %6

6:                                                ; preds = %3, %1
  %7 = phi float [ %5, %3 ], [ 0.000000e+00, %1 ]
  ret float %7
}

; Function Attrs: mustprogress nofree nounwind willreturn
declare double @strtod(ptr noundef readonly, ptr noundef captures(none)) local_unnamed_addr #25

; Function Attrs: mustprogress nofree norecurse nounwind willreturn uwtable
define dso_local double @qc_to_double_from_string(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #24 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %5, label %3

3:                                                ; preds = %1
  %4 = tail call double @strtod(ptr noundef nonnull captures(none) %0, ptr noundef null) #37
  br label %5

5:                                                ; preds = %3, %1
  %6 = phi double [ %4, %3 ], [ 0.000000e+00, %1 ]
  ret double %6
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
define dso_local signext i8 @qc_to_char_from_string(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #26 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %5, label %3

3:                                                ; preds = %1
  %4 = load i8, ptr %0, align 1, !tbaa !7
  br label %5

5:                                                ; preds = %3, %1
  %6 = phi i8 [ 0, %1 ], [ %4, %3 ]
  ret i8 %6
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local range(i32 0, 2) i32 @qc_to_int_from_bool(i1 noundef zeroext %0) local_unnamed_addr #10 {
  %2 = zext i1 %0 to i32
  ret i32 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef float @qc_to_float_from_int(i32 noundef %0) local_unnamed_addr #10 {
  %2 = sitofp i32 %0 to float
  ret float %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef double @qc_to_double_from_int(i32 noundef %0) local_unnamed_addr #10 {
  %2 = sitofp i32 %0 to double
  ret double %2
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print(ptr noundef %0) local_unnamed_addr #6 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %5, label %3

3:                                                ; preds = %1
  %4 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.38, ptr noundef nonnull %0)
  br label %5

5:                                                ; preds = %3, %1
  ret void
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_println(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #6 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %5, label %3

3:                                                ; preds = %1
  %4 = tail call i32 @puts(ptr nonnull dereferenceable(1) %0)
  br label %8

5:                                                ; preds = %1
  %6 = load ptr, ptr @stdout, align 8, !tbaa !10
  %7 = tail call noundef i32 @putc(i32 noundef 10, ptr noundef %6)
  br label %8

8:                                                ; preds = %5, %3
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @puts(ptr noundef readonly captures(none)) local_unnamed_addr #27

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_array_int(ptr noundef readonly captures(none) %0, i32 noundef %1) local_unnamed_addr #6 {
  %3 = load ptr, ptr @stdout, align 8, !tbaa !10
  %4 = tail call noundef i32 @putc(i32 noundef 91, ptr noundef %3)
  %5 = icmp sgt i32 %1, 0
  br i1 %5, label %6, label %10

6:                                                ; preds = %2
  %7 = add nsw i32 %1, -1
  %8 = zext nneg i32 %7 to i64
  %9 = zext nneg i32 %1 to i64
  br label %13

10:                                               ; preds = %21, %2
  %11 = load ptr, ptr @stdout, align 8, !tbaa !10
  %12 = tail call noundef i32 @putc(i32 noundef 93, ptr noundef %11)
  ret void

13:                                               ; preds = %21, %6
  %14 = phi i64 [ 0, %6 ], [ %22, %21 ]
  %15 = getelementptr inbounds nuw i32, ptr %0, i64 %14
  %16 = load i32, ptr %15, align 4, !tbaa !19
  %17 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.33, i32 noundef %16)
  %18 = icmp samesign ult i64 %14, %8
  br i1 %18, label %19, label %21

19:                                               ; preds = %13
  %20 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.42)
  br label %21

21:                                               ; preds = %19, %13
  %22 = add nuw nsw i64 %14, 1
  %23 = icmp eq i64 %22, %9
  br i1 %23, label %10, label %13, !llvm.loop !21
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_array_float(ptr noundef readonly captures(none) %0, i32 noundef %1) local_unnamed_addr #6 {
  %3 = load ptr, ptr @stdout, align 8, !tbaa !10
  %4 = tail call noundef i32 @putc(i32 noundef 91, ptr noundef %3)
  %5 = icmp sgt i32 %1, 0
  br i1 %5, label %6, label %10

6:                                                ; preds = %2
  %7 = add nsw i32 %1, -1
  %8 = zext nneg i32 %7 to i64
  %9 = zext nneg i32 %1 to i64
  br label %13

10:                                               ; preds = %22, %2
  %11 = load ptr, ptr @stdout, align 8, !tbaa !10
  %12 = tail call noundef i32 @putc(i32 noundef 93, ptr noundef %11)
  ret void

13:                                               ; preds = %22, %6
  %14 = phi i64 [ 0, %6 ], [ %23, %22 ]
  %15 = getelementptr inbounds nuw float, ptr %0, i64 %14
  %16 = load float, ptr %15, align 4, !tbaa !22
  %17 = fpext float %16 to double
  %18 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, double noundef %17)
  %19 = icmp samesign ult i64 %14, %8
  br i1 %19, label %20, label %22

20:                                               ; preds = %13
  %21 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.42)
  br label %22

22:                                               ; preds = %20, %13
  %23 = add nuw nsw i64 %14, 1
  %24 = icmp eq i64 %23, %9
  br i1 %24, label %10, label %13, !llvm.loop !24
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_array_double(ptr noundef readonly captures(none) %0, i32 noundef %1) local_unnamed_addr #6 {
  %3 = load ptr, ptr @stdout, align 8, !tbaa !10
  %4 = tail call noundef i32 @putc(i32 noundef 91, ptr noundef %3)
  %5 = icmp sgt i32 %1, 0
  br i1 %5, label %6, label %10

6:                                                ; preds = %2
  %7 = add nsw i32 %1, -1
  %8 = zext nneg i32 %7 to i64
  %9 = zext nneg i32 %1 to i64
  br label %13

10:                                               ; preds = %21, %2
  %11 = load ptr, ptr @stdout, align 8, !tbaa !10
  %12 = tail call noundef i32 @putc(i32 noundef 93, ptr noundef %11)
  ret void

13:                                               ; preds = %21, %6
  %14 = phi i64 [ 0, %6 ], [ %22, %21 ]
  %15 = getelementptr inbounds nuw double, ptr %0, i64 %14
  %16 = load double, ptr %15, align 8, !tbaa !25
  %17 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, double noundef %16)
  %18 = icmp samesign ult i64 %14, %8
  br i1 %18, label %19, label %21

19:                                               ; preds = %13
  %20 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.42)
  br label %21

21:                                               ; preds = %19, %13
  %22 = add nuw nsw i64 %14, 1
  %23 = icmp eq i64 %22, %9
  br i1 %23, label %10, label %13, !llvm.loop !27
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_array_string(ptr noundef readonly captures(none) %0, i32 noundef %1) local_unnamed_addr #6 {
  %3 = load ptr, ptr @stdout, align 8, !tbaa !10
  %4 = tail call noundef i32 @putc(i32 noundef 91, ptr noundef %3)
  %5 = icmp sgt i32 %1, 0
  br i1 %5, label %6, label %10

6:                                                ; preds = %2
  %7 = add nsw i32 %1, -1
  %8 = zext nneg i32 %7 to i64
  %9 = zext nneg i32 %1 to i64
  br label %13

10:                                               ; preds = %21, %2
  %11 = load ptr, ptr @stdout, align 8, !tbaa !10
  %12 = tail call noundef i32 @putc(i32 noundef 93, ptr noundef %11)
  ret void

13:                                               ; preds = %21, %6
  %14 = phi i64 [ 0, %6 ], [ %22, %21 ]
  %15 = getelementptr inbounds nuw ptr, ptr %0, i64 %14
  %16 = load ptr, ptr %15, align 8, !tbaa !28
  %17 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.44, ptr noundef %16)
  %18 = icmp samesign ult i64 %14, %8
  br i1 %18, label %19, label %21

19:                                               ; preds = %13
  %20 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.42)
  br label %21

21:                                               ; preds = %19, %13
  %22 = add nuw nsw i64 %14, 1
  %23 = icmp eq i64 %22, %9
  br i1 %23, label %10, label %13, !llvm.loop !30
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_array_char(ptr noundef readonly captures(none) %0, i32 noundef %1) local_unnamed_addr #6 {
  %3 = load ptr, ptr @stdout, align 8, !tbaa !10
  %4 = tail call noundef i32 @putc(i32 noundef 91, ptr noundef %3)
  %5 = icmp sgt i32 %1, 0
  br i1 %5, label %6, label %10

6:                                                ; preds = %2
  %7 = add nsw i32 %1, -1
  %8 = zext nneg i32 %7 to i64
  %9 = zext nneg i32 %1 to i64
  br label %13

10:                                               ; preds = %22, %2
  %11 = load ptr, ptr @stdout, align 8, !tbaa !10
  %12 = tail call noundef i32 @putc(i32 noundef 93, ptr noundef %11)
  ret void

13:                                               ; preds = %22, %6
  %14 = phi i64 [ 0, %6 ], [ %23, %22 ]
  %15 = getelementptr inbounds nuw i8, ptr %0, i64 %14
  %16 = load i8, ptr %15, align 1, !tbaa !7
  %17 = sext i8 %16 to i32
  %18 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.45, i32 noundef %17)
  %19 = icmp samesign ult i64 %14, %8
  br i1 %19, label %20, label %22

20:                                               ; preds = %13
  %21 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.42)
  br label %22

22:                                               ; preds = %20, %13
  %23 = add nuw nsw i64 %14, 1
  %24 = icmp eq i64 %23, %9
  br i1 %24, label %10, label %13, !llvm.loop !31
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_array_bool(ptr noundef readonly captures(none) %0, i32 noundef %1) local_unnamed_addr #6 {
  %3 = load ptr, ptr @stdout, align 8, !tbaa !10
  %4 = tail call noundef i32 @putc(i32 noundef 91, ptr noundef %3)
  %5 = icmp sgt i32 %1, 0
  br i1 %5, label %6, label %10

6:                                                ; preds = %2
  %7 = add nsw i32 %1, -1
  %8 = zext nneg i32 %7 to i64
  %9 = zext nneg i32 %1 to i64
  br label %13

10:                                               ; preds = %23, %2
  %11 = load ptr, ptr @stdout, align 8, !tbaa !10
  %12 = tail call noundef i32 @putc(i32 noundef 93, ptr noundef %11)
  ret void

13:                                               ; preds = %23, %6
  %14 = phi i64 [ 0, %6 ], [ %24, %23 ]
  %15 = getelementptr inbounds nuw i8, ptr %0, i64 %14
  %16 = load i8, ptr %15, align 1, !tbaa !32, !range !34, !noundef !35
  %17 = trunc nuw i8 %16 to i1
  %18 = select i1 %17, ptr @.str.23, ptr @.str.24
  %19 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.38, ptr noundef nonnull %18)
  %20 = icmp samesign ult i64 %14, %8
  br i1 %20, label %21, label %23

21:                                               ; preds = %13
  %22 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.42)
  br label %23

23:                                               ; preds = %21, %13
  %24 = add nuw nsw i64 %14, 1
  %25 = icmp eq i64 %24, %9
  br i1 %25, label %10, label %13, !llvm.loop !36
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_array_qbool(ptr noundef readonly captures(none) %0, i32 noundef %1) local_unnamed_addr #6 {
  %3 = load ptr, ptr @stdout, align 8, !tbaa !10
  %4 = tail call noundef i32 @putc(i32 noundef 91, ptr noundef %3)
  %5 = icmp sgt i32 %1, 0
  br i1 %5, label %6, label %10

6:                                                ; preds = %2
  %7 = add nsw i32 %1, -1
  %8 = zext nneg i32 %7 to i64
  %9 = zext nneg i32 %1 to i64
  br label %13

10:                                               ; preds = %25, %2
  %11 = load ptr, ptr @stdout, align 8, !tbaa !10
  %12 = tail call noundef i32 @putc(i32 noundef 93, ptr noundef %11)
  ret void

13:                                               ; preds = %25, %6
  %14 = phi i64 [ 0, %6 ], [ %26, %25 ]
  %15 = getelementptr inbounds nuw i8, ptr %0, i64 %14
  %16 = load i8, ptr %15, align 1, !tbaa !7
  %17 = and i8 %16, 3
  %18 = zext nneg i8 %17 to i64
  %19 = getelementptr inbounds nuw [4 x ptr], ptr @switch.table.qc_print_array_qbool, i64 0, i64 %18
  %20 = load ptr, ptr %19, align 8
  %21 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) %20)
  %22 = icmp samesign ult i64 %14, %8
  br i1 %22, label %23, label %25

23:                                               ; preds = %13
  %24 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.42)
  br label %25

25:                                               ; preds = %23, %13
  %26 = add nuw nsw i64 %14, 1
  %27 = icmp eq i64 %26, %9
  br i1 %27, label %10, label %13, !llvm.loop !37
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local range(i32 1, 9) i32 @sizeof_type(i32 noundef %0) local_unnamed_addr #10 {
  %2 = add i32 %0, -2
  %3 = icmp ult i32 %2, 5
  br i1 %3, label %4, label %8

4:                                                ; preds = %1
  %5 = zext nneg i32 %2 to i64
  %6 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.stringify_jagged_helper, i64 0, i64 %5
  %7 = load i32, ptr %6, align 4
  br label %8

8:                                                ; preds = %4, %1
  %9 = phi i32 [ %7, %4 ], [ 4, %1 ]
  ret i32 %9
}

; Function Attrs: mustprogress nounwind uwtable
define dso_local noundef ptr @qc_array_to_string_recursive(ptr noundef readonly captures(none) %0, i32 noundef %1, i32 noundef %2, ptr noundef readonly captures(none) %3) local_unnamed_addr #17 {
  %5 = alloca [256 x i8], align 16
  %6 = icmp eq i32 %2, 0
  br i1 %6, label %7, label %45

7:                                                ; preds = %4
  call void @llvm.lifetime.start.p0(i64 256, ptr nonnull %5) #37
  switch i32 %1, label %40 [
    i32 0, label %8
    i32 1, label %11
    i32 2, label %15
    i32 3, label %18
    i32 4, label %22
    i32 5, label %27
    i32 6, label %37
  ]

8:                                                ; preds = %7
  %9 = load i32, ptr %0, align 4, !tbaa !19
  %10 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 256, ptr noundef nonnull @.str.33, i32 noundef %9) #37
  br label %40

11:                                               ; preds = %7
  %12 = load float, ptr %0, align 4, !tbaa !22
  %13 = fpext float %12 to double
  %14 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 256, ptr noundef nonnull @.str.34, double noundef %13) #37
  br label %40

15:                                               ; preds = %7
  %16 = load double, ptr %0, align 8, !tbaa !25
  %17 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 256, ptr noundef nonnull @.str.34, double noundef %16) #37
  br label %40

18:                                               ; preds = %7
  %19 = load i8, ptr %0, align 1, !tbaa !7
  %20 = sext i8 %19 to i32
  %21 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 256, ptr noundef nonnull @.str.45, i32 noundef %20) #37
  br label %40

22:                                               ; preds = %7
  %23 = load i8, ptr %0, align 1, !tbaa !32, !range !34, !noundef !35
  %24 = trunc nuw i8 %23 to i1
  %25 = select i1 %24, ptr @.str.23, ptr @.str.24
  %26 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 256, ptr noundef nonnull @.str.38, ptr noundef nonnull %25) #37
  br label %40

27:                                               ; preds = %7
  %28 = load i8, ptr %0, align 1, !tbaa !7
  %29 = and i8 %28, 3
  switch i8 %29, label %30 [
    i8 0, label %34
    i8 1, label %33
  ]

30:                                               ; preds = %27
  %31 = icmp eq i8 %29, 2
  %32 = select i1 %31, ptr @.str.27, ptr @.str.28
  br label %34

33:                                               ; preds = %27
  br label %34

34:                                               ; preds = %33, %30, %27
  %35 = phi ptr [ @.str.25, %27 ], [ %32, %30 ], [ @.str.26, %33 ]
  %36 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 256, ptr noundef nonnull @.str.38, ptr noundef nonnull %35) #37
  br label %40

37:                                               ; preds = %7
  %38 = load ptr, ptr %0, align 8, !tbaa !28
  %39 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 256, ptr noundef nonnull @.str.44, ptr noundef %38) #37
  br label %40

40:                                               ; preds = %37, %34, %22, %18, %15, %11, %8, %7
  %41 = call i64 @strlen(ptr noundef nonnull dereferenceable(1) %5) #40
  %42 = add i64 %41, 1
  %43 = tail call noalias ptr @malloc(i64 noundef %42) #36
  %44 = call ptr @strcpy(ptr noundef nonnull dereferenceable(1) %43, ptr noundef nonnull dereferenceable(1) %5) #37
  call void @llvm.lifetime.end.p0(i64 256, ptr nonnull %5) #37
  br label %157

45:                                               ; preds = %4
  %46 = add i32 %1, -2
  %47 = icmp ult i32 %46, 5
  br i1 %47, label %48, label %52

48:                                               ; preds = %45
  %49 = zext nneg i32 %46 to i64
  %50 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.stringify_jagged_helper, i64 0, i64 %49
  %51 = load i32, ptr %50, align 4
  br label %52

52:                                               ; preds = %48, %45
  %53 = phi i32 [ %51, %48 ], [ 4, %45 ]
  %54 = icmp sgt i32 %2, 1
  br i1 %54, label %55, label %83

55:                                               ; preds = %52
  %56 = zext nneg i32 %2 to i64
  %57 = add nsw i64 %56, -1
  %58 = icmp ult i32 %2, 9
  br i1 %58, label %80, label %59

59:                                               ; preds = %55
  %60 = and i64 %57, -8
  %61 = or disjoint i64 %60, 1
  %62 = insertelement <4 x i32> <i32 poison, i32 1, i32 1, i32 1>, i32 %53, i64 0
  br label %63

63:                                               ; preds = %63, %59
  %64 = phi i64 [ 0, %59 ], [ %74, %63 ]
  %65 = phi <4 x i32> [ %62, %59 ], [ %72, %63 ]
  %66 = phi <4 x i32> [ splat (i32 1), %59 ], [ %73, %63 ]
  %67 = getelementptr inbounds nuw i32, ptr %3, i64 %64
  %68 = getelementptr inbounds nuw i8, ptr %67, i64 4
  %69 = getelementptr inbounds nuw i8, ptr %67, i64 20
  %70 = load <4 x i32>, ptr %68, align 4, !tbaa !19
  %71 = load <4 x i32>, ptr %69, align 4, !tbaa !19
  %72 = mul <4 x i32> %70, %65
  %73 = mul <4 x i32> %71, %66
  %74 = add nuw i64 %64, 8
  %75 = icmp eq i64 %74, %60
  br i1 %75, label %76, label %63, !llvm.loop !38

76:                                               ; preds = %63
  %77 = mul <4 x i32> %73, %72
  %78 = tail call i32 @llvm.vector.reduce.mul.v4i32(<4 x i32> %77)
  %79 = icmp eq i64 %57, %60
  br i1 %79, label %83, label %80

80:                                               ; preds = %76, %55
  %81 = phi i64 [ 1, %55 ], [ %61, %76 ]
  %82 = phi i32 [ %53, %55 ], [ %78, %76 ]
  br label %97

83:                                               ; preds = %97, %76, %52
  %84 = phi i32 [ %53, %52 ], [ %78, %76 ], [ %102, %97 ]
  %85 = load i32, ptr %3, align 4, !tbaa !19
  %86 = sext i32 %85 to i64
  %87 = shl nsw i64 %86, 3
  %88 = tail call noalias ptr @malloc(i64 noundef %87) #36
  %89 = icmp sgt i32 %85, 0
  br i1 %89, label %93, label %90

90:                                               ; preds = %83
  %91 = tail call noalias dereferenceable_or_null(3) ptr @malloc(i64 noundef 3) #36
  %92 = getelementptr inbounds nuw i8, ptr %91, i64 1
  store i8 91, ptr %91, align 1, !tbaa !7
  br label %130

93:                                               ; preds = %83
  %94 = add nsw i32 %2, -1
  %95 = getelementptr inbounds nuw i8, ptr %3, i64 4
  %96 = sext i32 %84 to i64
  br label %111

97:                                               ; preds = %97, %80
  %98 = phi i64 [ %103, %97 ], [ %81, %80 ]
  %99 = phi i32 [ %102, %97 ], [ %82, %80 ]
  %100 = getelementptr inbounds nuw i32, ptr %3, i64 %98
  %101 = load i32, ptr %100, align 4, !tbaa !19
  %102 = mul nsw i32 %101, %99
  %103 = add nuw nsw i64 %98, 1
  %104 = icmp eq i64 %103, %56
  br i1 %104, label %83, label %97, !llvm.loop !41

105:                                              ; preds = %111
  %106 = add nsw i32 %126, 1
  %107 = sext i32 %106 to i64
  %108 = icmp sgt i32 %121, 0
  %109 = tail call noalias ptr @malloc(i64 noundef %107) #36
  %110 = getelementptr inbounds nuw i8, ptr %109, i64 1
  store i8 91, ptr %109, align 1, !tbaa !7
  br i1 %108, label %134, label %130

111:                                              ; preds = %111, %93
  %112 = phi i64 [ 0, %93 ], [ %127, %111 ]
  %113 = phi i32 [ 2, %93 ], [ %126, %111 ]
  %114 = mul nsw i64 %112, %96
  %115 = getelementptr inbounds i8, ptr %0, i64 %114
  %116 = tail call ptr @qc_array_to_string_recursive(ptr noundef %115, i32 noundef %1, i32 noundef %94, ptr noundef nonnull %95)
  %117 = getelementptr inbounds nuw ptr, ptr %88, i64 %112
  store ptr %116, ptr %117, align 8, !tbaa !28
  %118 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %116) #40
  %119 = trunc i64 %118 to i32
  %120 = add i32 %113, %119
  %121 = load i32, ptr %3, align 4, !tbaa !19
  %122 = add nsw i32 %121, -1
  %123 = sext i32 %122 to i64
  %124 = icmp slt i64 %112, %123
  %125 = add nsw i32 %120, 2
  %126 = select i1 %124, i32 %125, i32 %120
  %127 = add nuw nsw i64 %112, 1
  %128 = sext i32 %121 to i64
  %129 = icmp slt i64 %127, %128
  br i1 %129, label %111, label %105, !llvm.loop !42

130:                                              ; preds = %151, %105, %90
  %131 = phi ptr [ %109, %105 ], [ %91, %90 ], [ %109, %151 ]
  %132 = phi ptr [ %110, %105 ], [ %92, %90 ], [ %153, %151 ]
  %133 = getelementptr inbounds nuw i8, ptr %132, i64 1
  store i8 93, ptr %132, align 1, !tbaa !7
  store i8 0, ptr %133, align 1, !tbaa !7
  tail call void @free(ptr noundef %88) #37
  br label %157

134:                                              ; preds = %151, %105
  %135 = phi i64 [ %154, %151 ], [ 0, %105 ]
  %136 = phi ptr [ %153, %151 ], [ %110, %105 ]
  %137 = getelementptr inbounds nuw ptr, ptr %88, i64 %135
  %138 = load ptr, ptr %137, align 8, !tbaa !28
  %139 = tail call ptr @strcpy(ptr noundef nonnull dereferenceable(1) %136, ptr noundef nonnull dereferenceable(1) %138) #37
  %140 = load ptr, ptr %137, align 8, !tbaa !28
  %141 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %140) #40
  %142 = getelementptr inbounds nuw i8, ptr %136, i64 %141
  tail call void @free(ptr noundef %140) #37
  %143 = load i32, ptr %3, align 4, !tbaa !19
  %144 = add nsw i32 %143, -1
  %145 = sext i32 %144 to i64
  %146 = icmp slt i64 %135, %145
  br i1 %146, label %147, label %151

147:                                              ; preds = %134
  %148 = getelementptr inbounds nuw i8, ptr %142, i64 1
  store i8 44, ptr %142, align 1, !tbaa !7
  %149 = getelementptr inbounds nuw i8, ptr %142, i64 2
  store i8 32, ptr %148, align 1, !tbaa !7
  %150 = load i32, ptr %3, align 4, !tbaa !19
  br label %151

151:                                              ; preds = %147, %134
  %152 = phi i32 [ %150, %147 ], [ %143, %134 ]
  %153 = phi ptr [ %149, %147 ], [ %142, %134 ]
  %154 = add nuw nsw i64 %135, 1
  %155 = sext i32 %152 to i64
  %156 = icmp slt i64 %154, %155
  br i1 %156, label %134, label %130, !llvm.loop !43

157:                                              ; preds = %130, %40
  %158 = phi ptr [ %43, %40 ], [ %131, %130 ]
  ret ptr %158
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.vector.reduce.mul.v4i32(<4 x i32>) #28

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_array_recursive(ptr noundef readonly captures(none) %0, i32 noundef %1, i32 noundef %2, ptr noundef readonly captures(none) %3) local_unnamed_addr #6 {
  %5 = icmp eq i32 %2, 0
  br i1 %5, label %6, label %41

6:                                                ; preds = %4
  switch i32 %1, label %116 [
    i32 0, label %7
    i32 1, label %10
    i32 2, label %14
    i32 3, label %17
    i32 4, label %21
    i32 5, label %26
    i32 6, label %38
  ]

7:                                                ; preds = %6
  %8 = load i32, ptr %0, align 4, !tbaa !19
  %9 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.33, i32 noundef %8)
  br label %116

10:                                               ; preds = %6
  %11 = load float, ptr %0, align 4, !tbaa !22
  %12 = fpext float %11 to double
  %13 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, double noundef %12)
  br label %116

14:                                               ; preds = %6
  %15 = load double, ptr %0, align 8, !tbaa !25
  %16 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, double noundef %15)
  br label %116

17:                                               ; preds = %6
  %18 = load i8, ptr %0, align 1, !tbaa !7
  %19 = sext i8 %18 to i32
  %20 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.45, i32 noundef %19)
  br label %116

21:                                               ; preds = %6
  %22 = load i8, ptr %0, align 1, !tbaa !32, !range !34, !noundef !35
  %23 = trunc nuw i8 %22 to i1
  %24 = select i1 %23, ptr @.str.23, ptr @.str.24
  %25 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.38, ptr noundef nonnull %24)
  br label %116

26:                                               ; preds = %6
  %27 = load i8, ptr %0, align 1, !tbaa !7
  %28 = and i8 %27, 3
  switch i8 %28, label %37 [
    i8 0, label %29
    i8 1, label %31
    i8 2, label %33
    i8 3, label %35
  ]

29:                                               ; preds = %26
  %30 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.25)
  br label %116

31:                                               ; preds = %26
  %32 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.26)
  br label %116

33:                                               ; preds = %26
  %34 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.27)
  br label %116

35:                                               ; preds = %26
  %36 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.28)
  br label %116

37:                                               ; preds = %26
  unreachable

38:                                               ; preds = %6
  %39 = load ptr, ptr %0, align 8, !tbaa !28
  %40 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.44, ptr noundef %39)
  br label %116

41:                                               ; preds = %4
  %42 = load ptr, ptr @stdout, align 8, !tbaa !10
  %43 = tail call noundef i32 @putc(i32 noundef 91, ptr noundef %42)
  %44 = add i32 %1, -2
  %45 = icmp ult i32 %44, 5
  br i1 %45, label %46, label %50

46:                                               ; preds = %41
  %47 = zext nneg i32 %44 to i64
  %48 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.stringify_jagged_helper, i64 0, i64 %47
  %49 = load i32, ptr %48, align 4
  br label %50

50:                                               ; preds = %46, %41
  %51 = phi i32 [ %49, %46 ], [ 4, %41 ]
  %52 = icmp sgt i32 %2, 1
  br i1 %52, label %53, label %81

53:                                               ; preds = %50
  %54 = zext nneg i32 %2 to i64
  %55 = add nsw i64 %54, -1
  %56 = icmp ult i32 %2, 9
  br i1 %56, label %78, label %57

57:                                               ; preds = %53
  %58 = and i64 %55, -8
  %59 = or disjoint i64 %58, 1
  %60 = insertelement <4 x i32> <i32 poison, i32 1, i32 1, i32 1>, i32 %51, i64 0
  br label %61

61:                                               ; preds = %61, %57
  %62 = phi i64 [ 0, %57 ], [ %72, %61 ]
  %63 = phi <4 x i32> [ %60, %57 ], [ %70, %61 ]
  %64 = phi <4 x i32> [ splat (i32 1), %57 ], [ %71, %61 ]
  %65 = getelementptr inbounds nuw i32, ptr %3, i64 %62
  %66 = getelementptr inbounds nuw i8, ptr %65, i64 4
  %67 = getelementptr inbounds nuw i8, ptr %65, i64 20
  %68 = load <4 x i32>, ptr %66, align 4, !tbaa !19
  %69 = load <4 x i32>, ptr %67, align 4, !tbaa !19
  %70 = mul <4 x i32> %68, %63
  %71 = mul <4 x i32> %69, %64
  %72 = add nuw i64 %62, 8
  %73 = icmp eq i64 %72, %58
  br i1 %73, label %74, label %61, !llvm.loop !44

74:                                               ; preds = %61
  %75 = mul <4 x i32> %71, %70
  %76 = tail call i32 @llvm.vector.reduce.mul.v4i32(<4 x i32> %75)
  %77 = icmp eq i64 %55, %58
  br i1 %77, label %81, label %78

78:                                               ; preds = %74, %53
  %79 = phi i64 [ 1, %53 ], [ %59, %74 ]
  %80 = phi i32 [ %51, %53 ], [ %76, %74 ]
  br label %89

81:                                               ; preds = %89, %74, %50
  %82 = phi i32 [ %51, %50 ], [ %76, %74 ], [ %94, %89 ]
  %83 = load i32, ptr %3, align 4, !tbaa !19
  %84 = icmp sgt i32 %83, 0
  br i1 %84, label %85, label %97

85:                                               ; preds = %81
  %86 = add nsw i32 %2, -1
  %87 = getelementptr inbounds nuw i8, ptr %3, i64 4
  %88 = sext i32 %82 to i64
  br label %100

89:                                               ; preds = %89, %78
  %90 = phi i64 [ %95, %89 ], [ %79, %78 ]
  %91 = phi i32 [ %94, %89 ], [ %80, %78 ]
  %92 = getelementptr inbounds nuw i32, ptr %3, i64 %90
  %93 = load i32, ptr %92, align 4, !tbaa !19
  %94 = mul nsw i32 %93, %91
  %95 = add nuw nsw i64 %90, 1
  %96 = icmp eq i64 %95, %54
  br i1 %96, label %81, label %89, !llvm.loop !45

97:                                               ; preds = %111, %81
  %98 = load ptr, ptr @stdout, align 8, !tbaa !10
  %99 = tail call noundef i32 @putc(i32 noundef 93, ptr noundef %98)
  br label %116

100:                                              ; preds = %111, %85
  %101 = phi i64 [ 0, %85 ], [ %113, %111 ]
  %102 = mul nsw i64 %101, %88
  %103 = getelementptr inbounds i8, ptr %0, i64 %102
  tail call void @qc_print_array_recursive(ptr noundef %103, i32 noundef %1, i32 noundef %86, ptr noundef nonnull %87)
  %104 = load i32, ptr %3, align 4, !tbaa !19
  %105 = add nsw i32 %104, -1
  %106 = sext i32 %105 to i64
  %107 = icmp slt i64 %101, %106
  br i1 %107, label %108, label %111

108:                                              ; preds = %100
  %109 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.42)
  %110 = load i32, ptr %3, align 4, !tbaa !19
  br label %111

111:                                              ; preds = %108, %100
  %112 = phi i32 [ %110, %108 ], [ %104, %100 ]
  %113 = add nuw nsw i64 %101, 1
  %114 = sext i32 %112 to i64
  %115 = icmp slt i64 %113, %114
  br i1 %115, label %100, label %97, !llvm.loop !46

116:                                              ; preds = %97, %38, %35, %33, %31, %29, %21, %17, %14, %10, %7, %6
  ret void
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(write, argmem: none, inaccessiblemem: readwrite) uwtable
define dso_local noalias noundef ptr @qc_create_jagged_array(i32 noundef %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #16 {
  %4 = tail call noalias dereferenceable_or_null(32) ptr @malloc(i64 noundef 32) #36
  %5 = sext i32 %0 to i64
  %6 = shl nsw i64 %5, 3
  %7 = tail call noalias ptr @malloc(i64 noundef %6) #36
  store ptr %7, ptr %4, align 8, !tbaa !47
  %8 = shl nsw i64 %5, 2
  %9 = tail call noalias ptr @malloc(i64 noundef %8) #36
  %10 = getelementptr inbounds nuw i8, ptr %4, i64 8
  store ptr %9, ptr %10, align 8, !tbaa !51
  %11 = getelementptr inbounds nuw i8, ptr %4, i64 16
  store i32 %0, ptr %11, align 8, !tbaa !52
  %12 = getelementptr inbounds nuw i8, ptr %4, i64 20
  store i32 %1, ptr %12, align 4, !tbaa !53
  %13 = getelementptr inbounds nuw i8, ptr %4, i64 24
  store i32 %2, ptr %13, align 8, !tbaa !54
  ret ptr %4
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(write, argmem: readwrite, inaccessiblemem: none) uwtable
define dso_local void @qc_set_jagged_element(ptr noundef readonly captures(none) %0, i32 noundef %1, ptr noundef %2, i32 noundef %3) local_unnamed_addr #29 {
  %5 = load ptr, ptr %0, align 8, !tbaa !47
  %6 = sext i32 %1 to i64
  %7 = getelementptr inbounds ptr, ptr %5, i64 %6
  store ptr %2, ptr %7, align 8, !tbaa !55
  %8 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %9 = load ptr, ptr %8, align 8, !tbaa !51
  %10 = getelementptr inbounds i32, ptr %9, i64 %6
  store i32 %3, ptr %10, align 4, !tbaa !19
  ret void
}

; Function Attrs: mustprogress nounwind uwtable
define dso_local void @qc_free_jagged_array(ptr noundef captures(none) %0) local_unnamed_addr #17 {
  %2 = getelementptr inbounds nuw i8, ptr %0, i64 24
  %3 = load i32, ptr %2, align 8, !tbaa !54
  %4 = icmp sgt i32 %3, 0
  %5 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %6 = load i32, ptr %5, align 8, !tbaa !52
  %7 = icmp sgt i32 %6, 0
  br i1 %4, label %9, label %8

8:                                                ; preds = %1
  br i1 %7, label %19, label %28

9:                                                ; preds = %1
  br i1 %7, label %10, label %28

10:                                               ; preds = %10, %9
  %11 = phi i64 [ %15, %10 ], [ 0, %9 ]
  %12 = load ptr, ptr %0, align 8, !tbaa !47
  %13 = getelementptr inbounds nuw ptr, ptr %12, i64 %11
  %14 = load ptr, ptr %13, align 8, !tbaa !55
  tail call void @qc_free_jagged_array(ptr noundef %14)
  %15 = add nuw nsw i64 %11, 1
  %16 = load i32, ptr %5, align 8, !tbaa !52
  %17 = sext i32 %16 to i64
  %18 = icmp slt i64 %15, %17
  br i1 %18, label %10, label %28, !llvm.loop !56

19:                                               ; preds = %19, %8
  %20 = phi i64 [ %24, %19 ], [ 0, %8 ]
  %21 = load ptr, ptr %0, align 8, !tbaa !47
  %22 = getelementptr inbounds nuw ptr, ptr %21, i64 %20
  %23 = load ptr, ptr %22, align 8, !tbaa !55
  tail call void @free(ptr noundef %23) #37
  %24 = add nuw nsw i64 %20, 1
  %25 = load i32, ptr %5, align 8, !tbaa !52
  %26 = sext i32 %25 to i64
  %27 = icmp slt i64 %24, %26
  br i1 %27, label %19, label %28, !llvm.loop !57

28:                                               ; preds = %19, %10, %9, %8
  %29 = load ptr, ptr %0, align 8, !tbaa !47
  tail call void @free(ptr noundef %29) #37
  %30 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %31 = load ptr, ptr %30, align 8, !tbaa !51
  tail call void @free(ptr noundef %31) #37
  tail call void @free(ptr noundef nonnull %0) #37
  ret void
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_jagged_array_recursive(ptr noundef readonly captures(none) %0) local_unnamed_addr #6 {
  %2 = load ptr, ptr @stdout, align 8, !tbaa !10
  %3 = tail call noundef i32 @putc(i32 noundef 91, ptr noundef %2)
  %4 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %5 = load i32, ptr %4, align 8, !tbaa !52
  %6 = icmp sgt i32 %5, 0
  br i1 %6, label %7, label %11

7:                                                ; preds = %1
  %8 = getelementptr inbounds nuw i8, ptr %0, i64 24
  %9 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %10 = getelementptr inbounds nuw i8, ptr %0, i64 20
  br label %14

11:                                               ; preds = %108, %1
  %12 = load ptr, ptr @stdout, align 8, !tbaa !10
  %13 = tail call noundef i32 @putc(i32 noundef 93, ptr noundef %12)
  ret void

14:                                               ; preds = %108, %7
  %15 = phi i64 [ 0, %7 ], [ %110, %108 ]
  %16 = load i32, ptr %8, align 8, !tbaa !54
  %17 = icmp sgt i32 %16, 1
  br i1 %17, label %18, label %22

18:                                               ; preds = %14
  %19 = load ptr, ptr %0, align 8, !tbaa !47
  %20 = getelementptr inbounds nuw ptr, ptr %19, i64 %15
  %21 = load ptr, ptr %20, align 8, !tbaa !55
  tail call void @qc_print_jagged_array_recursive(ptr noundef %21)
  br label %100

22:                                               ; preds = %14
  %23 = icmp eq i32 %16, 1
  br i1 %23, label %24, label %98

24:                                               ; preds = %22
  %25 = load ptr, ptr %0, align 8, !tbaa !47
  %26 = getelementptr inbounds nuw ptr, ptr %25, i64 %15
  %27 = load ptr, ptr %26, align 8, !tbaa !55
  %28 = load ptr, ptr @stdout, align 8, !tbaa !10
  %29 = tail call noundef i32 @putc(i32 noundef 91, ptr noundef %28)
  %30 = load ptr, ptr %9, align 8, !tbaa !51
  %31 = getelementptr inbounds nuw i32, ptr %30, i64 %15
  %32 = load i32, ptr %31, align 4, !tbaa !19
  %33 = icmp sgt i32 %32, 0
  br i1 %33, label %37, label %34

34:                                               ; preds = %94, %24
  %35 = load ptr, ptr @stdout, align 8, !tbaa !10
  %36 = tail call noundef i32 @putc(i32 noundef 93, ptr noundef %35)
  br label %100

37:                                               ; preds = %94, %24
  %38 = phi i32 [ %96, %94 ], [ 0, %24 ]
  %39 = load i32, ptr %10, align 4, !tbaa !53
  %40 = add i32 %39, -2
  %41 = icmp ult i32 %40, 5
  br i1 %41, label %42, label %46

42:                                               ; preds = %37
  %43 = zext nneg i32 %40 to i64
  %44 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.stringify_jagged_helper, i64 0, i64 %43
  %45 = load i32, ptr %44, align 4
  br label %46

46:                                               ; preds = %42, %37
  %47 = phi i32 [ %45, %42 ], [ 4, %37 ]
  %48 = mul nuw nsw i32 %47, %38
  %49 = zext nneg i32 %48 to i64
  %50 = getelementptr inbounds nuw i8, ptr %27, i64 %49
  switch i32 %39, label %83 [
    i32 0, label %51
    i32 1, label %54
    i32 2, label %58
    i32 3, label %61
    i32 4, label %65
    i32 5, label %70
    i32 6, label %80
  ]

51:                                               ; preds = %46
  %52 = load i32, ptr %50, align 4, !tbaa !19
  %53 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.33, i32 noundef %52)
  br label %83

54:                                               ; preds = %46
  %55 = load float, ptr %50, align 4, !tbaa !22
  %56 = fpext float %55 to double
  %57 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, double noundef %56)
  br label %83

58:                                               ; preds = %46
  %59 = load double, ptr %50, align 8, !tbaa !25
  %60 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, double noundef %59)
  br label %83

61:                                               ; preds = %46
  %62 = load i8, ptr %50, align 1, !tbaa !7
  %63 = sext i8 %62 to i32
  %64 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.45, i32 noundef %63)
  br label %83

65:                                               ; preds = %46
  %66 = load i8, ptr %50, align 1, !tbaa !32, !range !34, !noundef !35
  %67 = trunc nuw i8 %66 to i1
  %68 = select i1 %67, ptr @.str.23, ptr @.str.24
  %69 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.38, ptr noundef nonnull %68)
  br label %83

70:                                               ; preds = %46
  %71 = load i8, ptr %50, align 1, !tbaa !7
  %72 = and i8 %71, 3
  switch i8 %72, label %73 [
    i8 0, label %77
    i8 1, label %76
  ]

73:                                               ; preds = %70
  %74 = icmp eq i8 %72, 2
  %75 = select i1 %74, ptr @.str.27, ptr @.str.28
  br label %77

76:                                               ; preds = %70
  br label %77

77:                                               ; preds = %76, %73, %70
  %78 = phi ptr [ @.str.25, %70 ], [ %75, %73 ], [ @.str.26, %76 ]
  %79 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.38, ptr noundef nonnull %78)
  br label %83

80:                                               ; preds = %46
  %81 = load ptr, ptr %50, align 8, !tbaa !28
  %82 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.44, ptr noundef %81)
  br label %83

83:                                               ; preds = %80, %77, %65, %61, %58, %54, %51, %46
  %84 = load ptr, ptr %9, align 8, !tbaa !51
  %85 = getelementptr inbounds nuw i32, ptr %84, i64 %15
  %86 = load i32, ptr %85, align 4, !tbaa !19
  %87 = add nsw i32 %86, -1
  %88 = icmp slt i32 %38, %87
  br i1 %88, label %89, label %94

89:                                               ; preds = %83
  %90 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.42)
  %91 = load ptr, ptr %9, align 8, !tbaa !51
  %92 = getelementptr inbounds nuw i32, ptr %91, i64 %15
  %93 = load i32, ptr %92, align 4, !tbaa !19
  br label %94

94:                                               ; preds = %89, %83
  %95 = phi i32 [ %93, %89 ], [ %86, %83 ]
  %96 = add nuw nsw i32 %38, 1
  %97 = icmp slt i32 %96, %95
  br i1 %97, label %37, label %34, !llvm.loop !58

98:                                               ; preds = %22
  %99 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.46)
  br label %100

100:                                              ; preds = %98, %34, %18
  %101 = load i32, ptr %4, align 8, !tbaa !52
  %102 = add nsw i32 %101, -1
  %103 = sext i32 %102 to i64
  %104 = icmp slt i64 %15, %103
  br i1 %104, label %105, label %108

105:                                              ; preds = %100
  %106 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.42)
  %107 = load i32, ptr %4, align 8, !tbaa !52
  br label %108

108:                                              ; preds = %105, %100
  %109 = phi i32 [ %101, %100 ], [ %107, %105 ]
  %110 = add nuw nsw i64 %15, 1
  %111 = sext i32 %109 to i64
  %112 = icmp slt i64 %110, %111
  br i1 %112, label %14, label %11, !llvm.loop !59
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(read, inaccessiblemem: none) uwtable
define dso_local ptr @qc_jagged_array_get(ptr noundef readonly captures(address_is_null) %0, ptr noundef readonly captures(none) %1, i32 noundef %2) local_unnamed_addr #30 {
  %4 = icmp ne i32 %2, 0
  %5 = icmp ne ptr %0, null
  %6 = and i1 %5, %4
  br i1 %6, label %7, label %95

7:                                                ; preds = %85, %3
  %8 = phi i32 [ %92, %85 ], [ %2, %3 ]
  %9 = phi ptr [ %91, %85 ], [ %1, %3 ]
  %10 = phi ptr [ %89, %85 ], [ %0, %3 ]
  %11 = load i32, ptr %9, align 4, !tbaa !19
  %12 = icmp slt i32 %11, 0
  br i1 %12, label %95, label %13

13:                                               ; preds = %7
  %14 = getelementptr inbounds nuw i8, ptr %10, i64 16
  %15 = load i32, ptr %14, align 8, !tbaa !52
  %16 = icmp slt i32 %11, %15
  br i1 %16, label %17, label %95

17:                                               ; preds = %13
  %18 = getelementptr inbounds nuw i8, ptr %10, i64 24
  %19 = load i32, ptr %18, align 8, !tbaa !54
  switch i32 %19, label %85 [
    i32 0, label %20
    i32 1, label %55
  ]

20:                                               ; preds = %17
  %21 = icmp eq i32 %8, 1
  br i1 %21, label %22, label %27

22:                                               ; preds = %20
  %23 = load ptr, ptr %10, align 8, !tbaa !47
  %24 = zext nneg i32 %11 to i64
  %25 = getelementptr inbounds nuw ptr, ptr %23, i64 %24
  %26 = load ptr, ptr %25, align 8, !tbaa !55
  br label %95

27:                                               ; preds = %20
  %28 = getelementptr inbounds nuw i8, ptr %9, i64 4
  %29 = load i32, ptr %28, align 4, !tbaa !19
  %30 = icmp slt i32 %29, 0
  br i1 %30, label %95, label %31

31:                                               ; preds = %27
  %32 = getelementptr inbounds nuw i8, ptr %10, i64 8
  %33 = load ptr, ptr %32, align 8, !tbaa !51
  %34 = zext nneg i32 %11 to i64
  %35 = getelementptr inbounds nuw i32, ptr %33, i64 %34
  %36 = load i32, ptr %35, align 4, !tbaa !19
  %37 = icmp slt i32 %29, %36
  br i1 %37, label %38, label %95

38:                                               ; preds = %31
  %39 = load ptr, ptr %10, align 8, !tbaa !47
  %40 = getelementptr inbounds nuw ptr, ptr %39, i64 %34
  %41 = load ptr, ptr %40, align 8, !tbaa !55
  %42 = getelementptr inbounds nuw i8, ptr %10, i64 20
  %43 = load i32, ptr %42, align 4, !tbaa !53
  %44 = add i32 %43, -2
  %45 = icmp ult i32 %44, 5
  br i1 %45, label %46, label %50

46:                                               ; preds = %38
  %47 = zext nneg i32 %44 to i64
  %48 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.stringify_jagged_helper, i64 0, i64 %47
  %49 = load i32, ptr %48, align 4
  br label %50

50:                                               ; preds = %46, %38
  %51 = phi i32 [ %49, %46 ], [ 4, %38 ]
  %52 = mul nuw nsw i32 %51, %29
  %53 = zext nneg i32 %52 to i64
  %54 = getelementptr inbounds nuw i8, ptr %41, i64 %53
  br label %95

55:                                               ; preds = %17
  %56 = load ptr, ptr %10, align 8, !tbaa !47
  %57 = zext nneg i32 %11 to i64
  %58 = getelementptr inbounds nuw ptr, ptr %56, i64 %57
  %59 = load ptr, ptr %58, align 8, !tbaa !55
  %60 = icmp eq i32 %8, 1
  br i1 %60, label %95, label %61

61:                                               ; preds = %55
  %62 = getelementptr inbounds nuw i8, ptr %9, i64 4
  %63 = load i32, ptr %62, align 4, !tbaa !19
  %64 = icmp slt i32 %63, 0
  br i1 %64, label %95, label %65

65:                                               ; preds = %61
  %66 = getelementptr inbounds nuw i8, ptr %10, i64 8
  %67 = load ptr, ptr %66, align 8, !tbaa !51
  %68 = getelementptr inbounds nuw i32, ptr %67, i64 %57
  %69 = load i32, ptr %68, align 4, !tbaa !19
  %70 = icmp slt i32 %63, %69
  br i1 %70, label %71, label %95

71:                                               ; preds = %65
  %72 = getelementptr inbounds nuw i8, ptr %10, i64 20
  %73 = load i32, ptr %72, align 4, !tbaa !53
  %74 = add i32 %73, -2
  %75 = icmp ult i32 %74, 5
  br i1 %75, label %76, label %80

76:                                               ; preds = %71
  %77 = zext nneg i32 %74 to i64
  %78 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.stringify_jagged_helper, i64 0, i64 %77
  %79 = load i32, ptr %78, align 4
  br label %80

80:                                               ; preds = %76, %71
  %81 = phi i32 [ %79, %76 ], [ 4, %71 ]
  %82 = mul nuw nsw i32 %81, %63
  %83 = zext nneg i32 %82 to i64
  %84 = getelementptr inbounds nuw i8, ptr %59, i64 %83
  br label %95

85:                                               ; preds = %17
  %86 = load ptr, ptr %10, align 8, !tbaa !47
  %87 = zext nneg i32 %11 to i64
  %88 = getelementptr inbounds nuw ptr, ptr %86, i64 %87
  %89 = load ptr, ptr %88, align 8, !tbaa !55
  %90 = icmp eq ptr %89, null
  %91 = getelementptr inbounds nuw i8, ptr %9, i64 4
  %92 = add nsw i32 %8, -1
  %93 = icmp eq i32 %92, 0
  %94 = select i1 %90, i1 true, i1 %93
  br i1 %94, label %95, label %7

95:                                               ; preds = %85, %80, %65, %61, %55, %50, %31, %27, %22, %13, %7, %3
  %96 = phi ptr [ %26, %22 ], [ %54, %50 ], [ null, %31 ], [ null, %27 ], [ %59, %55 ], [ %84, %80 ], [ null, %65 ], [ null, %61 ], [ null, %3 ], [ null, %13 ], [ null, %7 ], [ null, %85 ]
  ret ptr %96
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(inaccessiblemem: readwrite) uwtable
define dso_local noalias noundef ptr @qc_create_leaf_row(i32 noundef %0, i32 noundef %1) local_unnamed_addr #0 {
  %3 = add i32 %1, -2
  %4 = icmp ult i32 %3, 5
  br i1 %4, label %5, label %9

5:                                                ; preds = %2
  %6 = zext nneg i32 %3 to i64
  %7 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.stringify_jagged_helper, i64 0, i64 %6
  %8 = load i32, ptr %7, align 4
  br label %9

9:                                                ; preds = %5, %2
  %10 = phi i32 [ %8, %5 ], [ 4, %2 ]
  %11 = mul nsw i32 %10, %0
  %12 = sext i32 %11 to i64
  %13 = tail call noalias ptr @malloc(i64 noundef %12) #36
  ret ptr %13
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: readwrite) uwtable
define dso_local void @qc_set_leaf_element(ptr noundef writeonly captures(none) %0, i32 noundef %1, ptr noundef readonly captures(none) %2, i32 noundef %3) local_unnamed_addr #31 {
  %5 = add i32 %3, -2
  %6 = icmp ult i32 %5, 5
  br i1 %6, label %7, label %11

7:                                                ; preds = %4
  %8 = zext nneg i32 %5 to i64
  %9 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.stringify_jagged_helper, i64 0, i64 %8
  %10 = load i32, ptr %9, align 4
  br label %11

11:                                               ; preds = %7, %4
  %12 = phi i32 [ %10, %7 ], [ 4, %4 ]
  %13 = add i32 %3, -2
  %14 = icmp ult i32 %13, 5
  br i1 %14, label %15, label %19

15:                                               ; preds = %11
  %16 = zext nneg i32 %13 to i64
  %17 = getelementptr inbounds nuw [5 x i64], ptr @switch.table.qc_set_leaf_element.51, i64 0, i64 %16
  %18 = load i64, ptr %17, align 8
  br label %19

19:                                               ; preds = %15, %11
  %20 = phi i64 [ %18, %15 ], [ 4, %11 ]
  %21 = mul nsw i32 %12, %1
  %22 = sext i32 %21 to i64
  %23 = getelementptr inbounds i8, ptr %0, i64 %22
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %23, ptr noundef nonnull align 1 dereferenceable(1) %2, i64 %20, i1 false)
  ret void
}

; Function Attrs: mustprogress nounwind uwtable
define dso_local void @stringify_jagged_helper(ptr noundef readonly captures(none) %0, ptr noundef captures(none) %1, ptr noundef captures(none) %2, ptr noundef captures(none) %3, ptr noundef captures(none) %4) local_unnamed_addr #17 {
  %6 = alloca [64 x i8], align 16
  %7 = load ptr, ptr %1, align 8, !tbaa !28
  store i8 91, ptr %7, align 1, !tbaa !7
  %8 = load ptr, ptr %1, align 8, !tbaa !28
  %9 = getelementptr inbounds nuw i8, ptr %8, i64 1
  store ptr %9, ptr %1, align 8, !tbaa !28
  %10 = load i32, ptr %2, align 4, !tbaa !19
  %11 = add nsw i32 %10, -1
  store i32 %11, ptr %2, align 4, !tbaa !19
  %12 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %13 = load i32, ptr %12, align 8, !tbaa !52
  %14 = icmp sgt i32 %13, 0
  br i1 %14, label %15, label %21

15:                                               ; preds = %5
  %16 = getelementptr inbounds nuw i8, ptr %0, i64 24
  %17 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %18 = getelementptr inbounds nuw i8, ptr %0, i64 20
  br label %27

19:                                               ; preds = %165
  %20 = load ptr, ptr %1, align 8, !tbaa !28
  br label %21

21:                                               ; preds = %19, %5
  %22 = phi ptr [ %20, %19 ], [ %9, %5 ]
  store i8 93, ptr %22, align 1, !tbaa !7
  %23 = load ptr, ptr %1, align 8, !tbaa !28
  %24 = getelementptr inbounds nuw i8, ptr %23, i64 1
  store ptr %24, ptr %1, align 8, !tbaa !28
  %25 = load i32, ptr %2, align 4, !tbaa !19
  %26 = add nsw i32 %25, -1
  store i32 %26, ptr %2, align 4, !tbaa !19
  ret void

27:                                               ; preds = %165, %15
  %28 = phi i64 [ 0, %15 ], [ %167, %165 ]
  %29 = load i32, ptr %16, align 8, !tbaa !54
  %30 = icmp sgt i32 %29, 0
  br i1 %30, label %31, label %35

31:                                               ; preds = %27
  %32 = load ptr, ptr %0, align 8, !tbaa !47
  %33 = getelementptr inbounds nuw ptr, ptr %32, i64 %28
  %34 = load ptr, ptr %33, align 8, !tbaa !55
  tail call void @stringify_jagged_helper(ptr noundef %34, ptr noundef nonnull %1, ptr noundef nonnull %2, ptr noundef %3, ptr noundef %4)
  br label %151

35:                                               ; preds = %27
  %36 = load ptr, ptr %1, align 8, !tbaa !28
  store i8 91, ptr %36, align 1, !tbaa !7
  %37 = load ptr, ptr %1, align 8, !tbaa !28
  %38 = getelementptr inbounds nuw i8, ptr %37, i64 1
  store ptr %38, ptr %1, align 8, !tbaa !28
  %39 = load i32, ptr %2, align 4, !tbaa !19
  %40 = add nsw i32 %39, -1
  store i32 %40, ptr %2, align 4, !tbaa !19
  %41 = load ptr, ptr %0, align 8, !tbaa !47
  %42 = getelementptr inbounds nuw ptr, ptr %41, i64 %28
  %43 = load ptr, ptr %42, align 8, !tbaa !55
  %44 = load ptr, ptr %17, align 8, !tbaa !51
  %45 = getelementptr inbounds nuw i32, ptr %44, i64 %28
  %46 = load i32, ptr %45, align 4, !tbaa !19
  %47 = icmp sgt i32 %46, 0
  br i1 %47, label %54, label %48

48:                                               ; preds = %146, %35
  %49 = phi ptr [ %38, %35 ], [ %147, %146 ]
  store i8 93, ptr %49, align 1, !tbaa !7
  %50 = load ptr, ptr %1, align 8, !tbaa !28
  %51 = getelementptr inbounds nuw i8, ptr %50, i64 1
  store ptr %51, ptr %1, align 8, !tbaa !28
  %52 = load i32, ptr %2, align 4, !tbaa !19
  %53 = add nsw i32 %52, -1
  store i32 %53, ptr %2, align 4, !tbaa !19
  br label %151

54:                                               ; preds = %146, %35
  %55 = phi i32 [ %149, %146 ], [ 0, %35 ]
  %56 = load i32, ptr %18, align 4, !tbaa !53
  %57 = add i32 %56, -2
  %58 = icmp ult i32 %57, 5
  br i1 %58, label %59, label %63

59:                                               ; preds = %54
  %60 = zext nneg i32 %57 to i64
  %61 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.stringify_jagged_helper, i64 0, i64 %60
  %62 = load i32, ptr %61, align 4
  br label %63

63:                                               ; preds = %59, %54
  %64 = phi i32 [ %62, %59 ], [ 4, %54 ]
  %65 = mul nuw nsw i32 %64, %55
  %66 = zext nneg i32 %65 to i64
  %67 = getelementptr inbounds nuw i8, ptr %43, i64 %66
  call void @llvm.lifetime.start.p0(i64 64, ptr nonnull %6) #37
  switch i32 %56, label %100 [
    i32 0, label %68
    i32 1, label %71
    i32 2, label %75
    i32 3, label %78
    i32 4, label %82
    i32 5, label %87
    i32 6, label %97
  ]

68:                                               ; preds = %63
  %69 = load i32, ptr %67, align 4, !tbaa !19
  %70 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %6, i64 noundef 64, ptr noundef nonnull @.str.33, i32 noundef %69) #37
  br label %100

71:                                               ; preds = %63
  %72 = load float, ptr %67, align 4, !tbaa !22
  %73 = fpext float %72 to double
  %74 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %6, i64 noundef 64, ptr noundef nonnull @.str.34, double noundef %73) #37
  br label %100

75:                                               ; preds = %63
  %76 = load double, ptr %67, align 8, !tbaa !25
  %77 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %6, i64 noundef 64, ptr noundef nonnull @.str.34, double noundef %76) #37
  br label %100

78:                                               ; preds = %63
  %79 = load i8, ptr %67, align 1, !tbaa !7
  %80 = sext i8 %79 to i32
  %81 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %6, i64 noundef 64, ptr noundef nonnull @.str.45, i32 noundef %80) #37
  br label %100

82:                                               ; preds = %63
  %83 = load i8, ptr %67, align 1, !tbaa !32, !range !34, !noundef !35
  %84 = trunc nuw i8 %83 to i1
  %85 = select i1 %84, ptr @.str.23, ptr @.str.24
  %86 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %6, i64 noundef 64, ptr noundef nonnull @.str.38, ptr noundef nonnull %85) #37
  br label %100

87:                                               ; preds = %63
  %88 = load i8, ptr %67, align 1, !tbaa !7
  %89 = and i8 %88, 3
  switch i8 %89, label %90 [
    i8 0, label %94
    i8 1, label %93
  ]

90:                                               ; preds = %87
  %91 = icmp eq i8 %89, 2
  %92 = select i1 %91, ptr @.str.27, ptr @.str.28
  br label %94

93:                                               ; preds = %87
  br label %94

94:                                               ; preds = %93, %90, %87
  %95 = phi ptr [ @.str.25, %87 ], [ %92, %90 ], [ @.str.26, %93 ]
  %96 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %6, i64 noundef 64, ptr noundef nonnull @.str.38, ptr noundef nonnull %95) #37
  br label %100

97:                                               ; preds = %63
  %98 = load ptr, ptr %67, align 8, !tbaa !28
  %99 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %6, i64 noundef 64, ptr noundef nonnull @.str.44, ptr noundef %98) #37
  br label %100

100:                                              ; preds = %97, %94, %82, %78, %75, %71, %68, %63
  %101 = call i64 @strlen(ptr noundef nonnull dereferenceable(1) %6) #40
  %102 = trunc i64 %101 to i32
  %103 = load i32, ptr %2, align 4, !tbaa !19
  %104 = add nsw i32 %102, 10
  %105 = icmp slt i32 %103, %104
  %106 = load ptr, ptr %1, align 8, !tbaa !28
  br i1 %105, label %107, label %122

107:                                              ; preds = %100
  %108 = load ptr, ptr %4, align 8, !tbaa !28
  %109 = ptrtoint ptr %106 to i64
  %110 = ptrtoint ptr %108 to i64
  %111 = sub i64 %109, %110
  %112 = trunc i64 %111 to i32
  %113 = load i32, ptr %3, align 4, !tbaa !19
  %114 = shl nsw i32 %113, 1
  store i32 %114, ptr %3, align 4, !tbaa !19
  %115 = sext i32 %114 to i64
  %116 = tail call ptr @realloc(ptr noundef %108, i64 noundef %115) #38
  store ptr %116, ptr %4, align 8, !tbaa !28
  %117 = shl i64 %111, 32
  %118 = ashr exact i64 %117, 32
  %119 = getelementptr inbounds i8, ptr %116, i64 %118
  store ptr %119, ptr %1, align 8, !tbaa !28
  %120 = load i32, ptr %3, align 4, !tbaa !19
  %121 = sub nsw i32 %120, %112
  store i32 %121, ptr %2, align 4, !tbaa !19
  br label %122

122:                                              ; preds = %107, %100
  %123 = phi ptr [ %119, %107 ], [ %106, %100 ]
  %124 = call ptr @strcpy(ptr noundef nonnull dereferenceable(1) %123, ptr noundef nonnull dereferenceable(1) %6) #37
  %125 = load ptr, ptr %1, align 8, !tbaa !28
  %126 = shl i64 %101, 32
  %127 = ashr exact i64 %126, 32
  %128 = getelementptr inbounds i8, ptr %125, i64 %127
  store ptr %128, ptr %1, align 8, !tbaa !28
  %129 = load i32, ptr %2, align 4, !tbaa !19
  %130 = sub nsw i32 %129, %102
  store i32 %130, ptr %2, align 4, !tbaa !19
  %131 = load ptr, ptr %17, align 8, !tbaa !51
  %132 = getelementptr inbounds nuw i32, ptr %131, i64 %28
  %133 = load i32, ptr %132, align 4, !tbaa !19
  %134 = add nsw i32 %133, -1
  %135 = icmp slt i32 %55, %134
  br i1 %135, label %136, label %146

136:                                              ; preds = %122
  store i8 44, ptr %128, align 1, !tbaa !7
  %137 = load ptr, ptr %1, align 8, !tbaa !28
  %138 = getelementptr inbounds nuw i8, ptr %137, i64 1
  store ptr %138, ptr %1, align 8, !tbaa !28
  store i8 32, ptr %138, align 1, !tbaa !7
  %139 = load ptr, ptr %1, align 8, !tbaa !28
  %140 = getelementptr inbounds nuw i8, ptr %139, i64 1
  store ptr %140, ptr %1, align 8, !tbaa !28
  %141 = load i32, ptr %2, align 4, !tbaa !19
  %142 = add nsw i32 %141, -2
  store i32 %142, ptr %2, align 4, !tbaa !19
  %143 = load ptr, ptr %17, align 8, !tbaa !51
  %144 = getelementptr inbounds nuw i32, ptr %143, i64 %28
  %145 = load i32, ptr %144, align 4, !tbaa !19
  br label %146

146:                                              ; preds = %136, %122
  %147 = phi ptr [ %140, %136 ], [ %128, %122 ]
  %148 = phi i32 [ %145, %136 ], [ %133, %122 ]
  call void @llvm.lifetime.end.p0(i64 64, ptr nonnull %6) #37
  %149 = add nuw nsw i32 %55, 1
  %150 = icmp slt i32 %149, %148
  br i1 %150, label %54, label %48, !llvm.loop !60

151:                                              ; preds = %48, %31
  %152 = load i32, ptr %12, align 8, !tbaa !52
  %153 = add nsw i32 %152, -1
  %154 = sext i32 %153 to i64
  %155 = icmp slt i64 %28, %154
  br i1 %155, label %156, label %165

156:                                              ; preds = %151
  %157 = load ptr, ptr %1, align 8, !tbaa !28
  store i8 44, ptr %157, align 1, !tbaa !7
  %158 = load ptr, ptr %1, align 8, !tbaa !28
  %159 = getelementptr inbounds nuw i8, ptr %158, i64 1
  store ptr %159, ptr %1, align 8, !tbaa !28
  store i8 32, ptr %159, align 1, !tbaa !7
  %160 = load ptr, ptr %1, align 8, !tbaa !28
  %161 = getelementptr inbounds nuw i8, ptr %160, i64 1
  store ptr %161, ptr %1, align 8, !tbaa !28
  %162 = load i32, ptr %2, align 4, !tbaa !19
  %163 = add nsw i32 %162, -2
  store i32 %163, ptr %2, align 4, !tbaa !19
  %164 = load i32, ptr %12, align 8, !tbaa !52
  br label %165

165:                                              ; preds = %156, %151
  %166 = phi i32 [ %152, %151 ], [ %164, %156 ]
  %167 = add nuw nsw i64 %28, 1
  %168 = sext i32 %166 to i64
  %169 = icmp slt i64 %167, %168
  br i1 %169, label %27, label %19, !llvm.loop !61
}

; Function Attrs: mustprogress nounwind uwtable
define dso_local ptr @qc_jagged_to_string(ptr noundef readonly captures(none) %0) local_unnamed_addr #17 {
  %2 = alloca i32, align 4
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca i32, align 4
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %2) #37
  store i32 1024, ptr %2, align 4, !tbaa !19
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %3) #37
  %6 = tail call noalias dereferenceable_or_null(1024) ptr @malloc(i64 noundef 1024) #36
  store ptr %6, ptr %3, align 8, !tbaa !28
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %4) #37
  store ptr %6, ptr %4, align 8, !tbaa !28
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %5) #37
  store i32 1024, ptr %5, align 4, !tbaa !19
  call void @stringify_jagged_helper(ptr noundef %0, ptr noundef nonnull %4, ptr noundef nonnull %5, ptr noundef nonnull %2, ptr noundef nonnull %3)
  %7 = load ptr, ptr %4, align 8, !tbaa !28
  store i8 0, ptr %7, align 1, !tbaa !7
  %8 = load ptr, ptr %3, align 8, !tbaa !28
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %5) #37
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %4) #37
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %3) #37
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %2) #37
  ret ptr %8
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(write, argmem: none, inaccessiblemem: readwrite) uwtable
define dso_local noalias noundef ptr @qc_create_list(i32 noundef %0) local_unnamed_addr #16 {
  %2 = tail call noalias dereferenceable_or_null(24) ptr @malloc(i64 noundef 24) #36
  %3 = getelementptr inbounds nuw i8, ptr %2, i64 12
  store i32 4, ptr %3, align 4, !tbaa !62
  %4 = getelementptr inbounds nuw i8, ptr %2, i64 8
  store i32 0, ptr %4, align 8, !tbaa !64
  %5 = getelementptr inbounds nuw i8, ptr %2, i64 16
  store i32 %0, ptr %5, align 8, !tbaa !65
  %6 = tail call noalias dereferenceable_or_null(32) ptr @malloc(i64 noundef 32) #36
  store ptr %6, ptr %2, align 8, !tbaa !66
  ret ptr %2
}

; Function Attrs: mustprogress nounwind willreturn uwtable
define dso_local void @qc_list_push(ptr noundef captures(none) %0, ptr noundef readonly captures(none) %1, i32 noundef %2) local_unnamed_addr #32 {
  %4 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %5 = load i32, ptr %4, align 8, !tbaa !64
  %6 = getelementptr inbounds nuw i8, ptr %0, i64 12
  %7 = load i32, ptr %6, align 4, !tbaa !62
  %8 = icmp slt i32 %5, %7
  br i1 %8, label %15, label %9

9:                                                ; preds = %3
  %10 = shl nsw i32 %7, 1
  store i32 %10, ptr %6, align 4, !tbaa !62
  %11 = load ptr, ptr %0, align 8, !tbaa !66
  %12 = sext i32 %10 to i64
  %13 = shl nsw i64 %12, 3
  %14 = tail call ptr @realloc(ptr noundef %11, i64 noundef %13) #38
  store ptr %14, ptr %0, align 8, !tbaa !66
  br label %15

15:                                               ; preds = %9, %3
  %16 = icmp slt i32 %2, 6
  br i1 %16, label %17, label %27

17:                                               ; preds = %15
  %18 = add i32 %2, -2
  %19 = icmp ult i32 %18, 4
  br i1 %19, label %20, label %24

20:                                               ; preds = %17
  %21 = zext nneg i32 %18 to i64
  %22 = getelementptr inbounds nuw [4 x i64], ptr @switch.table.qc_map_set.53, i64 0, i64 %21
  %23 = load i64, ptr %22, align 8
  br label %24

24:                                               ; preds = %20, %17
  %25 = phi i64 [ %23, %20 ], [ 4, %17 ]
  %26 = tail call noalias ptr @malloc(i64 noundef %25) #36
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %26, ptr noundef nonnull align 1 dereferenceable(1) %1, i64 %25, i1 false)
  br label %29

27:                                               ; preds = %15
  %28 = load ptr, ptr %1, align 8, !tbaa !55
  br label %29

29:                                               ; preds = %27, %24
  %30 = phi ptr [ %28, %27 ], [ %26, %24 ]
  %31 = load ptr, ptr %0, align 8, !tbaa !66
  %32 = load i32, ptr %4, align 8, !tbaa !64
  %33 = add nsw i32 %32, 1
  store i32 %33, ptr %4, align 8, !tbaa !64
  %34 = sext i32 %32 to i64
  %35 = getelementptr inbounds ptr, ptr %31, i64 %34
  store ptr %30, ptr %35, align 8, !tbaa !55
  ret void
}

; Function Attrs: mustprogress nounwind willreturn uwtable
define dso_local void @qc_list_set(ptr noundef readonly captures(none) %0, i32 noundef %1, ptr noundef readonly captures(none) %2) local_unnamed_addr #32 {
  %4 = icmp slt i32 %1, 0
  br i1 %4, label %34, label %5

5:                                                ; preds = %3
  %6 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %7 = load i32, ptr %6, align 8, !tbaa !64
  %8 = icmp slt i32 %1, %7
  br i1 %8, label %9, label %34

9:                                                ; preds = %5
  %10 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %11 = load i32, ptr %10, align 8, !tbaa !65
  %12 = icmp slt i32 %11, 6
  br i1 %12, label %13, label %29

13:                                               ; preds = %9
  %14 = add i32 %11, -2
  %15 = icmp ult i32 %14, 4
  br i1 %15, label %16, label %20

16:                                               ; preds = %13
  %17 = zext nneg i32 %14 to i64
  %18 = getelementptr inbounds nuw [4 x i64], ptr @switch.table.qc_map_set.53, i64 0, i64 %17
  %19 = load i64, ptr %18, align 8
  br label %20

20:                                               ; preds = %16, %13
  %21 = phi i64 [ %19, %16 ], [ 4, %13 ]
  %22 = tail call noalias ptr @malloc(i64 noundef %21) #36
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %22, ptr noundef nonnull align 1 dereferenceable(1) %2, i64 %21, i1 false)
  %23 = load ptr, ptr %0, align 8, !tbaa !66
  %24 = zext nneg i32 %1 to i64
  %25 = getelementptr inbounds nuw ptr, ptr %23, i64 %24
  %26 = load ptr, ptr %25, align 8, !tbaa !55
  tail call void @free(ptr noundef %26) #37
  %27 = load ptr, ptr %0, align 8, !tbaa !66
  %28 = getelementptr inbounds nuw ptr, ptr %27, i64 %24
  store ptr %22, ptr %28, align 8, !tbaa !55
  br label %34

29:                                               ; preds = %9
  %30 = load ptr, ptr %2, align 8, !tbaa !55
  %31 = load ptr, ptr %0, align 8, !tbaa !66
  %32 = zext nneg i32 %1 to i64
  %33 = getelementptr inbounds nuw ptr, ptr %31, i64 %32
  store ptr %30, ptr %33, align 8, !tbaa !55
  br label %34

34:                                               ; preds = %29, %20, %5, %3
  ret void
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(read, inaccessiblemem: none) uwtable
define dso_local ptr @qc_list_get(ptr noundef readonly captures(none) %0, i32 noundef %1) local_unnamed_addr #30 {
  %3 = icmp slt i32 %1, 0
  br i1 %3, label %13, label %4

4:                                                ; preds = %2
  %5 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %6 = load i32, ptr %5, align 8, !tbaa !64
  %7 = icmp slt i32 %1, %6
  br i1 %7, label %8, label %13

8:                                                ; preds = %4
  %9 = load ptr, ptr %0, align 8, !tbaa !66
  %10 = zext nneg i32 %1 to i64
  %11 = getelementptr inbounds nuw ptr, ptr %9, i64 %10
  %12 = load ptr, ptr %11, align 8, !tbaa !55
  br label %13

13:                                               ; preds = %8, %4, %2
  %14 = phi ptr [ %12, %8 ], [ null, %4 ], [ null, %2 ]
  ret ptr %14
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(read, argmem: readwrite, inaccessiblemem: none) uwtable
define dso_local ptr @qc_list_pop(ptr noundef captures(none) %0) local_unnamed_addr #33 {
  %2 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %3 = load i32, ptr %2, align 8, !tbaa !64
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %11, label %5

5:                                                ; preds = %1
  %6 = load ptr, ptr %0, align 8, !tbaa !66
  %7 = add nsw i32 %3, -1
  store i32 %7, ptr %2, align 8, !tbaa !64
  %8 = sext i32 %7 to i64
  %9 = getelementptr inbounds ptr, ptr %6, i64 %8
  %10 = load ptr, ptr %9, align 8, !tbaa !55
  br label %11

11:                                               ; preds = %5, %1
  %12 = phi ptr [ %10, %5 ], [ null, %1 ]
  ret ptr %12
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
define dso_local i32 @qc_list_length(ptr noundef readonly captures(none) %0) local_unnamed_addr #26 {
  %2 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %3 = load i32, ptr %2, align 8, !tbaa !64
  ret i32 %3
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(write, argmem: none, inaccessiblemem: readwrite) uwtable
define dso_local noalias noundef ptr @qc_create_map(i32 noundef %0, i32 noundef %1) local_unnamed_addr #16 {
  %3 = tail call noalias dereferenceable_or_null(32) ptr @malloc(i64 noundef 32) #36
  %4 = getelementptr inbounds nuw i8, ptr %3, i64 20
  store i32 4, ptr %4, align 4, !tbaa !67
  %5 = getelementptr inbounds nuw i8, ptr %3, i64 16
  store i32 0, ptr %5, align 8, !tbaa !69
  %6 = getelementptr inbounds nuw i8, ptr %3, i64 24
  store i32 %0, ptr %6, align 8, !tbaa !70
  %7 = getelementptr inbounds nuw i8, ptr %3, i64 28
  store i32 %1, ptr %7, align 4, !tbaa !71
  %8 = tail call noalias dereferenceable_or_null(32) ptr @malloc(i64 noundef 32) #36
  store ptr %8, ptr %3, align 8, !tbaa !72
  %9 = tail call noalias dereferenceable_or_null(32) ptr @malloc(i64 noundef 32) #36
  %10 = getelementptr inbounds nuw i8, ptr %3, i64 8
  store ptr %9, ptr %10, align 8, !tbaa !73
  ret ptr %3
}

; Function Attrs: mustprogress nofree norecurse nounwind willreturn memory(argmem: read) uwtable
define dso_local zeroext i1 @qc_compare_keys(ptr noundef readonly captures(address_is_null) %0, ptr noundef readonly captures(address_is_null) %1, i32 noundef %2) local_unnamed_addr #14 {
  %4 = icmp ne ptr %0, null
  %5 = icmp ne ptr %1, null
  %6 = and i1 %4, %5
  br i1 %6, label %7, label %35

7:                                                ; preds = %3
  switch i32 %2, label %35 [
    i32 0, label %8
    i32 1, label %12
    i32 2, label %16
    i32 3, label %20
    i32 4, label %24
    i32 5, label %28
    i32 6, label %32
  ]

8:                                                ; preds = %7
  %9 = load i32, ptr %0, align 4, !tbaa !19
  %10 = load i32, ptr %1, align 4, !tbaa !19
  %11 = icmp eq i32 %9, %10
  br label %35

12:                                               ; preds = %7
  %13 = load float, ptr %0, align 4, !tbaa !22
  %14 = load float, ptr %1, align 4, !tbaa !22
  %15 = fcmp oeq float %13, %14
  br label %35

16:                                               ; preds = %7
  %17 = load double, ptr %0, align 8, !tbaa !25
  %18 = load double, ptr %1, align 8, !tbaa !25
  %19 = fcmp oeq double %17, %18
  br label %35

20:                                               ; preds = %7
  %21 = load i8, ptr %0, align 1, !tbaa !7
  %22 = load i8, ptr %1, align 1, !tbaa !7
  %23 = icmp eq i8 %21, %22
  br label %35

24:                                               ; preds = %7
  %25 = load i8, ptr %0, align 1, !tbaa !32, !range !34, !noundef !35
  %26 = load i8, ptr %1, align 1, !tbaa !32, !range !34, !noundef !35
  %27 = icmp eq i8 %25, %26
  br label %35

28:                                               ; preds = %7
  %29 = load i8, ptr %0, align 1, !tbaa !7
  %30 = load i8, ptr %1, align 1, !tbaa !7
  %31 = icmp eq i8 %29, %30
  br label %35

32:                                               ; preds = %7
  %33 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(1) %1) #40
  %34 = icmp eq i32 %33, 0
  br label %35

35:                                               ; preds = %32, %28, %24, %20, %16, %12, %8, %7, %3
  %36 = phi i1 [ %11, %8 ], [ %15, %12 ], [ %19, %16 ], [ %23, %20 ], [ %27, %24 ], [ %31, %28 ], [ %34, %32 ], [ false, %3 ], [ false, %7 ]
  ret i1 %36
}

; Function Attrs: mustprogress nounwind uwtable
define dso_local void @qc_map_set(ptr noundef captures(none) %0, ptr noundef %1, ptr noundef %2) local_unnamed_addr #17 {
  %4 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %5 = load i32, ptr %4, align 8, !tbaa !69
  %6 = icmp sgt i32 %5, 0
  br i1 %6, label %7, label %155

7:                                                ; preds = %3
  %8 = load ptr, ptr %0, align 8, !tbaa !72
  %9 = getelementptr inbounds nuw i8, ptr %0, i64 24
  %10 = load i32, ptr %9, align 8, !tbaa !70
  %11 = freeze i32 %10
  %12 = icmp eq ptr %1, null
  br i1 %12, label %155, label %13

13:                                               ; preds = %7
  switch i32 %11, label %155 [
    i32 0, label %26
    i32 1, label %24
    i32 2, label %22
    i32 3, label %20
    i32 4, label %18
    i32 5, label %16
    i32 6, label %14
  ]

14:                                               ; preds = %13
  %15 = zext nneg i32 %5 to i64
  br label %100

16:                                               ; preds = %13
  %17 = zext nneg i32 %5 to i64
  br label %88

18:                                               ; preds = %13
  %19 = zext nneg i32 %5 to i64
  br label %76

20:                                               ; preds = %13
  %21 = zext nneg i32 %5 to i64
  br label %64

22:                                               ; preds = %13
  %23 = zext nneg i32 %5 to i64
  br label %52

24:                                               ; preds = %13
  %25 = zext nneg i32 %5 to i64
  br label %40

26:                                               ; preds = %13
  %27 = zext nneg i32 %5 to i64
  br label %28

28:                                               ; preds = %37, %26
  %29 = phi i64 [ 0, %26 ], [ %38, %37 ]
  %30 = getelementptr inbounds nuw ptr, ptr %8, i64 %29
  %31 = load ptr, ptr %30, align 8, !tbaa !55
  %32 = icmp eq ptr %31, null
  br i1 %32, label %37, label %33

33:                                               ; preds = %28
  %34 = load i32, ptr %31, align 4, !tbaa !19
  %35 = load i32, ptr %1, align 4, !tbaa !19
  %36 = icmp eq i32 %34, %35
  br i1 %36, label %111, label %37

37:                                               ; preds = %33, %28
  %38 = add nuw nsw i64 %29, 1
  %39 = icmp eq i64 %38, %27
  br i1 %39, label %155, label %28, !llvm.loop !74

40:                                               ; preds = %49, %24
  %41 = phi i64 [ 0, %24 ], [ %50, %49 ]
  %42 = getelementptr inbounds nuw ptr, ptr %8, i64 %41
  %43 = load ptr, ptr %42, align 8, !tbaa !55
  %44 = icmp eq ptr %43, null
  br i1 %44, label %49, label %45

45:                                               ; preds = %40
  %46 = load float, ptr %43, align 4, !tbaa !22
  %47 = load float, ptr %1, align 4, !tbaa !22
  %48 = fcmp oeq float %46, %47
  br i1 %48, label %111, label %49

49:                                               ; preds = %45, %40
  %50 = add nuw nsw i64 %41, 1
  %51 = icmp eq i64 %50, %25
  br i1 %51, label %155, label %40, !llvm.loop !74

52:                                               ; preds = %61, %22
  %53 = phi i64 [ 0, %22 ], [ %62, %61 ]
  %54 = getelementptr inbounds nuw ptr, ptr %8, i64 %53
  %55 = load ptr, ptr %54, align 8, !tbaa !55
  %56 = icmp eq ptr %55, null
  br i1 %56, label %61, label %57

57:                                               ; preds = %52
  %58 = load double, ptr %55, align 8, !tbaa !25
  %59 = load double, ptr %1, align 8, !tbaa !25
  %60 = fcmp oeq double %58, %59
  br i1 %60, label %111, label %61

61:                                               ; preds = %57, %52
  %62 = add nuw nsw i64 %53, 1
  %63 = icmp eq i64 %62, %23
  br i1 %63, label %155, label %52, !llvm.loop !74

64:                                               ; preds = %73, %20
  %65 = phi i64 [ 0, %20 ], [ %74, %73 ]
  %66 = getelementptr inbounds nuw ptr, ptr %8, i64 %65
  %67 = load ptr, ptr %66, align 8, !tbaa !55
  %68 = icmp eq ptr %67, null
  br i1 %68, label %73, label %69

69:                                               ; preds = %64
  %70 = load i8, ptr %67, align 1, !tbaa !7
  %71 = load i8, ptr %1, align 1, !tbaa !7
  %72 = icmp eq i8 %70, %71
  br i1 %72, label %111, label %73

73:                                               ; preds = %69, %64
  %74 = add nuw nsw i64 %65, 1
  %75 = icmp eq i64 %74, %21
  br i1 %75, label %155, label %64, !llvm.loop !74

76:                                               ; preds = %85, %18
  %77 = phi i64 [ 0, %18 ], [ %86, %85 ]
  %78 = getelementptr inbounds nuw ptr, ptr %8, i64 %77
  %79 = load ptr, ptr %78, align 8, !tbaa !55
  %80 = icmp eq ptr %79, null
  br i1 %80, label %85, label %81

81:                                               ; preds = %76
  %82 = load i8, ptr %79, align 1, !tbaa !32, !range !34, !noundef !35
  %83 = load i8, ptr %1, align 1, !tbaa !32, !range !34, !noundef !35
  %84 = icmp eq i8 %82, %83
  br i1 %84, label %111, label %85

85:                                               ; preds = %81, %76
  %86 = add nuw nsw i64 %77, 1
  %87 = icmp eq i64 %86, %19
  br i1 %87, label %155, label %76, !llvm.loop !74

88:                                               ; preds = %97, %16
  %89 = phi i64 [ 0, %16 ], [ %98, %97 ]
  %90 = getelementptr inbounds nuw ptr, ptr %8, i64 %89
  %91 = load ptr, ptr %90, align 8, !tbaa !55
  %92 = icmp eq ptr %91, null
  br i1 %92, label %97, label %93

93:                                               ; preds = %88
  %94 = load i8, ptr %91, align 1, !tbaa !7
  %95 = load i8, ptr %1, align 1, !tbaa !7
  %96 = icmp eq i8 %94, %95
  br i1 %96, label %111, label %97

97:                                               ; preds = %93, %88
  %98 = add nuw nsw i64 %89, 1
  %99 = icmp eq i64 %98, %17
  br i1 %99, label %155, label %88, !llvm.loop !74

100:                                              ; preds = %108, %14
  %101 = phi i64 [ 0, %14 ], [ %109, %108 ]
  %102 = getelementptr inbounds nuw ptr, ptr %8, i64 %101
  %103 = load ptr, ptr %102, align 8, !tbaa !55
  %104 = icmp eq ptr %103, null
  br i1 %104, label %108, label %105

105:                                              ; preds = %100
  %106 = tail call i32 @strcmp(ptr noundef nonnull readonly dereferenceable(1) %103, ptr noundef nonnull readonly dereferenceable(1) %1) #40
  %107 = icmp eq i32 %106, 0
  br i1 %107, label %116, label %108

108:                                              ; preds = %105, %100
  %109 = add nuw nsw i64 %101, 1
  %110 = icmp eq i64 %109, %15
  br i1 %110, label %155, label %100, !llvm.loop !74

111:                                              ; preds = %93, %81, %69, %57, %45, %33
  %112 = phi i64 [ %29, %33 ], [ %41, %45 ], [ %53, %57 ], [ %65, %69 ], [ %77, %81 ], [ %89, %93 ]
  %113 = getelementptr inbounds nuw i8, ptr %0, i64 28
  %114 = load i32, ptr %113, align 4, !tbaa !71
  %115 = icmp slt i32 %114, 6
  br i1 %115, label %120, label %143

116:                                              ; preds = %105
  %117 = getelementptr inbounds nuw i8, ptr %0, i64 28
  %118 = load i32, ptr %117, align 4, !tbaa !71
  %119 = icmp slt i32 %118, 6
  br i1 %119, label %120, label %147

120:                                              ; preds = %116, %111
  %121 = phi i64 [ %101, %116 ], [ %112, %111 ]
  %122 = phi i32 [ %118, %116 ], [ %114, %111 ]
  %123 = add i32 %122, -2
  %124 = icmp ult i32 %123, 4
  br i1 %124, label %125, label %129

125:                                              ; preds = %120
  %126 = zext nneg i32 %123 to i64
  %127 = getelementptr inbounds nuw [4 x i64], ptr @switch.table.qc_map_set.53, i64 0, i64 %126
  %128 = load i64, ptr %127, align 8
  br label %129

129:                                              ; preds = %125, %120
  %130 = phi i64 [ %128, %125 ], [ 4, %120 ]
  %131 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %132 = load ptr, ptr %131, align 8, !tbaa !73
  %133 = getelementptr inbounds nuw ptr, ptr %132, i64 %121
  %134 = load ptr, ptr %133, align 8, !tbaa !55
  %135 = icmp eq ptr %134, null
  br i1 %135, label %136, label %141

136:                                              ; preds = %129
  %137 = tail call noalias ptr @malloc(i64 noundef %130) #36
  store ptr %137, ptr %133, align 8, !tbaa !55
  %138 = load ptr, ptr %131, align 8, !tbaa !73
  %139 = getelementptr inbounds nuw ptr, ptr %138, i64 %121
  %140 = load ptr, ptr %139, align 8, !tbaa !55
  br label %141

141:                                              ; preds = %136, %129
  %142 = phi ptr [ %140, %136 ], [ %134, %129 ]
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %142, ptr noundef nonnull align 1 dereferenceable(1) %2, i64 %130, i1 false)
  br label %219

143:                                              ; preds = %111
  %144 = icmp eq i32 %11, 6
  br i1 %144, label %145, label %151

145:                                              ; preds = %143
  %146 = zext nneg i32 %5 to i64
  br label %147

147:                                              ; preds = %145, %116
  %148 = phi i64 [ %146, %145 ], [ %15, %116 ]
  %149 = tail call noalias ptr @strdup(ptr noundef nonnull %1) #37
  %150 = getelementptr inbounds nuw ptr, ptr %8, i64 %148
  store ptr %149, ptr %150, align 8, !tbaa !55
  br label %219

151:                                              ; preds = %143
  %152 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %153 = load ptr, ptr %152, align 8, !tbaa !73
  %154 = getelementptr inbounds nuw ptr, ptr %153, i64 %112
  store ptr %2, ptr %154, align 8, !tbaa !55
  br label %219

155:                                              ; preds = %108, %97, %85, %73, %61, %49, %37, %13, %7, %3
  %156 = getelementptr inbounds nuw i8, ptr %0, i64 20
  %157 = load i32, ptr %156, align 4, !tbaa !67
  %158 = icmp slt i32 %5, %157
  br i1 %158, label %171, label %159

159:                                              ; preds = %155
  %160 = shl nsw i32 %157, 1
  store i32 %160, ptr %156, align 4, !tbaa !67
  %161 = load ptr, ptr %0, align 8, !tbaa !72
  %162 = sext i32 %160 to i64
  %163 = shl nsw i64 %162, 3
  %164 = tail call ptr @realloc(ptr noundef %161, i64 noundef %163) #38
  store ptr %164, ptr %0, align 8, !tbaa !72
  %165 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %166 = load ptr, ptr %165, align 8, !tbaa !73
  %167 = load i32, ptr %156, align 4, !tbaa !67
  %168 = sext i32 %167 to i64
  %169 = shl nsw i64 %168, 3
  %170 = tail call ptr @realloc(ptr noundef %166, i64 noundef %169) #38
  store ptr %170, ptr %165, align 8, !tbaa !73
  br label %171

171:                                              ; preds = %159, %155
  %172 = getelementptr inbounds nuw i8, ptr %0, i64 24
  %173 = load i32, ptr %172, align 8, !tbaa !70
  %174 = icmp slt i32 %173, 6
  br i1 %174, label %175, label %185

175:                                              ; preds = %171
  %176 = add i32 %173, -2
  %177 = icmp ult i32 %176, 4
  br i1 %177, label %178, label %182

178:                                              ; preds = %175
  %179 = zext nneg i32 %176 to i64
  %180 = getelementptr inbounds nuw [4 x i64], ptr @switch.table.qc_map_set.53, i64 0, i64 %179
  %181 = load i64, ptr %180, align 8
  br label %182

182:                                              ; preds = %178, %175
  %183 = phi i64 [ %181, %178 ], [ 4, %175 ]
  %184 = tail call noalias ptr @malloc(i64 noundef %183) #36
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %184, ptr noundef nonnull align 1 dereferenceable(1) %1, i64 %183, i1 false)
  br label %189

185:                                              ; preds = %171
  %186 = icmp eq i32 %173, 6
  br i1 %186, label %187, label %189

187:                                              ; preds = %185
  %188 = tail call noalias ptr @strdup(ptr noundef %1) #37
  br label %189

189:                                              ; preds = %187, %185, %182
  %190 = phi ptr [ %188, %187 ], [ %184, %182 ], [ %1, %185 ]
  %191 = load ptr, ptr %0, align 8, !tbaa !72
  %192 = load i32, ptr %4, align 8, !tbaa !69
  %193 = sext i32 %192 to i64
  %194 = getelementptr inbounds ptr, ptr %191, i64 %193
  store ptr %190, ptr %194, align 8, !tbaa !55
  %195 = getelementptr inbounds nuw i8, ptr %0, i64 28
  %196 = load i32, ptr %195, align 4, !tbaa !71
  %197 = icmp slt i32 %196, 6
  br i1 %197, label %198, label %208

198:                                              ; preds = %189
  %199 = add i32 %196, -2
  %200 = icmp ult i32 %199, 4
  br i1 %200, label %201, label %205

201:                                              ; preds = %198
  %202 = zext nneg i32 %199 to i64
  %203 = getelementptr inbounds nuw [4 x i64], ptr @switch.table.qc_map_set.53, i64 0, i64 %202
  %204 = load i64, ptr %203, align 8
  br label %205

205:                                              ; preds = %201, %198
  %206 = phi i64 [ %204, %201 ], [ 4, %198 ]
  %207 = tail call noalias ptr @malloc(i64 noundef %206) #36
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %207, ptr noundef nonnull align 1 dereferenceable(1) %2, i64 %206, i1 false)
  br label %212

208:                                              ; preds = %189
  %209 = icmp eq i32 %196, 6
  br i1 %209, label %210, label %212

210:                                              ; preds = %208
  %211 = tail call noalias ptr @strdup(ptr noundef %2) #37
  br label %212

212:                                              ; preds = %210, %208, %205
  %213 = phi ptr [ %211, %210 ], [ %207, %205 ], [ %2, %208 ]
  %214 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %215 = load ptr, ptr %214, align 8, !tbaa !73
  %216 = sext i32 %192 to i64
  %217 = getelementptr inbounds ptr, ptr %215, i64 %216
  store ptr %213, ptr %217, align 8, !tbaa !55
  %218 = add nsw i32 %192, 1
  store i32 %218, ptr %4, align 8, !tbaa !69
  br label %219

219:                                              ; preds = %212, %151, %147, %141
  ret void
}

; Function Attrs: mustprogress nofree norecurse nounwind willreturn memory(read, inaccessiblemem: none) uwtable
define dso_local ptr @qc_map_get(ptr noundef readonly captures(none) %0, ptr noundef readonly captures(address_is_null) %1) local_unnamed_addr #34 {
  %3 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %4 = load i32, ptr %3, align 8, !tbaa !69
  %5 = icmp sgt i32 %4, 0
  br i1 %5, label %6, label %54

6:                                                ; preds = %2
  %7 = load ptr, ptr %0, align 8, !tbaa !72
  %8 = icmp eq ptr %1, null
  %9 = getelementptr inbounds nuw i8, ptr %0, i64 24
  br i1 %8, label %54, label %10

10:                                               ; preds = %6
  %11 = zext nneg i32 %4 to i64
  br label %12

12:                                               ; preds = %51, %10
  %13 = phi i64 [ 0, %10 ], [ %52, %51 ]
  %14 = getelementptr inbounds nuw ptr, ptr %7, i64 %13
  %15 = load ptr, ptr %14, align 8, !tbaa !55
  %16 = icmp eq ptr %15, null
  br i1 %16, label %51, label %17

17:                                               ; preds = %12
  %18 = load i32, ptr %9, align 8, !tbaa !70
  switch i32 %18, label %51 [
    i32 0, label %19
    i32 1, label %23
    i32 2, label %27
    i32 3, label %31
    i32 4, label %35
    i32 5, label %39
    i32 6, label %43
  ]

19:                                               ; preds = %17
  %20 = load i32, ptr %15, align 4, !tbaa !19
  %21 = load i32, ptr %1, align 4, !tbaa !19
  %22 = icmp eq i32 %20, %21
  br i1 %22, label %46, label %51

23:                                               ; preds = %17
  %24 = load float, ptr %15, align 4, !tbaa !22
  %25 = load float, ptr %1, align 4, !tbaa !22
  %26 = fcmp oeq float %24, %25
  br i1 %26, label %46, label %51

27:                                               ; preds = %17
  %28 = load double, ptr %15, align 8, !tbaa !25
  %29 = load double, ptr %1, align 8, !tbaa !25
  %30 = fcmp oeq double %28, %29
  br i1 %30, label %46, label %51

31:                                               ; preds = %17
  %32 = load i8, ptr %15, align 1, !tbaa !7
  %33 = load i8, ptr %1, align 1, !tbaa !7
  %34 = icmp eq i8 %32, %33
  br i1 %34, label %46, label %51

35:                                               ; preds = %17
  %36 = load i8, ptr %15, align 1, !tbaa !32, !range !34, !noundef !35
  %37 = load i8, ptr %1, align 1, !tbaa !32, !range !34, !noundef !35
  %38 = icmp eq i8 %36, %37
  br i1 %38, label %46, label %51

39:                                               ; preds = %17
  %40 = load i8, ptr %15, align 1, !tbaa !7
  %41 = load i8, ptr %1, align 1, !tbaa !7
  %42 = icmp eq i8 %40, %41
  br i1 %42, label %46, label %51

43:                                               ; preds = %17
  %44 = tail call i32 @strcmp(ptr noundef nonnull readonly dereferenceable(1) %15, ptr noundef nonnull readonly dereferenceable(1) %1) #40
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %46, label %51

46:                                               ; preds = %43, %39, %35, %31, %27, %23, %19
  %47 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %48 = load ptr, ptr %47, align 8, !tbaa !73
  %49 = getelementptr inbounds nuw ptr, ptr %48, i64 %13
  %50 = load ptr, ptr %49, align 8, !tbaa !55
  br label %54

51:                                               ; preds = %43, %39, %35, %31, %27, %23, %19, %17, %12
  %52 = add nuw nsw i64 %13, 1
  %53 = icmp eq i64 %52, %11
  br i1 %53, label %54, label %12, !llvm.loop !75

54:                                               ; preds = %51, %46, %6, %2
  %55 = phi ptr [ %50, %46 ], [ null, %2 ], [ null, %6 ], [ null, %51 ]
  ret ptr %55
}

; Function Attrs: mustprogress nofree norecurse nounwind willreturn memory(read, inaccessiblemem: none) uwtable
define dso_local noundef zeroext i1 @qc_map_has(ptr noundef readonly captures(none) %0, ptr noundef readonly captures(address_is_null) %1) local_unnamed_addr #34 {
  %3 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %4 = load i32, ptr %3, align 8, !tbaa !69
  %5 = icmp sgt i32 %4, 0
  br i1 %5, label %6, label %49

6:                                                ; preds = %2
  %7 = load ptr, ptr %0, align 8, !tbaa !72
  %8 = icmp eq ptr %1, null
  %9 = getelementptr inbounds nuw i8, ptr %0, i64 24
  br i1 %8, label %49, label %10

10:                                               ; preds = %6
  %11 = zext nneg i32 %4 to i64
  br label %12

12:                                               ; preds = %46, %10
  %13 = phi i64 [ 0, %10 ], [ %47, %46 ]
  %14 = getelementptr inbounds nuw ptr, ptr %7, i64 %13
  %15 = load ptr, ptr %14, align 8, !tbaa !55
  %16 = icmp eq ptr %15, null
  br i1 %16, label %46, label %17

17:                                               ; preds = %12
  %18 = load i32, ptr %9, align 8, !tbaa !70
  switch i32 %18, label %46 [
    i32 0, label %19
    i32 1, label %23
    i32 2, label %27
    i32 3, label %31
    i32 4, label %35
    i32 5, label %39
    i32 6, label %43
  ]

19:                                               ; preds = %17
  %20 = load i32, ptr %15, align 4, !tbaa !19
  %21 = load i32, ptr %1, align 4, !tbaa !19
  %22 = icmp eq i32 %20, %21
  br i1 %22, label %49, label %46

23:                                               ; preds = %17
  %24 = load float, ptr %15, align 4, !tbaa !22
  %25 = load float, ptr %1, align 4, !tbaa !22
  %26 = fcmp oeq float %24, %25
  br i1 %26, label %49, label %46

27:                                               ; preds = %17
  %28 = load double, ptr %15, align 8, !tbaa !25
  %29 = load double, ptr %1, align 8, !tbaa !25
  %30 = fcmp oeq double %28, %29
  br i1 %30, label %49, label %46

31:                                               ; preds = %17
  %32 = load i8, ptr %15, align 1, !tbaa !7
  %33 = load i8, ptr %1, align 1, !tbaa !7
  %34 = icmp eq i8 %32, %33
  br i1 %34, label %49, label %46

35:                                               ; preds = %17
  %36 = load i8, ptr %15, align 1, !tbaa !32, !range !34, !noundef !35
  %37 = load i8, ptr %1, align 1, !tbaa !32, !range !34, !noundef !35
  %38 = icmp eq i8 %36, %37
  br i1 %38, label %49, label %46

39:                                               ; preds = %17
  %40 = load i8, ptr %15, align 1, !tbaa !7
  %41 = load i8, ptr %1, align 1, !tbaa !7
  %42 = icmp eq i8 %40, %41
  br i1 %42, label %49, label %46

43:                                               ; preds = %17
  %44 = tail call i32 @strcmp(ptr noundef nonnull readonly dereferenceable(1) %15, ptr noundef nonnull readonly dereferenceable(1) %1) #40
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %49, label %46

46:                                               ; preds = %43, %39, %35, %31, %27, %23, %19, %17, %12
  %47 = add nuw nsw i64 %13, 1
  %48 = icmp eq i64 %47, %11
  br i1 %48, label %49, label %12, !llvm.loop !76

49:                                               ; preds = %46, %43, %39, %35, %31, %27, %23, %19, %6, %2
  %50 = phi i1 [ false, %2 ], [ false, %6 ], [ true, %39 ], [ true, %35 ], [ true, %31 ], [ true, %27 ], [ true, %23 ], [ true, %19 ], [ true, %43 ], [ false, %46 ]
  ret i1 %50
}

; Function Attrs: mustprogress nofree norecurse nounwind memory(readwrite, inaccessiblemem: none) uwtable
define dso_local void @qc_map_remove(ptr noundef captures(none) %0, ptr noundef readonly captures(address_is_null) %1) local_unnamed_addr #35 {
  %3 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %4 = load i32, ptr %3, align 8, !tbaa !69
  %5 = icmp sgt i32 %4, 0
  br i1 %5, label %6, label %95

6:                                                ; preds = %2
  %7 = load ptr, ptr %0, align 8, !tbaa !72
  %8 = icmp eq ptr %1, null
  %9 = getelementptr inbounds nuw i8, ptr %0, i64 24
  br i1 %8, label %95, label %10

10:                                               ; preds = %6
  %11 = zext nneg i32 %4 to i64
  br label %12

12:                                               ; preds = %92, %10
  %13 = phi i64 [ 0, %10 ], [ %93, %92 ]
  %14 = getelementptr inbounds nuw ptr, ptr %7, i64 %13
  %15 = load ptr, ptr %14, align 8, !tbaa !55
  %16 = icmp eq ptr %15, null
  br i1 %16, label %92, label %17

17:                                               ; preds = %12
  %18 = load i32, ptr %9, align 8, !tbaa !70
  switch i32 %18, label %92 [
    i32 0, label %19
    i32 1, label %23
    i32 2, label %27
    i32 3, label %31
    i32 4, label %35
    i32 5, label %39
    i32 6, label %43
  ]

19:                                               ; preds = %17
  %20 = load i32, ptr %15, align 4, !tbaa !19
  %21 = load i32, ptr %1, align 4, !tbaa !19
  %22 = icmp eq i32 %20, %21
  br i1 %22, label %46, label %92

23:                                               ; preds = %17
  %24 = load float, ptr %15, align 4, !tbaa !22
  %25 = load float, ptr %1, align 4, !tbaa !22
  %26 = fcmp oeq float %24, %25
  br i1 %26, label %46, label %92

27:                                               ; preds = %17
  %28 = load double, ptr %15, align 8, !tbaa !25
  %29 = load double, ptr %1, align 8, !tbaa !25
  %30 = fcmp oeq double %28, %29
  br i1 %30, label %46, label %92

31:                                               ; preds = %17
  %32 = load i8, ptr %15, align 1, !tbaa !7
  %33 = load i8, ptr %1, align 1, !tbaa !7
  %34 = icmp eq i8 %32, %33
  br i1 %34, label %46, label %92

35:                                               ; preds = %17
  %36 = load i8, ptr %15, align 1, !tbaa !32, !range !34, !noundef !35
  %37 = load i8, ptr %1, align 1, !tbaa !32, !range !34, !noundef !35
  %38 = icmp eq i8 %36, %37
  br i1 %38, label %46, label %92

39:                                               ; preds = %17
  %40 = load i8, ptr %15, align 1, !tbaa !7
  %41 = load i8, ptr %1, align 1, !tbaa !7
  %42 = icmp eq i8 %40, %41
  br i1 %42, label %46, label %92

43:                                               ; preds = %17
  %44 = tail call i32 @strcmp(ptr noundef nonnull readonly dereferenceable(1) %15, ptr noundef nonnull readonly dereferenceable(1) %1) #40
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %46, label %92

46:                                               ; preds = %43, %39, %35, %31, %27, %23, %19
  %47 = trunc nuw nsw i64 %13 to i32
  %48 = add nsw i32 %4, -1
  %49 = icmp sgt i32 %48, %47
  br i1 %49, label %50, label %70

50:                                               ; preds = %46
  %51 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %52 = zext i32 %48 to i64
  %53 = sub nsw i64 %52, %13
  %54 = and i64 %53, 1
  %55 = icmp eq i64 %54, 0
  br i1 %55, label %66, label %56

56:                                               ; preds = %50
  %57 = load ptr, ptr %0, align 8, !tbaa !72
  %58 = add nuw nsw i64 %13, 1
  %59 = getelementptr inbounds nuw ptr, ptr %57, i64 %58
  %60 = load ptr, ptr %59, align 8, !tbaa !55
  %61 = getelementptr inbounds nuw ptr, ptr %57, i64 %13
  store ptr %60, ptr %61, align 8, !tbaa !55
  %62 = load ptr, ptr %51, align 8, !tbaa !73
  %63 = getelementptr inbounds nuw ptr, ptr %62, i64 %58
  %64 = load ptr, ptr %63, align 8, !tbaa !55
  %65 = getelementptr inbounds nuw ptr, ptr %62, i64 %13
  store ptr %64, ptr %65, align 8, !tbaa !55
  br label %66

66:                                               ; preds = %56, %50
  %67 = phi i64 [ %13, %50 ], [ %58, %56 ]
  %68 = add nsw i64 %52, -1
  %69 = icmp eq i64 %13, %68
  br i1 %69, label %70, label %71

70:                                               ; preds = %71, %66, %46
  store i32 %48, ptr %3, align 8, !tbaa !69
  br label %95

71:                                               ; preds = %71, %66
  %72 = phi i64 [ %83, %71 ], [ %67, %66 ]
  %73 = load ptr, ptr %0, align 8, !tbaa !72
  %74 = add nuw nsw i64 %72, 1
  %75 = getelementptr inbounds nuw ptr, ptr %73, i64 %74
  %76 = load ptr, ptr %75, align 8, !tbaa !55
  %77 = getelementptr inbounds nuw ptr, ptr %73, i64 %72
  store ptr %76, ptr %77, align 8, !tbaa !55
  %78 = load ptr, ptr %51, align 8, !tbaa !73
  %79 = getelementptr inbounds nuw ptr, ptr %78, i64 %74
  %80 = load ptr, ptr %79, align 8, !tbaa !55
  %81 = getelementptr inbounds nuw ptr, ptr %78, i64 %72
  store ptr %80, ptr %81, align 8, !tbaa !55
  %82 = load ptr, ptr %0, align 8, !tbaa !72
  %83 = add nuw nsw i64 %72, 2
  %84 = getelementptr inbounds nuw ptr, ptr %82, i64 %83
  %85 = load ptr, ptr %84, align 8, !tbaa !55
  %86 = getelementptr inbounds nuw ptr, ptr %82, i64 %74
  store ptr %85, ptr %86, align 8, !tbaa !55
  %87 = load ptr, ptr %51, align 8, !tbaa !73
  %88 = getelementptr inbounds nuw ptr, ptr %87, i64 %83
  %89 = load ptr, ptr %88, align 8, !tbaa !55
  %90 = getelementptr inbounds nuw ptr, ptr %87, i64 %74
  store ptr %89, ptr %90, align 8, !tbaa !55
  %91 = icmp eq i64 %83, %52
  br i1 %91, label %70, label %71, !llvm.loop !77

92:                                               ; preds = %43, %39, %35, %31, %27, %23, %19, %17, %12
  %93 = add nuw nsw i64 %13, 1
  %94 = icmp eq i64 %93, %11
  br i1 %94, label %95, label %12, !llvm.loop !78

95:                                               ; preds = %92, %70, %6, %2
  ret void
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_map(ptr noundef readonly captures(none) %0) local_unnamed_addr #6 {
  %2 = load ptr, ptr @stdout, align 8, !tbaa !10
  %3 = tail call noundef i32 @putc(i32 noundef 123, ptr noundef %2)
  %4 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %5 = load i32, ptr %4, align 8, !tbaa !69
  %6 = icmp sgt i32 %5, 0
  br i1 %6, label %7, label %11

7:                                                ; preds = %1
  %8 = getelementptr inbounds nuw i8, ptr %0, i64 24
  %9 = getelementptr inbounds nuw i8, ptr %0, i64 28
  %10 = getelementptr inbounds nuw i8, ptr %0, i64 8
  br label %14

11:                                               ; preds = %132, %1
  %12 = load ptr, ptr @stdout, align 8, !tbaa !10
  %13 = tail call noundef i32 @putc(i32 noundef 125, ptr noundef %12)
  ret void

14:                                               ; preds = %132, %7
  %15 = phi i64 [ 0, %7 ], [ %134, %132 ]
  %16 = load i32, ptr %8, align 8, !tbaa !70
  switch i32 %16, label %69 [
    i32 0, label %17
    i32 1, label %23
    i32 2, label %30
    i32 3, label %36
    i32 4, label %43
    i32 5, label %51
    i32 6, label %64
  ]

17:                                               ; preds = %14
  %18 = load ptr, ptr %0, align 8, !tbaa !72
  %19 = getelementptr inbounds nuw ptr, ptr %18, i64 %15
  %20 = load ptr, ptr %19, align 8, !tbaa !55
  %21 = load i32, ptr %20, align 4, !tbaa !19
  %22 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.33, i32 noundef %21)
  br label %69

23:                                               ; preds = %14
  %24 = load ptr, ptr %0, align 8, !tbaa !72
  %25 = getelementptr inbounds nuw ptr, ptr %24, i64 %15
  %26 = load ptr, ptr %25, align 8, !tbaa !55
  %27 = load float, ptr %26, align 4, !tbaa !22
  %28 = fpext float %27 to double
  %29 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, double noundef %28)
  br label %69

30:                                               ; preds = %14
  %31 = load ptr, ptr %0, align 8, !tbaa !72
  %32 = getelementptr inbounds nuw ptr, ptr %31, i64 %15
  %33 = load ptr, ptr %32, align 8, !tbaa !55
  %34 = load double, ptr %33, align 8, !tbaa !25
  %35 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, double noundef %34)
  br label %69

36:                                               ; preds = %14
  %37 = load ptr, ptr %0, align 8, !tbaa !72
  %38 = getelementptr inbounds nuw ptr, ptr %37, i64 %15
  %39 = load ptr, ptr %38, align 8, !tbaa !55
  %40 = load i8, ptr %39, align 1, !tbaa !7
  %41 = sext i8 %40 to i32
  %42 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.45, i32 noundef %41)
  br label %69

43:                                               ; preds = %14
  %44 = load ptr, ptr %0, align 8, !tbaa !72
  %45 = getelementptr inbounds nuw ptr, ptr %44, i64 %15
  %46 = load ptr, ptr %45, align 8, !tbaa !55
  %47 = load i8, ptr %46, align 1, !tbaa !32, !range !34, !noundef !35
  %48 = trunc nuw i8 %47 to i1
  %49 = select i1 %48, ptr @.str.23, ptr @.str.24
  %50 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.38, ptr noundef nonnull %49)
  br label %69

51:                                               ; preds = %14
  %52 = load ptr, ptr %0, align 8, !tbaa !72
  %53 = getelementptr inbounds nuw ptr, ptr %52, i64 %15
  %54 = load ptr, ptr %53, align 8, !tbaa !55
  %55 = load i8, ptr %54, align 1, !tbaa !7
  %56 = and i8 %55, 3
  switch i8 %56, label %57 [
    i8 0, label %61
    i8 1, label %60
  ]

57:                                               ; preds = %51
  %58 = icmp eq i8 %56, 2
  %59 = select i1 %58, ptr @.str.27, ptr @.str.28
  br label %61

60:                                               ; preds = %51
  br label %61

61:                                               ; preds = %60, %57, %51
  %62 = phi ptr [ @.str.25, %51 ], [ %59, %57 ], [ @.str.26, %60 ]
  %63 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.38, ptr noundef nonnull %62)
  br label %69

64:                                               ; preds = %14
  %65 = load ptr, ptr %0, align 8, !tbaa !72
  %66 = getelementptr inbounds nuw ptr, ptr %65, i64 %15
  %67 = load ptr, ptr %66, align 8, !tbaa !55
  %68 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.44, ptr noundef %67)
  br label %69

69:                                               ; preds = %64, %61, %43, %36, %30, %23, %17, %14
  %70 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.48)
  %71 = load i32, ptr %9, align 4, !tbaa !71
  switch i32 %71, label %124 [
    i32 0, label %72
    i32 1, label %78
    i32 2, label %85
    i32 3, label %91
    i32 4, label %98
    i32 5, label %106
    i32 6, label %119
  ]

72:                                               ; preds = %69
  %73 = load ptr, ptr %10, align 8, !tbaa !73
  %74 = getelementptr inbounds nuw ptr, ptr %73, i64 %15
  %75 = load ptr, ptr %74, align 8, !tbaa !55
  %76 = load i32, ptr %75, align 4, !tbaa !19
  %77 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.33, i32 noundef %76)
  br label %124

78:                                               ; preds = %69
  %79 = load ptr, ptr %10, align 8, !tbaa !73
  %80 = getelementptr inbounds nuw ptr, ptr %79, i64 %15
  %81 = load ptr, ptr %80, align 8, !tbaa !55
  %82 = load float, ptr %81, align 4, !tbaa !22
  %83 = fpext float %82 to double
  %84 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, double noundef %83)
  br label %124

85:                                               ; preds = %69
  %86 = load ptr, ptr %10, align 8, !tbaa !73
  %87 = getelementptr inbounds nuw ptr, ptr %86, i64 %15
  %88 = load ptr, ptr %87, align 8, !tbaa !55
  %89 = load double, ptr %88, align 8, !tbaa !25
  %90 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, double noundef %89)
  br label %124

91:                                               ; preds = %69
  %92 = load ptr, ptr %10, align 8, !tbaa !73
  %93 = getelementptr inbounds nuw ptr, ptr %92, i64 %15
  %94 = load ptr, ptr %93, align 8, !tbaa !55
  %95 = load i8, ptr %94, align 1, !tbaa !7
  %96 = sext i8 %95 to i32
  %97 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.45, i32 noundef %96)
  br label %124

98:                                               ; preds = %69
  %99 = load ptr, ptr %10, align 8, !tbaa !73
  %100 = getelementptr inbounds nuw ptr, ptr %99, i64 %15
  %101 = load ptr, ptr %100, align 8, !tbaa !55
  %102 = load i8, ptr %101, align 1, !tbaa !32, !range !34, !noundef !35
  %103 = trunc nuw i8 %102 to i1
  %104 = select i1 %103, ptr @.str.23, ptr @.str.24
  %105 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.38, ptr noundef nonnull %104)
  br label %124

106:                                              ; preds = %69
  %107 = load ptr, ptr %10, align 8, !tbaa !73
  %108 = getelementptr inbounds nuw ptr, ptr %107, i64 %15
  %109 = load ptr, ptr %108, align 8, !tbaa !55
  %110 = load i8, ptr %109, align 1, !tbaa !7
  %111 = and i8 %110, 3
  switch i8 %111, label %112 [
    i8 0, label %116
    i8 1, label %115
  ]

112:                                              ; preds = %106
  %113 = icmp eq i8 %111, 2
  %114 = select i1 %113, ptr @.str.27, ptr @.str.28
  br label %116

115:                                              ; preds = %106
  br label %116

116:                                              ; preds = %115, %112, %106
  %117 = phi ptr [ @.str.25, %106 ], [ %114, %112 ], [ @.str.26, %115 ]
  %118 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.38, ptr noundef nonnull %117)
  br label %124

119:                                              ; preds = %69
  %120 = load ptr, ptr %10, align 8, !tbaa !73
  %121 = getelementptr inbounds nuw ptr, ptr %120, i64 %15
  %122 = load ptr, ptr %121, align 8, !tbaa !55
  %123 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.44, ptr noundef %122)
  br label %124

124:                                              ; preds = %119, %116, %98, %91, %85, %78, %72, %69
  %125 = load i32, ptr %4, align 8, !tbaa !69
  %126 = add nsw i32 %125, -1
  %127 = sext i32 %126 to i64
  %128 = icmp slt i64 %15, %127
  br i1 %128, label %129, label %132

129:                                              ; preds = %124
  %130 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.42)
  %131 = load i32, ptr %4, align 8, !tbaa !69
  br label %132

132:                                              ; preds = %129, %124
  %133 = phi i32 [ %125, %124 ], [ %131, %129 ]
  %134 = add nuw nsw i64 %15, 1
  %135 = sext i32 %133 to i64
  %136 = icmp slt i64 %134, %135
  br i1 %136, label %14, label %11, !llvm.loop !79
}

; Function Attrs: mustprogress nounwind uwtable
define dso_local ptr @qc_map_to_string(ptr noundef readonly captures(none) %0) local_unnamed_addr #17 {
  %2 = alloca [128 x i8], align 16
  %3 = tail call noalias dereferenceable_or_null(256) ptr @malloc(i64 noundef 256) #36
  %4 = getelementptr inbounds nuw i8, ptr %3, i64 1
  store i8 123, ptr %3, align 1, !tbaa !7
  %5 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %6 = load i32, ptr %5, align 8, !tbaa !69
  %7 = icmp sgt i32 %6, 0
  br i1 %7, label %8, label %12

8:                                                ; preds = %1
  %9 = getelementptr inbounds nuw i8, ptr %0, i64 24
  %10 = getelementptr inbounds nuw i8, ptr %0, i64 28
  %11 = getelementptr inbounds nuw i8, ptr %0, i64 8
  br label %16

12:                                               ; preds = %194, %1
  %13 = phi ptr [ %4, %1 ], [ %197, %194 ]
  %14 = phi ptr [ %3, %1 ], [ %178, %194 ]
  %15 = getelementptr inbounds nuw i8, ptr %13, i64 1
  store i8 125, ptr %13, align 1, !tbaa !7
  store i8 0, ptr %15, align 1, !tbaa !7
  ret ptr %14

16:                                               ; preds = %194, %8
  %17 = phi i64 [ 0, %8 ], [ %198, %194 ]
  %18 = phi i32 [ 256, %8 ], [ %179, %194 ]
  %19 = phi ptr [ %3, %8 ], [ %178, %194 ]
  %20 = phi ptr [ %4, %8 ], [ %197, %194 ]
  %21 = phi i32 [ 255, %8 ], [ %196, %194 ]
  call void @llvm.lifetime.start.p0(i64 128, ptr nonnull %2) #37
  %22 = load i32, ptr %9, align 8, !tbaa !70
  switch i32 %22, label %75 [
    i32 0, label %23
    i32 1, label %29
    i32 2, label %36
    i32 3, label %42
    i32 4, label %49
    i32 5, label %57
    i32 6, label %70
  ]

23:                                               ; preds = %16
  %24 = load ptr, ptr %0, align 8, !tbaa !72
  %25 = getelementptr inbounds nuw ptr, ptr %24, i64 %17
  %26 = load ptr, ptr %25, align 8, !tbaa !55
  %27 = load i32, ptr %26, align 4, !tbaa !19
  %28 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.33, i32 noundef %27) #37
  br label %75

29:                                               ; preds = %16
  %30 = load ptr, ptr %0, align 8, !tbaa !72
  %31 = getelementptr inbounds nuw ptr, ptr %30, i64 %17
  %32 = load ptr, ptr %31, align 8, !tbaa !55
  %33 = load float, ptr %32, align 4, !tbaa !22
  %34 = fpext float %33 to double
  %35 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.34, double noundef %34) #37
  br label %75

36:                                               ; preds = %16
  %37 = load ptr, ptr %0, align 8, !tbaa !72
  %38 = getelementptr inbounds nuw ptr, ptr %37, i64 %17
  %39 = load ptr, ptr %38, align 8, !tbaa !55
  %40 = load double, ptr %39, align 8, !tbaa !25
  %41 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.34, double noundef %40) #37
  br label %75

42:                                               ; preds = %16
  %43 = load ptr, ptr %0, align 8, !tbaa !72
  %44 = getelementptr inbounds nuw ptr, ptr %43, i64 %17
  %45 = load ptr, ptr %44, align 8, !tbaa !55
  %46 = load i8, ptr %45, align 1, !tbaa !7
  %47 = sext i8 %46 to i32
  %48 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.45, i32 noundef %47) #37
  br label %75

49:                                               ; preds = %16
  %50 = load ptr, ptr %0, align 8, !tbaa !72
  %51 = getelementptr inbounds nuw ptr, ptr %50, i64 %17
  %52 = load ptr, ptr %51, align 8, !tbaa !55
  %53 = load i8, ptr %52, align 1, !tbaa !32, !range !34, !noundef !35
  %54 = trunc nuw i8 %53 to i1
  %55 = select i1 %54, ptr @.str.23, ptr @.str.24
  %56 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.38, ptr noundef nonnull %55) #37
  br label %75

57:                                               ; preds = %16
  %58 = load ptr, ptr %0, align 8, !tbaa !72
  %59 = getelementptr inbounds nuw ptr, ptr %58, i64 %17
  %60 = load ptr, ptr %59, align 8, !tbaa !55
  %61 = load i8, ptr %60, align 1, !tbaa !7
  %62 = and i8 %61, 3
  switch i8 %62, label %63 [
    i8 0, label %67
    i8 1, label %66
  ]

63:                                               ; preds = %57
  %64 = icmp eq i8 %62, 2
  %65 = select i1 %64, ptr @.str.27, ptr @.str.28
  br label %67

66:                                               ; preds = %57
  br label %67

67:                                               ; preds = %66, %63, %57
  %68 = phi ptr [ @.str.25, %57 ], [ %65, %63 ], [ @.str.26, %66 ]
  %69 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.38, ptr noundef nonnull %68) #37
  br label %75

70:                                               ; preds = %16
  %71 = load ptr, ptr %0, align 8, !tbaa !72
  %72 = getelementptr inbounds nuw ptr, ptr %71, i64 %17
  %73 = load ptr, ptr %72, align 8, !tbaa !55
  %74 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.44, ptr noundef %73) #37
  br label %75

75:                                               ; preds = %70, %67, %49, %42, %36, %29, %23, %16
  %76 = call i64 @strlen(ptr noundef nonnull dereferenceable(1) %2) #40
  %77 = trunc i64 %76 to i32
  %78 = add nsw i32 %77, 10
  %79 = icmp slt i32 %21, %78
  br i1 %79, label %80, label %92

80:                                               ; preds = %75
  %81 = ptrtoint ptr %20 to i64
  %82 = ptrtoint ptr %19 to i64
  %83 = sub i64 %81, %82
  %84 = trunc i64 %83 to i32
  %85 = shl nsw i32 %18, 1
  %86 = sext i32 %85 to i64
  %87 = tail call ptr @realloc(ptr noundef %19, i64 noundef %86) #38
  %88 = shl i64 %83, 32
  %89 = ashr exact i64 %88, 32
  %90 = getelementptr inbounds i8, ptr %87, i64 %89
  %91 = sub nsw i32 %85, %84
  br label %92

92:                                               ; preds = %80, %75
  %93 = phi i32 [ %91, %80 ], [ %21, %75 ]
  %94 = phi ptr [ %90, %80 ], [ %20, %75 ]
  %95 = phi ptr [ %87, %80 ], [ %19, %75 ]
  %96 = phi i32 [ %85, %80 ], [ %18, %75 ]
  %97 = call ptr @strcpy(ptr noundef nonnull dereferenceable(1) %94, ptr noundef nonnull dereferenceable(1) %2) #37
  %98 = shl i64 %76, 32
  %99 = ashr exact i64 %98, 32
  %100 = getelementptr inbounds i8, ptr %94, i64 %99
  %101 = sub nsw i32 %93, %77
  %102 = getelementptr inbounds nuw i8, ptr %100, i64 1
  store i8 58, ptr %100, align 1, !tbaa !7
  %103 = getelementptr inbounds nuw i8, ptr %100, i64 2
  store i8 32, ptr %102, align 1, !tbaa !7
  %104 = add nsw i32 %101, -2
  %105 = load i32, ptr %10, align 4, !tbaa !71
  switch i32 %105, label %158 [
    i32 0, label %106
    i32 1, label %112
    i32 2, label %119
    i32 3, label %125
    i32 4, label %132
    i32 5, label %140
    i32 6, label %153
  ]

106:                                              ; preds = %92
  %107 = load ptr, ptr %11, align 8, !tbaa !73
  %108 = getelementptr inbounds nuw ptr, ptr %107, i64 %17
  %109 = load ptr, ptr %108, align 8, !tbaa !55
  %110 = load i32, ptr %109, align 4, !tbaa !19
  %111 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.33, i32 noundef %110) #37
  br label %158

112:                                              ; preds = %92
  %113 = load ptr, ptr %11, align 8, !tbaa !73
  %114 = getelementptr inbounds nuw ptr, ptr %113, i64 %17
  %115 = load ptr, ptr %114, align 8, !tbaa !55
  %116 = load float, ptr %115, align 4, !tbaa !22
  %117 = fpext float %116 to double
  %118 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.34, double noundef %117) #37
  br label %158

119:                                              ; preds = %92
  %120 = load ptr, ptr %11, align 8, !tbaa !73
  %121 = getelementptr inbounds nuw ptr, ptr %120, i64 %17
  %122 = load ptr, ptr %121, align 8, !tbaa !55
  %123 = load double, ptr %122, align 8, !tbaa !25
  %124 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.34, double noundef %123) #37
  br label %158

125:                                              ; preds = %92
  %126 = load ptr, ptr %11, align 8, !tbaa !73
  %127 = getelementptr inbounds nuw ptr, ptr %126, i64 %17
  %128 = load ptr, ptr %127, align 8, !tbaa !55
  %129 = load i8, ptr %128, align 1, !tbaa !7
  %130 = sext i8 %129 to i32
  %131 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.45, i32 noundef %130) #37
  br label %158

132:                                              ; preds = %92
  %133 = load ptr, ptr %11, align 8, !tbaa !73
  %134 = getelementptr inbounds nuw ptr, ptr %133, i64 %17
  %135 = load ptr, ptr %134, align 8, !tbaa !55
  %136 = load i8, ptr %135, align 1, !tbaa !32, !range !34, !noundef !35
  %137 = trunc nuw i8 %136 to i1
  %138 = select i1 %137, ptr @.str.23, ptr @.str.24
  %139 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.38, ptr noundef nonnull %138) #37
  br label %158

140:                                              ; preds = %92
  %141 = load ptr, ptr %11, align 8, !tbaa !73
  %142 = getelementptr inbounds nuw ptr, ptr %141, i64 %17
  %143 = load ptr, ptr %142, align 8, !tbaa !55
  %144 = load i8, ptr %143, align 1, !tbaa !7
  %145 = and i8 %144, 3
  switch i8 %145, label %146 [
    i8 0, label %150
    i8 1, label %149
  ]

146:                                              ; preds = %140
  %147 = icmp eq i8 %145, 2
  %148 = select i1 %147, ptr @.str.27, ptr @.str.28
  br label %150

149:                                              ; preds = %140
  br label %150

150:                                              ; preds = %149, %146, %140
  %151 = phi ptr [ @.str.25, %140 ], [ %148, %146 ], [ @.str.26, %149 ]
  %152 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.38, ptr noundef nonnull %151) #37
  br label %158

153:                                              ; preds = %92
  %154 = load ptr, ptr %11, align 8, !tbaa !73
  %155 = getelementptr inbounds nuw ptr, ptr %154, i64 %17
  %156 = load ptr, ptr %155, align 8, !tbaa !55
  %157 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.44, ptr noundef %156) #37
  br label %158

158:                                              ; preds = %153, %150, %132, %125, %119, %112, %106, %92
  %159 = call i64 @strlen(ptr noundef nonnull dereferenceable(1) %2) #40
  %160 = trunc i64 %159 to i32
  %161 = add nsw i32 %160, 10
  %162 = icmp slt i32 %104, %161
  br i1 %162, label %163, label %175

163:                                              ; preds = %158
  %164 = ptrtoint ptr %103 to i64
  %165 = ptrtoint ptr %95 to i64
  %166 = sub i64 %164, %165
  %167 = trunc i64 %166 to i32
  %168 = shl nsw i32 %96, 1
  %169 = sext i32 %168 to i64
  %170 = tail call ptr @realloc(ptr noundef %95, i64 noundef %169) #38
  %171 = shl i64 %166, 32
  %172 = ashr exact i64 %171, 32
  %173 = getelementptr inbounds i8, ptr %170, i64 %172
  %174 = sub nsw i32 %168, %167
  br label %175

175:                                              ; preds = %163, %158
  %176 = phi i32 [ %174, %163 ], [ %104, %158 ]
  %177 = phi ptr [ %173, %163 ], [ %103, %158 ]
  %178 = phi ptr [ %170, %163 ], [ %95, %158 ]
  %179 = phi i32 [ %168, %163 ], [ %96, %158 ]
  %180 = call ptr @strcpy(ptr noundef nonnull dereferenceable(1) %177, ptr noundef nonnull dereferenceable(1) %2) #37
  %181 = shl i64 %159, 32
  %182 = ashr exact i64 %181, 32
  %183 = getelementptr inbounds i8, ptr %177, i64 %182
  %184 = sub nsw i32 %176, %160
  %185 = load i32, ptr %5, align 8, !tbaa !69
  %186 = add nsw i32 %185, -1
  %187 = sext i32 %186 to i64
  %188 = icmp slt i64 %17, %187
  br i1 %188, label %189, label %194

189:                                              ; preds = %175
  %190 = getelementptr inbounds nuw i8, ptr %183, i64 1
  store i8 44, ptr %183, align 1, !tbaa !7
  %191 = getelementptr inbounds nuw i8, ptr %183, i64 2
  store i8 32, ptr %190, align 1, !tbaa !7
  %192 = add nsw i32 %184, -2
  %193 = load i32, ptr %5, align 8, !tbaa !69
  br label %194

194:                                              ; preds = %189, %175
  %195 = phi i32 [ %193, %189 ], [ %185, %175 ]
  %196 = phi i32 [ %192, %189 ], [ %184, %175 ]
  %197 = phi ptr [ %191, %189 ], [ %183, %175 ]
  call void @llvm.lifetime.end.p0(i64 128, ptr nonnull %2) #37
  %198 = add nuw nsw i64 %17, 1
  %199 = sext i32 %195 to i64
  %200 = icmp slt i64 %198, %199
  br i1 %200, label %16, label %12, !llvm.loop !80
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
define dso_local i32 @qc_map_size(ptr noundef readonly captures(none) %0) local_unnamed_addr #26 {
  %2 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %3 = load i32, ptr %2, align 8, !tbaa !69
  ret i32 %3
}

; Function Attrs: mustprogress nounwind uwtable
define dso_local noalias noundef ptr @qc_map_keys(ptr noundef readonly captures(none) %0) local_unnamed_addr #17 {
  %2 = getelementptr inbounds nuw i8, ptr %0, i64 24
  %3 = load i32, ptr %2, align 8, !tbaa !70
  %4 = tail call noalias dereferenceable_or_null(24) ptr @malloc(i64 noundef 24) #36
  %5 = getelementptr inbounds nuw i8, ptr %4, i64 12
  store i32 4, ptr %5, align 4, !tbaa !62
  %6 = getelementptr inbounds nuw i8, ptr %4, i64 8
  store i32 0, ptr %6, align 8, !tbaa !64
  %7 = getelementptr inbounds nuw i8, ptr %4, i64 16
  store i32 %3, ptr %7, align 8, !tbaa !65
  %8 = tail call noalias dereferenceable_or_null(32) ptr @malloc(i64 noundef 32) #36
  store ptr %8, ptr %4, align 8, !tbaa !66
  %9 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %10 = load i32, ptr %9, align 8, !tbaa !69
  %11 = icmp sgt i32 %10, 4
  br i1 %11, label %12, label %16

12:                                               ; preds = %1
  store i32 %10, ptr %5, align 4, !tbaa !62
  %13 = zext nneg i32 %10 to i64
  %14 = shl nuw nsw i64 %13, 3
  %15 = tail call ptr @realloc(ptr noundef %8, i64 noundef %14) #38
  store ptr %15, ptr %4, align 8, !tbaa !66
  br label %18

16:                                               ; preds = %1
  %17 = icmp sgt i32 %10, 0
  br i1 %17, label %18, label %108

18:                                               ; preds = %16, %12
  %19 = phi ptr [ %15, %12 ], [ %8, %16 ]
  %20 = ptrtoint ptr %19 to i64
  %21 = icmp slt i32 %3, 6
  br i1 %21, label %22, label %59

22:                                               ; preds = %18
  switch i32 %3, label %26 [
    i32 4, label %29
    i32 5, label %29
    i32 2, label %23
    i32 3, label %29
  ]

23:                                               ; preds = %22
  %24 = zext nneg i32 %10 to i64
  %25 = load ptr, ptr %0, align 8, !tbaa !72
  br label %41

26:                                               ; preds = %22
  %27 = zext nneg i32 %10 to i64
  %28 = load ptr, ptr %0, align 8, !tbaa !72
  br label %50

29:                                               ; preds = %22, %22, %22
  %30 = zext nneg i32 %10 to i64
  %31 = load ptr, ptr %0, align 8, !tbaa !72
  br label %32

32:                                               ; preds = %32, %29
  %33 = phi i64 [ %39, %32 ], [ 0, %29 ]
  %34 = tail call noalias dereferenceable_or_null(1) ptr @malloc(i64 noundef 1) #36
  %35 = getelementptr inbounds nuw ptr, ptr %31, i64 %33
  %36 = load ptr, ptr %35, align 8, !tbaa !55
  %37 = load i8, ptr %36, align 1
  store i8 %37, ptr %34, align 1
  %38 = getelementptr inbounds nuw ptr, ptr %19, i64 %33
  store ptr %34, ptr %38, align 8, !tbaa !55
  %39 = add nuw nsw i64 %33, 1
  %40 = icmp eq i64 %39, %30
  br i1 %40, label %108, label %32, !llvm.loop !81

41:                                               ; preds = %41, %23
  %42 = phi i64 [ 0, %23 ], [ %48, %41 ]
  %43 = tail call noalias dereferenceable_or_null(8) ptr @malloc(i64 noundef 8) #36
  %44 = getelementptr inbounds nuw ptr, ptr %25, i64 %42
  %45 = load ptr, ptr %44, align 8, !tbaa !55
  %46 = load i64, ptr %45, align 1
  store i64 %46, ptr %43, align 1
  %47 = getelementptr inbounds nuw ptr, ptr %19, i64 %42
  store ptr %43, ptr %47, align 8, !tbaa !55
  %48 = add nuw nsw i64 %42, 1
  %49 = icmp eq i64 %48, %24
  br i1 %49, label %108, label %41, !llvm.loop !81

50:                                               ; preds = %50, %26
  %51 = phi i64 [ 0, %26 ], [ %57, %50 ]
  %52 = tail call noalias dereferenceable_or_null(4) ptr @malloc(i64 noundef 4) #36
  %53 = getelementptr inbounds nuw ptr, ptr %28, i64 %51
  %54 = load ptr, ptr %53, align 8, !tbaa !55
  %55 = load i32, ptr %54, align 1
  store i32 %55, ptr %52, align 1
  %56 = getelementptr inbounds nuw ptr, ptr %19, i64 %51
  store ptr %52, ptr %56, align 8, !tbaa !55
  %57 = add nuw nsw i64 %51, 1
  %58 = icmp eq i64 %57, %27
  br i1 %58, label %108, label %50, !llvm.loop !81

59:                                               ; preds = %18
  %60 = icmp eq i32 %3, 6
  %61 = zext i32 %10 to i64
  %62 = load ptr, ptr %0, align 8, !tbaa !72
  br i1 %60, label %100, label %63

63:                                               ; preds = %59
  %64 = ptrtoint ptr %62 to i64
  %65 = icmp ult i32 %10, 6
  %66 = sub i64 %20, %64
  %67 = icmp ult i64 %66, 32
  %68 = select i1 %65, i1 true, i1 %67
  br i1 %68, label %83, label %69

69:                                               ; preds = %63
  %70 = and i64 %61, 4294967292
  br label %71

71:                                               ; preds = %71, %69
  %72 = phi i64 [ 0, %69 ], [ %79, %71 ]
  %73 = getelementptr inbounds nuw ptr, ptr %62, i64 %72
  %74 = getelementptr inbounds nuw i8, ptr %73, i64 16
  %75 = load <2 x ptr>, ptr %73, align 8, !tbaa !55
  %76 = load <2 x ptr>, ptr %74, align 8, !tbaa !55
  %77 = getelementptr inbounds nuw ptr, ptr %19, i64 %72
  %78 = getelementptr inbounds nuw i8, ptr %77, i64 16
  store <2 x ptr> %75, ptr %77, align 8, !tbaa !55
  store <2 x ptr> %76, ptr %78, align 8, !tbaa !55
  %79 = add nuw i64 %72, 4
  %80 = icmp eq i64 %79, %70
  br i1 %80, label %81, label %71, !llvm.loop !82

81:                                               ; preds = %71
  %82 = icmp eq i64 %70, %61
  br i1 %82, label %108, label %83

83:                                               ; preds = %81, %63
  %84 = phi i64 [ 0, %63 ], [ %70, %81 ]
  %85 = and i64 %61, 3
  %86 = icmp eq i64 %85, 0
  br i1 %86, label %96, label %87

87:                                               ; preds = %87, %83
  %88 = phi i64 [ %93, %87 ], [ %84, %83 ]
  %89 = phi i64 [ %94, %87 ], [ 0, %83 ]
  %90 = getelementptr inbounds nuw ptr, ptr %62, i64 %88
  %91 = load ptr, ptr %90, align 8, !tbaa !55
  %92 = getelementptr inbounds nuw ptr, ptr %19, i64 %88
  store ptr %91, ptr %92, align 8, !tbaa !55
  %93 = add nuw nsw i64 %88, 1
  %94 = add i64 %89, 1
  %95 = icmp eq i64 %94, %85
  br i1 %95, label %96, label %87, !llvm.loop !83

96:                                               ; preds = %87, %83
  %97 = phi i64 [ %84, %83 ], [ %93, %87 ]
  %98 = sub nsw i64 %84, %61
  %99 = icmp ugt i64 %98, -4
  br i1 %99, label %108, label %109

100:                                              ; preds = %100, %59
  %101 = phi i64 [ %106, %100 ], [ 0, %59 ]
  %102 = getelementptr inbounds nuw ptr, ptr %62, i64 %101
  %103 = load ptr, ptr %102, align 8, !tbaa !55
  %104 = tail call noalias ptr @strdup(ptr noundef %103) #37
  %105 = getelementptr inbounds nuw ptr, ptr %19, i64 %101
  store ptr %104, ptr %105, align 8, !tbaa !55
  %106 = add nuw nsw i64 %101, 1
  %107 = icmp eq i64 %106, %61
  br i1 %107, label %108, label %100, !llvm.loop !81

108:                                              ; preds = %109, %100, %96, %81, %50, %41, %32, %16
  store i32 %10, ptr %6, align 8, !tbaa !64
  ret ptr %4

109:                                              ; preds = %109, %96
  %110 = phi i64 [ %126, %109 ], [ %97, %96 ]
  %111 = getelementptr inbounds nuw ptr, ptr %62, i64 %110
  %112 = load ptr, ptr %111, align 8, !tbaa !55
  %113 = getelementptr inbounds nuw ptr, ptr %19, i64 %110
  store ptr %112, ptr %113, align 8, !tbaa !55
  %114 = add nuw nsw i64 %110, 1
  %115 = getelementptr inbounds nuw ptr, ptr %62, i64 %114
  %116 = load ptr, ptr %115, align 8, !tbaa !55
  %117 = getelementptr inbounds nuw ptr, ptr %19, i64 %114
  store ptr %116, ptr %117, align 8, !tbaa !55
  %118 = add nuw nsw i64 %110, 2
  %119 = getelementptr inbounds nuw ptr, ptr %62, i64 %118
  %120 = load ptr, ptr %119, align 8, !tbaa !55
  %121 = getelementptr inbounds nuw ptr, ptr %19, i64 %118
  store ptr %120, ptr %121, align 8, !tbaa !55
  %122 = add nuw nsw i64 %110, 3
  %123 = getelementptr inbounds nuw ptr, ptr %62, i64 %122
  %124 = load ptr, ptr %123, align 8, !tbaa !55
  %125 = getelementptr inbounds nuw ptr, ptr %19, i64 %122
  store ptr %124, ptr %125, align 8, !tbaa !55
  %126 = add nuw nsw i64 %110, 4
  %127 = icmp eq i64 %126, %61
  br i1 %127, label %108, label %109, !llvm.loop !85
}

; Function Attrs: mustprogress uwtable
define dso_local noundef ptr @qc_spread_call(ptr noundef %0, i32 noundef %1, ptr noundef %2, ptr noundef readonly captures(none) %3, i32 noundef %4, ptr noundef returned %5) local_unnamed_addr #21 {
  %7 = alloca %struct.ffi_cif, align 8
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %7) #37
  %8 = sext i32 %1 to i64
  %9 = shl nsw i64 %8, 3
  %10 = tail call noalias ptr @malloc(i64 noundef %9) #36
  %11 = icmp sgt i32 %1, 0
  br i1 %11, label %12, label %32

12:                                               ; preds = %6
  %13 = zext nneg i32 %1 to i64
  %14 = and i64 %13, 1
  %15 = icmp eq i32 %1, 1
  br i1 %15, label %18, label %16

16:                                               ; preds = %12
  %17 = and i64 %13, 2147483646
  br label %35

18:                                               ; preds = %57, %12
  %19 = phi i64 [ 0, %12 ], [ %59, %57 ]
  %20 = icmp eq i64 %14, 0
  br i1 %20, label %32, label %21

21:                                               ; preds = %18
  %22 = getelementptr inbounds nuw i32, ptr %3, i64 %19
  %23 = load i32, ptr %22, align 4, !tbaa !19
  %24 = getelementptr inbounds nuw ptr, ptr %10, i64 %19
  %25 = icmp ult i32 %23, 6
  br i1 %25, label %26, label %30

26:                                               ; preds = %21
  %27 = zext nneg i32 %23 to i64
  %28 = getelementptr inbounds nuw [6 x ptr], ptr @switch.table.qc_spread_call.54, i64 0, i64 %27
  %29 = load ptr, ptr %28, align 8
  br label %30

30:                                               ; preds = %26, %21
  %31 = phi ptr [ %29, %26 ], [ @ffi_type_pointer, %21 ]
  store ptr %31, ptr %24, align 8, !tbaa !86
  br label %32

32:                                               ; preds = %30, %18, %6
  %33 = add i32 %4, 1
  %34 = icmp ult i32 %33, 7
  br i1 %34, label %62, label %66

35:                                               ; preds = %57, %16
  %36 = phi i64 [ 0, %16 ], [ %59, %57 ]
  %37 = phi i64 [ 0, %16 ], [ %60, %57 ]
  %38 = getelementptr inbounds nuw i32, ptr %3, i64 %36
  %39 = load i32, ptr %38, align 4, !tbaa !19
  %40 = getelementptr inbounds nuw ptr, ptr %10, i64 %36
  %41 = icmp ult i32 %39, 6
  br i1 %41, label %42, label %46

42:                                               ; preds = %35
  %43 = zext nneg i32 %39 to i64
  %44 = getelementptr inbounds nuw [6 x ptr], ptr @switch.table.qc_spread_call.54, i64 0, i64 %43
  %45 = load ptr, ptr %44, align 8
  br label %46

46:                                               ; preds = %42, %35
  %47 = phi ptr [ %45, %42 ], [ @ffi_type_pointer, %35 ]
  store ptr %47, ptr %40, align 8, !tbaa !86
  %48 = or disjoint i64 %36, 1
  %49 = getelementptr inbounds nuw i32, ptr %3, i64 %48
  %50 = load i32, ptr %49, align 4, !tbaa !19
  %51 = getelementptr inbounds nuw ptr, ptr %10, i64 %48
  %52 = icmp ult i32 %50, 6
  br i1 %52, label %53, label %57

53:                                               ; preds = %46
  %54 = zext nneg i32 %50 to i64
  %55 = getelementptr inbounds nuw [6 x ptr], ptr @switch.table.qc_spread_call.54, i64 0, i64 %54
  %56 = load ptr, ptr %55, align 8
  br label %57

57:                                               ; preds = %53, %46
  %58 = phi ptr [ %56, %53 ], [ @ffi_type_pointer, %46 ]
  store ptr %58, ptr %51, align 8, !tbaa !86
  %59 = add nuw nsw i64 %36, 2
  %60 = add i64 %37, 2
  %61 = icmp eq i64 %60, %17
  br i1 %61, label %18, label %35, !llvm.loop !88

62:                                               ; preds = %32
  %63 = zext nneg i32 %33 to i64
  %64 = getelementptr inbounds nuw [7 x ptr], ptr @switch.table.qc_spread_call, i64 0, i64 %63
  %65 = load ptr, ptr %64, align 8
  br label %66

66:                                               ; preds = %62, %32
  %67 = phi ptr [ %65, %62 ], [ @ffi_type_pointer, %32 ]
  %68 = call i32 @ffi_prep_cif(ptr noundef nonnull %7, i32 noundef 2, i32 noundef %1, ptr noundef nonnull %67, ptr noundef %10)
  %69 = icmp eq i32 %68, 0
  br i1 %69, label %70, label %71

70:                                               ; preds = %66
  call void @ffi_call(ptr noundef nonnull %7, ptr noundef %0, ptr noundef %5, ptr noundef %2)
  br label %71

71:                                               ; preds = %70, %66
  call void @free(ptr noundef %10) #37
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %7) #37
  ret ptr %5
}

declare i32 @ffi_prep_cif(ptr noundef, i32 noundef, i32 noundef, ptr noundef, ptr noundef) local_unnamed_addr #22

declare void @ffi_call(ptr noundef, ptr noundef, ptr noundef, ptr noundef) local_unnamed_addr #22

; Function Attrs: mustprogress nounwind uwtable
define dso_local ptr @qc_list_to_string(ptr noundef readonly captures(none) %0) local_unnamed_addr #17 {
  %2 = alloca [128 x i8], align 16
  %3 = tail call noalias dereferenceable_or_null(256) ptr @malloc(i64 noundef 256) #36
  %4 = getelementptr inbounds nuw i8, ptr %3, i64 1
  store i8 91, ptr %3, align 1, !tbaa !7
  %5 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %6 = load i32, ptr %5, align 8, !tbaa !64
  %7 = icmp sgt i32 %6, 0
  br i1 %7, label %8, label %10

8:                                                ; preds = %1
  %9 = getelementptr inbounds nuw i8, ptr %0, i64 16
  br label %14

10:                                               ; preds = %109, %1
  %11 = phi ptr [ %4, %1 ], [ %112, %109 ]
  %12 = phi ptr [ %3, %1 ], [ %93, %109 ]
  %13 = getelementptr inbounds nuw i8, ptr %11, i64 1
  store i8 93, ptr %11, align 1, !tbaa !7
  store i8 0, ptr %13, align 1, !tbaa !7
  ret ptr %12

14:                                               ; preds = %109, %8
  %15 = phi i64 [ 0, %8 ], [ %113, %109 ]
  %16 = phi i32 [ 256, %8 ], [ %94, %109 ]
  %17 = phi ptr [ %3, %8 ], [ %93, %109 ]
  %18 = phi ptr [ %4, %8 ], [ %112, %109 ]
  %19 = phi i32 [ 255, %8 ], [ %111, %109 ]
  call void @llvm.lifetime.start.p0(i64 128, ptr nonnull %2) #37
  %20 = load i32, ptr %9, align 8, !tbaa !65
  switch i32 %20, label %73 [
    i32 0, label %21
    i32 1, label %27
    i32 2, label %34
    i32 3, label %40
    i32 4, label %47
    i32 5, label %55
    i32 6, label %68
  ]

21:                                               ; preds = %14
  %22 = load ptr, ptr %0, align 8, !tbaa !66
  %23 = getelementptr inbounds nuw ptr, ptr %22, i64 %15
  %24 = load ptr, ptr %23, align 8, !tbaa !55
  %25 = load i32, ptr %24, align 4, !tbaa !19
  %26 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.33, i32 noundef %25) #37
  br label %73

27:                                               ; preds = %14
  %28 = load ptr, ptr %0, align 8, !tbaa !66
  %29 = getelementptr inbounds nuw ptr, ptr %28, i64 %15
  %30 = load ptr, ptr %29, align 8, !tbaa !55
  %31 = load float, ptr %30, align 4, !tbaa !22
  %32 = fpext float %31 to double
  %33 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.34, double noundef %32) #37
  br label %73

34:                                               ; preds = %14
  %35 = load ptr, ptr %0, align 8, !tbaa !66
  %36 = getelementptr inbounds nuw ptr, ptr %35, i64 %15
  %37 = load ptr, ptr %36, align 8, !tbaa !55
  %38 = load double, ptr %37, align 8, !tbaa !25
  %39 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.34, double noundef %38) #37
  br label %73

40:                                               ; preds = %14
  %41 = load ptr, ptr %0, align 8, !tbaa !66
  %42 = getelementptr inbounds nuw ptr, ptr %41, i64 %15
  %43 = load ptr, ptr %42, align 8, !tbaa !55
  %44 = load i8, ptr %43, align 1, !tbaa !7
  %45 = sext i8 %44 to i32
  %46 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.45, i32 noundef %45) #37
  br label %73

47:                                               ; preds = %14
  %48 = load ptr, ptr %0, align 8, !tbaa !66
  %49 = getelementptr inbounds nuw ptr, ptr %48, i64 %15
  %50 = load ptr, ptr %49, align 8, !tbaa !55
  %51 = load i8, ptr %50, align 1, !tbaa !32, !range !34, !noundef !35
  %52 = trunc nuw i8 %51 to i1
  %53 = select i1 %52, ptr @.str.23, ptr @.str.24
  %54 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.38, ptr noundef nonnull %53) #37
  br label %73

55:                                               ; preds = %14
  %56 = load ptr, ptr %0, align 8, !tbaa !66
  %57 = getelementptr inbounds nuw ptr, ptr %56, i64 %15
  %58 = load ptr, ptr %57, align 8, !tbaa !55
  %59 = load i8, ptr %58, align 1, !tbaa !7
  %60 = and i8 %59, 3
  switch i8 %60, label %61 [
    i8 0, label %65
    i8 1, label %64
  ]

61:                                               ; preds = %55
  %62 = icmp eq i8 %60, 2
  %63 = select i1 %62, ptr @.str.27, ptr @.str.28
  br label %65

64:                                               ; preds = %55
  br label %65

65:                                               ; preds = %64, %61, %55
  %66 = phi ptr [ @.str.25, %55 ], [ %63, %61 ], [ @.str.26, %64 ]
  %67 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.38, ptr noundef nonnull %66) #37
  br label %73

68:                                               ; preds = %14
  %69 = load ptr, ptr %0, align 8, !tbaa !66
  %70 = getelementptr inbounds nuw ptr, ptr %69, i64 %15
  %71 = load ptr, ptr %70, align 8, !tbaa !55
  %72 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.44, ptr noundef %71) #37
  br label %73

73:                                               ; preds = %68, %65, %47, %40, %34, %27, %21, %14
  %74 = call i64 @strlen(ptr noundef nonnull dereferenceable(1) %2) #40
  %75 = trunc i64 %74 to i32
  %76 = add nsw i32 %75, 10
  %77 = icmp slt i32 %19, %76
  br i1 %77, label %78, label %90

78:                                               ; preds = %73
  %79 = ptrtoint ptr %18 to i64
  %80 = ptrtoint ptr %17 to i64
  %81 = sub i64 %79, %80
  %82 = trunc i64 %81 to i32
  %83 = shl nsw i32 %16, 1
  %84 = sext i32 %83 to i64
  %85 = tail call ptr @realloc(ptr noundef %17, i64 noundef %84) #38
  %86 = shl i64 %81, 32
  %87 = ashr exact i64 %86, 32
  %88 = getelementptr inbounds i8, ptr %85, i64 %87
  %89 = sub nsw i32 %83, %82
  br label %90

90:                                               ; preds = %78, %73
  %91 = phi i32 [ %89, %78 ], [ %19, %73 ]
  %92 = phi ptr [ %88, %78 ], [ %18, %73 ]
  %93 = phi ptr [ %85, %78 ], [ %17, %73 ]
  %94 = phi i32 [ %83, %78 ], [ %16, %73 ]
  %95 = call ptr @strcpy(ptr noundef nonnull dereferenceable(1) %92, ptr noundef nonnull dereferenceable(1) %2) #37
  %96 = shl i64 %74, 32
  %97 = ashr exact i64 %96, 32
  %98 = getelementptr inbounds i8, ptr %92, i64 %97
  %99 = sub nsw i32 %91, %75
  %100 = load i32, ptr %5, align 8, !tbaa !64
  %101 = add nsw i32 %100, -1
  %102 = sext i32 %101 to i64
  %103 = icmp slt i64 %15, %102
  br i1 %103, label %104, label %109

104:                                              ; preds = %90
  %105 = getelementptr inbounds nuw i8, ptr %98, i64 1
  store i8 44, ptr %98, align 1, !tbaa !7
  %106 = getelementptr inbounds nuw i8, ptr %98, i64 2
  store i8 32, ptr %105, align 1, !tbaa !7
  %107 = add nsw i32 %99, -2
  %108 = load i32, ptr %5, align 8, !tbaa !64
  br label %109

109:                                              ; preds = %104, %90
  %110 = phi i32 [ %108, %104 ], [ %100, %90 ]
  %111 = phi i32 [ %107, %104 ], [ %99, %90 ]
  %112 = phi ptr [ %106, %104 ], [ %98, %90 ]
  call void @llvm.lifetime.end.p0(i64 128, ptr nonnull %2) #37
  %113 = add nuw nsw i64 %15, 1
  %114 = sext i32 %110 to i64
  %115 = icmp slt i64 %113, %114
  br i1 %115, label %14, label %10, !llvm.loop !89
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_fopen(ptr noundef readonly captures(none) %0, ptr noundef readonly captures(none) %1) local_unnamed_addr #6 {
  %3 = tail call noalias ptr @fopen(ptr noundef %0, ptr noundef %1)
  ret ptr %3
}

; Function Attrs: nofree nounwind
declare noalias noundef ptr @fopen(ptr noundef readonly captures(none), ptr noundef readonly captures(none)) local_unnamed_addr #8

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_fclose(ptr noundef captures(address_is_null) %0) local_unnamed_addr #6 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %5, label %3

3:                                                ; preds = %1
  %4 = tail call i32 @fclose(ptr noundef nonnull %0)
  br label %5

5:                                                ; preds = %3, %1
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @fclose(ptr noundef captures(none)) local_unnamed_addr #8

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias ptr @qc_fread(ptr noundef captures(address_is_null) %0) local_unnamed_addr #6 {
  %2 = alloca [1024 x i8], align 16
  %3 = icmp eq ptr %0, null
  br i1 %3, label %4, label %6

4:                                                ; preds = %1
  %5 = tail call noalias dereferenceable_or_null(1) ptr @strdup(ptr noundef nonnull @.str.2) #37
  br label %21

6:                                                ; preds = %1
  call void @llvm.lifetime.start.p0(i64 1024, ptr nonnull %2) #37
  %7 = call ptr @fgets(ptr noundef nonnull %2, i32 noundef 1024, ptr noundef nonnull %0)
  %8 = icmp eq ptr %7, null
  br i1 %8, label %18, label %9

9:                                                ; preds = %6
  %10 = call i64 @strlen(ptr noundef nonnull dereferenceable(1) %2) #40
  %11 = icmp eq i64 %10, 0
  br i1 %11, label %18, label %12

12:                                               ; preds = %9
  %13 = add i64 %10, -1
  %14 = getelementptr inbounds nuw [1024 x i8], ptr %2, i64 0, i64 %13
  %15 = load i8, ptr %14, align 1, !tbaa !7
  %16 = icmp eq i8 %15, 10
  br i1 %16, label %17, label %18

17:                                               ; preds = %12
  store i8 0, ptr %14, align 1, !tbaa !7
  br label %18

18:                                               ; preds = %17, %12, %9, %6
  %19 = phi ptr [ %2, %17 ], [ %2, %12 ], [ %2, %9 ], [ @.str.2, %6 ]
  %20 = call noalias ptr @strdup(ptr noundef nonnull %19) #37
  call void @llvm.lifetime.end.p0(i64 1024, ptr nonnull %2) #37
  br label %21

21:                                               ; preds = %18, %4
  %22 = phi ptr [ %20, %18 ], [ %5, %4 ]
  ret ptr %22
}

; Function Attrs: nofree nounwind
declare noundef ptr @fgets(ptr noundef writeonly, i32 noundef, ptr noundef captures(none)) local_unnamed_addr #8

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_fwrite(ptr noundef captures(address_is_null) %0, ptr noundef readonly captures(address_is_null) %1) local_unnamed_addr #6 {
  %3 = icmp ne ptr %0, null
  %4 = icmp ne ptr %1, null
  %5 = and i1 %3, %4
  br i1 %5, label %6, label %9

6:                                                ; preds = %2
  %7 = tail call i32 @fputs(ptr noundef nonnull %1, ptr noundef nonnull %0)
  %8 = tail call i32 @fputc(i32 noundef 10, ptr noundef nonnull %0)
  br label %9

9:                                                ; preds = %6, %2
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @fputc(i32 noundef, ptr noundef captures(none)) local_unnamed_addr #8

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
define dso_local zeroext i1 @qc_variadic_is_empty(ptr noundef readonly captures(none) %0) local_unnamed_addr #26 {
  %2 = getelementptr inbounds nuw i8, ptr %0, i64 12
  %3 = load i32, ptr %2, align 4, !tbaa !90
  %4 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %5 = load i32, ptr %4, align 8, !tbaa !92
  %6 = icmp sge i32 %3, %5
  ret i1 %6
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(read, argmem: readwrite, inaccessiblemem: none) uwtable
define dso_local ptr @qc_variadic_next(ptr noundef captures(none) %0) local_unnamed_addr #33 {
  %2 = getelementptr inbounds nuw i8, ptr %0, i64 12
  %3 = load i32, ptr %2, align 4, !tbaa !90
  %4 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %5 = load i32, ptr %4, align 8, !tbaa !92
  %6 = icmp slt i32 %3, %5
  br i1 %6, label %7, label %13

7:                                                ; preds = %1
  %8 = load ptr, ptr %0, align 8, !tbaa !93
  %9 = sext i32 %3 to i64
  %10 = getelementptr inbounds ptr, ptr %8, i64 %9
  %11 = load ptr, ptr %10, align 8, !tbaa !55
  %12 = add nsw i32 %3, 1
  store i32 %12, ptr %2, align 4, !tbaa !90
  br label %13

13:                                               ; preds = %7, %1
  %14 = phi ptr [ %11, %7 ], [ null, %1 ]
  ret ptr %14
}

define void @Warrior_Warrior(ptr %0, i32 %1) {
entry:
  %hp = alloca i32, align 4
  store i32 %1, ptr %hp, align 4
  %hp1 = load i32, ptr %hp, align 4
  %2 = getelementptr inbounds nuw %Warrior, ptr %0, i32 0, i32 0
  store i32 %hp1, ptr %2, align 4
  ret void
}

define void @Node2_Node2(ptr %0, i32 %1, ptr %2) {
entry:
  %next = alloca ptr, align 8
  %val = alloca i32, align 4
  store i32 %1, ptr %val, align 4
  store ptr %2, ptr %next, align 8
  %next1 = load ptr, ptr %next, align 8
  %3 = getelementptr inbounds nuw %Node2, ptr %0, i32 0, i32 1
  store ptr %next1, ptr %3, align 8
  %val2 = load i32, ptr %val, align 4
  %4 = getelementptr inbounds nuw %Node2, ptr %0, i32 0, i32 0
  store i32 %val2, ptr %4, align 4
  ret void
}

define void @Node_Node(ptr %0, i32 %1) {
entry:
  %val = alloca i32, align 4
  store i32 %1, ptr %val, align 4
  %val1 = load i32, ptr %val, align 4
  %2 = getelementptr inbounds nuw %Node, ptr %0, i32 0, i32 0
  store i32 %val1, ptr %2, align 4
  %3 = getelementptr inbounds nuw %Node, ptr %0, i32 0, i32 1
  store ptr null, ptr %3, align 8
  ret void
}

define i32 @Node_setNext(ptr %0, ptr %1) {
entry:
  %n = alloca ptr, align 8
  store ptr %1, ptr %n, align 8
  %n1 = load ptr, ptr %n, align 8
  %2 = getelementptr inbounds nuw %Node, ptr %0, i32 0, i32 1
  store ptr %n1, ptr %2, align 8
  ret i32 0
}

define void @Refs_Refs(ptr %0, i32 %1) {
entry:
  %x = alloca i32, align 4
  store i32 %1, ptr %x, align 4
  %x1 = load i32, ptr %x, align 4
  %2 = getelementptr inbounds nuw %Refs, ptr %0, i32 0, i32 0
  store i32 %x1, ptr %2, align 4
  ret void
}

define i32 @Refs_getX(ptr %0, ptr %1) {
entry:
  %y = alloca ptr, align 8
  store ptr %1, ptr %y, align 8
  %2 = load ptr, ptr %y, align 8
  %assign_lhs_val = load i32, ptr %2, align 4
  %3 = getelementptr inbounds nuw %Refs, ptr %0, i32 0, i32 0
  %x = load i32, ptr %3, align 4
  store i32 %x, ptr %2, align 4
  ret i32 0
}

define i32 @Refs_setXp1(ptr %0, ptr %1) {
entry:
  %t = alloca ptr, align 8
  store ptr %1, ptr %t, align 8
  %2 = load ptr, ptr %t, align 8
  %assign_lhs_val = load i32, ptr %2, align 4
  %add = add i32 %assign_lhs_val, 1
  store i32 %add, ptr %2, align 4
  %3 = load ptr, ptr %t, align 8
  %t1 = load i32, ptr %3, align 4
  %4 = getelementptr inbounds nuw %Refs, ptr %0, i32 0, i32 0
  store i32 %t1, ptr %4, align 4
  ret i32 0
}

declare i32 @Refs_autoRet(ptr, ptr, i32)

define i32 @Refs_variadicMethod(ptr %0, i32 %1, ptr %2) {
entry:
  %i = alloca i32, align 4
  %var = alloca ptr, align 8
  %c = alloca i32, align 4
  store i32 %1, ptr %c, align 4
  store ptr %2, ptr %var, align 8
  store i32 0, ptr %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %i1 = load i32, ptr %i, align 4
  %c2 = load i32, ptr %c, align 4
  %icmplt = icmp slt i32 %i1, %c2
  br i1 %icmplt, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %variad = load ptr, ptr %var, align 8
  %variadc_arg = call ptr @qc_variadic_next(ptr %variad)
  %vararg_int = ptrtoint ptr %variadc_arg to i32
  %3 = sext i32 %vararg_int to i64
  call void @qc_print_string(ptr @23)
  %4 = call ptr @qc_fmt_int(i64 %3, i32 -1, i32 -1, i1 false)
  call void @qc_print_string(ptr %4)
  call void @qc_print_string(ptr @24)
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %assign_lhs_val = load i32, ptr %i, align 4
  %i3 = load i32, ptr %i, align 4
  %i4 = load i32, ptr %i, align 4
  %inc = add i32 %i4, 1
  store i32 %inc, ptr %i, align 4
  store i32 %inc, ptr %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret i32 0
}

define ptr @"Refs_operator="(ptr %0, %Refs %1) {
entry:
  %temp_obj = alloca %Refs, align 8
  %other = alloca %Refs, align 8
  store %Refs %1, ptr %other, align 4
  %other1 = load %Refs, ptr %other, align 4
  store %Refs %other1, ptr %temp_obj, align 4
  %2 = getelementptr inbounds nuw %Refs, ptr %temp_obj, i32 0, i32 0
  %x = load i32, ptr %2, align 4
  %3 = getelementptr inbounds nuw %Refs, ptr %0, i32 0, i32 0
  store i32 %x, ptr %3, align 4
  ret ptr %0
}

define void @"UnitTest::Test_Test"(ptr %0, i32 %1) {
entry:
  %Ttl = alloca i32, align 4
  store i32 %1, ptr %Ttl, align 4
  %2 = call ptr @qc_create_list(i32 6)
  %3 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 4
  store ptr %2, ptr %3, align 8
  %Ttl1 = load i32, ptr %Ttl, align 4
  %4 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 0
  store i32 %Ttl1, ptr %4, align 4
  %5 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 1
  store i32 0, ptr %5, align 4
  %6 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 2
  store i32 0, ptr %6, align 4
  %7 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 3
  store i32 0, ptr %7, align 4
  ret void
}

define i32 @"UnitTest::Test_Check"(ptr %0) {
entry:
  %message = alloca ptr, align 8
  %__foreach_i_message = alloca i32, align 4
  %1 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 1
  %Ran = load i32, ptr %1, align 4
  %2 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 0
  %Total = load i32, ptr %2, align 4
  %icmpge = icmp sge i32 %Ran, %Total
  br i1 %icmpge, label %then, label %ifcont

then:                                             ; preds = %entry
  %3 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 1
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 4
  %Messages = load ptr, ptr %4, align 8
  %list_len = call i32 @qc_list_length(ptr %Messages)
  %icmpgt = icmp sgt i32 %list_len, 0
  br i1 %icmpgt, label %then1, label %ifcont2

ifcont:                                           ; preds = %ifcont14, %entry
  ret i32 0

then1:                                            ; preds = %then
  %5 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 4
  %Messages3 = load ptr, ptr %5, align 8
  %coll_len = call i32 @qc_list_length(ptr %Messages3)
  store i32 0, ptr %__foreach_i_message, align 4
  br label %foreach.cond

ifcont2:                                          ; preds = %foreach.end, %then
  %6 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 3
  %Failed = load i32, ptr %6, align 4
  %fstr_i32 = call ptr @qc_to_string_int(i32 %Failed)
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.104, ptr %fstr_i32)
  %fstr_concat7 = call ptr @qc_string_concat(ptr %fstr_concat, ptr @.str.105)
  call void @qc_print_string(ptr @29)
  %7 = call ptr @qc_fmt_string(ptr %fstr_concat7, i32 -1, i1 false)
  call void @qc_print_string(ptr %7)
  call void @qc_print_string(ptr @30)
  %8 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 2
  %Passed = load i32, ptr %8, align 4
  %fstr_i328 = call ptr @qc_to_string_int(i32 %Passed)
  %fstr_concat9 = call ptr @qc_string_concat(ptr @.str.107, ptr %fstr_i328)
  %fstr_concat10 = call ptr @qc_string_concat(ptr %fstr_concat9, ptr @.str.108)
  call void @qc_print_string(ptr @31)
  %9 = call ptr @qc_fmt_string(ptr %fstr_concat10, i32 -1, i1 false)
  call void @qc_print_string(ptr %9)
  call void @qc_print_string(ptr @32)
  call void @qc_print_string(ptr @33)
  %10 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 3
  %Failed11 = load i32, ptr %10, align 4
  %icmpgt12 = icmp sgt i32 %Failed11, 0
  br i1 %icmpgt12, label %then13, label %else

foreach.cond:                                     ; preds = %foreach.inc, %then1
  %__foreach_i_message4 = load i32, ptr %__foreach_i_message, align 4
  %foreach_cmp = icmp slt i32 %__foreach_i_message4, %coll_len
  br i1 %foreach_cmp, label %foreach.body, label %foreach.end

foreach.body:                                     ; preds = %foreach.cond
  %elem_ptr = call ptr @qc_list_get(ptr %Messages3, i32 %__foreach_i_message4)
  store ptr %elem_ptr, ptr %message, align 8
  call void @qc_print_string(ptr @25)
  %message5 = load ptr, ptr %message, align 8
  call void @qc_print_string(ptr @26)
  %11 = call ptr @qc_fmt_string(ptr %message5, i32 -1, i1 false)
  call void @qc_print_string(ptr %11)
  call void @qc_print_string(ptr @27)
  br label %foreach.inc

foreach.inc:                                      ; preds = %foreach.body
  %__foreach_i_message6 = load i32, ptr %__foreach_i_message, align 4
  %i_inc = add i32 %__foreach_i_message6, 1
  store i32 %i_inc, ptr %__foreach_i_message, align 4
  br label %foreach.cond

foreach.end:                                      ; preds = %foreach.cond
  call void @qc_print_string(ptr @28)
  br label %ifcont2

then13:                                           ; preds = %ifcont2
  call void @qc_print_string(ptr @34)
  br label %ifcont14

ifcont14:                                         ; preds = %else, %then13
  br label %ifcont

else:                                             ; preds = %ifcont2
  call void @qc_print_string(ptr @35)
  br label %ifcont14
}

define i32 @"UnitTest::Test_Success"(ptr %0, ptr %1) {
entry:
  %push_arg = alloca ptr, align 8
  %message = alloca ptr, align 8
  store ptr %1, ptr %message, align 8
  %2 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 1
  %Ran = load i32, ptr %2, align 4
  %add = add i32 %Ran, 1
  %3 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 1
  store i32 %add, ptr %3, align 4
  %4 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 2
  %Passed = load i32, ptr %4, align 4
  %add1 = add i32 %Passed, 1
  %5 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 2
  store i32 %add1, ptr %5, align 4
  %6 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 4
  %ptr_ld = load ptr, ptr %6, align 8
  %message2 = load ptr, ptr %message, align 8
  %7 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 1
  %Ran3 = load i32, ptr %7, align 4
  %fstr_i32 = call ptr @qc_to_string_int(i32 %Ran3)
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.112, ptr %fstr_i32)
  %fstr_concat4 = call ptr @qc_string_concat(ptr %fstr_concat, ptr @.str.113)
  %8 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 0
  %Total = load i32, ptr %8, align 4
  %fstr_i325 = call ptr @qc_to_string_int(i32 %Total)
  %fstr_concat6 = call ptr @qc_string_concat(ptr %fstr_concat4, ptr %fstr_i325)
  %fstr_concat7 = call ptr @qc_string_concat(ptr %fstr_concat6, ptr @.str.114)
  %str_concat = call ptr @qc_string_concat(ptr %message2, ptr %fstr_concat7)
  store ptr %str_concat, ptr %push_arg, align 8
  call void @qc_list_push(ptr %ptr_ld, ptr %push_arg, i32 6)
  %Check_result = call i32 @"UnitTest::Test_Check"(ptr %0)
  ret i32 0
}

define i32 @"UnitTest::Test_Fail"(ptr %0, ptr %1) {
entry:
  %push_arg = alloca ptr, align 8
  %message = alloca ptr, align 8
  store ptr %1, ptr %message, align 8
  %2 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 1
  %Ran = load i32, ptr %2, align 4
  %add = add i32 %Ran, 1
  %3 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 1
  store i32 %add, ptr %3, align 4
  %4 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 3
  %Failed = load i32, ptr %4, align 4
  %add1 = add i32 %Failed, 1
  %5 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 3
  store i32 %add1, ptr %5, align 4
  %6 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 4
  %ptr_ld = load ptr, ptr %6, align 8
  %message2 = load ptr, ptr %message, align 8
  %7 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 1
  %Ran3 = load i32, ptr %7, align 4
  %fstr_i32 = call ptr @qc_to_string_int(i32 %Ran3)
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.115, ptr %fstr_i32)
  %fstr_concat4 = call ptr @qc_string_concat(ptr %fstr_concat, ptr @.str.116)
  %8 = getelementptr inbounds nuw %"UnitTest::Test", ptr %0, i32 0, i32 0
  %Total = load i32, ptr %8, align 4
  %fstr_i325 = call ptr @qc_to_string_int(i32 %Total)
  %fstr_concat6 = call ptr @qc_string_concat(ptr %fstr_concat4, ptr %fstr_i325)
  %fstr_concat7 = call ptr @qc_string_concat(ptr %fstr_concat6, ptr @.str.117)
  %str_concat = call ptr @qc_string_concat(ptr %message2, ptr %fstr_concat7)
  store ptr %str_concat, ptr %push_arg, align 8
  call void @qc_list_push(ptr %ptr_ld, ptr %push_arg, i32 6)
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
  %4 = call i1 @qc_string_eq(ptr %Call2, ptr @.str.118)
  %5 = xor i1 %4, true
  br i1 %5, label %then3, label %else5

ifcont:                                           ; preds = %ifcont15, %ifcont4
  ret i32 0

else:                                             ; preds = %entry
  %Call13 = load ptr, ptr %Call, align 8
  %6 = call i1 @qc_string_eq(ptr %Call13, ptr @.str.122)
  %7 = xor i1 %6, true
  br i1 %7, label %then14, label %else16

then3:                                            ; preds = %then
  %Call6 = load ptr, ptr %Call, align 8
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.119, ptr %Call6)
  %fstr_concat7 = call ptr @qc_string_concat(ptr %fstr_concat, ptr @.str.120)
  %FailMessage8 = load ptr, ptr %FailMessage, align 8
  %fstr_concat9 = call ptr @qc_string_concat(ptr %fstr_concat7, ptr %FailMessage8)
  %Fail_result = call i32 @"UnitTest::Test_Fail"(ptr %0, ptr %fstr_concat9)
  br label %ifcont4

ifcont4:                                          ; preds = %else5, %then3
  br label %ifcont

else5:                                            ; preds = %then
  %FailMessage10 = load ptr, ptr %FailMessage, align 8
  %fstr_concat11 = call ptr @qc_string_concat(ptr @.str.121, ptr %FailMessage10)
  %Fail_result12 = call i32 @"UnitTest::Test_Fail"(ptr %0, ptr %fstr_concat11)
  br label %ifcont4

then14:                                           ; preds = %else
  %Call17 = load ptr, ptr %Call, align 8
  %fstr_concat18 = call ptr @qc_string_concat(ptr @.str.123, ptr %Call17)
  %fstr_concat19 = call ptr @qc_string_concat(ptr %fstr_concat18, ptr @.str.124)
  %Success_result = call i32 @"UnitTest::Test_Success"(ptr %0, ptr %fstr_concat19)
  br label %ifcont15

ifcont15:                                         ; preds = %else16, %then14
  br label %ifcont

else16:                                           ; preds = %else
  %Success_result20 = call i32 @"UnitTest::Test_Success"(ptr %0, ptr @.str.125)
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
  %4 = call i1 @qc_string_eq(ptr %Call2, ptr @.str.126)
  %5 = xor i1 %4, true
  br i1 %5, label %then3, label %else5

ifcont:                                           ; preds = %ifcont15, %ifcont4
  ret i32 0

else:                                             ; preds = %entry
  %Call13 = load ptr, ptr %Call, align 8
  %6 = call i1 @qc_string_eq(ptr %Call13, ptr @.str.130)
  %7 = xor i1 %6, true
  br i1 %7, label %then14, label %else16

then3:                                            ; preds = %then
  %Call6 = load ptr, ptr %Call, align 8
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.127, ptr %Call6)
  %fstr_concat7 = call ptr @qc_string_concat(ptr %fstr_concat, ptr @.str.128)
  %FailMessage8 = load ptr, ptr %FailMessage, align 8
  %fstr_concat9 = call ptr @qc_string_concat(ptr %fstr_concat7, ptr %FailMessage8)
  %Fail_result = call i32 @"UnitTest::Test_Fail"(ptr %0, ptr %fstr_concat9)
  br label %ifcont4

ifcont4:                                          ; preds = %else5, %then3
  br label %ifcont

else5:                                            ; preds = %then
  %FailMessage10 = load ptr, ptr %FailMessage, align 8
  %fstr_concat11 = call ptr @qc_string_concat(ptr @.str.129, ptr %FailMessage10)
  %Fail_result12 = call i32 @"UnitTest::Test_Fail"(ptr %0, ptr %fstr_concat11)
  br label %ifcont4

then14:                                           ; preds = %else
  %Call17 = load ptr, ptr %Call, align 8
  %fstr_concat18 = call ptr @qc_string_concat(ptr @.str.131, ptr %Call17)
  %fstr_concat19 = call ptr @qc_string_concat(ptr %fstr_concat18, ptr @.str.132)
  %Success_result = call i32 @"UnitTest::Test_Success"(ptr %0, ptr %fstr_concat19)
  br label %ifcont15

ifcont15:                                         ; preds = %else16, %then14
  br label %ifcont

else16:                                           ; preds = %else
  %Success_result20 = call i32 @"UnitTest::Test_Success"(ptr %0, ptr @.str.133)
  br label %ifcont15
}

declare i32 @"UnitTest::Test_AssertNotEqual"(ptr, i32, i32, ptr, ptr)

define ptr @Point_repr(%Point %0) {
entry:
  %1 = call ptr @qc_string_concat(ptr @0, ptr @1)
  %2 = extractvalue %Point %0, 0
  %3 = call ptr @qc_to_string_int(i32 %2)
  %4 = call ptr @qc_string_concat(ptr %1, ptr %3)
  %5 = call ptr @qc_string_concat(ptr %4, ptr @2)
  %6 = call ptr @qc_string_concat(ptr %5, ptr @3)
  %7 = extractvalue %Point %0, 1
  %8 = call ptr @qc_to_string_int(i32 %7)
  %9 = call ptr @qc_string_concat(ptr %6, ptr %8)
  %10 = call ptr @qc_string_concat(ptr %9, ptr @4)
  ret ptr %10
}

define i32 @add(ptr %x, i32 %y) {
entry:
  %y2 = alloca i32, align 4
  %x1 = alloca ptr, align 8
  store ptr %x, ptr %x1, align 8
  store i32 %y, ptr %y2, align 4
  %0 = load ptr, ptr %x1, align 8
  %assign_lhs_val = load i32, ptr %0, align 4
  %y3 = load i32, ptr %y2, align 4
  %add = add i32 %assign_lhs_val, %y3
  store i32 %add, ptr %0, align 4
  ret i32 0
}

define i32 @addToX(ptr %x, i32 %y) {
entry:
  %y2 = alloca i32, align 4
  %x1 = alloca ptr, align 8
  store ptr %x, ptr %x1, align 8
  store i32 %y, ptr %y2, align 4
  %0 = load ptr, ptr %x1, align 8
  %x3 = load %Point, ptr %0, align 4
  %x4 = extractvalue %Point %x3, 0
  %y5 = load i32, ptr %y2, align 4
  %add = add i32 %x4, %y5
  %1 = load ptr, ptr %x1, align 8
  %x_ptr = getelementptr inbounds nuw %Point, ptr %1, i32 0, i32 0
  %2 = load ptr, ptr %x1, align 8
  %x6 = load %Point, ptr %2, align 4
  %x7 = extractvalue %Point %x6, 0
  %y8 = load i32, ptr %y2, align 4
  %add9 = add i32 %x7, %y8
  store i32 %add9, ptr %x_ptr, align 4
  ret i32 0
}

define i32 @increment(ptr %p) {
entry:
  %p1 = alloca ptr, align 8
  store ptr %p, ptr %p1, align 8
  %p2 = load ptr, ptr %p1, align 8
  %assign_lhs_val = load i32, ptr %p2, align 4
  %p3 = load ptr, ptr %p1, align 8
  %p4 = load ptr, ptr %p1, align 8
  %deref = load i32, ptr %p4, align 4
  %add = add i32 %deref, 1
  store i32 %add, ptr %p2, align 4
  ret i32 0
}

define i32 @swap(ptr %a, ptr %b) {
entry:
  %temp = alloca i32, align 4
  %b2 = alloca ptr, align 8
  %a1 = alloca ptr, align 8
  store ptr %a, ptr %a1, align 8
  store ptr %b, ptr %b2, align 8
  %0 = load ptr, ptr %a1, align 8
  %a3 = load i32, ptr %0, align 4
  store i32 %a3, ptr %temp, align 4
  %1 = load ptr, ptr %a1, align 8
  %assign_lhs_val = load i32, ptr %1, align 4
  %2 = load ptr, ptr %b2, align 8
  %b4 = load i32, ptr %2, align 4
  store i32 %b4, ptr %1, align 4
  %3 = load ptr, ptr %b2, align 8
  %assign_lhs_val5 = load i32, ptr %3, align 4
  %temp6 = load i32, ptr %temp, align 4
  store i32 %temp6, ptr %3, align 4
  ret i32 0
}

define i32 @autoPointer(ptr %p) {
entry:
  %p1 = alloca ptr, align 8
  store ptr %p, ptr %p1, align 8
  %p2 = load ptr, ptr %p1, align 8
  %assign_lhs_val = load i32, ptr %p2, align 4
  %p3 = load ptr, ptr %p1, align 8
  %p4 = load ptr, ptr %p1, align 8
  %deref = load i32, ptr %p4, align 4
  %mul = mul i32 %deref, 2
  store i32 %mul, ptr %p2, align 4
  ret i32 0
}

define i32 @TESTESTESTESTESTEST() {
entry:
  %ptr_ptr_ptr = alloca ptr, align 8
  %ptr_ptr = alloca ptr, align 8
  %ptr = alloca ptr, align 8
  %temp_obj23 = alloca %Node, align 8
  %temp_obj20 = alloca %Node, align 8
  %temp_obj16 = alloca %Node, align 8
  %nextVal = alloca i32, align 4
  %temp_obj = alloca %Node, align 8
  %temp = alloca ptr, align 8
  %n2 = alloca %Node, align 8
  %n1 = alloca %Node, align 8
  %magic = alloca i32, align 4
  %y = alloca i32, align 4
  %x = alloca i32, align 4
  %val = alloca i32, align 4
  %test = alloca %"UnitTest::Test", align 8
  call void @"UnitTest::Test_Test"(ptr %test, i32 6)
  store i32 10, ptr %val, align 4
  %val1 = load i32, ptr %val, align 4
  %calltmp = call i32 @increment(ptr %val)
  %val2 = load i32, ptr %val, align 4
  %AssertEqual_result = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %test, i32 11, i32 %val2, ptr @.str.57, ptr @.str.58)
  store i32 1, ptr %x, align 4
  store i32 2, ptr %y, align 4
  %calltmp3 = call i32 @swap(ptr %x, ptr %y)
  %x4 = load i32, ptr %x, align 4
  %AssertEqual_result5 = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %test, i32 2, i32 %x4, ptr @.str.59, ptr @.str.60)
  %y6 = load i32, ptr %y, align 4
  %AssertEqual_result7 = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %test, i32 1, i32 %y6, ptr @.str.61, ptr @.str.62)
  store i32 50, ptr %magic, align 4
  %magic8 = load i32, ptr %magic, align 4
  %calltmp9 = call i32 @autoPointer(ptr %magic)
  %magic10 = load i32, ptr %magic, align 4
  %AssertEqual_result11 = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %test, i32 100, i32 %magic10, ptr @.str.63, ptr @.str.64)
  call void @Node_Node(ptr %n1, i32 10)
  call void @Node_Node(ptr %n2, i32 20)
  %n212 = load %Node, ptr %n2, align 8
  %setNext_result = call i32 @Node_setNext(ptr %n1, ptr %n2)
  %n113 = load %Node, ptr %n1, align 8
  store %Node %n113, ptr %temp_obj, align 8
  %0 = getelementptr inbounds nuw %Node, ptr %temp_obj, i32 0, i32 1
  %next = load ptr, ptr %0, align 8
  store ptr %next, ptr %temp, align 8
  %temp14 = load ptr, ptr %temp, align 8
  %temp15 = load ptr, ptr %temp, align 8
  %deref = load %Node, ptr %temp15, align 8
  store %Node %deref, ptr %temp_obj16, align 8
  %1 = getelementptr inbounds nuw %Node, ptr %temp_obj16, i32 0, i32 0
  %value = load i32, ptr %1, align 4
  store i32 %value, ptr %nextVal, align 4
  %nextVal17 = load i32, ptr %nextVal, align 4
  %AssertEqual_result18 = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %test, i32 20, i32 %nextVal17, ptr @.str.65, ptr @.str.66)
  %n119 = load %Node, ptr %n1, align 8
  store %Node %n119, ptr %temp_obj20, align 8
  %2 = getelementptr inbounds nuw %Node, ptr %temp_obj20, i32 0, i32 1
  %next21 = load ptr, ptr %2, align 8
  %value_ptr = getelementptr inbounds nuw %Node, ptr %next21, i32 0, i32 0
  store i32 42, ptr %value_ptr, align 4
  %n222 = load %Node, ptr %n2, align 8
  store %Node %n222, ptr %temp_obj23, align 8
  %3 = getelementptr inbounds nuw %Node, ptr %temp_obj23, i32 0, i32 0
  %value24 = load i32, ptr %3, align 4
  %AssertEqual_result25 = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %test, i32 42, i32 %value24, ptr @.str.67, ptr @.str.68)
  store ptr null, ptr %ptr, align 8
  store ptr null, ptr %ptr_ptr, align 8
  store ptr null, ptr %ptr_ptr_ptr, align 8
  %assign_lhs_val = load ptr, ptr %ptr, align 8
  %x26 = load i32, ptr %x, align 4
  store ptr %x, ptr %ptr, align 8
  %assign_lhs_val27 = load ptr, ptr %ptr_ptr, align 8
  %ptr28 = load ptr, ptr %ptr, align 8
  store ptr %ptr, ptr %ptr_ptr, align 8
  %assign_lhs_val29 = load ptr, ptr %ptr_ptr_ptr, align 8
  %ptr_ptr30 = load ptr, ptr %ptr_ptr, align 8
  store ptr %ptr_ptr, ptr %ptr_ptr_ptr, align 8
  %ptr_ptr_ptr31 = load ptr, ptr %ptr_ptr_ptr, align 8
  call void @qc_print_string(ptr @5)
  %4 = call ptr @qc_fmt_ptr(ptr %ptr_ptr_ptr31, i32 -1, i1 false)
  call void @qc_print_string(ptr %4)
  %ptr_ptr_ptr32 = load ptr, ptr %ptr_ptr_ptr, align 8
  %ptr_ptr_ptr33 = load ptr, ptr %ptr_ptr_ptr, align 8
  %deref34 = load ptr, ptr %ptr_ptr_ptr33, align 8
  call void @qc_print_string(ptr @6)
  %5 = call ptr @qc_fmt_ptr(ptr %deref34, i32 -1, i1 false)
  call void @qc_print_string(ptr %5)
  %ptr_ptr_ptr35 = load ptr, ptr %ptr_ptr_ptr, align 8
  %ptr_ptr_ptr36 = load ptr, ptr %ptr_ptr_ptr, align 8
  %deref37 = load ptr, ptr %ptr_ptr_ptr36, align 8
  %ptr_ptr_ptr38 = load ptr, ptr %ptr_ptr_ptr, align 8
  %ptr_ptr_ptr39 = load ptr, ptr %ptr_ptr_ptr, align 8
  %deref40 = load ptr, ptr %ptr_ptr_ptr39, align 8
  %deref41 = load ptr, ptr %deref40, align 8
  call void @qc_print_string(ptr @7)
  %6 = call ptr @qc_fmt_ptr(ptr %deref41, i32 -1, i1 false)
  call void @qc_print_string(ptr %6)
  %ptr_ptr_ptr42 = load ptr, ptr %ptr_ptr_ptr, align 8
  %ptr_ptr_ptr43 = load ptr, ptr %ptr_ptr_ptr, align 8
  %deref44 = load ptr, ptr %ptr_ptr_ptr43, align 8
  %ptr_ptr_ptr45 = load ptr, ptr %ptr_ptr_ptr, align 8
  %ptr_ptr_ptr46 = load ptr, ptr %ptr_ptr_ptr, align 8
  %deref47 = load ptr, ptr %ptr_ptr_ptr46, align 8
  %deref48 = load ptr, ptr %deref47, align 8
  %ptr_ptr_ptr49 = load ptr, ptr %ptr_ptr_ptr, align 8
  %ptr_ptr_ptr50 = load ptr, ptr %ptr_ptr_ptr, align 8
  %deref51 = load ptr, ptr %ptr_ptr_ptr50, align 8
  %ptr_ptr_ptr52 = load ptr, ptr %ptr_ptr_ptr, align 8
  %ptr_ptr_ptr53 = load ptr, ptr %ptr_ptr_ptr, align 8
  %deref54 = load ptr, ptr %ptr_ptr_ptr53, align 8
  %deref55 = load ptr, ptr %deref54, align 8
  %deref56 = load i32, ptr %deref55, align 4
  %7 = sext i32 %deref56 to i64
  call void @qc_print_string(ptr @8)
  %8 = call ptr @qc_fmt_int(i64 %7, i32 -1, i32 -1, i1 false)
  call void @qc_print_string(ptr %8)
  call void @qc_print_string(ptr @9)
  ret i32 0
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
  %1 = call i1 @qc_string_eq(ptr %Call7, ptr @.str.37)
  %2 = xor i1 %1, true
  br i1 %2, label %then8, label %else10

ifcont:                                           ; preds = %ifcont35, %ifcont9
  ret i32 0

else:                                             ; preds = %entry
  %Call33 = load ptr, ptr %Call, align 8
  %3 = call i1 @qc_string_eq(ptr %Call33, ptr @.str.51)
  %4 = xor i1 %3, true
  br i1 %4, label %then34, label %else36

then8:                                            ; preds = %then
  %Call11 = load ptr, ptr %Call, align 8
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.39, ptr %Call11)
  %fstr_concat12 = call ptr @qc_string_concat(ptr %fstr_concat, ptr @.str.40)
  %expected13 = load i32, ptr %expected, align 4
  %fstr_i32 = call ptr @qc_to_string_int(i32 %expected13)
  %fstr_concat14 = call ptr @qc_string_concat(ptr %fstr_concat12, ptr %fstr_i32)
  %fstr_concat15 = call ptr @qc_string_concat(ptr %fstr_concat14, ptr @.str.41)
  %result16 = load i32, ptr %result, align 4
  %fstr_i3217 = call ptr @qc_to_string_int(i32 %result16)
  %fstr_concat18 = call ptr @qc_string_concat(ptr %fstr_concat15, ptr %fstr_i3217)
  %fstr_concat19 = call ptr @qc_string_concat(ptr %fstr_concat18, ptr @.str.43)
  %FailMessage20 = load ptr, ptr %FailMessage, align 8
  %fstr_concat21 = call ptr @qc_string_concat(ptr %fstr_concat19, ptr %FailMessage20)
  %Fail_result = call i32 @"UnitTest::Test_Fail"(ptr %0, ptr %fstr_concat21)
  br label %ifcont9

ifcont9:                                          ; preds = %else10, %then8
  br label %ifcont

else10:                                           ; preds = %then
  %expected22 = load i32, ptr %expected, align 4
  %fstr_i3223 = call ptr @qc_to_string_int(i32 %expected22)
  %fstr_concat24 = call ptr @qc_string_concat(ptr @.str.47, ptr %fstr_i3223)
  %fstr_concat25 = call ptr @qc_string_concat(ptr %fstr_concat24, ptr @.str.49)
  %result26 = load i32, ptr %result, align 4
  %fstr_i3227 = call ptr @qc_to_string_int(i32 %result26)
  %fstr_concat28 = call ptr @qc_string_concat(ptr %fstr_concat25, ptr %fstr_i3227)
  %fstr_concat29 = call ptr @qc_string_concat(ptr %fstr_concat28, ptr @.str.50)
  %FailMessage30 = load ptr, ptr %FailMessage, align 8
  %fstr_concat31 = call ptr @qc_string_concat(ptr %fstr_concat29, ptr %FailMessage30)
  %Fail_result32 = call i32 @"UnitTest::Test_Fail"(ptr %0, ptr %fstr_concat31)
  br label %ifcont9

then34:                                           ; preds = %else
  %Call37 = load ptr, ptr %Call, align 8
  %fstr_concat38 = call ptr @qc_string_concat(ptr @.str.52, ptr %Call37)
  %fstr_concat39 = call ptr @qc_string_concat(ptr %fstr_concat38, ptr @.str.53)
  %result40 = load i32, ptr %result, align 4
  %fstr_i3241 = call ptr @qc_to_string_int(i32 %result40)
  %fstr_concat42 = call ptr @qc_string_concat(ptr %fstr_concat39, ptr %fstr_i3241)
  %fstr_concat43 = call ptr @qc_string_concat(ptr %fstr_concat42, ptr @.str.54)
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
  %fstr_concat49 = call ptr @qc_string_concat(ptr @.str.55, ptr %fstr_i3248)
  %fstr_concat50 = call ptr @qc_string_concat(ptr %fstr_concat49, ptr @.str.56)
  %expected51 = load i32, ptr %expected, align 4
  %fstr_i3252 = call ptr @qc_to_string_int(i32 %expected51)
  %fstr_concat53 = call ptr @qc_string_concat(ptr %fstr_concat50, ptr %fstr_i3252)
  %Success_result54 = call i32 @"UnitTest::Test_Success"(ptr %0, ptr %fstr_concat53)
  br label %ifcont35
}

define i32 @test_nullptr() {
entry:
  %real_node = alloca ptr, align 8
  %nod = alloca %Node2, align 8
  %p = alloca ptr, align 8
  %w = alloca ptr, align 8
  %n = alloca ptr, align 8
  store ptr null, ptr %n, align 8
  store ptr null, ptr %w, align 8
  store ptr null, ptr %p, align 8
  %n1 = load ptr, ptr %n, align 8
  %ptr_eq = icmp eq ptr %n1, null
  br i1 %ptr_eq, label %then, label %else

then:                                             ; preds = %entry
  call void @qc_print_string(ptr @10)
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  call void @Node2_Node2(ptr %nod, i32 10, ptr null)
  %nod2 = load %Node2, ptr %nod, align 8
  store ptr %nod, ptr %real_node, align 8
  %real_node3 = load ptr, ptr %real_node, align 8
  %ptr_ne = icmp ne ptr %real_node3, null
  br i1 %ptr_ne, label %then4, label %ifcont5

else:                                             ; preds = %entry
  call void @qc_print_string(ptr @11)
  br label %ifcont

then4:                                            ; preds = %ifcont
  call void @qc_print_string(ptr @12)
  br label %ifcont5

ifcont5:                                          ; preds = %then4, %ifcont
  %real_node6 = load ptr, ptr %real_node, align 8
  %next_ptr = getelementptr inbounds nuw %Node2, ptr %real_node6, i32 0, i32 1
  store ptr null, ptr %next_ptr, align 8
  %assign_lhs_val = load ptr, ptr %n, align 8
  %real_node7 = load ptr, ptr %real_node, align 8
  store ptr %real_node7, ptr %n, align 8
  %assign_lhs_val8 = load ptr, ptr %n, align 8
  store ptr null, ptr %n, align 8
  ret i32 0
}

define i32 @final_ptr_test() {
entry:
  %i = alloca i32, align 4
  %arr_ptr25 = alloca ptr, align 8
  %val = alloca i32, align 4
  %n2 = alloca ptr, align 8
  %n = alloca ptr, align 8
  %dist = alloca i32, align 4
  %p_end = alloca ptr, align 8
  %p_start = alloca ptr, align 8
  %p23 = alloca ptr, align 8
  %p = alloca ptr, align 8
  %z = alloca i32, align 4
  %y = alloca i32, align 4
  %x = alloca i32, align 4
  store i32 10, ptr %x, align 4
  store i32 20, ptr %y, align 4
  store i32 30, ptr %z, align 4
  %x1 = load i32, ptr %x, align 4
  store ptr %x, ptr %p, align 8
  %p2 = load ptr, ptr %p, align 8
  %ptr_arr_addr = getelementptr i32, ptr %p2, i32 0
  %ptr_arr_val = load i32, ptr %ptr_arr_addr, align 4
  %icmpeq = icmp eq i32 %ptr_arr_val, 10
  br i1 %icmpeq, label %then, label %ifcont

then:                                             ; preds = %entry
  call void @qc_print_string(ptr @13)
  br label %ifcont

ifcont:                                           ; preds = %then, %entry
  %p4 = load ptr, ptr %p, align 8
  %ptr_arith_minus = getelementptr i32, ptr %p4, i32 -1
  store ptr %ptr_arith_minus, ptr %p23, align 8
  %p25 = load ptr, ptr %p23, align 8
  %ptr_arr_asi = getelementptr i32, ptr %p25, i32 0
  store i32 99, ptr %ptr_arr_asi, align 4
  %arr_ptr = load ptr, ptr %p23, align 8
  %arr_elem_ptr = getelementptr i32, ptr %arr_ptr, i32 0
  store i32 99, ptr %arr_elem_ptr, align 4
  %y6 = load i32, ptr %y, align 4
  %icmpeq7 = icmp eq i32 %y6, 99
  %z8 = load i32, ptr %z, align 4
  %icmpeq9 = icmp eq i32 %z8, 99
  %or = or i1 %icmpeq7, %icmpeq9
  br i1 %or, label %then10, label %ifcont11

then10:                                           ; preds = %ifcont
  call void @qc_print_string(ptr @14)
  br label %ifcont11

ifcont11:                                         ; preds = %then10, %ifcont
  %x12 = load i32, ptr %x, align 4
  store ptr %x, ptr %p_start, align 8
  %p_start13 = load ptr, ptr %p_start, align 8
  %ptr_arith_plus = getelementptr i32, ptr %p_start13, i32 5
  store ptr %ptr_arith_plus, ptr %p_end, align 8
  %p_end14 = load ptr, ptr %p_end, align 8
  %p_start15 = load ptr, ptr %p_start, align 8
  %0 = ptrtoint ptr %p_end14 to i64
  %1 = ptrtoint ptr %p_start15 to i64
  %2 = sub i64 %0, %1
  %ptr_diff = sdiv exact i64 %2, ptrtoint (ptr getelementptr (i32, ptr null, i32 1) to i64)
  %3 = trunc i64 %ptr_diff to i32
  store i32 %3, ptr %dist, align 4
  %dist16 = load i32, ptr %dist, align 4
  %icmpeq17 = icmp eq i32 %dist16, 5
  br i1 %icmpeq17, label %then18, label %ifcont19

then18:                                           ; preds = %ifcont11
  call void @qc_print_string(ptr @15)
  br label %ifcont19

ifcont19:                                         ; preds = %then18, %ifcont11
  store ptr null, ptr %n, align 8
  %n20 = load ptr, ptr %n, align 8
  %ptr_arith_plus21 = getelementptr i32, ptr %n20, i32 10
  store ptr %ptr_arith_plus21, ptr %n2, align 8
  %n222 = load ptr, ptr %n2, align 8
  %ptr_ne = icmp ne ptr %n222, null
  br i1 %ptr_ne, label %then23, label %ifcont24

then23:                                           ; preds = %ifcont19
  call void @qc_print_string(ptr @16)
  br label %ifcont24

ifcont24:                                         ; preds = %then23, %ifcont19
  store i32 0, ptr %val, align 4
  %val26 = load i32, ptr %val, align 4
  store ptr %val, ptr %arr_ptr25, align 8
  store i32 0, ptr %i, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.body, %ifcont24
  %i27 = load i32, ptr %i, align 4
  %icmplt = icmp slt i32 %i27, 5
  br i1 %icmplt, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %arr_ptr28 = load ptr, ptr %arr_ptr25, align 8
  %ptr_arr_asi29 = getelementptr i32, ptr %arr_ptr28, i32 0
  %i30 = load i32, ptr %i, align 4
  store i32 %i30, ptr %ptr_arr_asi29, align 4
  %i31 = load i32, ptr %i, align 4
  %arr_ptr32 = load ptr, ptr %arr_ptr25, align 8
  %arr_elem_ptr33 = getelementptr i32, ptr %arr_ptr32, i32 0
  store i32 %i31, ptr %arr_elem_ptr33, align 4
  %assign_lhs_val = load i32, ptr %i, align 4
  %i34 = load i32, ptr %i, align 4
  %add = add i32 %i34, 1
  store i32 %add, ptr %i, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %val35 = load i32, ptr %val, align 4
  %icmpeq36 = icmp eq i32 %val35, 4
  br i1 %icmpeq36, label %then37, label %ifcont38

then37:                                           ; preds = %while.end
  call void @qc_print_string(ptr @17)
  br label %ifcont38

ifcont38:                                         ; preds = %then37, %while.end
  ret i32 0
}

define i32 @testVarArgs(ptr %args) {
entry:
  %b = alloca i1, align 1
  %x = alloca i32, align 4
  %args1 = alloca ptr, align 8
  store ptr %args, ptr %args1, align 8
  %variad = load ptr, ptr %args1, align 8
  %variadc_arg = call ptr @qc_variadic_next(ptr %variad)
  %vararg_int = ptrtoint ptr %variadc_arg to i32
  store i32 %vararg_int, ptr %x, align 4
  %variad2 = load ptr, ptr %args1, align 8
  %variadc_is_empty = call i1 @qc_variadic_is_empty(ptr %variad2)
  store i1 %variadc_is_empty, ptr %b, align 1
  %x3 = load i32, ptr %x, align 4
  %0 = sext i32 %x3 to i64
  call void @qc_print_string(ptr @18)
  %1 = call ptr @qc_fmt_int(i64 %0, i32 -1, i32 -1, i1 false)
  call void @qc_print_string(ptr %1)
  %b4 = load i1, ptr %b, align 1
  %select_val = select i1 %b4, ptr @.str.79, ptr @.str.80
  call void @qc_print_string(ptr @19)
  %2 = call ptr @qc_fmt_string(ptr %select_val, i32 -1, i1 false)
  call void @qc_print_string(ptr %2)
  call void @qc_print_string(ptr @20)
  ret i32 0
}

define i32 @__user_entry() {
entry:
  %ptr_deref = alloca i32, align 4
  %py = alloca ptr, align 8
  %pnt = alloca %Point, align 8
  %x = alloca %Refs, align 8
  %z = alloca %Refs, align 8
  %r = alloca %Refs, align 8
  %n = alloca i32, align 4
  %y = alloca i32, align 4
  %test = alloca %"UnitTest::Test", align 8
  call void @"UnitTest::Test_Test"(ptr %test, i32 8)
  store i32 0, ptr %y, align 4
  %rx = alloca ptr, align 8
  store ptr %y, ptr %rx, align 8
  %0 = load ptr, ptr %rx, align 8
  %assign_lhs_val = load i32, ptr %0, align 4
  store i32 12345, ptr %0, align 4
  %1 = load ptr, ptr %rx, align 8
  %rx1 = load i32, ptr %1, align 4
  %AssertEqual_result = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %test, i32 12345, i32 %rx1, ptr @.str.81, ptr @.str.82)
  %y2 = load i32, ptr %y, align 4
  %AssertEqual_result3 = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %test, i32 12345, i32 %y2, ptr @.str.83, ptr @.str.84)
  store i32 1234, ptr %n, align 4
  %n4 = load i32, ptr %n, align 4
  %calltmp = call i32 @add(ptr %y, i32 %n4)
  %y5 = load i32, ptr %y, align 4
  %AssertEqual_result6 = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %test, i32 13579, i32 %y5, ptr @.str.85, ptr @.str.86)
  call void @Refs_Refs(ptr %r, i32 12345)
  call void @Refs_Refs(ptr %z, i32 321)
  call void @Refs_Refs(ptr %x, i32 21)
  %assign_lhs_val7 = load %Refs, ptr %x, align 4
  %assign_lhs_val8 = load %Refs, ptr %z, align 4
  %r9 = load %Refs, ptr %r, align 4
  %op_assign_tmp = call ptr @"Refs_operator="(ptr %z, %Refs %r9)
  %op_rhs_load = load %Refs, ptr %op_assign_tmp, align 4
  %op_assign_tmp10 = call ptr @"Refs_operator="(ptr %x, %Refs %op_rhs_load)
  %getX_result = call i32 @Refs_getX(ptr %x, ptr %y)
  %y11 = load i32, ptr %y, align 4
  %AssertEqual_result12 = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %test, i32 12345, i32 %y11, ptr @.str.87, ptr @.str.88)
  %setXp1_result = call i32 @Refs_setXp1(ptr %x, ptr %y)
  %n13 = load i32, ptr %n, align 4
  %2 = call i32 @"aAutoReturn_int&_int"(ptr %y, i32 %n13)
  %n14 = load i32, ptr %n, align 4
  %autoRet_result = call i32 @Refs_autoRet_int_int(ptr %x, ptr %y, i32 %n14)
  %y15 = load i32, ptr %y, align 4
  %AssertEqual_result16 = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %test, i32 14814, i32 %y15, ptr @.str.91, ptr @.str.92)
  store %Point { i32 1, i32 3 }, ptr %pnt, align 4
  %calltmp17 = call i32 @addToX(ptr %pnt, i32 21)
  %pnt18 = load %Point, ptr %pnt, align 4
  %x19 = extractvalue %Point %pnt18, 0
  %AssertEqual_result20 = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %test, i32 22, i32 %x19, ptr @.str.93, ptr @.str.94)
  %y21 = load i32, ptr %y, align 4
  store ptr %y, ptr %py, align 8
  %py22 = load ptr, ptr %py, align 8
  %py23 = load ptr, ptr %py, align 8
  %deref = load i32, ptr %py23, align 4
  store i32 %deref, ptr %ptr_deref, align 4
  %ptr_deref24 = load i32, ptr %ptr_deref, align 4
  %AssertEqual_result25 = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %test, i32 14814, i32 %ptr_deref24, ptr @.str.95, ptr @.str.96)
  %py26 = load ptr, ptr %py, align 8
  %assign_lhs_val27 = load i32, ptr %py26, align 4
  %add = add i32 %assign_lhs_val27, 123
  store i32 %add, ptr %py26, align 4
  %py28 = load ptr, ptr %py, align 8
  %py29 = load ptr, ptr %py, align 8
  %deref30 = load i32, ptr %py29, align 4
  %AssertEqual_result31 = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr %test, i32 14937, i32 %deref30, ptr @.str.97, ptr @.str.98)
  %calltmp32 = call i32 @TESTESTESTESTESTEST()
  %calltmp33 = call i32 @test_nullptr()
  %calltmp34 = call i32 @final_ptr_test()
  call void @qc_flush()
  %varadics_array = alloca ptr, align 8
  %3 = getelementptr ptr, ptr %varadics_array, i32 0
  store ptr inttoptr (i32 213 to ptr), ptr %3, align 8
  %variadic_struct = alloca { ptr, i32, i32 }, align 8
  %4 = getelementptr inbounds nuw { ptr, i32, i32 }, ptr %variadic_struct, i32 0, i32 0
  store ptr %varadics_array, ptr %4, align 8
  %5 = getelementptr inbounds nuw { ptr, i32, i32 }, ptr %variadic_struct, i32 0, i32 1
  store i32 1, ptr %5, align 4
  %6 = getelementptr inbounds nuw { ptr, i32, i32 }, ptr %variadic_struct, i32 0, i32 2
  store i32 0, ptr %6, align 4
  %calltmp35 = call i32 @testVarArgs(ptr %variadic_struct)
  %varadics_array36 = alloca ptr, i32 2, align 8
  %7 = getelementptr ptr, ptr %varadics_array36, i32 0
  store ptr inttoptr (i32 213 to ptr), ptr %7, align 8
  %8 = getelementptr ptr, ptr %varadics_array36, i32 1
  store ptr inttoptr (i32 12 to ptr), ptr %8, align 8
  %variadic_struct37 = alloca { ptr, i32, i32 }, align 8
  %9 = getelementptr inbounds nuw { ptr, i32, i32 }, ptr %variadic_struct37, i32 0, i32 0
  store ptr %varadics_array36, ptr %9, align 8
  %10 = getelementptr inbounds nuw { ptr, i32, i32 }, ptr %variadic_struct37, i32 0, i32 1
  store i32 2, ptr %10, align 4
  %11 = getelementptr inbounds nuw { ptr, i32, i32 }, ptr %variadic_struct37, i32 0, i32 2
  store i32 0, ptr %11, align 4
  %calltmp38 = call i32 @testVarArgs(ptr %variadic_struct37)
  %var_array = alloca ptr, i32 3, align 8
  %12 = getelementptr ptr, ptr %var_array, i32 0
  store ptr inttoptr (i32 123 to ptr), ptr %12, align 8
  %13 = getelementptr ptr, ptr %var_array, i32 1
  store ptr inttoptr (i32 328 to ptr), ptr %13, align 8
  %14 = getelementptr ptr, ptr %var_array, i32 2
  store ptr inttoptr (i32 50 to ptr), ptr %14, align 8
  %var_struct_alloc = alloca { ptr, i32, i32 }, align 8
  %15 = getelementptr inbounds nuw { ptr, i32, i32 }, ptr %var_struct_alloc, i32 0, i32 0
  store ptr %var_array, ptr %15, align 8
  %16 = getelementptr inbounds nuw { ptr, i32, i32 }, ptr %var_struct_alloc, i32 0, i32 1
  store i32 3, ptr %16, align 4
  %17 = getelementptr inbounds nuw { ptr, i32, i32 }, ptr %var_struct_alloc, i32 0, i32 2
  store i32 0, ptr %17, align 4
  %variadicMethod_result = call i32 @Refs_variadicMethod(ptr %x, i32 3, ptr %var_struct_alloc)
  ret i32 0
}

define i32 @"aAutoReturn_int&_int"(ptr %x1, i32 %y2) {
entry:
  %y = alloca i32, align 4
  %x = alloca ptr, align 8
  store ptr %x1, ptr %x, align 8
  store i32 %y2, ptr %y, align 4
  %y3 = load i32, ptr %y, align 4
  %0 = call i1 @qc_string_eq(ptr @21, ptr @.str.89)
  br i1 %0, label %then, label %ifcont

then:                                             ; preds = %entry
  %1 = load ptr, ptr %x, align 8
  %assign_lhs_val = load i32, ptr %1, align 4
  %y4 = load i32, ptr %y, align 4
  %add = add i32 %assign_lhs_val, %y4
  store i32 %add, ptr %1, align 4
  br label %ifcont

ifcont:                                           ; preds = %then, %entry
  ret i32 0
}

define i32 @Refs_autoRet_int_int(ptr %0, ptr %x1, i32 %y2) {
entry:
  %y = alloca i32, align 4
  %x = alloca ptr, align 8
  store ptr %x1, ptr %x, align 8
  store i32 %y2, ptr %y, align 4
  %y3 = load i32, ptr %y, align 4
  %1 = call i1 @qc_string_eq(ptr @22, ptr @.str.90)
  br i1 %1, label %then, label %ifcont

then:                                             ; preds = %entry
  %2 = load ptr, ptr %x, align 8
  %assign_lhs_val = load i32, ptr %2, align 4
  %y4 = load i32, ptr %y, align 4
  %add = add i32 %assign_lhs_val, %y4
  store i32 %add, ptr %2, align 4
  br label %ifcont

ifcont:                                           ; preds = %then, %entry
  ret i32 0
}

define i32 @main() {
entry:
  %entry_result = call i32 @__user_entry()
  ret i32 %entry_result
}

attributes #0 = { mustprogress nofree nounwind willreturn memory(inaccessiblemem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress nounwind willreturn memory(argmem: readwrite, inaccessiblemem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { mustprogress nounwind willreturn allockind("realloc") allocsize(1) memory(argmem: readwrite, inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { mustprogress nofree nounwind willreturn allockind("alloc,zeroed") allocsize(0,1) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { mustprogress nofree nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #7 = { nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #8 = { nofree nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #9 = { mustprogress nofree nounwind willreturn memory(argmem: readwrite, inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #10 = { mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #11 = { mustprogress nofree nounwind willreturn uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #12 = { mustprogress nofree nounwind willreturn memory(argmem: read) "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #13 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #14 = { mustprogress nofree norecurse nounwind willreturn memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #15 = { mustprogress nofree nounwind willreturn memory(readwrite, argmem: none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #16 = { mustprogress nofree nounwind willreturn memory(write, argmem: none, inaccessiblemem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #17 = { mustprogress nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #18 = { nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #19 = { mustprogress nofree nounwind memory(readwrite, argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #20 = { mustprogress nofree nounwind willreturn memory(read) "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #21 = { mustprogress uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #22 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #23 = { mustprogress nofree nounwind willreturn memory(argmem: readwrite) "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #24 = { mustprogress nofree norecurse nounwind willreturn uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #25 = { mustprogress nofree nounwind willreturn "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #26 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #27 = { nofree nounwind }
attributes #28 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #29 = { mustprogress nofree norecurse nosync nounwind willreturn memory(write, argmem: readwrite, inaccessiblemem: none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #30 = { mustprogress nofree norecurse nosync nounwind willreturn memory(read, inaccessiblemem: none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #31 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #32 = { mustprogress nounwind willreturn uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #33 = { mustprogress nofree norecurse nosync nounwind willreturn memory(read, argmem: readwrite, inaccessiblemem: none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #34 = { mustprogress nofree norecurse nounwind willreturn memory(read, inaccessiblemem: none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #35 = { mustprogress nofree norecurse nounwind memory(readwrite, inaccessiblemem: none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #36 = { nounwind allocsize(0) }
attributes #37 = { nounwind }
attributes #38 = { nounwind allocsize(1) }
attributes #39 = { nounwind allocsize(0,1) }
attributes #40 = { nounwind willreturn memory(read) }

!llvm.ident = !{!0}
!llvm.module.flags = !{!1, !2, !3, !4}

!0 = !{!"Debian clang version 21.1.8 (7+b1)"}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 2}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.mustprogress"}
!7 = !{!8, !8, i64 0}
!8 = !{!"omnipotent char", !9, i64 0}
!9 = !{!"Simple C++ TBAA"}
!10 = !{!11, !11, i64 0}
!11 = !{!"p1 _ZTS8_IO_FILE", !12, i64 0}
!12 = !{!"any pointer", !8, i64 0}
!13 = distinct !{!13, !6}
!14 = distinct !{!14, !6}
!15 = distinct !{!15, !6}
!16 = distinct !{!16, !6}
!17 = distinct !{!17, !6}
!18 = distinct !{!18, !6}
!19 = !{!20, !20, i64 0}
!20 = !{!"int", !8, i64 0}
!21 = distinct !{!21, !6}
!22 = !{!23, !23, i64 0}
!23 = !{!"float", !8, i64 0}
!24 = distinct !{!24, !6}
!25 = !{!26, !26, i64 0}
!26 = !{!"double", !8, i64 0}
!27 = distinct !{!27, !6}
!28 = !{!29, !29, i64 0}
!29 = !{!"p1 omnipotent char", !12, i64 0}
!30 = distinct !{!30, !6}
!31 = distinct !{!31, !6}
!32 = !{!33, !33, i64 0}
!33 = !{!"bool", !8, i64 0}
!34 = !{i8 0, i8 2}
!35 = !{}
!36 = distinct !{!36, !6}
!37 = distinct !{!37, !6}
!38 = distinct !{!38, !6, !39, !40}
!39 = !{!"llvm.loop.isvectorized", i32 1}
!40 = !{!"llvm.loop.unroll.runtime.disable"}
!41 = distinct !{!41, !6, !40, !39}
!42 = distinct !{!42, !6}
!43 = distinct !{!43, !6}
!44 = distinct !{!44, !6, !39, !40}
!45 = distinct !{!45, !6, !40, !39}
!46 = distinct !{!46, !6}
!47 = !{!48, !49, i64 0}
!48 = !{!"_ZTS15qc_jagged_array", !49, i64 0, !50, i64 8, !20, i64 16, !20, i64 20, !20, i64 24}
!49 = !{!"any p2 pointer", !12, i64 0}
!50 = !{!"p1 int", !12, i64 0}
!51 = !{!48, !50, i64 8}
!52 = !{!48, !20, i64 16}
!53 = !{!48, !20, i64 20}
!54 = !{!48, !20, i64 24}
!55 = !{!12, !12, i64 0}
!56 = distinct !{!56, !6}
!57 = distinct !{!57, !6}
!58 = distinct !{!58, !6}
!59 = distinct !{!59, !6}
!60 = distinct !{!60, !6}
!61 = distinct !{!61, !6}
!62 = !{!63, !20, i64 12}
!63 = !{!"_ZTS7qc_list", !49, i64 0, !20, i64 8, !20, i64 12, !20, i64 16}
!64 = !{!63, !20, i64 8}
!65 = !{!63, !20, i64 16}
!66 = !{!63, !49, i64 0}
!67 = !{!68, !20, i64 20}
!68 = !{!"_ZTS6qc_map", !49, i64 0, !49, i64 8, !20, i64 16, !20, i64 20, !20, i64 24, !20, i64 28}
!69 = !{!68, !20, i64 16}
!70 = !{!68, !20, i64 24}
!71 = !{!68, !20, i64 28}
!72 = !{!68, !49, i64 0}
!73 = !{!68, !49, i64 8}
!74 = distinct !{!74, !6}
!75 = distinct !{!75, !6}
!76 = distinct !{!76, !6}
!77 = distinct !{!77, !6}
!78 = distinct !{!78, !6}
!79 = distinct !{!79, !6}
!80 = distinct !{!80, !6}
!81 = distinct !{!81, !6}
!82 = distinct !{!82, !6, !39, !40}
!83 = distinct !{!83, !84}
!84 = !{!"llvm.loop.unroll.disable"}
!85 = distinct !{!85, !6, !39}
!86 = !{!87, !87, i64 0}
!87 = !{!"p1 _ZTS9_ffi_type", !12, i64 0}
!88 = distinct !{!88, !6}
!89 = distinct !{!89, !6}
!90 = !{!91, !20, i64 12}
!91 = !{!"_ZTS11qc_variadic", !49, i64 0, !20, i64 8, !20, i64 12}
!92 = !{!91, !20, i64 8}
!93 = !{!91, !49, i64 0}
