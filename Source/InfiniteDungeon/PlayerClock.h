// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerClock.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INFINITEDUNGEON_API UPlayerClock : public UActorComponent
{
	GENERATED_BODY()
private:
	bool isTicking;

public:	
	UPROPERTY(BlueprintReadWrite, Category = "playerClock")
		float rate;

	UPROPERTY(BlueprintReadWrite, Category = "playerClock")
		float seconds;

	UPROPERTY(BlueprintReadWrite, Category = "playerClock")
		int minutes;

	UPROPERTY(BlueprintReadWrite, Category = "playerClock")
		int hours;

	UPROPERTY(BlueprintReadWrite, Category = "playerClock")
		int days;

	UPROPERTY(BlueprintReadWrite, Category = "playerClock")
		int weeks;

	// Sets default values for this component's properties
	UPlayerClock();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Clock Methods")
		void UpdateTimer(float deltaTime);

	UFUNCTION(BlueprintCallable, Category = "Clock Methods")
		void StopTimer();

	UFUNCTION(BlueprintCallable, Category = "Clock Methods")
		void PauseTimer();

	UFUNCTION(BlueprintCallable, Category = "Clock Methods")
		void StartTimer();

	UFUNCTION(BlueprintCallable, Category = "Clock Methods")
		void ResetTimer();
};
