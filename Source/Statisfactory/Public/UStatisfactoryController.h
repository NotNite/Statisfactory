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

USTRUCT()
struct FTicketData {
  GENERATED_BODY()

  UPROPERTY()
  int Coupons;

  UPROPERTY()
  int PointsToNextCoupon;
};

UCLASS()
class STATISFACTORY_API UStatisfactoryController : public UFGServerControllerBase {
  GENERATED_BODY()

public:
  // Jank lol
  UPROPERTY()
  UWorld *World;

  UFUNCTION(FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator")
  FFGServerErrorResponse Statisfactory_GetPower(TArray<FPowerOutput> &OutData) const;

  UFUNCTION(FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator")
  FFGServerErrorResponse Statisfactory_GetDepots(TMap<FString, int32> &OutData) const;

  UFUNCTION(FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator")
  FFGServerErrorResponse Statisfactory_GetSink(FTicketData &OutData) const;
};
