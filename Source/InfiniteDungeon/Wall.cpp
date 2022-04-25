// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AWall::AWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	isConnected = true;
	wallPosition = WallPositionEnum::Front;
	myParentRoom = nullptr;
	myParentRoomNode = nullptr;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("default"), true);
	RootComponent->SetVisibility(false);
	roomNumber = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Room Number"), true);
	roomNumber->SetupAttachment(RootComponent);
}

AWall::~AWall() {

}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::DebugUpdateRoomNumber(int RoomNumber) {
	roomNumber->SetText(FText::AsCultureInvariant(FString::FromInt(RoomNumber)));
}

void AWall::SetWallText(FString* _str) {
	UTextRenderComponent* textRender = (UTextRenderComponent*)this->GetComponentByClass(UTextRenderComponent::StaticClass());
	if (NULL != textRender)
		textRender->SetText(FText::AsCultureInvariant(*_str));
}

TEnumAsByte<WallTypeEnum> AWall::GetRandomWallType() {
	return (WallTypeEnum)FMath::RandRange(0, (uint8)WallTypeEnum::NUM_WALL_TYPES - 1);
}

void AWall::ShowWall(bool _bShouldShow) {
	if (WallTypeEnum::Wall == wallType) {
		UStaticMeshComponent* wall = FindComponentByClass<UStaticMeshComponent>();
		wall->SetHiddenInGame(!_bShouldShow);
		wall->SetComponentTickEnabled(_bShouldShow);
		wall->SetVisibility(_bShouldShow);
		wall->SetActive(_bShouldShow);
		UBoxComponent* exit = FindComponentByClass<UBoxComponent>();
		exit->SetHiddenInGame(_bShouldShow);
		exit->SetComponentTickEnabled(!_bShouldShow);
		exit->SetVisibility(true);
		exit->SetActive(!_bShouldShow);
		UTextRenderComponent* roomNum = FindComponentByClass<UTextRenderComponent>();
		roomNum->SetHiddenInGame(!_bShouldShow);
		//roomNum->SetComponentTickEnabled(_bShouldShow);
		roomNum->SetVisibility(_bShouldShow);
		roomNum->SetActive(_bShouldShow);
		if (_bShouldShow) {
			exit->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			wall->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else {
			exit->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			wall->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		isConnected = _bShouldShow;
	}
}

void AWall::CloseInWall_Implementation() {
}
void AWall::CollapseFloor_Implementation() {
}
void AWall::ShootFromWall_Implementation() {
}

void AWall::SetWallCollision(bool _bHasCollision) {
	if (WallTypeEnum::Wall == wallType) {
		UBoxComponent* exit = FindComponentByClass<UBoxComponent>();
		exit->SetHiddenInGame(!_bHasCollision);
		exit->SetComponentTickEnabled(_bHasCollision);
		exit->SetVisibility(true);
		exit->SetActive(_bHasCollision);
		if (_bHasCollision) {
			exit->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else {
			exit->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
	if (WallTypeEnum::Floor_Ceiling == wallType) {
		USphereComponent* exit = FindComponentByClass<USphereComponent>();
		exit->SetHiddenInGame(!_bHasCollision);
		exit->SetComponentTickEnabled(_bHasCollision);
		exit->SetVisibility(true);
		exit->SetActive(_bHasCollision);
		if (_bHasCollision) {
			exit->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else {
			exit->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}
