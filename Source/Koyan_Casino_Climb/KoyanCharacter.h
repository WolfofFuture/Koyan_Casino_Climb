// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Misc/Optional.h"
#include "GameplayTagContainer.h"
#include <GameplayEffectTypes.h>
#include "AbilitySystemInterface.h"
#include "KoyanCharacter.generated.h"

UCLASS()
class KOYAN_CASINO_CLIMB_API AKoyanCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY()
	class UKCCAttributeSet* Attributes;

public:
	// Sets default values for this character's properties
	AKoyanCharacter();

	//Bierze z IAbilitySystemInterafce
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//Inicjalizacja default atrybutów
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "KoyanAtr")
		TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;
		//TSoftClassPtr<class UGameplayEffect> DefaultAttributeEffect;

	//Zbior umiejek
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "KoyanAnili")
		TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;
		//TArray<TSoftClassPtr<class UGameplayAbility>> DefaultAbilities;

};
