// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

// TODO Ist in 0.9.6 nicht vorhanden, aber in  0.9.9. Weiß auch nicht woher das kommt.
// #include "WheeledVehicle.h"
#include<iostream>
#include "Scoomatic/CarlaScoomaticBaseState.h"
#include "Scoomatic/ScoomaticControl.h"
// #include "Vehicle/VehicleLightState.h" // TODO lights were not included in 0.9.6, required now?
#include "Scoomatic/ScoomaticInputPriority.h"
// #include "Vehicle/VehiclePhysicsControl.h" // TODO no scoomatic physics control?
// #include "WheeledVehicleMovementComponent4W.h" // TODO no movement component

#include "CoreMinimal.h"

#include "CarlaScoomaticBase.generated.h"

class UBoxComponent;

/// Base class for CARLA Scoomatic Bases.
UCLASS()
class CARLA_API ACarlaScoomaticBase : public APawn
{
  GENERATED_BODY()

  // ===========================================================================
  /// @name Constructor and destructor
  // ===========================================================================
  /// @{
public:

  ACarlaScoomaticBase(const FObjectInitializer &ObjectInitializer);

  ~ACarlaScoomaticBase();

  void Tick(float DeltaTime) override;

  /// @}
  // ===========================================================================
  /// @name Get functions
  // ===========================================================================
  /// @{
public:

  /// Scoomatic control currently applied to this Scoomatic.
  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  const FScoomaticControl &GetScoomaticControl() const
  {
    return LastAppliedControl;
  }

  /// Transform of the Scoomatic. Location is shifted so it matches center of the
  /// Scoomatic bounds rather than the actor's location.
  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  FTransform GetScoomaticTransform() const
  {
    return GetActorTransform();
  }
/* TODO Forward speed previously not implemented in Scoomatic 0.9.6
  /// Forward speed in cm/s. Might be negative if goes backwards.
  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  float GetVehicleForwardSpeed() const;
  */

  /// Orientation vector of the vehicle, pointing forward.
  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  FVector GetScoomaticOrientation() const;

/* No gear for Scoomatic
  /// Active gear of the vehicle.
  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  int32 GetVehicleCurrentGear() const;
  */

  /// Transform of the Scoomatic's bounding box relative to the Scoomatic.
  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  FTransform GetScoomaticBoundingBoxTransform() const;

  /// Extent of the Scoomatic's bounding box.
  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  FVector GetScoomaticBoundingBoxExtent() const;

  /// Get Scoomatics's bounding box component.
  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  UBoxComponent *GetScoomaticBoundingBox() const
  {
    return ScoomaticBounds;
  }

/*
  /// Get the maximum angle at which the front wheel can steer.
  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  float GetMaximumSteerAngle() const;
*/

/* TODO AI debug state is new?
  /// @}
  // ===========================================================================
  /// @name AI debug state
  // ===========================================================================
  /// @{
public:

  /// @todo This function should be private to AScoomaticBaseAIController.
  void SetAIVehicleState(ECarlaScoomaticBaseState InState)
  {
    State = InState;
  }

  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  ECarlaScoomaticBaseState GetAIVehicleState() const
  {
    return State;
  }

  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  FVehiclePhysicsControl GetVehiclePhysicsControl();

  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  FVehicleLightState GetVehicleLightState();

  void ApplyVehiclePhysicsControl(const FVehiclePhysicsControl &PhysicsControl);

  // void SetVehicleLightState(const FVehicleLightState &LightState); // TODO light state
*/

  /// @}
  // ===========================================================================
  /// @name Scoomatic input control
  // ===========================================================================
  /// @{
public:

  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  void ApplyScoomaticControl(const FScoomaticControl &Control, EScoomaticInputPriority Priority)
  {
    if (InputControl.Priority <= Priority)
    {
      InputControl.Control = Control;
      InputControl.Priority = Priority;
    }
  }

  /// @todo This function should be private to AScoomaticBaseAIController.
  void FlushScoomaticControl();

  /// @}
  // ===========================================================================
  /// @name DEPRECATED Set functions
  // ===========================================================================
  /// @{
public:

  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  void SetLeftVelocity(float Value);

  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  void SetRightVelocity(float Value);

  /// @}
  // ===========================================================================
  /// @name Overriden from AActor
  // ===========================================================================
  /// @{

protected:

  virtual void BeginPlay() override;

  // TODO necessary?
  // UFUNCTION(BlueprintImplementableEvent)
  // void RefreshLightState(const FVehicleLightState &VehicleLightState);

  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  float GetLeftVelocity()
  {
    return VelocityLeft;
  }

  UFUNCTION(Category = "CARLA Scoomatic Base", BlueprintCallable)
  float GetRightVelocity()
  {
    return VelocityRight;
  }

  UPROPERTY(Category = "Scoomatic Attribute", VisibleAnywhere)
  float VelocityLeft;
  UPROPERTY(Category = "Scoomatic Attribute", VisibleAnywhere)
  float VelocityRight;

private:

  /// Current state of the Scoomatic controller (for debugging purposes).
  UPROPERTY(Category = "AI Controller", VisibleAnywhere)
  ECarlaScoomaticBaseState State = ECarlaScoomaticBaseState::UNKNOWN;

  UPROPERTY(Category = "CARLA Scoomatic Base", EditAnywhere)
  UBoxComponent *ScoomaticBounds;

  struct
  {
    EScoomaticInputPriority Priority = EScoomaticInputPriority::INVALID;
    FScoomaticControl Control;
    // FVehicleLightState LightState;
  }
  InputControl;

  FScoomaticControl LastAppliedControl;
};
