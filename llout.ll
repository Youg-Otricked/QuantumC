; ModuleID = 'qc_module'
source_filename = "qc_module"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.2 = private unnamed_addr constant [3 x i8] c"%g\00", align 1
@.str.3 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.str.4 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.str.5 = private unnamed_addr constant [5 x i8] c"none\00", align 1
@.str.6 = private unnamed_addr constant [7 x i8] c"qfalse\00", align 1
@.str.7 = private unnamed_addr constant [6 x i8] c"qtrue\00", align 1
@.str.8 = private unnamed_addr constant [5 x i8] c"both\00", align 1
@stdout = external local_unnamed_addr global ptr, align 8
@switch.table.qc_to_string_qbool = private unnamed_addr constant [4 x ptr] [ptr @.str.5, ptr @.str.6, ptr @.str.7, ptr @.str.8], align 8
@.str.9 = private constant [6 x i8] c"Alice\00"
@.str.10 = private constant [8 x i8] c"answer=\00"
@.str.11 = private constant [5 x i8] c", b=\00"
@.str.12 = private constant [5 x i8] c"Luca\00"
@.str.13 = private constant [17 x i8] c"Hello, Compiler!\00"
@.str.14 = private constant [5 x i8] c"\F0\9F\94\A5\00"
@.str.15 = private constant [6 x i8] c"Hello\00"
@.str.16 = private constant [6 x i8] c"World\00"
@.str.17 = private constant [2 x i8] c"!\00"
@.str.18 = private constant [1 x i8] zeroinitializer
@.str.19 = private constant [14 x i8] c"She said \22Hi\22\00"
@.str.20 = private constant [81 x i8] c"C:\\Users\\Luca(JK its ~/C^4 becuase i dont use the disgusting windows powershell)\00"

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local i32 @qc_powi_i32(i32 noundef %0, i32 noundef %1) local_unnamed_addr #0 {
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

; Function Attrs: mustprogress nofree nounwind willreturn uwtable
define dso_local noalias noundef ptr @qc_string_concat(ptr noundef readonly %0, ptr noundef readonly %1) local_unnamed_addr #1 {
  %3 = icmp eq ptr %0, null
  %4 = select i1 %3, ptr @.str, ptr %0
  %5 = icmp eq ptr %1, null
  %6 = select i1 %5, ptr @.str, ptr %1
  %7 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %4) #12
  %8 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %6) #12
  %9 = add i64 %8, %7
  %10 = add i64 %9, 1
  %11 = tail call noalias ptr @malloc(i64 noundef %10) #13
  %12 = icmp eq ptr %11, null
  br i1 %12, label %16, label %13

13:                                               ; preds = %2
  tail call void @llvm.memcpy.p0.p0.i64(ptr nonnull align 1 %11, ptr nonnull align 1 %4, i64 %7, i1 false)
  %14 = getelementptr inbounds i8, ptr %11, i64 %7
  tail call void @llvm.memcpy.p0.p0.i64(ptr nonnull align 1 %14, ptr nonnull align 1 %6, i64 %8, i1 false)
  %15 = getelementptr inbounds i8, ptr %11, i64 %9
  store i8 0, ptr %15, align 1, !tbaa !7
  br label %16

16:                                               ; preds = %13, %2
  ret ptr %11
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(argmem: read)
declare i64 @strlen(ptr nocapture noundef) local_unnamed_addr #2

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite)
declare noalias noundef ptr @malloc(i64 noundef) local_unnamed_addr #3

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #4

; Function Attrs: mustprogress nofree nounwind willreturn memory(argmem: read) uwtable
define dso_local i32 @qc_string_eq(ptr noundef readonly %0, ptr noundef readonly %1) local_unnamed_addr #5 {
  %3 = icmp ne ptr %0, null
  %4 = icmp ne ptr %1, null
  %5 = and i1 %3, %4
  br i1 %5, label %6, label %10

6:                                                ; preds = %2
  %7 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(1) %1) #12
  %8 = icmp eq i32 %7, 0
  %9 = zext i1 %8 to i32
  br label %10

