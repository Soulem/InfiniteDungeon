// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "HexRoom.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class INFINITEDUNGEON_API AHexRoom : public ARoom
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	AHexRoom();
	~AHexRoom();
	virtual void Tick(float DeltaTime) override;
	void SetTrapByType(TrapTypeEnum _roomTrapType) override;
};
