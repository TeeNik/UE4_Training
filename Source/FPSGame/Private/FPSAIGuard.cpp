// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "FPSGameMode.h"


// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnSeePawn);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);

}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalRotation = GetActorRotation();

}

void AFPSAIGuard::OnSeePawn(APawn* SeenPawn)
{
	if (SeenPawn == nullptr) return;

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32, 12, FColor::Red, false, 10);
	AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->CompleteMission(SeenPawn, true);
	}
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32, 12, FColor::Green, false, 10);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0;
	NewLookAt.Roll = 0;

	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(ResetRotationTimer);
	GetWorldTimerManager().SetTimer(ResetRotationTimer, this, &AFPSAIGuard::ResetOrientation, 3);
}

void AFPSAIGuard::ResetOrientation()
{
	SetActorRotation(OriginalRotation);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

