// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

#include "BaseCharacter.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitialLifeSpan = 30.f;
	
	Wrapper = CreateDefaultSubobject<USceneComponent>(TEXT("Wrapper"));
	SetRootComponent(Wrapper);
	
	NextSpawnReference = CreateDefaultSubobject<UArrowComponent>(TEXT("Next Spawn Reference"));
	NextSpawnReference->SetupAttachment(Wrapper);

	SpawnTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Trigger"));
	SpawnTrigger->SetupAttachment(Wrapper);

	SpawnTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATile::BeginOverlap);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATile::Spawn(ATempleRunGameModeBase* GameMode)
{
		const auto Template = IsValid(GameMode) ? GameMode->SortRandomTemplate() : nullptr;
		if(IsValid(Template))
		{
			if(!GameMode->LastSpawnedTile || !IsValid(GameMode->LastSpawnedTile))
				GameMode->LastSpawnedTile = this;
			
			const FTransform  SpawnTransform = GameMode->LastSpawnedTile->NextSpawnReference->GetComponentTransform();

			GameMode->SpawnTile(SpawnTransform);
		}
}

void ATile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                         int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(const auto Character = Cast<ABaseCharacter>(OtherActor))
	{
		Spawn(Character->GameMode);
	}
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

