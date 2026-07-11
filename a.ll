; ModuleID = 'master_module'
source_filename = "master_module"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"ArrayIterator<int>" = type { ptr, ptr, i32, i32 }
%"Array<int,2>" = type { ptr, ptr, i32 }

@.str = private unnamed_addr constant [11 x i8] c"%%%s%d.%dd\00", align 1
@.str.1 = private unnamed_addr constant [2 x i8] c"0\00", align 1
@.str.2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.3 = private unnamed_addr constant [7 x i8] c"%%.%dd\00", align 1
@.str.4 = private unnamed_addr constant [8 x i8] c"%%%s%dd\00", align 1
@.str.5 = private unnamed_addr constant [4 x i8] c"%%d\00", align 1
@.str.6 = private unnamed_addr constant [8 x i8] c"%%010lu\00", align 1
@.str.7 = private unnamed_addr constant [5 x i8] c"%%lu\00", align 1
@.str.8 = private unnamed_addr constant [11 x i8] c"%%%s%d.%df\00", align 1
@.str.9 = private unnamed_addr constant [7 x i8] c"%%.%df\00", align 1
@.str.10 = private unnamed_addr constant [8 x i8] c"%%%s%df\00", align 1
@.str.11 = private unnamed_addr constant [4 x i8] c"%%f\00", align 1
@.str.12 = private unnamed_addr constant [11 x i8] c"%%%s%d.%de\00", align 1
@.str.13 = private unnamed_addr constant [7 x i8] c"%%.%de\00", align 1
@.str.14 = private unnamed_addr constant [8 x i8] c"%%%s%de\00", align 1
@.str.15 = private unnamed_addr constant [4 x i8] c"%%e\00", align 1
@.str.16 = private unnamed_addr constant [8 x i8] c"%%%s%dc\00", align 1
@.str.17 = private unnamed_addr constant [4 x i8] c"%%c\00", align 1
@.str.18 = private unnamed_addr constant [8 x i8] c"%%%s%ds\00", align 1
@.str.19 = private unnamed_addr constant [4 x i8] c"%%s\00", align 1
@.str.20 = private unnamed_addr constant [8 x i8] c"%%%s%dx\00", align 1
@.str.21 = private unnamed_addr constant [4 x i8] c"%%x\00", align 1
@.str.22 = private unnamed_addr constant [8 x i8] c"%%%s%do\00", align 1
@.str.23 = private unnamed_addr constant [4 x i8] c"%%o\00", align 1
@.str.24 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.str.25 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.str.26 = private unnamed_addr constant [5 x i8] c"none\00", align 1
@.str.27 = private unnamed_addr constant [7 x i8] c"qfalse\00", align 1
@.str.28 = private unnamed_addr constant [6 x i8] c"qtrue\00", align 1
@.str.29 = private unnamed_addr constant [5 x i8] c"both\00", align 1
@.str.30 = private unnamed_addr constant [8 x i8] c"0x%0*jx\00", align 1
@.str.31 = private unnamed_addr constant [4 x i8] c"%*p\00", align 1
@.str.32 = private unnamed_addr constant [3 x i8] c"%p\00", align 1
@.str.33 = private unnamed_addr constant [4 x i8] c"%p\0A\00", align 1
@.str.34 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.35 = private unnamed_addr constant [3 x i8] c"%g\00", align 1
@.str.36 = private unnamed_addr constant [4 x i8] c"%ld\00", align 1
@.str.37 = private unnamed_addr constant [4 x i8] c"%hd\00", align 1
@stdout = external local_unnamed_addr global ptr, align 8
@stderr = external local_unnamed_addr global ptr, align 8
@stdin = external local_unnamed_addr global ptr, align 8
@.str.39 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.43 = private unnamed_addr constant [3 x i8] c", \00", align 1
@.str.45 = private unnamed_addr constant [5 x i8] c"\22%s\22\00", align 1
@.str.46 = private unnamed_addr constant [5 x i8] c"'%c'\00", align 1
@.str.47 = private unnamed_addr constant [6 x i8] c"ERROR\00", align 1
@.str.49 = private unnamed_addr constant [3 x i8] c": \00", align 1
@switch.table.qc_print_array_qbool = private unnamed_addr constant [4 x ptr] [ptr @.str.26, ptr @.str.27, ptr @.str.28, ptr @.str.29], align 8
@switch.table.qc_set_leaf_element.52 = private unnamed_addr constant [5 x i64] [i64 8, i64 1, i64 1, i64 1, i64 8], align 8
@switch.table.qc_stringify_jagged_helper = private unnamed_addr constant [5 x i32] [i32 8, i32 1, i32 1, i32 1, i32 8], align 4
@switch.table.qc_map_set.54 = private unnamed_addr constant [4 x i64] [i64 8, i64 1, i64 1, i64 1], align 8
@"ArrayIterator<int>_vtable" = internal constant [6 x ptr] [ptr @"ArrayIterator<int>_ArrayIterator", ptr @"ArrayIterator<int>__atEnd", ptr @"ArrayIterator<int>__next", ptr @"ArrayIterator<int>__atStart", ptr @"ArrayIterator<int>__prev", ptr @"ArrayIterator<int>__moveTo"]
@"Array<int,2>_vtable" = internal constant [5 x ptr] [ptr @"Array<int,2>_Array", ptr @"Array<int,2>_operator[]=", ptr @"Array<int,2>_operator[]", ptr @"Array<int,2>__begin", ptr @"Array<int,2>__end"]
@.str.38 = private constant [2 x i8] c"T\00"
@.str.40 = private constant [3 x i8] c"%i\00"
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [2 x i8] zeroinitializer, align 1

; Function Attrs: mustprogress nofree nounwind willreturn memory(inaccessiblemem: readwrite) uwtable
define internal noalias noundef ptr @qc_malloc(i64 noundef %0) local_unnamed_addr #0 {
  %2 = tail call noalias ptr @malloc(i64 noundef %0) #34
  ret ptr %2
}

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite)
declare noalias noundef ptr @malloc(i64 noundef) local_unnamed_addr #1

; Function Attrs: mustprogress nounwind willreturn memory(argmem: readwrite, inaccessiblemem: readwrite) uwtable
define internal void @qc_free(ptr noundef captures(none) %0) local_unnamed_addr #2 {
  tail call void @free(ptr noundef %0) #35
  ret void
}

; Function Attrs: mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite)
declare void @free(ptr allocptr noundef captures(none)) local_unnamed_addr #3

; Function Attrs: mustprogress nounwind willreturn memory(argmem: readwrite, inaccessiblemem: readwrite) uwtable
define internal noalias noundef ptr @qc_realloc(ptr noundef captures(none) %0, i64 noundef %1) local_unnamed_addr #2 {
  %3 = tail call ptr @realloc(ptr noundef %0, i64 noundef %1) #36
  ret ptr %3
}

; Function Attrs: mustprogress nounwind willreturn allockind("realloc") allocsize(1) memory(argmem: readwrite, inaccessiblemem: readwrite)
declare noalias noundef ptr @realloc(ptr allocptr noundef captures(none), i64 noundef) local_unnamed_addr #4

; Function Attrs: mustprogress nofree nounwind willreturn memory(inaccessiblemem: readwrite) uwtable
define internal noalias noundef ptr @qc_calloc(i64 noundef %0, i64 noundef %1) local_unnamed_addr #0 {
  %3 = tail call noalias ptr @calloc(i64 noundef %0, i64 noundef %1) #37
  ret ptr %3
}

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,zeroed") allocsize(0,1) memory(inaccessiblemem: readwrite)
declare noalias noundef ptr @calloc(i64 noundef, i64 noundef) local_unnamed_addr #5

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_fmt_int(i64 noundef %0, i32 noundef %1, i32 noundef %2, i1 noundef zeroext %3) local_unnamed_addr #6 {
  %5 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %5) #35
  %6 = icmp sgt i32 %2, -1
  %7 = icmp sgt i32 %1, 0
  br i1 %6, label %8, label %14

8:                                                ; preds = %4
  br i1 %7, label %9, label %12

9:                                                ; preds = %8
  %10 = select i1 %3, ptr @.str.1, ptr @.str.2
  %11 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str, ptr noundef nonnull %10, i32 noundef %1, i32 noundef %2) #35
  br label %20

12:                                               ; preds = %8
  %13 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.3, i32 noundef %2) #35
  br label %20

14:                                               ; preds = %4
  br i1 %7, label %15, label %18

15:                                               ; preds = %14
  %16 = select i1 %3, ptr @.str.1, ptr @.str.2
  %17 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.4, ptr noundef nonnull %16, i32 noundef %1) #35
  br label %20

18:                                               ; preds = %14
  %19 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.5) #35
  br label %20

20:                                               ; preds = %18, %15, %12, %9
  %21 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %5, i64 noundef %0) #35
  %22 = add nsw i32 %21, 1
  %23 = sext i32 %22 to i64
  %24 = tail call noalias ptr @malloc(i64 noundef %23) #34
  %25 = icmp eq ptr %24, null
  br i1 %25, label %28, label %26

26:                                               ; preds = %20
  %27 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull %24, i64 noundef %23, ptr noundef nonnull %5, i64 noundef %0) #35
  br label %28

28:                                               ; preds = %26, %20
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %5) #35
  ret ptr %24
}

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr captures(none)) #7

; Function Attrs: nofree nounwind
declare noundef i32 @snprintf(ptr noalias noundef writeonly captures(none), i64 noundef, ptr noundef readonly captures(none), ...) local_unnamed_addr #8

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr captures(none)) #7

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_flush() local_unnamed_addr #6 {
  %1 = tail call i32 @fflush(ptr noundef null)
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @fflush(ptr noundef captures(none)) local_unnamed_addr #8

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_fmt_unsigned_int(i64 noundef %0, i1 noundef zeroext %1) local_unnamed_addr #6 {
  %3 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %3) #35
  %4 = select i1 %1, ptr @.str.6, ptr @.str.7
  %5 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %3, i64 noundef 32, ptr noundef nonnull %4) #35
  %6 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %3, i64 noundef %0) #35
  %7 = icmp slt i32 %6, 0
  br i1 %7, label %15, label %8

8:                                                ; preds = %2
  %9 = add nuw nsw i32 %6, 1
  %10 = zext nneg i32 %9 to i64
  %11 = tail call noalias ptr @malloc(i64 noundef %10) #34
  %12 = icmp eq ptr %11, null
  br i1 %12, label %15, label %13

13:                                               ; preds = %8
  %14 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %11, i64 noundef %10, ptr noundef nonnull %3, i64 noundef %0) #35
  br label %15

15:                                               ; preds = %13, %8, %2
  %16 = phi ptr [ null, %2 ], [ %11, %13 ], [ null, %8 ]
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %3) #35
  ret ptr %16
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_fmt_float(double noundef %0, i32 noundef %1, i32 noundef %2, i1 noundef zeroext %3) local_unnamed_addr #6 {
  %5 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %5) #35
  %6 = icmp sgt i32 %2, -1
  %7 = icmp sgt i32 %1, 0
  br i1 %6, label %8, label %14

8:                                                ; preds = %4
  br i1 %7, label %9, label %12

9:                                                ; preds = %8
  %10 = select i1 %3, ptr @.str.1, ptr @.str.2
  %11 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.8, ptr noundef nonnull %10, i32 noundef %1, i32 noundef %2) #35
  br label %20

12:                                               ; preds = %8
  %13 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.9, i32 noundef %2) #35
  br label %20

14:                                               ; preds = %4
  br i1 %7, label %15, label %18

15:                                               ; preds = %14
  %16 = select i1 %3, ptr @.str.1, ptr @.str.2
  %17 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.10, ptr noundef nonnull %16, i32 noundef %1) #35
  br label %20

18:                                               ; preds = %14
  %19 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.11) #35
  br label %20

20:                                               ; preds = %18, %15, %12, %9
  %21 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %5, double noundef %0) #35
  %22 = icmp slt i32 %21, 0
  br i1 %22, label %30, label %23

23:                                               ; preds = %20
  %24 = add nuw i32 %21, 1
  %25 = zext i32 %24 to i64
  %26 = tail call noalias ptr @malloc(i64 noundef %25) #34
  %27 = icmp eq ptr %26, null
  br i1 %27, label %30, label %28

28:                                               ; preds = %23
  %29 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %26, i64 noundef %25, ptr noundef nonnull %5, double noundef %0) #35
  br label %30

30:                                               ; preds = %28, %23, %20
  %31 = phi ptr [ null, %20 ], [ %26, %28 ], [ null, %23 ]
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %5) #35
  ret ptr %31
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_fmt_double(double noundef %0, i32 noundef %1, i32 noundef %2, i1 noundef zeroext %3) local_unnamed_addr #6 {
  %5 = tail call ptr @qc_fmt_float(double noundef %0, i32 noundef %1, i32 noundef %2, i1 noundef zeroext %3)
  ret ptr %5
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_fmt_scientific(double noundef %0, i32 noundef %1, i32 noundef %2, i1 noundef zeroext %3) local_unnamed_addr #6 {
  %5 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %5) #35
  %6 = icmp sgt i32 %2, -1
  %7 = icmp sgt i32 %1, 0
  br i1 %6, label %8, label %14

8:                                                ; preds = %4
  br i1 %7, label %9, label %12

9:                                                ; preds = %8
  %10 = select i1 %3, ptr @.str.1, ptr @.str.2
  %11 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.12, ptr noundef nonnull %10, i32 noundef %1, i32 noundef %2) #35
  br label %20

12:                                               ; preds = %8
  %13 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.13, i32 noundef %2) #35
  br label %20

14:                                               ; preds = %4
  br i1 %7, label %15, label %18

15:                                               ; preds = %14
  %16 = select i1 %3, ptr @.str.1, ptr @.str.2
  %17 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.14, ptr noundef nonnull %16, i32 noundef %1) #35
  br label %20

18:                                               ; preds = %14
  %19 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 32, ptr noundef nonnull @.str.15) #35
  br label %20

20:                                               ; preds = %18, %15, %12, %9
  %21 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %5, double noundef %0) #35
  %22 = icmp slt i32 %21, 0
  br i1 %22, label %30, label %23

23:                                               ; preds = %20
  %24 = add nuw nsw i32 %21, 1
  %25 = zext nneg i32 %24 to i64
  %26 = tail call noalias ptr @malloc(i64 noundef %25) #34
  %27 = icmp eq ptr %26, null
  br i1 %27, label %30, label %28

28:                                               ; preds = %23
  %29 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %26, i64 noundef %25, ptr noundef nonnull %5, double noundef %0) #35
  br label %30

30:                                               ; preds = %28, %23, %20
  %31 = phi ptr [ null, %20 ], [ %26, %28 ], [ null, %23 ]
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %5) #35
  ret ptr %31
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_fmt_char(i8 noundef signext %0, i32 noundef %1, i1 noundef zeroext %2) local_unnamed_addr #6 {
  %4 = alloca [16 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 16, ptr nonnull %4) #35
  %5 = icmp sgt i32 %1, 0
  br i1 %5, label %6, label %9

6:                                                ; preds = %3
  %7 = select i1 %2, ptr @.str.1, ptr @.str.2
  %8 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 16, ptr noundef nonnull @.str.16, ptr noundef nonnull %7, i32 noundef %1) #35
  br label %11

9:                                                ; preds = %3
  %10 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 16, ptr noundef nonnull @.str.17) #35
  br label %11

