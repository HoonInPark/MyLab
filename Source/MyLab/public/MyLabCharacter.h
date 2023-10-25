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


USTRUCT(Atomic, BlueprintType)
struct FHierarchyActors
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> UpperActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> LowerActors;
};


USTRUCT(Atomic, BlueprintType)
struct FMaterialStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* SM_Comp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMaterialInterface*> Materials;
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

#pragma endregion _01_SearchDifferentTypes
	/**
	 * Equipment 태그가 달린 녀석들만 수집해서 동적으로 TMap 생성.
	 * 수동으로 하나하나 TMap에 넣는 방법은 다음과 같은 에러 메시지와 함께 안된다.
	 * Illegal TEXT reference to a private object in external package
	 *
	 * 일단 예제로 만든 Per 레벨에 속한 SM_ChamferCube1는 하위로 2와 3을 두고 있고,
	 * 3이 하위로 4를 두고 있다고 해보고 계통도 로직을 초기화해 보자.
{
  "Actors": [
	{
	  "Name": "SM_ChamferCube1",
	  "UpperObject": null,
	  "LowerObject": ["SM_ChamferCube2", "SM_ChamferCube3"]
	},
	{
	  "Name": "SM_ChamferCube2",
	  "UpperObject": ["SM_ChamferCube1"],
	  "LowerObject": [null]
	},
	{
	  "Name": "SM_ChamferCube3",
	  "UpperObject": ["SM_ChamferCube1"],
	  "LowerObject": ["SM_ChamferCube4”]
	},
	{
	  "Name":"SM_ChamferCube4",
		  "UpperObject":["SM_ChamferCube3”],
		  "LowerObject":[null]
	 }
   ]
}
	 */
	UPROPERTY()
	TMap<AActor*, FMaterialStruct> MapOfActors;

protected:
	void SearchActor(const FInputActionValue& Value);
#pragma region _02_ParseHierarchy

public:
	UPROPERTY()
	TMap<AActor*, FHierarchyActors> MapOfHierarchy;

	UFUNCTION(BlueprintCallable, Category=Hierarchy)
	void MakeHierarchy(FString _ActorNameOrLabel, TArray<AActor*> _UpperActors, TArray<AActor*> _LowerActors);
#pragma endregion _02_ParseHierarchy
};
