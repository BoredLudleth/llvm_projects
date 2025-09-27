; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind uwtable
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

declare i32 @simRand(...) local_unnamed_addr #2

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: nounwind uwtable
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

declare void @fillRect(i32 noundef, i32 noundef, i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #2

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
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
  %12 = urem i32 %11, 100
  %13 = add nsw i32 %3, 1
  %14 = srem i32 %13, 100
  %15 = mul nsw i32 %4, 100
  %16 = add nsw i32 %7, %12
  %17 = sext i32 %16 to i64
  %18 = getelementptr inbounds i32, ptr %0, i64 %17
  %19 = load i32, ptr %18, align 4, !tbaa !5
  %20 = add nsw i32 %7, %3
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds i32, ptr %0, i64 %21
  %23 = load i32, ptr %22, align 4, !tbaa !5
  %24 = add nsw i32 %23, %19
  %25 = add nsw i32 %7, %14
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds i32, ptr %0, i64 %26
  %28 = load i32, ptr %27, align 4, !tbaa !5
  %29 = add nsw i32 %24, %28
  %30 = add nsw i32 %12, %15
  %31 = sext i32 %30 to i64
  %32 = getelementptr inbounds i32, ptr %0, i64 %31
  %33 = load i32, ptr %32, align 4, !tbaa !5
  %34 = add nsw i32 %29, %33
  %35 = add nsw i32 %14, %15
  %36 = sext i32 %35 to i64
  %37 = getelementptr inbounds i32, ptr %0, i64 %36
  %38 = load i32, ptr %37, align 4, !tbaa !5
  %39 = add nsw i32 %34, %38
  %40 = add nsw i32 %10, %12
  %41 = sext i32 %40 to i64
  %42 = getelementptr inbounds i32, ptr %0, i64 %41
  %43 = load i32, ptr %42, align 4, !tbaa !5
  %44 = add nsw i32 %39, %43
  %45 = add nsw i32 %10, %3
  %46 = sext i32 %45 to i64
  %47 = getelementptr inbounds i32, ptr %0, i64 %46
  %48 = load i32, ptr %47, align 4, !tbaa !5
  %49 = add nsw i32 %44, %48
  %50 = add nsw i32 %10, %14
  %51 = sext i32 %50 to i64
  %52 = getelementptr inbounds i32, ptr %0, i64 %51
  %53 = load i32, ptr %52, align 4, !tbaa !5
  %54 = add nsw i32 %49, %53
  ret i32 %54
}

; Function Attrs: nofree norecurse nosync nounwind memory(argmem: readwrite) uwtable
define dso_local void @NextStep(ptr nocapture noundef %0) local_unnamed_addr #4 {
  %2 = alloca [10000 x i32], align 16
  call void @llvm.lifetime.start.p0(i64 40000, ptr nonnull %2) #7
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 16 dereferenceable(40000) %2, i8 0, i64 40000, i1 false)
  br label %3

3:                                                ; preds = %1, %65
  %4 = phi i64 [ 0, %1 ], [ %69, %65 ]
  %5 = trunc i64 %4 to i32
  %6 = urem i32 %5, 100
  %7 = trunc i64 %4 to i32
  %8 = udiv i32 %7, 100
  %9 = add nuw nsw i32 %8, 99
  %10 = urem i32 %9, 100
  %11 = mul nuw nsw i32 %10, 100
  %12 = add nuw nsw i32 %8, 1
  %13 = urem i32 %12, 100
  %14 = mul nuw nsw i32 %13, 100
  %15 = add nuw nsw i32 %6, 99
  %16 = urem i32 %15, 100
  %17 = add nuw nsw i32 %6, 1
  %18 = icmp eq i32 %17, 100
  %19 = select i1 %18, i32 0, i32 %17
  %20 = mul nuw nsw i32 %8, 100
  %21 = add nuw nsw i32 %11, %16
  %22 = zext nneg i32 %21 to i64
  %23 = getelementptr inbounds i32, ptr %0, i64 %22
  %24 = load i32, ptr %23, align 4, !tbaa !5
  %25 = add nuw nsw i32 %11, %6
  %26 = zext nneg i32 %25 to i64
  %27 = getelementptr inbounds i32, ptr %0, i64 %26
  %28 = load i32, ptr %27, align 4, !tbaa !5
  %29 = add nsw i32 %28, %24
  %30 = add nuw nsw i32 %11, %19
  %31 = zext nneg i32 %30 to i64
  %32 = getelementptr inbounds i32, ptr %0, i64 %31
  %33 = load i32, ptr %32, align 4, !tbaa !5
  %34 = add nsw i32 %29, %33
  %35 = add nuw nsw i32 %16, %20
  %36 = zext nneg i32 %35 to i64
  %37 = getelementptr inbounds i32, ptr %0, i64 %36
  %38 = load i32, ptr %37, align 4, !tbaa !5
  %39 = add nsw i32 %34, %38
  %40 = add nuw nsw i32 %19, %20
  %41 = zext nneg i32 %40 to i64
  %42 = getelementptr inbounds i32, ptr %0, i64 %41
  %43 = load i32, ptr %42, align 4, !tbaa !5
  %44 = add nsw i32 %39, %43
  %45 = add nuw nsw i32 %14, %16
  %46 = zext nneg i32 %45 to i64
  %47 = getelementptr inbounds i32, ptr %0, i64 %46
  %48 = load i32, ptr %47, align 4, !tbaa !5
  %49 = add nsw i32 %44, %48
  %50 = add nuw nsw i32 %14, %6
  %51 = zext nneg i32 %50 to i64
  %52 = getelementptr inbounds i32, ptr %0, i64 %51
  %53 = load i32, ptr %52, align 4, !tbaa !5
  %54 = add nsw i32 %49, %53
  %55 = add nuw nsw i32 %14, %19
  %56 = zext nneg i32 %55 to i64
  %57 = getelementptr inbounds i32, ptr %0, i64 %56
  %58 = load i32, ptr %57, align 4, !tbaa !5
  %59 = add nsw i32 %54, %58
  switch i32 %59, label %64 [
    i32 3, label %65
    i32 2, label %60
  ]

