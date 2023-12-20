// Fill out your copyright notice in the Description page of Project Settings.


#include "SDialogueTreeWidget.h"
#include "Editor.h"

void SDialogueTreeWidget::Construct(const FArguments& InArgs)
{
	Mean = InArgs._Mean;
	StandardDeviation = InArgs._StandardDeviation;
	OnMeanChanged = InArgs._OnMeanChanged;
	OnStandardDeviationChanged = InArgs._OnStandardDeviationChanged;
}

int32 SDialogueTreeWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	const int32 NumPoints = 512;
	TArray<FVector2D> Points;
	Points.Reserve(NumPoints);
	const FTransform2D PointsTransform = GetPointsTransform(AllottedGeometry);
	for (int32 PointIndex = 0; PointIndex < NumPoints; ++PointIndex)
	{
		const float X = PointIndex / (NumPoints - 1.0);
		const float D = (X - Mean.Get()) / StandardDeviation.Get();
		const float Y = FMath::Exp(-0.5f * D * D);
		Points.Add(PointsTransform.TransformPoint(FVector2D(X, Y)));
	}

	FSlateDrawElement::MakeLines(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(), Points);
	return LayerId;
}

FVector2D SDialogueTreeWidget::ComputeDesiredSize(float) const
{
	return FVector2D(200.0, 200.0);
}

FReply SDialogueTreeWidget::OnMouseButtonDown(const FGeometry& AllottedGeometry, const FPointerEvent& MouseEvent)
{
	if (GEditor && GEditor->CanTransact() && ensure(!GIsTransacting))
	{
		GEditor->BeginTransaction(TEXT(""), INVTEXT("Edit Dialogue Tree"), nullptr);
	}

	return FReply::Handled().CaptureMouse(SharedThis(this));
}

FReply SDialogueTreeWidget::OnMouseButtonUp(const FGeometry& AllottedGeometry, const FPointerEvent& MouseEvent)
{
	if (GEditor)
	{
		GEditor->EndTransaction();
	}

	return FReply::Handled().ReleaseMouseCapture();
}

FReply SDialogueTreeWidget::OnMouseMove(const FGeometry& AllottedGeometry, const FPointerEvent& MouseEvent)
{
	if (!HasMouseCapture())
	{
		return FReply::Unhandled();
	}

	const FTransform2D PointsTransform = GetPointsTransform(AllottedGeometry);
	const FVector2D LocalPosition = AllottedGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
	const FVector2D NormalizedPosition = PointsTransform.Inverse().TransformPoint(LocalPosition);

	if (OnMeanChanged.IsBound())
	{
		OnMeanChanged.Execute(NormalizedPosition.X);
	}

	if (OnStandardDeviationChanged.IsBound())
	{
		OnStandardDeviationChanged.Execute(FMath::Max(0.025f, FMath::Lerp(0.025f, 0.25f, NormalizedPosition.Y)));
	}

	return FReply::Handled();
}

FTransform2D SDialogueTreeWidget::GetPointsTransform(const FGeometry& AllotedGeometry) const
{
	const double Margin = 0.05 * AllotedGeometry.GetLocalSize().GetMin();
	const FScale2D Scale((AllotedGeometry.GetLocalSize() - 2.0 * Margin) * FVector2D(1.0, -1.0));
	const FVector2D Translation(Margin, AllotedGeometry.GetLocalSize().Y - Margin);
	return FTransform2D(Scale, Translation);
}

