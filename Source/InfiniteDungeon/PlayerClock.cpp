// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerClock.h"

// Sets default values for this component's properties
UPlayerClock::UPlayerClock()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	rate = 60.0f;
	StopTimer();
	// ...
}


// Called when the game starts
void UPlayerClock::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerClock::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateTimer(DeltaTime);
	// ...
}

void UPlayerClock::UpdateTimer(float deltaTime) {

	if (isTicking) {
		seconds += deltaTime;
		if (rate <= seconds) {
			minutes++;
			seconds -= 60.0f;
		}
		if (60 <= minutes) {
			hours++;
			minutes = 0;
		}
		if (24 <= hours) {
			days++;
			hours = 0;
		}
		if (7 <= days) {
			weeks++;
			days = 0;
		}
	}
}

void UPlayerClock::ResetTimer() {

	rate = 60.0f;

	seconds = 0;

	minutes = 0;

	hours = 0;

	days = 0;

	weeks = 0;
}

void UPlayerClock::StopTimer() { PauseTimer(); ResetTimer(); }

void UPlayerClock::PauseTimer() { isTicking = false; }

void UPlayerClock::StartTimer() { isTicking = true; }