10:                                               ; preds = %6, %2
  %11 = phi i32 [ %9, %6 ], [ 0, %2 ]
  ret i32 %11
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(argmem: read)
declare i32 @strcmp(ptr nocapture noundef, ptr nocapture noundef) local_unnamed_addr #2

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i8 @qc_qand(i8 noundef zeroext %0, i8 noundef zeroext %1) local_unnamed_addr #0 {
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
define dso_local noundef zeroext i8 @qc_qor(i8 noundef zeroext %0, i8 noundef zeroext %1) local_unnamed_addr #0 {
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
define dso_local noundef zeroext i8 @qc_qxor(i8 noundef zeroext %0, i8 noundef zeroext %1) local_unnamed_addr #0 {
  %3 = or i8 %1, %0
  %4 = icmp ult i8 %3, 2
  br i1 %4, label %18, label %5

5:                                                ; preds = %2
  %6 = icmp ult i8 %1, 2
  %7 = icmp ult i8 %0, 2
  %8 = icmp ugt i8 %1, 1
  %9 = and i1 %7, %8
  %10 = icmp ugt i8 %0, 1
  %11 = and i1 %10, %6
  %12 = or i1 %9, %11
  br i1 %12, label %18, label %13

13:                                               ; preds = %5
  %14 = icmp eq i8 %0, 2
  %15 = icmp eq i8 %1, 2
  %16 = and i1 %14, %15
  %17 = select i1 %16, i8 1, i8 3
  br label %18

18:                                               ; preds = %13, %5, %2
  %19 = phi i8 [ 0, %2 ], [ 3, %5 ], [ %17, %13 ]
  ret i8 %19
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i8 @qc_qnot(i8 noundef zeroext %0) local_unnamed_addr #0 {
  %2 = sub i8 3, %0
  ret i8 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @qc_qand_collapse(i8 noundef zeroext %0, i8 noundef zeroext %1) local_unnamed_addr #0 {
  %3 = and i8 %0, 2
  %4 = and i8 %3, %1
  %5 = icmp ne i8 %4, 0
  ret i1 %5
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef zeroext i1 @qc_qor_collapse(i8 noundef zeroext %0, i8 noundef zeroext %1) local_unnamed_addr #0 {
  %3 = or i8 %1, %0
  %4 = and i8 %3, 2
  %5 = icmp ne i8 %4, 0
  ret i1 %5
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_to_string_int(i32 noundef %0) local_unnamed_addr #6 {
  %2 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %2) #14
  %3 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 32, ptr noundef nonnull @.str.1, i32 noundef %0) #14
  %4 = icmp slt i32 %3, 0
  br i1 %4, label %11, label %5

5:                                                ; preds = %1
  %6 = add nuw nsw i32 %3, 1
  %7 = zext nneg i32 %6 to i64
  %8 = tail call noalias ptr @malloc(i64 noundef %7) #13
  %9 = icmp eq ptr %8, null
  br i1 %9, label %11, label %10

10:                                               ; preds = %5
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %8, ptr noundef nonnull align 16 dereferenceable(1) %2, i64 %7, i1 false)
  br label %11

11:                                               ; preds = %10, %5, %1
  %12 = phi ptr [ null, %1 ], [ %8, %10 ], [ null, %5 ]
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %2) #14
  ret ptr %12
}

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #7

; Function Attrs: nofree nounwind
declare noundef i32 @snprintf(ptr noalias nocapture noundef writeonly, i64 noundef, ptr nocapture noundef readonly, ...) local_unnamed_addr #8

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #7

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_to_string_float(float noundef %0) local_unnamed_addr #6 {
  %2 = alloca [64 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 64, ptr nonnull %2) #14
  %3 = fpext float %0 to double
  %4 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 64, ptr noundef nonnull @.str.2, double noundef %3) #14
  %5 = icmp slt i32 %4, 0
  br i1 %5, label %12, label %6

6:                                                ; preds = %1
  %7 = add nuw nsw i32 %4, 1
  %8 = zext nneg i32 %7 to i64
  %9 = tail call noalias ptr @malloc(i64 noundef %8) #13
  %10 = icmp eq ptr %9, null
  br i1 %10, label %12, label %11

