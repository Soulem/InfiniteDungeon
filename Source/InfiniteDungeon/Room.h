// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DisableActor.h"
#include "TriFloor.h"
#include "SquFloor.h"
#include "HexFloor.h"
#include "RoomTrigger.h"
#include "Room.generated.h"

UENUM(Blueprintable, BlueprintType)
enum RoomShapeEnum
{
	TRI					UMETA(DisplayName = "Triangle"),
	SQU					UMETA(DisplayName = "Square"),
	HEX					UMETA(DisplayName = "Hexagon"),
	NUM_ROOM_SHAPE,
	RAND_ROOM_SHAPE,
	NULL_ROOM_SHAPE
};

UENUM(Blueprintable, BlueprintType)
enum RoomTypeEnum {
	Normal					UMETA(DisplayName = "Normal"),
	Stairs_Ceiling			UMETA(DisplayName = "Stairs Ceiling"),
	Stairs_Both				UMETA(DisplayName = "Stairs Floor"),
	Hole_Floor				UMETA(DisplayName = "Hole Floor"),
	Hole_Ceiling			UMETA(DisplayName = "Hole Ceiling"),
	Hole_Both				UMETA(DisplayName = "Hole Both"),
	NUM_ROOMS_TYPES,
	RAND_ROOM_TYPES,
	NULL_ROOM_TYPES,
};
//Rope					UMETA(DisplayName = "Rope"),
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class INFINITEDUNGEON_API ARoom : public ADisableActor
{
	GENERATED_BODY()
	
protected:
	bool canFit = false;
	virtual void BeginPlay() override;

public:
	ARoom();

	~ARoom();

	TMap<TEnumAsByte<RoomShapeEnum>, UClass*> floorClassMap;
	
	TMap<TEnumAsByte<WallTypeEnum>, UClass*> wallClassesMap;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Room Variables")
		TEnumAsByte<RoomShapeEnum> roomShape;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room Variables")
		UChildActorComponent* trigger; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Room Variables")
		TEnumAsByte<RoomTypeEnum> roomType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Room Variables")
		TMap<TEnumAsByte<WallPositionEnum>, UChildActorComponent*> roomWalls;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Room Variables")
		TMap<TEnumAsByte<WallPositionEnum>, UChildActorComponent*> roomTrapWalls;

	UFUNCTION(BlueprintCallable, Category = "Room Functions")
		const bool GetCanFit() { return canFit; }

	UFUNCTION(BlueprintCallable, Category = "Trigger Functions")
		void CloseInWalls();

	UFUNCTION(BlueprintCallable, Category = "Trigger Functions")
		void ShootFromWalls();

	UFUNCTION(BlueprintCallable, Category = "Trigger Functions")
		void OnTriggerOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Collision Functions")
		void CheckCollision(TEnumAsByte<WallPositionEnum> _wallPosition);

	void RandomizeWalls(TArray<WallPositionEnum> _excludePositions = {});
	
	void PlayerEntersLeaves(bool _bIsLeaving);
	
	virtual void SetTrapByType(TrapTypeEnum _roomTrapType);
	virtual void SetRoomByType(RoomTypeEnum _roomType);

};
