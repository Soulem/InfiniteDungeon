// Fill out your copyright notice in the Description page of Project Settings.


#include "HexRoom.h"

AHexRoom::AHexRoom() {
    roomShape = RoomShapeEnum::HEX;

      FTransform HexCeiling_relativePos;
      HexCeiling_relativePos.SetLocation(FVector{ 0.0f, 0.0f, 1710.0f });
      HexCeiling_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 180.0f, 0.0f, 0.0f }));

      UChildActorComponent* ceiling = CreateDefaultSubobject<UChildActorComponent>(TEXT("Ceiling"), true);
      ceiling->SetRelativeTransform(HexCeiling_relativePos);
      ceiling->SetChildActorClass(floorClassMap[RoomShapeEnum::HEX]);
      ceiling->SetupAttachment(RootComponent);
      roomWalls.Add(WallPositionEnum::Ceiling, ceiling);

      FTransform Hexfloor_relativePos;
      Hexfloor_relativePos.SetLocation(FVector{ 0.0f, 0.0f, 0.0f });
      Hexfloor_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 0.0f }));

      UChildActorComponent* floor = CreateDefaultSubobject<UChildActorComponent>(TEXT("Floor"), true);
      floor->SetRelativeTransform(Hexfloor_relativePos);
      floor->SetChildActorClass(floorClassMap[RoomShapeEnum::HEX]);
      floor->SetupAttachment(RootComponent);
      roomWalls.Add(WallPositionEnum::Floor, floor);

      FTransform Front_wall_relativePos;
      Front_wall_relativePos.SetLocation(FVector{ 5884.0f, 0.0f, 0.0f });
      Front_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 0.0f }));

      UChildActorComponent* front = CreateDefaultSubobject<UChildActorComponent>(TEXT("Front"), true);
      front->SetRelativeTransform(Front_wall_relativePos);
      front->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
      front->SetupAttachment(RootComponent);
      roomWalls.Add(WallPositionEnum::Front, front);

      FTransform FrontRight_wall_relativePos;
      FrontRight_wall_relativePos.SetLocation(FVector{ 2939.5f, 5095.0f, 0.0f });
      FrontRight_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 60.0f }));

      UChildActorComponent* frontRight = CreateDefaultSubobject<UChildActorComponent>(TEXT("FrontRight"), true);
      frontRight->SetRelativeTransform(FrontRight_wall_relativePos);
      frontRight->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
      frontRight->SetupAttachment(RootComponent);
      roomWalls.Add(WallPositionEnum::Front_Right, frontRight);

      FTransform BackRight_wall_relativePos;
      BackRight_wall_relativePos.SetLocation(FVector{ -2939.5f, 5095.0f, 0.0f });
      BackRight_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 120.0f }));

      UChildActorComponent* backRight = CreateDefaultSubobject<UChildActorComponent>(TEXT("BackRight"), true);
      backRight->SetRelativeTransform(BackRight_wall_relativePos);
      backRight->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
      backRight->SetupAttachment(RootComponent);
      roomWalls.Add(WallPositionEnum::Back_Right, backRight);

      FTransform Back_wall_relativePos;
      Back_wall_relativePos.SetLocation(FVector{ -5884.0f, 0.0f, 0.0f });
      Back_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 180.0f }));

      UChildActorComponent* back = CreateDefaultSubobject<UChildActorComponent>(TEXT("Back"), true);
      back->SetRelativeTransform(Back_wall_relativePos);
      back->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
      back->SetupAttachment(RootComponent);
      roomWalls.Add(WallPositionEnum::Back, back);

      FTransform Back_Left_wall_relativePos;
      Back_Left_wall_relativePos.SetLocation(FVector{ -2939.5f, -5095.0f, 0.0f });
      Back_Left_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 240.0f }));

      UChildActorComponent* backLeft = CreateDefaultSubobject<UChildActorComponent>(TEXT("BackLeft"), true);
      backLeft->SetRelativeTransform(Back_Left_wall_relativePos);
      backLeft->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
      backLeft->SetupAttachment(RootComponent);
      roomWalls.Add(WallPositionEnum::Back_Left, backLeft);

      FTransform Front_Left_wall_relativePos;
      Front_Left_wall_relativePos.SetLocation(FVector{ 2939.5f, -5095.0f, 0.0f });
      Front_Left_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 300.0f }));

      UChildActorComponent* frontLeft = CreateDefaultSubobject<UChildActorComponent>(TEXT("FrontLeft"), true);
      frontLeft->SetRelativeTransform(Front_Left_wall_relativePos);
      frontLeft->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
      frontLeft->SetupAttachment(RootComponent);
      roomWalls.Add(WallPositionEnum::Front_Left, frontLeft);
}

AHexRoom::~AHexRoom() {

}

