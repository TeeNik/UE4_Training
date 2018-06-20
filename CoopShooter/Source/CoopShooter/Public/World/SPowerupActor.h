// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPowerupActor.generated.h"

UCLASS()
class COOPSHOOTER_API ASPowerupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerupActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "PowerUp")
	float PowerUpInterval;
	UPROPERTY(EditDefaultsOnly, Category = "PowerUp")
	int32 NumOfTicks;

	int32 TicksProcessed;

	FTimerHandle TimerHandle_PowerupTick;
	UFUNCTION()
	void OnTickPowerup();

public:	

	void ActivatePowerup();

	UFUNCTION(BlueprintImplementableEvent, Category="PowerUps")
	void OnActivated();
	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUps")
	void OnPowerupTicked();
	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUps")
	void OnExpired();
	
};
