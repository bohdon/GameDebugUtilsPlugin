// Copyright Bohdon Sayre, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameDebugSubsystem.generated.h"


/**
 * Manages the overall state of whether game debugging is enabled.
 *
 * The game mode should implement AllowCheats and check IsGameDebugEnabled()
 * in order to properly spawn cheat managers automatically after level travel.
 *
 * Additionally, the player controller should implement EnableCheats, and add
 * a DisableCheats exec function, which call EnableGameDebug/DisableGameDebug
 * on this subsystem respectively.
 */
UCLASS(Config = Game)
class GAMEDEBUGUTILS_API UGameDebugSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UGameDebugSubsystem();

	/** Automatically enable game debugging when playing in editor. */
	UPROPERTY(Config)
	bool bAutoEnableInEditor;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Enable game debug features. */
	UFUNCTION(BlueprintCallable, Category = "GameDebug")
	void EnableGameDebug();

	/** Disable game debug features. */
	UFUNCTION(BlueprintCallable, Category = "GameDebug")
	void DisableGameDebug();

	/** Set whether game debug features should be enabled. */
	UFUNCTION(BlueprintCallable, Category = "GameDebug")
	void SetGameDebugEnabled(bool bEnabled);

	/** Are game debug features enabled? */
	UFUNCTION(BlueprintPure, Category = "GameDebug")
	bool IsGameDebugEnabled() const { return bIsGameDebugEnabled; }

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameDebugChangedDynDelegate, bool, bIsEnabled);

	DECLARE_MULTICAST_DELEGATE_OneParam(FGameDebugChangedDelegate, bool /* bIsEnabled */);

	/** Called when game debug features are enabled or disabled. */
	UPROPERTY(BlueprintAssignable, DisplayName = "OnGameDebugChangedEvent")
	FGameDebugChangedDynDelegate OnGameDebugChangedEvent_BP;

	/** Called when game debug features are enabled or disabled. */
	FGameDebugChangedDelegate OnGameDebugChangedEvent;

protected:
	virtual void OnGameDebugEnabled();
	virtual void OnGameDebugDisabled();

private:
	/** Is game debugging currently enabled? */
	bool bIsGameDebugEnabled;
};
