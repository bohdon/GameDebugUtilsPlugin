// Copyright Bohdon Sayre, All Rights Reserved.


#include "GameDebugSubsystem.h"

#include "GameDebugCheatManager.h"


UGameDebugSubsystem::UGameDebugSubsystem()
	: bAutoEnableInEditor(true),
	  bIsGameDebugEnabled(false)
{
}

void UGameDebugSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (bAutoEnableInEditor && GIsEditor)
	{
		bIsGameDebugEnabled = true;
	}
}

void UGameDebugSubsystem::EnableGameDebug()
{
	SetGameDebugEnabled(true);
}

void UGameDebugSubsystem::DisableGameDebug()
{
	SetGameDebugEnabled(false);
}

void UGameDebugSubsystem::SetGameDebugEnabled(bool bEnabled)
{
	if (bIsGameDebugEnabled != bEnabled)
	{
		bIsGameDebugEnabled = bEnabled;

		if (bEnabled)
		{
			OnGameDebugEnabled();
		}
		else
		{
			OnGameDebugDisabled();
		}

		OnGameDebugChangedEvent.Broadcast(bIsGameDebugEnabled);
		OnGameDebugChangedEvent_BP.Broadcast(bIsGameDebugEnabled);
	}
}

void UGameDebugSubsystem::OnGameDebugEnabled()
{
	// add cheats to all player controllers
	if (const UWorld* World = GetGameInstance()->GetWorld())
	{
		for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* const PlayerController = Iterator->Get();
			if (PlayerController && PlayerController->IsLocalPlayerController())
			{
				PlayerController->AddCheats();
			}
		}
	}
}

void UGameDebugSubsystem::OnGameDebugDisabled()
{
	// remove cheats from all player controllers
	if (const UWorld* World = GetGameInstance()->GetWorld())
	{
		for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* const PlayerController = Iterator->Get();
			if (PlayerController && PlayerController->IsLocalPlayerController())
			{
				if (PlayerController->CheatManager)
				{
					if (UGameDebugCheatManager* DebugCheatManager = Cast<UGameDebugCheatManager>(PlayerController->CheatManager))
					{
						// deinitialize the cheat manager, not a concept built into the base cheat manager
						DebugCheatManager->DeinitCheatManager();
					}

					PlayerController->CheatManager = nullptr;
				}
			}
		}
	}
}
