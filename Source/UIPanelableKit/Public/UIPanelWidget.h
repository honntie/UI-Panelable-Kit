// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Containers/Array.h"
#include "UIPanelWidget.generated.h"

class UPanelController;

UENUM(BlueprintType, meta=(Category="UI Panelable Kit | Type"))
enum class EPanelState : uint8
{
	Display,
	Hidden
};

UCLASS(DisplayName="UI Panel")
class UIPANELABLEKIT_API UUIPanelWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region 蓝图变量
public:
	UPROPERTY(BlueprintReadOnly, meta=(Category="UI Panel"))
	EPanelState State = EPanelState::Hidden;
#pragma endregion 
	
#pragma region 蓝图函数
public:
	/// @description 获取控制面板的组件 \n
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(Category="UI Panelable Kit | UI Panel"))
	UPanelController* GetController() const;

	/// @description 设置显示状态, 同时回调OnShow \n
	/// @param ShowVisibility 显示状态的数值 \n
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | UI Panel"))
	void SetShow(ESlateVisibility ShowVisibility);

	/// @description 设置隐藏状态, 同时回调OnHide \n
	/// @param HiddenVisibility 隐藏状态的数值 \n
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | UI Panel"))
	void SetHidden(ESlateVisibility HiddenVisibility);
#pragma endregion 
	
#pragma region 蓝图可重载函数
public:
	/// @description 显示时回调的函数（仅触发和蓝图继承用） \n
	/// @param OriginalVisibility 触发时设置的值 \n
	/// @return 最终效果的值
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Panelable Kit | UI Panel"))
	ESlateVisibility OnShow(ESlateVisibility OriginalVisibility);

	/// @description 隐藏时回调的函数（仅触发和蓝图继承用） \n
	/// @param OriginalVisibility 触发时设置的值 \n
	/// @return 最终效果的值
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Panelable Kit | UI Panel"))
	ESlateVisibility OnHide(ESlateVisibility OriginalVisibility);
#pragma endregion 
	
#pragma region C++部分
protected:
	/// @description 控制面板 \n
	// ReSharper disable once CppUE4ProbableMemoryIssuesWithUObject
	UPanelController* SpaceController;

	/// @description 显示时回调的函数（仅C++继承用） \n
	/// @param ShowVisibility 触发时设置的值，如果希望面板有特殊效果可修改此值 \n
	virtual void OnShow_Native(ESlateVisibility& ShowVisibility);
	
	/// @description 隐藏时回调的函数（仅C++继承用） \n
	/// @param HideVisibility 触发时设置的值，如果希望面板有特殊效果可修改此值 \n
	virtual void OnHide_Native(ESlateVisibility& HideVisibility);
	
	/// @description 此函数仅声明，需要重写OnShow_Native \n
	/// @param OriginalVisibility 此函数仅声明，需要重写OnShow_Native \n
	/// @return 此函数仅声明，需要重写OnShow_Native
	virtual ESlateVisibility OnShow_Implementation(ESlateVisibility OriginalVisibility);
	
	/// @description 此函数仅声明，需要重写OnHide_Native \n
	/// @param OriginalVisibility 此函数仅声明，需要重写OnHide_Native \n
	/// @return 此函数仅声明，需要重写OnHide_Native
	virtual ESlateVisibility OnHide_Implementation(ESlateVisibility OriginalVisibility);
	
public:
	/// @description 设置控制面板的组件 \n
	/// @param Owner 控制面板 \n
	void SetController(UPanelController* Owner);
#pragma endregion 

};
