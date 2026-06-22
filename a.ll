; ModuleID = 'master_module'
source_filename = "master_module"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"UnitTest::Test" = type { i32, i32, i32, i32, ptr }

@.str.5 = private unnamed_addr constant [4 x i8] c"%%d\00", align 1
@.str.18 = private unnamed_addr constant [4 x i8] c"%%s\00", align 1
@.str.23 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.str.24 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.str.33 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.34 = private unnamed_addr constant [3 x i8] c"%g\00", align 1
@stdout = external local_unnamed_addr global ptr, align 8
@switch.table.qc_map_set.53 = private unnamed_addr constant [4 x i64] [i64 8, i64 1, i64 1, i64 1], align 8
@0 = private unnamed_addr constant [36 x i8] c"=== TESTING QUANTUM C STDLIB ===\0A\0A\00\00", align 1
@1 = private unnamed_addr constant [24 x i8] c"--- Testing Utils ---\0A\00\00", align 1
@.str.104 = private constant [18 x i8] c"range(0, 10, 2): \00"
@.str.105 = private constant [3 x i8] c", \00"
@.str.106 = private constant [3 x i8] c", \00"
@.str.107 = private constant [3 x i8] c", \00"
@.str.108 = private constant [3 x i8] c", \00"
@.str.109 = private constant [2 x i8] c"\0A\00"
@.str.111 = private constant [26 x i8] c"range(10, 0, -1) length: \00"
@.str.112 = private constant [2 x i8] c"\0A\00"
@2 = private unnamed_addr constant [22 x i8] c"Testing sleep(1)...\0A\00\00", align 1
@3 = private unnamed_addr constant [15 x i8] c"Sleep done!\0A\0A\00\00", align 1
@4 = private unnamed_addr constant [23 x i8] c"--- Testing Math ---\0A\00\00", align 1
@.str.117 = private constant [14 x i8] c"Math::pi() = \00"
@.str.118 = private constant [2 x i8] c"\0A\00"
@.str.120 = private constant [13 x i8] c"Math::e() = \00"
@.str.121 = private constant [2 x i8] c"\0A\00"
@.str.123 = private constant [20 x i8] c"Math::max(5, 10) = \00"
@.str.124 = private constant [2 x i8] c"\0A\00"
@.str.126 = private constant [20 x i8] c"Math::min(5, 10) = \00"
@.str.127 = private constant [2 x i8] c"\0A\00"
@.str.129 = private constant [18 x i8] c"Math::sqrt(16) = \00"
@.str.130 = private constant [2 x i8] c"\0A\00"
@.str.132 = private constant [18 x i8] c"Math::abs(-42) = \00"
@.str.133 = private constant [2 x i8] c"\0A\00"
@.str.135 = private constant [19 x i8] c"Math::ceil(3.2) = \00"
@.str.136 = private constant [2 x i8] c"\0A\00"
@.str.138 = private constant [20 x i8] c"Math::floor(3.8) = \00"
@.str.139 = private constant [2 x i8] c"\0A\00"
@.str.141 = private constant [16 x i8] c"Math::sin(0) = \00"
@.str.142 = private constant [2 x i8] c"\0A\00"
@.str.144 = private constant [16 x i8] c"Math::cos(0) = \00"
@.str.145 = private constant [2 x i8] c"\0A\00"
@.str.147 = private constant [16 x i8] c"Math::tan(0) = \00"
@.str.148 = private constant [2 x i8] c"\0A\00"
@.str.150 = private constant [20 x i8] c"Math::log(2.718) = \00"
@.str.151 = private constant [3 x i8] c"\0A\0A\00"
@5 = private unnamed_addr constant [30 x i8] c"--- Testing Collections ---\0A\00\00", align 1
@.str.154 = private constant [23 x i8] c"has([1,2,3,4,5], 3) = \00"
@.str.155 = private constant [2 x i8] c"\0A\00"
@.str.157 = private constant [24 x i8] c"has([1,2,3,4,5], 10) = \00"
@.str.158 = private constant [2 x i8] c"\0A\00"
@.str.160 = private constant [28 x i8] c"index_of([1,2,3,4,5], 3) = \00"
@.str.161 = private constant [2 x i8] c"\0A\00"
@.str.163 = private constant [20 x i8] c"sort([5,2,8,1,9]): \00"
@.str.164 = private constant [3 x i8] c", \00"
@.str.165 = private constant [3 x i8] c", \00"
@.str.166 = private constant [3 x i8] c", \00"
@.str.167 = private constant [3 x i8] c", \00"
@.str.168 = private constant [2 x i8] c"\0A\00"
@.str.170 = private constant [23 x i8] c"reverse([1,2,3,4,5]): \00"
@.str.171 = private constant [3 x i8] c", \00"
@.str.172 = private constant [3 x i8] c", \00"
@.str.173 = private constant [3 x i8] c", \00"
@.str.174 = private constant [3 x i8] c", \00"
@.str.175 = private constant [3 x i8] c"\0A\0A\00"
@.str.177 = private constant [25 x i8] c"remove([5,4,3,2,1], 2): \00"
@.str.178 = private constant [3 x i8] c", \00"
@.str.179 = private constant [3 x i8] c", \00"
@.str.180 = private constant [3 x i8] c", \00"
@.str.181 = private constant [3 x i8] c"\0A\0A\00"
@6 = private unnamed_addr constant [27 x i8] c"--- Testing UnitTest ---\0A\00\00", align 1
@.str.184 = private constant [16 x i8] c"[FAIL] On call \00"
@.str.185 = private constant [12 x i8] c": Expected \00"
@.str.186 = private constant [7 x i8] c", got \00"
@.str.187 = private constant [3 x i8] c". \00"
@.str.188 = private constant [17 x i8] c"[FAIL] Expected \00"
@.str.189 = private constant [7 x i8] c", got \00"
@.str.190 = private constant [3 x i8] c". \00"
@.str.191 = private constant [1 x i8] zeroinitializer
@.str.192 = private constant [19 x i8] c"[SUCCESS] on call \00"
@.str.193 = private constant [3 x i8] c": \00"
@.str.194 = private constant [15 x i8] c" was equal to \00"
@.str.195 = private constant [11 x i8] c"[SUCCESS] \00"
@.str.196 = private constant [15 x i8] c" was equal to \00"
@.str.197 = private constant [1 x i8] zeroinitializer
@.str.198 = private constant [8 x i8] c"5 == 5\0A\00"
@.str.199 = private constant [1 x i8] zeroinitializer
@.str.200 = private constant [11 x i8] c"10 == 5+5\0A\00"
@.str.202 = private constant [14 x i8] c"true is true\0A\00"
@.str.204 = private constant [16 x i8] c"false is false\0A\00"
@.str.205 = private constant [1 x i8] zeroinitializer
@.str.206 = private constant [16 x i8] c"[FAIL] On call \00"
@.str.207 = private constant [12 x i8] c": Expected \00"
@.str.208 = private constant [15 x i8] c" to not equal \00"
@.str.209 = private constant [3 x i8] c". \00"
@.str.210 = private constant [17 x i8] c"[FAIL] Expected \00"
@.str.211 = private constant [15 x i8] c" to not equal \00"
@.str.212 = private constant [3 x i8] c". \00"
@.str.213 = private constant [1 x i8] zeroinitializer
@.str.214 = private constant [19 x i8] c"[SUCCESS] on call \00"
@.str.215 = private constant [3 x i8] c": \00"
@.str.216 = private constant [18 x i8] c" wasn't equal to \00"
@.str.217 = private constant [11 x i8] c"[SUCCESS] \00"
@.str.218 = private constant [18 x i8] c" wasn't equal to \00"
@.str.219 = private constant [1 x i8] zeroinitializer
@.str.220 = private constant [9 x i8] c"5 != 10\0A\00"
@7 = private unnamed_addr constant [28 x i8] c"\0A--- Testing AdvQBool ---\0A\00\00", align 1
@.str.223 = private constant [10 x i8] c"AQB(75): \00"
@.str.224 = private constant [2 x i8] c"\0A\00"
@8 = private unnamed_addr constant [42 x i8] c"Testing 10 evaluations of 75% true AQB:\0A\00\00", align 1
@.str.227 = private constant [5 x i8] c"Got \00"
@.str.228 = private constant [26 x i8] c"/10 true (expected ~7-8)\0A\00"
@.str.230 = private constant [15 x i8] c"\0AAQB && test: \00"
@.str.231 = private constant [2 x i8] c"\0A\00"
@.str.233 = private constant [14 x i8] c"AQB || test: \00"
@.str.234 = private constant [2 x i8] c"\0A\00"
@.str.236 = private constant [12 x i8] c"!AQB test: \00"
@.str.237 = private constant [2 x i8] c"\0A\00"
@.str.238 = private constant [7 x i8] c"ls -la\00"
@9 = private unnamed_addr constant [37 x i8] c"\0A=== ALL STDLIB TESTS COMPLETE ===\0A\00\00", align 1
@10 = private unnamed_addr constant [3 x i8] c"\0A\00\00", align 1
@.str.244 = private constant [9 x i8] c"Failed: \00"
@.str.245 = private constant [2 x i8] c"\0A\00"
@.str.247 = private constant [9 x i8] c"Passed: \00"
@.str.248 = private constant [2 x i8] c"\0A\00"
@11 = private constant [1 x i8] zeroinitializer, align 1
@12 = private unnamed_addr constant [2 x i8] zeroinitializer, align 1
@13 = private unnamed_addr constant [33 x i8] c"==============================\0A\00\00", align 1
@14 = private unnamed_addr constant [9 x i8] c"[FAIL]\0A\00\00", align 1
@15 = private unnamed_addr constant [9 x i8] c"[PASS]\0A\00\00", align 1
@.str.252 = private constant [4 x i8] c": [\00"
@.str.253 = private constant [2 x i8] c"/\00"
@.str.254 = private constant [2 x i8] c"]\00"
@.str.255 = private constant [4 x i8] c": [\00"
@.str.256 = private constant [2 x i8] c"/\00"
@.str.257 = private constant [2 x i8] c"]\00"
@.str.262 = private constant [1 x i8] zeroinitializer
@.str.263 = private constant [19 x i8] c"[SUCCESS] on call \00"
@.str.264 = private constant [21 x i8] c": Condition was true\00"
@.str.265 = private constant [29 x i8] c"[SUCCESS] Condition was true\00"
@.str.270 = private constant [1 x i8] zeroinitializer
@.str.271 = private constant [19 x i8] c"[SUCCESS] on call \00"
@.str.272 = private constant [22 x i8] c": Condition was false\00"
@.str.273 = private constant [30 x i8] c"[SUCCESS] Condition was false\00"
@.str.277 = private constant [19 x i8] c"Advanced QBool is \00"
@.str.278 = private constant [11 x i8] c" true and \00"
@.str.279 = private constant [8 x i8] c" false.\00"

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite)
declare noalias noundef ptr @malloc(i64 noundef) local_unnamed_addr #0

; Function Attrs: mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite)
declare void @free(ptr allocptr noundef captures(none)) local_unnamed_addr #1

; Function Attrs: mustprogress nounwind willreturn allockind("realloc") allocsize(1) memory(argmem: readwrite, inaccessiblemem: readwrite)
declare noalias noundef ptr @realloc(ptr allocptr noundef captures(none), i64 noundef) local_unnamed_addr #2

; Function Attrs: mustprogress nofree nounwind uwtable
define internal fastcc noalias noundef ptr @qc_fmt_int(i64 noundef range(i64 -2147483648, 2147483648) %0) unnamed_addr #3 {
  %2 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %2) #20
  %3 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 32, ptr noundef nonnull @.str.5) #20
  %4 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %2, i64 noundef %0) #20
  %5 = add nsw i32 %4, 1
  %6 = sext i32 %5 to i64
  %7 = tail call noalias ptr @malloc(i64 noundef %6) #23
  %8 = icmp eq ptr %7, null
  br i1 %8, label %11, label %9

