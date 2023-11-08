// Copyright Bohdon Sayre, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "GameDebugCheatManager.generated.h"

class AGameDebugInputActor;


/**
 * A cheat manager that spawns an additional debug input actor for easy hotkey creation.
 */
UCLASS(Config = Game)
class GAMEDEBUGUTILS_API UGameDebugCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	/** The debug input actor to spawn for managing hotkeys, etc. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<AGameDebugInputActor> DebugInputActorClass;

	virtual void InitCheatManager() override;

	/** Called before the cheat manager is destroyed for performing cleanup. */
	void DeinitCheatManager();

	/** Called before the cheat manager is destroyed for performing cleanup. */
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "DeinitCheatManager")
	void DeinitCheatManager_BP();

	/** Return the debug input actor, if any. */
	UFUNCTION(BlueprintPure)
	AGameDebugInputActor* GetDebugInput() const { return DebugInputActor; }

	/** Spawn the debug input actor. Called automatically on init. */
	virtual void SpawnDebugInput();

	/** Destroy the debug input actor. Called automatically on deinit. */
	virtual void DestroyDebugInput();

protected:
	UPROPERTY(Transient)
	TObjectPtr<AGameDebugInputActor> DebugInputActor;
};
