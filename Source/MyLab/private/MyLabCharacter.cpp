// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyLabCharacter.h"

#include "EngineUtils.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Engine/StaticMeshActor.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AMyLabCharacter

AMyLabCharacter::AMyLabCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	bIsMatAlreadyChanged = false;
}

void AMyLabCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

#pragma region _01_SearchDifferentTypes
	if (const auto pWorld = GetWorld())
	{
		for (const auto& ActorRange : FActorRange(pWorld))
		{
			if (const auto SM_Actor_temp = Cast<AStaticMeshActor>(ActorRange))
			{
				const auto SM_Comp_temp = SM_Actor_temp->GetStaticMeshComponent();
				MapOfActors.Add(ActorRange, {SM_Comp_temp, SM_Comp_temp->GetMaterials()});
			}
		}
	}
#pragma endregion _01_SearchDifferentTypes
}

//////////////////////////////////////////////////////////////////////////// Input

void AMyLabCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyLabCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyLabCharacter::Look);

		// SearchDifferentTypes
		EnhancedInputComponent->BindAction(SearchAction, ETriggerEvent::Triggered, this, &AMyLabCharacter::SearchActor);

		// ShowHierarchy
		EnhancedInputComponent->BindAction(ShowHierarchy, ETriggerEvent::Triggered, this, &AMyLabCharacter::SearchActor);
		EnhancedInputComponent->BindAction(ShowHierarchy, ETriggerEvent::Triggered, this, &AMyLabCharacter::SearchActor);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void AMyLabCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AMyLabCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMyLabCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AMyLabCharacter::GetHasRifle()
{
	return bHasRifle;
}

#pragma region _01_SearchDifferentTypes
auto AMyLabCharacter::SearchActor(const FInputActionValue& Value) -> void
{
	for (auto Iter = MapOfActors.CreateConstIterator(); Iter; ++Iter)
	{
		if (Iter.Key()->ActorHasTag(TEXT("Equipment")))
			if (!bIsMatAlreadyChanged)
				Iter.Value().SM_Comp->SetOverlayMaterial(Mat_Overlay);
			else
				Iter.Value().SM_Comp->SetOverlayMaterial(nullptr);
		else if (!bIsMatAlreadyChanged)
			for (int32 i = 0; i < Iter.Value().SM_Comp->GetMaterials().Num(); ++i)
				Iter.Value().SM_Comp->SetMaterial(i, Mat_TransParent);
		else
			for (int32 i = 0; i < Iter.Value().SM_Comp->GetMaterials().Num(); ++i)
				Iter.Value().SM_Comp->SetMaterial(i, Iter.Value().Materials[i]);
	}

	bIsMatAlreadyChanged = !bIsMatAlreadyChanged;
}
#pragma endregion _01_SearchDifferentTypes

#pragma region _02_ParseHierarchy
	
#pragma endregion _02_ParseHierarchy
