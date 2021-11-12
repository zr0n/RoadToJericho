// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleWrapper = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Wrapper"));
	SetRootComponent(CapsuleWrapper);
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CapsuleWrapper);

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();

	MainCharacter = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	//CurrentDirection = static_cast<float>(Direction);
}

void AEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(MainCharacter == OtherActor)
	{
		Speed = 0x00;
		MainCharacter->GameMode->GameOver();
	}
}

void AEnemy::PursuePlayer()
{
	const auto PositionOffset = (GetActorRightVector() * (MainCharacter->GetActorLocation() - GetActorLocation()));
	if(PositionOffset.Size() > 10.f)
	{
		Direction = FMath::Sign(PositionOffset.X + PositionOffset.Y);
	}
	else
	{
		Direction = 0x00;
	}

	bDefeated = MainCharacter->GetActorLocation().X > GetActorLocation().X;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if(bDefeated)
		return;

	
	/*
	const float CurrentDistanceFromCenter = (GetActorLocation() - InitialLocation).Size();


	if(CurrentDistanceFromCenter >= MaxDistanceFromCenter && bCanTurn)
		TurnToOtherSide();
	*/

	if((GetActorLocation() - MainCharacter->GetActorLocation()).Size() <= DistanceToStartWalking)
	{
		PursuePlayer();
		SideWalk(DeltaTime);
	}
	
}

void AEnemy::SideWalk(const float DeltaTime)
{
	//Turn smoothly
	CurrentDirection = FMath::Lerp(CurrentDirection, static_cast<float>(Direction), AlphaSmoothness * DeltaTime);
	
	AddActorWorldOffset(GetActorRightVector() * Speed * CurrentDirection * DeltaTime);
}

void AEnemy::TurnToOtherSide()
{
	bCanTurn = false;

	if(const auto World = GetWorld())
	{
		FTimerHandle TimerHandle;
		World->GetTimerManager().SetTimer(TimerHandle, this, &AEnemy::EnableTurn, CoolDownTurn, false);
		Direction = Direction == 1 ? -1 : 1;
	}
	
}

void AEnemy::EnableTurn()
{
	bCanTurn = true;
}

