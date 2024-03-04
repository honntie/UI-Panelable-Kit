// Fill out your copyright notice in the Description page of Project Settings.


#include "PanelControllerComponent.h"

// #include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UPanelController::UPanelController()
{
	TargetSpace = TSubclassOf<UPanelSpaceWidget>();

	PanelSpace = nullptr;
}

bool UPanelController::RegisterPanel(UUIPanelWidget* Panel)
{
	UClass* PanelType = Panel->GetClass();
	if (PanelPool.Contains(PanelType)) return false;
	
	InitPanel(Panel);
	Panel->SetVisibility(ESlateVisibility::Collapsed);
	// UKismetSystemLibrary::PrintString(this, Panel->GetVisibility() == ESlateVisibility::Collapsed ? "Collapsed":"NotCollapsed");
	PanelPool.Add(PanelType, Panel);
	return true;
}

bool UPanelController::RegisterPanelForcibly(UUIPanelWidget* Panel)
{
	UClass* PanelType = Panel->GetClass();
	UUIPanelWidget** RefPanel = PanelPool.Find(PanelType);

	if (!RefPanel) InitPanel(Panel);
	else if (*RefPanel != Panel) InitPanel(Panel);
	else return false;
	
	Panel->SetVisibility(ESlateVisibility::Collapsed);
	// UKismetSystemLibrary::PrintString(this, Panel->GetVisibility() == ESlateVisibility::Collapsed ? "Collapsed":"NotCollapsed");
	PanelPool.Add(PanelType, Panel);
	return true;
}

bool UPanelController::LogoutPanel(UUIPanelWidget* Panel)
{
	if (!IsValid(PanelSpace))
	{
		PIE_Error("Invaild Panel Space", "Please use a vaild panel space. Error Class:" + GetName());
		return false;
	}
	
	if (PanelPool.Remove(Panel->GetClass()) == 0) return false;
	
	PanelSpace->RemoveFromParent();
	Panel->OnRegistered();
	Panel->SetController(nullptr);
	return true;
}

UUIPanelWidget* UPanelController::PushUI(TSubclassOf<UUIPanelWidget> PanelTarget)
{
	// SetOnView(true);
	if (!IsValid(PanelSpace))
	{
		PIE_Error("Invaild Panel Space", "Please use a vaild panel space. Error Class:" + GetName());
		return nullptr;
	}
	
	UUIPanelWidget* Target = GetPanelLazily(PanelTarget);
	PanelSpace->ShowPanel(Target);
	return Target;
}

void UPanelController::PopUI(bool IsLogout)
{
	if (!IsValid(PanelSpace))
	{
		PIE_Error("Invaild Panel Space", "Please use a vaild panel space. Error Class:" + GetName());
		return;
	}

	// 删除最后推出的面板
	UUIPanelWidget* Panel = PanelSpace->GetTopPanel();
	PanelSpace->HidePanel(Panel);
	if (IsLogout) LogoutPanel(Panel);
}

UUIPanelWidget* UPanelController::GetPanelLazily(TSubclassOf<UUIPanelWidget> PanelTarget)
{
	if (!IsValid(PanelSpace))
	{
		PIE_Error("Invaild Panel Space", "Please use a vaild panel space. Error Class:" + GetName());
		return nullptr;
	}
	
	UUIPanelWidget** RefPanel = PanelPool.Find(PanelTarget);
	UUIPanelWidget* Panel;
	if (RefPanel) Panel = *RefPanel;
	else
	{
		Panel = CreateWidget<UUIPanelWidget>(PanelSpace, PanelTarget);
		InitPanel(Panel);
		PanelPool.Add(PanelTarget, Panel);
	}
	return Panel;
}

void UPanelController::InitPanel(UUIPanelWidget* Panel)
{
	if (!IsValid(PanelSpace))
	{
		PIE_Error("Invaild Panel Space", "Please use a vaild panel space. Error Class:" + GetName());
		return;
	}
	
	Panel->SetController(this);
	PanelSpace->AddPanel(Panel);
	Panel->OnRegistered();
}

UPanelSpaceWidget* UPanelController::GetPanelSpace()
{
	if (!IsValid(PanelSpace))
	{
		if (TargetSpace != TSubclassOf<UPanelSpaceWidget>())
			SetPanelSpace(CreateWidget<UPanelSpaceWidget>(GetWorld(), TargetSpace));
		else SetPanelSpace(CreateWidget<UPanelSpaceWidget>(GetWorld()));
	}
	return PanelSpace;
}

void UPanelController::SetPanelSpace(UPanelSpaceWidget* Space)
{
	if (IsValid(PanelSpace)) return;

	// 注销上一个事件
	// if (PanelSpace)
	// {
	// 	PanelSpace->OnEnabled.Unbind();
	// 	PanelSpace->OnDisabled.Unbind();
	// 	PanelSpace->OnLogouted();
	// }

	// 注册当前的事件
	PanelSpace = Space;
	PanelSpace->OnEnabled.BindLambda([&](){ OnSpaceEnabled.Broadcast(); });
	PanelSpace->OnDisabled.BindLambda([&](){ OnSpaceDisabled.Broadcast(); });
	PanelSpace->OnRegistered();
}