9:                                                ; preds = %1
  %10 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull %7, i64 noundef %6, ptr noundef nonnull %2, i64 noundef %0) #20
  br label %11

11:                                               ; preds = %9, %1
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %2) #20
  ret ptr %7
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr captures(none)) #4

; Function Attrs: nofree nounwind
declare noundef i32 @snprintf(ptr noalias noundef writeonly captures(none), i64 noundef, ptr noundef readonly captures(none), ...) local_unnamed_addr #5

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr captures(none)) #4

; Function Attrs: mustprogress nofree nounwind uwtable
define internal fastcc void @qc_flush() unnamed_addr #3 {
  %1 = tail call i32 @fflush(ptr noundef null)
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @fflush(ptr noundef captures(none)) local_unnamed_addr #5

; Function Attrs: mustprogress nofree nounwind uwtable
define internal fastcc noalias noundef ptr @qc_fmt_string(ptr noundef %0) unnamed_addr #3 {
  %2 = alloca [16 x i8], align 16
  %3 = icmp eq ptr %0, null
  %4 = select i1 %3, ptr @11, ptr %0
  call void @llvm.lifetime.start.p0(i64 16, ptr nonnull %2) #20
  %5 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 16, ptr noundef nonnull @.str.18) #20
  %6 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %2, ptr noundef nonnull %4) #20
  %7 = icmp slt i32 %6, 0
  br i1 %7, label %15, label %8

8:                                                ; preds = %1
  %9 = add nuw nsw i32 %6, 1
  %10 = zext nneg i32 %9 to i64
  %11 = tail call noalias ptr @malloc(i64 noundef %10) #23
  %12 = icmp eq ptr %11, null
  br i1 %12, label %15, label %13

13:                                               ; preds = %8
  %14 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %11, i64 noundef %10, ptr noundef nonnull %2, ptr noundef nonnull %4) #20
  br label %15

15:                                               ; preds = %13, %8, %1
  %16 = phi ptr [ null, %1 ], [ %11, %13 ], [ null, %8 ]
  call void @llvm.lifetime.end.p0(i64 16, ptr nonnull %2) #20
  ret ptr %16
}

; Function Attrs: mustprogress nofree nounwind willreturn uwtable
define internal fastcc noalias noundef ptr @qc_string_concat(ptr noundef readonly captures(address_is_null) %0, ptr noundef readonly captures(address_is_null) %1) unnamed_addr #6 {
  %3 = icmp eq ptr %0, null
  %4 = select i1 %3, ptr @11, ptr %0
  %5 = icmp eq ptr %1, null
  %6 = select i1 %5, ptr @11, ptr %1
  %7 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %4) #24
  %8 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %6) #24
  %9 = add i64 %8, %7
  %10 = add i64 %9, 1
  %11 = tail call noalias ptr @malloc(i64 noundef %10) #23
  %12 = icmp eq ptr %11, null
  br i1 %12, label %16, label %13

13:                                               ; preds = %2
  tail call void @llvm.memcpy.p0.p0.i64(ptr nonnull align 1 %11, ptr nonnull align 1 %4, i64 %7, i1 false)
  %14 = getelementptr inbounds nuw i8, ptr %11, i64 %7
  tail call void @llvm.memcpy.p0.p0.i64(ptr nonnull align 1 %14, ptr nonnull align 1 %6, i64 %8, i1 false)
  %15 = getelementptr inbounds nuw i8, ptr %11, i64 %9
  store i8 0, ptr %15, align 1, !tbaa !5
  br label %16

16:                                               ; preds = %13, %2
  ret ptr %11
}

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: read)
declare i64 @strlen(ptr noundef captures(none)) local_unnamed_addr #7

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias writeonly captures(none), ptr noalias readonly captures(none), i64, i1 immarg) #8

; Function Attrs: mustprogress nofree norecurse nounwind willreturn memory(argmem: read) uwtable
define internal fastcc zeroext i1 @qc_string_eq(ptr noundef readonly captures(address_is_null) %0, ptr noundef readonly captures(address_is_null) %1) unnamed_addr #9 {
  %3 = icmp ne ptr %0, null
  %4 = icmp ne ptr %1, null
  %5 = and i1 %3, %4
  br i1 %5, label %6, label %9

6:                                                ; preds = %2
  %7 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(1) %1) #24
  %8 = icmp eq i32 %7, 0
  br label %9

9:                                                ; preds = %6, %2
  %10 = phi i1 [ %8, %6 ], [ false, %2 ]
  ret i1 %10
}

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: read)
declare i32 @strcmp(ptr noundef captures(none), ptr noundef captures(none)) local_unnamed_addr #7

; Function Attrs: mustprogress nofree nounwind uwtable
define internal fastcc noalias noundef ptr @qc_to_string_int(i32 noundef %0) unnamed_addr #3 {
  %2 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %2) #20
  %3 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 32, ptr noundef nonnull @.str.33, i32 noundef %0) #20
  %4 = icmp slt i32 %3, 0
  br i1 %4, label %11, label %5

5:                                                ; preds = %1
  %6 = add nuw nsw i32 %3, 1
  %7 = zext nneg i32 %6 to i64
  %8 = tail call noalias ptr @malloc(i64 noundef %7) #23
  %9 = icmp eq ptr %8, null
  br i1 %9, label %11, label %10

10:                                               ; preds = %5
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %8, ptr noundef nonnull align 16 dereferenceable(1) %2, i64 %7, i1 false)
  br label %11

11:                                               ; preds = %10, %5, %1
  %12 = phi ptr [ null, %1 ], [ %8, %10 ], [ null, %5 ]
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %2) #20
  ret ptr %12
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal fastcc i32 @qc_to_int_from_double(double noundef %0) unnamed_addr #10 {
  %2 = fptosi double %0 to i32
  ret i32 %2
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal fastcc noalias noundef ptr @qc_to_string_double(double noundef %0) unnamed_addr #3 {
  %2 = alloca [64 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 64, ptr nonnull %2) #20
  %3 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 64, ptr noundef nonnull @.str.34, double noundef %0) #20
  %4 = icmp slt i32 %3, 0
  br i1 %4, label %11, label %5

5:                                                ; preds = %1
  %6 = add nuw nsw i32 %3, 1
  %7 = zext nneg i32 %6 to i64
  %8 = tail call noalias ptr @malloc(i64 noundef %7) #23
  %9 = icmp eq ptr %8, null
  br i1 %9, label %11, label %10

10:                                               ; preds = %5
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %8, ptr noundef nonnull align 16 dereferenceable(1) %2, i64 %7, i1 false)
  br label %11

11:                                               ; preds = %10, %5, %1
  %12 = phi ptr [ null, %1 ], [ %8, %10 ], [ null, %5 ]
  call void @llvm.lifetime.end.p0(i64 64, ptr nonnull %2) #20
  ret ptr %12
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(readwrite, argmem: none) uwtable
define internal fastcc noalias noundef ptr @qc_to_string_bool(i1 noundef zeroext %0) unnamed_addr #11 {
  %2 = select i1 %0, i64 5, i64 6
  %3 = tail call noalias ptr @malloc(i64 noundef %2) #23
  %4 = icmp eq ptr %3, null
  br i1 %4, label %7, label %5

5:                                                ; preds = %1
  %6 = select i1 %0, ptr @.str.23, ptr @.str.24
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(5) %3, ptr noundef nonnull align 1 dereferenceable(5) %6, i64 %2, i1 false)
  br label %7

7:                                                ; preds = %5, %1
  ret ptr %3
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal fastcc void @qc_print_string(ptr noundef readonly captures(address_is_null) %0) unnamed_addr #3 {
  %2 = icmp eq ptr %0, null
  %3 = select i1 %2, ptr @11, ptr %0
  %4 = load ptr, ptr @stdout, align 8, !tbaa !8
  %5 = tail call i32 @fputs(ptr noundef nonnull %3, ptr noundef %4)
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @fputs(ptr noundef readonly captures(none), ptr noundef captures(none)) local_unnamed_addr #5

; Function Attrs: mustprogress nounwind uwtable
define internal fastcc i32 @qc_time() unnamed_addr #12 {
  %1 = tail call i64 @time(ptr noundef null) #20
  %2 = trunc i64 %1 to i32
  ret i32 %2
}

; Function Attrs: nounwind
declare i64 @time(ptr noundef) local_unnamed_addr #13

; Function Attrs: nounwind
declare i32 @rand() local_unnamed_addr #13

; Function Attrs: mustprogress nounwind uwtable
define internal fastcc range(i32 -99, 100) i32 @qc_random_range() unnamed_addr #12 {
  %1 = tail call i32 @rand() #20
  %2 = srem i32 %1, 100
  ret i32 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal fastcc noundef double @qc_to_double_from_int(i32 noundef %0) unnamed_addr #10 {
  %2 = sitofp i32 %0 to double
  ret double %2
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(write, argmem: none, inaccessiblemem: readwrite) uwtable
define internal fastcc noalias noundef ptr @qc_create_list(i32 noundef range(i32 0, 7) %0) unnamed_addr #14 {
  %2 = tail call noalias dereferenceable_or_null(24) ptr @malloc(i64 noundef 24) #23
  %3 = getelementptr inbounds nuw i8, ptr %2, i64 12
  store i32 4, ptr %3, align 4, !tbaa !11
  %4 = getelementptr inbounds nuw i8, ptr %2, i64 8
  store i32 0, ptr %4, align 8, !tbaa !15
  %5 = getelementptr inbounds nuw i8, ptr %2, i64 16
  store i32 %0, ptr %5, align 8, !tbaa !16
  %6 = tail call noalias dereferenceable_or_null(32) ptr @malloc(i64 noundef 32) #23
  store ptr %6, ptr %2, align 8, !tbaa !17
  ret ptr %2
}

; Function Attrs: mustprogress nounwind willreturn uwtable
define internal fastcc void @qc_list_push(ptr noundef captures(none) %0, ptr noundef nonnull readonly captures(none) %1, i32 noundef range(i32 0, 7) %2) unnamed_addr #15 {
  %4 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %5 = load i32, ptr %4, align 8, !tbaa !15
  %6 = getelementptr inbounds nuw i8, ptr %0, i64 12
  %7 = load i32, ptr %6, align 4, !tbaa !11
  %8 = icmp slt i32 %5, %7
  br i1 %8, label %15, label %9

9:                                                ; preds = %3
  %10 = shl nsw i32 %7, 1
  store i32 %10, ptr %6, align 4, !tbaa !11
  %11 = load ptr, ptr %0, align 8, !tbaa !17
  %12 = sext i32 %10 to i64
  %13 = shl nsw i64 %12, 3
  %14 = tail call ptr @realloc(ptr noundef %11, i64 noundef %13) #25
  store ptr %14, ptr %0, align 8, !tbaa !17
  br label %15

15:                                               ; preds = %9, %3
  %16 = icmp samesign ult i32 %2, 6
  br i1 %16, label %17, label %27

17:                                               ; preds = %15
  %18 = add nsw i32 %2, -2
  %19 = icmp ult i32 %18, 4
  br i1 %19, label %20, label %24

20:                                               ; preds = %17
  %21 = zext nneg i32 %18 to i64
  %22 = getelementptr inbounds nuw [4 x i64], ptr @switch.table.qc_map_set.53, i64 0, i64 %21
  %23 = load i64, ptr %22, align 8
  br label %24

24:                                               ; preds = %20, %17
  %25 = phi i64 [ %23, %20 ], [ 4, %17 ]
  %26 = tail call noalias ptr @malloc(i64 noundef %25) #23
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %26, ptr noundef nonnull align 1 dereferenceable(1) %1, i64 %25, i1 false)
  br label %29

27:                                               ; preds = %15
  %28 = load ptr, ptr %1, align 8, !tbaa !18
  br label %29

