// Copyright Bohdon Sayre, All Rights Reserved.


#include "GameDebugInputActor.h"

#include "GameFramework/CheatManager.h"


AGameDebugInputActor::AGameDebugInputActor()
{
}

APlayerController* AGameDebugInputActor::GetOwningPlayerController() const
{
	return Cast<APlayerController>(GetOwner());
}

UCheatManager* AGameDebugInputActor::GetCheatManager(TSubclassOf<UCheatManager> CheatManagerClass) const
{
	if (const APlayerController* Player = GetOwningPlayerController())
	{
		return Player->CheatManager;
	}
	return nullptr;
}

void AGameDebugInputActor::InitDebug_Implementation()
{
	if (APlayerController* PlayerController = GetOwningPlayerController())
	{
		EnableInput(PlayerController);
	}
}

void AGameDebugInputActor::DeinitDebug_Implementation()
{
	if (APlayerController* PlayerController = GetOwningPlayerController())
	{
		DisableInput(PlayerController);
	}
}
