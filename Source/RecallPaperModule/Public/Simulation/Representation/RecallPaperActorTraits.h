// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "MassEntityTraitBase.h"
#include "Representation/Actor/RecallPaperActorTypes.h"

#include "RecallPaperActorTraits.generated.h"

class UPaperFlipbookComponent;

UCLASS(meta=(DisplayName="RE PaperZD Character Actor"))
class URecallPaperCharacterActorTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()

public:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;

public:
	/**
	 * Editor utility method to apply this trait settings to a preview component.
	 */
	UFUNCTION(BlueprintCallable)
	void ApplyToFlipbookComponent(UPaperFlipbookComponent* FlipbookComponent);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ShowOnlyInnerProperties))
	FRecallPaperCharacterActorDesc Definition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTransform Offset = FTransform::Identity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bUseActorScale = true;
};

UCLASS(meta=(DisplayName="RE Paper Sprite Actor"))
class URecallPaperSpriteActorTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()

public:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;

public:
	/**
	 * Editor utility method to apply this trait settings to a preview component.
	 */
	UFUNCTION(BlueprintCallable)
	void ApplyToSpriteComponent(UPaperSpriteComponent* SpriteComponent);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ShowOnlyInnerProperties))
	FRecallPaperSpriteActorDesc Definition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTransform Offset = FTransform::Identity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bUseActorScale = true;
};