29:                                               ; preds = %27, %24
  %30 = phi ptr [ %28, %27 ], [ %26, %24 ]
  %31 = load ptr, ptr %0, align 8, !tbaa !17
  %32 = load i32, ptr %4, align 8, !tbaa !15
  %33 = add nsw i32 %32, 1
  store i32 %33, ptr %4, align 8, !tbaa !15
  %34 = sext i32 %32 to i64
  %35 = getelementptr inbounds ptr, ptr %31, i64 %34
  store ptr %30, ptr %35, align 8, !tbaa !18
  ret void
}

; Function Attrs: mustprogress nounwind willreturn uwtable
define internal fastcc void @qc_list_set(ptr noundef readonly captures(none) %0, i32 noundef %1, ptr noundef nonnull readonly captures(none) %2) unnamed_addr #15 {
  %4 = icmp slt i32 %1, 0
  br i1 %4, label %34, label %5

5:                                                ; preds = %3
  %6 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %7 = load i32, ptr %6, align 8, !tbaa !15
  %8 = icmp slt i32 %1, %7
  br i1 %8, label %9, label %34

9:                                                ; preds = %5
  %10 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %11 = load i32, ptr %10, align 8, !tbaa !16
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
  %22 = tail call noalias ptr @malloc(i64 noundef %21) #23
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %22, ptr noundef nonnull align 1 dereferenceable(1) %2, i64 %21, i1 false)
  %23 = load ptr, ptr %0, align 8, !tbaa !17
  %24 = zext nneg i32 %1 to i64
  %25 = getelementptr inbounds nuw ptr, ptr %23, i64 %24
  %26 = load ptr, ptr %25, align 8, !tbaa !18
  tail call void @free(ptr noundef %26) #20
  %27 = load ptr, ptr %0, align 8, !tbaa !17
  %28 = getelementptr inbounds nuw ptr, ptr %27, i64 %24
  store ptr %22, ptr %28, align 8, !tbaa !18
  br label %34

29:                                               ; preds = %9
  %30 = load ptr, ptr %2, align 8, !tbaa !18
  %31 = load ptr, ptr %0, align 8, !tbaa !17
  %32 = zext nneg i32 %1 to i64
  %33 = getelementptr inbounds nuw ptr, ptr %31, i64 %32
  store ptr %30, ptr %33, align 8, !tbaa !18
  br label %34

34:                                               ; preds = %29, %20, %5, %3
  ret void
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(read, inaccessiblemem: none) uwtable
define internal fastcc ptr @qc_list_get(ptr noundef readonly captures(none) %0, i32 noundef %1) unnamed_addr #16 {
  %3 = icmp slt i32 %1, 0
  br i1 %3, label %13, label %4

4:                                                ; preds = %2
  %5 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %6 = load i32, ptr %5, align 8, !tbaa !15
  %7 = icmp slt i32 %1, %6
  br i1 %7, label %8, label %13

8:                                                ; preds = %4
  %9 = load ptr, ptr %0, align 8, !tbaa !17
  %10 = zext nneg i32 %1 to i64
  %11 = getelementptr inbounds nuw ptr, ptr %9, i64 %10
  %12 = load ptr, ptr %11, align 8, !tbaa !18
  br label %13

13:                                               ; preds = %8, %4, %2
  %14 = phi ptr [ %12, %8 ], [ null, %4 ], [ null, %2 ]
  ret ptr %14
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(read, argmem: readwrite, inaccessiblemem: none) uwtable
define internal fastcc void @qc_list_pop(ptr noundef nonnull captures(none) %0) unnamed_addr #17 {
  %2 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %3 = load i32, ptr %2, align 8, !tbaa !15
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %7, label %5

5:                                                ; preds = %1
  %6 = add nsw i32 %3, -1
  store i32 %6, ptr %2, align 8, !tbaa !15
  br label %7

7:                                                ; preds = %5, %1
  ret void
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
define internal fastcc i32 @qc_list_length(ptr noundef readonly captures(none) %0) unnamed_addr #18 {
  %2 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %3 = load i32, ptr %2, align 8, !tbaa !15
  ret i32 %3
}

; Function Attrs: nofree nounwind
define internal fastcc void @"UnitTest::Test_Check.84"(ptr captures(none) %0) unnamed_addr #19 {
entry:
  %1 = getelementptr inbounds nuw i8, ptr %0, i64 4
  %Ran = load i32, ptr %1, align 4
  %Total = load i32, ptr %0, align 4
  %icmpge.not = icmp slt i32 %Ran, %Total
  br i1 %icmpge.not, label %ifcont, label %then

then:                                             ; preds = %entry
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %Messages = load ptr, ptr %2, align 8
  %list_len = tail call fastcc i32 @qc_list_length(ptr %Messages)
  %icmpgt = icmp sgt i32 %list_len, 0
  br i1 %icmpgt, label %foreach.body, label %ifcont2

ifcont:                                           ; preds = %ifcont2, %entry
  ret void

ifcont2:                                          ; preds = %foreach.end, %then
  %3 = getelementptr inbounds nuw i8, ptr %0, i64 12
  %Failed = load i32, ptr %3, align 4
  %fstr_i32 = tail call fastcc ptr @qc_to_string_int(i32 %Failed)
  %fstr_concat = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.244, ptr %fstr_i32)
  %fstr_concat7 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat, ptr nonnull @.str.245)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %4 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat7)
  tail call fastcc void @qc_print_string(ptr %4)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %5 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %Passed = load i32, ptr %5, align 4
  %fstr_i328 = tail call fastcc ptr @qc_to_string_int(i32 %Passed)
  %fstr_concat9 = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.247, ptr %fstr_i328)
  %fstr_concat10 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat9, ptr nonnull @.str.248)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %6 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat10)
  tail call fastcc void @qc_print_string(ptr %6)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  tail call fastcc void @qc_print_string(ptr nonnull @13)
  %Failed11 = load i32, ptr %3, align 4
  %icmpgt12 = icmp sgt i32 %Failed11, 0
  %. = select i1 %icmpgt12, ptr @14, ptr @15
  tail call fastcc void @qc_print_string(ptr nonnull %.)
  br label %ifcont

foreach.body:                                     ; preds = %then, %foreach.body
  %__foreach_i_message.016 = phi i32 [ %i_inc, %foreach.body ], [ 0, %then ]
  %elem_ptr = tail call fastcc ptr @qc_list_get(ptr %Messages, i32 %__foreach_i_message.016)
  tail call fastcc void @qc_print_string(ptr nonnull @13)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %7 = tail call fastcc ptr @qc_fmt_string(ptr %elem_ptr)
  tail call fastcc void @qc_print_string(ptr %7)
  tail call fastcc void @qc_print_string(ptr nonnull @10)
  %i_inc = add nuw nsw i32 %__foreach_i_message.016, 1
  %exitcond.not = icmp eq i32 %i_inc, %list_len
  br i1 %exitcond.not, label %foreach.end, label %foreach.body

foreach.end:                                      ; preds = %foreach.body
  tail call fastcc void @qc_print_string(ptr nonnull @13)
  br label %ifcont2
}

; Function Attrs: nounwind
define internal fastcc void @"UnitTest::Test_Success.85"(ptr captures(none) %0, ptr readonly captures(address_is_null) %1) unnamed_addr #20 {
entry:
  %push_arg = alloca ptr, align 8
  %2 = getelementptr inbounds nuw i8, ptr %0, i64 4
  %Ran = load i32, ptr %2, align 4
  %add = add i32 %Ran, 1
  store i32 %add, ptr %2, align 4
  %3 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %Passed = load i32, ptr %3, align 4
  %add1 = add i32 %Passed, 1
  store i32 %add1, ptr %3, align 4
  %4 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %ptr_ld = load ptr, ptr %4, align 8
  %fstr_i32 = tail call fastcc ptr @qc_to_string_int(i32 %add)
  %fstr_concat = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.252, ptr %fstr_i32)
  %fstr_concat4 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat, ptr nonnull @.str.253)
  %Total = load i32, ptr %0, align 4
  %fstr_i325 = tail call fastcc ptr @qc_to_string_int(i32 %Total)
  %fstr_concat6 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat4, ptr %fstr_i325)
  %fstr_concat7 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat6, ptr nonnull @.str.254)
  %str_concat = tail call fastcc ptr @qc_string_concat(ptr %1, ptr %fstr_concat7)
  store ptr %str_concat, ptr %push_arg, align 8
  %loaded_list_ptr = load ptr, ptr %ptr_ld, align 8
  call fastcc void @qc_list_push(ptr %loaded_list_ptr, ptr %push_arg, i32 6)
  tail call fastcc void @"UnitTest::Test_Check.84"(ptr nonnull %0)
  ret void
}

; Function Attrs: nounwind
define internal fastcc void @"UnitTest::Test_Fail.86"(ptr captures(none) %0, ptr readonly captures(address_is_null) %1) unnamed_addr #20 {
entry:
  %push_arg = alloca ptr, align 8
  %2 = getelementptr inbounds nuw i8, ptr %0, i64 4
  %Ran = load i32, ptr %2, align 4
  %add = add i32 %Ran, 1
  store i32 %add, ptr %2, align 4
  %3 = getelementptr inbounds nuw i8, ptr %0, i64 12
  %Failed = load i32, ptr %3, align 4
  %add1 = add i32 %Failed, 1
  store i32 %add1, ptr %3, align 4
  %4 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %ptr_ld = load ptr, ptr %4, align 8
  %fstr_i32 = tail call fastcc ptr @qc_to_string_int(i32 %add)
  %fstr_concat = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.255, ptr %fstr_i32)
  %fstr_concat4 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat, ptr nonnull @.str.256)
  %Total = load i32, ptr %0, align 4
  %fstr_i325 = tail call fastcc ptr @qc_to_string_int(i32 %Total)
  %fstr_concat6 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat4, ptr %fstr_i325)
  %fstr_concat7 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat6, ptr nonnull @.str.257)
  %str_concat = tail call fastcc ptr @qc_string_concat(ptr %1, ptr %fstr_concat7)
  store ptr %str_concat, ptr %push_arg, align 8
  %loaded_list_ptr = load ptr, ptr %ptr_ld, align 8
  call fastcc void @qc_list_push(ptr %loaded_list_ptr, ptr %push_arg, i32 6)
  tail call fastcc void @"UnitTest::Test_Check.84"(ptr nonnull %0)
  ret void
}

; Function Attrs: nofree norecurse nosync nounwind memory(read, inaccessiblemem: none)
define noundef i1 @"Collections::has_list<int>_int"(ptr readonly captures(none) %collection1, i32 %value2) local_unnamed_addr #21 {
entry:
  %coll_len = tail call fastcc i32 @qc_list_length(ptr %collection1)
  %foreach_cmp9 = icmp sgt i32 %coll_len, 0
  br i1 %foreach_cmp9, label %foreach.body, label %common.ret

foreach.body:                                     ; preds = %entry, %foreach.body
  %__foreach_i_val.010 = phi i32 [ %i_inc, %foreach.body ], [ 0, %entry ]
  %elem_ptr = tail call fastcc ptr @qc_list_get(ptr %collection1, i32 %__foreach_i_val.010)
  %elem = load i32, ptr %elem_ptr, align 4
  %icmpeq = icmp eq i32 %elem, %value2
  %i_inc = add nuw nsw i32 %__foreach_i_val.010, 1
  %exitcond.not = icmp eq i32 %i_inc, %coll_len
  %or.cond = select i1 %icmpeq, i1 true, i1 %exitcond.not
  br i1 %or.cond, label %common.ret, label %foreach.body

common.ret:                                       ; preds = %foreach.body, %entry
  %foreach_cmp.lcssa = phi i1 [ false, %entry ], [ %icmpeq, %foreach.body ]
  ret i1 %foreach_cmp.lcssa
}