11:                                               ; preds = %6
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %9, ptr noundef nonnull align 16 dereferenceable(1) %2, i64 %8, i1 false)
  br label %12

12:                                               ; preds = %11, %6, %1
  %13 = phi ptr [ null, %1 ], [ %9, %11 ], [ null, %6 ]
  call void @llvm.lifetime.end.p0(i64 64, ptr nonnull %2) #14
  ret ptr %13
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local noalias noundef ptr @qc_to_string_double(double noundef %0) local_unnamed_addr #6 {
  %2 = alloca [64 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 64, ptr nonnull %2) #14
  %3 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 64, ptr noundef nonnull @.str.2, double noundef %0) #14
  %4 = icmp slt i32 %3, 0
  br i1 %4, label %11, label %5

5:                                                ; preds = %1
  %6 = add nuw nsw i32 %3, 1
  %7 = zext nneg i32 %6 to i64
  %8 = tail call noalias ptr @malloc(i64 noundef %7) #13
  %9 = icmp eq ptr %8, null
  br i1 %9, label %11, label %10

10:                                               ; preds = %5
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %8, ptr noundef nonnull align 16 dereferenceable(1) %2, i64 %7, i1 false)
  br label %11

11:                                               ; preds = %10, %5, %1
  %12 = phi ptr [ null, %1 ], [ %8, %10 ], [ null, %5 ]
  call void @llvm.lifetime.end.p0(i64 64, ptr nonnull %2) #14
  ret ptr %12
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(readwrite, argmem: none) uwtable
define dso_local noalias noundef ptr @qc_to_string_bool(i1 noundef zeroext %0) local_unnamed_addr #9 {
  %2 = select i1 %0, i64 5, i64 6
  %3 = tail call noalias ptr @malloc(i64 noundef %2) #13
  %4 = icmp eq ptr %3, null
  br i1 %4, label %7, label %5

5:                                                ; preds = %1
  %6 = select i1 %0, ptr @.str.3, ptr @.str.4
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(5) %3, ptr noundef nonnull align 1 dereferenceable(5) %6, i64 %2, i1 false)
  br label %7

7:                                                ; preds = %5, %1
  ret ptr %3
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(readwrite, argmem: none) uwtable
define dso_local noalias noundef ptr @qc_to_string_qbool(i8 noundef zeroext %0) local_unnamed_addr #9 {
  %2 = and i8 %0, 3
  %3 = zext nneg i8 %2 to i64
  %4 = getelementptr inbounds [4 x ptr], ptr @switch.table.qc_to_string_qbool, i64 0, i64 %3
  %5 = load ptr, ptr %4, align 8
  %6 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %5) #12
  %7 = add i64 %6, 1
  %8 = tail call noalias ptr @malloc(i64 noundef %7) #13
  %9 = icmp eq ptr %8, null
  br i1 %9, label %11, label %10

10:                                               ; preds = %1
  tail call void @llvm.memcpy.p0.p0.i64(ptr nonnull align 1 %8, ptr nonnull align 1 %5, i64 %7, i1 false)
  br label %11

11:                                               ; preds = %10, %1
  ret ptr %8
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(write, argmem: none, inaccessiblemem: readwrite) uwtable
define dso_local noalias noundef ptr @qc_to_string_char(i8 noundef signext %0) local_unnamed_addr #10 {
  %2 = tail call noalias dereferenceable_or_null(2) ptr @malloc(i64 noundef 2) #13
  %3 = icmp eq ptr %2, null
  br i1 %3, label %6, label %4

4:                                                ; preds = %1
  store i8 %0, ptr %2, align 1, !tbaa !7
  %5 = getelementptr inbounds i8, ptr %2, i64 1
  store i8 0, ptr %5, align 1, !tbaa !7
  br label %6

