# Arc Launching
####UE4 C++ Launching Objects With Arcs

##Setup

1. Add the functions to your project.
2. Go through the .h and .cpp files and replace ClassName with the classes name.

##Implementation

1. Add the following line to the header file of the object that needs a health component.

	UHealthComponent HealthComponent;
	
2. Add the following line to the constructor in the cpp file of the object that needs a health component.

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(this, TEXT("HealthComponent"));
	
3. Call AmmoComponent->Fire(); when you are shooting.
4. Call AmmoComponent->Reload(); when you want to reload.

This Health Component contains 1 blueprint assignable event that is called OnHealthDepleted which triggers when health reaches zero

##Useful extra functions:

__GetHealthPercent()__ - Returns 0-1 value for the amount of health left __( Useful for HUDS and progress bars )__.

__IsDepleted()__ - Returns true if you have 0 health or less.
