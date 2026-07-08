// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0


#include "Simulation/Representation/RecallPaperActorTraits.h"

#include "MassEntityTemplateRegistry.h"
#include "MassEntityView.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Simulation/Representation/RecallActorRepresentationFragments.h"
#include "Simulation/Representation/RecallPaperFragments.h"
#include "Simulation/Transform/RecallTransformFragments.h"
#include "Utility/Trait/RecallTraitUtils.h"

#if WITH_EDITORONLY_DATA
#include "PaperFlipbookComponent.h"
#endif // WITH_EDITORONLY_DATA

//----------------------------------------------------------------------//
// URecallPaperCharacterActorTrait
//----------------------------------------------------------------------//
void URecallPaperCharacterActorTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	FMassEntityManager& EntityManager = UE::Mass::Utils::GetEntityManagerChecked(World);
	
	BuildContext.RequireFragment<FRecallTransformFragment>();

	FRecallActorRepresentationFragment& ActorFragment = BuildContext.AddFragment_GetRef<FRecallActorRepresentationFragment>();
	ActorFragment.Offset = Offset;

	if (bUseActorScale)
	{
		BuildContext.GetMutableObjectFragmentInitializers().Add([this, &World](UObject& Owner, FMassEntityView& EntityView, const EMassTranslationDirection CurrentDirection)
			{
				if (const AActor* Actor = Recall::Trait::Utils::AsActor(Owner))
				{
					FRecallActorRepresentationFragment& ActorRepresentationFragment = EntityView.GetFragmentData<FRecallActorRepresentationFragment>();
					ActorRepresentationFragment.Scale *= Actor->GetActorScale3D();
				}
			}
		);
	}

	FRecallPaperCharacterConstSharedFragment SharedFragment;
	SharedFragment.Definition = Definition;

	BuildContext.AddConstSharedFragment(EntityManager.GetOrCreateConstSharedFragment(SharedFragment));
}

void URecallPaperCharacterActorTrait::ApplyToFlipbookComponent(UPaperFlipbookComponent* FlipbookComponent)
{
#if WITH_EDITORONLY_DATA
	if (!IsValid(FlipbookComponent))
	{
		return;
	}

	FlipbookComponent->EmptyOverrideMaterials();

	// Load soft object paths for editor preview
	if (UPaperFlipbook* LoadedFlipbook = Cast<UPaperFlipbook>(Definition.Flipbook.TryLoad()))
	{
		FlipbookComponent->SetFlipbook(LoadedFlipbook);
	}

	FlipbookComponent->SetRelativeTransform(Offset);

	if (UMaterialInterface* LoadedMaterial = Cast<UMaterialInterface>(Definition.MaterialOverride.TryLoad()))
	{
		FlipbookComponent->SetMaterial(0, LoadedMaterial);
	}
#endif // WITH_EDITORONLY_DATA
}

//----------------------------------------------------------------------//
// URecallPaperSpriteActorTrait
//----------------------------------------------------------------------//
void URecallPaperSpriteActorTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	FMassEntityManager& EntityManager = UE::Mass::Utils::GetEntityManagerChecked(World);
	
	BuildContext.RequireFragment<FRecallTransformFragment>();

	FRecallActorRepresentationFragment& ActorFragment = BuildContext.AddFragment_GetRef<FRecallActorRepresentationFragment>();
	ActorFragment.Offset = Offset;

	if (bUseActorScale)
	{
		BuildContext.GetMutableObjectFragmentInitializers().Add([this, &World](UObject& Owner, FMassEntityView& EntityView, const EMassTranslationDirection CurrentDirection)
			{
				if (const AActor* Actor = Recall::Trait::Utils::AsActor(Owner))
				{
					FRecallActorRepresentationFragment& ActorRepresentationFragment = EntityView.GetFragmentData<FRecallActorRepresentationFragment>();
					ActorRepresentationFragment.Scale *= Actor->GetActorScale3D();
				}
			}
		);
	}

	FRecallPaperSpriteConstSharedFragment SharedFragment;
	SharedFragment.Definition = Definition;

	BuildContext.AddConstSharedFragment(EntityManager.GetOrCreateConstSharedFragment(SharedFragment));
}

void URecallPaperSpriteActorTrait::ApplyToSpriteComponent(UPaperSpriteComponent* SpriteComponent)
{
#if WITH_EDITORONLY_DATA
	if (!IsValid(SpriteComponent))
	{
		return;
	}

	SpriteComponent->EmptyOverrideMaterials();

	// Load soft object path for editor preview
	if (UPaperSprite* LoadedSprite = Cast<UPaperSprite>(Definition.Sprite.TryLoad()))
	{
		SpriteComponent->SetSprite(LoadedSprite);
	}

	SpriteComponent->SetRelativeTransform(Offset);
#endif // WITH_EDITORONLY_DATA
}
