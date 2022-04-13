// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "SquRoom.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class INFINITEDUNGEON_API ASquRoom : public ARoom
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	ASquRoom();
	~ASquRoom();

	void SetTrapByType(TrapTypeEnum _roomTrapType) override;
	virtual void Tick(float DeltaTime) override;
};
