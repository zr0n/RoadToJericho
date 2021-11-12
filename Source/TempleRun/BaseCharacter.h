// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TempleRunGameModeBase.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class TEMPLERUN_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta=(AllowPrivateAccess=true))
	float RightSpeedFactor = .5f;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float MaxSpeedReached;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta=(AllowPrivateAccess=true))
	float InitialSpeed = 600.f;
	
	ATempleRunGameModeBase* GameMode;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveRight(const float AxisValue);
	void AutoGoForward();

};
