#include "UStatisfactoryWorldSubsystem.h"

#include "Engine/World.h"
#include "FGServerAPIManager.h"
#include "FGServerSubsystem.h"
#include "UStatisfactoryController.h"

UStatisfactoryWorldSubsystem::UStatisfactoryWorldSubsystem() {
  // I have no idea what I'm doing and it shows
  this->Controller = NewObject<UStatisfactoryController>();
  this->Controller->World = this->GetWorld();
}

void UStatisfactoryWorldSubsystem::RegisterRoute(UFGServerAPIManager *Manager, const char *Name) {
  auto Handler = FFGRequestHandlerRegistration();
  Handler.HandlerObject = this->Controller;
  Handler.HandlerFunction = this->Controller->FindFunction(Name);
  Handler.FunctionName = FName(Name);
  Handler.PrivilegeLevel = EPrivilegeLevel::NotAuthenticated;
  auto handlers = Manager->GetmRegisteredHandlers();
  handlers.Add(FString(Name), Handler);
  Manager->SetmRegisteredHandlers(handlers);
}

void UStatisfactoryWorldSubsystem::PostInitialize() {
  const auto World = this->GetWorld();
  if (World == nullptr)
    return;

  const auto GameInstance = World->GetGameInstance();
  if (GameInstance == nullptr)
    return;

  const auto Subsystem = GameInstance->GetSubsystem<UFGServerSubsystem>();
  if (Subsystem == nullptr)
    return;

  const auto ServerAPIManager = Subsystem->GetServerAPIManager();
  if (ServerAPIManager == nullptr)
    return;

  // The API registering doesn't work for me? so this will do
  this->RegisterRoute(ServerAPIManager, "Statisfactory_GetPower");
  this->RegisterRoute(ServerAPIManager, "Statisfactory_GetDepots");
}
