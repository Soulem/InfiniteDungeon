// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectManager.h"
#include "InfiniteLevel.h"

UObjectManager::UObjectManager() {
	roomClassesMap.Add(RoomShapeEnum::TRI, LoadClass<ATriRoom>(NULL, *FString("Blueprint'/Game/Room/TriRoom/TriRoom_BP.TriRoom_BP_C'")));
	roomClassesMap.Add(RoomShapeEnum::SQU, LoadClass<ASquRoom>(NULL, *FString("Blueprint'/Game/Room/SquRoom/SquRoom_BP.SquRoom_BP_C'")));
	roomClassesMap.Add(RoomShapeEnum::HEX, LoadClass<AHexRoom>(NULL, *FString("Blueprint'/Game/Room/HexRoom/HexRoom_BP.HexRoom_BP_C'")));
	roomsByShape.Empty();
}

UObjectManager::~UObjectManager() {

}

ARoomNode* UObjectManager::GetRoom(TEnumAsByte<RoomShapeEnum> _roomShape) {
	ARoomNode* returnNode = nullptr;
	returnNode = roomsByShape[_roomShape].Pop();
	returnNode->SetActive(true);
	return returnNode;
}

void UObjectManager::ReturnRoom(ARoomNode* _room) {
	FTransform worldTransform;
	worldTransform.SetLocation({ -900000.0f, -900000.0f, -900000.0f });
	worldTransform.SetRotation(FQuat::MakeFromEuler({}));
	_room->SetActorTransform(worldTransform);
	_room->SetActive(false);
	roomsByShape[_room->data->roomShape].Push(_room);
}

void UObjectManager::InitializeRoomManager(AInfiniteLevel* _level) {
	if (!isInitialized) {
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = (AActor*)_level;
		SpawnInfo.Instigator = NULL;
		SpawnInfo.ObjectFlags |= RF_Transient;

		FTransform worldTransform;
		worldTransform.SetLocation({ -900000.0f, -900000.0f, -900000.0f });

		ARoomNode* tri = NewObject<ARoomNode>(ARoomNode::StaticClass());
		tri->CreateRoom(_level->GetWorld(), SpawnInfo, roomClassesMap[RoomShapeEnum::TRI], RoomShapeEnum::TRI, worldTransform);
		tri->SetActive(false);
		roomsByShape.Add(RoomShapeEnum::TRI, { tri });
		ARoomNode* squ = NewObject<ARoomNode>(ARoomNode::StaticClass());
		squ->CreateRoom(_level->GetWorld(), SpawnInfo, roomClassesMap[RoomShapeEnum::SQU], RoomShapeEnum::SQU, worldTransform);
		squ->SetActive(false);
		roomsByShape.Add(RoomShapeEnum::SQU, { squ });
		ARoomNode* hex = NewObject<ARoomNode>(ARoomNode::StaticClass());
		hex->CreateRoom(_level->GetWorld(), SpawnInfo, roomClassesMap[RoomShapeEnum::HEX], RoomShapeEnum::HEX, worldTransform);
		hex->SetActive(false);
		roomsByShape.Add(RoomShapeEnum::HEX, { hex });

		for (int i = 1; i < MAX_NUM_ROOMS; ++i) {
			tri = NewObject<ARoomNode>(ARoomNode::StaticClass());
			tri->CreateRoom(_level->GetWorld(), SpawnInfo, roomClassesMap[RoomShapeEnum::TRI], RoomShapeEnum::TRI, worldTransform);
			tri->SetActive(false);
			roomsByShape[RoomShapeEnum::TRI].Add(tri);
			squ = NewObject<ARoomNode>(ARoomNode::StaticClass());
			squ->CreateRoom(_level->GetWorld(), SpawnInfo, roomClassesMap[RoomShapeEnum::SQU], RoomShapeEnum::SQU, worldTransform);
			squ->SetActive(false);
			roomsByShape[RoomShapeEnum::SQU].Add(squ);
			hex = NewObject<ARoomNode>(ARoomNode::StaticClass());
			hex->CreateRoom(_level->GetWorld(), SpawnInfo, roomClassesMap[RoomShapeEnum::HEX], RoomShapeEnum::HEX, worldTransform);
			hex->SetActive(false);
			roomsByShape[RoomShapeEnum::HEX].Add(hex);
		}

		isInitialized = true;
	}
}

bool UObjectManager::CheckListByShape(RoomShapeEnum _roomShape) {
	return roomsByShape[RoomShapeEnum::TRI].Num() > 0 ? true : false;
}