; ModuleID = '../SDL/app.c'
source_filename = "../SDL/app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind optsize uwtable
define dso_local void @GenerateStartPosition(ptr nocapture noundef writeonly %0) local_unnamed_addr #0 {
  br label %3

2:                                                ; preds = %3
  ret void

3:                                                ; preds = %1, %3
  %4 = phi i64 [ 0, %1 ], [ %8, %3 ]
  %5 = tail call i32 (...) @simRand() #7
  %6 = and i32 %5, 1
  %7 = getelementptr inbounds i32, ptr %0, i64 %4
  store i32 %6, ptr %7, align 4, !tbaa !5
  %8 = add nuw nsw i64 %4, 1
  %9 = icmp eq i64 %8, 10000
  br i1 %9, label %2, label %3, !llvm.loop !9
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: optsize
declare i32 @simRand(...) local_unnamed_addr #2

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: nounwind optsize uwtable
define dso_local void @paintXY(i32 noundef %0, i32 noundef %1) local_unnamed_addr #0 {
  %3 = srem i32 %0, 100
  %4 = sdiv i32 %0, 100
  %5 = mul nsw i32 %3, 10
  %6 = or disjoint i32 %5, 1
  %7 = mul nsw i32 %4, 10
  %8 = or disjoint i32 %7, 1
  tail call void @fillRect(i32 noundef %6, i32 noundef %8, i32 noundef 9, i32 noundef 9, i32 noundef %1) #7
  ret void
}

; Function Attrs: optsize
declare void @fillRect(i32 noundef, i32 noundef, i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #2

; Function Attrs: mustprogress nofree norecurse nosync nounwind optsize willreturn memory(argmem: read) uwtable
define dso_local i32 @countNeighbours(ptr nocapture noundef readonly %0, i32 noundef %1) local_unnamed_addr #3 {
  %3 = srem i32 %1, 100
  %4 = sdiv i32 %1, 100
  %5 = add nsw i32 %4, 99
  %6 = srem i32 %5, 100
  %7 = mul nsw i32 %6, 100
  %8 = add nsw i32 %4, 1
  %9 = srem i32 %8, 100
  %10 = mul nsw i32 %9, 100
  %11 = add nsw i32 %3, 99
  %12 = add nsw i32 %3, -1
  %13 = icmp ult i32 %11, 100
  %14 = select i1 %13, i32 %11, i32 %12
  %15 = trunc i32 %3 to i8
  %16 = add nsw i8 %15, 1
  %17 = srem i8 %16, 100
  %18 = sext i8 %17 to i32
  %19 = mul nsw i32 %4, 100
  %20 = add nsw i32 %7, %14
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds i32, ptr %0, i64 %21
  %23 = load i32, ptr %22, align 4, !tbaa !5
  %24 = add nsw i32 %7, %3
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds i32, ptr %0, i64 %25
  %27 = load i32, ptr %26, align 4, !tbaa !5
  %28 = add nsw i32 %27, %23
  %29 = add nsw i32 %7, %18
  %30 = sext i32 %29 to i64
  %31 = getelementptr inbounds i32, ptr %0, i64 %30
  %32 = load i32, ptr %31, align 4, !tbaa !5
  %33 = add nsw i32 %28, %32
  %34 = add nsw i32 %14, %19
  %35 = sext i32 %34 to i64
  %36 = getelementptr inbounds i32, ptr %0, i64 %35
  %37 = load i32, ptr %36, align 4, !tbaa !5
  %38 = add nsw i32 %33, %37
  %39 = add nsw i32 %19, %18
  %40 = sext i32 %39 to i64
  %41 = getelementptr inbounds i32, ptr %0, i64 %40
  %42 = load i32, ptr %41, align 4, !tbaa !5
  %43 = add nsw i32 %38, %42
  %44 = add nsw i32 %10, %14
  %45 = sext i32 %44 to i64
  %46 = getelementptr inbounds i32, ptr %0, i64 %45
  %47 = load i32, ptr %46, align 4, !tbaa !5
  %48 = add nsw i32 %43, %47
  %49 = add nsw i32 %10, %3
  %50 = sext i32 %49 to i64
  %51 = getelementptr inbounds i32, ptr %0, i64 %50
  %52 = load i32, ptr %51, align 4, !tbaa !5
  %53 = add nsw i32 %48, %52
  %54 = add nsw i32 %10, %18
  %55 = sext i32 %54 to i64
  %56 = getelementptr inbounds i32, ptr %0, i64 %55
  %57 = load i32, ptr %56, align 4, !tbaa !5
  %58 = add nsw i32 %53, %57
  ret i32 %58
}

; Function Attrs: nofree norecurse nosync nounwind optsize memory(argmem: readwrite) uwtable
define dso_local void @NextStep(ptr nocapture noundef %0) local_unnamed_addr #4 {
  %2 = alloca [10000 x i32], align 16
  call void @llvm.lifetime.start.p0(i64 40000, ptr nonnull %2) #8
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 16 dereferenceable(40000) %2, i8 0, i64 40000, i1 false)
  br label %3