6:                                                ; preds = %4, %1
  ret ptr %2
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_string(ptr noundef readonly %0) local_unnamed_addr #6 {
  %2 = icmp eq ptr %0, null
  %3 = select i1 %2, ptr @.str, ptr %0
  %4 = load ptr, ptr @stdout, align 8, !tbaa !10
  %5 = tail call i32 @fputs(ptr noundef nonnull %3, ptr noundef %4)
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @fputs(ptr nocapture noundef readonly, ptr nocapture noundef) local_unnamed_addr #8

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_int(i32 noundef %0) local_unnamed_addr #6 {
  %2 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.1, i32 noundef %0)
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @printf(ptr nocapture noundef readonly, ...) local_unnamed_addr #8

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_double(double noundef %0) local_unnamed_addr #6 {
  %2 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.2, double noundef %0)
  ret void
}

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local void @qc_print_char(i8 noundef signext %0) local_unnamed_addr #6 {
  %2 = zext i8 %0 to i32
  %3 = load ptr, ptr @stdout, align 8, !tbaa !10
  %4 = tail call i32 @putc(i32 noundef %2, ptr noundef %3)
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @putc(i32 noundef, ptr nocapture noundef) local_unnamed_addr #8

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
  ret { i32, ptr } { i32 123, ptr @.str.9 }
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

