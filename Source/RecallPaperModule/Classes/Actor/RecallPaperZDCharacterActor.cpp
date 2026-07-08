// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0


#include "RecallPaperZDCharacterActor.h"

#include "Animation/RecallPaperZDAnimInstance.h"
#include "PaperCharacter.h"
#include "PaperZDAnimationComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimInstance.h"

ARecallPaperZDCharacterActor::ARecallPaperZDCharacterActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootComponent"));
	
	// Try to create the sprite component
	Sprite = CreateOptionalDefaultSubobject<UPaperFlipbookComponent>(APaperCharacter::SpriteComponentName);
	if (Sprite)
	{
		Sprite->AlwaysLoadOnClient = true;
		Sprite->AlwaysLoadOnServer = true;
		Sprite->bOwnerNoSee = false;
		Sprite->bAffectDynamicIndirectLighting = true;
		Sprite->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Sprite->SetupAttachment(GetRootComponent());
		static FName CollisionProfileName(TEXT("CharacterMesh"));
		Sprite->SetCollisionProfileName(CollisionProfileName);
		Sprite->SetGenerateOverlapEvents(false);
	}
	
	AnimationComponent = CreateDefaultSubobject<UPaperZDAnimationComponent>(TEXT("Animation"));
	AnimationComponent->InitRenderComponent(GetSprite());
}

TSubclassOf<UPaperZDAnimInstance> ARecallPaperZDCharacterActor::GetSequencerAnimInstanceClass() const
{
	return AnimationComponent->GetSequencerAnimInstanceClass();
}

UPaperZDAnimInstance* ARecallPaperZDCharacterActor::GetSequencerAnimInstance()
{
	return AnimationComponent->GetSequencerAnimInstance();
}

URecallPaperZDAnimInstance* ARecallPaperZDCharacterActor::GetAnimInstance() const
{
	return Cast<URecallPaperZDAnimInstance>(AnimationComponent->GetAnimInstance());
}
