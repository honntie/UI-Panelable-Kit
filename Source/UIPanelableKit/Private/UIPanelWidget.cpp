// Fill out your copyright notice in the Description page of Project Settings.


#include "UIPanelWidget.h"


void UUIPanelWidget::SetDisplay(ESlateVisibility DisplayerVisibility)
{
	SetVisibility(DisplayerVisibility);
	State = EPanelState::Display;
	OnShowed();
}

void UUIPanelWidget::SetHidden(ESlateVisibility HiddenVisibility)
{
	SetVisibility(HiddenVisibility);
	State = EPanelState::Hidden;
	OnHided();
}