11:                                               ; preds = %9, %6
  %12 = sext i8 %0 to i32
  %13 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %4, i32 noundef %12) #35
  %14 = icmp slt i32 %13, 0
  br i1 %14, label %22, label %15

15:                                               ; preds = %11
  %16 = add nuw nsw i32 %13, 1
  %17 = zext nneg i32 %16 to i64
  %18 = tail call noalias ptr @malloc(i64 noundef %17) #34
  %19 = icmp eq ptr %18, null
  br i1 %19, label %22, label %20

20:                                               ; preds = %15
  %21 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %18, i64 noundef %17, ptr noundef nonnull %4, i32 noundef %12) #35
  br label %22

22:                                               ; preds = %20, %15, %11
  %23 = phi ptr [ null, %11 ], [ %18, %20 ], [ null, %15 ]
  call void @llvm.lifetime.end.p0(i64 16, ptr nonnull %4) #35
  ret ptr %23
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_fmt_string(ptr noundef %0, i32 noundef %1, i1 noundef zeroext %2) local_unnamed_addr #6 {
  %4 = alloca [16 x i8], align 16
  %5 = icmp eq ptr %0, null
  %6 = select i1 %5, ptr @.str.2, ptr %0
  call void @llvm.lifetime.start.p0(i64 16, ptr nonnull %4) #35
  %7 = icmp sgt i32 %1, 0
  br i1 %7, label %8, label %11

8:                                                ; preds = %3
  %9 = select i1 %2, ptr @.str.1, ptr @.str.2
  %10 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 16, ptr noundef nonnull @.str.18, ptr noundef nonnull %9, i32 noundef %1) #35
  br label %13

11:                                               ; preds = %3
  %12 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 16, ptr noundef nonnull @.str.19) #35
  br label %13

13:                                               ; preds = %11, %8
  %14 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %4, ptr noundef nonnull %6) #35
  %15 = icmp slt i32 %14, 0
  br i1 %15, label %23, label %16

16:                                               ; preds = %13
  %17 = add nuw nsw i32 %14, 1
  %18 = zext nneg i32 %17 to i64
  %19 = tail call noalias ptr @malloc(i64 noundef %18) #34
  %20 = icmp eq ptr %19, null
  br i1 %20, label %23, label %21

21:                                               ; preds = %16
  %22 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %19, i64 noundef %18, ptr noundef nonnull %4, ptr noundef nonnull %6) #35
  br label %23

23:                                               ; preds = %21, %16, %13
  %24 = phi ptr [ null, %13 ], [ %19, %21 ], [ null, %16 ]
  call void @llvm.lifetime.end.p0(i64 16, ptr nonnull %4) #35
  ret ptr %24
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_fmt_hex(i64 noundef %0, i32 noundef %1, i1 noundef zeroext %2) local_unnamed_addr #6 {
  %4 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %4) #35
  %5 = icmp sgt i32 %1, 0
  br i1 %5, label %6, label %9

6:                                                ; preds = %3
  %7 = select i1 %2, ptr @.str.1, ptr @.str.2
  %8 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 32, ptr noundef nonnull @.str.20, ptr noundef nonnull %7, i32 noundef %1) #35
  br label %11

9:                                                ; preds = %3
  %10 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 32, ptr noundef nonnull @.str.21) #35
  br label %11

11:                                               ; preds = %9, %6
  %12 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %4, i64 noundef %0) #35
  %13 = add nsw i32 %12, 1
  %14 = sext i32 %13 to i64
  %15 = tail call noalias ptr @malloc(i64 noundef %14) #34
  %16 = icmp eq ptr %15, null
  br i1 %16, label %19, label %17

17:                                               ; preds = %11
  %18 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull %15, i64 noundef %14, ptr noundef nonnull %4, i64 noundef %0) #35
  br label %19

19:                                               ; preds = %17, %11
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %4) #35
  ret ptr %15
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_fmt_octal(i64 noundef %0, i32 noundef %1, i1 noundef zeroext %2) local_unnamed_addr #6 {
  %4 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %4) #35
  %5 = icmp sgt i32 %1, 0
  br i1 %5, label %6, label %9

6:                                                ; preds = %3
  %7 = select i1 %2, ptr @.str.1, ptr @.str.2
  %8 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 32, ptr noundef nonnull @.str.22, ptr noundef nonnull %7, i32 noundef %1) #35
  br label %11

9:                                                ; preds = %3
  %10 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 32, ptr noundef nonnull @.str.23) #35
  br label %11

11:                                               ; preds = %9, %6
  %12 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %4, i64 noundef %0) #35
  %13 = add nsw i32 %12, 1
  %14 = sext i32 %13 to i64
  %15 = tail call noalias ptr @malloc(i64 noundef %14) #34
  %16 = icmp eq ptr %15, null
  br i1 %16, label %19, label %17

17:                                               ; preds = %11
  %18 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull %15, i64 noundef %14, ptr noundef nonnull %4, i64 noundef %0) #35
  br label %19

19:                                               ; preds = %17, %11
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %4) #35
  ret ptr %15
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_fmt_bool(i1 noundef zeroext %0, i32 noundef %1, i1 noundef zeroext %2) local_unnamed_addr #6 {
  %4 = alloca [16 x i8], align 16
  %5 = select i1 %0, ptr @.str.24, ptr @.str.25
  call void @llvm.lifetime.start.p0(i64 16, ptr nonnull %4) #35
  %6 = icmp sgt i32 %1, 0
  br i1 %6, label %7, label %10

7:                                                ; preds = %3
  %8 = select i1 %2, ptr @.str.1, ptr @.str.2
  %9 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 16, ptr noundef nonnull @.str.18, ptr noundef nonnull %8, i32 noundef %1) #35
  br label %12

10:                                               ; preds = %3
  %11 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 16, ptr noundef nonnull @.str.19) #35
  br label %12

12:                                               ; preds = %10, %7
  %13 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %4, ptr noundef nonnull %5) #35
  %14 = icmp slt i32 %13, 0
  br i1 %14, label %22, label %15

15:                                               ; preds = %12
  %16 = add nuw nsw i32 %13, 1
  %17 = zext nneg i32 %16 to i64
  %18 = tail call noalias ptr @malloc(i64 noundef %17) #34
  %19 = icmp eq ptr %18, null
  br i1 %19, label %22, label %20

20:                                               ; preds = %15
  %21 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %18, i64 noundef %17, ptr noundef nonnull %4, ptr noundef nonnull %5) #35
  br label %22

22:                                               ; preds = %20, %15, %12
  %23 = phi ptr [ null, %12 ], [ %18, %20 ], [ null, %15 ]
  call void @llvm.lifetime.end.p0(i64 16, ptr nonnull %4) #35
  ret ptr %23
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_fmt_qbool(i8 noundef zeroext %0, i32 noundef %1, i1 noundef zeroext %2) local_unnamed_addr #6 {
  %4 = alloca [16 x i8], align 16
  %5 = and i8 %0, 3
  %6 = zext nneg i8 %5 to i64
  %7 = getelementptr inbounds nuw [4 x ptr], ptr @switch.table.qc_print_array_qbool, i64 0, i64 %6
  %8 = load ptr, ptr %7, align 8
  call void @llvm.lifetime.start.p0(i64 16, ptr nonnull %4) #35
  %9 = icmp sgt i32 %1, 0
  br i1 %9, label %10, label %13

10:                                               ; preds = %3
  %11 = select i1 %2, ptr @.str.1, ptr @.str.2
  %12 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 16, ptr noundef nonnull @.str.18, ptr noundef nonnull %11, i32 noundef %1) #35
  br label %15

13:                                               ; preds = %3
  %14 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 16, ptr noundef nonnull @.str.19) #35
  br label %15

15:                                               ; preds = %13, %10
  %16 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %4, ptr noundef nonnull %8) #35
  %17 = icmp slt i32 %16, 0
  br i1 %17, label %25, label %18

18:                                               ; preds = %15
  %19 = add nuw nsw i32 %16, 1
  %20 = zext nneg i32 %19 to i64
  %21 = tail call noalias ptr @malloc(i64 noundef %20) #34
  %22 = icmp eq ptr %21, null
  br i1 %22, label %25, label %23

23:                                               ; preds = %18
  %24 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %21, i64 noundef %20, ptr noundef nonnull %4, ptr noundef nonnull %8) #35
  br label %25

25:                                               ; preds = %23, %18, %15
  %26 = phi ptr [ null, %15 ], [ %21, %23 ], [ null, %18 ]
  call void @llvm.lifetime.end.p0(i64 16, ptr nonnull %4) #35
  ret ptr %26
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias ptr @qc_fmt_ptr(ptr noundef %0, i32 noundef %1, i1 noundef zeroext %2) local_unnamed_addr #6 {
  %4 = alloca [64 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 64, ptr nonnull %4) #35
  %5 = icmp sgt i32 %1, 0
  %6 = and i1 %2, %5
  br i1 %6, label %7, label %10

7:                                                ; preds = %3
  %8 = ptrtoint ptr %0 to i64
  %9 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 64, ptr noundef nonnull @.str.30, i32 noundef %1, i64 noundef %8) #35
  br label %15

10:                                               ; preds = %3
  br i1 %5, label %11, label %13

11:                                               ; preds = %10
  %12 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 64, ptr noundef nonnull @.str.31, i32 noundef %1, ptr noundef %0) #35
  br label %15

13:                                               ; preds = %10
  %14 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %4, i64 noundef 64, ptr noundef nonnull @.str.32, ptr noundef %0) #35
  br label %15

15:                                               ; preds = %13, %11, %7
  %16 = call noalias ptr @strdup(ptr noundef nonnull %4) #35
  call void @llvm.lifetime.end.p0(i64 64, ptr nonnull %4) #35
  ret ptr %16
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(argmem: readwrite, inaccessiblemem: readwrite)
declare noalias ptr @strdup(ptr noundef readonly captures(none)) local_unnamed_addr #9

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal i32 @qc_powi_i32(i32 noundef %0, i32 noundef %1) local_unnamed_addr #10 {
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
define internal void @qc_print_ptr(ptr noundef %0) local_unnamed_addr #6 {
  %2 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.33, ptr noundef %0)
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @printf(ptr noundef readonly captures(none), ...) local_unnamed_addr #8

; Function Attrs: mustprogress nofree nounwind willreturn uwtable
define internal noalias noundef ptr @qc_string_concat(ptr noundef readonly captures(address_is_null) %0, ptr noundef readonly captures(address_is_null) %1) local_unnamed_addr #11 {
  %3 = icmp eq ptr %0, null
  %4 = select i1 %3, ptr @.str.2, ptr %0
  %5 = icmp eq ptr %1, null
  %6 = select i1 %5, ptr @.str.2, ptr %1
  %7 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %4) #38
  %8 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %6) #38
  %9 = add i64 %8, %7
  %10 = add i64 %9, 1
  %11 = tail call noalias ptr @malloc(i64 noundef %10) #34
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
define internal zeroext i1 @qc_string_eq(ptr noundef readonly captures(address_is_null) %0, ptr noundef readonly captures(address_is_null) %1) local_unnamed_addr #14 {
  %3 = icmp ne ptr %0, null
  %4 = icmp ne ptr %1, null
  %5 = and i1 %3, %4
  br i1 %5, label %6, label %9

6:                                                ; preds = %2
  %7 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(1) %1) #38
  %8 = icmp eq i32 %7, 0
  br label %9

9:                                                ; preds = %6, %2
  %10 = phi i1 [ %8, %6 ], [ false, %2 ]
  ret i1 %10
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(argmem: read)
declare i32 @strcmp(ptr noundef captures(none), ptr noundef captures(none)) local_unnamed_addr #12

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal noundef zeroext range(i8 1, 4) i8 @qc_qand(i8 noundef zeroext %0, i8 noundef zeroext %1) local_unnamed_addr #10 {
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
define internal zeroext range(i8 0, 4) i8 @qc_qor(i8 noundef zeroext %0, i8 noundef zeroext %1) local_unnamed_addr #10 {
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
define internal zeroext range(i8 0, 4) i8 @qc_qxor(i8 noundef zeroext %0, i8 noundef zeroext %1) local_unnamed_addr #10 {
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
define internal noundef zeroext i8 @qc_qnot(i8 noundef zeroext %0) local_unnamed_addr #10 {
  %2 = sub i8 3, %0
  ret i8 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal noundef zeroext i1 @qc_qand_collapse(i8 noundef zeroext %0, i8 noundef zeroext %1) local_unnamed_addr #10 {
  %3 = and i8 %0, 2
  %4 = and i8 %3, %1
  %5 = icmp ne i8 %4, 0
  ret i1 %5
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal noundef zeroext i1 @qc_qor_collapse(i8 noundef zeroext %0, i8 noundef zeroext %1) local_unnamed_addr #10 {
  %3 = or i8 %1, %0
  %4 = and i8 %3, 2
  %5 = icmp ne i8 %4, 0
  ret i1 %5
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_to_string_int(i32 noundef %0) local_unnamed_addr #6 {
  %2 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %2) #35
  %3 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 32, ptr noundef nonnull @.str.34, i32 noundef %0) #35
  %4 = icmp slt i32 %3, 0
  br i1 %4, label %11, label %5

5:                                                ; preds = %1
  %6 = add nuw nsw i32 %3, 1
  %7 = zext nneg i32 %6 to i64
  %8 = tail call noalias ptr @malloc(i64 noundef %7) #34
  %9 = icmp eq ptr %8, null
  br i1 %9, label %11, label %10

10:                                               ; preds = %5
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %8, ptr noundef nonnull align 16 dereferenceable(1) %2, i64 %7, i1 false)
  br label %11

11:                                               ; preds = %10, %5, %1
  %12 = phi ptr [ null, %1 ], [ %8, %10 ], [ null, %5 ]
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %2) #35
  ret ptr %12
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_to_string_float(float noundef %0) local_unnamed_addr #6 {
  %2 = alloca [64 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 64, ptr nonnull %2) #35
  %3 = fpext float %0 to double
  %4 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 64, ptr noundef nonnull @.str.35, double noundef %3) #35
  %5 = icmp slt i32 %4, 0
  br i1 %5, label %12, label %6

6:                                                ; preds = %1
  %7 = add nuw nsw i32 %4, 1
  %8 = zext nneg i32 %7 to i64
  %9 = tail call noalias ptr @malloc(i64 noundef %8) #34
  %10 = icmp eq ptr %9, null
  br i1 %10, label %12, label %11

11:                                               ; preds = %6
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %9, ptr noundef nonnull align 16 dereferenceable(1) %2, i64 %8, i1 false)
  br label %12

12:                                               ; preds = %11, %6, %1
  %13 = phi ptr [ null, %1 ], [ %9, %11 ], [ null, %6 ]
  call void @llvm.lifetime.end.p0(i64 64, ptr nonnull %2) #35
  ret ptr %13
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_to_string_long_int(i64 noundef %0) local_unnamed_addr #6 {
  %2 = alloca [32 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %2) #35
  %3 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 32, ptr noundef nonnull @.str.36, i64 noundef %0) #35
  %4 = icmp slt i32 %3, 0
  br i1 %4, label %11, label %5

5:                                                ; preds = %1
  %6 = add nuw nsw i32 %3, 1
  %7 = zext nneg i32 %6 to i64
  %8 = tail call noalias ptr @malloc(i64 noundef %7) #34
  %9 = icmp eq ptr %8, null
  br i1 %9, label %11, label %10

10:                                               ; preds = %5
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %8, ptr noundef nonnull align 16 dereferenceable(1) %2, i64 %7, i1 false)
  br label %11

