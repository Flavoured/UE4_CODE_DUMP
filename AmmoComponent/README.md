# AmmoComponent
####UE4 C++ Ammo Component 

##Setup

1. Add the .h and .cpp files to your project.
2. Go through the .h and .cpp files and replace GameName with your projects name.
3. May need to Generate Project Files

##Implementation

1. Add the following line to the header file of the object that needs an ammo component.

	UAmmoComponent* AmmoComponent;
	
2. Add the following line to the cpp file of the object that needs an ammo component.

	AmmoComponent = CreateDefaultSubobject<UAmmoComponent>(this, TEXT("AmmoComponent"));
	
3. Call AmmoComponent->Fire(); when you are shooting.
4. Call AmmoComponent->Reload(); when you want to reload.

You can modify variables in the details panel of the component on the object it is attached to.
The Fire and Reload functions handle everything for you, but if you want you can run functions directly.

##Delegates / blueprint events:

__OnAmmoDepleted__ - Called when you run out of your main ammo.

__OnReserveDepleted__ - Called when you run out of your reserve ammo.

__OnReloadStart__ - Called when reloading starts.

__OnReloadComplete__ - Called when reloading has finished.

##Useful extra functions:

__GetAmmoPercent()__ - Returns 0-1 value for the amount of ammo left in your magazine __( Useful for HUDS and progress bars )__.

__GetReloadTimePercent()__ - Returns 0-1 value for the time left in reload cycle __( Useful for HUDS and progress bars )__.

__GetRemaindingReloadTime()__ - Same as above but returns in seconds __( Useful for HUDS )__.

__GetDebugInfo()__ - Returns String that can be printed to show ammocomponent information.
