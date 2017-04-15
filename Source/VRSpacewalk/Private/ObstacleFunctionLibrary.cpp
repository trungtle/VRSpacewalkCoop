// Fill out your copyright notice in the Description page of Project Settings.

#include "VRSpacewalk.h"
#include "ObstacleFunctionLibrary.h"

int UObstacleFunctionLibrary::blockSize = 10;
int UObstacleFunctionLibrary::cullDistance = 1000;
TMap<FVector, AActor *> UObstacleFunctionLibrary::spawned = TMap<FVector, AActor *>();

void UObstacleFunctionLibrary::Cleanup(FVector &screenStart, FVector &forward) {
	for (auto &ele : spawned) {
		FVector dist = screenStart - ele.Key;
		float dot = FVector::DotProduct(dist, forward);
		if (dot < 0 && -1 * dot >= cullDistance) {
			ele.Value->Destroy();
			spawned.Remove(ele.Key);
		}
	}
}

FVector UObstacleFunctionLibrary::reduceToHsh(FVector &position) {
	return FVector((int) position.X % UObstacleFunctionLibrary::blockSize,
		(int) position.Y % UObstacleFunctionLibrary::blockSize,
		(int) position.Z % UObstacleFunctionLibrary::blockSize);
}

AActor *UObstacleFunctionLibrary::SpawnObstacle(const UObject *worldContext, UClass *actorClass, const FVector &start, const FVector &end,
	const float bounds) {
	FVector rand;
	rand.X = FMath::FRand();
	rand.Y = FMath::FRand();
	rand.Z = FMath::FRand();

	FVector centerPoint = start + end / 2;
	FVector loc = centerPoint + (rand * bounds);
	FVector reduced = reduceToHsh(loc);
	if (spawned.Contains(reduced)) {
		// dummy for now, find better space filling algo later
		return SpawnObstacle(worldContext, actorClass, start, end, bounds);
	}
	else {
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FRotator rot = FRotator::ZeroRotator;
		AActor *actor = worldContext->GetWorld()->SpawnActor(actorClass, &loc, &rot, params);
		spawned.Add(reduced, actor);
		return actor;
	}
}

