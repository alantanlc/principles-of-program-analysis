; ModuleID = './test-files/test5.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 0, i32* %1
  store i32 -2, i32* %a, align 4
  store i32 5, i32* %b, align 4
  store i32 0, i32* %x, align 4
  store i32 0, i32* %i, align 4
  br label %2

; <label>:2                                       ; preds = %20, %0
  %3 = load i32* %i, align 4
  %4 = add nsw i32 %3, 1
  store i32 %4, i32* %i, align 4
  %5 = icmp slt i32 %3, 10
  br i1 %5, label %6, label %21

; <label>:6                                       ; preds = %2
  %7 = load i32* %a, align 4
  %8 = icmp sgt i32 %7, 0
  br i1 %8, label %9, label %12

; <label>:9                                       ; preds = %6
  %10 = load i32* %x, align 4
  %11 = add nsw i32 %10, 7
  store i32 %11, i32* %x, align 4
  store i32 5, i32* %y, align 4
  br label %15

; <label>:12                                      ; preds = %6
  %13 = load i32* %x, align 4
  %14 = sub nsw i32 %13, 2
  store i32 %14, i32* %x, align 4
  store i32 1, i32* %y, align 4
  br label %15

; <label>:15                                      ; preds = %12, %9
  %16 = load i32* %b, align 4
  %17 = icmp sgt i32 %16, 0
  br i1 %17, label %18, label %19

; <label>:18                                      ; preds = %15
  store i32 6, i32* %a, align 4
  br label %20

; <label>:19                                      ; preds = %15
  store i32 -5, i32* %a, align 4
  br label %20

; <label>:20                                      ; preds = %19, %18
  br label %2

; <label>:21                                      ; preds = %2
  %22 = load i32* %1
  ret i32 %22
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"Ubuntu clang version 3.5.2-3ubuntu1 (tags/RELEASE_352/final) (based on LLVM 3.5.2)"}
