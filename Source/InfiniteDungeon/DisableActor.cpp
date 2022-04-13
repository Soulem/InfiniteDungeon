// Fill out your copyright notice in the Description page of Project Settings.


#include "DisableActor.h"

// Sets default values
ADisableActor::ADisableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//bOverrideTick = !PrimaryActorTick.bCanEverTick;
}

ADisableActor::~ADisableActor() {

}

// Called when the game starts or when spawned
void ADisableActor::BeginPlay()
{
	Super::BeginPlay();
	bOverrideTick = !PrimaryActorTick.bCanEverTick;
}

// Called every frame
void ADisableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADisableActor::SetActive(bool _bActive) {
	if (bOverrideTick)
		SetActorTickEnabled(false);
	else
		SetActorTickEnabled(_bActive);
	SetActorHiddenInGame(!_bActive);
	SetActorEnableCollision(_bActive);
}