11:                                               ; preds = %10, %5, %1
  %12 = phi ptr [ null, %1 ], [ %8, %10 ], [ null, %5 ]
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %2) #35
  ret ptr %12
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_to_string_short_int(i16 noundef signext %0) local_unnamed_addr #6 {
  %2 = alloca [64 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 64, ptr nonnull %2) #35
  %3 = sext i16 %0 to i32
  %4 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 64, ptr noundef nonnull @.str.37, i32 noundef %3) #35
  %5 = icmp slt i32 %4, 0
  br i1 %5, label %12, label %6

6:                                                ; preds = %1
  %7 = add nuw nsw i32 %4, 1
  %8 = zext nneg i32 %7 to i64
  %9 = tail call noalias ptr @malloc(i64 noundef %8) #34
  %10 = icmp eq ptr %9, null
  br i1 %10, label %12, label %11

11:                                               ; preds = %6
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %9, ptr noundef nonnull align 16 dereferenceable(1) %2, i64 %8, i1 false)
  br label %12

12:                                               ; preds = %11, %6, %1
  %13 = phi ptr [ null, %1 ], [ %9, %11 ], [ null, %6 ]
  call void @llvm.lifetime.end.p0(i64 64, ptr nonnull %2) #35
  ret ptr %13
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal i32 @qc_to_int_from_float(float noundef %0) local_unnamed_addr #10 {
  %2 = fptosi float %0 to i32
  ret i32 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal i32 @qc_to_int_from_double(double noundef %0) local_unnamed_addr #10 {
  %2 = fptosi double %0 to i32
  ret i32 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal range(i32 -128, 128) i32 @qc_to_int_from_char(i8 noundef signext %0) local_unnamed_addr #10 {
  %2 = sext i8 %0 to i32
  ret i32 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal noundef float @qc_to_float_from_double(double noundef %0) local_unnamed_addr #10 {
  %2 = fptrunc double %0 to float
  ret float %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal noundef float @qc_to_float_from_bool(i1 noundef zeroext %0) local_unnamed_addr #10 {
  %2 = select i1 %0, float 1.000000e+00, float 0.000000e+00
  ret float %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal noundef double @qc_to_double_from_float(float noundef %0) local_unnamed_addr #10 {
  %2 = fpext float %0 to double
  ret double %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal noundef double @qc_to_double_from_bool(i1 noundef zeroext %0) local_unnamed_addr #10 {
  %2 = select i1 %0, double 1.000000e+00, double 0.000000e+00
  ret double %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal noundef zeroext i1 @qc_to_bool_from_int(i32 noundef %0) local_unnamed_addr #10 {
  %2 = icmp ne i32 %0, 0
  ret i1 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal noundef zeroext i1 @qc_to_bool_from_float(float noundef %0) local_unnamed_addr #10 {
  %2 = fcmp une float %0, 0.000000e+00
  ret i1 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal noundef zeroext i1 @qc_to_bool_from_double(double noundef %0) local_unnamed_addr #10 {
  %2 = fcmp une double %0, 0.000000e+00
  ret i1 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal noundef signext i8 @qc_to_char_from_int(i32 noundef %0) local_unnamed_addr #10 {
  %2 = trunc i32 %0 to i8
  ret i8 %2
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_to_string_double(double noundef %0) local_unnamed_addr #6 {
  %2 = alloca [64 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 64, ptr nonnull %2) #35
  %3 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 64, ptr noundef nonnull @.str.35, double noundef %0) #35
  %4 = icmp slt i32 %3, 0
  br i1 %4, label %11, label %5

5:                                                ; preds = %1
  %6 = add nuw nsw i32 %3, 1
  %7 = zext nneg i32 %6 to i64
  %8 = tail call noalias ptr @malloc(i64 noundef %7) #34
  %9 = icmp eq ptr %8, null
  br i1 %9, label %11, label %10

10:                                               ; preds = %5
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %8, ptr noundef nonnull align 16 dereferenceable(1) %2, i64 %7, i1 false)
  br label %11

11:                                               ; preds = %10, %5, %1
  %12 = phi ptr [ null, %1 ], [ %8, %10 ], [ null, %5 ]
  call void @llvm.lifetime.end.p0(i64 64, ptr nonnull %2) #35
  ret ptr %12
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(readwrite, argmem: none) uwtable
define internal noalias noundef ptr @qc_to_string_bool(i1 noundef zeroext %0) local_unnamed_addr #15 {
  %2 = select i1 %0, i64 5, i64 6
  %3 = tail call noalias ptr @malloc(i64 noundef %2) #34
  %4 = icmp eq ptr %3, null
  br i1 %4, label %7, label %5

5:                                                ; preds = %1
  %6 = select i1 %0, ptr @.str.24, ptr @.str.25
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(5) %3, ptr noundef nonnull align 1 dereferenceable(5) %6, i64 %2, i1 false)
  br label %7

7:                                                ; preds = %5, %1
  ret ptr %3
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(readwrite, argmem: none) uwtable
define internal noalias noundef ptr @qc_to_string_qbool(i8 noundef zeroext %0) local_unnamed_addr #15 {
  %2 = and i8 %0, 3
  %3 = zext nneg i8 %2 to i64
  %4 = getelementptr inbounds nuw [4 x ptr], ptr @switch.table.qc_print_array_qbool, i64 0, i64 %3
  %5 = load ptr, ptr %4, align 8
  %6 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %5) #38
  %7 = add i64 %6, 1
  %8 = tail call noalias ptr @malloc(i64 noundef %7) #34
  %9 = icmp eq ptr %8, null
  br i1 %9, label %11, label %10

10:                                               ; preds = %1
  tail call void @llvm.memcpy.p0.p0.i64(ptr nonnull align 1 %8, ptr nonnull align 1 %5, i64 %7, i1 false)
  br label %11

11:                                               ; preds = %10, %1
  ret ptr %8
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(write, argmem: none, inaccessiblemem: readwrite) uwtable
define internal noalias noundef ptr @qc_to_string_char(i8 noundef signext %0) local_unnamed_addr #16 {
  %2 = tail call noalias dereferenceable_or_null(2) ptr @malloc(i64 noundef 2) #34
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
define internal void @qc_print_string(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #6 {
  %2 = icmp eq ptr %0, null
  %3 = select i1 %2, ptr @.str.2, ptr %0
  %4 = load ptr, ptr @stdout, align 8, !tbaa !10
  %5 = tail call i32 @fputs(ptr noundef nonnull %3, ptr noundef %4)
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @fputs(ptr noundef readonly captures(none), ptr noundef captures(none)) local_unnamed_addr #8

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_print_int(i32 noundef %0) local_unnamed_addr #6 {
  %2 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, i32 noundef %0)
  ret void
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_print_double(double noundef %0) local_unnamed_addr #6 {
  %2 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.35, double noundef %0)
  ret void
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_print_char(i8 noundef signext %0) local_unnamed_addr #6 {
  %2 = zext i8 %0 to i32
  %3 = load ptr, ptr @stdout, align 8, !tbaa !10
  %4 = tail call noundef i32 @putc(i32 noundef %2, ptr noundef %3)
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @putc(i32 noundef, ptr noundef captures(none)) local_unnamed_addr #8

; Function Attrs: mustprogress nounwind uwtable
define internal i32 @qc_time() local_unnamed_addr #17 {
  %1 = tail call i64 @time(ptr noundef null) #35
  %2 = trunc i64 %1 to i32
  ret i32 %2
}

; Function Attrs: nounwind
declare i64 @time(ptr noundef) local_unnamed_addr #18

; Function Attrs: mustprogress nounwind uwtable
define internal void @qc_seed(i32 noundef %0) local_unnamed_addr #17 {
  tail call void @srand(i32 noundef %0) #35
  ret void
}

; Function Attrs: nounwind
declare void @srand(i32 noundef) local_unnamed_addr #18

; Function Attrs: mustprogress nounwind uwtable
define internal float @qc_random_float() local_unnamed_addr #17 {
  %1 = tail call i32 @rand() #35
  %2 = sitofp i32 %1 to float
  %3 = fmul float %2, 0x3E00000000000000
  ret float %3
}

; Function Attrs: nounwind
declare i32 @rand() local_unnamed_addr #18

; Function Attrs: mustprogress nounwind uwtable
define internal range(i32 -2147483647, -2147483648) i32 @qc_random_int(i32 noundef %0) local_unnamed_addr #17 {
  %2 = tail call i32 @rand() #35
  %3 = srem i32 %2, %0
  ret i32 %3
}

; Function Attrs: mustprogress nounwind uwtable
define internal i32 @qc_random_range(i32 noundef %0, i32 noundef %1) local_unnamed_addr #17 {
  %3 = tail call i32 @rand() #35
  %4 = sub nsw i32 %1, %0
  %5 = srem i32 %3, %4
  %6 = add nsw i32 %5, %0
  ret i32 %6
}

; Function Attrs: mustprogress nofree norecurse nounwind willreturn memory(argmem: read) uwtable
define internal i32 @qc_len(ptr noundef readonly captures(none) %0) local_unnamed_addr #14 {
  %2 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #38
  %3 = trunc i64 %2 to i32
  ret i32 %3
}

; Function Attrs: mustprogress nofree nounwind memory(readwrite, argmem: read) uwtable
define internal noalias noundef ptr @qc_to_lower(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #19 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %22, label %3

3:                                                ; preds = %1
  %4 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #38
  %5 = add i64 %4, 1
  %6 = tail call noalias ptr @malloc(i64 noundef %5) #34
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
  %17 = tail call i32 @tolower(i32 noundef %16) #38
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
define internal noalias noundef ptr @qc_to_upper(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #19 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %22, label %3

3:                                                ; preds = %1
  %4 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #38
  %5 = add i64 %4, 1
  %6 = tail call noalias ptr @malloc(i64 noundef %5) #34
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
  %17 = tail call i32 @toupper(i32 noundef %16) #38
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
define internal noalias noundef ptr @qc_substring(ptr noundef readonly captures(address_is_null) %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #11 {
  %4 = icmp eq ptr %0, null
  br i1 %4, label %29, label %5

5:                                                ; preds = %3
  %6 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #38
  %7 = trunc i64 %6 to i32
  %8 = icmp slt i32 %1, 0
  br i1 %8, label %13, label %9

9:                                                ; preds = %5
  %10 = icmp sge i32 %1, %7
  %11 = icmp slt i32 %2, 1
  %12 = or i1 %11, %10
  br i1 %12, label %13, label %15

13:                                               ; preds = %9, %5
  %14 = tail call noalias dereferenceable_or_null(1) ptr @malloc(i64 noundef 1) #34
  store i8 0, ptr %14, align 1, !tbaa !7
  br label %29

15:                                               ; preds = %9
  %16 = add nuw nsw i32 %2, %1
  %17 = icmp samesign ugt i32 %16, %7
  %18 = sub nsw i32 %7, %1
  %19 = select i1 %17, i32 %18, i32 %2
  %20 = add nuw nsw i32 %19, 1
  %21 = zext nneg i32 %20 to i64
  %22 = tail call noalias ptr @malloc(i64 noundef %21) #34
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
define internal range(i32 0, 2) i32 @qc_contains(ptr noundef readonly %0, ptr noundef readonly captures(address_is_null) %1) local_unnamed_addr #14 {
  %3 = icmp ne ptr %0, null
  %4 = icmp ne ptr %1, null
  %5 = and i1 %3, %4
  br i1 %5, label %6, label %10

6:                                                ; preds = %2
  %7 = tail call noundef ptr @strstr(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(1) %1) #38
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
define internal range(i32 0, 2) i32 @qc_startswith(ptr noundef readonly captures(address_is_null) %0, ptr noundef readonly captures(address_is_null) %1) local_unnamed_addr #14 {
  %3 = icmp ne ptr %0, null
  %4 = icmp ne ptr %1, null
  %5 = and i1 %3, %4
  br i1 %5, label %6, label %11

6:                                                ; preds = %2
  %7 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %1) #38
  %8 = tail call i32 @strncmp(ptr noundef nonnull %0, ptr noundef nonnull %1, i64 noundef %7) #38
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
define internal range(i32 0, 2) i32 @qc_endswith(ptr noundef readonly captures(address_is_null) %0, ptr noundef readonly captures(address_is_null) %1) local_unnamed_addr #14 {
  %3 = icmp ne ptr %0, null
  %4 = icmp ne ptr %1, null
  %5 = and i1 %3, %4
  br i1 %5, label %6, label %17

6:                                                ; preds = %2
  %7 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #38
  %8 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %1) #38
  %9 = icmp ugt i64 %8, %7
  br i1 %9, label %17, label %10

10:                                               ; preds = %6
  %11 = getelementptr inbounds nuw i8, ptr %0, i64 %7
  %12 = sub i64 0, %8
  %13 = getelementptr inbounds i8, ptr %11, i64 %12
  %14 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %13, ptr noundef nonnull dereferenceable(1) %1) #38
  %15 = icmp eq i32 %14, 0
  %16 = zext i1 %15 to i32
  br label %17

17:                                               ; preds = %10, %6, %2
  %18 = phi i32 [ 0, %2 ], [ %16, %10 ], [ 0, %6 ]
  ret i32 %18
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_print_float(float noundef %0) local_unnamed_addr #6 {
  %2 = fpext float %0 to double
  %3 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.35, double noundef %2)
  ret void
}

; Function Attrs: mustprogress nofree norecurse nounwind willreturn memory(argmem: read) uwtable
define internal zeroext i1 @qc_to_bool_from_string(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #14 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %13, label %3

3:                                                ; preds = %1
  %4 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(5) @.str.24) #38
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
define internal zeroext range(i8 0, 4) i8 @qc_to_qbool_from_string(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #14 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %13, label %3

3:                                                ; preds = %1
  %4 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(6) @.str.28) #38
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %13, label %6

6:                                                ; preds = %3
  %7 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(7) @.str.27) #38
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %13, label %9

9:                                                ; preds = %6
  %10 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(5) @.str.29) #38
  %11 = icmp eq i32 %10, 0
  %12 = select i1 %11, i8 3, i8 0
  br label %13

13:                                               ; preds = %9, %6, %3, %1
  %14 = phi i8 [ 0, %1 ], [ 2, %3 ], [ 1, %6 ], [ %12, %9 ]
  ret i8 %14
}

; Function Attrs: mustprogress uwtable
define internal noalias ptr @qc_qin() local_unnamed_addr #21 {
  %1 = alloca [1024 x i8], align 16
  %2 = load ptr, ptr @stdout, align 8, !tbaa !10
  %3 = tail call i32 @fflush(ptr noundef %2)
  %4 = load ptr, ptr @stderr, align 8, !tbaa !10
  %5 = tail call i32 @fflush(ptr noundef %4)
  %6 = load ptr, ptr @stdin, align 8, !tbaa !10
  %7 = tail call i32 @fflush(ptr noundef %6)
  call void @llvm.lifetime.start.p0(i64 1024, ptr nonnull %1) #35
  %8 = call i32 (ptr, ...) @__isoc23_scanf(ptr noundef nonnull @.str.39, ptr noundef nonnull %1)
  %9 = load ptr, ptr @stderr, align 8, !tbaa !10
  %10 = call i32 @fflush(ptr noundef %9)
  %11 = load ptr, ptr @stdin, align 8, !tbaa !10
  %12 = call i32 @fflush(ptr noundef %11)
  %13 = icmp eq i32 %8, 1
  %14 = select i1 %13, ptr %1, ptr @.str.2
  %15 = call noalias ptr @strdup(ptr noundef nonnull %14) #35
  call void @llvm.lifetime.end.p0(i64 1024, ptr nonnull %1) #35
  ret ptr %15
}

