#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "SVONPath.h"
#include "SVONLink.h"

#include "SVONNavigationComponent.generated.h"

class ASVONVolume;
struct FSVONLink;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UESVON_API USVONNavigationComponent 
    : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SVON|Debug")
	bool bDebugPrintCurrentPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SVON|Debug")
	bool bDebugPrintMortonCodes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SVON|Debug")
	bool bDebugDrawOpenNodes = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SVON|Heuristics")
	bool bUseUnitCost = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SVON|Heuristics")
	float UnitCost = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SVON|Heuristics")
	float WeightEstimate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SVON|Heuristics")
	float NodeSizeCompensation = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SVON|Heuristics")
	ESVONPathCostType PathCostType = ESVONPathCostType::SPCT_Euclidean;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SVO Navigation | Smoothing")
	int32 SmoothingIterations = 0;

	// Sets default values for this component's properties
	USVONNavigationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// The current navigation volume
	ASVONVolume* CurrentNavVolume;

	// Do I have a valid nav volume ready?
	bool HasNavVolume();

	// Check the scene for a valid volume that I am within the extents of
	bool FindVolume();

	// Print current layer/morton Code information
	void DebugLocalLocation(FVector& aPosition);

	FSVONLink LastLocation;

	TQueue<int32> JobQueue;
	TArray<FVector> DebugPoints;

	bool bIsBusy;

	int32 PointDebugIndex;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Get a Nav Location
	FSVONLink GetNavLocation(FVector& OutLocation);

	/* This method isn't hooked up at the moment, pending integration with existing systems */
	bool FindPathAsync(const FVector& StartLocation, const FVector& TargetLocation, FNavPathSharedPtr* OutNavPath);

	bool FindPathImmediate(const FVector& StartLocation, const FVector& TargetLocation, FNavPathSharedPtr* OutNavPath);
};