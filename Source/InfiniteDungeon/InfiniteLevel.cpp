// Fill out your copyright notice in the Description page of Project Settings.


#include "InfiniteLevel.h"

AInfiniteLevel::AInfiniteLevel() {
	roomCounter = 0;
	depth = 0;
	levelBuild = LevelBuildEnum::STATIC_NUMBERD;
	selectedRoomShapesArray.Add(RoomShapeEnum::TRI);
	selectedRoomShapesArray.Add(RoomShapeEnum::SQU);
	selectedRoomShapesArray.Add(RoomShapeEnum::HEX);
}

AInfiniteLevel::~AInfiniteLevel() {

}

void AInfiniteLevel::CreateLevelWithNumRooms(FTransform startingWorldPos, const int numRooms) {
	if (startHere == NULL) {
		SetStartNode(startingWorldPos);
	}
	SetCollisionRooms();
	int i = 0;
	SetCollisionRoomsVisibility(true);
	while ((roomArray.Num() < numRooms &&
		i < roomArray.Num()) &&
		(objectManager->CheckListByShape(RoomShapeEnum::TRI) ||
			objectManager->CheckListByShape(RoomShapeEnum::SQU) ||
			objectManager->CheckListByShape(RoomShapeEnum::HEX))) {
		creationIterator = roomArray[i];

		if (!((AFloor*)creationIterator->data->roomWalls[WallPositionEnum::Floor]->GetChildActor())->isConnected) {
			PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Floor, i);
		}
		if (!((AFloor*)creationIterator->data->roomWalls[WallPositionEnum::Ceiling]->GetChildActor())->isConnected && roomArray.Num() < numRooms) {
			PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Ceiling, i);
		}
		if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Front]->GetChildActor())->isConnected && roomArray.Num() < numRooms) {
			PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Front, i);
		}
		switch (creationIterator->data->roomShape)
		{
		case RoomShapeEnum::HEX: {
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Front_Right]->GetChildActor())->isConnected && roomArray.Num() < numRooms) {
				PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Front_Right, i);
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Back_Right]->GetChildActor())->isConnected && roomArray.Num() < numRooms) {
				PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Back_Right, i);
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Back]->GetChildActor())->isConnected && roomArray.Num() < numRooms) {
				PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Back, i);
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Back_Left]->GetChildActor())->isConnected && roomArray.Num() < numRooms) {
				PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Back_Left, i);
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Front_Left]->GetChildActor())->isConnected && roomArray.Num() < numRooms) {
				PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Front_Left, i);
			}
			break;
		}
		case RoomShapeEnum::SQU: {
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Right]->GetChildActor())->isConnected && roomArray.Num() < numRooms) {
				PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Right, i);
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Back]->GetChildActor())->isConnected && roomArray.Num() < numRooms) {
				PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Back, i);
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Left]->GetChildActor())->isConnected && roomArray.Num() < numRooms) {
				PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Left, i);
			}
			break;
		}
		case RoomShapeEnum::TRI: {
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Right]->GetChildActor())->isConnected && roomArray.Num() < numRooms) {
				PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Right, i);
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Left]->GetChildActor())->isConnected && roomArray.Num() < numRooms) {
				PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Left, i);
			}
			break;
		}
		default:
			break;
		}
		if (i < roomArray.Num()) {
			i++;
		}
	}
	CloseWalls();
	SetCollisionRoomsVisibility(false);
}

