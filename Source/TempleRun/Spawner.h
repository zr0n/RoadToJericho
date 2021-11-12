// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class TEMPLERUN_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta=(AllowPrivateAccess=true))
	TSubclassOf<AActor> Template;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Spawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
