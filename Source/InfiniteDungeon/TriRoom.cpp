// Fill out your copyright notice in the Description page of Project Settings.


#include "TriRoom.h"

ATriRoom::ATriRoom() {
	roomShape = RoomShapeEnum::TRI;

	FTransform Ceiling_relativePos;
	Ceiling_relativePos.SetLocation(FVector{ 0.0f, 0.0f, 1710.0f });
	Ceiling_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 180.0f, 0.0f, 0.0f }));

	UChildActorComponent* ceiling = CreateDefaultSubobject<UChildActorComponent>(TEXT("Ceiling"), true);
	ceiling->SetRelativeTransform(Ceiling_relativePos);
	ceiling->SetChildActorClass(floorClassMap[RoomShapeEnum::TRI]);
	ceiling->SetupAttachment(RootComponent);
	roomWalls.Add(WallPositionEnum::Ceiling, ceiling);

	FTransform Floor_relativePos;
	Floor_relativePos.SetLocation(FVector{ 0.0f, 0.0f, 0.0f });
	Floor_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 0.0f }));

	UChildActorComponent* floor = CreateDefaultSubobject<UChildActorComponent>(TEXT("Floor"), true);
	floor->SetRelativeTransform(Floor_relativePos);
	floor->SetChildActorClass(floorClassMap[RoomShapeEnum::TRI]);
	floor->SetupAttachment(RootComponent);
	roomWalls.Add(WallPositionEnum::Floor, floor);

	FTransform Front_wall_relativePos;
	Front_wall_relativePos.SetLocation(FVector{ 1958.0f, 0.0f, 0.0f });
	Front_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 0.0f }));

	UChildActorComponent* front = CreateDefaultSubobject<UChildActorComponent>(TEXT("Front"), true);
	front->SetRelativeTransform(Front_wall_relativePos);
	front->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
	front->SetupAttachment(RootComponent);
	roomWalls.Add(WallPositionEnum::Front, front);

	FTransform Right_wall_relativePos;
	Right_wall_relativePos.SetLocation(FVector{ -977.0f, 1695.5f, 0.0f });
	Right_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 120.0f }));

	UChildActorComponent* right = CreateDefaultSubobject<UChildActorComponent>(TEXT("Right"), true);
	right->SetRelativeTransform(Right_wall_relativePos);
	right->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
	right->SetupAttachment(RootComponent);
	roomWalls.Add(WallPositionEnum::Right, right);

	FTransform Left_wall_relativePos;
	Left_wall_relativePos.SetLocation(FVector{ -977.0f, -1695.5f, 0.0f });
	Left_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 240.0f }));

	UChildActorComponent* left = CreateDefaultSubobject<UChildActorComponent>(TEXT("Left"), true);
	left->SetRelativeTransform(Left_wall_relativePos);
	left->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
	left->SetupAttachment(RootComponent);
	roomWalls.Add(WallPositionEnum::Left, left);
}

ATriRoom::~ATriRoom() {}

void ATriRoom::BeginPlay() {
	Super::BeginPlay();
	((ARoomTrigger*)trigger->GetChildActor())->trapTrigger->SetRelativeLocation(FVector{ 0.0f, 0.0f, 330.0f });
	((ARoomTrigger*)trigger->GetChildActor())->trapTrigger->SetRelativeScale3D(FVector{ 30.0f, 30.0f, 10.0f });

	((AWall*)this->roomWalls[WallPositionEnum::Ceiling]->GetChildActor())->wallPosition = WallPositionEnum::Ceiling;
	((AWall*)this->roomWalls[WallPositionEnum::Ceiling]->GetChildActor())->myParentRoom = this;

	((AWall*)this->roomWalls[WallPositionEnum::Floor]->GetChildActor())->wallPosition = WallPositionEnum::Floor;
	((AWall*)this->roomWalls[WallPositionEnum::Floor]->GetChildActor())->myParentRoom = this;

	((AWall*)this->roomWalls[WallPositionEnum::Front]->GetChildActor())->wallPosition = WallPositionEnum::Front;
	((AWall*)this->roomWalls[WallPositionEnum::Front]->GetChildActor())->myParentRoom = this;

	((AWall*)this->roomWalls[WallPositionEnum::Right]->GetChildActor())->wallPosition = WallPositionEnum::Right;
	((AWall*)this->roomWalls[WallPositionEnum::Right]->GetChildActor())->myParentRoom = this;

	((AWall*)this->roomWalls[WallPositionEnum::Left]->GetChildActor())->wallPosition = WallPositionEnum::Left;
	((AWall*)this->roomWalls[WallPositionEnum::Left]->GetChildActor())->myParentRoom = this;
}

void ATriRoom::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ATriRoom::SetTrapByType(TrapTypeEnum _roomTrapType) {
	Super::SetTrapByType(_roomTrapType);
	switch (_roomTrapType) {
	case TrapTypeEnum::None: {
		break;
	}
	case TrapTypeEnum::Close_In: {
		FTransform Front_wall_relativePos;
		Front_wall_relativePos.SetLocation(FVector{ 1958.0f, 0.0f, 0.0f });
		Front_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 0.0f }));

		UChildActorComponent* front = CreateDefaultSubobject<UChildActorComponent>(TEXT("Front"), true);
		front->SetRelativeTransform(Front_wall_relativePos);
		front->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
		front->SetupAttachment(RootComponent);
		roomTrapWalls.Add(WallPositionEnum::Front, front);

		FTransform Right_wall_relativePos;
		Right_wall_relativePos.SetLocation(FVector{ -977.0f, 1695.5f, 0.0f });
		Right_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 120.0f }));

		UChildActorComponent* right = CreateDefaultSubobject<UChildActorComponent>(TEXT("Right"), true);
		right->SetRelativeTransform(Right_wall_relativePos);
		right->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
		right->SetupAttachment(RootComponent);
		roomTrapWalls.Add(WallPositionEnum::Right, right);

		FTransform Left_wall_relativePos;
		Left_wall_relativePos.SetLocation(FVector{ -977.0f, -1695.5f, 0.0f });
		Left_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 240.0f }));

		UChildActorComponent* left = CreateDefaultSubobject<UChildActorComponent>(TEXT("Left"), true);
		left->SetRelativeTransform(Left_wall_relativePos);
		left->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
		left->SetupAttachment(RootComponent);
		roomTrapWalls.Add(WallPositionEnum::Left, left);
		break;
	}
	default: {

	}
	}
}
