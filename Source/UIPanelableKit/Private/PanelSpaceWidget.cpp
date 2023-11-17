// Fill out your copyright notice in the Description page of Project Settings.


#include "PanelSpaceWidget.h"
#include "Components/PanelSlot.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/OverlaySlot.h"
#include "Components/PanelWidget.h"
#include "Components/VerticalBoxSlot.h"


void PIE_Error(const FString& Title, const FString& Info)
{
	FMessageLog("PIE").Error(FText::FromString(Title + ": " + Info));
}

void UPanelSpaceWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Space = Cast<UPanelWidget>(GetRootWidget());
	
	if (!IsValid(Space)) PIE_Error("NotPanelWidget", "RootWidget is not PanelWidget. Error Class:" + GetName()); 
}

void UPanelSpaceWidget::OnShowed_Implementation()
{
	UUIPanelWidget::OnShowed_Implementation();
	OnEnabled.Execute();
}

void UPanelSpaceWidget::OnHided_Implementation()
{
	UUIPanelWidget::OnHided_Implementation();
	OnDisabled.Execute();
}

void UPanelSpaceWidget::ShowPanel(UUIPanelWidget* Panel)
{
	// 未显示空间情况
	if (State != EPanelState::Display) SetDisplay(DisplayVisibility);
	
	if (GetTopPanel() == Panel) return;
	
	Panel->SetDisplay(InShowVisibility(Panel));
	Panels.Remove(Panel);
	Panels.Add(Panel);
}

void UPanelSpaceWidget::HidePanel(UUIPanelWidget* Panel)
{
	// const int LastPanelsNum = Panels.Num();
	// Panels.Remove(Panel);
	// if (LastPanelsNum == Panels.Num()) return;
	
	if (Panels.Remove(Panel) == 0) return;
	Panel->SetHidden(InHideVisibility(Panel));

	// 没有面板显示情况
	if (Panels.Num() == 0) SetHidden(HiddenVisibility);
}

void UPanelSpaceWidget::OnProcessPanel_Implementation(UPanelSlot* PanelSlot)
{
	if (const auto CanvasSlot = Cast<UCanvasPanelSlot>(PanelSlot))
	{
		CanvasSlot->SetAnchors({0, 0, 1, 1});
	}
	else if (const auto HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(PanelSlot))
	{
		HorizontalBoxSlot->SetHorizontalAlignment(HAlign_Fill);
		HorizontalBoxSlot->SetVerticalAlignment(VAlign_Fill);
	}
	else if (const auto VerticalBoxSlot = Cast<UVerticalBoxSlot>(PanelSlot))
	{
		VerticalBoxSlot->SetHorizontalAlignment(HAlign_Fill);
		VerticalBoxSlot->SetVerticalAlignment(VAlign_Fill);
	}
	else if (const auto OverlaySlot = Cast<UOverlaySlot>(PanelSlot))
	{
		OverlaySlot->SetHorizontalAlignment(HAlign_Fill);
		OverlaySlot->SetVerticalAlignment(VAlign_Fill);
	}
}

void UPanelSpaceWidget::AddPanel(UUIPanelWidget* Panel)
{
	if (!IsValid(Space)) PIE_Error("NotPanelWidget", "RootWidget is not PanelWidget. Error Class:" + GetName()); 
	else
	{
		OnProcessPanel(Space->AddChild(Panel));
		// if (!Panels.Find(Panel)) Panels.Add(Panel);
	}
}
