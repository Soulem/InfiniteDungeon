// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DisableActor.h"
#include "Components/TextRenderComponent.h"
#include "Wall.generated.h"

#define TRI_TO_TRI 3926.0f
#define TRI_TO_SQU 5363.0f
#define TRI_TO_HEX 7852.0f
#define SQU_TO_SQU 6800.0f
#define SQU_TO_HEX 9289.0f
#define HEX_TO_HEX 11778.0f
#define HEX_MIN_SPAWN_POINT 530.0f
#define HEX_MAX_SPAWN_POINT 1750.0f
#define SQU_MIN_SPAWN_POINT 530.0f
#define SQU_MAX_SPAWN_POINT 1400.0f
#define TRI_MIN_SPAWN_POINT 530.0f
#define TRI_MAX_SPAWN_POINT 600.0f
#define STAIRS_UP 865.0f
#define STAIRS_DOWN -845.0f
#define	VERTICAL -1710.0f

UENUM(Blueprintable, BlueprintType)
enum WallPositionEnum {
	Front			UMETA(DisplayName = "Front"),
	Front_Right		UMETA(DisplayName = "Front_Right"),
	Right			UMETA(DisplayName = "Right"),
	Back_Right		UMETA(DisplayName = "Back_Right"),
	Back			UMETA(DisplayName = "Back"),
	Back_Left		UMETA(DisplayName = "Back_Left"),
	Left			UMETA(DisplayName = "Left"),
	Front_Left		UMETA(DisplayName = "Front_Left"),
	Floor			UMETA(DisplayName = "Floor"),
	Ceiling			UMETA(DisplayName = "Ceiling"),
	NUM_WALLS,
	RAND_WALL,
	NULL_WALL
};

UENUM(Blueprintable, BlueprintType)
enum WallTypeEnum {
	Wall					UMETA(DisplayName = "Wall"),
	Floor_Ceiling			UMETA(DisplayName = "Floor Ceiling"),
	Wall_No_Exit			UMETA(DisplayName = "Wall_No_Exit"),
	Wall_Destructable		UMETA(DisplayName = "Wall_Destructable"),
	Wall_Murder_Holes		UMETA(DisplayName = "Wall_Murder_Holes"),
	NUM_WALL_TYPES,
	RAND_WALL_TYPES,
	NULL_WALL_TYPES
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class INFINITEDUNGEON_API AWall : public ADisableActor
{
	GENERATED_BODY()

public:
		// Sets default values for this actor's properties
		AWall();
		~AWall();

	UPROPERTY(BlueprintReadWrite, Category = "Collision")
		bool isConnected;

	UPROPERTY(BlueprintReadWrite, Category = "Collision")
		TEnumAsByte<WallPositionEnum> wallPosition;

	UPROPERTY(BlueprintReadWrite, Category = "Wall Variables")
		AActor* myParentRoom;

	UPROPERTY(BlueprintReadWrite, Category = "Wall Variables")
		UObject* myParentRoomNode;

	UPROPERTY(BlueprintReadWrite, Category = "Wall Variables")
		TEnumAsByte<WallTypeEnum> wallType;

	UPROPERTY(BlueprintReadWrite, Category = "Debug Wall Variables")
		UTextRenderComponent* roomNumber;

protected:
// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DebugUpdateRoomNumber(int RoomNumber);

	void ShowWall(bool _bShouldShow);
	void SetWallText(FString* _str);

	static TEnumAsByte<WallTypeEnum> GetRandomWallType();

	void SetWallCollision(bool _bHasCollision);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Trigger Functions")
		void CloseInWall();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Trigger Functions")
		void CollapseFloor();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Trigger Functions")
		void ShootFromWall();
};
