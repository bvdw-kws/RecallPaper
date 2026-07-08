// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0


#include "RecallPaperActorFactory.h"

#include "Actor/RecallPaperZDCharacterActor.h"
#include "PaperSpriteActor.h"
#include "Representation/Actor/RecallPaperActorTypes.h"
#include "Representation/Actor/Pool/RecallPaperActorPool.h"
#include "StructUtils/InstancedStruct.h"

//----------------------------------------------------------------------//
// URecallPaperCharacterActorFactory
//----------------------------------------------------------------------//
TSharedPtr<IRecallObjectPoolInterface> URecallPaperCharacterActorFactory::BuildActorPool() const
{
	return MakeShared<FRecallPaperCharacterActorPool>();
}

FName URecallPaperCharacterActorFactory::GetActorPoolName(const FInstancedStruct& Desc) const
{
	const FRecallPaperCharacterActorDesc& PaperDesc = Desc.Get<FRecallPaperCharacterActorDesc>();
	if (!PaperDesc.Blueprint.IsNull())
	{
		return *PaperDesc.Blueprint.GetAssetName();
	}
	else
	{
		return ARecallPaperZDCharacterActor::StaticClass()->GetFName();
	}
}

//----------------------------------------------------------------------//
// URecallPaperSpriteActorFactory
//----------------------------------------------------------------------//
TSharedPtr<IRecallObjectPoolInterface> URecallPaperSpriteActorFactory::BuildActorPool() const
{
	return MakeShared<FRecallPaperSpriteActorPool>();
}

FName URecallPaperSpriteActorFactory::GetActorPoolName(const FInstancedStruct& Desc) const
{
	const FRecallPaperSpriteActorDesc& PaperDesc = Desc.Get<FRecallPaperSpriteActorDesc>();
	if (!PaperDesc.Blueprint.IsNull())
	{
		return *PaperDesc.Blueprint.GetAssetName();
	}
	else
	{
		return APaperSpriteActor::StaticClass()->GetFName();
	}
}
