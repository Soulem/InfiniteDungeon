// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomNode.h"

ARoomNode::ARoomNode() {
	connectedRooms.Empty();
}

ARoomNode::~ARoomNode() {

}

void ARoomNode::AddConnectRoomNode(WallPositionEnum _wall, ARoomNode* _newRoom) {
	connectedRooms.Add(_wall, _newRoom);
}

void ARoomNode::CreateRoom(UWorld* world, FActorSpawnParameters _spawnInfo, TSubclassOf<class ARoom> room, TEnumAsByte<RoomShapeEnum> roomShape, FTransform& worldPos) {

	// Pointing it to a newly created world object.  It's like you have to double up.
	data = (ARoom*)world->GetWorld()->SpawnActor(room, &worldPos, _spawnInfo);
	if (data == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("data is null"));
	}
	((AWall*)data->roomWalls[WallPositionEnum::Front]->GetChildActor())->ShowWall(false);
	data->RandomizeWalls({WallPositionEnum::Front});

	TArray<UChildActorComponent*> walls;
	data->roomWalls.GenerateValueArray(walls);
	for (UChildActorComponent* wall : walls) {
		((AWall*)wall->GetChildActor())->myParentRoomNode = this;
	}

	/*if (RoomEnum::HEX == data->roomShape)
		data->spawner->CreateSpawnableActor(world, level, SpawnableTypeEnum::WOLF, 1);*/
}