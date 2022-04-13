// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStats.h"

// Sets default values for this component's properties
UPlayerStats::UPlayerStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	health_max = health = 100;
	health = health_max;
	playerType = PlayerTypeEnum::NO_PLAYERTYPE;
	roomCountByType.Add(RoomShapeEnum::TRI, 0);
	roomCountByType.Add(RoomShapeEnum::SQU, 0);
	roomCountByType.Add(RoomShapeEnum::HEX, 0);
	// ...
}


// Called when the game starts
void UPlayerStats::BeginPlay()
{
	Super::BeginPlay();

	
	// ...
	
}


// Called every frame
void UPlayerStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

