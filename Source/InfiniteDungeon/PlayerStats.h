// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Room.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStats.generated.h"

UENUM(Blueprintable, BlueprintType)
enum  PlayerTypeEnum {
	TWO_HANDED		UMETA(DisplayName = "TWO_HANDED"),
	ONE_HANDED		UMETA(DisplayName = "ONE_HANDED"),
	DUAL_WIELD		UMETA(DisplayName = "DUAL_WIELD"),
	NO_PLAYERTYPE,
	NUM_PT,
	RAND_PT,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INFINITEDUNGEON_API UPlayerStats : public UActorComponent
{
	GENERATED_BODY()

private:
	TEnumAsByte<PlayerTypeEnum> playerType;

public:	
	// Sets default values for this component's properties
	UPlayerStats();

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
		int health;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
		int health_max;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
		TMap<TEnumAsByte<RoomShapeEnum>, int> roomCountByType;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