declare i32 @__isoc23_scanf(ptr noundef, ...) local_unnamed_addr #22

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_print_bool(i1 noundef zeroext %0) local_unnamed_addr #6 {
  %2 = select i1 %0, ptr @.str.24, ptr @.str.25
  %3 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.39, ptr noundef nonnull %2)
  ret void
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_trim(ptr noundef %0) local_unnamed_addr #6 {
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
  %10 = tail call i32 @isspace(i32 noundef %9) #38
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %18, label %12

12:                                               ; preds = %6
  %13 = getelementptr inbounds nuw i8, ptr %8, i64 1
  %14 = load i8, ptr %13, align 1, !tbaa !7
  %15 = icmp eq i8 %14, 0
  br i1 %15, label %16, label %6, !llvm.loop !15

16:                                               ; preds = %12, %3
  %17 = tail call noalias dereferenceable_or_null(1) ptr @malloc(i64 noundef 1) #34
  store i8 0, ptr %17, align 1, !tbaa !7
  br label %40

18:                                               ; preds = %6
  %19 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %8) #38
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
  %28 = tail call i32 @isspace(i32 noundef %27) #38
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %30, label %21, !llvm.loop !16

30:                                               ; preds = %25, %21
  %31 = ptrtoint ptr %23 to i64
  %32 = ptrtoint ptr %8 to i64
  %33 = sub i64 %31, %32
  %34 = add i64 %33, 2
  %35 = tail call noalias ptr @malloc(i64 noundef %34) #34
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
define internal noundef ptr @qc_replace(ptr noundef readonly %0, ptr noundef readonly captures(address_is_null) %1, ptr noundef readonly captures(address_is_null) %2) local_unnamed_addr #6 {
  %4 = icmp ne ptr %0, null
  %5 = icmp ne ptr %1, null
  %6 = and i1 %4, %5
  %7 = icmp ne ptr %2, null
  %8 = and i1 %6, %7
  br i1 %8, label %9, label %65

9:                                                ; preds = %3
  %10 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %1) #38
  %11 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %2) #38
  %12 = icmp eq i64 %10, 0
  br i1 %12, label %16, label %13

13:                                               ; preds = %9
  %14 = tail call noundef ptr @strstr(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(1) %1) #38
  %15 = icmp eq ptr %14, null
  br i1 %15, label %28, label %21

16:                                               ; preds = %9
  %17 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #38
  %18 = add i64 %17, 1
  %19 = tail call noalias ptr @malloc(i64 noundef %18) #34
  %20 = tail call ptr @strcpy(ptr noundef nonnull dereferenceable(1) %19, ptr noundef nonnull dereferenceable(1) %0) #35
  br label %65

21:                                               ; preds = %21, %13
  %22 = phi ptr [ %26, %21 ], [ %14, %13 ]
  %23 = phi i32 [ %24, %21 ], [ 0, %13 ]
  %24 = add nuw nsw i32 %23, 1
  %25 = getelementptr inbounds nuw i8, ptr %22, i64 %10
  %26 = tail call noundef ptr @strstr(ptr noundef nonnull dereferenceable(1) %25, ptr noundef nonnull dereferenceable(1) %1) #38
  %27 = icmp eq ptr %26, null
  br i1 %27, label %33, label %21, !llvm.loop !17

28:                                               ; preds = %13
  %29 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #38
  %30 = add i64 %29, 1
  %31 = tail call noalias ptr @malloc(i64 noundef %30) #34
  %32 = tail call ptr @strcpy(ptr noundef nonnull dereferenceable(1) %31, ptr noundef nonnull dereferenceable(1) %0) #35
  br label %65

33:                                               ; preds = %21
  %34 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #38
  %35 = zext nneg i32 %24 to i64
  %36 = sub i64 %11, %10
  %37 = mul i64 %36, %35
  %38 = add i64 %37, 1
  %39 = add i64 %38, %34
  %40 = tail call noalias ptr @malloc(i64 noundef %39) #34
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
define internal i32 @qc_to_int_from_string(ptr noundef %0) local_unnamed_addr #17 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %6, label %3

3:                                                ; preds = %1
  %4 = tail call i64 @__isoc23_strtol(ptr noundef nonnull %0, ptr noundef null, i32 noundef 10) #35
  %5 = trunc i64 %4 to i32
  br label %6

6:                                                ; preds = %3, %1
  %7 = phi i32 [ %5, %3 ], [ 0, %1 ]
  ret i32 %7
}

; Function Attrs: nounwind
declare i64 @__isoc23_strtol(ptr noundef, ptr noundef, i32 noundef) local_unnamed_addr #18

; Function Attrs: mustprogress nounwind uwtable
define internal signext i16 @qc_to_short_int_from_string(ptr noundef %0) local_unnamed_addr #17 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %6, label %3

3:                                                ; preds = %1
  %4 = tail call i64 @__isoc23_strtol(ptr noundef nonnull %0, ptr noundef null, i32 noundef 10) #35
  %5 = trunc i64 %4 to i16
  br label %6

6:                                                ; preds = %3, %1
  %7 = phi i16 [ %5, %3 ], [ 0, %1 ]
  ret i16 %7
}

; Function Attrs: mustprogress nounwind uwtable
define internal i64 @qc_to_long_int_from_string(ptr noundef %0) local_unnamed_addr #17 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %5, label %3

3:                                                ; preds = %1
  %4 = tail call i64 @__isoc23_strtoll(ptr noundef nonnull %0, ptr noundef null, i32 noundef 10) #35
  br label %5

5:                                                ; preds = %3, %1
  %6 = phi i64 [ %4, %3 ], [ 0, %1 ]
  ret i64 %6
}

; Function Attrs: nounwind
declare i64 @__isoc23_strtoll(ptr noundef, ptr noundef, i32 noundef) local_unnamed_addr #18

; Function Attrs: mustprogress nounwind uwtable
define internal i64 @qc_to_addr_t_from_string(ptr noundef %0) local_unnamed_addr #17 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %5, label %3

3:                                                ; preds = %1
  %4 = tail call i64 @__isoc23_strtoull(ptr noundef nonnull %0, ptr noundef null, i32 noundef 10) #35
  br label %5

5:                                                ; preds = %3, %1
  %6 = phi i64 [ %4, %3 ], [ 0, %1 ]
  ret i64 %6
}

; Function Attrs: nounwind
declare i64 @__isoc23_strtoull(ptr noundef, ptr noundef, i32 noundef) local_unnamed_addr #18

; Function Attrs: mustprogress nofree norecurse nounwind willreturn uwtable
define internal float @qc_to_float_from_string(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #24 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %6, label %3

3:                                                ; preds = %1
  %4 = tail call double @strtod(ptr noundef nonnull captures(none) %0, ptr noundef null) #35
  %5 = fptrunc double %4 to float
  br label %6

6:                                                ; preds = %3, %1
  %7 = phi float [ %5, %3 ], [ 0.000000e+00, %1 ]
  ret float %7
}

; Function Attrs: mustprogress nofree nounwind willreturn
declare double @strtod(ptr noundef readonly, ptr noundef captures(none)) local_unnamed_addr #25

; Function Attrs: mustprogress nofree norecurse nounwind willreturn uwtable
define internal double @qc_to_double_from_string(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #24 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %5, label %3

3:                                                ; preds = %1
  %4 = tail call double @strtod(ptr noundef nonnull captures(none) %0, ptr noundef null) #35
  br label %5

5:                                                ; preds = %3, %1
  %6 = phi double [ %4, %3 ], [ 0.000000e+00, %1 ]
  ret double %6
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
define internal signext i8 @qc_to_char_from_string(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #26 {
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
define internal range(i32 0, 2) i32 @qc_to_int_from_bool(i1 noundef zeroext %0) local_unnamed_addr #10 {
  %2 = zext i1 %0 to i32
  ret i32 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal noundef float @qc_to_float_from_int(i32 noundef %0) local_unnamed_addr #10 {
  %2 = sitofp i32 %0 to float
  ret float %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal noundef double @qc_to_double_from_int(i32 noundef %0) local_unnamed_addr #10 {
  %2 = sitofp i32 %0 to double
  ret double %2
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_print(ptr noundef %0) local_unnamed_addr #6 {
  %2 = icmp eq ptr %0, null
  br i1 %2, label %5, label %3

3:                                                ; preds = %1
  %4 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.39, ptr noundef nonnull %0)
  br label %5

5:                                                ; preds = %3, %1
  ret void
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_println(ptr noundef readonly captures(address_is_null) %0) local_unnamed_addr #6 {
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
define internal void @qc_print_array_int(ptr noundef readonly captures(none) %0, i32 noundef %1) local_unnamed_addr #6 {
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
  %17 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, i32 noundef %16)
  %18 = icmp samesign ult i64 %14, %8
  br i1 %18, label %19, label %21

19:                                               ; preds = %13
  %20 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.43)
  br label %21

21:                                               ; preds = %19, %13
  %22 = add nuw nsw i64 %14, 1
  %23 = icmp eq i64 %22, %9
  br i1 %23, label %10, label %13, !llvm.loop !21
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_print_array_float(ptr noundef readonly captures(none) %0, i32 noundef %1) local_unnamed_addr #6 {
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
  %18 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.35, double noundef %17)
  %19 = icmp samesign ult i64 %14, %8
  br i1 %19, label %20, label %22

20:                                               ; preds = %13
  %21 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.43)
  br label %22

22:                                               ; preds = %20, %13
  %23 = add nuw nsw i64 %14, 1
  %24 = icmp eq i64 %23, %9
  br i1 %24, label %10, label %13, !llvm.loop !24
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_print_array_double(ptr noundef readonly captures(none) %0, i32 noundef %1) local_unnamed_addr #6 {
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
  %17 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.35, double noundef %16)
  %18 = icmp samesign ult i64 %14, %8
  br i1 %18, label %19, label %21

19:                                               ; preds = %13
  %20 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.43)
  br label %21

21:                                               ; preds = %19, %13
  %22 = add nuw nsw i64 %14, 1
  %23 = icmp eq i64 %22, %9
  br i1 %23, label %10, label %13, !llvm.loop !27
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_print_array_string(ptr noundef readonly captures(none) %0, i32 noundef %1) local_unnamed_addr #6 {
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
  %17 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.45, ptr noundef %16)
  %18 = icmp samesign ult i64 %14, %8
  br i1 %18, label %19, label %21

19:                                               ; preds = %13
  %20 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.43)
  br label %21

21:                                               ; preds = %19, %13
  %22 = add nuw nsw i64 %14, 1
  %23 = icmp eq i64 %22, %9
  br i1 %23, label %10, label %13, !llvm.loop !30
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_print_array_char(ptr noundef readonly captures(none) %0, i32 noundef %1) local_unnamed_addr #6 {
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
  %18 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.46, i32 noundef %17)
  %19 = icmp samesign ult i64 %14, %8
  br i1 %19, label %20, label %22

20:                                               ; preds = %13
  %21 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.43)
  br label %22

22:                                               ; preds = %20, %13
  %23 = add nuw nsw i64 %14, 1
  %24 = icmp eq i64 %23, %9
  br i1 %24, label %10, label %13, !llvm.loop !31
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_print_array_bool(ptr noundef readonly captures(none) %0, i32 noundef %1) local_unnamed_addr #6 {
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
  %18 = select i1 %17, ptr @.str.24, ptr @.str.25
  %19 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.39, ptr noundef nonnull %18)
  %20 = icmp samesign ult i64 %14, %8
  br i1 %20, label %21, label %23

21:                                               ; preds = %13
  %22 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.43)
  br label %23

23:                                               ; preds = %21, %13
  %24 = add nuw nsw i64 %14, 1
  %25 = icmp eq i64 %24, %9
  br i1 %25, label %10, label %13, !llvm.loop !36
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_print_array_qbool(ptr noundef readonly captures(none) %0, i32 noundef %1) local_unnamed_addr #6 {
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
  %24 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.43)
  br label %25

25:                                               ; preds = %23, %13
  %26 = add nuw nsw i64 %14, 1
  %27 = icmp eq i64 %26, %9
  br i1 %27, label %10, label %13, !llvm.loop !37
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define internal range(i32 1, 9) i32 @qc_sizeof_type(i32 noundef %0) local_unnamed_addr #10 {
  %2 = add i32 %0, -2
  %3 = icmp ult i32 %2, 5
  br i1 %3, label %4, label %8

4:                                                ; preds = %1
  %5 = zext nneg i32 %2 to i64
  %6 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.qc_stringify_jagged_helper, i64 0, i64 %5
  %7 = load i32, ptr %6, align 4
  br label %8

8:                                                ; preds = %4, %1
  %9 = phi i32 [ %7, %4 ], [ 4, %1 ]
  ret i32 %9
}

; Function Attrs: mustprogress nounwind uwtable
define internal noundef ptr @qc_array_to_string_recursive(ptr noundef readonly captures(none) %0, i32 noundef %1, i32 noundef %2, ptr noundef readonly captures(none) %3) local_unnamed_addr #17 {
  %5 = alloca [256 x i8], align 16
  %6 = icmp eq i32 %2, 0
  br i1 %6, label %7, label %45

7:                                                ; preds = %4
  call void @llvm.lifetime.start.p0(i64 256, ptr nonnull %5) #35
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
  %10 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 256, ptr noundef nonnull @.str.34, i32 noundef %9) #35
  br label %40

11:                                               ; preds = %7
  %12 = load float, ptr %0, align 4, !tbaa !22
  %13 = fpext float %12 to double
  %14 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 256, ptr noundef nonnull @.str.35, double noundef %13) #35
  br label %40

15:                                               ; preds = %7
  %16 = load double, ptr %0, align 8, !tbaa !25
  %17 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 256, ptr noundef nonnull @.str.35, double noundef %16) #35
  br label %40

18:                                               ; preds = %7
  %19 = load i8, ptr %0, align 1, !tbaa !7
  %20 = sext i8 %19 to i32
  %21 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 256, ptr noundef nonnull @.str.46, i32 noundef %20) #35
  br label %40

22:                                               ; preds = %7
  %23 = load i8, ptr %0, align 1, !tbaa !32, !range !34, !noundef !35
  %24 = trunc nuw i8 %23 to i1
  %25 = select i1 %24, ptr @.str.24, ptr @.str.25
  %26 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 256, ptr noundef nonnull @.str.39, ptr noundef nonnull %25) #35
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
  %32 = select i1 %31, ptr @.str.28, ptr @.str.29
  br label %34

33:                                               ; preds = %27
  br label %34

34:                                               ; preds = %33, %30, %27
  %35 = phi ptr [ @.str.26, %27 ], [ %32, %30 ], [ @.str.27, %33 ]
  %36 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 256, ptr noundef nonnull @.str.39, ptr noundef nonnull %35) #35
  br label %40

37:                                               ; preds = %7
  %38 = load ptr, ptr %0, align 8, !tbaa !28
  %39 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %5, i64 noundef 256, ptr noundef nonnull @.str.45, ptr noundef %38) #35
  br label %40

