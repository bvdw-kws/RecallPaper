// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0


#include "RecallPaperActorPool.h"

#include "Actor/RecallPaperZDCharacterActor.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"
#include "PaperSpriteActor.h"
#include "PaperSpriteComponent.h"
#include "PaperZDAnimationComponent.h"
#include "Representation/Actor/RecallPaperActorTypes.h"
#include "StructUtils/InstancedStruct.h"

namespace RecallPaperAssetKeys
{
	static constexpr const TCHAR* FLIPBOOK				= TEXT("Flipbook");
	static constexpr const TCHAR* ANIM_INSTANCE			= TEXT("AnimInstance");
	static constexpr const TCHAR* MATERIAL_OVERRIDE		= TEXT("MaterialOverride");
	static constexpr const TCHAR* SPRITE				= TEXT("Sprite");
}

//----------------------------------------------------------------------//
// FRecallPaperCharacterActorPool
//----------------------------------------------------------------------//
template<typename ActorType>
static ActorType* SpawnPoolActor(const TWeakObjectPtr<UWorld>& World, const TSubclassOf<ActorType>& Class)
{
	if (World.IsValid())
	{
		UClass* ActorClass = Class ? *Class : ActorType::StaticClass();
		check(ActorClass);
		ActorType* NewActor = World->SpawnActorDeferred<ActorType>(ActorClass, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		NewActor->bOnlyRelevantToOwner = true;
		NewActor->FinishSpawning(FTransform::Identity);
		return NewActor;
	}

	return nullptr;
}

AActor* FRecallPaperCharacterActorPool::CreateObject(const FInstancedStruct& Desc)
{
	const FRecallPaperCharacterActorDesc& PaperDesc = Desc.Get<FRecallPaperCharacterActorDesc>();
	return SpawnPoolActor<ARecallPaperZDCharacterActor>(GetContainer().GetWorld(), GetActorClass<ARecallPaperZDCharacterActor>());
}

void FRecallPaperCharacterActorPool::InitObject(AActor* Actor, const FInstancedStruct& Desc)
{
	const FRecallPaperCharacterActorDesc& PaperDesc = Desc.Get<FRecallPaperCharacterActorDesc>();

	if (ARecallPaperZDCharacterActor* PaperZDActor = Cast<ARecallPaperZDCharacterActor>(Actor))
	{
		if (UPaperFlipbookComponent* FlipbookComponent = PaperZDActor->GetSprite())
		{
			FlipbookComponent->EmptyOverrideMaterials();
		}

		// Collect assets that need loading
		TMap<FName, FSoftObjectPath> AssetsToLoad;
		if (!PaperDesc.AnimInstance.IsNull())
		{
			AssetsToLoad.Add(RecallPaperAssetKeys::ANIM_INSTANCE, PaperDesc.AnimInstance);
		}
		if (!PaperDesc.Flipbook.IsNull())
		{
			AssetsToLoad.Add(RecallPaperAssetKeys::FLIPBOOK, PaperDesc.Flipbook);
		}
		if (!PaperDesc.MaterialOverride.IsNull())
		{
			AssetsToLoad.Add(RecallPaperAssetKeys::MATERIAL_OVERRIDE, PaperDesc.MaterialOverride);
		}

		// Request async asset loading with callback
		URecallObjectPoolContainer& PoolContainer = GetPoolContainerChecked();
		PoolContainer.RequestActorAssets(Actor, AssetsToLoad,
			[this](AActor* LoadedActor, const TMap<FName, UObject*>& LoadedAssets)
			{
				OnPaperCharacterAssetsLoaded(LoadedActor, LoadedAssets);
			});
	}
}

void FRecallPaperCharacterActorPool::OnPaperCharacterAssetsLoaded(AActor* LoadedActor, const TMap<FName, UObject*>& LoadedAssets)
{
	if (ARecallPaperZDCharacterActor* LoadedPaperActor = Cast<ARecallPaperZDCharacterActor>(LoadedActor))
	{
		// Apply loaded animation instance
		if (UClass* LoadedAnimInstance = Cast<UClass>(LoadedAssets.FindRef(RecallPaperAssetKeys::ANIM_INSTANCE)))
		{
			if (UPaperZDAnimationComponent* AnimComponent = LoadedPaperActor->GetAnimationComponent())
			{
				AnimComponent->SetAnimInstanceClass(LoadedAnimInstance);
			}
		}

		if (UPaperFlipbookComponent* FlipbookComponent = LoadedPaperActor->GetSprite())
		{
			// Apply loaded flipbook
			if (UPaperFlipbook* LoadedFlipbook = Cast<UPaperFlipbook>(LoadedAssets.FindRef(RecallPaperAssetKeys::FLIPBOOK)))
			{
				FlipbookComponent->SetFlipbook(LoadedFlipbook);
			}

			// Apply loaded material override
			if (UMaterialInterface* LoadedMaterial = Cast<UMaterialInterface>(LoadedAssets.FindRef(RecallPaperAssetKeys::MATERIAL_OVERRIDE)))
			{
				FlipbookComponent->SetMaterial(0, LoadedMaterial);
			}
		}
	}
}

void FRecallPaperCharacterActorPool::EnableObject(AActor* Actor)
{
	SetActorActive(Actor, true);
}

void FRecallPaperCharacterActorPool::DisableObject(AActor* Actor)
{
	SetActorActive(Actor, false);
}

//----------------------------------------------------------------------//
// FRecallPaperSpriteActorPool
//----------------------------------------------------------------------//
AActor* FRecallPaperSpriteActorPool::CreateObject(const FInstancedStruct& Desc)
{
	const FRecallPaperSpriteActorDesc& PaperDesc = Desc.Get<FRecallPaperSpriteActorDesc>();
	return SpawnPoolActor<APaperSpriteActor>(GetContainer().GetWorld(), GetActorClass<APaperSpriteActor>());
}

void FRecallPaperSpriteActorPool::InitObject(AActor* Actor, const FInstancedStruct& Desc)
{
	const FRecallPaperSpriteActorDesc& PaperDesc = Desc.Get<FRecallPaperSpriteActorDesc>();

	if (APaperSpriteActor* PaperSpriteActor = Cast<APaperSpriteActor>(Actor))
	{
		// Collect assets that need loading
		TMap<FName, FSoftObjectPath> AssetsToLoad;
		if (!PaperDesc.Sprite.IsNull())
		{
			AssetsToLoad.Add(RecallPaperAssetKeys::SPRITE, PaperDesc.Sprite);
		}

		// Request async asset loading with callback
		URecallObjectPoolContainer& PoolContainer = GetPoolContainerChecked();
		PoolContainer.RequestActorAssets(Actor, AssetsToLoad,
			[this](AActor* LoadedActor, const TMap<FName, UObject*>& LoadedAssets)
			{
				OnPaperSpriteAssetsLoaded(LoadedActor, LoadedAssets);
			});
	}
}

void FRecallPaperSpriteActorPool::OnPaperSpriteAssetsLoaded(AActor* LoadedActor, const TMap<FName, UObject*>& LoadedAssets)
{
	if (APaperSpriteActor* LoadedSpriteActor = Cast<APaperSpriteActor>(LoadedActor))
	{
		// Apply loaded sprite
		if (UPaperSprite* LoadedSprite = Cast<UPaperSprite>(LoadedAssets.FindRef(RecallPaperAssetKeys::SPRITE)))
		{
			if (UPaperSpriteComponent* RenderComponent = LoadedSpriteActor->GetRenderComponent())
			{
				RenderComponent->SetSprite(LoadedSprite);
			}
		}
	}
}

void FRecallPaperSpriteActorPool::EnableObject(AActor* Actor)
{
	SetActorActive(Actor, true);
}

void FRecallPaperSpriteActorPool::DisableObject(AActor* Actor)
{
	SetActorActive(Actor, false);
}
