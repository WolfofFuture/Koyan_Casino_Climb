// Fill out your copyright notice in the Description page of Project Settings.


#include "KCCAttributeSet.h"
UKCCAttributeSet::UKCCAttributeSet() {

}

void UKCCAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	NewValue = FMath::Clamp(NewValue, 0, 100);
}

bool UKCCAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	float ArmorDamage = FMath::Abs(Data.EvaluatedData.Magnitude);

	if (Data.EvaluatedData.Attribute == GetArmorAttribute() && ArmorDamage > GetArmor() && Data.EvaluatedData.Magnitude < 0)
		Health.SetCurrentValue(Health.GetCurrentValue() - (ArmorDamage - GetArmor()));
	
	return true;
}