; Function Attrs: nofree norecurse nosync nounwind memory(read, inaccessiblemem: none)
define range(i32 -2147483648, 2147483647) i32 @"Collections::index_of_list<int>_int"(ptr readonly captures(none) %collection1, i32 %value2) local_unnamed_addr #21 {
entry:
  %list_len = tail call fastcc i32 @qc_list_length(ptr %collection1)
  %icmplt14 = icmp sgt i32 %list_len, 0
  br i1 %icmplt14, label %for.body, label %common.ret

for.body:                                         ; preds = %entry, %ifcont
  %"Collections::i.015" = phi i32 [ %inc, %ifcont ], [ 0, %entry ]
  %list_elem_ptr = tail call fastcc ptr @qc_list_get(ptr %collection1, i32 %"Collections::i.015")
  %list_elem = load i32, ptr %list_elem_ptr, align 4
  %icmpeq = icmp eq i32 %list_elem, %value2
  br i1 %icmpeq, label %common.ret, label %ifcont

common.ret:                                       ; preds = %ifcont, %for.body, %entry
  %common.ret.op = phi i32 [ -1, %entry ], [ %"Collections::i.015", %for.body ], [ -1, %ifcont ]
  ret i32 %common.ret.op

ifcont:                                           ; preds = %for.body
  %inc = add nuw nsw i32 %"Collections::i.015", 1
  %exitcond.not = icmp eq i32 %inc, %list_len
  br i1 %exitcond.not, label %common.ret, label %for.body
}

; Function Attrs: nounwind
define noundef ptr @"Collections::reverse_list<int>"(ptr readonly returned captures(ret: address, provenance) %collection1) local_unnamed_addr #20 {
entry:
  %list_set_val18 = alloca i32, align 4
  %list_set_val = alloca i32, align 4
  %list_len = tail call fastcc i32 @qc_list_length(ptr %collection1)
  %sdiv = sdiv i32 %list_len, 2
  %icmplt31 = icmp sgt i32 %list_len, 1
  br i1 %icmplt31, label %for.body, label %for.end

for.body:                                         ; preds = %entry, %for.body
  %"Collections::i.032" = phi i32 [ %inc, %for.body ], [ 0, %entry ]
  %list_elem_ptr = tail call fastcc ptr @qc_list_get(ptr %collection1, i32 %"Collections::i.032")
  %list_elem = load i32, ptr %list_elem_ptr, align 4
  %0 = xor i32 %"Collections::i.032", -1
  %sub9 = add nsw i32 %list_len, %0
  %list_elem_ptr10 = tail call fastcc ptr @qc_list_get(ptr %collection1, i32 %sub9)
  %list_elem11 = load i32, ptr %list_elem_ptr10, align 4
  store i32 %list_elem11, ptr %list_set_val, align 4
  call fastcc void @qc_list_set(ptr %collection1, i32 %"Collections::i.032", ptr %list_set_val)
  store i32 %list_elem, ptr %list_set_val18, align 4
  call fastcc void @qc_list_set(ptr %collection1, i32 %sub9, ptr %list_set_val18)
  %inc = add nuw nsw i32 %"Collections::i.032", 1
  %exitcond.not = icmp eq i32 %inc, %sdiv
  br i1 %exitcond.not, label %for.end, label %for.body

for.end:                                          ; preds = %for.body, %entry
  ret ptr %collection1
}

; Function Attrs: nounwind
define ptr @"Collections::remove_list<int>_int"(ptr %collection1, i32 %value2) local_unnamed_addr #20 {
entry:
  %list_set_val = alloca i32, align 4
  %collection = alloca ptr, align 8
  store ptr %collection1, ptr %collection, align 8
  %list_len.i = tail call fastcc i32 @qc_list_length(ptr readonly %collection1)
  %icmplt14.i = icmp sgt i32 %list_len.i, 0
  br i1 %icmplt14.i, label %for.body.i, label %ifcont

for.body.i:                                       ; preds = %entry, %ifcont.i
  %"Collections::i.015.i" = phi i32 [ %inc.i, %ifcont.i ], [ 0, %entry ]
  %list_elem_ptr.i = tail call fastcc ptr @qc_list_get(ptr readonly %collection1, i32 %"Collections::i.015.i")
  %list_elem.i = load i32, ptr %list_elem_ptr.i, align 4
  %icmpeq.i = icmp eq i32 %list_elem.i, %value2
  br i1 %icmpeq.i, label %for.cond.preheader, label %ifcont.i

for.cond.preheader:                               ; preds = %for.body.i
  %list_len22 = tail call fastcc i32 @qc_list_length(ptr %collection1)
  %sub23 = add i32 %list_len22, -1
  %icmplt24 = icmp slt i32 %"Collections::i.015.i", %sub23
  br i1 %icmplt24, label %for.body, label %for.end

ifcont.i:                                         ; preds = %for.body.i
  %inc.i = add nuw nsw i32 %"Collections::i.015.i", 1
  %exitcond.not.i = icmp eq i32 %inc.i, %list_len.i
  br i1 %exitcond.not.i, label %ifcont, label %for.body.i

ifcont:                                           ; preds = %ifcont.i, %entry, %for.end
  %collection12 = phi ptr [ %collection1, %entry ], [ %collection12.pre, %for.end ], [ %collection1, %ifcont.i ]
  ret ptr %collection12

for.body:                                         ; preds = %for.cond.preheader, %for.body
  %"Collections::i.025" = phi i32 [ %add, %for.body ], [ %"Collections::i.015.i", %for.cond.preheader ]
  %add = add nuw nsw i32 %"Collections::i.025", 1
  %list_elem_ptr = tail call fastcc ptr @qc_list_get(ptr %collection1, i32 %add)
  %list_elem = load i32, ptr %list_elem_ptr, align 4
  store i32 %list_elem, ptr %list_set_val, align 4
  call fastcc void @qc_list_set(ptr %collection1, i32 %"Collections::i.025", ptr %list_set_val)
  %list_len = tail call fastcc i32 @qc_list_length(ptr %collection1)
  %sub = add i32 %list_len, -1
  %icmplt = icmp slt i32 %add, %sub
  br i1 %icmplt, label %for.body, label %for.end

for.end:                                          ; preds = %for.body, %for.cond.preheader
  call fastcc void @qc_list_pop(ptr %collection)
  %collection12.pre = load ptr, ptr %collection, align 8
  br label %ifcont
}

; Function Attrs: nounwind
define noundef i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr captures(none) %0, i32 %expected1, i32 %result2, ptr readonly captures(address_is_null) %FailMessage3, ptr readonly captures(address_is_null) %Call4) local_unnamed_addr #20 {
entry:
  %icmpne.not = icmp eq i32 %expected1, %result2
  br i1 %icmpne.not, label %else, label %then

then:                                             ; preds = %entry
  %1 = tail call fastcc i1 @qc_string_eq(ptr %Call4, ptr nonnull @11)
  br i1 %1, label %else10, label %then8

ifcont:                                           ; preds = %then34, %else36, %then8, %else10
  ret i32 0

else:                                             ; preds = %entry
  %2 = tail call fastcc i1 @qc_string_eq(ptr %Call4, ptr nonnull @.str.191)
  br i1 %2, label %else36, label %then34

then8:                                            ; preds = %then
  %fstr_concat = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.184, ptr %Call4)
  %fstr_concat12 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat, ptr nonnull @.str.185)
  %fstr_i32 = tail call fastcc ptr @qc_to_string_int(i32 %expected1)
  %fstr_concat14 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat12, ptr %fstr_i32)
  %fstr_concat15 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat14, ptr nonnull @.str.186)
  %fstr_i3217 = tail call fastcc ptr @qc_to_string_int(i32 %result2)
  %fstr_concat18 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat15, ptr %fstr_i3217)
  %fstr_concat19 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat18, ptr nonnull @.str.187)
  %fstr_concat21 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat19, ptr %FailMessage3)
  tail call fastcc void @"UnitTest::Test_Fail.86"(ptr %0, ptr %fstr_concat21)
  br label %ifcont

else10:                                           ; preds = %then
  %fstr_i3223 = tail call fastcc ptr @qc_to_string_int(i32 %expected1)
  %fstr_concat24 = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.188, ptr %fstr_i3223)
  %fstr_concat25 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat24, ptr nonnull @.str.189)
  %fstr_i3227 = tail call fastcc ptr @qc_to_string_int(i32 %result2)
  %fstr_concat28 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat25, ptr %fstr_i3227)
  %fstr_concat29 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat28, ptr nonnull @.str.190)
  %fstr_concat31 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat29, ptr %FailMessage3)
  tail call fastcc void @"UnitTest::Test_Fail.86"(ptr %0, ptr %fstr_concat31)
  br label %ifcont

then34:                                           ; preds = %else
  %fstr_concat38 = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.192, ptr %Call4)
  %fstr_concat39 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat38, ptr nonnull @.str.193)
  %fstr_i3241 = tail call fastcc ptr @qc_to_string_int(i32 %expected1)
  %fstr_concat42 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat39, ptr %fstr_i3241)
  %fstr_concat43 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat42, ptr nonnull @.str.194)
  %fstr_i3245 = tail call fastcc ptr @qc_to_string_int(i32 %expected1)
  %fstr_concat46 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat43, ptr %fstr_i3245)
  tail call fastcc void @"UnitTest::Test_Success.85"(ptr %0, ptr %fstr_concat46)
  br label %ifcont

else36:                                           ; preds = %else
  %fstr_i3248 = tail call fastcc ptr @qc_to_string_int(i32 %expected1)
  %fstr_concat49 = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.195, ptr %fstr_i3248)
  %fstr_concat50 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat49, ptr nonnull @.str.196)
  %fstr_i3252 = tail call fastcc ptr @qc_to_string_int(i32 %expected1)
  %fstr_concat53 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat50, ptr %fstr_i3252)
  tail call fastcc void @"UnitTest::Test_Success.85"(ptr %0, ptr %fstr_concat53)
  br label %ifcont
}

; Function Attrs: nounwind
define noundef i32 @"UnitTest::Test_AssertNotEqual_int_int_string_string"(ptr captures(none) %0, i32 %notExpected1, i32 %result2, ptr readonly captures(address_is_null) %FailMessage3, ptr readonly captures(address_is_null) %Call4) local_unnamed_addr #20 {
entry:
  %icmpeq = icmp eq i32 %notExpected1, %result2
  br i1 %icmpeq, label %then, label %else

then:                                             ; preds = %entry
  %1 = tail call fastcc i1 @qc_string_eq(ptr %Call4, ptr nonnull @.str.205)
  br i1 %1, label %else10, label %then8

ifcont:                                           ; preds = %then34, %else36, %then8, %else10
  ret i32 0

else:                                             ; preds = %entry
  %2 = tail call fastcc i1 @qc_string_eq(ptr %Call4, ptr nonnull @.str.213)
  br i1 %2, label %else36, label %then34

then8:                                            ; preds = %then
  %fstr_concat = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.206, ptr %Call4)
  %fstr_concat12 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat, ptr nonnull @.str.207)
  %fstr_i32 = tail call fastcc ptr @qc_to_string_int(i32 %notExpected1)
  %fstr_concat14 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat12, ptr %fstr_i32)
  %fstr_concat15 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat14, ptr nonnull @.str.208)
  %fstr_i3217 = tail call fastcc ptr @qc_to_string_int(i32 %notExpected1)
  %fstr_concat18 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat15, ptr %fstr_i3217)
  %fstr_concat19 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat18, ptr nonnull @.str.209)
  %fstr_concat21 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat19, ptr %FailMessage3)
  tail call fastcc void @"UnitTest::Test_Fail.86"(ptr %0, ptr %fstr_concat21)
  br label %ifcont

