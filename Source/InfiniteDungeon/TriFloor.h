// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Floor.h"
#include "TriFloor.generated.h"

/**
 * 
 */
UCLASS()
class INFINITEDUNGEON_API ATriFloor : public AFloor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	ATriFloor();
	~ATriFloor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
