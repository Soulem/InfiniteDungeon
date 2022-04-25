// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ObjectManager.h"
#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "InfiniteLevel.generated.h"

UENUM(Blueprintable, BlueprintType)
enum LevelBuildEnum {
	STATIC_NUMBERD		UMETA(DisplayName = "STATIC_NUMBERD"),
	DYNAMIC_GENERATIONAL UMETA(DisplayName = "DYNAMIC_GENERATIONAL"),
	ONLINE			UMETA(DisplayName = "ONLINE"),
	NUM_LB,
	RAND_LB,
};

USTRUCT(Blueprintable, BlueprintType)
struct FNextRoomTransformData {
public:
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "Transform Data")
		TEnumAsByte<WallPositionEnum> newWall;

	UPROPERTY(BlueprintReadWrite, Category = "Transform Data")
		float magnitude;

	UPROPERTY(BlueprintReadWrite, Category = "Transform Data")
		float zRotation;

	UPROPERTY(BlueprintReadWrite, Category = "Transform Data")
		TMap<TEnumAsByte<WallPositionEnum>, AWall*> siblingWallsForRoom;
};

/**
 * 
 */
UCLASS()
class INFINITEDUNGEON_API AInfiniteLevel : public ALevelScriptActor
{
	GENERATED_BODY()

private:
	void SetStartNode(FTransform startingWorldPos);
	void CloseWalls();

public:
	UPROPERTY(BlueprintReadWrite, Category = "Level Variables")
		TArray<TEnumAsByte<RoomShapeEnum>> selectedRoomShapesArray;

	UPROPERTY(BlueprintReadWrite, Category = "Level Variables")
		UObjectManager* objectManager;

	UPROPERTY(BlueprintReadWrite, Category = "Level Variables")
		ARoomNode* startHere = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Level Variables")
		ARoomNode* playerNode = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Level Variables")
		ARoomNode* creationIterator = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Level Variables")
		TArray<ARoomNode*> roomArray;
	
	UPROPERTY(BlueprintReadOnly, Category = "Level Variables")
		TSet<ARoomNode*> roomsToDrawBuffer;

	UPROPERTY(BlueprintReadOnly, Category = "Level Variables")
		TMap<TEnumAsByte<RoomShapeEnum>, ARoomNode*> debugRoomMap;

	UPROPERTY(BlueprintReadWrite, Category = "Level Variables")
		TEnumAsByte<LevelBuildEnum> levelBuild;

	UPROPERTY(BlueprintReadOnly, Category = "Level Variables")
		int minNumRooms;

	UPROPERTY(BlueprintReadWrite, Category = "Level Variables")
		bool isInfinite;

	UPROPERTY(BlueprintReadOnly, Category = "Level Variables")
		int roomCounter;

	UPROPERTY(BlueprintReadOnly, category = "Level Data")
		int generations;

	UPROPERTY(BlueprintReadOnly, category = "Level Data")
		int depth;

	AInfiniteLevel();
	~AInfiniteLevel();

	UFUNCTION(BlueprintCallable, Category = "Level Functions")
		void AddRoomToLevel(TEnumAsByte<WallPositionEnum> _parentConnectedWall, TEnumAsByte<WallPositionEnum> _childConnectedWall, TEnumAsByte<RoomShapeEnum> roomShape, TEnumAsByte<RoomTypeEnum> _selectedRoomType, TMap<TEnumAsByte<WallPositionEnum>, ARoomNode*> _connectedRooms, FTransform& worldPos);

	UFUNCTION(BlueprintCallable, Category = "NameGeneratorBPLibrary")
		void SetCollisionRooms();
	UFUNCTION(BlueprintCallable, Category = "Level Functions")
		void SetCollisionRoomsVisibility(bool isVisible);
	/*UFUNCTION(BlueprintCallable, Category = "Level Functions")
		FRoomPair GetRoomClass(TMap<TEnumAsByte<RoomPoolEnum>, TSubclassOf<class ARoom>> selectableRoomMap, TEnumAsByte<RoomPoolEnum> selectableRoom, int RandMin = 0, int RandMaxOffset = 0);*/
	UFUNCTION(BlueprintCallable, Category = "Level Functions")
		void CreateLevelWithNumRooms(FTransform startingWorldPos, const int numRooms);
	UFUNCTION(BlueprintCallable, Category = "Level Functions")
		bool PlaceNewRoom(TEnumAsByte<RoomShapeEnum> parentRoomShape, TEnumAsByte<WallPositionEnum> parentWall, int roomIterator);
	

	UFUNCTION(BlueprintCallable, Category = "Level Functions")
		void RemoveRoomsFromRoomList();

	UFUNCTION(BlueprintCallable, Category = "Level Functions")
		void CreateLevelFromPlayer(FTransform startingWorldPos, int numGenerations);
	UFUNCTION(BlueprintCallable, Category = "Level Functions")
		void CreateLevelFromPlayerRecursive(ARoomNode* _playerNode, int generation, int itter);

	void SetMagnitudeAndNewWall(TEnumAsByte<RoomShapeEnum> _currRoomShape, TEnumAsByte<RoomShapeEnum> _nextRoomShape, TEnumAsByte<WallPositionEnum> _currWall, FNextRoomTransformData& transformData);
	void SetMagnitudeAndNewWallTRI(TEnumAsByte<RoomShapeEnum> _nextRoomShape, TEnumAsByte<WallPositionEnum> _currWall, FNextRoomTransformData& transformData);
	void SetMagnitudeAndNewWallSQU(TEnumAsByte<RoomShapeEnum> _nextRoomShape, TEnumAsByte<WallPositionEnum> _currWall, FNextRoomTransformData& transformData);
	void SetMagnitudeAndNewWallHEX(TEnumAsByte<RoomShapeEnum> _nextRoomShape, TEnumAsByte<WallPositionEnum> _currWall, FNextRoomTransformData& transformData);
};
