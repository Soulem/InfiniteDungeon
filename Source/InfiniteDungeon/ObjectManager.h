// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoomNode.h"
#include "Engine/GameInstance.h"
#include "ObjectManager.generated.h"

#define MAX_NUM_ROOMS 50

class AInfiniteLevel;

/**
 * 
 */
UCLASS()
class INFINITEDUNGEON_API UObjectManager : public UGameInstance
{
	GENERATED_BODY()
	
private:
	TMap<TEnumAsByte<RoomShapeEnum>, TArray<ARoomNode*>> roomsByShape;
	bool isInitialized = false;
	UObjectManager();
public:
	TMap<TEnumAsByte<RoomShapeEnum>, UClass*> roomClassesMap;
	ARoomNode* GetRoom(TEnumAsByte<RoomShapeEnum> _roomShape);

	~UObjectManager();

	void ReturnRoom(ARoomNode* _room);
	
	UFUNCTION(BlueprintCallable, Category = "Room Manager Functions")
		bool CheckListByShape(RoomShapeEnum _roomShape);

	UFUNCTION(BlueprintCallable, Category = "Room Manager Functions")
		void InitializeRoomManager(AInfiniteLevel* _level);
};
