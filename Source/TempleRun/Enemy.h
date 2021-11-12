// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class TEMPLERUN_API AEnemy : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Components)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Components)
	class UCapsuleComponent* CapsuleWrapper;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Components)
	float Speed = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Components)
	float MaxDistanceFromCenter = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Enemy)
	float DistanceToStartWalking = 1000.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Enemy)
	int Direction = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Enemy)
	float AlphaSmoothness = 17.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Enemy)
	float CoolDownTurn = .7f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Enemy)
	bool bDefeated;

protected:

	FVector InitialLocation;
	float CurrentDirection;
	bool bCanTurn = true;
	class ABaseCharacter* MainCharacter;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void PursuePlayer();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SideWalk(const float DeltaTime);
	
	void TurnToOtherSide();

	UFUNCTION()
	void EnableTurn();

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetCurrentDirection () const { return CurrentDirection; }

};
