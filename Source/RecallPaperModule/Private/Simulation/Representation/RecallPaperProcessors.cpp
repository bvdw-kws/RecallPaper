// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0


#include "RecallPaperProcessors.h"

#include "Actor/RecallPaperZDCharacterActor.h"
#include "Animation/RecallPaperZDAnimInstance.h"
#include "MassExecutionContext.h"
#include "Physics/RecallPhysicsObjects.h"
#include "Simulation/Ability/RecallAbilityFragments.h"
#include "Simulation/Movement/RecallMovementFragments.h"
#include "Simulation/Physics/RecallPhysicsBodyFragment.h"
#include "Simulation/Physics/RecallPhysicsCharacterFragments.h"
#include "Simulation/Representation/RecallPaperFragments.h"
#include "Simulation/Representation/RecallActorRepresentationFragments.h"
#include "System/Actor/RecallActorSubsystem.h"
#include "System/Physics/RecallPhysicsSubsystem.h"
#include "Utility/Math/RecallMathUtils.h"
#include "Utility/Simulation/RecallSimulationUtils.h"

//----------------------------------------------------------------------//
// URecallPaperCharacterInitializer
//----------------------------------------------------------------------//
URecallPaperCharacterInitializer::URecallPaperCharacterInitializer()
	: EntityQuery(*this)
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::All);
	ObservedTypes.Add(FRecallActorRepresentationFragment::StaticStruct());
	ObservedOperations = EMassObservedOperationFlags::Add;
}

void URecallPaperCharacterInitializer::InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& InEntityManager)
{
	Super::InitializeInternal(Owner, InEntityManager);
}

void URecallPaperCharacterInitializer::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	EntityQuery.AddRequirement<FRecallActorRepresentationFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddConstSharedRequirement<FRecallPaperCharacterConstSharedFragment>(EMassFragmentPresence::All);
	EntityQuery.AddSubsystemRequirement<URecallActorSubsystem>(EMassFragmentAccess::ReadWrite);
}

void URecallPaperCharacterInitializer::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk(Context, [](FMassExecutionContext& Context)
	{
		URecallActorSubsystem& ActorSystem = Context.GetMutableSubsystemChecked<URecallActorSubsystem>();

		const FRecallPaperCharacterConstSharedFragment& PaperConstSharedFragment = Context.GetConstSharedFragment<FRecallPaperCharacterConstSharedFragment>();

		const TArrayView<FRecallActorRepresentationFragment> ActorList = Context.GetMutableFragmentView<FRecallActorRepresentationFragment>();

		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); EntityIndex++)
		{
			FRecallActorRepresentationFragment& ActorFragment = ActorList[EntityIndex];
			if (ActorFragment.ActorHandle.IsSet())
			{
				continue;
			}

			ActorFragment.ActorHandle = ActorSystem.CreateActor(PaperConstSharedFragment.Definition);
		}
	});
}

//----------------------------------------------------------------------//
// URecallPaperSpriteInitializer
//----------------------------------------------------------------------//
URecallPaperSpriteInitializer::URecallPaperSpriteInitializer()
	: EntityQuery(*this)
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::All);
	ObservedTypes.Add(FRecallActorRepresentationFragment::StaticStruct());
	ObservedOperations = EMassObservedOperationFlags::Add;
}

void URecallPaperSpriteInitializer::InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& InEntityManager)
{
	Super::InitializeInternal(Owner, InEntityManager);
}

void URecallPaperSpriteInitializer::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	EntityQuery.AddRequirement<FRecallActorRepresentationFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddConstSharedRequirement<FRecallPaperSpriteConstSharedFragment>(EMassFragmentPresence::All);
	EntityQuery.AddSubsystemRequirement<URecallActorSubsystem>(EMassFragmentAccess::ReadWrite);
}

void URecallPaperSpriteInitializer::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk(Context, [](FMassExecutionContext& Context)
	{
		URecallActorSubsystem& ActorSystem = Context.GetMutableSubsystemChecked<URecallActorSubsystem>();

		const FRecallPaperSpriteConstSharedFragment& PaperConstSharedFragment = Context.GetConstSharedFragment<FRecallPaperSpriteConstSharedFragment>();

		const TArrayView<FRecallActorRepresentationFragment> ActorList = Context.GetMutableFragmentView<FRecallActorRepresentationFragment>();

		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); EntityIndex++)
		{
			FRecallActorRepresentationFragment& ActorFragment = ActorList[EntityIndex];
			if (ActorFragment.ActorHandle.IsSet())
			{
				continue;
			}

			ActorFragment.ActorHandle = ActorSystem.CreateActor(PaperConstSharedFragment.Definition);
		}
	});
}

