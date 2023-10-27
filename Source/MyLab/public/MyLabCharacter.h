// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MyLab.h"
#include "GameFramework/Character.h"
#include "MyLabCharacter.generated.h"

struct FInputActionValue;
struct FMaterialStruct;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FAbsorptionChillerHeater
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Hierarchy)
	TMap<TSoftObjectPtr<AActor>, FName> coolingWaterSupplyLineGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Hierarchy)
	TMap<TSoftObjectPtr<AActor>, FName> coolingWaterReturnLineGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Hierarchy)
	TMap<TSoftObjectPtr<AActor>, FName> chilledWaterSupplyLineGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Hierarchy)
	TMap<TSoftObjectPtr<AActor>, FName> chilledWaterReturnLineGroup;
};

USTRUCT(Atomic, BlueprintType)
struct FMaterialStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* SM_Comp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UMaterialInterface*> Materials;
};

UENUM(BlueprintType)
enum class EHierarchyType : uint8
{
	HIERARCHY_1 UMETA(DisplayName="Hierarchy_1"),
	HIERARCHY_2 UMETA(DisplayName="Hierarchy_2")
};

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AMyLabCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

public:
	AMyLabCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	/**
	 * 
	 */
#pragma region _01_SearchDifferentTypes

public:
	UPROPERTY()
	bool bIsMatAlreadyChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Material)
	UMaterialInstance* Mat_Overlay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Material)
	UMaterialInstance* Mat_TransParent;

private:
	/** Search Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SearchAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ShowHierarchy_1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ShowHierarchy_2;
	
#pragma endregion _01_SearchDifferentTypes
	UPROPERTY()
	TMap<AActor*, FMaterialStruct> MapOfActors;

protected:
	void SearchActor(const FInputActionValue& Value);
	
#pragma region _02_ParseHierarchy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Hierarchy)
	FAbsorptionChillerHeater AbsorptionChillerHeater_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Hierarchy)
	FAbsorptionChillerHeater AbsorptionChillerHeater_2;

	void ShowHierarchy_01(const FInputActionValue& Value);
	void ShowHierarchy_02(const FInputActionValue& Value);

	void ShowHierarchy(EHierarchyType _HierarchyType);
#pragma endregion _02_ParseHierarchy
};
