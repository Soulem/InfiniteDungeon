// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"

ARoom::ARoom() {

	wallClassesMap.Add(WallTypeEnum::Wall, LoadClass<AWall>(NULL, *FString("Blueprint'/Game/Wall/Wall_BP.Wall_BP_C'")));

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("default"), true);
	RootComponent->SetVisibility(false);

	trigger = CreateDefaultSubobject<UChildActorComponent>(TEXT("trigger"), true);
	trigger->SetChildActorClass(ARoomTrigger::StaticClass());
	trigger->SetupAttachment(RootComponent);

	floorClassMap.Add(RoomShapeEnum::TRI, LoadClass<AWall>(NULL, *FString("Blueprint'/Game/Wall/Tri/TriFloor.TriFloor_C'")));
	floorClassMap.Add(RoomShapeEnum::SQU, LoadClass<AWall>(NULL, *FString("Blueprint'/Game/Wall/Squ/SquFloor.SquFloor_C'")));
	floorClassMap.Add(RoomShapeEnum::HEX, LoadClass<AWall>(NULL, *FString("Blueprint'/Game/Wall/Hex/HexFloor.HexFloor_C'")));
}

ARoom::~ARoom() {

}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();
	((ARoomTrigger*)trigger->GetChildActor())->trapType = TrapTypeEnum::None;
	((ARoomTrigger*)trigger->GetChildActor())->trapTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARoom::OnTriggerOverLap);
	
	TArray<UChildActorComponent*> walls;
	roomWalls.GenerateValueArray(walls);
	for (UChildActorComponent *wall : walls) {
		((AWall*)wall->GetChildActor())->myParentRoom = this;
	}
}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoom::CloseInWalls() {

}

void ARoom::ShootFromWalls() {

}

void ARoom::OnTriggerOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	/*if (OtherActor->IsA(AInfiniteDungeonCharacter::StaticClass()) &&
		0 < roomWalls.Num()) {
		switch (trapType) {
		case RoomTypeEnum::Close_In: {
			//SetRoomType(trapType);
			CloseInWalls();
			break;
		}
		case RoomTypeEnum::Floor_Collapse: {
			//myWalls[
			::Floor]->CollapseFloor();
			break;
		}
		case RoomTypeEnum::Floor_Collapse_Murder: {
			//SetRoomType(trapType);
			ShootFromWalls();
			// We want to do this after some time, or after enemies die.
			//myWalls[WallPositionEnum::Floor]->CollapseFloor();
			break;
		}
		case RoomTypeEnum::Murder: {
			//SetRoomType(trapType);
			ShootFromWalls();
			break;
		}
		case RoomTypeEnum::Rope_Close_In: {
			//SetRoomType(trapType);
			CloseInWalls();
			break;
		}
		case RoomTypeEnum::Rope_Murder: {
			//SetRoomType(trapType);
			ShootFromWalls();
			break;
		}
		case RoomTypeEnum::Stairs_Exit_Murder: {
			//SetRoomType(trapType);
			ShootFromWalls();
			break;
		}
		case RoomTypeEnum::Stairs_No_Exit_Murder: {
			//SetRoomType(trapType);
			ShootFromWalls();
			break;
		}
		case RoomTypeEnum::Hole_Murder: {
			//SetRoomType(trapType);
			ShootFromWalls();
			break;
		}
		case RoomTypeEnum::Hole_Close_In: {
			//SetRoomType(trapType);
			CloseInWalls();
			break;
		}
		}
	}

	trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);*/
}

void ARoom::RandomizeWalls(TArray<WallPositionEnum> _excludePositions) {
	TArray<TEnumAsByte<WallPositionEnum>> wallPositions;
	roomWalls.GenerateKeyArray(wallPositions);
	_excludePositions.Add(WallPositionEnum::Ceiling);
	_excludePositions.Add(WallPositionEnum::Floor);
	int rand = 0;
	for (TEnumAsByte<WallPositionEnum> wall : wallPositions) {
		if (!_excludePositions.Contains(wall)) {
			rand = FMath::RandRange(0, 5);

			if (rand < 2)
				((AWall*)roomWalls[wall]->GetChildActor())->ShowWall(true);
			else
				((AWall*)roomWalls[wall]->GetChildActor())->ShowWall(false);
		}
	}
}