void AHexRoom::BeginPlay() {
    Super::BeginPlay();
    ((ARoomTrigger*)trigger->GetChildActor())->trapTrigger->SetRelativeLocation(FVector{ 0.0f, 0.0f, 330.0f });
    ((ARoomTrigger*)trigger->GetChildActor())->trapTrigger->SetRelativeScale3D(FVector{ 75.0f, 75.0f, 10.0f });

    ((AWall*)roomWalls[WallPositionEnum::Ceiling]->GetChildActor())->wallPosition = WallPositionEnum::Ceiling;
    ((AWall*)this->roomWalls[WallPositionEnum::Ceiling]->GetChildActor())->myParentRoom = this;

    ((AWall*)roomWalls[WallPositionEnum::Floor]->GetChildActor())->wallPosition = WallPositionEnum::Floor;
    ((AWall*)this->roomWalls[WallPositionEnum::Floor]->GetChildActor())->myParentRoom = this;

    ((AWall*)roomWalls[WallPositionEnum::Front]->GetChildActor())->wallPosition = WallPositionEnum::Front;
    ((AWall*)this->roomWalls[WallPositionEnum::Front]->GetChildActor())->myParentRoom = this;

    ((AWall*)roomWalls[WallPositionEnum::Front_Right]->GetChildActor())->wallPosition = WallPositionEnum::Front_Right;
    ((AWall*)this->roomWalls[WallPositionEnum::Front_Right]->GetChildActor())->myParentRoom = this;

    ((AWall*)roomWalls[WallPositionEnum::Back_Right]->GetChildActor())->wallPosition = WallPositionEnum::Back_Right;
    ((AWall*)this->roomWalls[WallPositionEnum::Back_Right]->GetChildActor())->myParentRoom = this;

    ((AWall*)roomWalls[WallPositionEnum::Back]->GetChildActor())->wallPosition = WallPositionEnum::Back;
    ((AWall*)this->roomWalls[WallPositionEnum::Back]->GetChildActor())->myParentRoom = this;

    ((AWall*)roomWalls[WallPositionEnum::Back_Left]->GetChildActor())->wallPosition = WallPositionEnum::Back_Left;
    ((AWall*)this->roomWalls[WallPositionEnum::Back_Left]->GetChildActor())->myParentRoom = this;

    ((AWall*)roomWalls[WallPositionEnum::Front_Left]->GetChildActor())->wallPosition = WallPositionEnum::Front_Left;
    ((AWall*)this->roomWalls[WallPositionEnum::Front_Left]->GetChildActor())->myParentRoom = this;
}

void AHexRoom::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void AHexRoom::SetTrapByType(TrapTypeEnum _roomTrapType) {
    Super::SetTrapByType(_roomTrapType);
    ((ARoomTrigger*)trigger->GetChildActor())->trapType = _roomTrapType;
    switch (_roomTrapType) {
    case TrapTypeEnum::None: {
        break;
    }
    case TrapTypeEnum::Close_In: {
        FTransform Front_wall_relativePos;
        Front_wall_relativePos.SetLocation(FVector{ 5884.0f, 0.0f, 0.0f });
        Front_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 0.0f }));

        UChildActorComponent* front = CreateDefaultSubobject<UChildActorComponent>(TEXT("Front"), true);
        front->SetRelativeTransform(Front_wall_relativePos);
        front->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
        front->SetupAttachment(RootComponent);
        roomTrapWalls.Add(WallPositionEnum::Front, front);

        FTransform FrontRight_wall_relativePos;
        FrontRight_wall_relativePos.SetLocation(FVector{ 2939.5f, 5095.0f, 0.0f });
        FrontRight_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 60.0f }));

        UChildActorComponent* frontRight = CreateDefaultSubobject<UChildActorComponent>(TEXT("FrontRight"), true);
        frontRight->SetRelativeTransform(FrontRight_wall_relativePos);
        frontRight->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
        frontRight->SetupAttachment(RootComponent);
        roomTrapWalls.Add(WallPositionEnum::Front_Right, frontRight);

        FTransform BackRight_wall_relativePos;
        BackRight_wall_relativePos.SetLocation(FVector{ -2939.5f, 5095.0f, 0.0f });
        BackRight_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 120.0f }));

        UChildActorComponent* backRight = CreateDefaultSubobject<UChildActorComponent>(TEXT("BackRight"), true);
        backRight->SetRelativeTransform(BackRight_wall_relativePos);
        backRight->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
        backRight->SetupAttachment(RootComponent);
        roomTrapWalls.Add(WallPositionEnum::Back_Right, backRight);

        FTransform Back_wall_relativePos;
        Back_wall_relativePos.SetLocation(FVector{ -5884.0f, 0.0f, 0.0f });
        Back_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 180.0f }));

        UChildActorComponent* back = CreateDefaultSubobject<UChildActorComponent>(TEXT("Back"), true);
        back->SetRelativeTransform(Back_wall_relativePos);
        back->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
        back->SetupAttachment(RootComponent);
        roomTrapWalls.Add(WallPositionEnum::Back, back);

        FTransform Back_Left_wall_relativePos;
        Back_Left_wall_relativePos.SetLocation(FVector{ -2939.5f, -5095.0f, 0.0f });
        Back_Left_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 240.0f }));

        UChildActorComponent* backLeft = CreateDefaultSubobject<UChildActorComponent>(TEXT("BackLeft"), true);
        backLeft->SetRelativeTransform(Back_Left_wall_relativePos);
        backLeft->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
        backLeft->SetupAttachment(RootComponent);
        roomTrapWalls.Add(WallPositionEnum::Back_Left, backLeft);

        FTransform Front_Left_wall_relativePos;
        Front_Left_wall_relativePos.SetLocation(FVector{ 2939.5f, -5095.0f, 0.0f });
        Front_Left_wall_relativePos.SetRotation(FQuat::MakeFromEuler(FVector{ 0.0f, 0.0f, 300.0f }));

        UChildActorComponent* frontLeft = CreateDefaultSubobject<UChildActorComponent>(TEXT("FrontLeft"), true);
        frontLeft->SetRelativeTransform(Front_Left_wall_relativePos);
        frontLeft->SetChildActorClass(wallClassesMap[WallTypeEnum::Wall]);
        frontLeft->SetupAttachment(RootComponent);
        roomTrapWalls.Add(WallPositionEnum::Front_Left, frontLeft);
        break;
    }
    default: {

    }
    }
}