bool AInfiniteLevel::PlaceNewRoom(TEnumAsByte<RoomShapeEnum> parentRoomType, TEnumAsByte<WallPositionEnum> parentWall, int roomIterator) {
	
	// stuff we'll need 
	// the room shape and type that was selected
	// current room's Transform, and the current wall's forwad and up vector
	// collision room's default position (should be defaulted or const somewhere else)
	// TODO:: track which other rooms are conneded to the room being placed.
	//			I think this only effects HEX rooms.
	RoomShapeEnum selectedRoomShape = RoomShapeEnum::NULL_ROOM_SHAPE;
	RoomTypeEnum selectedRoomType = RoomTypeEnum::Normal;

	FTransform currRoomWorldTransform = creationIterator->data->GetTransform();
	FVector currWallForwardVector = creationIterator->data->roomWalls[parentWall]->GetChildActor()->GetActorForwardVector();
	FVector currWallUpVector = creationIterator->data->roomWalls[parentWall]->GetChildActor()->GetActorUpVector();
	FNextRoomTransformData transformData;
	FVector collisionRoomPosition = { 900000.0f, 900000.0f, 900000.0f };
	TMap<TEnumAsByte<WallPositionEnum>, AWall*> collidedWallMap;

	// is this the first room?
	// place a room based off the parentWall
	// select a random room shape.
	if (0 == roomIterator) {
		if (WallPositionEnum::Ceiling == parentWall) {
			switch (creationIterator->data->roomType) {
			case RoomTypeEnum::Stairs_Ceiling: {
				TArray<TEnumAsByte<RoomTypeEnum>> tempArray = { RoomTypeEnum::Stairs_Both, RoomTypeEnum::Hole_Both, RoomTypeEnum::Hole_Floor };
				selectedRoomType = tempArray[FMath::RandRange(0, tempArray.Num() - 1)];
				break;
			}
			case RoomTypeEnum::Stairs_Both: {
				TArray<TEnumAsByte<RoomTypeEnum>> tempArray = { RoomTypeEnum::Stairs_Both, RoomTypeEnum::Hole_Both, RoomTypeEnum::Hole_Floor };
				selectedRoomType = tempArray[FMath::RandRange(0, tempArray.Num() - 1)];
				break;
			}
			case RoomTypeEnum::Hole_Ceiling: {
				TArray<TEnumAsByte<RoomTypeEnum>> tempArray = { RoomTypeEnum::Hole_Both, RoomTypeEnum::Hole_Floor };
				selectedRoomType = tempArray[FMath::RandRange(0, tempArray.Num() - 1)];
				break;
			}
			case RoomTypeEnum::Hole_Both: {
				TArray<TEnumAsByte<RoomTypeEnum>> tempArray = { RoomTypeEnum::Hole_Both, RoomTypeEnum::Hole_Floor };
				selectedRoomType = tempArray[FMath::RandRange(0, tempArray.Num() - 1)];
				break;
			}
			default: {

			}
			};

		}
		else if (WallPositionEnum::Floor == parentWall) {
			switch (creationIterator->data->roomType) {
			case RoomTypeEnum::Stairs_Both: {
				TArray<TEnumAsByte<RoomTypeEnum>> tempArray = { RoomTypeEnum::Stairs_Both, RoomTypeEnum::Stairs_Ceiling };
				selectedRoomType = tempArray[FMath::RandRange(0, tempArray.Num() - 1)];
				break;
			}
			case RoomTypeEnum::Hole_Floor: {
				TArray<TEnumAsByte<RoomTypeEnum>> tempArray = { RoomTypeEnum::Hole_Both, RoomTypeEnum::Hole_Ceiling };
				selectedRoomType = tempArray[FMath::RandRange(0, tempArray.Num() - 1)];
				break;
			}
			case RoomTypeEnum::Hole_Both: {
				TArray<TEnumAsByte<RoomTypeEnum>> tempArray = { RoomTypeEnum::Hole_Both, RoomTypeEnum::Hole_Ceiling };
				selectedRoomType = tempArray[FMath::RandRange(0, tempArray.Num() - 1)];
				break;
			}
			default: {

			}
			};
		}
		selectedRoomShape = selectedRoomShapesArray[FMath::RandRange(0, selectedRoomShapesArray.Num() - 1)];
	}
	// else we are going to check for collision
	else {
		// find out where to put the wall.
		// transformData is a variable used for output
		// and contains the information we need.
		SetMagnitudeAndNewWall(creationIterator->data->roomShape, RoomShapeEnum::TRI, parentWall, transformData);

		// set our tri room collider's transform.
		// need to do this depending on where the parentWall is.
		FVector newLocationOffset;
		if (WallPositionEnum::Ceiling == parentWall ||
			WallPositionEnum::Floor == parentWall) {
			newLocationOffset = { currWallUpVector.X, currWallUpVector.Y, currWallUpVector.Z * transformData.magnitude };
		}
		else {
			newLocationOffset = { currWallForwardVector.X * transformData.magnitude, currWallForwardVector.Y * transformData.magnitude, currWallForwardVector.Z };
		}
		FRotator currRotation1(currRoomWorldTransform.GetRotation());
		FVector4 tempVector;
		tempVector.X = 0.0f;
		tempVector.Y = 0.0f;
		tempVector.Z = transformData.zRotation + currRotation1.Euler().Z;
		tempVector.W = 0.0f;
		FTransform newRoomWorldTransform;
		newRoomWorldTransform.SetTranslation(currRoomWorldTransform.GetLocation() + newLocationOffset);
		newRoomWorldTransform.SetRotation(FQuat::MakeFromEuler(tempVector));
		debugRoomMap[RoomShapeEnum::TRI]->data->SetActorTransform(newRoomWorldTransform);

		// check collision based on the parentWall.
		// if a room is being connected to the floor
		// we check to see if the collider's ceiling hits anything.
		// move the tri room collider back.
		if (WallPositionEnum::Floor == parentWall)
			((ARoom*)debugRoomMap[RoomShapeEnum::TRI]->data)->CheckCollision(WallPositionEnum::Ceiling);
		else
			((ARoom*)debugRoomMap[RoomShapeEnum::TRI]->data)->CheckCollision(WallPositionEnum::Floor);

		debugRoomMap[RoomShapeEnum::TRI]->data->SetActorLocation(collisionRoomPosition);

		// if the tri room collider fits
		// do the same check again for squ room collider
		if (((ARoom*)debugRoomMap[RoomShapeEnum::TRI]->data)->GetCanFit()) {
			SetMagnitudeAndNewWall(creationIterator->data->roomShape, RoomShapeEnum::SQU, parentWall, transformData);

			if (WallPositionEnum::Ceiling == parentWall ||
				WallPositionEnum::Floor == parentWall) {
				newLocationOffset = { currWallUpVector.X, currWallUpVector.Y, currWallUpVector.Z * transformData.magnitude };
			}
			else {
				newLocationOffset = { currWallForwardVector.X * transformData.magnitude, currWallForwardVector.Y * transformData.magnitude, currWallForwardVector.Z };
			}
			FRotator currRotation2(currRoomWorldTransform.GetRotation());
			tempVector.X = 0.0f;
			tempVector.Y = 0.0f;
			tempVector.Z = transformData.zRotation + currRotation2.Euler().Z;
			tempVector.W = 0.0f;
			newRoomWorldTransform.SetTranslation(currRoomWorldTransform.GetLocation() + newLocationOffset);
			newRoomWorldTransform.SetRotation(FQuat::MakeFromEuler(tempVector));
			debugRoomMap[RoomShapeEnum::SQU]->data->SetActorTransform(newRoomWorldTransform);

			if (WallPositionEnum::Floor == parentWall)
				((ARoom*)debugRoomMap[RoomShapeEnum::SQU]->data)->CheckCollision(WallPositionEnum::Ceiling);
			else
				((ARoom*)debugRoomMap[RoomShapeEnum::SQU]->data)->CheckCollision(WallPositionEnum::Floor);

			debugRoomMap[RoomShapeEnum::SQU]->data->SetActorLocation(collisionRoomPosition);
		}
		// This was the first round for changing the floor on the fly to try to squese a room 
		// on the floor or ceiling
		/*else {
			if (WallPositionEnum::Floor == parentWall) {
				switch (creationIterator->data->roomType) {
				case RoomTypeEnum::Stairs_Both: {
					creationIterator->data->SetRoomByType(RoomTypeEnum::Stairs_Ceiling);
					break;
				}
				case RoomTypeEnum::Hole_Floor: {
					creationIterator->data->SetRoomByType(RoomTypeEnum::Normal);
					break;
				}
				case RoomTypeEnum::Hole_Both: {
					creationIterator->data->SetRoomByType(RoomTypeEnum::Hole_Ceiling);
					break;
				}

				default: {
				}
				};
			}
			else if (WallPositionEnum::Ceiling == parentWall) {
				switch (creationIterator->data->roomType) {
				case RoomTypeEnum::Stairs_Ceiling: {
					creationIterator->data->SetRoomByType(RoomTypeEnum::Normal);
					break;
				}
				case RoomTypeEnum::Stairs_Both: {
					creationIterator->data->SetRoomByType(RoomTypeEnum::Hole_Floor);
					break;
				}
				case RoomTypeEnum::Hole_Ceiling: {
					creationIterator->data->SetRoomByType(RoomTypeEnum::Normal);
					break;
				}
				case RoomTypeEnum::Hole_Both: {
					creationIterator->data->SetRoomByType(RoomTypeEnum::Hole_Floor);
					break;
				}

				default: {
				}
				};
			}
		}*/
		// if the squ room collider fits
		// do the same check again for Hex room collider
		if (((ARoom*)debugRoomMap[RoomShapeEnum::SQU]->data)->GetCanFit()) {
			// do it for Hexagon debug room
			SetMagnitudeAndNewWall(creationIterator->data->roomShape, RoomShapeEnum::HEX, parentWall, transformData);

			if (WallPositionEnum::Ceiling == parentWall ||
				WallPositionEnum::Floor == parentWall) {
				newLocationOffset = { currWallUpVector.X, currWallUpVector.Y, currWallUpVector.Z * transformData.magnitude };
			}
			else {
				newLocationOffset = { currWallForwardVector.X * transformData.magnitude, currWallForwardVector.Y * transformData.magnitude, currWallForwardVector.Z };
			}
			FRotator currRotation3(currRoomWorldTransform.GetRotation());
			tempVector.X = 0.0f;
			tempVector.Y = 0.0f;
			tempVector.Z = transformData.zRotation + currRotation3.Euler().Z;
			tempVector.W = 0.0f;
			newRoomWorldTransform.SetTranslation(currRoomWorldTransform.GetLocation() + newLocationOffset);
			newRoomWorldTransform.SetRotation(FQuat::MakeFromEuler(tempVector));
			debugRoomMap[RoomShapeEnum::HEX]->data->SetActorTransform(newRoomWorldTransform);

			if (WallPositionEnum::Floor == parentWall)
				((ARoom*)debugRoomMap[RoomShapeEnum::HEX]->data)->CheckCollision(WallPositionEnum::Ceiling);
			else
				((ARoom*)debugRoomMap[RoomShapeEnum::HEX]->data)->CheckCollision(WallPositionEnum::Floor);

			debugRoomMap[RoomShapeEnum::HEX]->data->SetActorLocation(collisionRoomPosition);
		}
		int maxRandRooms = 0;

		// get a random shape based on what room shapes can fit
		if (((ARoom*)debugRoomMap[RoomShapeEnum::TRI]->data)->GetCanFit()) {
			if (((ARoom*)debugRoomMap[RoomShapeEnum::SQU]->data)->GetCanFit()) {
				maxRandRooms++;
				if (((ARoom*)debugRoomMap[RoomShapeEnum::HEX]->data)->GetCanFit()) {
					maxRandRooms++;
				}
			}
			selectedRoomShape = (RoomShapeEnum)FMath::RandRange(0, maxRandRooms);
		}
	}
	// if we get have a valid room shape set our new room
	// in the same fashion as the room colliders.
	if (selectedRoomShapesArray.Contains(selectedRoomShape)) {
		SetMagnitudeAndNewWall(creationIterator->data->roomShape, selectedRoomShape, parentWall, transformData);
		FVector newLocationOffset;

		if (WallPositionEnum::Ceiling == parentWall ||
			WallPositionEnum::Floor == parentWall) {
			newLocationOffset = { currWallUpVector.X, currWallUpVector.Y, currWallUpVector.Z * transformData.magnitude };
		}
		else {
			newLocationOffset = { currWallForwardVector.X * transformData.magnitude, currWallForwardVector.Y * transformData.magnitude, currWallForwardVector.Z };
		}
		FRotator currRotation(currRoomWorldTransform.GetRotation());
		FVector4 tempVector;
		tempVector.X = 0.0f;
		tempVector.Y = 0.0f;
		tempVector.Z = transformData.zRotation + currRotation.Euler().Z;
		tempVector.W = 0.0f;

		FTransform newRoomWorldTransform;
		newRoomWorldTransform.SetTranslation(currRoomWorldTransform.GetLocation() + newLocationOffset);
		newRoomWorldTransform.SetRotation(FQuat::MakeFromEuler(tempVector));
		const TMap<TEnumAsByte<WallPositionEnum>, ARoomNode*> zeroMap;

		// Add room based off the parentWall 
		if (WallPositionEnum::Ceiling == parentWall) {
			switch (creationIterator->data->roomType) {
			case RoomTypeEnum::Stairs_Ceiling: {
				TArray<TEnumAsByte<RoomTypeEnum>> tempArray = { RoomTypeEnum::Stairs_Both, RoomTypeEnum::Hole_Both, RoomTypeEnum::Hole_Floor };
				selectedRoomType = tempArray[FMath::RandRange(0, tempArray.Num() - 1)];
				break;
			}
			case RoomTypeEnum::Stairs_Both: {
				TArray<TEnumAsByte<RoomTypeEnum>> tempArray = { RoomTypeEnum::Stairs_Both, RoomTypeEnum::Hole_Both, RoomTypeEnum::Hole_Floor };
				selectedRoomType = tempArray[FMath::RandRange(0, tempArray.Num() - 1)];
				break;
			}
			case RoomTypeEnum::Hole_Ceiling: {
				TArray<TEnumAsByte<RoomTypeEnum>> tempArray = { RoomTypeEnum::Hole_Both, RoomTypeEnum::Hole_Floor };
				selectedRoomType = tempArray[FMath::RandRange(0, tempArray.Num() - 1)];
				break;
			}
			case RoomTypeEnum::Hole_Both: {
				TArray<TEnumAsByte<RoomTypeEnum>> tempArray = { RoomTypeEnum::Hole_Both, RoomTypeEnum::Hole_Floor };
				selectedRoomType = tempArray[FMath::RandRange(0, tempArray.Num() - 1)];
				break;
			}
			default: {

			}
			};
			AddRoomToLevel(parentWall, WallPositionEnum::Floor, selectedRoomShape, selectedRoomType, zeroMap, newRoomWorldTransform);
		}
		else if (WallPositionEnum::Floor == parentWall) {
			switch (creationIterator->data->roomType) {
			case RoomTypeEnum::Stairs_Both: {
				TArray<TEnumAsByte<RoomTypeEnum>> tempArray = { RoomTypeEnum::Stairs_Both, RoomTypeEnum::Stairs_Ceiling };
				selectedRoomType = tempArray[FMath::RandRange(0, tempArray.Num() - 1)];
				break;
			}
			case RoomTypeEnum::Hole_Floor: {
				TArray<TEnumAsByte<RoomTypeEnum>> tempArray = { RoomTypeEnum::Hole_Both, RoomTypeEnum::Hole_Ceiling };
				selectedRoomType = tempArray[FMath::RandRange(0, tempArray.Num() - 1)];
				break;
			}
			case RoomTypeEnum::Hole_Both: {
				TArray<TEnumAsByte<RoomTypeEnum>> tempArray = { RoomTypeEnum::Hole_Both, RoomTypeEnum::Hole_Ceiling };
				selectedRoomType = tempArray[FMath::RandRange(0, tempArray.Num() - 1)];
				break;
			}
			default: {

			}
			};
			AddRoomToLevel(parentWall, WallPositionEnum::Ceiling, selectedRoomShape, selectedRoomType, zeroMap, newRoomWorldTransform);
		}
		else {
			selectedRoomType = (RoomTypeEnum)FMath::RandRange(0, ((uint8)RoomTypeEnum::NUM_ROOMS_TYPES) - 1);
			AddRoomToLevel(parentWall, WallPositionEnum::Front, selectedRoomShape, selectedRoomType, zeroMap, newRoomWorldTransform);
		}
		return true;
	}
	// we didn't find a valid room shape.
	return false;
}

