// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	UE_LOG(LogTemp, Display, TEXT("Configured moved distance: %f"), MaxDistance);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	if (FVector::Dist(CurrentLocation, StartLocation) >= MaxDistance)
	{
		float OverShoot = FVector::Dist(CurrentLocation, StartLocation) - MaxDistance;
		FString Name = GetName();
		UE_LOG(LogTemp, Display, TEXT("%s Overshot by: %f"), *Name, OverShoot);
		PlatformVelocity = -PlatformVelocity;
		StartLocation = CurrentLocation;
	}
	CurrentLocation += PlatformVelocity * DeltaTime;
	SetActorLocation(CurrentLocation);
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation += RotationVelocity * DeltaTime;
	SetActorRotation(CurrentRotation);
}