else10:                                           ; preds = %then
  %fstr_i3223 = tail call fastcc ptr @qc_to_string_int(i32 %notExpected1)
  %fstr_concat24 = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.210, ptr %fstr_i3223)
  %fstr_concat25 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat24, ptr nonnull @.str.211)
  %fstr_i3227 = tail call fastcc ptr @qc_to_string_int(i32 %notExpected1)
  %fstr_concat28 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat25, ptr %fstr_i3227)
  %fstr_concat29 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat28, ptr nonnull @.str.212)
  %fstr_concat31 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat29, ptr %FailMessage3)
  tail call fastcc void @"UnitTest::Test_Fail.86"(ptr %0, ptr %fstr_concat31)
  br label %ifcont

then34:                                           ; preds = %else
  %fstr_concat38 = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.214, ptr %Call4)
  %fstr_concat39 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat38, ptr nonnull @.str.215)
  %fstr_i3241 = tail call fastcc ptr @qc_to_string_int(i32 %result2)
  %fstr_concat42 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat39, ptr %fstr_i3241)
  %fstr_concat43 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat42, ptr nonnull @.str.216)
  %fstr_i3245 = tail call fastcc ptr @qc_to_string_int(i32 %notExpected1)
  %fstr_concat46 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat43, ptr %fstr_i3245)
  tail call fastcc void @"UnitTest::Test_Success.85"(ptr %0, ptr %fstr_concat46)
  br label %ifcont

else36:                                           ; preds = %else
  %fstr_i3248 = tail call fastcc ptr @qc_to_string_int(i32 %result2)
  %fstr_concat49 = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.217, ptr %fstr_i3248)
  %fstr_concat50 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat49, ptr nonnull @.str.218)
  %fstr_i3252 = tail call fastcc ptr @qc_to_string_int(i32 %notExpected1)
  %fstr_concat53 = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat50, ptr %fstr_i3252)
  tail call fastcc void @"UnitTest::Test_Success.85"(ptr %0, ptr %fstr_concat53)
  br label %ifcont
}

define noundef i32 @main() local_unnamed_addr {
entry:
  %list_set_val22.i.i = alloca i32, align 4
  %list_set_val.i.i = alloca i32, align 4
  %push_arg24.i.i = alloca i32, align 4
  %push_arg.i.i = alloca i32, align 4
  %test.i = alloca %"UnitTest::Test", align 8
  %temp_elem193.i = alloca i32, align 4
  %temp_elem192.i = alloca i32, align 4
  %temp_elem191.i = alloca i32, align 4
  %temp_elem190.i = alloca i32, align 4
  %temp_elem189.i = alloca i32, align 4
  %temp_elem154.i = alloca i32, align 4
  %temp_elem153.i = alloca i32, align 4
  %temp_elem152.i = alloca i32, align 4
  %temp_elem151.i = alloca i32, align 4
  %temp_elem150.i = alloca i32, align 4
  %temp_elem137.i = alloca i32, align 4
  %temp_elem136.i = alloca i32, align 4
  %temp_elem135.i = alloca i32, align 4
  %temp_elem134.i = alloca i32, align 4
  %temp_elem.i = alloca i32, align 4
  call void @llvm.lifetime.start.p0(i64 24, ptr nonnull %test.i)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %temp_elem193.i)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %temp_elem192.i)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %temp_elem191.i)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %temp_elem190.i)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %temp_elem189.i)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %temp_elem154.i)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %temp_elem153.i)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %temp_elem152.i)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %temp_elem151.i)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %temp_elem150.i)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %temp_elem137.i)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %temp_elem136.i)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %temp_elem135.i)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %temp_elem134.i)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %temp_elem.i)
  tail call fastcc void @qc_print_string(ptr nonnull @0)
  tail call fastcc void @qc_print_string(ptr nonnull @1)
  %list_ptr.i = tail call fastcc ptr @qc_create_list(i32 0)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %push_arg.i.i)
  %list_ptr.i.i = tail call fastcc ptr @qc_create_list(i32 0)
  store i32 0, ptr %push_arg.i.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr.i.i, ptr %push_arg.i.i, i32 0)
  store i32 2, ptr %push_arg.i.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr.i.i, ptr %push_arg.i.i, i32 0)
  store i32 4, ptr %push_arg.i.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr.i.i, ptr %push_arg.i.i, i32 0)
  store i32 6, ptr %push_arg.i.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr.i.i, ptr %push_arg.i.i, i32 0)
  store i32 8, ptr %push_arg.i.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr.i.i, ptr %push_arg.i.i, i32 0)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %push_arg.i.i)
  %list_len.i = tail call fastcc i32 @qc_list_length(ptr %list_ptr.i.i)
  %0 = sext i32 %list_len.i to i64
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %1 = tail call fastcc ptr @qc_fmt_int(i64 %0)
  tail call fastcc void @qc_print_string(ptr %1)
  tail call fastcc void @qc_print_string(ptr nonnull @10)
  %list_elem_ptr.i = tail call fastcc ptr @qc_list_get(ptr %list_ptr.i.i, i32 0)
  %list_elem.i = load i32, ptr %list_elem_ptr.i, align 4
  %fstr_i32.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem.i)
  %fstr_concat.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.104, ptr %fstr_i32.i)
  %fstr_concat3.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat.i, ptr nonnull @.str.105)
  %list_elem_ptr5.i = tail call fastcc ptr @qc_list_get(ptr %list_ptr.i.i, i32 1)
  %list_elem6.i = load i32, ptr %list_elem_ptr5.i, align 4
  %fstr_i327.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem6.i)
  %fstr_concat8.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat3.i, ptr %fstr_i327.i)
  %fstr_concat9.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat8.i, ptr nonnull @.str.106)
  %list_elem_ptr11.i = tail call fastcc ptr @qc_list_get(ptr %list_ptr.i.i, i32 2)
  %list_elem12.i = load i32, ptr %list_elem_ptr11.i, align 4
  %fstr_i3213.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem12.i)
  %fstr_concat14.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat9.i, ptr %fstr_i3213.i)
  %fstr_concat15.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat14.i, ptr nonnull @.str.107)
  %list_elem_ptr17.i = tail call fastcc ptr @qc_list_get(ptr %list_ptr.i.i, i32 3)
  %list_elem18.i = load i32, ptr %list_elem_ptr17.i, align 4
  %fstr_i3219.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem18.i)
  %fstr_concat20.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat15.i, ptr %fstr_i3219.i)
  %fstr_concat21.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat20.i, ptr nonnull @.str.108)
  %list_elem_ptr23.i = tail call fastcc ptr @qc_list_get(ptr %list_ptr.i.i, i32 4)
  %list_elem24.i = load i32, ptr %list_elem_ptr23.i, align 4
  %fstr_i3225.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem24.i)
  %fstr_concat26.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat21.i, ptr %fstr_i3225.i)
  %fstr_concat27.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat26.i, ptr nonnull @.str.109)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %2 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat27.i)
  tail call fastcc void @qc_print_string(ptr %2)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %list_ptr28.i = tail call fastcc ptr @qc_create_list(i32 0)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %push_arg24.i.i)
  %list_ptr.i289.i = tail call fastcc ptr @qc_create_list(i32 0)
  store i32 10, ptr %push_arg24.i.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr.i289.i, ptr %push_arg24.i.i, i32 0)
  store i32 9, ptr %push_arg24.i.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr.i289.i, ptr %push_arg24.i.i, i32 0)
  store i32 8, ptr %push_arg24.i.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr.i289.i, ptr %push_arg24.i.i, i32 0)
  store i32 7, ptr %push_arg24.i.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr.i289.i, ptr %push_arg24.i.i, i32 0)
  store i32 6, ptr %push_arg24.i.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr.i289.i, ptr %push_arg24.i.i, i32 0)
  store i32 5, ptr %push_arg24.i.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr.i289.i, ptr %push_arg24.i.i, i32 0)
  store i32 4, ptr %push_arg24.i.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr.i289.i, ptr %push_arg24.i.i, i32 0)
  store i32 3, ptr %push_arg24.i.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr.i289.i, ptr %push_arg24.i.i, i32 0)
  store i32 2, ptr %push_arg24.i.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr.i289.i, ptr %push_arg24.i.i, i32 0)
  store i32 1, ptr %push_arg24.i.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr.i289.i, ptr %push_arg24.i.i, i32 0)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %push_arg24.i.i)
  %list_len31.i = tail call fastcc i32 @qc_list_length(ptr %list_ptr.i289.i)
  %fstr_i3232.i = tail call fastcc ptr @qc_to_string_int(i32 %list_len31.i)
  %fstr_concat33.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.111, ptr %fstr_i3232.i)
  %fstr_concat34.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat33.i, ptr nonnull @.str.112)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %3 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat34.i)
  tail call fastcc void @qc_print_string(ptr %3)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  tail call fastcc void @qc_print_string(ptr nonnull @2)
  %builtin_call.i.i = tail call fastcc i32 @qc_time()
  %add.i291.i = add i32 %builtin_call.i.i, 1
  %builtin_call211.i.i = tail call fastcc i32 @qc_time()
  %icmplt12.i.i = icmp slt i32 %builtin_call211.i.i, %add.i291.i
  br i1 %icmplt12.i.i, label %for.cond.preheader.i.i, label %"Utils::sleep.exit.i"

for.cond.preheader.i.i:                           ; preds = %entry, %for.cond.preheader.i.i
  %builtin_call2.i.i = tail call fastcc i32 @qc_time()
  %icmplt.i292.i = icmp slt i32 %builtin_call2.i.i, %add.i291.i
  br i1 %icmplt.i292.i, label %for.cond.preheader.i.i, label %"Utils::sleep.exit.i"

"Utils::sleep.exit.i":                            ; preds = %for.cond.preheader.i.i, %entry
  tail call fastcc void @qc_print_string(ptr nonnull @3)
  tail call fastcc void @qc_print_string(ptr nonnull @4)
  %fstr_f64.i = tail call fastcc ptr @qc_to_string_double(double 0x400921FB54442D18)
  %fstr_concat37.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.117, ptr %fstr_f64.i)
  %fstr_concat38.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat37.i, ptr nonnull @.str.118)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %4 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat38.i)
  tail call fastcc void @qc_print_string(ptr %4)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %fstr_f6440.i = tail call fastcc ptr @qc_to_string_double(double 0x4005BF0A8B145769)
  %fstr_concat41.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.120, ptr %fstr_f6440.i)
  %fstr_concat42.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat41.i, ptr nonnull @.str.121)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %5 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat42.i)
  tail call fastcc void @qc_print_string(ptr %5)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %fstr_i3245.i = tail call fastcc ptr @qc_to_string_int(i32 10)
  %fstr_concat50.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.123, ptr %fstr_i3245.i)
  %fstr_concat51.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat50.i, ptr nonnull @.str.124)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %6 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat51.i)
  tail call fastcc void @qc_print_string(ptr %6)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %fstr_i3261.i = tail call fastcc ptr @qc_to_string_int(i32 5)
  %fstr_concat69.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.126, ptr %fstr_i3261.i)
  %fstr_concat70.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat69.i, ptr nonnull @.str.127)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %7 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat70.i)
  tail call fastcc void @qc_print_string(ptr %7)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %to_double.i.i = tail call fastcc double @qc_to_double_from_int(i32 16)
  %sqrt.i.i = tail call double @llvm.sqrt.f64(double %to_double.i.i)
  %abs.i.i = tail call double @llvm.fabs.f64(double %sqrt.i.i)
  %isinf.i.i = fcmp oeq double %to_double.i.i, 0xFFF0000000000000
  %pow.i.i = select i1 %isinf.i.i, double 0x7FF0000000000000, double %abs.i.i
  %fstr_f6485.i = tail call fastcc ptr @qc_to_string_double(double %pow.i.i)
  %fstr_concat87.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.129, ptr %fstr_f6485.i)
  %fstr_concat88.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat87.i, ptr nonnull @.str.130)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %8 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat88.i)
  tail call fastcc void @qc_print_string(ptr %8)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %fstr_f64103.i = tail call fastcc ptr @qc_to_string_double(double 4.200000e+01)
  %fstr_concat105.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.132, ptr %fstr_f64103.i)
  %fstr_concat106.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat105.i, ptr nonnull @.str.133)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %9 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat106.i)
  tail call fastcc void @qc_print_string(ptr %9)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %to_int.i.i = tail call fastcc i32 @qc_to_int_from_double(double 3.200000e+00)
  %to_double5.i.i = tail call fastcc double @qc_to_double_from_int(i32 %to_int.i.i)
  %fcmpeq.i.i = fcmp une double %to_double5.i.i, 3.200000e+00
  %add.i298.i = zext i1 %fcmpeq.i.i to i32
  %spec.select.i.i = add i32 %to_int.i.i, %add.i298.i
  %fstr_i32109.i = tail call fastcc ptr @qc_to_string_int(i32 %spec.select.i.i)
  %fstr_concat110.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.135, ptr %fstr_i32109.i)
  %fstr_concat111.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat110.i, ptr nonnull @.str.136)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %10 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat111.i)
  tail call fastcc void @qc_print_string(ptr %10)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %to_int.i300.i = tail call fastcc i32 @qc_to_int_from_double(double 3.800000e+00)
  %fstr_i32114.i = tail call fastcc ptr @qc_to_string_int(i32 %to_int.i300.i)
  %fstr_concat115.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.138, ptr %fstr_i32114.i)
  %fstr_concat116.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat115.i, ptr nonnull @.str.139)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %11 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat116.i)
  tail call fastcc void @qc_print_string(ptr %11)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %fstr_f64118.i = tail call fastcc ptr @qc_to_string_double(double 0.000000e+00)
  %fstr_concat119.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.141, ptr %fstr_f64118.i)
  %fstr_concat120.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat119.i, ptr nonnull @.str.142)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %12 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat120.i)
  tail call fastcc void @qc_print_string(ptr %12)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %fstr_f64122.i = tail call fastcc ptr @qc_to_string_double(double 1.000000e+00)
  %fstr_concat123.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.144, ptr %fstr_f64122.i)
  %fstr_concat124.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat123.i, ptr nonnull @.str.145)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %13 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat124.i)
  tail call fastcc void @qc_print_string(ptr %13)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %fstr_f64126.i = tail call fastcc ptr @qc_to_string_double(double 0.000000e+00)
  %fstr_concat127.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.147, ptr %fstr_f64126.i)
  %fstr_concat128.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat127.i, ptr nonnull @.str.148)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %14 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat128.i)
  tail call fastcc void @qc_print_string(ptr %14)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  br label %for.body.i303.i

