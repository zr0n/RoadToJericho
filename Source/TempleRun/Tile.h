// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TempleRunGameModeBase.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TEMPLERUN_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Components)
	USceneComponent* Wrapper;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Components)
	class UArrowComponent* NextSpawnReference;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Components)
	class UBoxComponent* SpawnTrigger;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Spawn(ATempleRunGameModeBase* GameMode);

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

};
