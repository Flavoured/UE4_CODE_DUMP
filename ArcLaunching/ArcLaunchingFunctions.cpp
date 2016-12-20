// ClassName should be replaced with the name of the class these functions are placed in.

// Goes in Header File if you want the below examples to work properly
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwing")
	UClass* ObjectToThrow;

// Example 1 - Launches predefined object towards the mouse (Bind to mousebutton to make some sort of grenade)
void ClassName::LaunchObjectTowardsMouse()
{
	FTransform start = GetActorTransform();

	FHitResult hitResult; // OUT Variable

	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, false, hitResult);
	FVector end = hitResult.Location;

	LaunchNewObjectTowardsLocation(ObjectToThrow, start, end, 100.f, 1000.f, 1.f);
}

// Example 2 - Launches predefined object towards the object that this function is running on from a given start point
void ClassName::LaunchObjectTowardsThis()
{
	FTransform start = FTransform(FRotator(0, 0, 0), FVector(-550, -200, 270), FVector(1, 1, 1));

	FVector end = GetActorLocation();

	LaunchNewObjectTowardsLocation(ObjectToThrow, start, end, 100.f, 1000.f, 1.f);
}

// Spawns a object and launches it towards its end position, clamping range between minRange and maxRange
AActor* ClassName::LaunchNewObjectTowardsLocation(UClass* Object, FTransform spawnPos, FVector endPos, float minRange, float maxRange, float gravityScale)
{
	FRotator r = spawnPos.GetRotation().Euler().Rotation();
	FVector l = spawnPos.GetLocation();
	FVector LaunchVelocity = FVector(0, 0, 0); // OUT VARIABLE

	AActor* newObject = GetWorld()->SpawnActor(Object, &l, &r, FActorSpawnParameters());

	// Calculates the arc velocity and assigns it to the Out variable "LaunchVelocity"
	UGameplayStatics::SuggestProjectileVelocity_CustomArc(newObject, LaunchVelocity, newObject->GetActorLocation(), endPos, -980*gravityScale);
	
	// Limit the range on which the arc will reach
	LaunchVelocity = (LaunchVelocity / LaunchVelocity.Size()) * FMath::Clamp(LaunchVelocity.Size(), minRange, maxRange);

	// Find the Movement Component of our newely spawned actor, if it has one then assign it the new velocity
	auto PMComponent = newObject->FindComponentByClass<UProjectileMovementComponent>();
	if (PMComponent)
		PMComponent->Velocity = LaunchVelocity;

	return newObject;
}

// Launches a passed in object towards target position, clamping range between minRange and maxRange
void ClassName::LaunchObjectTowardsLocation(AActor* Object, FVector targetPos, float minRange, float maxRange, float gravityScale)
{
	FVector LaunchVelocity = FVector(0, 0, 0); // OUT VARIABLE

	// Calculates the arc velocity and assigns it to the Out variable "LaunchVelocity"
	UGameplayStatics::SuggestProjectileVelocity_CustomArc(Object, LaunchVelocity, Object->GetActorLocation(), targetPos, -980 * gravityScale);

	// Limit the range on which the arc will reach
	LaunchVelocity = (LaunchVelocity / LaunchVelocity.Size()) * FMath::Clamp(LaunchVelocity.Size(), minRange, maxRange);

	// Find the Movement Component of our actor, if it has one then assign it the new velocity
	auto PMComponent = Object->FindComponentByClass<UProjectileMovementComponent>();
	if(PMComponent)
		PMComponent->Velocity = LaunchVelocity;
}