// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriRoom.h"
#include "SquRoom.h"
#include "HexRoom.h"
#include "RoomNode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class INFINITEDUNGEON_API ARoomNode : public ADisableActor
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintReadWrite, Category = "Room Node Variables")
		ARoom* data;

	UPROPERTY(BlueprintReadWrite, Category = "Room Node Variables")
		TMap<TEnumAsByte<WallPositionEnum>, ARoomNode*> connectedRooms;

	UPROPERTY(BlueprintReadWrite, Category = "Room Node Variables")
		bool hasPlayerBeenHere = false;

	ARoomNode();
	~ARoomNode();
	void AddConnectRoomNode(WallPositionEnum _wall, ARoomNode* _newRoom);
	void CreateRoom(UWorld* world, FActorSpawnParameters _spawnInfo, TSubclassOf<class ARoom> room, TEnumAsByte<RoomShapeEnum> roomShape, FTransform& worldPos);
	
	UFUNCTION(BlueprintCallable, Category = "Room Node Functions")
		void PlayerEntersLeaves(bool _bIsLeaving);
};