void ARoom::CheckCollision(TEnumAsByte<WallPositionEnum> _wallPosition) {
	AFloor* floor = (AFloor*)roomWalls[_wallPosition]->GetChildActor();
	TSet<AActor*> triCollisionArray;
	TSet<AActor*> squCollisionArray;
	TSet<AActor*> hexCollisionArray;
	floor->GetOverlappingActors(triCollisionArray, floorClassMap[RoomShapeEnum::TRI]);
	floor->GetOverlappingActors(squCollisionArray, floorClassMap[RoomShapeEnum::SQU]);
	floor->GetOverlappingActors(hexCollisionArray, floorClassMap[RoomShapeEnum::HEX]);
	if (triCollisionArray.Num() > 0 ||
		squCollisionArray.Num() > 0 ||
		hexCollisionArray.Num() > 0) {
		canFit = false;
		return;
	}
	canFit = true;
}

void ARoom::SetTrapByType(TrapTypeEnum _roomTrapType) {
	((ARoomTrigger*)trigger->GetChildActor())->trapType = _roomTrapType;
}

void ARoom::SetRoomByType(RoomTypeEnum _roomType) {
	roomType = _roomType;

	switch (_roomType) {
	case RoomTypeEnum::Stairs_Ceiling: {
		((AFloor*)roomWalls[WallPositionEnum::Ceiling]->GetChildActor())->ShowFloor({ FloorPartEnum::Exit });
		((AFloor*)roomWalls[WallPositionEnum::Floor]->GetChildActor())->ShowFloor({ FloorPartEnum::Solid});
		((AFloor*)roomWalls[WallPositionEnum::Floor]->GetChildActor())->ShowPart({ FloorPartEnum::Stairs });
		break;
	}
	case RoomTypeEnum::Stairs_Both: {
		((AFloor*)roomWalls[WallPositionEnum::Ceiling]->GetChildActor())->ShowFloor({ FloorPartEnum::Exit });
		((AFloor*)roomWalls[WallPositionEnum::Floor]->GetChildActor())->ShowFloor({ FloorPartEnum::Exit });
		((AFloor*)roomWalls[WallPositionEnum::Floor]->GetChildActor())->ShowPart({ FloorPartEnum::Stairs });
		break;
	}
	case RoomTypeEnum::Hole_Floor: {
		((AFloor*)roomWalls[WallPositionEnum::Ceiling]->GetChildActor())->ShowFloor({ FloorPartEnum::Solid });
		((AFloor*)roomWalls[WallPositionEnum::Floor]->GetChildActor())->ShowFloor({ FloorPartEnum::Exit });
		((AFloor*)roomWalls[WallPositionEnum::Floor]->GetChildActor())->ShowPart({});
		break;
	}
	case RoomTypeEnum::Hole_Ceiling: {
		((AFloor*)roomWalls[WallPositionEnum::Ceiling]->GetChildActor())->ShowFloor({ FloorPartEnum::Exit });
		((AFloor*)roomWalls[WallPositionEnum::Floor]->GetChildActor())->ShowFloor({ FloorPartEnum::Solid });
		((AFloor*)roomWalls[WallPositionEnum::Floor]->GetChildActor())->ShowPart({});
		break;
	}
	case RoomTypeEnum::Hole_Both: {
		((AFloor*)roomWalls[WallPositionEnum::Ceiling]->GetChildActor())->ShowFloor({ FloorPartEnum::Exit });
		((AFloor*)roomWalls[WallPositionEnum::Floor]->GetChildActor())->ShowFloor({ FloorPartEnum::Exit });
		((AFloor*)roomWalls[WallPositionEnum::Floor]->GetChildActor())->ShowPart({});
		break;
	}
	default: {

	}
	}
}