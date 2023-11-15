// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PanelSpaceWidget.h"
#include "PanelControllerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpaceChagedDelegate);


UCLASS(DisplayName="Panel Controller", ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UIPANELABLEKIT_API UPanelControllerComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region 只可编辑的变量
private:
	/// Describe | 面板空间的类型 \n
	UPROPERTY(EditDefaultsOnly, meta=(Category="UI Panelable Kit | Panel Controller"))
	TSubclassOf<UPanelSpaceWidget> TargetSpace;
#pragma endregion
	
#pragma region 蓝图变量
public:	
	/// Describe | 显示面板的Widget空间 \n
	UPROPERTY(BlueprintReadWrite, BlueprintSetter=SetPanelSpace, meta=(Category="UI Panelable Kit | Panel Controller"))
	UPanelSpaceWidget* PanelSpace;

	/// Describe | 面板空间激活时触发 \n
	UPROPERTY(BlueprintAssignable, meta=(Category="UI Panelable Kit | Panel Controller"))
	FOnSpaceChagedDelegate OnSpaceEnabled;

	/// Describe | 面板空间关闭时触发
	UPROPERTY(BlueprintAssignable, meta=(Category="UI Panelable Kit | Panel Controller"))
	FOnSpaceChagedDelegate OnSpaceDisabled;
	
protected:
	/// Describe | 记录所有面板的地方 \n
	UPROPERTY(BlueprintReadOnly, meta=(Category="UI Panelable Kit | Panel Controller"))
	TMap<TSubclassOf<UUIPanelWidget>, UUIPanelWidget*> PanelPool;
#pragma endregion
	
#pragma region 蓝图函数
public:
	/// Describe | SpaceWidget的Setter \n
	/// Space | 设置对象 \n
	UFUNCTION(BlueprintCallable, BlueprintSetter)
	virtual void SetPanelSpace(UPanelSpaceWidget* Space); 
	
	/// Describe | 手动注册面板, 调用时不再需要自动创建 \n
	/// Panel | 加入注册的面板 \n
	/// Return | 是否注册成功 (不存在同类型面板)
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | Panel Controller"))
	bool RegisterPanel(UUIPanelWidget* Panel);

	/// Describe | 注册面板并覆盖同类型面板, 调用时不再需要自动创建 \n
	/// Panel | 加入注册的面板 \n
	/// Return | 是否覆盖注册成功 (不存在面板), 如果false则不触发注册事件
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | Panel Controller"))
	bool RegisterPanelForcibly(UUIPanelWidget* Panel);
	
	/// Describe | 从该组件注销面板 \n
	/// Panel | 需要注销的面板 \n
	/// Return | 面板是否在组件中 \n
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | Panel Controller"))
	bool LogoutPanel(UUIPanelWidget* Panel);
	
	/// Describe | 显示指定面板 \n
	/// PanelTarget | 显示的对象 \n
	/// Return | 显示的面板 \n
	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType = "PanelTarget", Category="UI Panelable Kit | Panel Controller"))
	UUIPanelWidget* PushUI(TSubclassOf<UUIPanelWidget> PanelTarget);

	/// Describe | 关闭最顶层面板 \n
	UFUNCTION(BlueprintCallable, meta=(Category="UI Panelable Kit | Panel Controller"))
	void PopUI(bool IsLogout = false);
#pragma endregion

#pragma region 重载函数
public:
	// Sets default values for this component's properties
	UPanelControllerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
#pragma endregion 
	
#pragma region C++部分
private:
	/// Describe | 获取面板, 如果面板不存在则自动创建到PanelSpace里 \n
	/// PanelTarget | 需要获取的面板类型 \n
	/// Return | 面板类型 \n
	UUIPanelWidget* GetPanelLazily(TSubclassOf<UUIPanelWidget> PanelTarget);

	/// Describe | 初始化面板 \n
	/// Panel | 面板对象 \n
	void InitPanel(UUIPanelWidget* Panel);
#pragma endregion
};
