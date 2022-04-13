// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DisableActor.h"
#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "RoomTrigger.generated.h"


UENUM(Blueprintable, BlueprintType)
enum TrapTypeEnum {
	None					UMETA(DisplayName = "None"),
	Close_In				UMETA(DisplayName = "Close In"),
	NUM_TRAP_TYPES,
	RAND_TRAP_TYPES,
	NULL_TRAP_TYPES,
	Murder					UMETA(DisplayName = "Murder"),
	Floor_Vanish	        UMETA(DisplayName = "Floor Vanish"),
	Floor_Collapse			UMETA(DisplayName = "Floor Collapse"),
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class INFINITEDUNGEON_API ARoomTrigger : public ADisableActor
{
	GENERATED_BODY()
public:
	ARoomTrigger();
	~ARoomTrigger();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trap Trigger Variables")
		TEnumAsByte<TrapTypeEnum> trapType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trap Trigger Variables")
		UBoxComponent* trapTrigger;
};