void AInfiniteLevel::SetMagnitudeAndNewWall(TEnumAsByte<RoomShapeEnum> _currRoomShape, TEnumAsByte<RoomShapeEnum> _nextRoomShape, TEnumAsByte<WallPositionEnum> _currWall, FNextRoomTransformData& transformData) {
	transformData.newWall = WallPositionEnum::Front;
	if (_currRoomShape == RoomShapeEnum::TRI) {
		SetMagnitudeAndNewWallTRI(_nextRoomShape, _currWall, transformData);
	}
	else if (_currRoomShape == RoomShapeEnum::SQU) {
		SetMagnitudeAndNewWallSQU(_nextRoomShape, _currWall, transformData);
	}
	else if (_currRoomShape == RoomShapeEnum::HEX) {
		SetMagnitudeAndNewWallHEX(_nextRoomShape, _currWall, transformData);
	}

}

void AInfiniteLevel::SetMagnitudeAndNewWallTRI(TEnumAsByte<RoomShapeEnum> _nextRoomShape, TEnumAsByte<WallPositionEnum> _currWall, FNextRoomTransformData& transformData) {
	TArray<TEnumAsByte<WallPositionEnum>> collidedWallsForPefectFitKeyArray;

	if (WallPositionEnum::Floor == _currWall) {
		transformData.magnitude = VERTICAL;
		transformData.zRotation = 180.0f;
	}
	else if (WallPositionEnum::Ceiling == _currWall) {
		transformData.magnitude = VERTICAL;
		transformData.zRotation = 180.0f;
	}
	else {
		switch (_nextRoomShape) {
		case RoomShapeEnum::TRI: {

			transformData.magnitude = TRI_TO_TRI;
			if (WallPositionEnum::Front == _currWall)
				transformData.zRotation = 180.0f;
			else if (WallPositionEnum::Right == _currWall)
				transformData.zRotation = 300.0f;
			else if (WallPositionEnum::Left == _currWall)
				transformData.zRotation = 60.0f;
			break;
		}
		case RoomShapeEnum::SQU: {
			transformData.magnitude = TRI_TO_SQU;
			if (WallPositionEnum::Front == _currWall)
				transformData.zRotation = 180.0f;
			else if (WallPositionEnum::Right == _currWall)
				transformData.zRotation = 300.0f;
			else if (WallPositionEnum::Left == _currWall)
				transformData.zRotation = 60.0f;
			break;
		}
		case RoomShapeEnum::HEX: {
			transformData.magnitude = TRI_TO_HEX;
			if (WallPositionEnum::Front == _currWall)
				transformData.zRotation = 180.0f;
			else if (WallPositionEnum::Right == _currWall)
				transformData.zRotation = 300.0f;
			else if (WallPositionEnum::Left == _currWall)
				transformData.zRotation = 60.0f;
			break;
		}
		};
	}
}

