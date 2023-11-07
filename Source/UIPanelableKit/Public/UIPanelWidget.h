// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PanelTypeLibrary.h"
#include "UIPanelWidget.generated.h"

class UPanelControllerComponent;


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
	/// Describe | 获取控制面板的组件 \n
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(Category="UI Panelable Kit | UI Panel"))
	UPanelControllerComponent* GetController() const { return SpaceController; }

	/// Describe | 设置显示状态, 同时回调OnShow \n
	/// Visibility | 显示状态的数值 \n
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | UI Panel"))
	void SetDisplay(ESlateVisibility DisplayerVisibility);

	/// Describe | 设置隐藏状态, 同时回调OnHided \n
	/// Visibility | 隐藏状态的数值 \n
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | UI Panel"))
	void SetHidden(ESlateVisibility HiddenVisibility);
#pragma endregion 
	
#pragma region 蓝图可重载函数
public:
	/// Describe | 在PanelController注册时触发 \n
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Panelable Kit | UI Panel"))
	void OnRegistered();
	virtual void OnRegistered_Implementation() {}

	/// Describe | 在PanelController注销时触发 \n
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Panelable Kit | UI Panel"))
	void OnLogouted();
	virtual void OnLogouted_Implementation() {}
	
	/// Describe | 显示时回调的函数 \n
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Panelable Kit | UI Panel"))
	void OnShowed();
	virtual void OnShowed_Implementation() {}

	/// Describe | 隐藏时回调的函数 \n
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Panelable Kit | UI Panel"))
	void OnHided();
	virtual void OnHided_Implementation() {}
#pragma endregion 
	
#pragma region C++部分
private:
	/// Describe | 控制面板 \n
	UPanelControllerComponent* SpaceController;

public:
	/// Describe | 设置控制面板的组件 \n
	/// Owner | 控制面板 \n
	void SetController(UPanelControllerComponent* Owner) { SpaceController = Owner; };
#pragma endregion 

};
