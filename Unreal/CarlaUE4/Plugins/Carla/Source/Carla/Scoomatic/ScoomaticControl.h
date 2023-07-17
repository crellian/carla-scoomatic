#pragma once

#include "ScoomaticControl.generated.h"

USTRUCT(BlueprintType)
struct CARLA_API FScoomaticControl
{
    GENERATED_BODY()

    UPROPERTY(Category = "Scoomatic Control", EditAnywhere, BlueprintReadWrite)
    float LeftVelocity = 0.0f;

    UPROPERTY(Category = "Scoomatic Control", EditAnywhere, BlueprintReadWrite)
    float RightVelocity = 0.0f;
};