40:                                               ; preds = %37, %34, %22, %18, %15, %11, %8, %7
  %41 = call i64 @strlen(ptr noundef nonnull dereferenceable(1) %5) #38
  %42 = add i64 %41, 1
  %43 = tail call noalias ptr @malloc(i64 noundef %42) #34
  %44 = call ptr @strcpy(ptr noundef nonnull dereferenceable(1) %43, ptr noundef nonnull dereferenceable(1) %5) #35
  call void @llvm.lifetime.end.p0(i64 256, ptr nonnull %5) #35
  br label %157

45:                                               ; preds = %4
  %46 = add i32 %1, -2
  %47 = icmp ult i32 %46, 5
  br i1 %47, label %48, label %52

48:                                               ; preds = %45
  %49 = zext nneg i32 %46 to i64
  %50 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.qc_stringify_jagged_helper, i64 0, i64 %49
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
  %88 = tail call noalias ptr @malloc(i64 noundef %87) #34
  %89 = icmp sgt i32 %85, 0
  br i1 %89, label %93, label %90

90:                                               ; preds = %83
  %91 = tail call noalias dereferenceable_or_null(3) ptr @malloc(i64 noundef 3) #34
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
  %109 = tail call noalias ptr @malloc(i64 noundef %107) #34
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
  %118 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %116) #38
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
  tail call void @free(ptr noundef %88) #35
  br label %157

134:                                              ; preds = %151, %105
  %135 = phi i64 [ %154, %151 ], [ 0, %105 ]
  %136 = phi ptr [ %153, %151 ], [ %110, %105 ]
  %137 = getelementptr inbounds nuw ptr, ptr %88, i64 %135
  %138 = load ptr, ptr %137, align 8, !tbaa !28
  %139 = tail call ptr @strcpy(ptr noundef nonnull dereferenceable(1) %136, ptr noundef nonnull dereferenceable(1) %138) #35
  %140 = load ptr, ptr %137, align 8, !tbaa !28
  %141 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %140) #38
  %142 = getelementptr inbounds nuw i8, ptr %136, i64 %141
  tail call void @free(ptr noundef %140) #35
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
define internal void @qc_print_array_recursive(ptr noundef readonly captures(none) %0, i32 noundef %1, i32 noundef %2, ptr noundef readonly captures(none) %3) local_unnamed_addr #6 {
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
  %9 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, i32 noundef %8)
  br label %116

10:                                               ; preds = %6
  %11 = load float, ptr %0, align 4, !tbaa !22
  %12 = fpext float %11 to double
  %13 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.35, double noundef %12)
  br label %116

14:                                               ; preds = %6
  %15 = load double, ptr %0, align 8, !tbaa !25
  %16 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.35, double noundef %15)
  br label %116

17:                                               ; preds = %6
  %18 = load i8, ptr %0, align 1, !tbaa !7
  %19 = sext i8 %18 to i32
  %20 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.46, i32 noundef %19)
  br label %116

21:                                               ; preds = %6
  %22 = load i8, ptr %0, align 1, !tbaa !32, !range !34, !noundef !35
  %23 = trunc nuw i8 %22 to i1
  %24 = select i1 %23, ptr @.str.24, ptr @.str.25
  %25 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.39, ptr noundef nonnull %24)
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
  %30 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.26)
  br label %116

31:                                               ; preds = %26
  %32 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.27)
  br label %116

33:                                               ; preds = %26
  %34 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.28)
  br label %116

35:                                               ; preds = %26
  %36 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.29)
  br label %116

37:                                               ; preds = %26
  unreachable

38:                                               ; preds = %6
  %39 = load ptr, ptr %0, align 8, !tbaa !28
  %40 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.45, ptr noundef %39)
  br label %116

41:                                               ; preds = %4
  %42 = load ptr, ptr @stdout, align 8, !tbaa !10
  %43 = tail call noundef i32 @putc(i32 noundef 91, ptr noundef %42)
  %44 = add i32 %1, -2
  %45 = icmp ult i32 %44, 5
  br i1 %45, label %46, label %50

46:                                               ; preds = %41
  %47 = zext nneg i32 %44 to i64
  %48 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.qc_stringify_jagged_helper, i64 0, i64 %47
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
  %109 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.43)
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
define internal noalias noundef ptr @qc_create_jagged_array(i32 noundef %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #16 {
  %4 = tail call noalias dereferenceable_or_null(32) ptr @malloc(i64 noundef 32) #34
  %5 = sext i32 %0 to i64
  %6 = shl nsw i64 %5, 3
  %7 = tail call noalias ptr @malloc(i64 noundef %6) #34
  store ptr %7, ptr %4, align 8, !tbaa !47
  %8 = shl nsw i64 %5, 2
  %9 = tail call noalias ptr @malloc(i64 noundef %8) #34
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
define internal void @qc_set_jagged_element(ptr noundef readonly captures(none) %0, i32 noundef %1, ptr noundef %2, i32 noundef %3) local_unnamed_addr #29 {
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
define internal void @qc_free_jagged_array(ptr noundef captures(none) %0) local_unnamed_addr #17 {
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
  tail call void @free(ptr noundef %23) #35
  %24 = add nuw nsw i64 %20, 1
  %25 = load i32, ptr %5, align 8, !tbaa !52
  %26 = sext i32 %25 to i64
  %27 = icmp slt i64 %24, %26
  br i1 %27, label %19, label %28, !llvm.loop !57

28:                                               ; preds = %19, %10, %9, %8
  %29 = load ptr, ptr %0, align 8, !tbaa !47
  tail call void @free(ptr noundef %29) #35
  %30 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %31 = load ptr, ptr %30, align 8, !tbaa !51
  tail call void @free(ptr noundef %31) #35
  tail call void @free(ptr noundef nonnull %0) #35
  ret void
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_print_jagged_array_recursive(ptr noundef readonly captures(none) %0) local_unnamed_addr #6 {
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
  %44 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.qc_stringify_jagged_helper, i64 0, i64 %43
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
  %53 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, i32 noundef %52)
  br label %83

54:                                               ; preds = %46
  %55 = load float, ptr %50, align 4, !tbaa !22
  %56 = fpext float %55 to double
  %57 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.35, double noundef %56)
  br label %83

58:                                               ; preds = %46
  %59 = load double, ptr %50, align 8, !tbaa !25
  %60 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.35, double noundef %59)
  br label %83

61:                                               ; preds = %46
  %62 = load i8, ptr %50, align 1, !tbaa !7
  %63 = sext i8 %62 to i32
  %64 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.46, i32 noundef %63)
  br label %83

65:                                               ; preds = %46
  %66 = load i8, ptr %50, align 1, !tbaa !32, !range !34, !noundef !35
  %67 = trunc nuw i8 %66 to i1
  %68 = select i1 %67, ptr @.str.24, ptr @.str.25
  %69 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.39, ptr noundef nonnull %68)
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
  %75 = select i1 %74, ptr @.str.28, ptr @.str.29
  br label %77

76:                                               ; preds = %70
  br label %77

77:                                               ; preds = %76, %73, %70
  %78 = phi ptr [ @.str.26, %70 ], [ %75, %73 ], [ @.str.27, %76 ]
  %79 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.39, ptr noundef nonnull %78)
  br label %83

80:                                               ; preds = %46
  %81 = load ptr, ptr %50, align 8, !tbaa !28
  %82 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.45, ptr noundef %81)
  br label %83

83:                                               ; preds = %80, %77, %65, %61, %58, %54, %51, %46
  %84 = load ptr, ptr %9, align 8, !tbaa !51
  %85 = getelementptr inbounds nuw i32, ptr %84, i64 %15
  %86 = load i32, ptr %85, align 4, !tbaa !19
  %87 = add nsw i32 %86, -1
  %88 = icmp slt i32 %38, %87
  br i1 %88, label %89, label %94

89:                                               ; preds = %83
  %90 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.43)
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
  %99 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.47)
  br label %100

100:                                              ; preds = %98, %34, %18
  %101 = load i32, ptr %4, align 8, !tbaa !52
  %102 = add nsw i32 %101, -1
  %103 = sext i32 %102 to i64
  %104 = icmp slt i64 %15, %103
  br i1 %104, label %105, label %108

105:                                              ; preds = %100
  %106 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.43)
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
define internal ptr @qc_jagged_array_get(ptr noundef readonly captures(address_is_null) %0, ptr noundef readonly captures(none) %1, i32 noundef %2) local_unnamed_addr #30 {
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
  %48 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.qc_stringify_jagged_helper, i64 0, i64 %47
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
  %78 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.qc_stringify_jagged_helper, i64 0, i64 %77
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
define internal noalias noundef ptr @qc_create_leaf_row(i32 noundef %0, i32 noundef %1) local_unnamed_addr #0 {
  %3 = add i32 %1, -2
  %4 = icmp ult i32 %3, 5
  br i1 %4, label %5, label %9

5:                                                ; preds = %2
  %6 = zext nneg i32 %3 to i64
  %7 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.qc_stringify_jagged_helper, i64 0, i64 %6
  %8 = load i32, ptr %7, align 4
  br label %9

9:                                                ; preds = %5, %2
  %10 = phi i32 [ %8, %5 ], [ 4, %2 ]
  %11 = mul nsw i32 %10, %0
  %12 = sext i32 %11 to i64
  %13 = tail call noalias ptr @malloc(i64 noundef %12) #34
  ret ptr %13
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: readwrite) uwtable
define internal void @qc_set_leaf_element(ptr noundef writeonly captures(none) %0, i32 noundef %1, ptr noundef readonly captures(none) %2, i32 noundef %3) local_unnamed_addr #31 {
  %5 = add i32 %3, -2
  %6 = icmp ult i32 %5, 5
  br i1 %6, label %7, label %11

7:                                                ; preds = %4
  %8 = zext nneg i32 %5 to i64
  %9 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.qc_stringify_jagged_helper, i64 0, i64 %8
  %10 = load i32, ptr %9, align 4
  br label %11

11:                                               ; preds = %7, %4
  %12 = phi i32 [ %10, %7 ], [ 4, %4 ]
  %13 = add i32 %3, -2
  %14 = icmp ult i32 %13, 5
  br i1 %14, label %15, label %19

15:                                               ; preds = %11
  %16 = zext nneg i32 %13 to i64
  %17 = getelementptr inbounds nuw [5 x i64], ptr @switch.table.qc_set_leaf_element.52, i64 0, i64 %16
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
define internal void @qc_stringify_jagged_helper(ptr noundef readonly captures(none) %0, ptr noundef captures(none) %1, ptr noundef captures(none) %2, ptr noundef captures(none) %3, ptr noundef captures(none) %4) local_unnamed_addr #17 {
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
  tail call void @qc_stringify_jagged_helper(ptr noundef %34, ptr noundef nonnull %1, ptr noundef nonnull %2, ptr noundef %3, ptr noundef %4)
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
  %61 = getelementptr inbounds nuw [5 x i32], ptr @switch.table.qc_stringify_jagged_helper, i64 0, i64 %60
  %62 = load i32, ptr %61, align 4
  br label %63

63:                                               ; preds = %59, %54
  %64 = phi i32 [ %62, %59 ], [ 4, %54 ]
  %65 = mul nuw nsw i32 %64, %55
  %66 = zext nneg i32 %65 to i64
  %67 = getelementptr inbounds nuw i8, ptr %43, i64 %66
  call void @llvm.lifetime.start.p0(i64 64, ptr nonnull %6) #35
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
  %70 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %6, i64 noundef 64, ptr noundef nonnull @.str.34, i32 noundef %69) #35
  br label %100

71:                                               ; preds = %63
  %72 = load float, ptr %67, align 4, !tbaa !22
  %73 = fpext float %72 to double
  %74 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %6, i64 noundef 64, ptr noundef nonnull @.str.35, double noundef %73) #35
  br label %100

75:                                               ; preds = %63
  %76 = load double, ptr %67, align 8, !tbaa !25
  %77 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %6, i64 noundef 64, ptr noundef nonnull @.str.35, double noundef %76) #35
  br label %100

78:                                               ; preds = %63
  %79 = load i8, ptr %67, align 1, !tbaa !7
  %80 = sext i8 %79 to i32
  %81 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %6, i64 noundef 64, ptr noundef nonnull @.str.46, i32 noundef %80) #35
  br label %100

82:                                               ; preds = %63
  %83 = load i8, ptr %67, align 1, !tbaa !32, !range !34, !noundef !35
  %84 = trunc nuw i8 %83 to i1
  %85 = select i1 %84, ptr @.str.24, ptr @.str.25
  %86 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %6, i64 noundef 64, ptr noundef nonnull @.str.39, ptr noundef nonnull %85) #35
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
  %92 = select i1 %91, ptr @.str.28, ptr @.str.29
  br label %94

93:                                               ; preds = %87
  br label %94

94:                                               ; preds = %93, %90, %87
  %95 = phi ptr [ @.str.26, %87 ], [ %92, %90 ], [ @.str.27, %93 ]
  %96 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %6, i64 noundef 64, ptr noundef nonnull @.str.39, ptr noundef nonnull %95) #35
  br label %100

97:                                               ; preds = %63
  %98 = load ptr, ptr %67, align 8, !tbaa !28
  %99 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %6, i64 noundef 64, ptr noundef nonnull @.str.45, ptr noundef %98) #35
  br label %100

100:                                              ; preds = %97, %94, %82, %78, %75, %71, %68, %63
  %101 = call i64 @strlen(ptr noundef nonnull dereferenceable(1) %6) #38
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
  %116 = tail call ptr @realloc(ptr noundef %108, i64 noundef %115) #36
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
  %124 = call ptr @strcpy(ptr noundef nonnull dereferenceable(1) %123, ptr noundef nonnull dereferenceable(1) %6) #35
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
  call void @llvm.lifetime.end.p0(i64 64, ptr nonnull %6) #35
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
define internal ptr @qc_jagged_to_string(ptr noundef readonly captures(none) %0) local_unnamed_addr #17 {
  %2 = alloca i32, align 4
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca i32, align 4
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %2) #35
  store i32 1024, ptr %2, align 4, !tbaa !19
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %3) #35
  %6 = tail call noalias dereferenceable_or_null(1024) ptr @malloc(i64 noundef 1024) #34
  store ptr %6, ptr %3, align 8, !tbaa !28
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %4) #35
  store ptr %6, ptr %4, align 8, !tbaa !28
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %5) #35
  store i32 1024, ptr %5, align 4, !tbaa !19
  call void @qc_stringify_jagged_helper(ptr noundef %0, ptr noundef nonnull %4, ptr noundef nonnull %5, ptr noundef nonnull %2, ptr noundef nonnull %3)
  %7 = load ptr, ptr %4, align 8, !tbaa !28
  store i8 0, ptr %7, align 1, !tbaa !7
  %8 = load ptr, ptr %3, align 8, !tbaa !28
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %5) #35
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %4) #35
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %3) #35
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %2) #35
  ret ptr %8
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(write, argmem: none, inaccessiblemem: readwrite) uwtable
define internal noalias noundef ptr @qc_create_map(i32 noundef %0, i32 noundef %1) local_unnamed_addr #16 {
  %3 = tail call noalias dereferenceable_or_null(32) ptr @malloc(i64 noundef 32) #34
  %4 = getelementptr inbounds nuw i8, ptr %3, i64 20
  store i32 4, ptr %4, align 4, !tbaa !62
  %5 = getelementptr inbounds nuw i8, ptr %3, i64 16
  store i32 0, ptr %5, align 8, !tbaa !64
  %6 = getelementptr inbounds nuw i8, ptr %3, i64 24
  store i32 %0, ptr %6, align 8, !tbaa !65
  %7 = getelementptr inbounds nuw i8, ptr %3, i64 28
  store i32 %1, ptr %7, align 4, !tbaa !66
  %8 = tail call noalias dereferenceable_or_null(32) ptr @malloc(i64 noundef 32) #34
  store ptr %8, ptr %3, align 8, !tbaa !67
  %9 = tail call noalias dereferenceable_or_null(32) ptr @malloc(i64 noundef 32) #34
  %10 = getelementptr inbounds nuw i8, ptr %3, i64 8
  store ptr %9, ptr %10, align 8, !tbaa !68
  ret ptr %3
}

