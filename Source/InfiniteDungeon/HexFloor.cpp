// Fill out your copyright notice in the Description page of Project Settings.


#include "HexFloor.h"

AHexFloor::AHexFloor() {
	FTransform zeroPos;
	zeroPos.SetLocation(FVector{ 0.0f, 0.0f, 0.0f });
	zeroPos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 0.0f }));
}

AHexFloor::~AHexFloor() {

}

// Called when the game starts or when spawned
void AHexFloor::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AHexFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}