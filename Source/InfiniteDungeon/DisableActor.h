// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DisableActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INFINITEDUNGEON_API ADisableActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ADisableActor();
	~ADisableActor();

	bool bOverrideTick = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetActive(bool _bActive);
};
