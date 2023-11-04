// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIPanelWidget.h"
#include "PanelSpaceWidget.generated.h"

DECLARE_DELEGATE(FOnChangedActivedDelegate)



UCLASS(DisplayName="Panel Space")
class UIPANELABLEKIT_API UPanelSpaceWidget : public UUIPanelWidget
{
	GENERATED_BODY()
	
#pragma region 蓝图变量
public:
	/// Describe | 空间显示时的枚举值 \n
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Category="UI Panelable Kit | Panel Space"))
	ESlateVisibility DisplayVisibility = ESlateVisibility::Visible;
	
	/// Describe | 空间隐藏时的枚举值 \n
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Category="UI Panelable Kit | Panel Space"))
	ESlateVisibility HiddenVisibility = ESlateVisibility::Collapsed;
	
protected:
	/// Describe | 当前已显示的所有面板, 索引越小面板越靠后 \n
	UPROPERTY(BlueprintReadWrite, meta=(Category="UI Panelable Kit | Panel Space"))
	TArray<UUIPanelWidget*> Panels;
#pragma endregion 

#pragma region 重写虚函数
public:
	/// Describe | 初始化时获取根PanelWidget \n
	virtual void NativeOnInitialized() override;

	/// Describe | 显示时回调 \n
	void OnShowed_Implementation() override;

	/// Describe | 所有面板隐藏时回调 \n
	void OnHided_Implementation() override;
#pragma endregion 

#pragma region 蓝图函数
public:
	/// Describe | 显示面板, 显示完成后会加进Panels并成为新的TopPanel \n
	/// Panel | 面板对象 \n
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | Panel Space"))
	void ShowPanel(UUIPanelWidget* Panel);
	
	/// Describe | 隐藏面板， 隐藏前将自身从Panels删除 \n
	/// Panel | 面板对象 \n
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | Panel Space"))
	void HidePanel(UUIPanelWidget* Panel);

	/// Describe | 获取当前最顶层的面板, 也就是Panels的最末端 \n
	/// Return | 返回面板 \n
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(Category="UI Panelable Kit | Panel Space"))
	UUIPanelWidget* GetTopPanel() const { return Panels.Num() > 0 ? Panels.Last(0):nullptr; }
#pragma endregion

#pragma region 蓝图可重载函数
public:
	/// Describe | 显示面板前的事件 \n
	/// Target | 需显示的面板 \n
	/// Return | 面板的显示属性 \n
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Panelable Kit | Panel Space"))
	ESlateVisibility InShowVisibility(UUIPanelWidget* Target);
	virtual ESlateVisibility InShowVisibility_Implementation(UUIPanelWidget* Target) { return ESlateVisibility::Visible; }
	
	/// Describe | 隐藏面板前的事件 \n
	/// Target | 需隐藏的面板 \n
	/// Return | 面板的隐藏属性 \n
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Panelable Kit | Panel Space"))
	ESlateVisibility InHideVisibility(UUIPanelWidget* Target);
	virtual ESlateVisibility InHideVisibility_Implementation(UUIPanelWidget* Target) { return ESlateVisibility::Collapsed; }
#pragma endregion

#pragma region C++部分
public:
	/// Describe | 激活委托 \n
	FOnChangedActivedDelegate OnEnabled;
	
	/// Describe | 关闭委托 \n
	FOnChangedActivedDelegate OnDisabled;
	
	/// Describe | 将新的面板加入到当前的面板空间 \n
	/// Panel | 面板对象 \n
	void AddPanel(UUIPanelWidget* Panel);

private:
	/// Describe | 存放面板地方 \n
	UPanelWidget* Space;

#pragma endregion 
};


/// Describe | 输出错误到MessageLog的Play In Editor \n
/// Title | 前缀消息 \n
/// Info | 具体消息 \n
void PIE_Error(const FString& Title, const FString& Info);
