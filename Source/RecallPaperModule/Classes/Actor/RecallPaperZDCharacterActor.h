// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "GameFramework/Actor.h"
#include "Sequencer/IPaperZDSequencerSource.h"

#include "RecallPaperZDCharacterActor.generated.h"

class URecallPaperZDAnimInstance;
class UPaperZDAnimationComponent;
class UPaperZDAnimInstance;

UCLASS(Blueprintable)
class RECALLPAPERMODULE_API ARecallPaperZDCharacterActor : public AActor, public IPaperZDSequencerSource
{
	GENERATED_UCLASS_BODY()
	
private:
	/** The main skeletal mesh associated with this Character (optional sub-object). */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPaperFlipbookComponent> Sprite;

	/* Animation component that manages the AnimBP. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PaperZD", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperZDAnimationComponent> AnimationComponent;

public:

	//~ Begin IPaperZDSequencerSource Interface
	virtual TSubclassOf<UPaperZDAnimInstance> GetSequencerAnimInstanceClass() const override;
	virtual UPaperZDAnimInstance* GetSequencerAnimInstance() override;
	//~ End IPaperZDSequencerSource Interface

	/** Returns Sprite subobject **/
	FORCEINLINE class UPaperFlipbookComponent* GetSprite() const { return Sprite; }
	
	//getters
	FORCEINLINE UPaperZDAnimationComponent* GetAnimationComponent() const { return AnimationComponent; }

	/* Obtain the AnimInstance that drives this character. */
	UFUNCTION(BlueprintPure, Category = "PaperZD")
	URecallPaperZDAnimInstance* GetAnimInstance() const;
};
