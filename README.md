# RecallPaper

PaperZD and Paper2D integration for the Recall ECS framework — 2D sprite/character animation for deterministic, rollback-based multiplayer.

## Overview

RecallPaper bridges Recall's ECS entities with PaperZD's animation system, so 2D characters and sprites can be driven from ECS fragments and processors while staying frame-synchronized with the ability system.

## Module

### RecallPaperModule (Runtime)

- **`URecallPaperZDAnimInstance`** — custom PaperZD animation instance driven by ECS/ability state
- **`ARecallPaperZDCharacterActor`** — 2D character actor with animation instance and material override support, flipbook fallback
- **`URecallPaperActorFactory`** / **`URecallPaperActorPool`** — actor creation and pooling for 2D representation
- **`RecallPaperActorTypes`** — character/sprite actor descriptors
- Processors and traits (`RecallPaperProcessors`, `RecallPaperActorTraits`) driving representation updates from ECS fragments

## Dependencies

- Recall
- RecallGameplay
- RecallAbility
- PaperZD
- VariableCollection

## Setup

1. Enable the plugin (disabled by default).
2. Enable PaperZD and the Recall dependency plugins.
3. Configure character blueprints with a `URecallPaperZDAnimInstance` and PaperZD animation assets.

## Notes

- Author: Bastien Van de Walle
- Category: Gameplay
- Disabled by default; opt in per project