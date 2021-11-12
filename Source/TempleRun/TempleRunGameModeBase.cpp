// Copyright Epic Games, Inc. All Rights Reserved.


#include "TempleRunGameModeBase.h"

#include "Tile.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void ATempleRunGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(true);
	SpawnInitialTiles();
}

void ATempleRunGameModeBase::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(InitialCountDown)
	{
		InitialCountDown -= DeltaTime;
		if(InitialCountDown <= 0x00)
		{
			InitialCountDown = 0x00;
			StartGame();
		}
	}
}

void ATempleRunGameModeBase::StartGame()
{
	bIsGameRunning = true;
}

void ATempleRunGameModeBase::StopGame()
{
	bIsGameRunning = false;
}

void ATempleRunGameModeBase::SpawnInitialTiles()
{
	for(int i = 0; i < InitialTiles; i++)
	{
		FTransform SpawnTransform;
		
		if(LastSpawnedTile)
			SpawnTransform = LastSpawnedTile->NextSpawnReference->GetComponentTransform();

		SpawnTile(SpawnTransform, true);
	}
}

void ATempleRunGameModeBase::SpawnTile(const FTransform SpawnTransform, const bool bInitial)
{
	if(const auto World = GetWorld())
		LastSpawnedTile = World->SpawnActor<ATile>(SortRandomTemplate(0x00, bInitial ? 0 : BIAS_OFF_FLAG), SpawnTransform.GetLocation(), SpawnTransform.GetRotation().Rotator());
}

void ATempleRunGameModeBase::GameOver()
{
	bIsGameRunning = false;
	if(OnGameOver.IsBound())
		OnGameOver.Broadcast();

	SetMatchState(TEXT("Over"));
}

TSubclassOf<ATile> ATempleRunGameModeBase::SortRandomTemplate(const int Iterations, const int Bias) const
{
	if(!TilesTemplate.Num())
		return nullptr;

	

	if(Bias != BIAS_OFF_FLAG && Bias < TilesTemplate.Num())
		return TilesTemplate[Bias].Template;
	
	TArray<FTileSpawnInfo> Tiles(TilesTemplate);

	//Shuffle Array
	Tiles.Sort([](const auto A, const auto B)
	{
		return FMath::SRand() > .5f;
	});

	if(Iterations >= MaxSpawnTries)
		return Tiles[UKismetMathLibrary::RandomInteger(Tiles.Num())].Template;

	for(const auto Tile : Tiles)
		if(FMath::SRand() <= Tile.SpawnChance)
			return Tile.Template;

	return SortRandomTemplate(Iterations + 1);
}