void AInfiniteLevel::SetMagnitudeAndNewWallSQU(TEnumAsByte<RoomShapeEnum> _nextRoomShape, TEnumAsByte<WallPositionEnum> _currWall, FNextRoomTransformData& transformData) {
	TArray<TEnumAsByte<WallPositionEnum>> collidedWallsForPefectFitKeyArray;
	if (WallPositionEnum::Floor == _currWall) {
		transformData.magnitude = VERTICAL;
		transformData.zRotation = 180.0f;
	}
	else if (WallPositionEnum::Ceiling == _currWall) {
		transformData.magnitude = VERTICAL;
		transformData.zRotation = 180.0f;
	}
	else {
		switch (_nextRoomShape) {
		case RoomShapeEnum::TRI: {
			transformData.magnitude = TRI_TO_SQU;
			if (WallPositionEnum::Front == _currWall)
				transformData.zRotation = 180.0f;
			else if (WallPositionEnum::Right == _currWall)
				transformData.zRotation = 270.0f;
			else if (WallPositionEnum::Back == _currWall)
				transformData.zRotation = 0.0f;
			else if (WallPositionEnum::Left == _currWall)
				transformData.zRotation = 90.0f;
			break;
		}
		case RoomShapeEnum::SQU: {
			transformData.magnitude = SQU_TO_SQU;
			if (WallPositionEnum::Front == _currWall)
				transformData.zRotation = 180.0f;
			else if (WallPositionEnum::Right == _currWall)
				transformData.zRotation = 270.0f;
			else if (WallPositionEnum::Back == _currWall)
				transformData.zRotation = 0.0f;
			else if (WallPositionEnum::Left == _currWall)
				transformData.zRotation = 90.0f;
			break;
		}
		case RoomShapeEnum::HEX: {
			transformData.magnitude = SQU_TO_HEX;
			if (WallPositionEnum::Front == _currWall)
				transformData.zRotation = 180.0f;
			else if (WallPositionEnum::Right == _currWall)
				transformData.zRotation = 270.0f;
			else if (WallPositionEnum::Back == _currWall)
				transformData.zRotation = 0.0f;
			else if (WallPositionEnum::Left == _currWall)
				transformData.zRotation = 90.0f;
			break;
		}
		}
	}
}

