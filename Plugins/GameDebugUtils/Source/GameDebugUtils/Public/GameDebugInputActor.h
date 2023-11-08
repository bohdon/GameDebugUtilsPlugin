// Copyright Bohdon Sayre, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameDebugInputActor.generated.h"


/**
 * An actor designed to receive input for debug hotkeys.
 *
 * Spawned automatically by the GameDebugCheatManager, this actor
 * allows easy creation of hotkeys in blueprint using standard key input events.
 */
UCLASS()
class GAMEDEBUGUTILS_API AGameDebugInputActor : public AActor
{
	GENERATED_BODY()

public:
	AGameDebugInputActor();

	/**
	 * Initialize this debug actor. Enables input from the player controller by default.
	 * Be sure to call the super if implementing in blueprint.
	 */
	UFUNCTION(BlueprintNativeEvent)
	void InitDebug();

	/** Called just before destroying this actor when game debugging is disabled. */
	UFUNCTION(BlueprintNativeEvent)
	void DeinitDebug();

	/** Return the owning player controller for this debug input. */
	UFUNCTION(BlueprintPure, Category = "GameDebug")
	APlayerController* GetOwningPlayerController() const;

	/** Return the cheat manager for the owning player, cast to a type. */
	UFUNCTION(BlueprintPure, Meta = (DeterminesOutputType = "CheatManagerClass"), Category = "GameDebug")
	UCheatManager* GetCheatManager(TSubclassOf<UCheatManager> CheatManagerClass) const;
};
