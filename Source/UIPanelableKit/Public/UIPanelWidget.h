// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PanelTypeLibrary.h"
#include "UIPanelWidget.generated.h"

class UPanelController;


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
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(Category="UI Layer Kit | UI Panel"))
	UPanelController* GetController() const;

	/// @description 设置显示状态, 同时回调OnShow \n
	/// @param ShowVisibility 显示状态的数值 \n
	UFUNCTION(BlueprintCallable, meta=(Category="UI Layer Kit | UI Panel"))
	void SetShow(ESlateVisibility ShowVisibility);

	/// @description 设置隐藏状态, 同时回调OnHide \n
	/// @param HiddenVisibility 隐藏状态的数值 \n
	UFUNCTION(BlueprintCallable, meta=(Category="UI Layer Kit | UI Panel"))
	void SetHidden(ESlateVisibility HiddenVisibility);
#pragma endregion 
	
#pragma region 蓝图可重载函数
public:
	/// @description 在PanelController注册时触发 \n
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Layer Kit | UI Panel"))
	void OnRegistered();

	/// @description 在PanelController注销时触发 \n
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Layer Kit | UI Panel"))
	void OnLogouted();
	
	/// @description 显示时回调的函数 \n
	/// @param ShowVisibility 触发时设置的值，如果希望面板有特殊效果可修改此值 \n
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Layer Kit | UI Panel"))
	void OnShow(UPARAM(ref)ESlateVisibility& ShowVisibility);

	/// @description 隐藏时回调的函数 \n
	/// @param HiddenVisibility 触发时设置的值，如果希望面板有特殊效果可修改此值 \n
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Layer Kit | UI Panel"))
	void OnHide(UPARAM(ref)ESlateVisibility& HiddenVisibility);
#pragma endregion 
	
#pragma region C++部分
protected:
	/// @description 控制面板 \n
	UPanelController* SpaceController;

public:
	/// @description 设置控制面板的组件 \n
	/// @param Owner 控制面板 \n
	void SetController(UPanelController* Owner);
#pragma endregion 

};
