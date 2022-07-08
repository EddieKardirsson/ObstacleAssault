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
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Move platform FORWARD
		// Get current location
	FVector CurrentLocation = GetActorLocation();
		// Add vector to that location
	CurrentLocation += PlatformVelocity * DeltaTime;
		// Set actor location
	SetActorLocation(CurrentLocation);
	// Send platform BACK if gone too far
		// Check how far platform moved
	DistanceMoved = FVector::Dist(StartingLocation, CurrentLocation);
		// Reverse direction of motion if gone too far
	if (DistanceMoved > MovedDistance) {				
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartingLocation += MoveDirection * MovedDistance;
		SetActorLocation(StartingLocation);
		PlatformVelocity = -PlatformVelocity;
	}
			
	 
}