; Function Attrs: mustprogress nofree norecurse nounwind willreturn memory(argmem: read) uwtable
define internal zeroext i1 @qc_compare_keys(ptr noundef readonly captures(address_is_null) %0, ptr noundef readonly captures(address_is_null) %1, i32 noundef %2) local_unnamed_addr #14 {
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
  %33 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(1) %1) #38
  %34 = icmp eq i32 %33, 0
  br label %35

35:                                               ; preds = %32, %28, %24, %20, %16, %12, %8, %7, %3
  %36 = phi i1 [ %11, %8 ], [ %15, %12 ], [ %19, %16 ], [ %23, %20 ], [ %27, %24 ], [ %31, %28 ], [ %34, %32 ], [ false, %3 ], [ false, %7 ]
  ret i1 %36
}

; Function Attrs: mustprogress nounwind uwtable
define internal void @qc_map_set(ptr noundef captures(none) %0, ptr noundef %1, ptr noundef %2) local_unnamed_addr #17 {
  %4 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %5 = load i32, ptr %4, align 8, !tbaa !64
  %6 = icmp sgt i32 %5, 0
  br i1 %6, label %7, label %155

7:                                                ; preds = %3
  %8 = load ptr, ptr %0, align 8, !tbaa !67
  %9 = getelementptr inbounds nuw i8, ptr %0, i64 24
  %10 = load i32, ptr %9, align 8, !tbaa !65
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
  br i1 %39, label %155, label %28, !llvm.loop !69

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
  br i1 %51, label %155, label %40, !llvm.loop !69

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
  br i1 %63, label %155, label %52, !llvm.loop !69

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
  br i1 %75, label %155, label %64, !llvm.loop !69

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
  br i1 %87, label %155, label %76, !llvm.loop !69

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
  br i1 %99, label %155, label %88, !llvm.loop !69

100:                                              ; preds = %108, %14
  %101 = phi i64 [ 0, %14 ], [ %109, %108 ]
  %102 = getelementptr inbounds nuw ptr, ptr %8, i64 %101
  %103 = load ptr, ptr %102, align 8, !tbaa !55
  %104 = icmp eq ptr %103, null
  br i1 %104, label %108, label %105

105:                                              ; preds = %100
  %106 = tail call i32 @strcmp(ptr noundef nonnull readonly dereferenceable(1) %103, ptr noundef nonnull readonly dereferenceable(1) %1) #38
  %107 = icmp eq i32 %106, 0
  br i1 %107, label %116, label %108

108:                                              ; preds = %105, %100
  %109 = add nuw nsw i64 %101, 1
  %110 = icmp eq i64 %109, %15
  br i1 %110, label %155, label %100, !llvm.loop !69

111:                                              ; preds = %93, %81, %69, %57, %45, %33
  %112 = phi i64 [ %29, %33 ], [ %41, %45 ], [ %53, %57 ], [ %65, %69 ], [ %77, %81 ], [ %89, %93 ]
  %113 = getelementptr inbounds nuw i8, ptr %0, i64 28
  %114 = load i32, ptr %113, align 4, !tbaa !66
  %115 = icmp slt i32 %114, 6
  br i1 %115, label %120, label %143

116:                                              ; preds = %105
  %117 = getelementptr inbounds nuw i8, ptr %0, i64 28
  %118 = load i32, ptr %117, align 4, !tbaa !66
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
  %127 = getelementptr inbounds nuw [4 x i64], ptr @switch.table.qc_map_set.54, i64 0, i64 %126
  %128 = load i64, ptr %127, align 8
  br label %129

129:                                              ; preds = %125, %120
  %130 = phi i64 [ %128, %125 ], [ 4, %120 ]
  %131 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %132 = load ptr, ptr %131, align 8, !tbaa !68
  %133 = getelementptr inbounds nuw ptr, ptr %132, i64 %121
  %134 = load ptr, ptr %133, align 8, !tbaa !55
  %135 = icmp eq ptr %134, null
  br i1 %135, label %136, label %141

136:                                              ; preds = %129
  %137 = tail call noalias ptr @malloc(i64 noundef %130) #34
  store ptr %137, ptr %133, align 8, !tbaa !55
  %138 = load ptr, ptr %131, align 8, !tbaa !68
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
  %149 = tail call noalias ptr @strdup(ptr noundef nonnull %1) #35
  %150 = getelementptr inbounds nuw ptr, ptr %8, i64 %148
  store ptr %149, ptr %150, align 8, !tbaa !55
  br label %219

151:                                              ; preds = %143
  %152 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %153 = load ptr, ptr %152, align 8, !tbaa !68
  %154 = getelementptr inbounds nuw ptr, ptr %153, i64 %112
  store ptr %2, ptr %154, align 8, !tbaa !55
  br label %219

155:                                              ; preds = %108, %97, %85, %73, %61, %49, %37, %13, %7, %3
  %156 = getelementptr inbounds nuw i8, ptr %0, i64 20
  %157 = load i32, ptr %156, align 4, !tbaa !62
  %158 = icmp slt i32 %5, %157
  br i1 %158, label %171, label %159

159:                                              ; preds = %155
  %160 = shl nsw i32 %157, 1
  store i32 %160, ptr %156, align 4, !tbaa !62
  %161 = load ptr, ptr %0, align 8, !tbaa !67
  %162 = sext i32 %160 to i64
  %163 = shl nsw i64 %162, 3
  %164 = tail call ptr @realloc(ptr noundef %161, i64 noundef %163) #36
  store ptr %164, ptr %0, align 8, !tbaa !67
  %165 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %166 = load ptr, ptr %165, align 8, !tbaa !68
  %167 = load i32, ptr %156, align 4, !tbaa !62
  %168 = sext i32 %167 to i64
  %169 = shl nsw i64 %168, 3
  %170 = tail call ptr @realloc(ptr noundef %166, i64 noundef %169) #36
  store ptr %170, ptr %165, align 8, !tbaa !68
  br label %171

171:                                              ; preds = %159, %155
  %172 = getelementptr inbounds nuw i8, ptr %0, i64 24
  %173 = load i32, ptr %172, align 8, !tbaa !65
  %174 = icmp slt i32 %173, 6
  br i1 %174, label %175, label %185

175:                                              ; preds = %171
  %176 = add i32 %173, -2
  %177 = icmp ult i32 %176, 4
  br i1 %177, label %178, label %182

178:                                              ; preds = %175
  %179 = zext nneg i32 %176 to i64
  %180 = getelementptr inbounds nuw [4 x i64], ptr @switch.table.qc_map_set.54, i64 0, i64 %179
  %181 = load i64, ptr %180, align 8
  br label %182

182:                                              ; preds = %178, %175
  %183 = phi i64 [ %181, %178 ], [ 4, %175 ]
  %184 = tail call noalias ptr @malloc(i64 noundef %183) #34
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %184, ptr noundef nonnull align 1 dereferenceable(1) %1, i64 %183, i1 false)
  br label %189

185:                                              ; preds = %171
  %186 = icmp eq i32 %173, 6
  br i1 %186, label %187, label %189

187:                                              ; preds = %185
  %188 = tail call noalias ptr @strdup(ptr noundef %1) #35
  br label %189

189:                                              ; preds = %187, %185, %182
  %190 = phi ptr [ %188, %187 ], [ %184, %182 ], [ %1, %185 ]
  %191 = load ptr, ptr %0, align 8, !tbaa !67
  %192 = load i32, ptr %4, align 8, !tbaa !64
  %193 = sext i32 %192 to i64
  %194 = getelementptr inbounds ptr, ptr %191, i64 %193
  store ptr %190, ptr %194, align 8, !tbaa !55
  %195 = getelementptr inbounds nuw i8, ptr %0, i64 28
  %196 = load i32, ptr %195, align 4, !tbaa !66
  %197 = icmp slt i32 %196, 6
  br i1 %197, label %198, label %208

198:                                              ; preds = %189
  %199 = add i32 %196, -2
  %200 = icmp ult i32 %199, 4
  br i1 %200, label %201, label %205

201:                                              ; preds = %198
  %202 = zext nneg i32 %199 to i64
  %203 = getelementptr inbounds nuw [4 x i64], ptr @switch.table.qc_map_set.54, i64 0, i64 %202
  %204 = load i64, ptr %203, align 8
  br label %205

205:                                              ; preds = %201, %198
  %206 = phi i64 [ %204, %201 ], [ 4, %198 ]
  %207 = tail call noalias ptr @malloc(i64 noundef %206) #34
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 1 dereferenceable(1) %207, ptr noundef nonnull align 1 dereferenceable(1) %2, i64 %206, i1 false)
  br label %212

208:                                              ; preds = %189
  %209 = icmp eq i32 %196, 6
  br i1 %209, label %210, label %212

210:                                              ; preds = %208
  %211 = tail call noalias ptr @strdup(ptr noundef %2) #35
  br label %212

212:                                              ; preds = %210, %208, %205
  %213 = phi ptr [ %211, %210 ], [ %207, %205 ], [ %2, %208 ]
  %214 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %215 = load ptr, ptr %214, align 8, !tbaa !68
  %216 = sext i32 %192 to i64
  %217 = getelementptr inbounds ptr, ptr %215, i64 %216
  store ptr %213, ptr %217, align 8, !tbaa !55
  %218 = add nsw i32 %192, 1
  store i32 %218, ptr %4, align 8, !tbaa !64
  br label %219

219:                                              ; preds = %212, %151, %147, %141
  ret void
}

; Function Attrs: mustprogress nofree norecurse nounwind willreturn memory(read, inaccessiblemem: none) uwtable
define internal ptr @qc_map_get(ptr noundef readonly captures(none) %0, ptr noundef readonly captures(address_is_null) %1) local_unnamed_addr #32 {
  %3 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %4 = load i32, ptr %3, align 8, !tbaa !64
  %5 = icmp sgt i32 %4, 0
  br i1 %5, label %6, label %54

6:                                                ; preds = %2
  %7 = load ptr, ptr %0, align 8, !tbaa !67
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
  %18 = load i32, ptr %9, align 8, !tbaa !65
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
  %44 = tail call i32 @strcmp(ptr noundef nonnull readonly dereferenceable(1) %15, ptr noundef nonnull readonly dereferenceable(1) %1) #38
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %46, label %51

46:                                               ; preds = %43, %39, %35, %31, %27, %23, %19
  %47 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %48 = load ptr, ptr %47, align 8, !tbaa !68
  %49 = getelementptr inbounds nuw ptr, ptr %48, i64 %13
  %50 = load ptr, ptr %49, align 8, !tbaa !55
  br label %54

51:                                               ; preds = %43, %39, %35, %31, %27, %23, %19, %17, %12
  %52 = add nuw nsw i64 %13, 1
  %53 = icmp eq i64 %52, %11
  br i1 %53, label %54, label %12, !llvm.loop !70

54:                                               ; preds = %51, %46, %6, %2
  %55 = phi ptr [ %50, %46 ], [ null, %2 ], [ null, %6 ], [ null, %51 ]
  ret ptr %55
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_print_map(ptr noundef readonly captures(none) %0) local_unnamed_addr #6 {
  %2 = load ptr, ptr @stdout, align 8, !tbaa !10
  %3 = tail call noundef i32 @putc(i32 noundef 123, ptr noundef %2)
  %4 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %5 = load i32, ptr %4, align 8, !tbaa !64
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
  %16 = load i32, ptr %8, align 8, !tbaa !65
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
  %18 = load ptr, ptr %0, align 8, !tbaa !67
  %19 = getelementptr inbounds nuw ptr, ptr %18, i64 %15
  %20 = load ptr, ptr %19, align 8, !tbaa !55
  %21 = load i32, ptr %20, align 4, !tbaa !19
  %22 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, i32 noundef %21)
  br label %69

23:                                               ; preds = %14
  %24 = load ptr, ptr %0, align 8, !tbaa !67
  %25 = getelementptr inbounds nuw ptr, ptr %24, i64 %15
  %26 = load ptr, ptr %25, align 8, !tbaa !55
  %27 = load float, ptr %26, align 4, !tbaa !22
  %28 = fpext float %27 to double
  %29 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.35, double noundef %28)
  br label %69

30:                                               ; preds = %14
  %31 = load ptr, ptr %0, align 8, !tbaa !67
  %32 = getelementptr inbounds nuw ptr, ptr %31, i64 %15
  %33 = load ptr, ptr %32, align 8, !tbaa !55
  %34 = load double, ptr %33, align 8, !tbaa !25
  %35 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.35, double noundef %34)
  br label %69

36:                                               ; preds = %14
  %37 = load ptr, ptr %0, align 8, !tbaa !67
  %38 = getelementptr inbounds nuw ptr, ptr %37, i64 %15
  %39 = load ptr, ptr %38, align 8, !tbaa !55
  %40 = load i8, ptr %39, align 1, !tbaa !7
  %41 = sext i8 %40 to i32
  %42 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.46, i32 noundef %41)
  br label %69

43:                                               ; preds = %14
  %44 = load ptr, ptr %0, align 8, !tbaa !67
  %45 = getelementptr inbounds nuw ptr, ptr %44, i64 %15
  %46 = load ptr, ptr %45, align 8, !tbaa !55
  %47 = load i8, ptr %46, align 1, !tbaa !32, !range !34, !noundef !35
  %48 = trunc nuw i8 %47 to i1
  %49 = select i1 %48, ptr @.str.24, ptr @.str.25
  %50 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.39, ptr noundef nonnull %49)
  br label %69

51:                                               ; preds = %14
  %52 = load ptr, ptr %0, align 8, !tbaa !67
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
  %59 = select i1 %58, ptr @.str.28, ptr @.str.29
  br label %61

60:                                               ; preds = %51
  br label %61

61:                                               ; preds = %60, %57, %51
  %62 = phi ptr [ @.str.26, %51 ], [ %59, %57 ], [ @.str.27, %60 ]
  %63 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.39, ptr noundef nonnull %62)
  br label %69

64:                                               ; preds = %14
  %65 = load ptr, ptr %0, align 8, !tbaa !67
  %66 = getelementptr inbounds nuw ptr, ptr %65, i64 %15
  %67 = load ptr, ptr %66, align 8, !tbaa !55
  %68 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.45, ptr noundef %67)
  br label %69

69:                                               ; preds = %64, %61, %43, %36, %30, %23, %17, %14
  %70 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.49)
  %71 = load i32, ptr %9, align 4, !tbaa !66
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
  %73 = load ptr, ptr %10, align 8, !tbaa !68
  %74 = getelementptr inbounds nuw ptr, ptr %73, i64 %15
  %75 = load ptr, ptr %74, align 8, !tbaa !55
  %76 = load i32, ptr %75, align 4, !tbaa !19
  %77 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.34, i32 noundef %76)
  br label %124

78:                                               ; preds = %69
  %79 = load ptr, ptr %10, align 8, !tbaa !68
  %80 = getelementptr inbounds nuw ptr, ptr %79, i64 %15
  %81 = load ptr, ptr %80, align 8, !tbaa !55
  %82 = load float, ptr %81, align 4, !tbaa !22
  %83 = fpext float %82 to double
  %84 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.35, double noundef %83)
  br label %124

