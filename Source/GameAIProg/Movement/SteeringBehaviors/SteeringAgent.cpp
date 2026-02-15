// Fill out your copyright notice in the Description page of Project Settings.

#include "SteeringAgent.h"

#include "Materials/MaterialExpressionArccosine.h"


// Sets default values
ASteeringAgent::ASteeringAgent()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASteeringAgent::BeginPlay()
{
	Super::BeginPlay();
}

void ASteeringAgent::BeginDestroy()
{
	Super::BeginDestroy();
}

// Called every frame
void ASteeringAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SteeringBehavior)
	{
		const float rotationSpeed = 2.f;;
		
		SteeringOutput output = SteeringBehavior->CalculateSteering(DeltaTime, *this);
		if (abs(output.AngularVelocity) < 0.3f)
		{
			DeltaTime = 1.f / rotationSpeed; //Angle will clip to target once it gets close enough
		}
		output.LinearVelocity = output.LinearVelocity.GetRotated(output.AngularVelocity * DeltaTime * rotationSpeed);
		
		AddMovementInput(FVector{output.LinearVelocity, 0.f});
	}
}

// Called to bind functionality to input
void ASteeringAgent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASteeringAgent::SetSteeringBehavior(ISteeringBehavior* NewSteeringBehavior)
{
	SteeringBehavior = NewSteeringBehavior;
}

