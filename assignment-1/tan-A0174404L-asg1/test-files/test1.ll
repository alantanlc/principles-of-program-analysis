; ModuleID = 'test1.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %a = alloca i32, align 4
  %c = alloca i32, align 4
  store i32 0, i32* %1
  store i32 0, i32* %c, align 4
  %2 = load i32* %a, align 4
  %3 = icmp sgt i32 %2, 0
  br i1 %3, label %4, label %7

; <label>:4                                       ; preds = %0
  %5 = load i32* %c, align 4
  %6 = add nsw i32 %5, 10
  store i32 %6, i32* %c, align 4
  br label %10

; <label>:7                                       ; preds = %0
  %8 = load i32* %c, align 4
  %9 = add nsw i32 %8, 15
  store i32 %9, i32* %c, align 4
  br label %10

; <label>:10                                      ; preds = %7, %4
  %11 = load i32* %1
  ret i32 %11
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"Ubuntu clang version 3.5.2-3ubuntu1 (tags/RELEASE_352/final) (based on LLVM 3.5.2)"}