for.body.i303.i:                                  ; preds = %for.body.i303.i, %"Utils::sleep.exit.i"
  %"Math::i.045.i.i" = phi i32 [ 1, %"Utils::sleep.exit.i" ], [ %inc23.i.i, %for.body.i303.i ]
  %"Math::term.044.i.i" = phi double [ 3.590000e-01, %"Utils::sleep.exit.i" ], [ %fmul19.i.i, %for.body.i303.i ]
  %"Math::result.043.i.i" = phi double [ 0.000000e+00, %"Utils::sleep.exit.i" ], [ %fadd.i.i, %for.body.i303.i ]
  %to_double.i304.i = tail call fastcc double @qc_to_double_from_int(i32 %"Math::i.045.i.i")
  %fdiv16.i.i = fdiv double %"Math::term.044.i.i", %to_double.i304.i
  %fadd.i.i = fadd double %"Math::result.043.i.i", %fdiv16.i.i
  %fmul19.i.i = fmul double %"Math::term.044.i.i", -3.590000e-01
  %inc23.i.i = add nuw nsw i32 %"Math::i.045.i.i", 1
  %exitcond.not.i.i = icmp eq i32 %inc23.i.i, 21
  br i1 %exitcond.not.i.i, label %"Math::log.exit.i", label %for.body.i303.i

"Math::log.exit.i":                               ; preds = %for.body.i303.i
  %fadd26.i.i = fadd double %fadd.i.i, 0x3FE62E42FEFA39EF
  %fstr_f64130.i = tail call fastcc ptr @qc_to_string_double(double %fadd26.i.i)
  %fstr_concat131.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.150, ptr %fstr_f64130.i)
  %fstr_concat132.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat131.i, ptr nonnull @.str.151)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %15 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat132.i)
  tail call fastcc void @qc_print_string(ptr %15)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  tail call fastcc void @qc_print_string(ptr nonnull @5)
  %list_ptr133.i = tail call fastcc ptr @qc_create_list(i32 0)
  store i32 1, ptr %temp_elem.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr133.i, ptr %temp_elem.i, i32 0)
  store i32 2, ptr %temp_elem134.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr133.i, ptr %temp_elem134.i, i32 0)
  store i32 3, ptr %temp_elem135.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr133.i, ptr %temp_elem135.i, i32 0)
  store i32 4, ptr %temp_elem136.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr133.i, ptr %temp_elem136.i, i32 0)
  store i32 5, ptr %temp_elem137.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr133.i, ptr %temp_elem137.i, i32 0)
  %coll_len.i.i = tail call fastcc i32 @qc_list_length(ptr readonly %list_ptr133.i)
  %foreach_cmp9.i.i = icmp sgt i32 %coll_len.i.i, 0
  br i1 %foreach_cmp9.i.i, label %foreach.body.i.i, label %"Collections::has_list<int>_int.exit317.critedge.i"

foreach.body.i.i:                                 ; preds = %"Math::log.exit.i", %foreach.body.i.i
  %__foreach_i_val.010.i.i = phi i32 [ %i_inc.i.i, %foreach.body.i.i ], [ 0, %"Math::log.exit.i" ]
  %elem_ptr.i.i = tail call fastcc ptr @qc_list_get(ptr readonly %list_ptr133.i, i32 %__foreach_i_val.010.i.i)
  %elem.i.i = load i32, ptr %elem_ptr.i.i, align 4
  %icmpeq.i.i = icmp eq i32 %elem.i.i, 3
  %i_inc.i.i = add nuw nsw i32 %__foreach_i_val.010.i.i, 1
  %exitcond.not.i305.i = icmp eq i32 %i_inc.i.i, %coll_len.i.i
  %or.cond.i = select i1 %icmpeq.i.i, i1 true, i1 %exitcond.not.i305.i
  br i1 %or.cond.i, label %"Collections::has_list<int>_int.exit.i", label %foreach.body.i.i

"Collections::has_list<int>_int.exit.i":          ; preds = %foreach.body.i.i
  %fstr_bool.i = tail call fastcc ptr @qc_to_string_bool(i1 %icmpeq.i.i)
  %fstr_concat139.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.154, ptr %fstr_bool.i)
  %fstr_concat140.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat139.i, ptr nonnull @.str.155)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %16 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat140.i)
  tail call fastcc void @qc_print_string(ptr %16)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  br label %foreach.body.i309.i

foreach.body.i309.i:                              ; preds = %foreach.body.i309.i, %"Collections::has_list<int>_int.exit.i"
  %__foreach_i_val.010.i310.i = phi i32 [ 0, %"Collections::has_list<int>_int.exit.i" ], [ %i_inc.i315.i, %foreach.body.i309.i ]
  %elem_ptr.i311.i = tail call fastcc ptr @qc_list_get(ptr readonly %list_ptr133.i, i32 %__foreach_i_val.010.i310.i)
  %elem.i312.i = load i32, ptr %elem_ptr.i311.i, align 4
  %icmpeq.i313.i = icmp eq i32 %elem.i312.i, 10
  %i_inc.i315.i = add nuw nsw i32 %__foreach_i_val.010.i310.i, 1
  %exitcond.not.i316.i = icmp eq i32 %i_inc.i315.i, %coll_len.i.i
  %or.cond = select i1 %icmpeq.i313.i, i1 true, i1 %exitcond.not.i316.i
  br i1 %or.cond, label %"Collections::has_list<int>_int.exit317.i", label %foreach.body.i309.i

"Collections::has_list<int>_int.exit317.critedge.i": ; preds = %"Math::log.exit.i"
  %fstr_bool.c.i = tail call fastcc ptr @qc_to_string_bool(i1 false)
  %fstr_concat139.c.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.154, ptr %fstr_bool.c.i)
  %fstr_concat140.c.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat139.c.i, ptr nonnull @.str.155)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %17 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat140.c.i)
  tail call fastcc void @qc_print_string(ptr %17)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  br label %"Collections::has_list<int>_int.exit317.i"

"Collections::has_list<int>_int.exit317.i":       ; preds = %foreach.body.i309.i, %"Collections::has_list<int>_int.exit317.critedge.i"
  %foreach_cmp.lcssa.i308.i = phi i1 [ false, %"Collections::has_list<int>_int.exit317.critedge.i" ], [ %icmpeq.i313.i, %foreach.body.i309.i ]
  %fstr_bool142.i = tail call fastcc ptr @qc_to_string_bool(i1 %foreach_cmp.lcssa.i308.i)
  %fstr_concat143.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.157, ptr %fstr_bool142.i)
  %fstr_concat144.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat143.i, ptr nonnull @.str.158)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %18 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat144.i)
  tail call fastcc void @qc_print_string(ptr %18)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  br i1 %foreach_cmp9.i.i, label %for.body.i319.i, label %"Collections::index_of_list<int>_int.exit.i"

for.body.i319.i:                                  ; preds = %"Collections::has_list<int>_int.exit317.i", %ifcont.i.i
  %"Collections::i.015.i.i" = phi i32 [ %inc.i.i, %ifcont.i.i ], [ 0, %"Collections::has_list<int>_int.exit317.i" ]
  %list_elem_ptr.i.i = tail call fastcc ptr @qc_list_get(ptr readonly %list_ptr133.i, i32 %"Collections::i.015.i.i")
  %list_elem.i.i = load i32, ptr %list_elem_ptr.i.i, align 4
  %icmpeq.i320.i = icmp eq i32 %list_elem.i.i, 3
  br i1 %icmpeq.i320.i, label %"Collections::index_of_list<int>_int.exit.i", label %ifcont.i.i

ifcont.i.i:                                       ; preds = %for.body.i319.i
  %inc.i.i = add nuw nsw i32 %"Collections::i.015.i.i", 1
  %exitcond.not.i321.i = icmp eq i32 %inc.i.i, %coll_len.i.i
  br i1 %exitcond.not.i321.i, label %"Collections::index_of_list<int>_int.exit.i", label %for.body.i319.i

"Collections::index_of_list<int>_int.exit.i":     ; preds = %ifcont.i.i, %for.body.i319.i, %"Collections::has_list<int>_int.exit317.i"
  %common.ret.op.i318.i = phi i32 [ -1, %"Collections::has_list<int>_int.exit317.i" ], [ %"Collections::i.015.i.i", %for.body.i319.i ], [ -1, %ifcont.i.i ]
  %fstr_i32146.i = tail call fastcc ptr @qc_to_string_int(i32 %common.ret.op.i318.i)
  %fstr_concat147.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.160, ptr %fstr_i32146.i)
  %fstr_concat148.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat147.i, ptr nonnull @.str.161)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %19 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat148.i)
  tail call fastcc void @qc_print_string(ptr %19)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %list_ptr149.i = tail call fastcc ptr @qc_create_list(i32 0)
  store i32 5, ptr %temp_elem150.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr149.i, ptr %temp_elem150.i, i32 0)
  store i32 2, ptr %temp_elem151.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr149.i, ptr %temp_elem151.i, i32 0)
  store i32 8, ptr %temp_elem152.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr149.i, ptr %temp_elem152.i, i32 0)
  store i32 1, ptr %temp_elem153.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr149.i, ptr %temp_elem153.i, i32 0)
  store i32 9, ptr %temp_elem154.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr149.i, ptr %temp_elem154.i, i32 0)
  %list_ptr155.i = tail call fastcc ptr @qc_create_list(i32 0)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %list_set_val22.i.i)
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %list_set_val.i.i)
  %list_len.i322.i = tail call fastcc i32 @qc_list_length(ptr readonly %list_ptr149.i)
  br label %for.cond.preheader.i323.i

