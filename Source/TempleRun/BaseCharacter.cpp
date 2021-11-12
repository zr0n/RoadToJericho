// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->GravityScale = 0x00;
	
	const auto World = GetWorld();

	
	GameMode = World ? Cast<ATempleRunGameModeBase>(World->GetAuthGameMode()) : nullptr;

	if(!IsValid(GameMode))
		UKismetSystemLibrary::QuitGame(this, Cast<APlayerController>(GetController()), EQuitPreference::Quit, true);


	//GetCharacterMovement()->MaxWalkSpeed = InitialSpeed;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!GameMode || !GameMode->bIsGameRunning)
		return;
	
	if(!GetCharacterMovement()->GravityScale)
	{
		GetCharacterMovement()->GravityScale = 1.f;
		GetCharacterMovement()->Velocity = GetActorForwardVector() * InitialSpeed;
	}

	AutoGoForward();


	if(GetVelocity().Size() > MaxSpeedReached)
		MaxSpeedReached = GetVelocity().Size();
	else if(GetVelocity().Size() < MaxSpeedReached)
		GetCharacterMovement()->Velocity = GetVelocity().GetSafeNormal() * MaxSpeedReached;
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABaseCharacter::MoveRight);
}

void ABaseCharacter::MoveRight(const float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue * RightSpeedFactor);
}

void ABaseCharacter::AutoGoForward()
{
	AddMovementInput(GetActorForwardVector(), 1.f);
}

