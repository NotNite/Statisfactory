#pragma once
#include "UStatisfactoryController.h"
#include "WorldSubsystem.h"

#include "UStatisfactoryWorldSubsystem.generated.h"

UCLASS()
class UStatisfactoryWorldSubsystem : public UWorldSubsystem {
  GENERATED_BODY()

public:
  UStatisfactoryWorldSubsystem();
  virtual void PostInitialize() override;

  UPROPERTY()
  UStatisfactoryController *Controller;

private:
  void RegisterRoute(UFGServerAPIManager *Manager, const char *Name);
};