85:                                               ; preds = %69
  %86 = load ptr, ptr %10, align 8, !tbaa !68
  %87 = getelementptr inbounds nuw ptr, ptr %86, i64 %15
  %88 = load ptr, ptr %87, align 8, !tbaa !55
  %89 = load double, ptr %88, align 8, !tbaa !25
  %90 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.35, double noundef %89)
  br label %124

91:                                               ; preds = %69
  %92 = load ptr, ptr %10, align 8, !tbaa !68
  %93 = getelementptr inbounds nuw ptr, ptr %92, i64 %15
  %94 = load ptr, ptr %93, align 8, !tbaa !55
  %95 = load i8, ptr %94, align 1, !tbaa !7
  %96 = sext i8 %95 to i32
  %97 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.46, i32 noundef %96)
  br label %124

98:                                               ; preds = %69
  %99 = load ptr, ptr %10, align 8, !tbaa !68
  %100 = getelementptr inbounds nuw ptr, ptr %99, i64 %15
  %101 = load ptr, ptr %100, align 8, !tbaa !55
  %102 = load i8, ptr %101, align 1, !tbaa !32, !range !34, !noundef !35
  %103 = trunc nuw i8 %102 to i1
  %104 = select i1 %103, ptr @.str.24, ptr @.str.25
  %105 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.39, ptr noundef nonnull %104)
  br label %124

106:                                              ; preds = %69
  %107 = load ptr, ptr %10, align 8, !tbaa !68
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
  %114 = select i1 %113, ptr @.str.28, ptr @.str.29
  br label %116

115:                                              ; preds = %106
  br label %116

116:                                              ; preds = %115, %112, %106
  %117 = phi ptr [ @.str.26, %106 ], [ %114, %112 ], [ @.str.27, %115 ]
  %118 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.39, ptr noundef nonnull %117)
  br label %124

119:                                              ; preds = %69
  %120 = load ptr, ptr %10, align 8, !tbaa !68
  %121 = getelementptr inbounds nuw ptr, ptr %120, i64 %15
  %122 = load ptr, ptr %121, align 8, !tbaa !55
  %123 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.45, ptr noundef %122)
  br label %124

124:                                              ; preds = %119, %116, %98, %91, %85, %78, %72, %69
  %125 = load i32, ptr %4, align 8, !tbaa !64
  %126 = add nsw i32 %125, -1
  %127 = sext i32 %126 to i64
  %128 = icmp slt i64 %15, %127
  br i1 %128, label %129, label %132

129:                                              ; preds = %124
  %130 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.43)
  %131 = load i32, ptr %4, align 8, !tbaa !64
  br label %132

132:                                              ; preds = %129, %124
  %133 = phi i32 [ %125, %124 ], [ %131, %129 ]
  %134 = add nuw nsw i64 %15, 1
  %135 = sext i32 %133 to i64
  %136 = icmp slt i64 %134, %135
  br i1 %136, label %14, label %11, !llvm.loop !71
}

; Function Attrs: mustprogress nounwind uwtable
define internal ptr @qc_map_to_string(ptr noundef readonly captures(none) %0) local_unnamed_addr #17 {
  %2 = alloca [128 x i8], align 16
  %3 = tail call noalias dereferenceable_or_null(256) ptr @malloc(i64 noundef 256) #34
  %4 = getelementptr inbounds nuw i8, ptr %3, i64 1
  store i8 123, ptr %3, align 1, !tbaa !7
  %5 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %6 = load i32, ptr %5, align 8, !tbaa !64
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
  call void @llvm.lifetime.start.p0(i64 128, ptr nonnull %2) #35
  %22 = load i32, ptr %9, align 8, !tbaa !65
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
  %24 = load ptr, ptr %0, align 8, !tbaa !67
  %25 = getelementptr inbounds nuw ptr, ptr %24, i64 %17
  %26 = load ptr, ptr %25, align 8, !tbaa !55
  %27 = load i32, ptr %26, align 4, !tbaa !19
  %28 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.34, i32 noundef %27) #35
  br label %75

29:                                               ; preds = %16
  %30 = load ptr, ptr %0, align 8, !tbaa !67
  %31 = getelementptr inbounds nuw ptr, ptr %30, i64 %17
  %32 = load ptr, ptr %31, align 8, !tbaa !55
  %33 = load float, ptr %32, align 4, !tbaa !22
  %34 = fpext float %33 to double
  %35 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.35, double noundef %34) #35
  br label %75

36:                                               ; preds = %16
  %37 = load ptr, ptr %0, align 8, !tbaa !67
  %38 = getelementptr inbounds nuw ptr, ptr %37, i64 %17
  %39 = load ptr, ptr %38, align 8, !tbaa !55
  %40 = load double, ptr %39, align 8, !tbaa !25
  %41 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.35, double noundef %40) #35
  br label %75

42:                                               ; preds = %16
  %43 = load ptr, ptr %0, align 8, !tbaa !67
  %44 = getelementptr inbounds nuw ptr, ptr %43, i64 %17
  %45 = load ptr, ptr %44, align 8, !tbaa !55
  %46 = load i8, ptr %45, align 1, !tbaa !7
  %47 = sext i8 %46 to i32
  %48 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.46, i32 noundef %47) #35
  br label %75

49:                                               ; preds = %16
  %50 = load ptr, ptr %0, align 8, !tbaa !67
  %51 = getelementptr inbounds nuw ptr, ptr %50, i64 %17
  %52 = load ptr, ptr %51, align 8, !tbaa !55
  %53 = load i8, ptr %52, align 1, !tbaa !32, !range !34, !noundef !35
  %54 = trunc nuw i8 %53 to i1
  %55 = select i1 %54, ptr @.str.24, ptr @.str.25
  %56 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.39, ptr noundef nonnull %55) #35
  br label %75

57:                                               ; preds = %16
  %58 = load ptr, ptr %0, align 8, !tbaa !67
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
  %65 = select i1 %64, ptr @.str.28, ptr @.str.29
  br label %67

66:                                               ; preds = %57
  br label %67

67:                                               ; preds = %66, %63, %57
  %68 = phi ptr [ @.str.26, %57 ], [ %65, %63 ], [ @.str.27, %66 ]
  %69 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.39, ptr noundef nonnull %68) #35
  br label %75

70:                                               ; preds = %16
  %71 = load ptr, ptr %0, align 8, !tbaa !67
  %72 = getelementptr inbounds nuw ptr, ptr %71, i64 %17
  %73 = load ptr, ptr %72, align 8, !tbaa !55
  %74 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.45, ptr noundef %73) #35
  br label %75

75:                                               ; preds = %70, %67, %49, %42, %36, %29, %23, %16
  %76 = call i64 @strlen(ptr noundef nonnull dereferenceable(1) %2) #38
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
  %87 = tail call ptr @realloc(ptr noundef %19, i64 noundef %86) #36
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
  %97 = call ptr @strcpy(ptr noundef nonnull dereferenceable(1) %94, ptr noundef nonnull dereferenceable(1) %2) #35
  %98 = shl i64 %76, 32
  %99 = ashr exact i64 %98, 32
  %100 = getelementptr inbounds i8, ptr %94, i64 %99
  %101 = sub nsw i32 %93, %77
  %102 = getelementptr inbounds nuw i8, ptr %100, i64 1
  store i8 58, ptr %100, align 1, !tbaa !7
  %103 = getelementptr inbounds nuw i8, ptr %100, i64 2
  store i8 32, ptr %102, align 1, !tbaa !7
  %104 = add nsw i32 %101, -2
  %105 = load i32, ptr %10, align 4, !tbaa !66
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
  %107 = load ptr, ptr %11, align 8, !tbaa !68
  %108 = getelementptr inbounds nuw ptr, ptr %107, i64 %17
  %109 = load ptr, ptr %108, align 8, !tbaa !55
  %110 = load i32, ptr %109, align 4, !tbaa !19
  %111 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.34, i32 noundef %110) #35
  br label %158

112:                                              ; preds = %92
  %113 = load ptr, ptr %11, align 8, !tbaa !68
  %114 = getelementptr inbounds nuw ptr, ptr %113, i64 %17
  %115 = load ptr, ptr %114, align 8, !tbaa !55
  %116 = load float, ptr %115, align 4, !tbaa !22
  %117 = fpext float %116 to double
  %118 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.35, double noundef %117) #35
  br label %158

119:                                              ; preds = %92
  %120 = load ptr, ptr %11, align 8, !tbaa !68
  %121 = getelementptr inbounds nuw ptr, ptr %120, i64 %17
  %122 = load ptr, ptr %121, align 8, !tbaa !55
  %123 = load double, ptr %122, align 8, !tbaa !25
  %124 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.35, double noundef %123) #35
  br label %158

125:                                              ; preds = %92
  %126 = load ptr, ptr %11, align 8, !tbaa !68
  %127 = getelementptr inbounds nuw ptr, ptr %126, i64 %17
  %128 = load ptr, ptr %127, align 8, !tbaa !55
  %129 = load i8, ptr %128, align 1, !tbaa !7
  %130 = sext i8 %129 to i32
  %131 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.46, i32 noundef %130) #35
  br label %158

132:                                              ; preds = %92
  %133 = load ptr, ptr %11, align 8, !tbaa !68
  %134 = getelementptr inbounds nuw ptr, ptr %133, i64 %17
  %135 = load ptr, ptr %134, align 8, !tbaa !55
  %136 = load i8, ptr %135, align 1, !tbaa !32, !range !34, !noundef !35
  %137 = trunc nuw i8 %136 to i1
  %138 = select i1 %137, ptr @.str.24, ptr @.str.25
  %139 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.39, ptr noundef nonnull %138) #35
  br label %158

140:                                              ; preds = %92
  %141 = load ptr, ptr %11, align 8, !tbaa !68
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
  %148 = select i1 %147, ptr @.str.28, ptr @.str.29
  br label %150

149:                                              ; preds = %140
  br label %150

150:                                              ; preds = %149, %146, %140
  %151 = phi ptr [ @.str.26, %140 ], [ %148, %146 ], [ @.str.27, %149 ]
  %152 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.39, ptr noundef nonnull %151) #35
  br label %158

153:                                              ; preds = %92
  %154 = load ptr, ptr %11, align 8, !tbaa !68
  %155 = getelementptr inbounds nuw ptr, ptr %154, i64 %17
  %156 = load ptr, ptr %155, align 8, !tbaa !55
  %157 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 128, ptr noundef nonnull @.str.45, ptr noundef %156) #35
  br label %158

158:                                              ; preds = %153, %150, %132, %125, %119, %112, %106, %92
  %159 = call i64 @strlen(ptr noundef nonnull dereferenceable(1) %2) #38
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
  %170 = tail call ptr @realloc(ptr noundef %95, i64 noundef %169) #36
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
  %180 = call ptr @strcpy(ptr noundef nonnull dereferenceable(1) %177, ptr noundef nonnull dereferenceable(1) %2) #35
  %181 = shl i64 %159, 32
  %182 = ashr exact i64 %181, 32
  %183 = getelementptr inbounds i8, ptr %177, i64 %182
  %184 = sub nsw i32 %176, %160
  %185 = load i32, ptr %5, align 8, !tbaa !64
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
  %193 = load i32, ptr %5, align 8, !tbaa !64
  br label %194

194:                                              ; preds = %189, %175
  %195 = phi i32 [ %193, %189 ], [ %185, %175 ]
  %196 = phi i32 [ %192, %189 ], [ %184, %175 ]
  %197 = phi ptr [ %191, %189 ], [ %183, %175 ]
  call void @llvm.lifetime.end.p0(i64 128, ptr nonnull %2) #35
  %198 = add nuw nsw i64 %17, 1
  %199 = sext i32 %195 to i64
  %200 = icmp slt i64 %198, %199
  br i1 %200, label %16, label %12, !llvm.loop !72
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
define internal i32 @qc_map_size(ptr noundef readonly captures(none) %0) local_unnamed_addr #26 {
  %2 = getelementptr inbounds nuw i8, ptr %0, i64 16
  %3 = load i32, ptr %2, align 8, !tbaa !64
  ret i32 %3
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal noalias noundef ptr @qc_fopen(ptr noundef readonly captures(none) %0, ptr noundef readonly captures(none) %1) local_unnamed_addr #6 {
  %3 = tail call noalias ptr @fopen(ptr noundef %0, ptr noundef %1)
  ret ptr %3
}

; Function Attrs: nofree nounwind
declare noalias noundef ptr @fopen(ptr noundef readonly captures(none), ptr noundef readonly captures(none)) local_unnamed_addr #8

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_fclose(ptr noundef captures(address_is_null) %0) local_unnamed_addr #6 {
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
define internal noalias ptr @qc_fread(ptr noundef captures(address_is_null) %0) local_unnamed_addr #6 {
  %2 = alloca [1024 x i8], align 16
  %3 = icmp eq ptr %0, null
  br i1 %3, label %4, label %6

4:                                                ; preds = %1
  %5 = tail call noalias dereferenceable_or_null(1) ptr @strdup(ptr noundef nonnull @.str.2) #35
  br label %21

6:                                                ; preds = %1
  call void @llvm.lifetime.start.p0(i64 1024, ptr nonnull %2) #35
  %7 = call ptr @fgets(ptr noundef nonnull %2, i32 noundef 1024, ptr noundef nonnull %0)
  %8 = icmp eq ptr %7, null
  br i1 %8, label %18, label %9

9:                                                ; preds = %6
  %10 = call i64 @strlen(ptr noundef nonnull dereferenceable(1) %2) #38
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
  %20 = call noalias ptr @strdup(ptr noundef nonnull %19) #35
  call void @llvm.lifetime.end.p0(i64 1024, ptr nonnull %2) #35
  br label %21

21:                                               ; preds = %18, %4
  %22 = phi ptr [ %20, %18 ], [ %5, %4 ]
  ret ptr %22
}

; Function Attrs: nofree nounwind
declare noundef ptr @fgets(ptr noundef writeonly, i32 noundef, ptr noundef captures(none)) local_unnamed_addr #8

; Function Attrs: mustprogress nofree nounwind uwtable
define internal void @qc_fwrite(ptr noundef captures(address_is_null) %0, ptr noundef readonly captures(address_is_null) %1) local_unnamed_addr #6 {
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
define internal zeroext i1 @qc_variadic_is_empty(ptr noundef readonly captures(none) %0) local_unnamed_addr #26 {
  %2 = getelementptr inbounds nuw i8, ptr %0, i64 12
  %3 = load i32, ptr %2, align 4, !tbaa !73
  %4 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %5 = load i32, ptr %4, align 8, !tbaa !75
  %6 = icmp sge i32 %3, %5
  ret i1 %6
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(read, argmem: readwrite, inaccessiblemem: none) uwtable
define internal ptr @qc_variadic_next(ptr noundef captures(none) %0) local_unnamed_addr #33 {
  %2 = getelementptr inbounds nuw i8, ptr %0, i64 12
  %3 = load i32, ptr %2, align 4, !tbaa !73
  %4 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %5 = load i32, ptr %4, align 8, !tbaa !75
  %6 = icmp slt i32 %3, %5
  br i1 %6, label %7, label %13

