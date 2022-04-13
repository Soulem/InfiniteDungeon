// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "TriRoom.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class INFINITEDUNGEON_API ATriRoom : public ARoom
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	ATriRoom();

	~ATriRoom();

	virtual void Tick(float DeltaTime) override;
	void SetTrapByType(TrapTypeEnum _roomTrapType) override;
};
