// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "SFlyingMovementComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API USFlyingMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

	
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:

	/* MoveTo destination */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Destination;

	UPROPERTY(EditDefaultsOnly)
	float BumpImpulse;

	float VelocityDampening;

public:

	USFlyingMovementComponent();
};
