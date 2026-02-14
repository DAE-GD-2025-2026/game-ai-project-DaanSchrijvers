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
    Steering.LinearVelocity = Target.Position - Agent.GetPosition();

    DrawDebugLine(
        Agent.GetWorld(),
        FVector{ Agent.GetPosition().X, Agent.GetPosition().Y,0 },
        FVector{ Target.Position.X, Target.Position.Y,0 },
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
        FVector{ Agent.GetPosition().X, Agent.GetPosition().Y,0 },
        FVector{ Target.Position.X, Target.Position.Y,0 },
        FColor::Green
    );

    return Steering;
}