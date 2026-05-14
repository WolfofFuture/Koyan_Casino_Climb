// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPooled.h"

// Sets default values for this component's properties
UObjectPooled::UObjectPooled()
{
}


// Called when the game starts
void UObjectPooled::BeginPlay()
{
	Super::BeginPlay();

	if (PooledObjectClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr) {
			for (int i = 0; i < PoolSize; i++)
			{
				APooledObject* PoolableActor = World->SpawnActor<APooledObject>(PooledObjectClass, FVector().ZeroVector, FRotator().ZeroRotator);
				if (PoolableActor != nullptr)
				{
					PoolableActor->SetActive(false);
					PoolableActor->SetPoolIndex(i);
					PoolableActor->OnPooledObjectDespawn.AddDynamic(this, &UObjectPooled::OnPooledObjectDespawn);
					ObjectPool.Add(PoolableActor);
				}
			}
		}
	}
	
}
APooledObject* UObjectPooled::SpawnPooledObject()
{

	for (APooledObject* PoolableActor : ObjectPool) 
	{
		if (PoolableActor != nullptr && !PoolableActor->IsActive()) 
		{
			PoolableActor->TeleportTo(FVector(0,0,0), FRotator(0,0,0));
			PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
			PoolableActor->SetActive(true);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
			
			return  PoolableActor;
		}
	}

	if (SpawnedPoolIndexes.Num() > 0)
	{
		int PooledObjectIndex = SpawnedPoolIndexes[0];
		SpawnedPoolIndexes.Remove(PooledObjectIndex);
		APooledObject* PoolableActor = ObjectPool[PooledObjectIndex];

		if (PoolableActor != nullptr)
		{
			PoolableActor->SetActive(false);
			PoolableActor->TeleportTo(FVector(0, 0, 0), FRotator(0, 0, 0));
			PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
			PoolableActor->SetActive(true);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
			return  PoolableActor;
		}
	}

	return nullptr;
}
void UObjectPooled::OnPooledObjectDespawn(APooledObject* PoolActor)
{
	SpawnedPoolIndexes.Remove(PoolActor->GetPoolIndex());
}