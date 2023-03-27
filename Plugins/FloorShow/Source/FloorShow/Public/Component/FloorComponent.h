// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "FloorComponent.generated.h"


/**
 * 楼层组件
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLOORSHOW_API UFloorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFloorComponent();

	//楼栋名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloorShow|FloorComponent")
	FString BuildingName;

	//楼层号
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloorShow|FloorComponent")
	int32 FloorIndex;

	//三维，二维空间切换时的曲线
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloorShow|FloorComponent")
	UCurveFloat* SpaceSwitchCurve;

	//透明度切换时的曲线
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloorShow|FloorComponent")
	UCurveFloat* TranspLerpCurve;

	//楼层抬升时的曲线
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloorShow|FloorComponent")
	UCurveFloat* LiftLerpCurve;

private:
	//此Component的拥有者
	UPROPERTY()
	AActor* OwnerActor = nullptr;

	UStaticMeshComponent* StaticMeshComponent = nullptr;

	//三维、二维切换时间轴
	UPROPERTY()
	UTimelineComponent* SpaceSwitchTimelineComp = nullptr;

	UPROPERTY()
	FOnTimelineFloat SpaceSwitchTickCallback;

	/**************楼层透明度切换相关**************/
	//透明度切换时间轴
	UPROPERTY()
	UTimelineComponent* TranspLerpTimelineComp = nullptr;
	UPROPERTY()
	FOnTimelineFloat TranspLerpTickCallback;
	//材质透明参数名称
	FName TranspParamName;
	//材质透明参数值
	float TranspParamValue;
	//当前透明参数值
	float CurTranspParamValue;
	//当前使用的材质参数集
	UMaterialParameterCollection* CurCollection;

	/**************楼层移动相关**************/
	//楼层原始位置
	FVector OriginLocation;
	//楼层目标抬升位置
	UPROPERTY(EditAnywhere, Category = "FloorShow|FloorComponent")
	FVector TargetLiftLocation;
	//楼层当前位置
	FVector CurLocation;
	//目标移动位置
	FVector TargetLocation;
	//楼层抬升时间轴
	UPROPERTY()
	UTimelineComponent* LiftLerpTimelineComp = nullptr;
	UPROPERTY()
	FOnTimelineFloat LiftLerpTickCallback;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * 二维，三维空间切换
	 *
	 * @param bSwitchToThreeDim	勾选切换到三维，不勾选切换到二维
	 */
	UFUNCTION()
	void SpaceSwitch(bool bSwitchToThreeDim);

	/**
	 * 设置楼层透明度
	 *
	 * @param ParameterName			参数名称
	 * @param Transparency			透明度
	 */
	UFUNCTION(BlueprintCallable, Category = "FloorShow|FloorComponent")
	void SetTransparent(FName ParameterName, float Transparency, bool bLerp);

	/**
	 * 楼层抬升
	 */
	UFUNCTION(BlueprintCallable, Category = "FloorShow|FloorComponent")
	void FloorLift(bool bReverse, bool bLerp);

private:
	/**
	 * 二维，三维空间切换具体逻辑
	 */
	UFUNCTION()
	void OnSpaceSwitchUpdate(float Alpha);

	/**
	 * 透明度切换 Lerp 具体逻辑
	 */
	UFUNCTION()
	void OnTranspLerpUpdate(float Alpha);

	/**
	 * 楼层抬升 Lerp 具体逻辑
	 */
	UFUNCTION()
	void OnLiftLerpUpdate(float Alpha);
};