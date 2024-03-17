// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Containers/Map.h"
#include "PanelSpaceWidget.h"
#include "PanelController.generated.h"


UCLASS(Blueprintable, DisplayName="Panel Controller")
class UIPANELABLEKIT_API UPanelController : public UPrimaryDataAsset
{
	GENERATED_BODY()

#pragma region 只可编辑的变量
private:
	/// @description 面板空间的类型 \n
	UPROPERTY(EditDefaultsOnly, meta=(Category="UI Panelable Kit | Panel Controller"))
	TSubclassOf<UPanelSpaceWidget> DefaultSpace = TSubclassOf<UPanelSpaceWidget>();

	/// @description 初始化时显示的面板，Push顺序为数组正序 \n
	UPROPERTY(EditDefaultsOnly, meta=(Category="UI Panelable Kit | Panel Controller"))
	TSet<TSubclassOf<UUIPanelWidget>> InitPushPanels;
#pragma endregion

#pragma region 蓝图变量
public:
	/// @description 默认显示面板的Widget空间，空间已被释放或者控制还未使用时可以重新设置，否则其Setter将会失效，如果第一次Getter则会根据TargetSpace生成空间 \n
	UPROPERTY(BlueprintReadWrite, BlueprintSetter=SetPanelSpace, BlueprintGetter=GetPanelSpace, meta=(Category="UI Panelable Kit | Panel Controller"))
	UPanelSpaceWidget* PanelSpace = nullptr;

protected:
	/// @description 记录所有面板的地方 \n
	UPROPERTY(BlueprintReadOnly, meta=(Category="UI Panelable Kit | Panel Controller"))
	TMap<TSubclassOf<UUIPanelWidget>, UUIPanelWidget*> PanelPool;
#pragma endregion

#pragma region 蓝图函数
public:
	/// @description 初始化，会将SpacePanel和InitPushPanels构建。如果SpacePanel已被存在则不会再次初始化 \n
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | Panel Controller"))
	void Init();

	/// @description 移除控制器和SpacePanel的所有面板 \n
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | Panel Controller"))
	void Reset();
	
	/// @description 手动注册面板, 调用时不再需要自动创建 \n
	/// @param Panel 加入注册的面板 \n
	/// @return 是否注册成功 (不存在同类型面板)
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | Panel Controller"))
	bool RegisterPanel(UUIPanelWidget* Panel);

	/// @description 注册面板并覆盖同类型面板, 调用时不再需要自动创建 \n
	/// @param Panel 加入注册的面板 \n
	/// @return 是否覆盖注册成功 (不存在面板), 如果false则不触发注册事件
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | Panel Controller"))
	bool RegisterPanelForcibly(UUIPanelWidget* Panel);

	/// @description 从该组件注销面板 \n
	/// @param Panel 需要注销的面板 \n
	/// @return 面板是否在组件中 \n
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | Panel Controller"))
	bool LogoutPanel(UUIPanelWidget* Panel);

	/// @description 显示指定面板 \n
	/// @param PanelTarget 显示的对象 \n
	/// @return 显示的面板 \n
	UFUNCTION(BlueprintCallable,
		meta=(DeterminesOutputType = "PanelTarget", Category="UI Panelable Kit | Panel Controller"))
	UUIPanelWidget* PushUI(TSubclassOf<UUIPanelWidget> PanelTarget);

	/// @description 关闭最顶层面板 \n
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | Panel Controller"))
	void PopUI(bool IsLogout = false);
#pragma endregion

#pragma region C++部分
public:
	/// @description SpaceWidget的Setter \n
	/// @param Space 设置对象 \n
	UFUNCTION(BlueprintSetter)
	void SetPanelSpace(UPanelSpaceWidget* Space);
	
	/// @description SpaceWidget的Getter \n
	/// @return 返回对象 \n
	UFUNCTION(BlueprintGetter)
	UPanelSpaceWidget* GetPanelSpace();

private:
	/// @description 获取面板, 如果面板不存在则自动创建到PanelSpace里 \n
	/// @param PanelTarget 需要获取的面板类型 \n
	/// @return 面板类型 \n
	UUIPanelWidget* GetPanelLazily(TSubclassOf<UUIPanelWidget> PanelTarget);

	/// @description 初始化面板 \n
	/// @param Panel 面板对象 \n
	void InitPanel(UUIPanelWidget* Panel);
#pragma endregion
};
