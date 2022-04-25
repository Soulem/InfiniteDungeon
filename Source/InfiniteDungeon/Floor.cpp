// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor.h"

AFloor::AFloor(){
	wallType = WallTypeEnum::Floor_Ceiling;

	FTransform zeroPos;
	zeroPos.SetLocation(FVector{ 0.0f, 0.0f, 458.0f });
	zeroPos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 0.0f }));
	zeroPos.SetScale3D(FVector{14.0f, 14.0f, 14.0f});
	floorExit = CreateDefaultSubobject<USphereComponent>(TEXT("Floor Exit"), true);
	floorExit->SetWorldTransform(zeroPos);
	floorExit->SetActive(false);
	floorExit->SetHiddenInGame(true);
	floorExit->SetVisibility(false);
	floorExit->SetComponentTickEnabled(false);
	floorExit->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

AFloor::~AFloor(){

}

void AFloor::ShowFloor(TArray<FloorPartEnum> _floorPartsToShow) {
	TArray<TEnumAsByte<FloorPartEnum>> tempArray;
	floorMap.GenerateKeyArray(tempArray);
	for (TEnumAsByte<FloorPartEnum> key : tempArray) {
		if (floorMap[key] == nullptr)
			floorMap.Remove(key);
		else if (_floorPartsToShow.Contains(key)){
			floorMap[key]->SetActive(true);
			floorMap[key]->SetHiddenInGame(false);
			floorMap[key]->SetVisibility(true);
			floorMap[key]->SetComponentTickEnabled(true);
			floorMap[key]->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else
		{
			floorMap[key]->SetActive(false);
			floorMap[key]->SetHiddenInGame(true);
			floorMap[key]->SetVisibility(false);
			floorMap[key]->SetComponentTickEnabled(false);
			floorMap[key]->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
	if (_floorPartsToShow.Contains(FloorPartEnum::Solid)) {
		isConnected = true;
		floorExit->SetActive(false);
		floorExit->SetHiddenInGame(true);
		floorExit->SetVisibility(false);
		floorExit->SetComponentTickEnabled(false);
		floorExit->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else {
		isConnected = false;
		floorExit->SetActive(true);
		floorExit->SetHiddenInGame(false);
		floorExit->SetVisibility(true);
		floorExit->SetComponentTickEnabled(true);
		floorExit->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void AFloor::ShowPart(TArray<FloorPartEnum> _floorPartsToShow) {
	TArray<TEnumAsByte<FloorPartEnum>> tempArray;
	partMap.GenerateKeyArray(tempArray);
	for (TEnumAsByte<FloorPartEnum> key : tempArray) {
		if (partMap[key] == nullptr)
			partMap.Remove(key);
		else if (_floorPartsToShow.Contains(key)) {
			partMap[key]->SetActive(true);
			partMap[key]->SetHiddenInGame(false);
			partMap[key]->SetVisibility(true);
			partMap[key]->SetComponentTickEnabled(true);
			partMap[key]->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else
		{
			partMap[key]->SetActive(false);
			partMap[key]->SetHiddenInGame(true);
			partMap[key]->SetVisibility(false);
			partMap[key]->SetComponentTickEnabled(false);
			partMap[key]->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}
// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();
	ShowFloor({FloorPartEnum::Solid});
	ShowPart({});
}


// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}