define double @square(double %x) {
entry:
  %x1 = alloca double, align 8
  store double %x, ptr %x1, align 8
  %x2 = load double, ptr %x1, align 8
  %x3 = load double, ptr %x1, align 8
  %fmul = fmul double %x2, %x3
  ret double %fmul
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

define i32 @main() {
entry:
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
  %testerf = alloca i32, align 4
  store i32 5, ptr %testerf, align 4
  store float 3.500000e+00, ptr %testerfloat, align 4
  %testerf1 = load i32, ptr %testerf, align 4
  %fstr_i32 = call ptr @qc_to_string_int(i32 %testerf1)
  %fstr_concat = call ptr @qc_string_concat(ptr @.str.10, ptr %fstr_i32)
  %fstr_concat2 = call ptr @qc_string_concat(ptr %fstr_concat, ptr @.str.11)
  %testerfloat3 = load float, ptr %testerfloat, align 4
  %fstr_f32 = call ptr @qc_to_string_float(float %testerfloat3)
  %fstr_concat4 = call ptr @qc_string_concat(ptr %fstr_concat2, ptr %fstr_f32)
  store ptr %fstr_concat4, ptr %fstringt, align 8
  %fstringt5 = load ptr, ptr %fstringt, align 8
  call void @qc_print_string(ptr %fstringt5)
  call void @qc_print_char(i8 10)
  %calltmp = call i32 @add(i32 2, i32 3)
  store i32 %calltmp, ptr %xdddddddd, align 4
  store ptr @__lambda_0, ptr %adder, align 8
  %adder6 = load ptr, ptr %adder, align 8
  %calltmp7 = call i32 %adder6(i32 10, i32 20)
  store i32 %calltmp7, ptr %ydddddddd, align 4
  %calltmp8 = call { i32, ptr } @get_user()
  %0 = extractvalue { i32, ptr } %calltmp8, 0
  store i32 %0, ptr %idddddd, align 4
  %1 = extractvalue { i32, ptr } %calltmp8, 1
  store ptr %1, ptr %asdfname, align 8
  %ydddddddd9 = load i32, ptr %ydddddddd, align 4
  call void @qc_print_int(i32 %ydddddddd9)
  call void @qc_print_char(i8 10)
  %calltmp10 = call i32 @mul_add(i32 2, i32 3, i32 4)
  store i32 %calltmp10, ptr %v1, align 4
  %calltmp11 = call double @square(double 1.500000e+00)
  store double %calltmp11, ptr %v2, align 8
  %v112 = load i32, ptr %v1, align 4
  %calltmp13 = call i32 @mul_add(i32 %v112, i32 3, i32 1)
  store i32 %calltmp13, ptr %v3, align 4
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
  store ptr @.str.12, ptr %name, align 8
  store ptr @.str.13, ptr %greeting, align 8
  store ptr @.str.14, ptr %emoji, align 8
  store i32 10, ptr %x, align 4
  store i32 3, ptr %y, align 4
  %x14 = load i32, ptr %x, align 4
  %y15 = load i32, ptr %y, align 4
  %add = add i32 %x14, %y15
  store i32 %add, ptr %sum, align 4
  %x16 = load i32, ptr %x, align 4
  %y17 = load i32, ptr %y, align 4
  %sub = sub i32 %x16, %y17
  store i32 %sub, ptr %diff, align 4
  %x18 = load i32, ptr %x, align 4
  %y19 = load i32, ptr %y, align 4
  %mul = mul i32 %x18, %y19
  store i32 %mul, ptr %prod, align 4
  %x20 = load i32, ptr %x, align 4
  %y21 = load i32, ptr %y, align 4
  %sdiv = sdiv i32 %x20, %y21
  store i32 %sdiv, ptr %quot, align 4
  %x22 = load i32, ptr %x, align 4
  %y23 = load i32, ptr %y, align 4
  %srem = srem i32 %x22, %y23
  store i32 %srem, ptr %rem, align 4
  %powi = call i32 @qc_powi_i32(i32 2, i32 8)
  store i32 %powi, ptr %power, align 4
  %x24 = load i32, ptr %x, align 4
  %add25 = add i32 %x24, 5
  store i32 %add25, ptr %x, align 4
  %x26 = load i32, ptr %x, align 4
  %sub27 = sub i32 %x26, 3
  store i32 %sub27, ptr %x, align 4
  %x28 = load i32, ptr %x, align 4
  %mul29 = mul i32 %x28, 2
  store i32 %mul29, ptr %x, align 4
  %x30 = load i32, ptr %x, align 4
  %sdiv31 = sdiv i32 %x30, 4
  store i32 %sdiv31, ptr %x, align 4
  %x32 = load i32, ptr %x, align 4
  %srem33 = srem i32 %x32, 5
  store i32 %srem33, ptr %x, align 4
  store float 1.050000e+01, ptr %a, align 4
  store float 2.500000e+00, ptr %b, align 4
  %a34 = load float, ptr %a, align 4
  %b35 = load float, ptr %b, align 4
  %fadd = fadd float %a34, %b35
  store float %fadd, ptr %fsum, align 4
  %a36 = load float, ptr %a, align 4
  %b37 = load float, ptr %b, align 4
  %fsub = fsub float %a36, %b37
  store float %fsub, ptr %fdiff, align 4
  %a38 = load float, ptr %a, align 4
  %b39 = load float, ptr %b, align 4
  %fmul = fmul float %a38, %b39
  store float %fmul, ptr %fprod, align 4
  %a40 = load float, ptr %a, align 4
  %b41 = load float, ptr %b, align 4
  %fdiv = fdiv float %a40, %b41
  store float %fdiv, ptr %fquot, align 4
  %a42 = load float, ptr %a, align 4
  %fadd43 = fadd float %a42, 1.500000e+00
  store float %fadd43, ptr %a, align 4
  %a44 = load float, ptr %a, align 4
  %fsub45 = fsub float %a44, 2.000000e+00
  store float %fsub45, ptr %a, align 4
  %a46 = load float, ptr %a, align 4
  %fmul47 = fmul float %a46, 3.000000e+00
  store float %fmul47, ptr %a, align 4
  %a48 = load float, ptr %a, align 4
  %fdiv49 = fdiv float %a48, 5.000000e+00
  store float %fdiv49, ptr %a, align 4
  store i32 10, ptr %i, align 4
  store float 0x40091EB860000000, ptr %f, align 4
  store double 2.718000e+00, ptr %d, align 8
  %f50 = load float, ptr %f, align 4
  %d51 = load double, ptr %d, align 8
  %promote_to_double = fpext float %f50 to double
  %fadd52 = fadd double %promote_to_double, %d51
  store double %fadd52, ptr %result1, align 8
  %i53 = load i32, ptr %i, align 4
  %i54 = load i32, ptr %i, align 4
  %add55 = add i32 %i53, %i54
  store i32 %add55, ptr %result2, align 4
  %i56 = load i32, ptr %i, align 4
  %mul57 = mul i32 %i56, 2
  store i32 %mul57, ptr %result3, align 4
  %i58 = load i32, ptr %i, align 4
  %add59 = add i32 %i58, 5
  store i32 %add59, ptr %i, align 4
  %f60 = load float, ptr %f, align 4
  %fadd61 = fadd float %f60, 1.500000e+00
  store float %fadd61, ptr %f, align 4
  %d62 = load double, ptr %d, align 8
  %fadd63 = fadd double %d62, 1.000000e-03
  store double %fadd63, ptr %d, align 8
  store i8 65, ptr %start, align 1
  store i8 90, ptr %end, align 1
  store i8 32, ptr %space, align 1
  store i8 10, ptr %newline, align 1
  store i8 9, ptr %tab, align 1
  %start64 = load i8, ptr %start, align 1
  store i8 66, ptr %start, align 1
  %end65 = load i8, ptr %end, align 1
  store i8 89, ptr %end, align 1
  store i1 true, ptr %yes, align 1
  store i1 false, ptr %no, align 1
  %yes66 = load i1, ptr %yes, align 1
  store i1 false, ptr %yes, align 1
  %no67 = load i1, ptr %no, align 1
  store i1 true, ptr %no, align 1
  %yes68 = load i1, ptr %yes, align 1
  store i1 true, ptr %yes, align 1
  store i2 -1, ptr %schrodinger, align 1
  store i2 -2, ptr %alive, align 1
  store i2 1, ptr %dead, align 1
  store i2 0, ptr %nul, align 1
  %schrodinger69 = load i2, ptr %schrodinger, align 1
  store i2 -2, ptr %schrodinger, align 1
  %alive70 = load i2, ptr %alive, align 1
  store i2 -1, ptr %alive, align 1
  %dead71 = load i2, ptr %dead, align 1
  store i2 0, ptr %dead, align 1
  %nul72 = load i2, ptr %nul, align 1
  store i2 1, ptr %nul, align 1
  store ptr @.str.15, ptr %hello, align 8
  store ptr @.str.16, ptr %world, align 8
  store ptr @.str.17, ptr %exclaim, align 8
  store ptr @.str.18, ptr %non, align 8
  store ptr @.str.19, ptr %quote, align 8
  store ptr @.str.20, ptr %path, align 8
  store i32 2, ptr %base, align 4
  store i32 10, ptr %exp, align 4
  store float 2.000000e+00, ptr %fbase, align 4
  store float 3.000000e+00, ptr %fexp, align 4
  %fbase73 = load float, ptr %fbase, align 4
  %fexp74 = load float, ptr %fexp, align 4
  %pow = call float @llvm.pow.f32(float %fbase73, float %fexp74)
  store float %pow, ptr %fresult, align 4
  store double 1.500000e+00, ptr %dbase, align 8
  store double 2.000000e+00, ptr %dexp, align 8
  %dbase75 = load double, ptr %dbase, align 8
  %dexp76 = load double, ptr %dexp, align 8
  %pow77 = call double @llvm.pow.f64(double %dbase75, double %dexp76)
  store double %pow77, ptr %dresult, align 8
  store i32 5, ptr %xdd, align 4
  store i32 10, ptr %ydd, align 4
  %xdd78 = load i32, ptr %xdd, align 4
  %ydd79 = load i32, ptr %ydd, align 4
  %icmpeq = icmp eq i32 %xdd78, %ydd79
  store i1 %icmpeq, ptr %eq, align 1
  %xdd80 = load i32, ptr %xdd, align 4
  %ydd81 = load i32, ptr %ydd, align 4
  %icmpne = icmp ne i32 %xdd80, %ydd81
  store i1 %icmpne, ptr %ne, align 1
  %xdd82 = load i32, ptr %xdd, align 4
  %ydd83 = load i32, ptr %ydd, align 4
  %icmplt = icmp slt i32 %xdd82, %ydd83
  store i1 %icmplt, ptr %lt, align 1
  %xdd84 = load i32, ptr %xdd, align 4
  %ydd85 = load i32, ptr %ydd, align 4
  %icmpgt = icmp sgt i32 %xdd84, %ydd85
  store i1 %icmpgt, ptr %gt, align 1
  %xdd86 = load i32, ptr %xdd, align 4
  %ydd87 = load i32, ptr %ydd, align 4
  %icmple = icmp sle i32 %xdd86, %ydd87
  store i1 %icmple, ptr %lte, align 1
  %xdd88 = load i32, ptr %xdd, align 4
  %ydd89 = load i32, ptr %ydd, align 4
  %icmpge = icmp sge i32 %xdd88, %ydd89
  store i1 %icmpge, ptr %gte, align 1
  store i32 0, ptr %result, align 4
  %xdd90 = load i32, ptr %xdd, align 4
  %icmpgt91 = icmp sgt i32 %xdd90, 3
  br i1 %icmpgt91, label %then, label %else

then:                                             ; preds = %entry
  %result92 = load i32, ptr %result, align 4
  store i32 10, ptr %result, align 4
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %i94 = load i32, ptr %i, align 4
  store i32 0, ptr %i, align 4
  %sum95 = load i32, ptr %sum, align 4
  store i32 0, ptr %sum, align 4
  br label %while.cond

else:                                             ; preds = %entry
  %result93 = load i32, ptr %result, align 4
  store i32 20, ptr %result, align 4
  br label %ifcont

while.cond:                                       ; preds = %while.body, %ifcont
  %i96 = load i32, ptr %i, align 4
  %icmplt97 = icmp slt i32 %i96, 5
  br i1 %icmplt97, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %sum98 = load i32, ptr %sum, align 4
  %i99 = load i32, ptr %i, align 4
  %add100 = add i32 %sum98, %i99
  store i32 %add100, ptr %sum, align 4
  %i101 = load i32, ptr %i, align 4
  %add102 = add i32 %i101, 1
  store i32 %add102, ptr %i, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %sum103 = load i32, ptr %sum, align 4
  store i32 0, ptr %sum, align 4
  store i32 0, ptr %xyz, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %while.end
  %xyz104 = load i32, ptr %xyz, align 4
  %icmplt105 = icmp slt i32 %xyz104, 5
  br i1 %icmplt105, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %sum106 = load i32, ptr %sum, align 4
  %xyz107 = load i32, ptr %xyz, align 4
  %add108 = add i32 %sum106, %xyz107
  store i32 %add108, ptr %sum, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %xyz109 = load i32, ptr %xyz, align 4
  %add110 = add i32 %xyz109, 1
  store i32 %add110, ptr %xyz, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  store i1 true, ptr %ata, align 1
  store i1 false, ptr %btb, align 1
  %ata111 = load i1, ptr %ata, align 1
  %btb112 = load i1, ptr %btb, align 1
  %and = and i1 %ata111, %btb112
  store i1 %and, ptr %and_test, align 1
  %ata113 = load i1, ptr %ata, align 1
  %btb114 = load i1, ptr %btb, align 1
  %or = or i1 %ata113, %btb114
  store i1 %or, ptr %or_test, align 1
  %ata115 = load i1, ptr %ata, align 1
  %btb116 = load i1, ptr %btb, align 1
  %xor = xor i1 %ata115, %btb116
  store i1 %xor, ptr %xor_test, align 1
  %ata117 = load i1, ptr %ata, align 1
  %not = xor i1 %ata117, true
  store i1 %not, ptr %not_test, align 1
  %sum118 = load i32, ptr %sum, align 4
  switch i32 %sum118, label %switch.case120 [
    i32 1, label %switch.case
    i32 5, label %switch.case119
  ]

switch.end:                                       ; preds = %switch.case120, %switch.case119, %switch.case
  store i2 -1, ptr %both_tester, align 1
  %both_tester123 = load i2, ptr %both_tester, align 1
  %2 = and i2 %both_tester123, -2
  %3 = icmp ne i2 %2, 0
  br i1 %3, label %qif.body, label %qelif.check

switch.case:                                      ; preds = %for.end
  br label %switch.end

switch.case119:                                   ; preds = %for.end
  %sum121 = load i32, ptr %sum, align 4
  store i32 2, ptr %sum, align 4
  br label %switch.end

switch.case120:                                   ; preds = %for.end
  %sum122 = load i32, ptr %sum, align 4
  store i32 0, ptr %sum, align 4
  br label %switch.end

qif.end:                                          ; preds = %qelse.body, %qelif.check, %qif.body
  %x128 = load i32, ptr %x, align 4
  store i32 0, ptr %x, align 4
  %both_tester129 = load i2, ptr %both_tester, align 1
  br label %qsw.check_true

qif.body:                                         ; preds = %switch.end
  %sum124 = load i32, ptr %sum, align 4
  %add125 = add i32 %sum124, 123
  store i32 %add125, ptr %sum, align 4
  br label %qif.end

qelif.check:                                      ; preds = %switch.end
  %4 = and i2 %both_tester123, 1
  %5 = icmp ne i2 %4, 0
  br i1 %5, label %qelse.body, label %qif.end

qelse.body:                                       ; preds = %qelif.check
  %sum126 = load i32, ptr %sum, align 4
  %add127 = add i32 %sum126, 321
  store i32 %add127, ptr %sum, align 4
  br label %qif.end

qsw.check_true:                                   ; preds = %qif.end
  %has_true = and i2 %both_tester129, -2
  %is_true = icmp ne i2 %has_true, 0
  br i1 %is_true, label %qsw.check_false, label %qsw.check_false

qsw.check_false:                                  ; preds = %qsw.check_true, %qsw.check_true
  %has_false = and i2 %both_tester129, 1
  %is_false = icmp ne i2 %has_false, 0
  %is_both = and i1 %is_true, %is_false
  %not_false = xor i1 %is_false, true
  %is_qtrue_only = and i1 %is_true, %not_false
  %not_true = xor i1 %is_true, true
  %is_qfalse_only = and i1 %not_true, %is_false
  %is_none = and i1 %not_true, %not_false
  br i1 %is_both, label %qsw.case_b, label %qsw.check_qtrue

qswitch.end:                                      ; preds = %qsw.case_b, %qsw.case_t, %qsw.check_none_final, %qsw.check_none_final, %qsw.check_qfalse
  %x132 = load i32, ptr %x, align 4
  %sum133 = load i32, ptr %sum, align 4
  %add134 = add i32 %x132, %sum133
  %xdddddddd135 = load i32, ptr %xdddddddd, align 4
  %add136 = add i32 %add134, %xdddddddd135
  %calltmp137 = call i32 @twice(i32 22)
  %add138 = add i32 %add136, %calltmp137
  ret i32 %add138

qsw.case_t:                                       ; preds = %qsw.check_qtrue
  %x130 = load i32, ptr %x, align 4
  store i32 2, ptr %x, align 4
  br label %qswitch.end

qsw.case_b:                                       ; preds = %qsw.check_false
  %x131 = load i32, ptr %x, align 4
  store i32 1, ptr %x, align 4
  br label %qswitch.end

qsw.check_qtrue:                                  ; preds = %qsw.check_false
  br i1 %is_qtrue_only, label %qsw.case_t, label %qsw.check_qfalse

qsw.check_qfalse:                                 ; preds = %qsw.check_qtrue
  br i1 %is_qfalse_only, label %qswitch.end, label %qsw.check_none_final

qsw.check_none_final:                             ; preds = %qsw.check_qfalse
  br i1 %is_none, label %qswitch.end, label %qswitch.end
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
declare float @llvm.pow.f32(float, float) #11

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare double @llvm.pow.f64(double, double) #11

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nofree nounwind willreturn uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress nofree nounwind willreturn memory(argmem: read) "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #5 = { mustprogress nofree nounwind willreturn memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { mustprogress nofree nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #7 = { nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #8 = { nofree nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #9 = { mustprogress nofree nounwind willreturn memory(readwrite, argmem: none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #10 = { mustprogress nofree nounwind willreturn memory(write, argmem: none, inaccessiblemem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #11 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #12 = { nounwind willreturn memory(read) }
attributes #13 = { nounwind allocsize(0) }
attributes #14 = { nounwind }

!llvm.ident = !{!0}
!llvm.module.flags = !{!1, !2, !3, !4}

!0 = !{!"Ubuntu clang version 18.1.3 (1ubuntu1)"}
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
!11 = !{!"any pointer", !8, i64 0}
