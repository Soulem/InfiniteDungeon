// Fill out your copyright notice in the Description page of Project Settings.


#include "TriFloor.h"

ATriFloor::ATriFloor() {
	FTransform zeroPos;
	zeroPos.SetLocation(FVector{ 0.0f, 0.0f, 0.0f });
	zeroPos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 0.0f }));
}

ATriFloor::~ATriFloor() {

}

// Called when the game starts or when spawned
void ATriFloor::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void ATriFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}