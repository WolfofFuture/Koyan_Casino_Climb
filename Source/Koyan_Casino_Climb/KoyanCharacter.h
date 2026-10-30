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
	// Przypisuje domyœlne wartoœci obiektu postaci
	AKoyanCharacter();

	//Bierze w³aœciwoœci z IAbilitySystemInterafce
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int MaxArmor = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int MaxKoyanCoins = 999999;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int MaxShebaCoins = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int MaxCommandSpells = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int MaxGorgonTail = 30;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//Inicjalizacja default atrybutów
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Koyan FPS")
		TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;
		

	//Inicjalizacja default umiejêtnoœci
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Koyan FPS")
		TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;
		

};
