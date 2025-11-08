// Fill out your copyright notice in the Description page of Project Settings.


#include "PaizyCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APaizyCharacterBase::APaizyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// add the ability system component by replication mode settings
	m_abilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	m_abilitySystemComponent->SetIsReplicated(true);
	m_abilitySystemComponent->SetReplicationMode(m_abilitySystemReplicationMode);

	// set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(35.f, 90.f);

	// don't rotate when the controller rotates. let that just affect the camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f); 

	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;	// Value semantics: 0 = no mid-air steering, 1 = almost full steering
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;
}

// Called when the game starts or when spawned
void APaizyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APaizyCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (m_abilitySystemComponent)
	{
		m_abilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void APaizyCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (m_abilitySystemComponent)
	{
		m_abilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

// Called every frame
void APaizyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APaizyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

class UAbilitySystemComponent* APaizyCharacterBase::GetAbilitySystemComponent() const
{
		return m_abilitySystemComponent;
}

