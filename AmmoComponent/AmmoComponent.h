/*
Implementation:

GAMENAME_API needs to be set to the name that you chose
When you created the project

eg. SHOOTERGAME_API - Make sure its in capitals


Usage:

Put This In Your Gun Class File (Gun.h)
	UAmmoComponent AmmoComponent;

Put This In Your Gun Constructor (Gun.cpp)
	AmmoComponent = CreateDefaultSubobject<UAmmoComponent>(this, TEXT("AmmoComponent"));

*/

#pragma once

#include "Components/ActorComponent.h"
#include "AmmoComponent.generated.h" // May need to regenerate visual studio files after adding the files to your project


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAmmoComponentDelegate);


UCLASS( Config=Game, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMENAME_API UAmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAmmoComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Handles all ammo for you
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		bool Fire();

	// Handles all reloading for you
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		void Reload();

	// Checks if you are reloading
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		bool IsReloading();

	// Stops and resets reloading
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		void CancelReload();

	// Simple Function To Subtract Ammo and Clamps between 0 - MaxAmmo
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		int32 TakeAmmo(int32 Amount);

	// Simple Function To Add Ammo and Clamps between 0 - MaxAmmo
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		int32 GiveAmmo(int32 Amount);

	// Simple Function To Subtract Reserve Ammo and Clamps between 0 - MaxReserveAmmo
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		int32 TakeReserveAmmo();

	// Simple Function To Add Reserve Ammo and Clamps between 0 - MaxReserveAmmo
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		int32 GiveReserveAmmo(int32 Amount);

	// Simple Function That Sets Ammo To NewAmmo Param, Clamped between 0 - MaxAmmo
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		int32 SetAmmo(int32 NewAmmo);

	// Simple Function That Sets Reserve To NewReserveAmmo Param, Clamped between 0 - MaxReserveAmmo
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		int32 SetReserveAmmo(int32 NewReserveAmmo);

	// Simple Function That Sets MaxAmmo To NewMaxAmmo
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		int32 SetMaxAmmo(int32 NewMaxAmmo);

	// Simple Function That Sets MaxReserveAmmo To NewMaxReserveAmmo
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		int32 SetMaxReserveAmmo(int32 NewMaxReserveAmmo);

	// Simple Function That Returns 0-1 float value for (TimeLeft/ReloadDuration)
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		float GetReloadTimeLeftPercent();

	// Simple Function That Returns True If Ammo <= 0
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		bool IsAmmoDepleted();

	// Simple Function That Returns True If ReserveAmmo <= 0
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		bool IsReserveAmmoDepleted();

	// Simple Function That Returns 0-1 float value for (Ammo/MaxAmmo)
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		float GetAmmoPercent();

	// Simple Function That Returns float value for Time Left in Reload Timer ( 0 if timer doesn't exist )
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		float GetRemaindingReloadTime();

	// Function that returns true if both NeedsToReload() and CanReload() are true
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		bool NeedsAndCanReload();

	// Returns useful Debug Info That Can Be Printed (Ammo / ReserveAmmo, Reloading: bIsReloading)
	// Could Be Improved To Return Things Such As Max Values
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		FString GetDebugInfo();

	// Sets Variables to their defined max value
	UFUNCTION(BlueprintCallable, Category = "AmmoComponent")
		void ResetAmmo();

	// Delegate that is called from SetAmmo() when Ammo <= 0
	UPROPERTY(BlueprintAssignable, Category = "AmmoComponent")
		FAmmoComponentDelegate OnAmmoDepleted;

	// Delegate that is called from SetReserveAmmo() when ReserveAmmo <= 0
	UPROPERTY(BlueprintAssignable, Category = "AmmoComponent")
		FAmmoComponentDelegate OnReserveDepleted;

	// Delegate that is called from StartReloading()
	UPROPERTY(BlueprintAssignable, Category = "AmmoComponent")
		FAmmoComponentDelegate OnReloadStart;

	// Delegate that is called from FinishReloading();
	UPROPERTY(BlueprintAssignable, Category = "AmmoComponent")
		FAmmoComponentDelegate OnReloadComplete;

private:

	// Setters
	float SetReloadDuration(float NewReloadDuration);

	// Helper Functions - You can expose these to BP if you want
	bool NeedsToReload();
	bool CanReload();

	// Shouldn't need to call these directly
	void StartReloading();
	void FinishReloading();

	// Variables
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 Ammo = 30;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 MaxAmmo = 30;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 ReserveAmmo = 90;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 MaxReserveAmmo = 90;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float ReloadDuration = 2.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		bool FiringWithNoBulletsStartsReload = false;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 BulletsPerShot = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		bool bShootingInteruptsReload = false;

	// Shouldn't need to touch this ever
	// TODO this bool sucks, is almost useless
		bool bIsReloading = false;

	// Shouldn't need to touch this ever
	FTimerHandle ReloadingHandle;
};