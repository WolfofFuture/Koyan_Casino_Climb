// Fill out your copyright notice in the Description page of Project Settings.


#include "KCCAttributeSet.h"
#include "KoyanCharacter.h"
UKCCAttributeSet::UKCCAttributeSet() {

}

void UKCCAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	//NewValue = FMath::Clamp(NewValue, 0, 100);

	AKoyanCharacter* KoyanChar = Cast<AKoyanCharacter>(GetOwningActor());

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, KoyanChar->MaxHealth);
	}
	else if (Attribute == GetArmorAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, KoyanChar->MaxArmor);
	}
	else if (Attribute == GetKoyanCoinsAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, KoyanChar->MaxKoyanPoints);
	}
	else if (Attribute == GetShebaCoinsAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, KoyanChar->MaxShebaPoints);
	}
	else if (Attribute == GetCommandSpellsAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, KoyanChar->MaxCommandSpells);
	}

}

bool UKCCAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	float AbsoluteMagnitude = FMath::Abs(Data.EvaluatedData.Magnitude);

	AKoyanCharacter* KoyanChar = Cast<AKoyanCharacter>(GetOwningActor());

	if (Data.EvaluatedData.Magnitude > 0)
	{
		if (Data.EvaluatedData.Attribute == GetArmorAttribute() && GetArmor() + AbsoluteMagnitude >= KoyanChar->MaxArmor)
		{
			SetArmor(KoyanChar->MaxArmor);
			return false;
		}

		else if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() + AbsoluteMagnitude >= KoyanChar->MaxHealth)
		{
			SetHealth(KoyanChar->MaxHealth);
			return false;
		}
		else if (Data.EvaluatedData.Attribute == GetKoyanCoinsAttribute() && GetKoyanCoins() + AbsoluteMagnitude >= KoyanChar->MaxKoyanPoints)
		{
			SetKoyanCoins(KoyanChar->MaxKoyanPoints);
			return false;
		}
		else if (Data.EvaluatedData.Attribute == GetCommandSpellsAttribute() && GetCommandSpells() + AbsoluteMagnitude >= KoyanChar->MaxCommandSpells)
		{
			SetCommandSpells(KoyanChar->MaxCommandSpells);
			return false;
		}
		else if (Data.EvaluatedData.Attribute == GetShebaCoinsAttribute() && GetShebaCoins() + AbsoluteMagnitude >= KoyanChar->MaxShebaPoints)
		{
			SetShebaCoins(KoyanChar->MaxShebaPoints);
			return false;
		}
	}
	else if (Data.EvaluatedData.Magnitude < 0)
	{
		if (Data.EvaluatedData.Attribute == GetArmorAttribute() && AbsoluteMagnitude > GetArmor())
			Health.SetCurrentValue(Health.GetCurrentValue() - (AbsoluteMagnitude - GetArmor()));
	}
	return true;
}

void UKCCAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() < 0)
		SetHealth(0);
	else if (Data.EvaluatedData.Attribute == GetArmorAttribute() && GetArmor() < 0)
		SetArmor(0);
	else if (Data.EvaluatedData.Attribute == GetKoyanCoinsAttribute() && GetKoyanCoins() < 0)
		SetKoyanCoins(0);
	else if (Data.EvaluatedData.Attribute == GetShebaCoinsAttribute() && GetShebaCoins() < 0)
		SetShebaCoins(0);
	else if (Data.EvaluatedData.Attribute == GetCommandSpellsAttribute() && GetCommandSpells() < 0)
		SetCommandSpells(0);
}


