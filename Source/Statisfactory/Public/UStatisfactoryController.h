#pragma once
#include "CoreMinimal.h"
#include "FGServerControllerBase.h"
#include "Server/FGDSSharedTypes.h"

#include "UStatisfactoryController.generated.h"

USTRUCT()
struct FPowerOutput {
  GENERATED_BODY()

  UPROPERTY()
  int Id;

  UPROPERTY()
  float PowerConsumed;

  UPROPERTY()
  float PowerProduced;

  UPROPERTY()
  float PowerProductionCapacity;

  UPROPERTY()
  float MaximumPowerConsumption;

  UPROPERTY()
  float BatteryPowerInput;
};

UCLASS()
class STATISFACTORY_API UStatisfactoryController : public UFGServerControllerBase {
  GENERATED_BODY()

public:
  UPROPERTY()
  UWorld *World;

  // TODO: Authentication
  UFUNCTION(FGServerRequestHandler, FGServerRequestPrivilegeLevel = "NotAuthenticated")
  FFGServerErrorResponse Statisfactory_GetPower(TArray<FPowerOutput> &OutData);

  UFUNCTION(FGServerRequestHandler, FGServerRequestPrivilegeLevel = "NotAuthenticated")
  FFGServerErrorResponse Statisfactory_GetDepots(TMap<FString, int32> &OutData) const;
};
