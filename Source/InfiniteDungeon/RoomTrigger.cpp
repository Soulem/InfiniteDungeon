// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomTrigger.h"

ARoomTrigger::ARoomTrigger()
{
	trapTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"), true);
	RootComponent = trapTrigger;
}

ARoomTrigger::~ARoomTrigger()
{
}
