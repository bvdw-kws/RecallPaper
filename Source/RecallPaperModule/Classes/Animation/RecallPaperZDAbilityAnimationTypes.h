// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "CoreMinimal.h"
#include "Data/Ability/RecallAbilityAnimationTypes.h"
#include "AnimSequences/PaperZDAnimSequence.h"

#include "RecallPaperZDAbilityAnimationTypes.generated.h"

USTRUCT(BlueprintType, DisplayName="PaperZD Anim Sequence")
struct RECALLPAPERMODULE_API FRecallPaperZDAnimSequenceWrapper : public FRecallAbilityAnimationWrapperBase
{
	GENERATED_BODY()
	
	/**
	 * Animation to play during the anim section.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UPaperZDAnimSequence> Asset;

	virtual TObjectPtr<UObject> GetAnimationAsset() const override
	{
		return Asset;
	}
};
