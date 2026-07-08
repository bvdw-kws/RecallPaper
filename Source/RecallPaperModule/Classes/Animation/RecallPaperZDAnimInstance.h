// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "PaperZDAnimInstance.h"

#include "RecallPaperZDAnimInstance.generated.h"

class URecallAbilityAsset;

UCLASS(Blueprintable)
class URecallPaperZDAnimInstance : public UPaperZDAnimInstance
{
	GENERATED_BODY()

#pragma region Ability
public:
	// Tracks the last game frame when the most recent animation montage was played
	UPROPERTY(Transient)
	int32 LastMontageChangeGameFrame = 0;

	UPROPERTY(Transient, BlueprintReadOnly, Category=Animation)
	float AnimBlend = 0.0f;
	
	UPROPERTY(Transient, BlueprintReadOnly, Category=Animation)
	float BlendSpaceInputX = 0.0f;
	
	UPROPERTY(Transient, BlueprintReadOnly, Category=Animation)
	float BlendSpaceInputY = 0.0f;
	
	UPROPERTY(Transient, BlueprintReadOnly, Category=Animation)
	float LocomotionBlend = 1.0f;
	
public:
	UFUNCTION(BlueprintCallable)
	void PlayAnimSequence(UPaperZDAnimSequence* BlendSpace);
	
	void SynchronizeToAbilityFrame(const URecallAbilityAsset* Ability, float Frame);
#pragma endregion Ability

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bGrounded = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Units=CentimetersPerSecond))
	FVector Velocity = FVector::ZeroVector;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector2f MovementDirection = FVector2f::ZeroVector;
};
