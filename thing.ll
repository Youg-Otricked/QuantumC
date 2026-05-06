; ModuleID = 'qc_module'
source_filename = "qc_module"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.1 = private constant [5 x i8] c"Luca\00"
@.str.2 = private constant [17 x i8] c"Hello, Compiler!\00"
@.str.3 = private constant [5 x i8] c"\F0\9F\94\A5\00"
@.str.4 = private constant [6 x i8] c"Hello\00"
@.str.5 = private constant [6 x i8] c"World\00"
@.str.6 = private constant [2 x i8] c"!\00"
@.str.7 = private constant [1 x i8] zeroinitializer
@.str.8 = private constant [14 x i8] c"She said \22Hi\22\00"
@.str.9 = private constant [81 x i8] c"C:\\Users\\Luca(JK its ~/C^4 becuase i dont use the disgusting windows powershell)\00"

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
  %7 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %4) #7
  %8 = tail call i64 @strlen(ptr noundef nonnull dereferenceable(1) %6) #7
  %9 = add i64 %8, %7
  %10 = add i64 %9, 1
  %11 = tail call noalias ptr @malloc(i64 noundef %10) #8
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
  %7 = tail call i32 @strcmp(ptr noundef nonnull dereferenceable(1) %0, ptr noundef nonnull dereferenceable(1) %1) #7
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