void AInfiniteLevel::SetMagnitudeAndNewWallHEX(TEnumAsByte<RoomShapeEnum> _nextRoomShape, TEnumAsByte<WallPositionEnum> _currWall, FNextRoomTransformData& transformData) {
	TArray<TEnumAsByte<WallPositionEnum>> collidedWallsForPefectFitKeyArray;
	if (WallPositionEnum::Floor == _currWall) {
		transformData.magnitude = VERTICAL;
		transformData.zRotation = 180.0f;
	}
	else if (WallPositionEnum::Ceiling == _currWall) {
		transformData.magnitude = VERTICAL;
		transformData.zRotation = 180.0f;
	}
	else {
		switch (_nextRoomShape) {
		case RoomShapeEnum::TRI: {
			transformData.magnitude = TRI_TO_HEX;
			if (WallPositionEnum::Front == _currWall)
				transformData.zRotation = 180.0f;
			else if (WallPositionEnum::Front_Right == _currWall)
				transformData.zRotation = 240.0f;
			else if (WallPositionEnum::Back_Right == _currWall)
				transformData.zRotation = 300.0f;
			else if (WallPositionEnum::Back == _currWall)
				transformData.zRotation = 0.0f;
			else if (WallPositionEnum::Back_Left == _currWall)
				transformData.zRotation = 60.0f;
			else if (WallPositionEnum::Front_Left == _currWall)
				transformData.zRotation = 120.0f;
			break;
		}
		case RoomShapeEnum::SQU: {
			transformData.magnitude = SQU_TO_HEX;
			if (WallPositionEnum::Front == _currWall)
				transformData.zRotation = 180.0f;
			else if (WallPositionEnum::Front_Right == _currWall)
				transformData.zRotation = 240.0f;
			else if (WallPositionEnum::Back_Right == _currWall)
				transformData.zRotation = 300.0f;
			else if (WallPositionEnum::Back == _currWall)
				transformData.zRotation = 0.0f;
			else if (WallPositionEnum::Back_Left == _currWall)
				transformData.zRotation = 60.0f;
			else if (WallPositionEnum::Front_Left == _currWall)
				transformData.zRotation = 120.0f;
			break;
		}
		case RoomShapeEnum::HEX: {
			transformData.magnitude = HEX_TO_HEX;
			if (WallPositionEnum::Front == _currWall)
				transformData.zRotation = 180.0f;
			else if (WallPositionEnum::Front_Right == _currWall)
				transformData.zRotation = 240.0f;
			else if (WallPositionEnum::Back_Right == _currWall)
				transformData.zRotation = 300.0f;
			else if (WallPositionEnum::Back == _currWall)
				transformData.zRotation = 0.0f;
			else if (WallPositionEnum::Back_Left == _currWall)
				transformData.zRotation = 60.0f;
			else if (WallPositionEnum::Front_Left == _currWall)
				transformData.zRotation = 120.0f;
			break;
		}
		}
	}
}