while.cond.loopexit.i.i:                          ; preds = %ifcont.i329.i
  br i1 %"Collections::swapped.2.i.i", label %for.cond.preheader.i323.i, label %"Collections::sort.exit.i"

for.cond.preheader.i323.i:                        ; preds = %while.cond.loopexit.i.i, %"Collections::index_of_list<int>_int.exit.i"
  %indvars.iv.in.i.i = phi i32 [ %list_len.i322.i, %"Collections::index_of_list<int>_int.exit.i" ], [ %indvars.iv.i.i, %while.cond.loopexit.i.i ]
  %indvars.iv.i.i = add i32 %indvars.iv.in.i.i, -1
  %icmplt39.i.i = icmp sgt i32 %indvars.iv.i.i, 0
  br i1 %icmplt39.i.i, label %for.body.i325.i, label %"Collections::sort.exit.i"

for.body.i325.i:                                  ; preds = %for.cond.preheader.i323.i, %ifcont.i329.i
  %"Collections::i.041.i.i" = phi i32 [ %add.i328.i, %ifcont.i329.i ], [ 0, %for.cond.preheader.i323.i ]
  %"Collections::swapped.140.i.i" = phi i1 [ %"Collections::swapped.2.i.i", %ifcont.i329.i ], [ false, %for.cond.preheader.i323.i ]
  %list_elem_ptr.i326.i = tail call fastcc ptr @qc_list_get(ptr readonly %list_ptr149.i, i32 %"Collections::i.041.i.i")
  %list_elem.i327.i = load i32, ptr %list_elem_ptr.i326.i, align 4
  %add.i328.i = add nuw nsw i32 %"Collections::i.041.i.i", 1
  %list_elem_ptr6.i.i = tail call fastcc ptr @qc_list_get(ptr readonly %list_ptr149.i, i32 %add.i328.i)
  %list_elem7.i.i = load i32, ptr %list_elem_ptr6.i.i, align 4
  %icmpgt.i.i = icmp sgt i32 %list_elem.i327.i, %list_elem7.i.i
  br i1 %icmpgt.i.i, label %then.i.i, label %ifcont.i329.i

then.i.i:                                         ; preds = %for.body.i325.i
  store i32 %list_elem7.i.i, ptr %list_set_val.i.i, align 4
  call fastcc void @qc_list_set(ptr readonly %list_ptr149.i, i32 %"Collections::i.041.i.i", ptr %list_set_val.i.i)
  store i32 %list_elem.i327.i, ptr %list_set_val22.i.i, align 4
  call fastcc void @qc_list_set(ptr readonly %list_ptr149.i, i32 %add.i328.i, ptr %list_set_val22.i.i)
  br label %ifcont.i329.i

ifcont.i329.i:                                    ; preds = %then.i.i, %for.body.i325.i
  %"Collections::swapped.2.i.i" = phi i1 [ true, %then.i.i ], [ %"Collections::swapped.140.i.i", %for.body.i325.i ]
  %exitcond.not.i330.i = icmp eq i32 %add.i328.i, %indvars.iv.i.i
  br i1 %exitcond.not.i330.i, label %while.cond.loopexit.i.i, label %for.body.i325.i

"Collections::sort.exit.i":                       ; preds = %for.cond.preheader.i323.i, %while.cond.loopexit.i.i
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %list_set_val22.i.i)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %list_set_val.i.i)
  %list_elem_ptr159.i = tail call fastcc ptr @qc_list_get(ptr %list_ptr149.i, i32 0)
  %list_elem160.i = load i32, ptr %list_elem_ptr159.i, align 4
  %fstr_i32161.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem160.i)
  %fstr_concat162.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.163, ptr %fstr_i32161.i)
  %fstr_concat163.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat162.i, ptr nonnull @.str.164)
  %list_elem_ptr165.i = tail call fastcc ptr @qc_list_get(ptr %list_ptr149.i, i32 1)
  %list_elem166.i = load i32, ptr %list_elem_ptr165.i, align 4
  %fstr_i32167.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem166.i)
  %fstr_concat168.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat163.i, ptr %fstr_i32167.i)
  %fstr_concat169.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat168.i, ptr nonnull @.str.165)
  %list_elem_ptr171.i = tail call fastcc ptr @qc_list_get(ptr %list_ptr149.i, i32 2)
  %list_elem172.i = load i32, ptr %list_elem_ptr171.i, align 4
  %fstr_i32173.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem172.i)
  %fstr_concat174.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat169.i, ptr %fstr_i32173.i)
  %fstr_concat175.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat174.i, ptr nonnull @.str.166)
  %list_elem_ptr177.i = tail call fastcc ptr @qc_list_get(ptr %list_ptr149.i, i32 3)
  %list_elem178.i = load i32, ptr %list_elem_ptr177.i, align 4
  %fstr_i32179.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem178.i)
  %fstr_concat180.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat175.i, ptr %fstr_i32179.i)
  %fstr_concat181.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat180.i, ptr nonnull @.str.167)
  %list_elem_ptr183.i = tail call fastcc ptr @qc_list_get(ptr %list_ptr149.i, i32 4)
  %list_elem184.i = load i32, ptr %list_elem_ptr183.i, align 4
  %fstr_i32185.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem184.i)
  %fstr_concat186.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat181.i, ptr %fstr_i32185.i)
  %fstr_concat187.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat186.i, ptr nonnull @.str.168)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %20 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat187.i)
  tail call fastcc void @qc_print_string(ptr %20)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %list_ptr188.i = tail call fastcc ptr @qc_create_list(i32 0)
  store i32 1, ptr %temp_elem189.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr188.i, ptr %temp_elem189.i, i32 0)
  store i32 2, ptr %temp_elem190.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr188.i, ptr %temp_elem190.i, i32 0)
  store i32 3, ptr %temp_elem191.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr188.i, ptr %temp_elem191.i, i32 0)
  store i32 4, ptr %temp_elem192.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr188.i, ptr %temp_elem192.i, i32 0)
  store i32 5, ptr %temp_elem193.i, align 4
  call fastcc void @qc_list_push(ptr %list_ptr188.i, ptr %temp_elem193.i, i32 0)
  %list_ptr194.i = tail call fastcc ptr @qc_create_list(i32 0)
  %21 = tail call ptr @"Collections::reverse_list<int>"(ptr %list_ptr188.i)
  %list_elem_ptr197.i = tail call fastcc ptr @qc_list_get(ptr %list_ptr188.i, i32 0)
  %list_elem198.i = load i32, ptr %list_elem_ptr197.i, align 4
  %fstr_i32199.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem198.i)
  %fstr_concat200.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.170, ptr %fstr_i32199.i)
  %fstr_concat201.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat200.i, ptr nonnull @.str.171)
  %list_elem_ptr203.i = tail call fastcc ptr @qc_list_get(ptr %list_ptr188.i, i32 1)
  %list_elem204.i = load i32, ptr %list_elem_ptr203.i, align 4
  %fstr_i32205.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem204.i)
  %fstr_concat206.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat201.i, ptr %fstr_i32205.i)
  %fstr_concat207.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat206.i, ptr nonnull @.str.172)
  %list_elem_ptr209.i = tail call fastcc ptr @qc_list_get(ptr %list_ptr188.i, i32 2)
  %list_elem210.i = load i32, ptr %list_elem_ptr209.i, align 4
  %fstr_i32211.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem210.i)
  %fstr_concat212.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat207.i, ptr %fstr_i32211.i)
  %fstr_concat213.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat212.i, ptr nonnull @.str.173)
  %list_elem_ptr215.i = tail call fastcc ptr @qc_list_get(ptr %list_ptr188.i, i32 3)
  %list_elem216.i = load i32, ptr %list_elem_ptr215.i, align 4
  %fstr_i32217.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem216.i)
  %fstr_concat218.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat213.i, ptr %fstr_i32217.i)
  %fstr_concat219.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat218.i, ptr nonnull @.str.174)
  %list_elem_ptr221.i = tail call fastcc ptr @qc_list_get(ptr %list_ptr188.i, i32 4)
  %list_elem222.i = load i32, ptr %list_elem_ptr221.i, align 4
  %fstr_i32223.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem222.i)
  %fstr_concat224.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat219.i, ptr %fstr_i32223.i)
  %fstr_concat225.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat224.i, ptr nonnull @.str.175)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %22 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat225.i)
  tail call fastcc void @qc_print_string(ptr %22)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %23 = tail call ptr @"Collections::remove_list<int>_int"(ptr %list_ptr188.i, i32 2)
  %list_elem_ptr228.i = tail call fastcc ptr @qc_list_get(ptr %23, i32 0)
  %list_elem229.i = load i32, ptr %list_elem_ptr228.i, align 4
  %fstr_i32230.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem229.i)
  %fstr_concat231.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.177, ptr %fstr_i32230.i)
  %fstr_concat232.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat231.i, ptr nonnull @.str.178)
  %list_elem_ptr234.i = tail call fastcc ptr @qc_list_get(ptr %23, i32 1)
  %list_elem235.i = load i32, ptr %list_elem_ptr234.i, align 4
  %fstr_i32236.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem235.i)
  %fstr_concat237.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat232.i, ptr %fstr_i32236.i)
  %fstr_concat238.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat237.i, ptr nonnull @.str.179)
  %list_elem_ptr240.i = tail call fastcc ptr @qc_list_get(ptr %23, i32 2)
  %list_elem241.i = load i32, ptr %list_elem_ptr240.i, align 4
  %fstr_i32242.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem241.i)
  %fstr_concat243.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat238.i, ptr %fstr_i32242.i)
  %fstr_concat244.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat243.i, ptr nonnull @.str.180)
  %list_elem_ptr246.i = tail call fastcc ptr @qc_list_get(ptr %23, i32 3)
  %list_elem247.i = load i32, ptr %list_elem_ptr246.i, align 4
  %fstr_i32248.i = tail call fastcc ptr @qc_to_string_int(i32 %list_elem247.i)
  %fstr_concat249.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat244.i, ptr %fstr_i32248.i)
  %fstr_concat250.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat249.i, ptr nonnull @.str.181)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %24 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat250.i)
  tail call fastcc void @qc_print_string(ptr %24)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  tail call fastcc void @qc_print_string(ptr nonnull @6)
  %25 = tail call fastcc ptr @qc_create_list(i32 6)
  %26 = getelementptr inbounds nuw i8, ptr %test.i, i64 16
  store ptr %25, ptr %26, align 8
  store i32 5, ptr %test.i, align 8
  %27 = getelementptr inbounds nuw i8, ptr %test.i, i64 4
  store i32 0, ptr %27, align 4
  %28 = getelementptr inbounds nuw i8, ptr %test.i, i64 8
  store i32 0, ptr %28, align 8
  %29 = getelementptr inbounds nuw i8, ptr %test.i, i64 12
  store i32 0, ptr %29, align 4
  %AssertEqual_result.i = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr nonnull %test.i, i32 5, i32 5, ptr nonnull @.str.197, ptr nonnull @.str.198)
  %AssertEqual_result251.i = call i32 @"UnitTest::Test_AssertEqual_int_int_string_string"(ptr nonnull %test.i, i32 10, i32 10, ptr nonnull @.str.199, ptr nonnull @.str.200)
  %30 = tail call fastcc i1 @qc_string_eq(ptr nonnull @.str.202, ptr nonnull @.str.262)
  br i1 %30, label %"UnitTest::Test_AssertTrue.88.exit.i", label %then14.i.i

then14.i.i:                                       ; preds = %"Collections::sort.exit.i"
  %fstr_concat18.i.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.263, ptr nonnull @.str.202)
  %fstr_concat19.i.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat18.i.i, ptr nonnull @.str.264)
  br label %"UnitTest::Test_AssertTrue.88.exit.i"

