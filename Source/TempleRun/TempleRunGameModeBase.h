// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TempleRunGameModeBase.generated.h"

class ATile;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FTileSpawnInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Temple Run")
	TSubclassOf<ATile> Template;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Temple Run", meta = (ClampMin = "0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float SpawnChance;
};

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOver);

constexpr int BIAS_OFF_FLAG = -1;

UCLASS()
class TEMPLERUN_API ATempleRunGameModeBase : public AGameMode
{
	GENERATED_BODY()


	virtual void BeginPlay() override;
	virtual void Tick(const float DeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=TempleRun)
	int InitialTiles = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=TempleRun)
	float InitialCountDown = 3.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=TempleRun)
	int MaxSpawnTries = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTileSpawnInfo> TilesTemplate;

	UPROPERTY(BlueprintAssignable)
	FGameOver OnGameOver;

	UPROPERTY(BlueprintReadOnly)
	bool bIsGameRunning;

	UPROPERTY()
	class ATile* LastSpawnedTile;

	void StartGame();
	void StopGame();
	void SpawnInitialTiles();
	void SpawnTile(const FTransform SpawnTransform, const bool bInitial = false);

	UFUNCTION(BlueprintCallable, Category=TempleRun)
	void GameOver();

	TSubclassOf<ATile> SortRandomTemplate(const int Iterations = 0x00, const int Bias = -1) const;
	
};