void AInfiniteLevel::CreateLevelFromPlayer(FTransform startingWorldPos, int numGenerations) {

	generations = numGenerations;
	if (playerNode == NULL) {
		SetStartNode(startingWorldPos);
		roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
	}
	SetCollisionRooms();
	int i = 0;
	SetCollisionRoomsVisibility(true);
	int generation = 0;

	if (generation < generations) {
		creationIterator = roomArray[i];
		if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Floor]->GetChildActor())->isConnected) {
			// don't turn this on yet,  working on collision and lining up rooms.
			if(PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Floor, i)){
				roomCounter++;
				roomsToDrawBuffer.Add(roomArray[roomArray.Num()-1]);
			}
		}
		if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Ceiling]->GetChildActor())->isConnected) {
			// don't turn this on yet,  working on collision and lining up rooms.
			if(PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Ceiling, i)){
			roomCounter++;
				roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
		}
		if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Front]->GetChildActor())->isConnected) {
			if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Front, i)) {
				roomCounter++;
				roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
			}
		}
		switch (creationIterator->data->roomShape)
		{
		case RoomShapeEnum::HEX: {
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Front_Right]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Front_Right, i)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Back_Right]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Back_Right, i)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Back]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Back, i)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Back_Left]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Back_Left, i)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Front_Left]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Front_Left, i)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			break;
		}
		case RoomShapeEnum::SQU: {
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Right]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Right, i)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Back]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Back, i)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Left]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Left, i)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			break;
		}
		case RoomShapeEnum::TRI: {
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Right]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Right, i)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Left]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Left, i)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			break;
		}
		default:
			break;
		}
		TArray<ARoomNode*> childRoomsArray;
		creationIterator->connectedRooms.GenerateValueArray(childRoomsArray);
		generation++;
		for (ARoomNode* childRoom : childRoomsArray) {
			CreateLevelFromPlayerRecursive(childRoom, generation, i+1);
		}
	}
	generation--;

	SetCollisionRoomsVisibility(false);
}

