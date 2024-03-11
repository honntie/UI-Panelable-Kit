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

void UUIPanelWidget::OnShow_Native(ESlateVisibility& ShowVisibility)
{
}

void UUIPanelWidget::OnHide_Native(ESlateVisibility& HideVisibility)
{
}

ESlateVisibility UUIPanelWidget::OnShow_Implementation(ESlateVisibility OriginalVisibility)
{
	OnShow_Native(OriginalVisibility);
	return OriginalVisibility;
}

ESlateVisibility UUIPanelWidget::OnHide_Implementation(ESlateVisibility OriginalVisibility)
{
	OnHide_Native(OriginalVisibility);
	return OriginalVisibility;
}

void UUIPanelWidget::SetController(UPanelController* Owner)
{
	SpaceController = Owner;
}
