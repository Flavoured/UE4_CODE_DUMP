/*
Implementation:
GAMENAME_API needs to be set to the name that you chose
When you created the project
eg. SHOOTERGAME_API
Usage:
Add the following line to the header file of the object that needs a health component. (eg. Player.h):
	UHealthComponent HealthComponent;
Add the following line to the constructor in the cpp file of the object that needs a health component. (eg. Player.h):
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(this, TEXT("HealthComponent"));
*/

#pragma once

#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMENAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintCallable, Category = HealthComponent)
		float SetHealth(const float NewHealth);
	UFUNCTION(BlueprintCallable, Category = HealthComponent)
		float AddHealth(float Amount);
	UFUNCTION(BlueprintCallable, Category = HealthComponent)
		float TakeHealth(float Amount);
	UFUNCTION(BlueprintCallable, Category = HealthComponent)
		float GetHealth();
	UFUNCTION(BlueprintCallable, Category = HealthComponent)
		float GetMaxHealth();
	UFUNCTION(BlueprintCallable, Category = HealthComponent)
		bool IsDepleted();
	UFUNCTION(BlueprintCallable, Category = HealthComponent)
		float GetHealthPercent();
		
	UPROPERTY(EditAnywhere)
		float HealthPoints = 0.f;
	UPROPERTY(EditAnywhere)
		float MaxHealthPoints = 100.f;
	UPROPERTY(EditAnywhere)
		bool ResetHealthOnPlay = true;

	UPROPERTY(BlueprintAssignable, Category = HealthComponent)
		FHealthEvent OnHealthDepleted;

};