// Issue here is that building the level vertically results in rooms overlapping with eachother.
void AInfiniteLevel::CreateLevelFromPlayerRecursive(ARoomNode* _playerNode, int generation, int itter) {
	// check to see if our playerNode is good.
	if (playerNode == NULL) {
		// Error out or player is dead
		return;
	}

	// if this node isn't in there, add it to the list of rooms to draw.
	if (!roomsToDrawBuffer.Contains(_playerNode))
		roomsToDrawBuffer.Add(_playerNode);

	// turn on our rooms used for collision.
	SetCollisionRoomsVisibility(true);

	// if the current generation passed in is less than the max generation
	// that was set when the level was first generated.
	if (generation < generations) {
		// create rooms from the room passed in.
		creationIterator = _playerNode;
		// if the floor is not connected, try to add a room.
		if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Floor]->GetChildActor())->isConnected) {
			if(PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Floor, itter)){
				// if we can place a room increase the room counter and 
				// add the room to the list of rooms to draw.
				roomCounter++;
				roomsToDrawBuffer.Add(roomArray[roomArray.Num()-1]);
			}
		}
		// do the same thing for the ceiling
		if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Ceiling]->GetChildActor())->isConnected) {
			if(PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Ceiling, itter)){
				roomCounter++;
				roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
			}
		}
		// do the same thing for the front wall
		if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Front]->GetChildActor())->isConnected) {
			if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Front, itter)) {
				roomCounter++;
				roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
			}
		}

		// do the same thing for each wall.
		// we will check our room shape to see which walls we need to check.
		switch (creationIterator->data->roomShape)
		{
		case RoomShapeEnum::HEX: {
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Front_Right]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Front_Right, itter)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Back_Right]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Back_Right, itter)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Back]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Back, itter)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Back_Left]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Back_Left, itter)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Front_Left]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Front_Left, itter)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			break;
		}
		case RoomShapeEnum::SQU: {
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Right]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Right, itter)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Back]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Back, itter)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Left]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Left, itter)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			break;
		}
		case RoomShapeEnum::TRI: {
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Right]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Right, itter)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			if (!((AWall*)creationIterator->data->roomWalls[WallPositionEnum::Left]->GetChildActor())->isConnected) {
				if (PlaceNewRoom(creationIterator->data->roomShape, WallPositionEnum::Left, itter)) {
					roomCounter++;
					roomsToDrawBuffer.Add(roomArray[roomArray.Num() - 1]);
				}
			}
			break;
		}
		default:
			break;
		}

		// grab the rooms connected to the room we're creating rom.
		// increment current generation (passed in) and itter.
		// call CreateLevelFromPlayerRecursive for each child.
		TArray<ARoomNode*> childRoomsArray;
		creationIterator->connectedRooms.GenerateValueArray(childRoomsArray);
		for (ARoomNode* childRoom : childRoomsArray) {
			CreateLevelFromPlayerRecursive(childRoom, ++generation, ++itter);
		}
	}
	//decrement the current generation
	generation--;

	// turn off rooms used for collision.
	SetCollisionRoomsVisibility(false);
}

void AInfiniteLevel::RemoveRoomsFromRoomList() {
	// for the number of rooms added in our roomsArray list
	for (int i = roomArray.Num() - 1; i >= 0; --i) {
		// if the current room is not in our draw buffer
		// grab the keys for the connected rooms.
		if (!roomsToDrawBuffer.Contains(roomArray[i])) {
			TArray<TEnumAsByte<WallPositionEnum>> wallPositionArray;
			roomArray[i]->connectedRooms.GenerateKeyArray(wallPositionArray);
			// for each key
			// grab the keys for the connected room's connected rooms.
			for (TEnumAsByte<WallPositionEnum> wallPosition : wallPositionArray) {
				TArray<TEnumAsByte<WallPositionEnum>> childWallPositionArray;
				roomArray[i]->connectedRooms[wallPosition]->connectedRooms.GenerateKeyArray(childWallPositionArray);
				// for each key
				// if the connected room's connected room is our current room
				// unconnect and the connected room's connected room at the wall and back out.
				for (TEnumAsByte<WallPositionEnum> childWallPosition : childWallPositionArray) {
					if (roomArray[i]->connectedRooms[wallPosition]->connectedRooms[childWallPosition] == roomArray[i]) {
						((AWall*)roomArray[i]->connectedRooms[wallPosition]->data->roomWalls[childWallPosition]->GetChildActor())->isConnected = false;
						roomArray[i]->connectedRooms[wallPosition]->connectedRooms.Remove(childWallPosition);
						break;
					}
				}
				// unconnect and the connected room at the wall.
				((AWall*)roomArray[i]->data->roomWalls[wallPosition]->GetChildActor())->isConnected = false;
				roomArray[i]->connectedRooms.Remove(wallPosition);
			}
			// return the current room to the objectManager.
			// and decrease the counter.
			objectManager->ReturnRoom(roomArray[i]);
			roomArray.RemoveAt(i);
			roomCounter--;
		}
	}
	// empty the draw buffer.
	roomsToDrawBuffer.Empty();
}

void AInfiniteLevel::SetStartNode(FTransform startingWorldPos) {
	if (startHere == NULL) {
		RoomShapeEnum randShape = (RoomShapeEnum)FMath::RandRange(0, ((uint8)RoomShapeEnum::NUM_ROOM_SHAPE) - 1);
		const TMap<TEnumAsByte<WallPositionEnum>, ARoomNode*> zeroMap;
		RoomTypeEnum randType = RoomTypeEnum::Stairs_Both;//(RoomTypeEnum)FMath::RandRange(0, ((uint8)RoomTypeEnum::NUM_ROOMS_TYPES) - 1);
		AddRoomToLevel(WallPositionEnum::NULL_WALL, WallPositionEnum::NULL_WALL, randShape, randType, zeroMap, startingWorldPos);
	}
}

