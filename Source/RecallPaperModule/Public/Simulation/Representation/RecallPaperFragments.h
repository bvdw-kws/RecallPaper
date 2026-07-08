// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "MassEntityTypes.h"
#include "Representation/Actor/RecallPaperActorTypes.h"

#include "RecallPaperFragments.generated.h"

USTRUCT()
struct FRecallPaperCharacterConstSharedFragment : public FMassConstSharedFragment
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	FRecallPaperCharacterActorDesc Definition;
};

USTRUCT()
struct FRecallPaperSpriteConstSharedFragment : public FMassConstSharedFragment
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	FRecallPaperSpriteActorDesc Definition;
};
