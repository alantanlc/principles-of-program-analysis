; ModuleID = './test-files/test3.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  %z = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 0, i32* %1
  store i32 0, i32* %z, align 4
  store i32 0, i32* %i, align 4
  br label %2

; <label>:2                                       ; preds = %5, %0
  %3 = load i32* %i, align 4
  %4 = icmp slt i32 %3, 10
  br i1 %4, label %5, label %25

; <label>:5                                       ; preds = %2
  %6 = load i32* %x, align 4
  %7 = load i32* %y, align 4
  %8 = mul nsw i32 2, %7
  %9 = mul nsw i32 %8, 3
  %10 = load i32* %z, align 4
  %11 = mul nsw i32 %9, %10
  %12 = add nsw i32 %6, %11
  %13 = srem i32 %12, 3
  %14 = sub nsw i32 0, %13
  store i32 %14, i32* %x, align 4
  %15 = load i32* %x, align 4
  %16 = mul nsw i32 3, %15
  %17 = load i32* %y, align 4
  %18 = mul nsw i32 2, %17
  %19 = add nsw i32 %16, %18
  %20 = load i32* %z, align 4
  %21 = add nsw i32 %19, %20
  %22 = srem i32 %21, 11
  store i32 %22, i32* %y, align 4
  %23 = load i32* %z, align 4
  %24 = add nsw i32 %23, 1
  store i32 %24, i32* %z, align 4
  br label %2

; <label>:25                                      ; preds = %2
  ret i32 0
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"Ubuntu clang version 3.5.2-3ubuntu1 (tags/RELEASE_352/final) (based on LLVM 3.5.2)"}