//----------------------------------------------------------------------//
// URecallPaperAnimationRepresentationProcessor
//----------------------------------------------------------------------//
URecallPaperAnimationRepresentationProcessor::URecallPaperAnimationRepresentationProcessor()
	: EntityQuery(*this)
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::All);
	ProcessingPhase = EMassProcessingPhase::Render;
	bRequiresGameThreadExecution = true;
}

void URecallPaperAnimationRepresentationProcessor::InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& InEntityManager)
{
	Super::InitializeInternal(Owner, InEntityManager);
}

void URecallPaperAnimationRepresentationProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	EntityQuery.AddRequirement<FRecallActorRepresentationFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddRequirement<FRecallMovementFragment>(EMassFragmentAccess::ReadOnly, EMassFragmentPresence::Optional);
	EntityQuery.AddRequirement<FJPRPhysicsBodyFragment>(EMassFragmentAccess::ReadOnly, EMassFragmentPresence::Optional);
	EntityQuery.AddRequirement<FJPRPhysicsCharacterFragment>(EMassFragmentAccess::ReadOnly, EMassFragmentPresence::Optional);
	EntityQuery.AddConstSharedRequirement<FRecallPaperCharacterConstSharedFragment>(EMassFragmentPresence::All);
	EntityQuery.AddSubsystemRequirement<URecallActorSubsystem>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddSubsystemRequirement<URecallPhysicsSubsystem>(EMassFragmentAccess::ReadOnly);
}

void URecallPaperAnimationRepresentationProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(Recall_Paper_AnimationRepresentation);

	EntityQuery.ForEachEntityChunk(Context, [](FMassExecutionContext& Context)
	{
		const URecallActorSubsystem& ActorSystem = Context.GetSubsystemChecked<URecallActorSubsystem>();
		const URecallPhysicsSubsystem& PhysicsSystem = Context.GetSubsystemChecked<URecallPhysicsSubsystem>();

		const TConstArrayView<FRecallActorRepresentationFragment> ActorList = Context.GetFragmentView<FRecallActorRepresentationFragment>();
		const TConstArrayView<FRecallMovementFragment> MovementList = Context.GetFragmentView<FRecallMovementFragment>();
		const TConstArrayView<FJPRPhysicsBodyFragment> BodyList = Context.GetFragmentView<FJPRPhysicsBodyFragment>();
		const TConstArrayView<FJPRPhysicsCharacterFragment> CharacterList = Context.GetFragmentView<FJPRPhysicsCharacterFragment>();

		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); EntityIndex++)
		{
			const FRecallActorRepresentationFragment& ActorFragment = ActorList[EntityIndex];

			const TWeakObjectPtr<ARecallPaperZDCharacterActor> PaperZDActor = ActorSystem.GetActor<ARecallPaperZDCharacterActor>(ActorFragment.ActorHandle);
			if (!PaperZDActor.IsValid())
			{
				continue;
			}

			URecallPaperZDAnimInstance* AnimInstance =PaperZDActor->GetAnimInstance();
			if (!IsValid(AnimInstance))
			{
				continue;
			}

			if (MovementList.IsValidIndex(EntityIndex))
			{
				const FRecallMovementFragment& MovementFragment = MovementList[EntityIndex];
				AnimInstance->MovementDirection = MovementFragment.MovementDirection;
			}

			if (BodyList.IsValidIndex(EntityIndex))
			{
				const FJPRPhysicsBodyFragment& BodyFragment = BodyList[EntityIndex];
				const FConstRecallPhysicsBodyView Body = PhysicsSystem.GetBody(BodyFragment.BodyHandle);
				if (Body.IsValid())
				{
					AnimInstance->Velocity = Recall::Math::Utils::UnitsPerFrameToPerSecond(
						Body.GetLinearVelocity());
				}
			}

			if (CharacterList.IsValidIndex(EntityIndex))
			{
				const FJPRPhysicsCharacterFragment& CharacterFragment = CharacterList[EntityIndex];
				AnimInstance->bGrounded = CharacterFragment.bIsSupported;
			}
		}
	});
}

//----------------------------------------------------------------------//
// URecallAbilityAnimationPaperRepresentationProcessor
//----------------------------------------------------------------------//
URecallAbilityAnimationPaperRepresentationProcessor::URecallAbilityAnimationPaperRepresentationProcessor()
	: EntityQuery(*this)
{
	ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::All);
	ProcessingPhase = EMassProcessingPhase::Render;
	bRequiresGameThreadExecution = true;
}

