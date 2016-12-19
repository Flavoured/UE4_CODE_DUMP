// Fill out your copyright notice in the Description page of Project Settings.

#include "GameName.h"
#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ResetHealthOnPlay)
	{
		SetHealth(MaxHealthPoints);
	}
}


// Called every frame
void UHealthComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// bCanEverTick should be set to false
	UE_LOG(LogTemp, Warning, TEXT("Why does this component need to tick?"))
}


// Sets Health
float UHealthComponent::SetHealth(const float NewHealth)
{
	HealthPoints = NewHealth;

	if (GetHealth() <= 0.f)
	{
		OnHealthDepleted.Broadcast();
	}

	return HealthPoints;
}


// Adds Health
float UHealthComponent::AddHealth(float Amount)
{
	SetHealth(GetHealth() + Amount);
	return HealthPoints;
}


// Takes Health
float UHealthComponent::TakeHealth(float Amount)
{
	SetHealth(GetHealth() - Amount);
	return HealthPoints;
}


// Gets Health
float UHealthComponent::GetHealth()
{
	return HealthPoints;
}


// Gets Max Health
float UHealthComponent::GetMaxHealth()
{
	return MaxHealthPoints;
}


// Checks if Health <= 0
bool UHealthComponent::IsDepleted()
{
	return GetHealth() <= 0;
}


// Gets Health As Percent ( Useful for HUD Progress Bar )
float UHealthComponent::GetHealthPercent()
{
	return GetHealth()/GetMaxHealth();
}