60:                                               ; preds = %3
  %61 = getelementptr inbounds i32, ptr %0, i64 %4
  %62 = load i32, ptr %61, align 4, !tbaa !5
  %63 = icmp eq i32 %62, 1
  br label %65

64:                                               ; preds = %3
  br label %65

65:                                               ; preds = %3, %64, %60
  %66 = phi i1 [ true, %3 ], [ %63, %60 ], [ false, %64 ]
  %67 = zext i1 %66 to i32
  %68 = getelementptr inbounds [10000 x i32], ptr %2, i64 0, i64 %4
  store i32 %67, ptr %68, align 4, !tbaa !5
  %69 = add nuw nsw i64 %4, 1
  %70 = icmp eq i64 %69, 10000
  br i1 %70, label %71, label %3, !llvm.loop !12

71:                                               ; preds = %65
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 4 dereferenceable(40000) %0, ptr noundef nonnull align 16 dereferenceable(40000) %2, i64 40000, i1 false), !tbaa !5
  call void @llvm.lifetime.end.p0(i64 40000, ptr nonnull %2) #7
  ret void
}

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #5

; Function Attrs: nounwind uwtable
define dso_local void @DrawField(ptr nocapture noundef readonly %0) local_unnamed_addr #0 {
  br label %3

2:                                                ; preds = %3
  ret void

3:                                                ; preds = %1, %3
  %4 = phi i64 [ 0, %1 ], [ %17, %3 ]
  %5 = getelementptr inbounds i32, ptr %0, i64 %4
  %6 = load i32, ptr %5, align 4, !tbaa !5
  %7 = icmp eq i32 %6, 0
  %8 = trunc i64 %4 to i32
  %9 = urem i32 %8, 100
  %10 = trunc i64 %4 to i32
  %11 = udiv i32 %10, 100
  %12 = mul nuw nsw i32 %9, 10
  %13 = or disjoint i32 %12, 1
  %14 = mul nuw nsw i32 %11, 10
  %15 = or disjoint i32 %14, 1
  %16 = select i1 %7, i32 -1, i32 -16764058
  tail call void @fillRect(i32 noundef %13, i32 noundef %15, i32 noundef 9, i32 noundef 9, i32 noundef %16) #7
  %17 = add nuw nsw i64 %4, 1
  %18 = icmp eq i64 %17, 10000
  br i1 %18, label %2, label %3, !llvm.loop !13
}

; Function Attrs: nounwind uwtable
define dso_local void @app() local_unnamed_addr #0 {
  %1 = alloca [10000 x i32], align 16
  call void @llvm.lifetime.start.p0(i64 40000, ptr nonnull %1) #7
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
  br i1 %8, label %9, label %2, !llvm.loop !9

9:                                                ; preds = %2, %27
  %10 = phi i32 [ %28, %27 ], [ 0, %2 ]
  br label %12

11:                                               ; preds = %27
  call void @llvm.lifetime.end.p0(i64 40000, ptr nonnull %1) #7
  ret void

12:                                               ; preds = %9, %12
  %13 = phi i64 [ %25, %12 ], [ 0, %9 ]
  %14 = getelementptr inbounds i32, ptr %1, i64 %13
  %15 = load i32, ptr %14, align 4, !tbaa !5
  %16 = icmp eq i32 %15, 0
  %17 = trunc i64 %13 to i32
  %18 = urem i32 %17, 100
  %19 = udiv i32 %17, 100
  %20 = mul nuw nsw i32 %18, 10
  %21 = or disjoint i32 %20, 1
  %22 = mul nuw nsw i32 %19, 10
  %23 = or disjoint i32 %22, 1
  %24 = select i1 %16, i32 -1, i32 -16764058
  tail call void @fillRect(i32 noundef %21, i32 noundef %23, i32 noundef 9, i32 noundef 9, i32 noundef %24) #7
  %25 = add nuw nsw i64 %13, 1
  %26 = icmp eq i64 %25, 10000
  br i1 %26, label %27, label %12, !llvm.loop !13

27:                                               ; preds = %12
  call void @NextStep(ptr noundef nonnull %1)
  tail call void (...) @simFlush() #7
  %28 = add nuw nsw i32 %10, 1
  %29 = icmp eq i32 %28, 10000
  br i1 %29, label %11, label %9, !llvm.loop !14
}

declare void @simFlush(...) local_unnamed_addr #2

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #6

attributes #0 = { nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nofree norecurse nosync nounwind memory(argmem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { mustprogress nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #6 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #7 = { nounwind }

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
!9 = distinct !{!9, !10, !11}
!10 = !{!"llvm.loop.mustprogress"}
!11 = !{!"llvm.loop.unroll.disable"}
!12 = distinct !{!12, !10, !11}
!13 = distinct !{!13, !10, !11}
!14 = distinct !{!14, !10, !11}
