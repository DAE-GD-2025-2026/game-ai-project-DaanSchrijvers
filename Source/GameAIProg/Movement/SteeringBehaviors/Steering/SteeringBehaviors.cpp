#include "SteeringBehaviors.h"
#include "GameAIProg/Movement/SteeringBehaviors/SteeringAgent.h"

//SEEK
//*******
// TODO: Do the Week01 assignment :^)
//Seek
SteeringOutput Seek::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	Agent.SetMaxLinearSpeed(MaxSpeed);

	SteeringOutput Steering{};
	if (!Agent.GetLastMovementInputVector().Equals(FVector{}))
	{
		Steering.LinearVelocity = FVector2D{Agent.GetLastMovementInputVector().X, Agent.GetLastMovementInputVector().Y};
	}
	else
	{
		Steering.LinearVelocity = Target.Position - Agent.GetPosition();
	}
	int targetLeftOrRight = 1;
	if (Target.Position.Y < Agent.GetPosition().Y)
	{
		targetLeftOrRight = -1;
	}
	float targetAngle = targetLeftOrRight * acos(FVector2D(Target.Position - Agent.GetPosition()).GetSafeNormal().X);
	float angleDifference = targetAngle - (Agent.GetRotation() *PI / 180.f);
	if (angleDifference > PI)
	{
		angleDifference = angleDifference - 2 * PI;
	} 
	else if (angleDifference < -PI)
	{
		angleDifference = angleDifference + 2 * PI;
	}
	Steering.AngularVelocity = angleDifference * 180.f / PI;

	DrawDebugLine(
		Agent.GetWorld(),
		FVector{Agent.GetPosition().X, Agent.GetPosition().Y, 0},
		FVector{Target.Position.X, Target.Position.Y, 0},
		FColor::Green
	);

	return Steering;
}

//Flee
SteeringOutput Flee::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	Agent.SetMaxLinearSpeed(MaxSpeed);

	SteeringOutput Steering{};
	Steering.LinearVelocity = Agent.GetPosition() - Target.Position;

	DrawDebugLine(
		Agent.GetWorld(),
		FVector{Agent.GetPosition().X, Agent.GetPosition().Y, 0},
		FVector{Target.Position.X, Target.Position.Y, 0},
		FColor::Green
	);

	return Steering;
}
