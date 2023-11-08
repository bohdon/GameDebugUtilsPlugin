// Copyright Bohdon Sayre, All Rights Reserved.


#include "GameDebugCheatManager.h"

#include "GameDebugInputActor.h"


void UGameDebugCheatManager::InitCheatManager()
{
	SpawnDebugInput();

	Super::InitCheatManager();
}

void UGameDebugCheatManager::DeinitCheatManager()
{
	DeinitCheatManager_BP();

	DestroyDebugInput();
}

void UGameDebugCheatManager::SpawnDebugInput()
{
	if (DebugInputActorClass.IsNull() || IsValid(DebugInputActor))
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOuterAPlayerController();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// blocking load the actor class
		const TSubclassOf<AGameDebugInputActor> DebugInputClassRef = DebugInputActorClass.LoadSynchronous();
		DebugInputActor = World->SpawnActor<AGameDebugInputActor>(DebugInputClassRef, SpawnParams);
		if (DebugInputActor)
		{
			DebugInputActor->InitDebug();
		}
	}
}

void UGameDebugCheatManager::DestroyDebugInput()
{
	if (DebugInputActor)
	{
		DebugInputActor->DeinitDebug();
		DebugInputActor->Destroy();
		DebugInputActor = nullptr;
	}
}
