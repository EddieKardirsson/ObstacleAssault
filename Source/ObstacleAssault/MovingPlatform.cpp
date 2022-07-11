// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include "GameFramework/Character.h"

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

	StartingLocation = GetActorLocation();

	const FString Name = GetName();

	UE_LOG(LogTemp, Display, TEXT("Here's my string: %s"), *Name);
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
	if (ShouldPlatformReturn()) {		
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartingLocation += MoveDirection * MovedDistance;
		SetActorLocation(StartingLocation);
		PlatformVelocity = -PlatformVelocity;
	}else{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += PlatformVelocity * DeltaTime;
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	UE_LOG(LogTemp, Error, TEXT("RotatePlatform called by %s: Delta: %f"), *GetName(), DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MovedDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartingLocation, GetActorLocation());
}
