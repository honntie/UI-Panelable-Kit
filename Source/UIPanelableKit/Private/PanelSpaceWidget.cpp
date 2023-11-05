// Fill out your copyright notice in the Description page of Project Settings.


#include "PanelSpaceWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelWidget.h"


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
	if (Panels.Num() == 0) SetHidden(HiddenVisibility);
}

void UPanelSpaceWidget::AddPanel(UUIPanelWidget* Panel)
{
	if (!IsValid(Space)) PIE_Error("NotPanelWidget", "RootWidget is not PanelWidget. Error Class:" + GetName()); 
	else
	{
		Cast<UCanvasPanelSlot>(Space->AddChild(Panel))->SetAnchors({0, 0, 1, 1});
		// if (!Panels.Find(Panel)) Panels.Add(Panel);
	}
}
