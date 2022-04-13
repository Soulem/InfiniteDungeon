// Fill out your copyright notice in the Description page of Project Settings.


#include "SquFloor.h"

ASquFloor::ASquFloor() {
	FTransform zeroPos;
	zeroPos.SetLocation(FVector{ 0.0f, 0.0f, 0.0f });
	zeroPos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 0.0f }));
}

ASquFloor::~ASquFloor() {

}

// Called when the game starts or when spawned
void ASquFloor::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void ASquFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}