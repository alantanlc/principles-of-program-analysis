; ModuleID = 'test3.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %x = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 0, i32* %1
  store i32 0, i32* %x, align 4
  store i32 0, i32* %i, align 4
  br label %2

; <label>:2                                       ; preds = %13, %0
  %3 = load i32* %i, align 4
  %4 = icmp slt i32 %3, 50
  br i1 %4, label %5, label %16

; <label>:5                                       ; preds = %2
  %6 = load i32* %a, align 4
  %7 = icmp sgt i32 %6, 0
  br i1 %7, label %8, label %11

; <label>:8                                       ; preds = %5
  %9 = load i32* %x, align 4
  %10 = sub nsw i32 %9, 5
  store i32 %10, i32* %x, align 4
  br label %12

; <label>:11                                      ; preds = %5
  store i32 2, i32* %x, align 4
  br label %12

; <label>:12                                      ; preds = %11, %8
  br label %13

; <label>:13                                      ; preds = %12
  %14 = load i32* %i, align 4
  %15 = add nsw i32 %14, 1
  store i32 %15, i32* %i, align 4
  br label %2

; <label>:16                                      ; preds = %2
  %17 = load i32* %1
  ret i32 %17
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"Ubuntu clang version 3.5.2-3ubuntu1 (tags/RELEASE_352/final) (based on LLVM 3.5.2)"}