3:                                                ; preds = %1, %12
  %4 = phi i64 [ 0, %1 ], [ %16, %12 ]
  %5 = trunc i64 %4 to i32
  %6 = tail call i32 @countNeighbours(ptr noundef %0, i32 noundef %5) #9
  switch i32 %6, label %11 [
    i32 3, label %12
    i32 2, label %7
  ]

7:                                                ; preds = %3
  %8 = getelementptr inbounds i32, ptr %0, i64 %4
  %9 = load i32, ptr %8, align 4, !tbaa !5
  %10 = icmp eq i32 %9, 1
  br label %12

11:                                               ; preds = %3
  br label %12

12:                                               ; preds = %3, %11, %7
  %13 = phi i1 [ true, %3 ], [ %10, %7 ], [ false, %11 ]
  %14 = zext i1 %13 to i32
  %15 = getelementptr inbounds [10000 x i32], ptr %2, i64 0, i64 %4
  store i32 %14, ptr %15, align 4, !tbaa !5
  %16 = add nuw nsw i64 %4, 1
  %17 = icmp eq i64 %16, 10000
  br i1 %17, label %18, label %3, !llvm.loop !11

18:                                               ; preds = %12
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 4 dereferenceable(40000) %0, ptr noundef nonnull align 16 dereferenceable(40000) %2, i64 40000, i1 false), !tbaa !5
  call void @llvm.lifetime.end.p0(i64 40000, ptr nonnull %2) #8
  ret void
}

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #5

; Function Attrs: nounwind optsize uwtable
define dso_local void @DrawField(ptr nocapture noundef readonly %0) local_unnamed_addr #0 {
  br label %3

2:                                                ; preds = %3
  ret void

3:                                                ; preds = %1, %3
  %4 = phi i64 [ 0, %1 ], [ %18, %3 ]
  %5 = getelementptr inbounds i32, ptr %0, i64 %4
  %6 = load i32, ptr %5, align 4, !tbaa !5
  %7 = icmp eq i32 %6, 0
  %8 = trunc i64 %4 to i16
  %9 = urem i16 %8, 100
  %10 = udiv i16 %8, 100
  %11 = mul nuw nsw i16 %9, 10
  %12 = or disjoint i16 %11, 1
  %13 = zext nneg i16 %12 to i32
  %14 = mul nuw nsw i16 %10, 10
  %15 = or disjoint i16 %14, 1
  %16 = zext nneg i16 %15 to i32
  %17 = select i1 %7, i32 -1, i32 -16764058
  tail call void @fillRect(i32 noundef %13, i32 noundef %16, i32 noundef 9, i32 noundef 9, i32 noundef %17) #7
  %18 = add nuw nsw i64 %4, 1
  %19 = icmp eq i64 %18, 10000
  br i1 %19, label %2, label %3, !llvm.loop !12
}

; Function Attrs: nounwind optsize uwtable
define dso_local void @app() local_unnamed_addr #0 {
  %1 = alloca [10000 x i32], align 16
  call void @llvm.lifetime.start.p0(i64 40000, ptr nonnull %1) #8
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 16 dereferenceable(40000) %1, i8 0, i64 40000, i1 false)
  br label %2

2:                                                ; preds = %2, %0
  %3 = phi i64 [ 0, %0 ], [ %7, %2 ]
  %4 = tail call i32 (...) @simRand() #7
  %5 = and i32 %4, 1
  %6 = getelementptr inbounds i32, ptr %1, i64 %3
  store i32 %5, ptr %6, align 4, !tbaa !5
  %7 = add nuw nsw i64 %3, 1
  %8 = icmp eq i64 %7, 10000
  br i1 %8, label %10, label %2, !llvm.loop !9

9:                                                ; preds = %10
  call void @llvm.lifetime.end.p0(i64 40000, ptr nonnull %1) #8
  ret void

10:                                               ; preds = %2, %10
  %11 = phi i32 [ %12, %10 ], [ 0, %2 ]
  call void @DrawField(ptr noundef nonnull %1) #9
  call void @NextStep(ptr noundef nonnull %1) #9
  tail call void (...) @simFlush() #7
  %12 = add nuw nsw i32 %11, 1
  %13 = icmp eq i32 %12, 10000
  br i1 %13, label %9, label %10, !llvm.loop !13
}

; Function Attrs: optsize
declare void @simFlush(...) local_unnamed_addr #2

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #6

attributes #0 = { nounwind optsize uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { optsize "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { mustprogress nofree norecurse nosync nounwind optsize willreturn memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nofree norecurse nosync nounwind optsize memory(argmem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { mustprogress nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #6 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #7 = { nounwind optsize }
attributes #8 = { nounwind }
attributes #9 = { optsize }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"Ubuntu clang version 18.1.3 (1ubuntu1)"}
!5 = !{!6, !6, i64 0}
!6 = !{!"int", !7, i64 0}
!7 = !{!"omnipotent char", !8, i64 0}
!8 = !{!"Simple C/C++ TBAA"}
!9 = distinct !{!9, !10}
!10 = !{!"llvm.loop.mustprogress"}
!11 = distinct !{!11, !10}
!12 = distinct !{!12, !10}
!13 = distinct !{!13, !10}
