// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SWeapon.h"
#include "SCharacter.generated.h"



UCLASS()
class COOPSHOOTER_API ASCharacter : public ACharacter
{
GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void BeginCrouch();
	void EndCrouch();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;

	bool WantsToZoom;
	float DefaulFOV;
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float ZoomedFOV;
	UPROPERTY(EditDefaultsOnly, Category = "Player", meta=(ClampMin = 0.1, ClampMax = 100))
	float ZoomInterpSpeed;

	void BeginZoom();
	void EndZoom();

	ASWeapon* CurrentWeapon;
	void StartFire();
	void StopFire();

	UPROPERTY(EditDefaultsOnly, Category="Player")
	TSubclassOf<ASWeapon> StarterWeaponClass;

	UPROPERTY(VisibleDefaultsOnly, Category="Player")
	FName WeaponAttachSocketName;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;

};
