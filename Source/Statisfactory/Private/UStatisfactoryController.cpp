#include "UStatisfactoryController.h"

#include "../../../../../Source/FactoryGame/Public/Server/FGDSSharedTypes.h"
#include "FGCentralStorageSubsystem.h"
#include "FGCircuitSubsystem.h"
#include "FGDSSharedTypes.h"
#include "FGResourceSinkSubsystem.h"
#include "StructuredLog.h"

static FFGServerErrorResponse SubsystemError =
    FFGServerErrorResponse::Error("statisfactory_subsystem", "Couldn't get subsystem");

FFGServerErrorResponse STATISFACTORY_API
UStatisfactoryController::Statisfactory_GetPower(TArray<FPowerOutput> &OutData) const {
  OutData = {};

  auto Subsystem = AFGCircuitSubsystem::Get(this->World);
  if (Subsystem == nullptr)
    return SubsystemError;

  TArray<int> Seen = {};
  for (auto Pair : Subsystem->mCircuits) {
    auto Circuit = Pair.Value;
    if (const auto PowerCircuit = Cast<UFGPowerCircuit>(Circuit)) {
      auto Id = PowerCircuit->GetCircuitGroupID();
      if (Id == -1 || Seen.Contains(Id))
        continue;
      Seen.Push(Id);

      FPowerCircuitStats Stats = {};
      PowerCircuit->GetStats(Stats);

      FPowerOutput PowerOutput = {};
      PowerOutput.Id = Id;
      PowerOutput.PowerConsumed = Stats.PowerConsumed;
      PowerOutput.PowerProduced = Stats.PowerProduced;
      PowerOutput.PowerProductionCapacity = Stats.PowerProductionCapacity;
      PowerOutput.MaximumPowerConsumption = Stats.MaximumPowerConsumption;
      PowerOutput.BatteryPowerInput = Stats.BatteryPowerInput;
      OutData.Add(PowerOutput);
    }
  }

  return FFGServerErrorResponse::Ok();
}

FFGServerErrorResponse UStatisfactoryController::Statisfactory_GetDepots(TMap<FString, int32> &OutData) const {
  OutData = {};

  auto Subsystem = AFGCentralStorageSubsystem::Get(this->World);
  if (Subsystem == nullptr)
    return SubsystemError;

  TArray<FItemAmount> Out;
  Subsystem->GetAllItemsFromCentralStorage(Out);

  for (auto Item : Out) {
    auto Name = UFGItemDescriptor::GetItemName(Item.ItemClass.Get());
    auto Amount = Item.Amount;
    OutData.Add(Name.ToString(), Amount);
  }

  return FFGServerErrorResponse::Ok();
}

FFGServerErrorResponse UStatisfactoryController::Statisfactory_GetSink(FTicketData &OutData) const {
  OutData = {};
  auto Subsystem = AFGResourceSinkSubsystem::Get(this->World);
  if (Subsystem == nullptr)
    return SubsystemError;

  OutData.Coupons = Subsystem->GetNumCoupons();
  OutData.PointsToNextCoupon = Subsystem->GetNumPointsToNextCoupon(EResourceSinkTrack::RST_Default);

  return FFGServerErrorResponse::Ok();
}