void URecallAbilityAnimationPaperRepresentationProcessor::InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& InEntityManager)
{
	Super::InitializeInternal(Owner, InEntityManager);
}

void URecallAbilityAnimationPaperRepresentationProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	EntityQuery.AddRequirement<FRecallAbilityAnimationFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddRequirement<FRecallActorRepresentationFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddRequirement<FRecallAbilityFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddConstSharedRequirement<FRecallPaperCharacterConstSharedFragment>(EMassFragmentPresence::All);
	EntityQuery.AddSubsystemRequirement<URecallActorSubsystem>(EMassFragmentAccess::ReadOnly);
}

void URecallAbilityAnimationPaperRepresentationProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	QUICK_SCOPE_CYCLE_COUNTER(Recall_AbilityAnimationPaper_Representation);

	EntityQuery.ForEachEntityChunk(Context, [](FMassExecutionContext& Context)
	{
		const uint32 Frame = Recall::Simulation::Utils::GetFrame(Context.GetWorld());		
		const float FixedDeltaTime = Recall::Simulation::Utils::GetFixedDeltaTime(Context.GetWorld());

		const URecallActorSubsystem& ActorSystem = Context.GetSubsystemChecked<URecallActorSubsystem>();
		
		const TConstArrayView<FRecallAbilityFragment> AbilityList = Context.GetFragmentView<FRecallAbilityFragment>();
			
		const TConstArrayView<FRecallActorRepresentationFragment> ActorList = Context.GetFragmentView<FRecallActorRepresentationFragment>();
		const TConstArrayView<FRecallAbilityAnimationFragment> AnimationLIst = Context.GetFragmentView<FRecallAbilityAnimationFragment>();
		
		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); EntityIndex++)
		{
			const FRecallAbilityFragment& AbilityFragment = AbilityList[EntityIndex];			
			const FRecallActorRepresentationFragment& ActorFragment = ActorList[EntityIndex];
			const FRecallAbilityAnimationFragment& AnimationFragment = AnimationLIst[EntityIndex];
			
			const TWeakObjectPtr<ARecallPaperZDCharacterActor> Actor = ActorSystem.GetActor<ARecallPaperZDCharacterActor>(ActorFragment.ActorHandle);
			if (!Actor.IsValid())
			{
				continue;
			}

			URecallPaperZDAnimInstance* AnimInst = Actor->GetAnimInstance();
			if (!ensureAlwaysMsgf(IsValid(AnimInst), TEXT("Invalid anim instance")))
			{
				continue;
			}

			// Only update the montage once per game simulation update. 
			bool bPlayNewAnimationMontage = false;
			const int32 LastGameFrame = Frame;
			const bool bFirstTickOfAnimInst = AnimInst->LastMontageChangeGameFrame == 0;
				
			if (AnimationFragment.bPlayNewAnimationMontage && LastGameFrame > AnimInst->LastMontageChangeGameFrame)
			{
				bPlayNewAnimationMontage = true;
				AnimInst->LastMontageChangeGameFrame = LastGameFrame;
			}

			// Update animation
			if (bPlayNewAnimationMontage)
			{						
				if (UPaperZDAnimSequence* AnimationAsset = Cast<UPaperZDAnimSequence>(AnimationFragment.AnimationAsset))
				{
					AnimInst->PlayAnimSequence(AnimationAsset);
				}
			}

			{
				// Synchronize the playing animation time with the game simulation state.
				AnimInst->SynchronizeToAbilityFrame(AbilityFragment.CurrentAbility, AbilityFragment.CurrentFrameTime);
			}

			// Synchronize Animation Blending
			AnimInst->AnimBlend = AnimationFragment.AnimInstanceBlend;
			AnimInst->LocomotionBlend = AnimationFragment.AnimInstanceLocomotionBlend;

			// const bool StopAnimTick = SimulationRate <= 0 || AnimationFragment.bPauseAnimation;

			// We disable the tick only when the delta time would be 0 and there's no animation to change.
			// If we don't disable the tick the Unreal animation system will call any notify state's Begin events multiple times.
			// SkeletalMesh->EnableExternalUpdate(bPlayNewAnimationMontage || !StopAnimTick);

			// Work around for the first frame a actor is shown.
			if (bFirstTickOfAnimInst)
			{
				// AnimInst->Tick(FixedDeltaTime, false);
			}
		}
	});
}
