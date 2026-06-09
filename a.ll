; ModuleID = 'a.ll'
source_filename = "qc_module"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%variadic = type { ptr, i32, i32 }

define internal i1 @variadic_is_empty(ptr %v) {
entry:
  %v1 = alloca ptr, align 8
  store ptr %v, ptr %v1, align 8
  %v2 = load ptr, ptr %v1, align 8
  %v3 = load ptr, ptr %v1, align 8
  %deref = load %variadic, ptr %v3, align 8
  %current_index = extractvalue %variadic %deref, 2
  %v4 = load ptr, ptr %v1, align 8
  %v5 = load ptr, ptr %v1, align 8
  %deref6 = load %variadic, ptr %v5, align 8
  %count = extractvalue %variadic %deref6, 1
  %icmpge = icmp sge i32 %current_index, %count
  ret i1 %icmpge
}

define internal ptr @variadic_next(ptr %v) {
entry:
  %data = alloca ptr, align 8
  %v1 = alloca ptr, align 8
  store ptr %v, ptr %v1, align 8
  %v2 = load ptr, ptr %v1, align 8
  %calltmp = call i1 @variadic_is_empty(ptr %v2)
  br i1 %calltmp, label %then, label %ifcont

then:                                             ; preds = %entry
  ret ptr null

ifcont:                                           ; preds = %entry
  %v3 = load ptr, ptr %v1, align 8
  %v4 = load ptr, ptr %v1, align 8
  %deref = load %variadic, ptr %v4, align 8
  %current_index = extractvalue %variadic %deref, 2
  %v5 = load ptr, ptr %v1, align 8
  %v6 = load ptr, ptr %v1, align 8
  %deref7 = load %variadic, ptr %v6, align 8
  %items = extractvalue %variadic %deref7, 0
  %ptr_arr_addr = getelementptr ptr, ptr %items, i32 %current_index
  %ptr_arr_val = load ptr, ptr %ptr_arr_addr, align 8
  store ptr %ptr_arr_val, ptr %data, align 8
  %v8 = load ptr, ptr %v1, align 8
  %v9 = load ptr, ptr %v1, align 8
  %deref10 = load %variadic, ptr %v9, align 8
  %current_index11 = extractvalue %variadic %deref10, 2
  %v12 = load ptr, ptr %v1, align 8
  %v13 = load ptr, ptr %v1, align 8
  %deref14 = load %variadic, ptr %v13, align 8
  %current_index15 = extractvalue %variadic %deref14, 2
  %v16 = load ptr, ptr %v1, align 8
  %current_index_ptr = getelementptr inbounds nuw %variadic, ptr %v16, i32 0, i32 2
  %inc_deref = load i32, ptr %current_index_ptr, align 4
  %inc = add i32 %inc_deref, 1
  store i32 %inc, ptr %current_index_ptr, align 4
  %data17 = load ptr, ptr %data, align 8
  ret ptr %data17
}

define internal i32 @__user_entry() {
entry:
  %b = alloca i1, align 1
  %xp = alloca ptr, align 8
  %x = alloca i32, align 4
  %v = alloca %variadic, align 8
  store %variadic { ptr null, i32 1, i32 0 }, ptr %v, align 8
  store i32 123, ptr %x, align 4
  %x1 = load i32, ptr %x, align 4
  store ptr %x, ptr %xp, align 8
  %xp2 = load ptr, ptr %xp, align 8
  %items_ptr = getelementptr inbounds nuw %variadic, ptr %v, i32 0, i32 0
  %xp3 = load ptr, ptr %xp, align 8
  store ptr %xp, ptr %items_ptr, align 8
  %v4 = load %variadic, ptr %v, align 8
  %calltmp = call i1 @variadic_is_empty(ptr %v)
  store i1 %calltmp, ptr %b, align 1
  %assign_lhs_val = load ptr, ptr %xp, align 8
  %v5 = load %variadic, ptr %v, align 8
  %calltmp6 = call ptr @variadic_next(ptr %v)
  store ptr %calltmp6, ptr %xp, align 8
  %assign_lhs_val7 = load i32, ptr %x, align 4
  %xp8 = load ptr, ptr %xp, align 8
  %xp9 = load ptr, ptr %xp, align 8
  %deref = load i32, ptr %xp9, align 4
  store i32 %deref, ptr %x, align 4
  ret i32 0
}

define i32 @main() {
entry:
  %entry_result = call i32 @__user_entry()
  ret i32 %entry_result
}

!llvm.ident = !{!0}
!llvm.module.flags = !{!1, !2, !3, !4}

!0 = !{!"Debian clang version 21.1.8 (7+b1)"}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 2}