void AInfiniteLevel::AddRoomToLevel(TEnumAsByte<WallPositionEnum> _parentConnectedWall, TEnumAsByte<WallPositionEnum> _childConnectedWall, TEnumAsByte<RoomShapeEnum> roomShape, TEnumAsByte<RoomTypeEnum> _selectedRoomType, TMap<TEnumAsByte<WallPositionEnum>, ARoomNode*> _connectedRooms, FTransform& worldPos) {
	//Spawn the first room.
	if (startHere == NULL) {
		startHere = creationIterator = playerNode = objectManager->GetRoom(roomShape);
		startHere->data->SetActorTransform(worldPos);
		startHere->data->SetRoomByType(_selectedRoomType);
		roomArray.Add(startHere);
	}
	else {
		ARoomNode* temp = objectManager->GetRoom(roomShape);
		temp->data->SetActorTransform(worldPos);
		temp->data->SetRoomByType(_selectedRoomType);
		creationIterator->connectedRooms.Add(_parentConnectedWall, temp);
		temp->connectedRooms.Add(_childConnectedWall, creationIterator);
		if (WallPositionEnum::Floor == _parentConnectedWall ||
			WallPositionEnum::Ceiling == _parentConnectedWall) {
			((AFloor*)creationIterator->data->roomWalls[_parentConnectedWall]->GetChildActor())->isConnected = true;;
			((AFloor*)temp->data->roomWalls[_childConnectedWall]->GetChildActor())->isConnected = true;
		}
		else {
			((AWall*)creationIterator->data->roomWalls[_parentConnectedWall]->GetChildActor())->isConnected = true;;
			((AWall*)temp->data->roomWalls[_childConnectedWall]->GetChildActor())->isConnected = true;
		}
		roomArray.Add(temp);
	}
}

void AInfiniteLevel::SetCollisionRooms() {
	if (0 == debugRoomMap.Num()) {
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = (AActor*)this;
		SpawnInfo.Instigator = NULL;
		SpawnInfo.ObjectFlags |= RF_Transient;
		FTransform worldTransformsForDefaultObj;
		FVector position = { 900000.0f, 900000.0f, 900000.0f };
		worldTransformsForDefaultObj.SetLocation(position);
		debugRoomMap.Add(RoomShapeEnum::TRI, NewObject<ARoomNode>(ARoomNode::StaticClass()));
		debugRoomMap.Add(RoomShapeEnum::SQU, NewObject<ARoomNode>(ARoomNode::StaticClass()));
		debugRoomMap.Add(RoomShapeEnum::HEX, NewObject<ARoomNode>(ARoomNode::StaticClass()));
		debugRoomMap[RoomShapeEnum::TRI]->CreateRoom(this->GetWorld(), SpawnInfo, objectManager->roomClassesMap[RoomShapeEnum::TRI], RoomShapeEnum::TRI, worldTransformsForDefaultObj);
		debugRoomMap[RoomShapeEnum::SQU]->CreateRoom(this->GetWorld(), SpawnInfo, objectManager->roomClassesMap[RoomShapeEnum::SQU], RoomShapeEnum::SQU, worldTransformsForDefaultObj);
		debugRoomMap[RoomShapeEnum::HEX]->CreateRoom(this->GetWorld(), SpawnInfo, objectManager->roomClassesMap[RoomShapeEnum::HEX], RoomShapeEnum::HEX, worldTransformsForDefaultObj);
		//debugRoomMap[RoomShapeEnum::TRI]->data->SetActorLocation(position);
		//debugRoomMap[RoomShapeEnum::SQU]->data->SetActorLocation(position);     
		//debugRoomMap[RoomShapeEnum::HEX]->data->SetActorLocation(position);
	}
}

void AInfiniteLevel::SetCollisionRoomsVisibility(bool isVisible) {
	if (0 != debugRoomMap.Num()) {
		debugRoomMap[RoomShapeEnum::TRI]->SetActive(isVisible);

		debugRoomMap[RoomShapeEnum::SQU]->SetActive(isVisible);

		debugRoomMap[RoomShapeEnum::HEX]->SetActive(isVisible);
	}
}

void AInfiniteLevel::CloseWalls() {
	for (ARoomNode* room : roomArray) {
		TArray<TEnumAsByte<WallPositionEnum>> positionArray;
		room->data->roomWalls.GenerateKeyArray(positionArray);
		for (WallPositionEnum position : positionArray) {
			if (!((AWall*)room->data->roomWalls[position]->GetChildActor())->isConnected) {
				switch (position) {
				case WallPositionEnum::Ceiling: {
					switch (room->data->roomType) {
					case RoomTypeEnum::Stairs_Ceiling: {
						room->data->SetRoomByType(RoomTypeEnum::Normal);
						break;
					}
					case RoomTypeEnum::Stairs_Both: {
						room->data->SetRoomByType(RoomTypeEnum::Hole_Floor);
						break;
					}
					case RoomTypeEnum::Hole_Ceiling: {
						room->data->SetRoomByType(RoomTypeEnum::Normal);
						break;
					}
					case RoomTypeEnum::Hole_Both: {
						room->data->SetRoomByType(RoomTypeEnum::Hole_Floor);
						break;
					}

					default: {

					}
					};
					break;
				}
				case WallPositionEnum::Floor: {
					switch (room->data->roomType) {
					case RoomTypeEnum::Stairs_Both: {
						room->data->SetRoomByType(RoomTypeEnum::Stairs_Ceiling);
						break;
					}
					case RoomTypeEnum::Hole_Floor: {
						room->data->SetRoomByType(RoomTypeEnum::Normal);
						break;
					}
					case RoomTypeEnum::Hole_Both: {
						room->data->SetRoomByType(RoomTypeEnum::Hole_Ceiling);
						break;
					}
					default: {

					}
					};
					break;
				}
				default: {
					((AWall*)room->data->roomWalls[position]->GetChildActor())->ShowWall(true);
				}
				};
			}
		}
	}
}