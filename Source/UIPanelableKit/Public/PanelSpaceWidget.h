// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIPanelWidget.h"
#include "PanelSpaceWidget.generated.h"



UCLASS(DisplayName="Panel Space")
class UIPANELABLEKIT_API UPanelSpaceWidget : public UUIPanelWidget
{
	GENERATED_BODY()
	
#pragma region 蓝图变量
protected:
	/// @description 默认创建的控制器类型 \n
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Category="UI Panelable Kit | Panel Space"))
	TSubclassOf<UPanelController> DefaultUser;

	/// @description 使用自身的控制器，如果不存在则会自动创建一个 \n
	UPROPERTY(BlueprintReadWrite,BlueprintSetter=SetUser,BlueprintGetter=GetUser, meta=(Category="UI Panelable Kit | Panel Space"))
	UPanelController* User = nullptr;
	
	/// @description 当前已显示的所有面板, 索引越小面板越靠后 \n
	UPROPERTY(BlueprintReadOnly, meta=(Category="UI Panelable Kit | Panel Space"))
	TArray<UUIPanelWidget*> Panels;
#pragma endregion 

#pragma region 重写虚函数
public:
	/// @description 初始化时获取根PanelWidget \n
	virtual void NativeOnInitialized() override;
#pragma endregion 

#pragma region 蓝图函数
public:
	/// @description 显示面板, 显示完成后会加进Panels并成为新的TopPanel \n
	/// @param Panel 面板对象 \n
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | Panel Space"))
	void ShowPanel(UUIPanelWidget* Panel);
	
	/// @description 隐藏面板， 隐藏前将自身从Panels删除 \n
	/// @param Panel 面板对象 \n
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | Panel Space"))
	void HidePanel(UUIPanelWidget* Panel);

	/// @description 获取当前最顶层的面板, 也就是Panels的最末端 \n
	/// @return 返回面板 \n
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(Category="UI Panelable Kit | Panel Space"))
	UUIPanelWidget* GetTopPanel() const;
#pragma endregion

#pragma region 蓝图可重载函数
public:
	/// @description 显示最底层面板事件，触发ShowPanel时如果Panels为空则触发 \n
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Panelable Kit | Panel Space"))
	void OnEnable();

	/// @description 隐藏所有面板事件，当Panels为空后触发 \n
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Panelable Kit | Panel Space"))
	void OnDisable();
	
	/// @description 新增面板时对面板的处理, 默认把面板大小覆盖到全屏 (当前默认仅支持CanvasPanel, HorizontalBox, VerticalBox, Overlay, 其他情况请自行重写覆盖该函数) \n
	/// @param PanelSlot 被添加面板的插槽 \n
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Panelable Kit | Panel Space"))
	void OnPanelProcess(UPanelSlot* PanelSlot);

	/// @description 显示面板前的事件 \n
	/// @param Target 需显示的面板 \n
	/// @return 面板的显示属性 \n
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Panelable Kit | Panel Space"))
	ESlateVisibility OnPanelShow(UUIPanelWidget* Target);

	/// @description 隐藏面板前的事件 \n
	/// @param Target 需隐藏的面板 \n
	/// @return 面板的隐藏属性 \n
	UFUNCTION(BlueprintNativeEvent, meta=(Category="UI Panelable Kit | Panel Space"))
	ESlateVisibility OnPanelHide(UUIPanelWidget* Target);
#pragma endregion

#pragma region C++部分
public:
	/// @description 将新的面板加入到当前的面板空间 \n
	/// @param Panel 面板对象 \n
	void AddPanel(UUIPanelWidget* Panel);

	/// @description 获得使用自身空间的控制器 \n
	/// @return 返回控制器
	UFUNCTION(BlueprintGetter)
	UPanelController* GetUser();

	/// @description 设置新的控制器，如果设置之前自身已被使用则无法设置 \n
	/// @param Target 新的控制器 \n
	UFUNCTION(BlueprintSetter)
	void SetUser(UPanelController* Target);

private:
	/// @description 存放面板地方 \n
	// ReSharper disable once CppUE4ProbableMemoryIssuesWithUObject
	UPanelWidget* Space;

#pragma endregion 
};


/// @description 输出错误到MessageLog的Play In Editor \n
/// @param Title 前缀消息 \n
/// @param Info 具体消息 \n
void PIE_Error(const FString& Title, const FString& Info);
