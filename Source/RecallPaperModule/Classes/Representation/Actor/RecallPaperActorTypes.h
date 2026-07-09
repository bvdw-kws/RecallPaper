// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "Representation/Actor/RecallActorRepresentationTypes.h"
#include "UObject/SoftObjectPath.h"

#include "RecallPaperActorTypes.generated.h"

USTRUCT(BlueprintType)
struct RECALLPAPERMODULE_API FRecallPaperCharacterActorDesc : public FRecallActorRepresentationDesc
{
	GENERATED_BODY()

	FRecallPaperCharacterActorDesc();

	/** Blueprint used for the representation of our entity. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowedClasses="/Script/RecallPaperModule.RecallPaperZDCharacterActor"))
	FSoftClassPath Blueprint;

	/**
	 * PaperZD anim instance class.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowedClasses="/Script/RecallPaperModule.RecallPaperZDAnimInstance"))
	FSoftClassPath AnimInstance;

	/**
	 * Default flipbook. Optional if anim instance is not set.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowedClasses="/Script/Paper2D.PaperFlipbook"))
	FSoftObjectPath Flipbook;

	/**
	 * Material to use for this sprite.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowedClasses="/Script/Engine.MaterialInterface"))
	FSoftObjectPath MaterialOverride;

	virtual FSoftClassPath GetSoftClassPath() const override { return Blueprint; }
};

USTRUCT(BlueprintType)
struct RECALLPAPERMODULE_API FRecallPaperSpriteActorDesc : public FRecallActorRepresentationDesc
{
	GENERATED_BODY()

	FRecallPaperSpriteActorDesc();

	/** Blueprint used for the representation of our entity. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowedClasses="/Script/Paper2D.PaperSpriteActor"))
	FSoftClassPath Blueprint;

	/**
	 * Sprite used for this actor
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowedClasses="/Script/Paper2D.PaperSprite"))
	FSoftObjectPath Sprite;

	virtual FSoftClassPath GetSoftClassPath() const override { return Blueprint; }
};
