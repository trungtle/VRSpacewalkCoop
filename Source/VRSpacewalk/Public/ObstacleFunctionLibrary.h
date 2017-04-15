// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ObstacleFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class VRSPACEWALK_API UObstacleFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Obstacle Spawning")
	static AActor *SpawnObstacle(const UObject *worldContext, UClass *actorClass, const FVector &start, const FVector &end,
		const float bounds);

	UFUNCTION(BlueprintCallable, Category = "Obstacle Spawning")
	static void Cleanup(FVector &screenStart, FVector &forward);
private:
	static int blockSize;
	static int cullDistance;
	static FVector reduceToHsh(FVector &in);
	static TMap<FVector, AActor *> spawned;
	
};
