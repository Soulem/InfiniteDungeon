// Fill out your copyright notice in the Description page of Project Settings.


#include "SquRoom.h"

ASquRoom::ASquRoom() {
    roomShape = RoomShapeEnum::SQU;

    FTransform HexCeiling_relativePos;
    HexCeiling_relativePos.SetLocation(FVector{ 0.0f, 0.0f, 1710.0f });
    HexCeiling_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 180.0f, 0.0f, 0.0f }));

    UChildActorComponent* ceiling = CreateDefaultSubobject<UChildActorComponent>(TEXT("Ceiling"), true);
    ceiling->SetRelativeTransform(HexCeiling_relativePos);
    ceiling->SetChildActorClass(floorClassMap[RoomShapeEnum::SQU]);
    ceiling->SetupAttachment(RootComponent);
    roomWalls.Add(WallPositionEnum::Ceiling, ceiling);

    FTransform Hexfloor_relativePos;
    Hexfloor_relativePos.SetLocation(FVector{ 0.0f, 0.0f, 0.0f });
    Hexfloor_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 0.0f }));

    UChildActorComponent* floor = CreateDefaultSubobject<UChildActorComponent>(TEXT("Floor"), true);
    floor->SetRelativeTransform(Hexfloor_relativePos);
    floor->SetChildActorClass(floorClassMap[RoomShapeEnum::SQU]);
    floor->SetupAttachment(RootComponent);
    roomWalls.Add(WallPositionEnum::Floor, floor);

    FTransform Front_wall_relativePos;
    Front_wall_relativePos.SetLocation(FVector{ 3395.0f, 0.0f, 0.0f });
    Front_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 0.0f }));

    UChildActorComponent* front = CreateDefaultSubobject<UChildActorComponent>(TEXT("Front"), true);
    front->SetRelativeTransform(Front_wall_relativePos);
    front->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
    front->SetupAttachment(RootComponent);
    roomWalls.Add(WallPositionEnum::Front, front);

    FTransform Right_wall_relativePos;
    Right_wall_relativePos.SetLocation(FVector{ 0.0f,  3395.0f, 0.0f });
    Right_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 90.0f }));

    UChildActorComponent* right = CreateDefaultSubobject<UChildActorComponent>(TEXT("Right"), true);
    right->SetRelativeTransform(Right_wall_relativePos);
    right->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
    right->SetupAttachment(RootComponent);
    roomWalls.Add(WallPositionEnum::Right, right);

    FTransform Back_wall_relativePos;
    Back_wall_relativePos.SetLocation(FVector{ -3395.0f, 0.0f, 0.0f });
    Back_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 180.0f }));

    UChildActorComponent* back = CreateDefaultSubobject<UChildActorComponent>(TEXT("Back"), true);
    back->SetRelativeTransform(Back_wall_relativePos);
    back->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
    back->SetupAttachment(RootComponent);
    roomWalls.Add(WallPositionEnum::Back, back);

    FTransform Left_wall_relativePos;
    Left_wall_relativePos.SetLocation(FVector{ 0.0f, -3395.0f, 0.0f });
    Left_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 270.0f }));

    UChildActorComponent* left = CreateDefaultSubobject<UChildActorComponent>(TEXT("Left"), true);
    left->SetRelativeTransform(Left_wall_relativePos);
    left->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
    left->SetupAttachment(RootComponent);
    roomWalls.Add(WallPositionEnum::Left, left);
}

ASquRoom::~ASquRoom() {   
}

void ASquRoom::BeginPlay() {
    Super::BeginPlay();
    ((ARoomTrigger*)trigger->GetChildActor())->trapTrigger->SetRelativeLocation(FVector{ 0.0f, 0.0f, 330.0f });
    ((ARoomTrigger*)trigger->GetChildActor())->trapTrigger->SetRelativeScale3D(FVector{ 48.5f, 48.5f, 10.0f });

      ((AWall*)roomWalls[WallPositionEnum::Ceiling]->GetChildActor())->wallPosition = WallPositionEnum::Ceiling;
      ((AWall*)this->roomWalls[WallPositionEnum::Ceiling]->GetChildActor())->myParentRoom = this;

      ((AWall*)roomWalls[WallPositionEnum::Floor]->GetChildActor())->wallPosition = WallPositionEnum::Floor;    ((AWall*)this->roomWalls[WallPositionEnum::Ceiling]->GetChildActor())->myParentRoom = this;
      ((AWall*)this->roomWalls[WallPositionEnum::Floor]->GetChildActor())->myParentRoom = this;

      ((AWall*)roomWalls[WallPositionEnum::Front]->GetChildActor())->wallPosition = WallPositionEnum::Front;
      ((AWall*)this->roomWalls[WallPositionEnum::Front]->GetChildActor())->myParentRoom = this;

      ((AWall*)roomWalls[WallPositionEnum::Right]->GetChildActor())->wallPosition = WallPositionEnum::Right;
      ((AWall*)this->roomWalls[WallPositionEnum::Right]->GetChildActor())->myParentRoom = this;

      ((AWall*)roomWalls[WallPositionEnum::Back]->GetChildActor())->wallPosition = WallPositionEnum::Back;
      ((AWall*)this->roomWalls[WallPositionEnum::Back]->GetChildActor())->myParentRoom = this;

      ((AWall*)roomWalls[WallPositionEnum::Left]->GetChildActor())->wallPosition = WallPositionEnum::Left;
      ((AWall*)this->roomWalls[WallPositionEnum::Left]->GetChildActor())->myParentRoom = this;
}

void ASquRoom::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void ASquRoom::SetTrapByType(TrapTypeEnum _roomTrapType) {

    Super::SetTrapByType(_roomTrapType);
    ((ARoomTrigger*)trigger->GetChildActor())->trapType = _roomTrapType;
    switch (_roomTrapType) {
    case TrapTypeEnum::None: {
        break;
    }
    case TrapTypeEnum::Close_In: {
        FTransform Front_wall_relativePos;
        Front_wall_relativePos.SetLocation(FVector{ 3395.0f, 0.0f, 0.0f });
        Front_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 0.0f }));

        UChildActorComponent* front = CreateDefaultSubobject<UChildActorComponent>(TEXT("Front"), true);
        front->SetRelativeTransform(Front_wall_relativePos);
        front->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
        front->SetupAttachment(RootComponent);
        roomTrapWalls.Add(WallPositionEnum::Front, front);

        FTransform Right_wall_relativePos;
        Right_wall_relativePos.SetLocation(FVector{ 0.0f,  3395.0f, 0.0f });
        Right_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 90.0f }));

        UChildActorComponent* right = CreateDefaultSubobject<UChildActorComponent>(TEXT("Right"), true);
        right->SetRelativeTransform(Right_wall_relativePos);
        right->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
        right->SetupAttachment(RootComponent);
        roomTrapWalls.Add(WallPositionEnum::Right, right);

        FTransform Back_wall_relativePos;
        Back_wall_relativePos.SetLocation(FVector{ -3395.0f, 0.0f, 0.0f });
        Back_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 180.0f }));

        UChildActorComponent* back = CreateDefaultSubobject<UChildActorComponent>(TEXT("Back"), true);
        back->SetRelativeTransform(Back_wall_relativePos);
        back->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
        back->SetupAttachment(RootComponent);
        roomTrapWalls.Add(WallPositionEnum::Back, back);

        FTransform Left_wall_relativePos;
        Left_wall_relativePos.SetLocation(FVector{ 0.0f, -3395.0f, 0.0f });
        Left_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 270.0f }));

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