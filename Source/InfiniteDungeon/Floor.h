// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Wall.h"
#include "Floor.generated.h"

UENUM(Blueprintable, BlueprintType)
enum FloorPartEnum {
	Solid				UMETA(DisplayName = "Solid"),
	Exit				UMETA(DisplayName = "Exit"),
	Stairs				UMETA(DisplayName = "Stairs"),
	NUM_FLOOR_PARTS,
	RAND_FLOOR_PART,
	NULL_FLOOR_PART,
	Hole				UMETA(DisplayName = "Hole"),
};
/**
 * 
 */
UCLASS()
class INFINITEDUNGEON_API AFloor : public AWall
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Variables")
	TMap<TEnumAsByte<FloorPartEnum>, UStaticMeshComponent*> floorMap;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Variables")
	TMap<TEnumAsByte<FloorPartEnum>, UStaticMeshComponent*> partMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trap Trigger Variables")
	USphereComponent* floorExit;

	AFloor();
	~AFloor();
	
	virtual void ShowFloor(TArray<FloorPartEnum> _floorPartsToShow);
	virtual void ShowPart(TArray<FloorPartEnum> _floorPartsToShow);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
