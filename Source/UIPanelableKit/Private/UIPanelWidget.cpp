// Fill out your copyright notice in the Description page of Project Settings.


#include "UIPanelWidget.h"


UPanelController* UUIPanelWidget::GetController() const
{
	return SpaceController;
}

void UUIPanelWidget::SetShow(ESlateVisibility ShowVisibility)
{
	OnShow(ShowVisibility);
	SetVisibility(ShowVisibility);
	State = EPanelState::Display;
}

void UUIPanelWidget::SetHidden(ESlateVisibility HiddenVisibility)
{
	OnHide(HiddenVisibility);
	SetVisibility(HiddenVisibility);
	State = EPanelState::Hidden;
}

void UUIPanelWidget::OnRegistered_Implementation() {}

void UUIPanelWidget::OnLogouted_Implementation() {}

void UUIPanelWidget::OnShow_Implementation(ESlateVisibility& ShowVisibility) {}

void UUIPanelWidget::OnHide_Implementation(ESlateVisibility& HiddenVisibility) {}

void UUIPanelWidget::SetController(UPanelController* Owner)
{
	SpaceController = Owner;
}
