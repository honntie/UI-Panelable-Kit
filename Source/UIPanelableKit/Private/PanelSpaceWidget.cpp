// Fill out your copyright notice in the Description page of Project Settings.


#include "PanelSpaceWidget.h"
#include "..\Public\PanelController.h"
#include "Components/PanelSlot.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/OverlaySlot.h"
#include "Components/PanelWidget.h"
#include "Components/VerticalBoxSlot.h"

#define CHECK_ROOT_PANEL(Result) \
	if (!IsValid(Space)) \
	{ \
		PIE_Error("NotPanelWidget", "RootWidget is not PanelWidget. Error Class:" + GetName()); \
		return Result; \
	}

void PIE_Error(const FString& Title, const FString& Info)
{
	FMessageLog("PIE").Error(FText::FromString(Title + ": " + Info));
}

void UPanelSpaceWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Space = Cast<UPanelWidget>(GetRootWidget());
	
	CHECK_ROOT_PANEL()
}

void UPanelSpaceWidget::ShowPanel(UUIPanelWidget* Panel)
{
	// 未显示空间情况
	if (State != EPanelState::Display) SetShow(GetVisibility());
	
	if (GetTopPanel() == Panel) return;
	
	Panel->SetShow(OnShowPanel(Panel));
	Panels.Remove(Panel);
	Panels.Add(Panel);
}

void UPanelSpaceWidget::HidePanel(UUIPanelWidget* Panel)
{
	if (Panels.Remove(Panel) == 0) return;
	Panel->SetHidden(OnHidePanel(Panel));

	// 没有面板显示情况
	if (Panels.Num() == 0) SetHidden(GetVisibility());
}

UUIPanelWidget* UPanelSpaceWidget::GetTopPanel() const
{
	return Panels.Num() > 0 ? Panels.Last(0) : nullptr;
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

ESlateVisibility UPanelSpaceWidget::OnShowPanel_Implementation(UUIPanelWidget* Target)
{
	return ESlateVisibility::Visible;
}

ESlateVisibility UPanelSpaceWidget::OnHidePanel_Implementation(UUIPanelWidget* Target)
{
	return ESlateVisibility::Collapsed;
}

void UPanelSpaceWidget::AddPanel(UUIPanelWidget* Panel)
{
	CHECK_ROOT_PANEL()
	OnProcessPanel(Space->AddChild(Panel));
}

UPanelController* UPanelSpaceWidget::GetUser()
{
	if (User == nullptr) SetUser(NewObject<UPanelController>(this));
	return User;
}

void UPanelSpaceWidget::SetUser(UPanelController* Target)
{
	if (Target == User) return;
	else if (IsValid(Target) && IsValid(User)) return;
	
	User = Target;
	Target->SetPanelSpace(this);
 }