7:                                                ; preds = %1
  %8 = load ptr, ptr %0, align 8, !tbaa !76
  %9 = sext i32 %3 to i64
  %10 = getelementptr inbounds ptr, ptr %8, i64 %9
  %11 = load ptr, ptr %10, align 8, !tbaa !55
  %12 = add nsw i32 %3, 1
  store i32 %12, ptr %2, align 4, !tbaa !73
  br label %13

13:                                               ; preds = %7, %1
  %14 = phi ptr [ %11, %7 ], [ null, %1 ]
  ret ptr %14
}

define internal i32 @__user_entry() {
entry:
  %elem = alloca i32, align 4
  %__foreach_i_elem = alloca i32, align 4
  %__iter_elem = alloca %"ArrayIterator<int>", align 8
  %x = alloca %"Array<int,2>", align 8
  %0 = alloca [2 x i32], align 4
  store [2 x i32] [i32 1, i32 2], ptr %0, align 4
  %decayptr = getelementptr inbounds [2 x i32], ptr %0, i32 0, i32 0
  %"operator[]=_result" = call void @"Array<int,2>_operator[]="(ptr %x, ptr %decayptr, i32 2)
  %vptr_field = getelementptr inbounds nuw %"Array<int,2>", ptr %x, i32 0, i32 0
  store ptr @"Array<int,2>_vtable", ptr %vptr_field, align 8
  %x1 = load %"Array<int,2>", ptr %x, align 8
  %_begin_result = call %"ArrayIterator<int>" @"Array<int,2>__begin"(%"Array<int,2>" %x1)
  store %"ArrayIterator<int>" %_begin_result, ptr %__iter_elem, align 8
  store i32 0, ptr %__foreach_i_elem, align 4
  br label %foreach.cond

foreach.cond:                                     ; preds = %foreach.body, %entry
  %_atEnd_result = call i1 @"ArrayIterator<int>__atEnd"(ptr %__iter_elem)
  br i1 %_atEnd_result, label %foreach.end, label %foreach.body

foreach.body:                                     ; preds = %foreach.cond
  %1 = load %"ArrayIterator<int>", ptr %__iter_elem, align 8
  %_next_result = call i32 @"ArrayIterator<int>__next"(ptr %__iter_elem)
  store i32 %_next_result, ptr %elem, align 4
  %elem2 = load i32, ptr %elem, align 4
  %2 = sext i32 %elem2 to i64
  call void @qc_print_string(ptr @0)
  %3 = call ptr @qc_fmt_int(i64 %2, i32 -1, i32 -1, i1 false)
  call void @qc_print_string(ptr %3)
  call void @qc_print_string(ptr @1)
  br label %foreach.cond

foreach.inc:                                      ; No predecessors!

foreach.end:                                      ; preds = %foreach.cond
  ret i32 0
}

define internal void @"Array<int,2>_Array"(ptr %0) {
entry:
  %1 = getelementptr inbounds nuw %"Array<int,2>", ptr %0, i32 0, i32 1
  store ptr null, ptr %1, align 8
  %2 = getelementptr inbounds nuw %"Array<int,2>", ptr %0, i32 0, i32 2
  store i32 0, ptr %2, align 4
  ret void
}

define internal void @"Array<int,2>_operator[]="(ptr %0, ptr %1, i32 %2) {
entry:
  %i = alloca i32, align 4
  %length = alloca i32, align 4
  %data = alloca ptr, align 8
  store ptr %1, ptr %data, align 8
  store i32 %2, ptr %length, align 4
  %length1 = load i32, ptr %length, align 4
  %icmpgt = icmp sgt i32 %length1, 2
  br i1 %icmpgt, label %then, label %else

then:                                             ; preds = %entry
  %length2 = load i32, ptr %length, align 4
  %3 = getelementptr inbounds nuw %"Array<int,2>", ptr %0, i32 0, i32 2
  store i32 %length2, ptr %3, align 4
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %4 = getelementptr inbounds nuw %"Array<int,2>", ptr %0, i32 0, i32 2
  %size = load i32, ptr %4, align 4
  %promote_int = sext i32 %size to i64
  %mul = mul i64 4, %promote_int
  %builtin_call = call ptr @qc_malloc(i64 %mul)
  %5 = getelementptr inbounds nuw %"Array<int,2>", ptr %0, i32 0, i32 1
  store ptr %builtin_call, ptr %5, align 8
  store i32 0, ptr %i, align 4
  br label %for.cond

else:                                             ; preds = %entry
  %6 = getelementptr inbounds nuw %"Array<int,2>", ptr %0, i32 0, i32 2
  store i32 2, ptr %6, align 4
  br label %ifcont

for.cond:                                         ; preds = %for.inc, %ifcont
  %i3 = load i32, ptr %i, align 4
  %7 = getelementptr inbounds nuw %"Array<int,2>", ptr %0, i32 0, i32 2
  %size4 = load i32, ptr %7, align 4
  %icmplt = icmp slt i32 %i3, %size4
  br i1 %icmplt, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %i5 = load i32, ptr %i, align 4
  %8 = getelementptr inbounds nuw %"Array<int,2>", ptr %0, i32 0, i32 1
  %data6 = load ptr, ptr %8, align 8
  %ptr_arr_asi = getelementptr i32, ptr %data6, i32 %i5
  %i7 = load i32, ptr %i, align 4
  %data8 = load ptr, ptr %data, align 8
  %ptr_arr_addr = getelementptr i32, ptr %data8, i32 %i7
  %ptr_arr_val = load i32, ptr %ptr_arr_addr, align 4
  store i32 %ptr_arr_val, ptr %ptr_arr_asi, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %i9 = load i32, ptr %i, align 4
  %i10 = load i32, ptr %i, align 4
  %inc_deref = load i32, ptr %i, align 4
  %inc = add i32 %inc_deref, 1
  store i32 %inc, ptr %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret void
}

define internal i32 @"Array<int,2>_operator[]"(ptr %0, i32 %1) {
entry:
  %index = alloca i32, align 4
  store i32 %1, ptr %index, align 4
  %index1 = load i32, ptr %index, align 4
  %2 = getelementptr inbounds nuw %"Array<int,2>", ptr %0, i32 0, i32 1
  %data = load ptr, ptr %2, align 8
  %ptr_arr_addr = getelementptr i32, ptr %data, i32 %index1
  %ptr_arr_val = load i32, ptr %ptr_arr_addr, align 4
  ret i32 %ptr_arr_val
}

define internal void @"ArrayIterator<int>_ArrayIterator"(ptr %0, ptr %1, i32 %2, i1 %3) {
entry:
  %is_end = alloca i1, align 1
  %size = alloca i32, align 4
  %data = alloca ptr, align 8
  store ptr %1, ptr %data, align 8
  store i32 %2, ptr %size, align 4
  store i1 %3, ptr %is_end, align 1
  %data1 = load ptr, ptr %data, align 8
  %4 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 1
  store ptr %data1, ptr %4, align 8
  %size2 = load i32, ptr %size, align 4
  %5 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 2
  store i32 %size2, ptr %5, align 4
  %size3 = load i32, ptr %size, align 4
  %sub = sub i32 %size3, 1
  %is_end4 = load i1, ptr %is_end, align 1
  %select_val = select i1 %is_end4, i32 %sub, i32 0
  %6 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 3
  store i32 %select_val, ptr %6, align 4
  ret void
}

define internal i1 @"ArrayIterator<int>__atEnd"(ptr %0) {
entry:
  %1 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 2
  %size = load i32, ptr %1, align 4
  %2 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 3
  %current_index = load i32, ptr %2, align 4
  %icmple = icmp sle i32 %size, %current_index
  ret i1 %icmple
}

define internal i32 @"ArrayIterator<int>__next"(ptr %0) {
entry:
  %vptr_field = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 0
  %vptr = load ptr, ptr %vptr_field, align 8
  %vtable_slot = getelementptr ptr, ptr %vptr, i32 1
  %fn_ptr = load ptr, ptr %vtable_slot, align 8
  %1 = call i1 %fn_ptr(ptr %0)
  %not = xor i1 %1, true
  br i1 %not, label %then, label %ifcont

then:                                             ; preds = %entry
  %2 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 3
  %current_index = load i32, ptr %2, align 4
  %3 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 3
  %current_index1 = load i32, ptr %3, align 4
  %current_index_ptr = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 3
  %inc_deref = load i32, ptr %current_index_ptr, align 4
  %inc = add i32 %inc_deref, 1
  store i32 %inc, ptr %current_index_ptr, align 4
  %4 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 1
  %data = load ptr, ptr %4, align 8
  %ptr_arr_addr = getelementptr i32, ptr %data, i32 %inc_deref
  %ptr_arr_val = load i32, ptr %ptr_arr_addr, align 4
  ret i32 %ptr_arr_val

ifcont:                                           ; preds = %entry
  %5 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 3
  %current_index2 = load i32, ptr %5, align 4
  %6 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 1
  %data3 = load ptr, ptr %6, align 8
  %ptr_arr_addr4 = getelementptr i32, ptr %data3, i32 %current_index2
  %ptr_arr_val5 = load i32, ptr %ptr_arr_addr4, align 4
  ret i32 %ptr_arr_val5
}

define internal i1 @"ArrayIterator<int>__atStart"(ptr %0) {
entry:
  %1 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 3
  %current_index = load i32, ptr %1, align 4
  %icmple = icmp sle i32 %current_index, 0
  ret i1 %icmple
}

define internal i32 @"ArrayIterator<int>__prev"(ptr %0) {
entry:
  %vptr_field = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 0
  %vptr = load ptr, ptr %vptr_field, align 8
  %vtable_slot = getelementptr ptr, ptr %vptr, i32 3
  %fn_ptr = load ptr, ptr %vtable_slot, align 8
  %1 = call i1 %fn_ptr(ptr %0)
  %not = xor i1 %1, true
  br i1 %not, label %then, label %ifcont

then:                                             ; preds = %entry
  %2 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 3
  %current_index = load i32, ptr %2, align 4
  %3 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 3
  %current_index1 = load i32, ptr %3, align 4
  %current_index_ptr = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 3
  %inc_deref = load i32, ptr %current_index_ptr, align 4
  %dec = sub i32 %inc_deref, 1
  store i32 %dec, ptr %current_index_ptr, align 4
  %4 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 1
  %data = load ptr, ptr %4, align 8
  %ptr_arr_addr = getelementptr i32, ptr %data, i32 %dec
  %ptr_arr_val = load i32, ptr %ptr_arr_addr, align 4
  ret i32 %ptr_arr_val

ifcont:                                           ; preds = %entry
  %5 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 3
  %current_index2 = load i32, ptr %5, align 4
  %6 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 1
  %data3 = load ptr, ptr %6, align 8
  %ptr_arr_addr4 = getelementptr i32, ptr %data3, i32 %current_index2
  %ptr_arr_val5 = load i32, ptr %ptr_arr_addr4, align 4
  ret i32 %ptr_arr_val5
}

define internal void @"ArrayIterator<int>__moveTo"(ptr %0, i32 %1) {
entry:
  %index = alloca i32, align 4
  store i32 %1, ptr %index, align 4
  %index1 = load i32, ptr %index, align 4
  %2 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 2
  %size = load i32, ptr %2, align 4
  %icmpge = icmp sge i32 %index1, %size
  br i1 %icmpge, label %then, label %elif.cond

then:                                             ; preds = %entry
  %assign_lhs_val = load i32, ptr %index, align 4
  %3 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 2
  %size2 = load i32, ptr %3, align 4
  %sub = sub i32 %size2, 1
  store i32 %sub, ptr %index, align 4
  br label %ifcont

ifcont:                                           ; preds = %elif.body, %elif.cond, %then
  %index5 = load i32, ptr %index, align 4
  %4 = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %0, i32 0, i32 3
  store i32 %index5, ptr %4, align 4
  ret void

elif.cond:                                        ; preds = %entry
  %index3 = load i32, ptr %index, align 4
  %icmplt = icmp slt i32 %index3, 0
  br i1 %icmplt, label %elif.body, label %ifcont

elif.body:                                        ; preds = %elif.cond
  %assign_lhs_val4 = load i32, ptr %index, align 4
  store i32 0, ptr %index, align 4
  br label %ifcont
}

define internal %"ArrayIterator<int>" @"Array<int,2>__begin"(ptr %0) {
entry:
  %"temp_ArrayIterator<int>" = alloca %"ArrayIterator<int>", align 8
  %1 = getelementptr inbounds nuw %"Array<int,2>", ptr %0, i32 0, i32 1
  %data = load ptr, ptr %1, align 8
  %2 = getelementptr inbounds nuw %"Array<int,2>", ptr %0, i32 0, i32 2
  %size = load i32, ptr %2, align 4
  call void @"ArrayIterator<int>_ArrayIterator"(ptr %"temp_ArrayIterator<int>", ptr %data, i32 %size, i1 false)
  %vptr_field = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %"temp_ArrayIterator<int>", i32 0, i32 0
  store ptr @"ArrayIterator<int>_vtable", ptr %vptr_field, align 8
  %"ArrayIterator<int>_inst" = load %"ArrayIterator<int>", ptr %"temp_ArrayIterator<int>", align 8
  ret %"ArrayIterator<int>" %"ArrayIterator<int>_inst"
}

define internal %"ArrayIterator<int>" @"Array<int,2>__end"(ptr %0) {
entry:
  %"temp_ArrayIterator<int>" = alloca %"ArrayIterator<int>", align 8
  %1 = getelementptr inbounds nuw %"Array<int,2>", ptr %0, i32 0, i32 1
  %data = load ptr, ptr %1, align 8
  %2 = getelementptr inbounds nuw %"Array<int,2>", ptr %0, i32 0, i32 2
  %size = load i32, ptr %2, align 4
  call void @"ArrayIterator<int>_ArrayIterator"(ptr %"temp_ArrayIterator<int>", ptr %data, i32 %size, i1 true)
  %vptr_field = getelementptr inbounds nuw %"ArrayIterator<int>", ptr %"temp_ArrayIterator<int>", i32 0, i32 0
  store ptr @"ArrayIterator<int>_vtable", ptr %vptr_field, align 8
  %"ArrayIterator<int>_inst" = load %"ArrayIterator<int>", ptr %"temp_ArrayIterator<int>", align 8
  ret %"ArrayIterator<int>" %"ArrayIterator<int>_inst"
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
attributes #32 = { mustprogress nofree norecurse nounwind willreturn memory(read, inaccessiblemem: none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #33 = { mustprogress nofree norecurse nosync nounwind willreturn memory(read, argmem: readwrite, inaccessiblemem: none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #34 = { nounwind allocsize(0) }
attributes #35 = { nounwind }
attributes #36 = { nounwind allocsize(1) }
attributes #37 = { nounwind allocsize(0,1) }
attributes #38 = { nounwind willreturn memory(read) }

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
!62 = !{!63, !20, i64 20}
!63 = !{!"_ZTS6qc_map", !49, i64 0, !49, i64 8, !20, i64 16, !20, i64 20, !20, i64 24, !20, i64 28}
!64 = !{!63, !20, i64 16}
!65 = !{!63, !20, i64 24}
!66 = !{!63, !20, i64 28}
!67 = !{!63, !49, i64 0}
!68 = !{!63, !49, i64 8}
!69 = distinct !{!69, !6}
!70 = distinct !{!70, !6}
!71 = distinct !{!71, !6}
!72 = distinct !{!72, !6}
!73 = !{!74, !20, i64 12}
!74 = !{!"_ZTS11qc_variadic", !49, i64 0, !20, i64 8, !20, i64 12}
!75 = !{!74, !20, i64 8}
!76 = !{!74, !49, i64 0}
