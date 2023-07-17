// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

#include <queue>

#include "GameFramework/Controller.h"

// #include "Traffic/TrafficLightState.h"
#include "Scoomatic/ScoomaticControl.h"

#include "ScoomaticBaseAIController.generated.h"

class ACarlaScoomaticBase;
// TODO class URandomEngine;
// TODO class URoadMap;

/// Wheeled vehicle controller with optional AI.
UCLASS()
class CARLA_API AScoomaticBaseAIController final : public AController
{
  GENERATED_BODY()

  // ===========================================================================
  /// @name Constructor and destructor
  // ===========================================================================
  /// @{

public:

  AScoomaticBaseAIController(const FObjectInitializer &ObjectInitializer);

  ~AScoomaticBaseAIController();

  /// @}
  // ===========================================================================
  /// @name Controller overrides
  // ===========================================================================
  /// @{

public:

  void OnPossess(APawn *aPawn) override;

  void OnUnPossess() override;

  void Tick(float DeltaTime) override;

  /// @}
  // ===========================================================================
  /// @name Possessed vehicle
  // ===========================================================================
  /// @{

public:

  UFUNCTION(Category = "Scoomatic Base Controller", BlueprintCallable)
  bool IsPossessingAScoomatic() const
  {
    return Scoomatic != nullptr;
  }

  // TODO Warum kommt das hier zwei mal vor?
  UFUNCTION(Category = "Scoomatic Base Controller", BlueprintCallable)
  ACarlaScoomaticBase *GetPossessedScoomatic()
  {
    return Scoomatic;
  }

  const ACarlaScoomaticBase *GetPossessedScoomatic() const
  {
    return Scoomatic;
  }

  /// @}
  // ===========================================================================
  /// @name Control options
  // ===========================================================================
  /// @{

  UFUNCTION(Category = "Scoomatic Base Controller", BlueprintCallable)
  void SetStickyControl(bool bEnabled)
  {
    bControlIsSticky = bEnabled;
  }

  /// @}
  // ===========================================================================
  /// @name Road map
  // ===========================================================================
  /// @{

/* TODO
public:

  void SetRoadMap(URoadMap *InRoadMap)
  {
    RoadMap = InRoadMap;
  }

  UFUNCTION(Category = "Road Map", BlueprintCallable)
  URoadMap *GetRoadMap()
  {
    return RoadMap;
  }
*/

  /// @}
  // ===========================================================================
  /// @name Random engine
  // ===========================================================================
  /// @{

/* TODO
public:

  UFUNCTION(Category = "Random Engine", BlueprintCallable)
  URandomEngine *GetRandomEngine()
  {
    check(RandomEngine != nullptr);
    return RandomEngine;
  }
*/

  /// @}
  // ===========================================================================
  /// @name Autopilot
  // ===========================================================================
  /// @{

public:

  UFUNCTION(Category = "Scoomatic Base Controller", BlueprintCallable)
  bool IsAutopilotEnabled() const
  {
    return bAutopilotEnabled;
  }

  /* TODO
  UFUNCTION(Category = "Wheeled Vehicle Controller", BlueprintCallable)
  void SetAutopilot(bool Enable, bool KeepState = false)
  {
    if (IsAutopilotEnabled() != Enable)
    {
      ConfigureAutopilot(Enable, KeepState);
    }
  }

  UFUNCTION(Category = "Wheeled Vehicle Controller", BlueprintCallable)
  void ToggleAutopilot()
  {
    ConfigureAutopilot(!bAutopilotEnabled);
  }

private:

  void ConfigureAutopilot(const bool Enable, const bool KeepState = false);
*/

  /// @}
  // ===========================================================================
  /// @name Traffic
  // ===========================================================================
  /// @{

/* TODO
public:

  /// Get current speed limit in km/h.
  UFUNCTION(Category = "Wheeled Vehicle Controller", BlueprintCallable)
  float GetSpeedLimit() const
  {
    return SpeedLimit;
  }

  /// Set vehicle's speed limit in km/h.
  UFUNCTION(Category = "Wheeled Vehicle Controller", BlueprintCallable)
  void SetSpeedLimit(float InSpeedLimit)
  {
    SpeedLimit = InSpeedLimit;
  }

  /// Get traffic light state currently affecting this vehicle.
  UFUNCTION(Category = "Wheeled Vehicle Controller", BlueprintCallable)
  ETrafficLightState GetTrafficLightState() const
  {
    return TrafficLightState;
  }

  /// Set traffic light state currently affecting this vehicle.
  UFUNCTION(Category = "Wheeled Vehicle Controller", BlueprintCallable)
  void SetTrafficLightState(ETrafficLightState InTrafficLightState)
  {
    TrafficLightState = InTrafficLightState;
  }

  /// Get traffic light currently affecting this vehicle.
  UFUNCTION(Category = "Wheeled Vehicle Controller", BlueprintCallable)
  ATrafficLightBase *GetTrafficLight() const
  {
    return TrafficLight;
  }

  /// Set traffic light currently affecting this vehicle.
  UFUNCTION(Category = "Wheeled Vehicle Controller", BlueprintCallable)
  void SetTrafficLight(ATrafficLightBase *InTrafficLight)
  {
    TrafficLight = InTrafficLight;
  }

  /// Set a fixed route to follow if autopilot is enabled.
  UFUNCTION(Category = "Wheeled Vehicle Controller", BlueprintCallable)
  void SetFixedRoute(const TArray<FVector> &Locations, bool bOverwriteCurrent = true);

  /// @}

private:

  UPROPERTY()
  ACarlaWheeledVehicle *Vehicle = nullptr;

  UPROPERTY()
  URoadMap *RoadMap = nullptr;

  UPROPERTY()
  URandomEngine *RandomEngine = nullptr;

  UPROPERTY(VisibleAnywhere)
  bool bAutopilotEnabled = false;

  UPROPERTY(VisibleAnywhere)
  bool bControlIsSticky = true;

  UPROPERTY(VisibleAnywhere)
  float SpeedLimit = 30.0f;

  UPROPERTY(VisibleAnywhere)
  ETrafficLightState TrafficLightState = ETrafficLightState::Green;

  UPROPERTY(VisibleAnywhere)
  float MaximumSteerAngle = -1.0f;

  UPROPERTY()
  ATrafficLightBase *TrafficLight;

  std::queue<FVector> TargetLocations;
  */

 /// @}
  // ===========================================================================
  // -- Member variables -------------------------------------------------------
  // ===========================================================================
  /// @{

private:

  UPROPERTY() // TODO Das gab es in 0.9.9 nicht mehr
  ACarlaScoomaticBase *Scoomatic = nullptr;

  UPROPERTY(VisibleAnywhere)
  bool bAutopilotEnabled = false;

  UPROPERTY(VisibleAnywhere)
  bool bControlIsSticky = true;
};
