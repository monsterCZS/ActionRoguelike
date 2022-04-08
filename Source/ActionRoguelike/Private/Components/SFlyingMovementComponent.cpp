// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SFlyingMovementComponent.h"



USFlyingMovementComponent::USFlyingMovementComponent()
{
	BumpImpulse = 500.f;
	VelocityDampening = 1.0f;
}


void USFlyingMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldSkipUpdate(DeltaTime) || GetOwner() == nullptr)
	{
		return;
	}

	if (Velocity.SizeSquared() > 1.0f)
	{
		// Convert to a consistent velocity 'drag' regardless of current speed.
		const float DampeningDelta = (VelocityDampening) * DeltaTime;
		//float DragFactor = DampeningDelta / VelocitySize;
		Velocity *= FMath::Clamp(1.0f - DampeningDelta, 0.0f, 1.0f);
	}
	else
	{
		// Stop entirely avoid jitter
		Velocity = FVector(0);
	}

	if (Destination.IsNearlyZero())
	{
		// Assume 0,0,0 means no destination is set
		return;
	}

	FVector DesiredDirection = Destination - UpdatedComponent->GetComponentLocation();
	DesiredDirection.Normalize();
	
	// Add forces to the current velocity
	Velocity += DesiredDirection * 1000.0f * DeltaTime; // 'forward thrust'
	
	FVector DeltaMovement = Velocity * DeltaTime;
	
	// Move the ship in the world
	FHitResult Hit;
	SafeMoveUpdatedComponent(DeltaMovement, FQuat::Identity, true, Hit, ETeleportType::None);

	// Resolve any collision
	if (Hit.IsValidBlockingHit())
	{
		//HandleImpact(Hit, DeltaTime, DeltaMovement);

		// Override velocity entirely
		Velocity = Hit.ImpactNormal * BumpImpulse;
	}

	// Push new velocity into Component for other systems to read out
	UpdateComponentVelocity();
}