define i32 @main() {
entry:
  %both_tester = alloca i2, align 1
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
  store ptr @.str.1, ptr %name, align 8
  store ptr @.str.2, ptr %greeting, align 8
  store ptr @.str.3, ptr %emoji, align 8
  store i32 10, ptr %x, align 4
  store i32 3, ptr %y, align 4
  %x1 = load i32, ptr %x, align 4
  %y2 = load i32, ptr %y, align 4
  %add = add i32 %x1, %y2
  store i32 %add, ptr %sum, align 4
  %x3 = load i32, ptr %x, align 4
  %y4 = load i32, ptr %y, align 4
  %sub = sub i32 %x3, %y4
  store i32 %sub, ptr %diff, align 4
  %x5 = load i32, ptr %x, align 4
  %y6 = load i32, ptr %y, align 4
  %mul = mul i32 %x5, %y6
  store i32 %mul, ptr %prod, align 4
  %x7 = load i32, ptr %x, align 4
  %y8 = load i32, ptr %y, align 4
  %sdiv = sdiv i32 %x7, %y8
  store i32 %sdiv, ptr %quot, align 4
  %x9 = load i32, ptr %x, align 4
  %y10 = load i32, ptr %y, align 4
  %srem = srem i32 %x9, %y10
  store i32 %srem, ptr %rem, align 4
  %powi = call i32 @qc_powi_i32(i32 2, i32 8)
  store i32 %powi, ptr %power, align 4
  %x11 = load i32, ptr %x, align 4
  %add12 = add i32 %x11, 5
  store i32 %add12, ptr %x, align 4
  %x13 = load i32, ptr %x, align 4
  %sub14 = sub i32 %x13, 3
  store i32 %sub14, ptr %x, align 4
  %x15 = load i32, ptr %x, align 4
  %mul16 = mul i32 %x15, 2
  store i32 %mul16, ptr %x, align 4
  %x17 = load i32, ptr %x, align 4
  %sdiv18 = sdiv i32 %x17, 4
  store i32 %sdiv18, ptr %x, align 4
  %x19 = load i32, ptr %x, align 4
  %srem20 = srem i32 %x19, 5
  store i32 %srem20, ptr %x, align 4
  store float 1.050000e+01, ptr %a, align 4
  store float 2.500000e+00, ptr %b, align 4
  %a21 = load float, ptr %a, align 4
  %b22 = load float, ptr %b, align 4
  %fadd = fadd float %a21, %b22
  store float %fadd, ptr %fsum, align 4
  %a23 = load float, ptr %a, align 4
  %b24 = load float, ptr %b, align 4
  %fsub = fsub float %a23, %b24
  store float %fsub, ptr %fdiff, align 4
  %a25 = load float, ptr %a, align 4
  %b26 = load float, ptr %b, align 4
  %fmul = fmul float %a25, %b26
  store float %fmul, ptr %fprod, align 4
  %a27 = load float, ptr %a, align 4
  %b28 = load float, ptr %b, align 4
  %fdiv = fdiv float %a27, %b28
  store float %fdiv, ptr %fquot, align 4
  %a29 = load float, ptr %a, align 4
  %fadd30 = fadd float %a29, 1.500000e+00
  store float %fadd30, ptr %a, align 4
  %a31 = load float, ptr %a, align 4
  %fsub32 = fsub float %a31, 2.000000e+00
  store float %fsub32, ptr %a, align 4
  %a33 = load float, ptr %a, align 4
  %fmul34 = fmul float %a33, 3.000000e+00
  store float %fmul34, ptr %a, align 4
  %a35 = load float, ptr %a, align 4
  %fdiv36 = fdiv float %a35, 5.000000e+00
  store float %fdiv36, ptr %a, align 4
  store i32 10, ptr %i, align 4
  store float 0x40091EB860000000, ptr %f, align 4
  store double 2.718000e+00, ptr %d, align 8
  %f37 = load float, ptr %f, align 4
  %d38 = load double, ptr %d, align 8
  %promote_to_double = fpext float %f37 to double
  %fadd39 = fadd double %promote_to_double, %d38
  store double %fadd39, ptr %result1, align 8
  %i40 = load i32, ptr %i, align 4
  %i41 = load i32, ptr %i, align 4
  %add42 = add i32 %i40, %i41
  store i32 %add42, ptr %result2, align 4
  %i43 = load i32, ptr %i, align 4
  %mul44 = mul i32 %i43, 2
  store i32 %mul44, ptr %result3, align 4
  %i45 = load i32, ptr %i, align 4
  %add46 = add i32 %i45, 5
  store i32 %add46, ptr %i, align 4
  %f47 = load float, ptr %f, align 4
  %fadd48 = fadd float %f47, 1.500000e+00
  store float %fadd48, ptr %f, align 4
  %d49 = load double, ptr %d, align 8
  %fadd50 = fadd double %d49, 1.000000e-03
  store double %fadd50, ptr %d, align 8
  store i8 65, ptr %start, align 1
  store i8 90, ptr %end, align 1
  store i8 32, ptr %space, align 1
  store i8 10, ptr %newline, align 1
  store i8 9, ptr %tab, align 1
  %start51 = load i8, ptr %start, align 1
  store i8 66, ptr %start, align 1
  %end52 = load i8, ptr %end, align 1
  store i8 89, ptr %end, align 1
  store i1 true, ptr %yes, align 1
  store i1 false, ptr %no, align 1
  %yes53 = load i1, ptr %yes, align 1
  store i1 false, ptr %yes, align 1
  %no54 = load i1, ptr %no, align 1
  store i1 true, ptr %no, align 1
  %yes55 = load i1, ptr %yes, align 1
  store i1 true, ptr %yes, align 1
  store i2 -1, ptr %schrodinger, align 1
  store i2 -2, ptr %alive, align 1
  store i2 1, ptr %dead, align 1
  store i2 0, ptr %nul, align 1
  %schrodinger56 = load i2, ptr %schrodinger, align 1
  store i2 -2, ptr %schrodinger, align 1
  %alive57 = load i2, ptr %alive, align 1
  store i2 -1, ptr %alive, align 1
  %dead58 = load i2, ptr %dead, align 1
  store i2 0, ptr %dead, align 1
  %nul59 = load i2, ptr %nul, align 1
  store i2 1, ptr %nul, align 1
  store ptr @.str.4, ptr %hello, align 8
  store ptr @.str.5, ptr %world, align 8
  store ptr @.str.6, ptr %exclaim, align 8
  store ptr @.str.7, ptr %non, align 8
  store ptr @.str.8, ptr %quote, align 8
  store ptr @.str.9, ptr %path, align 8
  store i32 2, ptr %base, align 4
  store i32 10, ptr %exp, align 4
  store float 2.000000e+00, ptr %fbase, align 4
  store float 3.000000e+00, ptr %fexp, align 4
  %fbase60 = load float, ptr %fbase, align 4
  %fexp61 = load float, ptr %fexp, align 4
  %pow = call float @llvm.pow.f32(float %fbase60, float %fexp61)
  store float %pow, ptr %fresult, align 4
  store double 1.500000e+00, ptr %dbase, align 8
  store double 2.000000e+00, ptr %dexp, align 8
  %dbase62 = load double, ptr %dbase, align 8
  %dexp63 = load double, ptr %dexp, align 8
  %pow64 = call double @llvm.pow.f64(double %dbase62, double %dexp63)
  store double %pow64, ptr %dresult, align 8
  store i32 5, ptr %xdd, align 4
  store i32 10, ptr %ydd, align 4
  %xdd65 = load i32, ptr %xdd, align 4
  %ydd66 = load i32, ptr %ydd, align 4
  %icmpeq = icmp eq i32 %xdd65, %ydd66
  store i1 %icmpeq, ptr %eq, align 1
  %xdd67 = load i32, ptr %xdd, align 4
  %ydd68 = load i32, ptr %ydd, align 4
  %icmpne = icmp ne i32 %xdd67, %ydd68
  store i1 %icmpne, ptr %ne, align 1
  %xdd69 = load i32, ptr %xdd, align 4
  %ydd70 = load i32, ptr %ydd, align 4
  %icmplt = icmp slt i32 %xdd69, %ydd70
  store i1 %icmplt, ptr %lt, align 1
  %xdd71 = load i32, ptr %xdd, align 4
  %ydd72 = load i32, ptr %ydd, align 4
  %icmpgt = icmp sgt i32 %xdd71, %ydd72
  store i1 %icmpgt, ptr %gt, align 1
  %xdd73 = load i32, ptr %xdd, align 4
  %ydd74 = load i32, ptr %ydd, align 4
  %icmple = icmp sle i32 %xdd73, %ydd74
  store i1 %icmple, ptr %lte, align 1
  %xdd75 = load i32, ptr %xdd, align 4
  %ydd76 = load i32, ptr %ydd, align 4
  %icmpge = icmp sge i32 %xdd75, %ydd76
  store i1 %icmpge, ptr %gte, align 1
  store i32 0, ptr %result, align 4
  %xdd77 = load i32, ptr %xdd, align 4
  %icmpgt78 = icmp sgt i32 %xdd77, 3
  br i1 %icmpgt78, label %then, label %else

then:                                             ; preds = %entry
  %result79 = load i32, ptr %result, align 4
  store i32 10, ptr %result, align 4
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %i81 = load i32, ptr %i, align 4
  store i32 0, ptr %i, align 4
  %sum82 = load i32, ptr %sum, align 4
  store i32 0, ptr %sum, align 4
  br label %while.cond

else:                                             ; preds = %entry
  %result80 = load i32, ptr %result, align 4
  store i32 20, ptr %result, align 4
  br label %ifcont

while.cond:                                       ; preds = %while.body, %ifcont
  %i83 = load i32, ptr %i, align 4
  %icmplt84 = icmp slt i32 %i83, 5
  br i1 %icmplt84, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %sum85 = load i32, ptr %sum, align 4
  %i86 = load i32, ptr %i, align 4
  %add87 = add i32 %sum85, %i86
  store i32 %add87, ptr %sum, align 4
  %i88 = load i32, ptr %i, align 4
  %add89 = add i32 %i88, 1
  store i32 %add89, ptr %i, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %sum90 = load i32, ptr %sum, align 4
  store i32 0, ptr %sum, align 4
  store i32 0, ptr %xyz, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %while.end
  %xyz91 = load i32, ptr %xyz, align 4
  %icmplt92 = icmp slt i32 %xyz91, 5
  br i1 %icmplt92, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %sum93 = load i32, ptr %sum, align 4
  %xyz94 = load i32, ptr %xyz, align 4
  %add95 = add i32 %sum93, %xyz94
  store i32 %add95, ptr %sum, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %xyz96 = load i32, ptr %xyz, align 4
  %add97 = add i32 %xyz96, 1
  store i32 %add97, ptr %xyz, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  store i1 true, ptr %ata, align 1
  store i1 false, ptr %btb, align 1
  %ata98 = load i1, ptr %ata, align 1
  %btb99 = load i1, ptr %btb, align 1
  %and = and i1 %ata98, %btb99
  store i1 %and, ptr %and_test, align 1
  %ata100 = load i1, ptr %ata, align 1
  %btb101 = load i1, ptr %btb, align 1
  %or = or i1 %ata100, %btb101
  store i1 %or, ptr %or_test, align 1
  %ata102 = load i1, ptr %ata, align 1
  %btb103 = load i1, ptr %btb, align 1
  %xor = xor i1 %ata102, %btb103
  store i1 %xor, ptr %xor_test, align 1
  %ata104 = load i1, ptr %ata, align 1
  %not = xor i1 %ata104, true
  store i1 %not, ptr %xor_test, align 1
  %sum105 = load i32, ptr %sum, align 4
  switch i32 %sum105, label %switch.case107 [
    i32 1, label %switch.case
    i32 5, label %switch.case106
  ]

switch.end:                                       ; preds = %switch.case107, %switch.case106, %switch.case
  store i2 -1, ptr %both_tester, align 1
  %both_tester110 = load i2, ptr %both_tester, align 1
  %0 = and i2 %both_tester110, -2
  %1 = icmp ne i2 %0, 0
  br i1 %1, label %qif.body, label %qelif.check

switch.case:                                      ; preds = %for.end
  br label %switch.end

switch.case106:                                   ; preds = %for.end
  %sum108 = load i32, ptr %sum, align 4
  store i32 2, ptr %sum, align 4
  br label %switch.end

switch.case107:                                   ; preds = %for.end
  %sum109 = load i32, ptr %sum, align 4
  store i32 0, ptr %sum, align 4
  br label %switch.end

qif.end:                                          ; preds = %qelse.body, %qelif.check, %qif.body
  %x115 = load i32, ptr %x, align 4
  store i32 0, ptr %x, align 4
  %both_tester116 = load i2, ptr %both_tester, align 1
  br label %qsw.check_true

qif.body:                                         ; preds = %switch.end
  %sum111 = load i32, ptr %sum, align 4
  %add112 = add i32 %sum111, 123
  store i32 %add112, ptr %sum, align 4
  br label %qif.end

qelif.check:                                      ; preds = %switch.end
  %2 = and i2 %both_tester110, 1
  %3 = icmp ne i2 %2, 0
  br i1 %3, label %qelse.body, label %qif.end

qelse.body:                                       ; preds = %qelif.check
  %sum113 = load i32, ptr %sum, align 4
  %add114 = add i32 %sum113, 321
  store i32 %add114, ptr %sum, align 4
  br label %qif.end

qsw.check_true:                                   ; preds = %qif.end
  %has_true = and i2 %both_tester116, -2
  %is_true = icmp ne i2 %has_true, 0
  br i1 %is_true, label %qsw.check_false, label %qsw.check_false

qsw.check_false:                                  ; preds = %qsw.check_true, %qsw.check_true
  %has_false = and i2 %both_tester116, 1
  %is_false = icmp ne i2 %has_false, 0
  %is_both = and i1 %is_true, %is_false
  %not_false = xor i1 %is_false, true
  %is_qtrue_only = and i1 %is_true, %not_false
  %not_true = xor i1 %is_true, true
  %is_qfalse_only = and i1 %not_true, %is_false
  %is_none = and i1 %not_true, %not_false
  br i1 %is_both, label %qsw.case_b, label %qsw.check_qtrue

qswitch.end:                                      ; preds = %qsw.case_b, %qsw.case_t, %qsw.check_none_final, %qsw.check_none_final, %qsw.check_qfalse
  ret i32 0

qsw.case_t:                                       ; preds = %qsw.check_qtrue
  %x117 = load i32, ptr %x, align 4
  store i32 2, ptr %x, align 4
  br label %qswitch.end

qsw.case_b:                                       ; preds = %qsw.check_false
  %x118 = load i32, ptr %x, align 4
  store i32 1, ptr %x, align 4
  br label %qswitch.end

qsw.check_qtrue:                                  ; preds = %qsw.check_false
  br i1 %is_qtrue_only, label %qsw.case_t, label %qsw.check_qfalse

qsw.check_qfalse:                                 ; preds = %qsw.check_qtrue
  br i1 %is_qfalse_only, label %qswitch.end, label %qsw.check_none_final

qsw.check_none_final:                             ; preds = %qsw.check_qfalse
  br i1 %is_none, label %qswitch.end, label %qswitch.end
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare float @llvm.pow.f32(float, float) #6

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare double @llvm.pow.f64(double, double) #6

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nofree nounwind willreturn uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress nofree nounwind willreturn memory(argmem: read) "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #5 = { mustprogress nofree nounwind willreturn memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #7 = { nounwind willreturn memory(read) }
attributes #8 = { nounwind allocsize(0) }

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