"UnitTest::Test_AssertTrue.88.exit.i":            ; preds = %then14.i.i, %"Collections::sort.exit.i"
  %fstr_concat19.sink.i.i = phi ptr [ %fstr_concat19.i.i, %then14.i.i ], [ @.str.265, %"Collections::sort.exit.i" ]
  call fastcc void @"UnitTest::Test_Success.85"(ptr nonnull %test.i, ptr %fstr_concat19.sink.i.i)
  %31 = tail call fastcc i1 @qc_string_eq(ptr nonnull @.str.204, ptr nonnull @.str.270)
  br i1 %31, label %__user_entry.exit, label %then14.i332.i

then14.i332.i:                                    ; preds = %"UnitTest::Test_AssertTrue.88.exit.i"
  %fstr_concat18.i333.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.271, ptr nonnull @.str.204)
  %fstr_concat19.i334.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat18.i333.i, ptr nonnull @.str.272)
  br label %__user_entry.exit

__user_entry.exit:                                ; preds = %"UnitTest::Test_AssertTrue.88.exit.i", %then14.i332.i
  %fstr_concat19.sink.i336.i = phi ptr [ %fstr_concat19.i334.i, %then14.i332.i ], [ @.str.273, %"UnitTest::Test_AssertTrue.88.exit.i" ]
  call fastcc void @"UnitTest::Test_Success.85"(ptr nonnull %test.i, ptr %fstr_concat19.sink.i336.i)
  %AssertNotEqual_result.i = call i32 @"UnitTest::Test_AssertNotEqual_int_int_string_string"(ptr nonnull %test.i, i32 5, i32 10, ptr nonnull @.str.219, ptr nonnull @.str.220)
  tail call fastcc void @qc_print_string(ptr nonnull @7)
  %fstr_i32.i.i = tail call fastcc ptr @qc_to_string_int(i32 75)
  %fstr_concat.i.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.277, ptr %fstr_i32.i.i)
  %fstr_concat1.i.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat.i.i, ptr nonnull @.str.278)
  %fstr_i322.i.i = tail call fastcc ptr @qc_to_string_int(i32 25)
  %fstr_concat3.i.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat1.i.i, ptr %fstr_i322.i.i)
  %fstr_concat4.i.i = tail call fastcc noalias noundef ptr @qc_string_concat(ptr %fstr_concat3.i.i, ptr nonnull @.str.279)
  %fstr_concat252.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.223, ptr %fstr_concat4.i.i)
  %fstr_concat253.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat252.i, ptr nonnull @.str.224)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %32 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat253.i)
  tail call fastcc void @qc_print_string(ptr %32)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  tail call fastcc void @qc_print_string(ptr nonnull @8)
  %builtin_call.i338.i = tail call fastcc i32 @qc_random_range()
  %icmplt.i340.i = icmp sgt i32 %builtin_call.i338.i, 24
  %inc.i = zext i1 %icmplt.i340.i to i32
  %builtin_call.i338.1.i = tail call fastcc i32 @qc_random_range()
  %icmplt.i340.1.i = icmp sgt i32 %builtin_call.i338.1.i, 24
  %inc.1.i = zext i1 %icmplt.i340.1.i to i32
  %spec.select.1.i = add nuw nsw i32 %inc.1.i, %inc.i
  %builtin_call.i338.2.i = tail call fastcc i32 @qc_random_range()
  %icmplt.i340.2.i = icmp sgt i32 %builtin_call.i338.2.i, 24
  %inc.2.i = zext i1 %icmplt.i340.2.i to i32
  %spec.select.2.i = add nuw nsw i32 %spec.select.1.i, %inc.2.i
  %builtin_call.i338.3.i = tail call fastcc i32 @qc_random_range()
  %icmplt.i340.3.i = icmp sgt i32 %builtin_call.i338.3.i, 24
  %inc.3.i = zext i1 %icmplt.i340.3.i to i32
  %spec.select.3.i = add nuw nsw i32 %spec.select.2.i, %inc.3.i
  %builtin_call.i338.4.i = tail call fastcc i32 @qc_random_range()
  %icmplt.i340.4.i = icmp sgt i32 %builtin_call.i338.4.i, 24
  %inc.4.i = zext i1 %icmplt.i340.4.i to i32
  %spec.select.4.i = add nuw nsw i32 %spec.select.3.i, %inc.4.i
  %builtin_call.i338.5.i = tail call fastcc i32 @qc_random_range()
  %icmplt.i340.5.i = icmp sgt i32 %builtin_call.i338.5.i, 24
  %inc.5.i = zext i1 %icmplt.i340.5.i to i32
  %spec.select.5.i = add nuw nsw i32 %spec.select.4.i, %inc.5.i
  %builtin_call.i338.6.i = tail call fastcc i32 @qc_random_range()
  %icmplt.i340.6.i = icmp sgt i32 %builtin_call.i338.6.i, 24
  %inc.6.i = zext i1 %icmplt.i340.6.i to i32
  %spec.select.6.i = add nuw nsw i32 %spec.select.5.i, %inc.6.i
  %builtin_call.i338.7.i = tail call fastcc i32 @qc_random_range()
  %icmplt.i340.7.i = icmp sgt i32 %builtin_call.i338.7.i, 24
  %inc.7.i = zext i1 %icmplt.i340.7.i to i32
  %spec.select.7.i = add nuw nsw i32 %spec.select.6.i, %inc.7.i
  %builtin_call.i338.8.i = tail call fastcc i32 @qc_random_range()
  %icmplt.i340.8.i = icmp sgt i32 %builtin_call.i338.8.i, 24
  %inc.8.i = zext i1 %icmplt.i340.8.i to i32
  %spec.select.8.i = add nuw nsw i32 %spec.select.7.i, %inc.8.i
  %builtin_call.i338.9.i = tail call fastcc i32 @qc_random_range()
  %icmplt.i340.9.i = icmp sgt i32 %builtin_call.i338.9.i, 24
  %inc.9.i = zext i1 %icmplt.i340.9.i to i32
  %spec.select.9.i = add nuw nsw i32 %spec.select.8.i, %inc.9.i
  %fstr_i32262.i = tail call fastcc ptr @qc_to_string_int(i32 %spec.select.9.i)
  %fstr_concat263.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.227, ptr %fstr_i32262.i)
  %fstr_concat264.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat263.i, ptr nonnull @.str.228)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %33 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat264.i)
  tail call fastcc void @qc_print_string(ptr %33)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %builtin_call.i341.i = tail call fastcc i32 @qc_random_range()
  %icmplt.i343.i = icmp sgt i32 %builtin_call.i341.i, 24
  %builtin_call.i344.i = tail call fastcc i32 @qc_random_range()
  %icmplt.i346.i = icmp sgt i32 %builtin_call.i344.i, 49
  %and.i = and i1 %icmplt.i343.i, %icmplt.i346.i
  %fstr_bool267.i = tail call fastcc ptr @qc_to_string_bool(i1 %and.i)
  %fstr_concat268.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.230, ptr %fstr_bool267.i)
  %fstr_concat269.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat268.i, ptr nonnull @.str.231)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %34 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat269.i)
  tail call fastcc void @qc_print_string(ptr %34)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %builtin_call.i347.i = tail call fastcc i32 @qc_random_range()
  %icmplt.i349.i = icmp sgt i32 %builtin_call.i347.i, 24
  %builtin_call.i350.i = tail call fastcc i32 @qc_random_range()
  %icmplt.i352.i = icmp sgt i32 %builtin_call.i350.i, 49
  %or.i = or i1 %icmplt.i349.i, %icmplt.i352.i
  %fstr_bool272.i = tail call fastcc ptr @qc_to_string_bool(i1 %or.i)
  %fstr_concat273.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.233, ptr %fstr_bool272.i)
  %fstr_concat274.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat273.i, ptr nonnull @.str.234)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %35 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat274.i)
  tail call fastcc void @qc_print_string(ptr %35)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  %builtin_call.i353.i = tail call fastcc i32 @qc_random_range()
  %icmplt.i355.i = icmp slt i32 %builtin_call.i353.i, 25
  %fstr_bool276.i = tail call fastcc ptr @qc_to_string_bool(i1 %icmplt.i355.i)
  %fstr_concat277.i = tail call fastcc ptr @qc_string_concat(ptr nonnull @.str.236, ptr %fstr_bool276.i)
  %fstr_concat278.i = tail call fastcc ptr @qc_string_concat(ptr %fstr_concat277.i, ptr nonnull @.str.237)
  tail call fastcc void @qc_print_string(ptr nonnull @11)
  %36 = tail call fastcc ptr @qc_fmt_string(ptr %fstr_concat278.i)
  tail call fastcc void @qc_print_string(ptr %36)
  tail call fastcc void @qc_print_string(ptr nonnull @12)
  tail call fastcc void @qc_flush()
  tail call void asm sideeffect inteldialect "\0A        mov rdi, $0\0A        call system\0A        ", "r,~{rdi}"(ptr nonnull @.str.238) #20
  tail call fastcc void @qc_print_string(ptr nonnull @9)
  call void @llvm.lifetime.end.p0(i64 24, ptr nonnull %test.i)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %temp_elem193.i)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %temp_elem192.i)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %temp_elem191.i)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %temp_elem190.i)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %temp_elem189.i)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %temp_elem154.i)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %temp_elem153.i)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %temp_elem152.i)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %temp_elem151.i)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %temp_elem150.i)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %temp_elem137.i)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %temp_elem136.i)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %temp_elem135.i)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %temp_elem134.i)
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %temp_elem.i)
  ret i32 0
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare double @llvm.sqrt.f64(double) #22

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare double @llvm.fabs.f64(double) #22

attributes #0 = { mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress nounwind willreturn allockind("realloc") allocsize(1) memory(argmem: readwrite, inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { mustprogress nofree nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #5 = { nofree nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { mustprogress nofree nounwind willreturn uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #7 = { mustprogress nocallback nofree nounwind willreturn memory(argmem: read) "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #8 = { mustprogress nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #9 = { mustprogress nofree norecurse nounwind willreturn memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #10 = { mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #11 = { mustprogress nofree nounwind willreturn memory(readwrite, argmem: none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #12 = { mustprogress nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #13 = { nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #14 = { mustprogress nofree nounwind willreturn memory(write, argmem: none, inaccessiblemem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #15 = { mustprogress nounwind willreturn uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #16 = { mustprogress nofree norecurse nosync nounwind willreturn memory(read, inaccessiblemem: none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #17 = { mustprogress nofree norecurse nosync nounwind willreturn memory(read, argmem: readwrite, inaccessiblemem: none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #18 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #19 = { nofree nounwind }
attributes #20 = { nounwind }
attributes #21 = { nofree norecurse nosync nounwind memory(read, inaccessiblemem: none) }
attributes #22 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #23 = { nounwind allocsize(0) }
attributes #24 = { nounwind willreturn memory(read) }
attributes #25 = { nounwind allocsize(1) }

!llvm.ident = !{!0}
!llvm.module.flags = !{!1, !2, !3, !4}

!0 = !{!"Debian clang version 21.1.8 (7+b1)"}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 2}
!5 = !{!6, !6, i64 0}
!6 = !{!"omnipotent char", !7, i64 0}
!7 = !{!"Simple C++ TBAA"}
!8 = !{!9, !9, i64 0}
!9 = !{!"p1 _ZTS8_IO_FILE", !10, i64 0}
!10 = !{!"any pointer", !6, i64 0}
!11 = !{!12, !14, i64 12}
!12 = !{!"_ZTS7qc_list", !13, i64 0, !14, i64 8, !14, i64 12, !14, i64 16}
!13 = !{!"any p2 pointer", !10, i64 0}
!14 = !{!"int", !6, i64 0}
!15 = !{!12, !14, i64 8}
!16 = !{!12, !14, i64 16}
!17 = !{!12, !13, i64 0}
!18 = !{!10, !10, i64 0}
