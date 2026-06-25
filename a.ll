; ModuleID = 'master_module'
source_filename = "master_module"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str.19 = private unnamed_addr constant [4 x i8] c"%%s\00", align 1
@.str.32 = private unnamed_addr constant [3 x i8] c"%p\00", align 1
@stdout = external local_unnamed_addr global ptr, align 8
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [3 x i8] c", \00", align 1
@2 = private unnamed_addr constant [2 x i8] zeroinitializer, align 1

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite)
declare noalias noundef ptr @malloc(i64 noundef) local_unnamed_addr #0

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr captures(none)) #1

; Function Attrs: nofree nounwind
declare noundef i32 @snprintf(ptr noalias noundef writeonly captures(none), i64 noundef, ptr noundef readonly captures(none), ...) local_unnamed_addr #2

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr captures(none)) #1

; Function Attrs: mustprogress nofree nounwind uwtable
define internal fastcc noalias noundef ptr @qc_fmt_string(ptr noundef %0) unnamed_addr #3 {
  %2 = alloca [16 x i8], align 16
  %3 = icmp eq ptr %0, null
  %4 = select i1 %3, ptr @0, ptr %0
  call void @llvm.lifetime.start.p0(i64 16, ptr nonnull %2) #7
  %5 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 16, ptr noundef nonnull @.str.19) #7
  %6 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef null, i64 noundef 0, ptr noundef nonnull %2, ptr noundef nonnull %4) #7
  %7 = icmp slt i32 %6, 0
  br i1 %7, label %15, label %8

8:                                                ; preds = %1
  %9 = add nuw nsw i32 %6, 1
  %10 = zext nneg i32 %9 to i64
  %11 = tail call noalias ptr @malloc(i64 noundef %10) #8
  %12 = icmp eq ptr %11, null
  br i1 %12, label %15, label %13

13:                                               ; preds = %8
  %14 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %11, i64 noundef %10, ptr noundef nonnull %2, ptr noundef nonnull %4) #7
  br label %15

15:                                               ; preds = %13, %8, %1
  %16 = phi ptr [ null, %1 ], [ %11, %13 ], [ null, %8 ]
  call void @llvm.lifetime.end.p0(i64 16, ptr nonnull %2) #7
  ret ptr %16
}

; Function Attrs: mustprogress nofree nounwind uwtable
define internal fastcc noalias ptr @qc_fmt_ptr(ptr noundef %0) unnamed_addr #3 {
  %2 = alloca [64 x i8], align 16
  call void @llvm.lifetime.start.p0(i64 64, ptr nonnull %2) #7
  %3 = call i32 (ptr, i64, ptr, ...) @snprintf(ptr noundef nonnull dereferenceable(1) %2, i64 noundef 64, ptr noundef nonnull @.str.32, ptr noundef %0) #7
  %4 = call noalias ptr @strdup(ptr noundef nonnull %2) #7
  call void @llvm.lifetime.end.p0(i64 64, ptr nonnull %2) #7
  ret ptr %4
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(argmem: readwrite, inaccessiblemem: readwrite)
declare noalias ptr @strdup(ptr noundef readonly captures(none)) local_unnamed_addr #4

; Function Attrs: mustprogress nofree nounwind uwtable
define internal fastcc void @qc_print_string(ptr noundef readonly captures(address_is_null) %0) unnamed_addr #3 {
  %2 = icmp eq ptr %0, null
  %3 = select i1 %2, ptr @0, ptr %0
  %4 = load ptr, ptr @stdout, align 8, !tbaa !5
  %5 = tail call i32 @fputs(ptr noundef nonnull %3, ptr noundef %4)
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @fputs(ptr noundef readonly captures(none), ptr noundef captures(none)) local_unnamed_addr #2

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
define internal fastcc i32 @qc_list_length(ptr noundef readonly captures(none) %0) unnamed_addr #5 {
  %2 = getelementptr inbounds nuw i8, ptr %0, i64 8
  %3 = load i32, ptr %2, align 8, !tbaa !10
  ret i32 %3
}

; Function Attrs: nofree nounwind
define noundef i32 @main(i32 %0, ptr %1) local_unnamed_addr #6 {
entry:
  %list_len.i = tail call fastcc i32 @qc_list_length(ptr %1)
  %icmpgt.i = icmp sgt i32 %list_len.i, 1
  br i1 %icmpgt.i, label %then.i, label %__user_entry.exit

then.i:                                           ; preds = %entry
  %arr_elem_ptr.i = getelementptr i8, ptr %1, i64 8
  tail call fastcc void @qc_print_string(ptr nonnull @0)
  %2 = tail call fastcc ptr @qc_fmt_string(ptr %arr_elem_ptr.i)
  tail call fastcc void @qc_print_string(ptr %2)
  tail call fastcc void @qc_print_string(ptr nonnull @1)
  %3 = tail call fastcc ptr @qc_fmt_ptr(ptr %arr_elem_ptr.i)
  tail call fastcc void @qc_print_string(ptr %3)
  tail call fastcc void @qc_print_string(ptr nonnull @2)
  br label %__user_entry.exit

__user_entry.exit:                                ; preds = %entry, %then.i
  ret i32 0
}

attributes #0 = { mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { nofree nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { mustprogress nofree nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { mustprogress nofree nounwind willreturn memory(argmem: readwrite, inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { nofree nounwind }
attributes #7 = { nounwind }
attributes #8 = { nounwind allocsize(0) }

!llvm.ident = !{!0}
!llvm.module.flags = !{!1, !2, !3, !4}

!0 = !{!"Debian clang version 21.1.8 (7+b1)"}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 2}
!5 = !{!6, !6, i64 0}
!6 = !{!"p1 _ZTS8_IO_FILE", !7, i64 0}
!7 = !{!"any pointer", !8, i64 0}
!8 = !{!"omnipotent char", !9, i64 0}
!9 = !{!"Simple C++ TBAA"}
!10 = !{!11, !13, i64 8}
!11 = !{!"_ZTS7qc_list", !12, i64 0, !13, i64 8, !13, i64 12, !13, i64 16}
!12 = !{!"any p2 pointer", !7, i64 0}
!13 = !{!"int", !8, i64 0}
