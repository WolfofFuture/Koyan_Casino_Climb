// Fill out your copyright notice in the Description page of Project Settings.


#include "KCCCharacter.h"
#include "AbilitySystemComponent.h"
#include "KCCAttributeSet.h"

// Sets default values
AKCCCharacter::AKCCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	Attributes = CreateDefaultSubobject<UKCCAttributeSet>("Attributes");

}

UAbilitySystemComponent* AKCCCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AKCCCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent) 
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		//przypisanie defaultowych atrybutów
		if (DefaultAttributeEffect) 
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddSourceObject(this);
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
		//przypisanie umiejek
		if (HasAuthority())
		{
			for (TSubclassOf<UGameplayAbility>& StartupAbility : DefaultAbilities)
			{
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility.GetDefaultObject(), 1, 0));
			}
		}
	}
}



