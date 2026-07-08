# RecallPaper - Unreal Engine Plugin

This is the **RecallPaper** plugin, a comprehensive 2D animation integration system built on top of the Recall ECS framework, providing PaperZD and Paper2D support for deterministic multiplayer 2D games.

## About RecallPaper

RecallPaper is a specialized 2D animation system that extends the Recall ECS framework with complete PaperZD integration. It offers seamless 2D sprite animation, character representation, and visual effects for ECS entities. The plugin bridges the gap between Recall's high-performance ECS architecture and Unreal Engine's powerful 2D animation tools.

The plugin provides:

- **PaperZD Integration**: Complete integration with PaperZD animation system for ECS entities
- **2D Character System**: Specialized 2D character actors with animation instance support
- **Sprite Representation**: Efficient sprite-based visual representation for ECS entities
- **Animation Synchronization**: Frame-perfect animation synchronization with ability system
- **Actor Pool Management**: Optimized actor pooling for 2D representation performance
- **Material Override System**: Dynamic material switching for sprite customization

## Plugin Description

*Paper ZD and Paper 2D implementation for Recall*

This plugin is a **2D animation integration framework** built on top of Recall ECS framework with the following key features:
- **PaperZD Integration** for advanced 2D animation workflows
- **Paper2D Support** for sprite-based entity representation
- **Animation Instance** integration with Recall ability system
- **Actor Factory** system for efficient 2D actor creation and management
- **Representation Layer** specifically designed for 2D game development
- **Performance Optimization** for large numbers of animated 2D entities

## Origin and Development

**Based on**: Recall ECS Framework + PaperZD Animation System
**Enhanced by**: Bastien Van de Walle
**Purpose**: Complete 2D animation system for Recall ECS
**Architecture**: Modular 2D framework with PaperZD and Paper2D integration
**Inspiration**: Modern 2D games requiring high-performance animation with ECS architecture

## Core Module

### RecallPaperModule (Runtime)
**Complete 2D animation and representation system**

#### Animation System
- **Animation Instance**: `URecallPaperZDAnimInstance` - Custom PaperZD animation instance
- **Ability Integration**: Frame synchronization with Recall ability system
- **Animation Types**: Support for animation sequences, blend spaces, and montages
- **State Management**: Animation state tracking and synchronization

#### Character System
- **Character Actor**: `ARecallPaperZDCharacterActor` - Specialized 2D character representation
- **Animation Integration**: Direct integration with PaperZD animation instances
- **Material Override**: Dynamic material switching for character customization
- **Flipbook Support**: Default flipbook animation for simple characters

#### Representation System
- **Actor Types**: Character and sprite actor descriptors for entity representation
- **Actor Factory**: `URecallPaperActorFactory` - Efficient 2D actor creation system
- **Actor Pool**: `URecallPaperActorPool` - Performance-optimized actor pooling
- **Fragment System**: ECS fragments for 2D character and sprite configuration

#### Processing Systems
- **Representation Processors**: ECS processors for 2D visual representation updates
- **Actor Traits**: Trait system for configuring 2D entity representation
- **Performance Optimization**: Specialized processing for 2D animation performance

## Key Features

### Comprehensive 2D Animation Framework
- **Single Module Design**: Focused module specifically for 2D animation integration
- **ECS Integration**: Native integration with Recall ECS framework
- **Deterministic Animation**: All animation systems designed for deterministic multiplayer
- **PaperZD Support**: Full integration with PaperZD's advanced animation features
- **Performance Focus**: Optimized for large numbers of animated 2D entities

### Advanced PaperZD Integration
- **Animation Instance**: Custom animation instance class with ECS integration
- **Ability Synchronization**: Frame-perfect synchronization with ability system animations
- **Montage Support**: Support for animation montages and complex animation sequences
- **Blend Space Integration**: Support for 2D blend spaces and directional animations
- **State Tracking**: Advanced animation state tracking and management

### 2D Character System
- **Character Representation**: Specialized character actors for ECS entity representation
- **Animation Workflow**: Complete animation workflow from ECS data to visual output
- **Material System**: Dynamic material override system for character customization
- **Flipbook Fallback**: Fallback to simple flipbook animation when needed
- **Performance Optimization**: Efficient character representation with actor pooling

### Sprite System
- **Sprite Actors**: Specialized sprite actors for simple 2D entity representation
- **Paper2D Integration**: Full integration with Unreal Engine's Paper2D system
- **Static Sprites**: Support for static sprite representation
- **Dynamic Switching**: Runtime sprite switching and customization
- **Performance**: Optimized sprite representation for large entity counts

## Architecture Overview

### 2D Animation System Architecture
```
RecallPaper Framework
├── Animation System (PaperZD integration, ability sync, state management)
├── Character System (2D character actors, animation instances)
├── Sprite System (Paper2D integration, sprite actors)
├── Representation (Actor factories, pools, fragments)
└── Processing (ECS processors, traits, performance optimization)
```

### Animation Workflow
```
ECS Entity → Fragment Data → Animation Instance → PaperZD Animation → Visual Output
```

### Representation Flow
```
Entity Creation → Actor Factory → Actor Pool → Visual Representation → Animation Update
```

### Integration Flow
```
Recall ECS → RecallPaper → PaperZD/Paper2D → Visual Rendering
```

## Integration

The plugin integrates with:
- **Recall Framework**: Core ECS framework with rollback support
- **RecallGameplay**: Gameplay systems integration for 2D game mechanics
- **RecallAbility**: Ability system for synchronized 2D animations
- **PaperZD**: Advanced 2D animation system for complex character animation
- **Paper2D**: Unreal Engine's 2D sprite system for visual representation
- **VariableCollection**: Dynamic configuration and parameter management

## Key Differences from Standard 2D Systems

### ECS Integration
- **Standard Systems**: Component-based 2D animation with individual character management
- **RecallPaper**: Native ECS entity-based 2D animation processing

### Performance Architecture
- **Standard Systems**: Individual actor-based 2D character management
- **RecallPaper**: High-performance ECS processing with actor pooling

### Animation Synchronization
- **Standard Systems**: Independent animation timing and state management
- **RecallPaper**: Frame-perfect synchronization with ability system and ECS

### Multiplayer Support
- **Standard Systems**: Limited multiplayer animation consistency
- **RecallPaper**: Deterministic 2D animation designed for rollback netcode

## Configuration

### Basic Setup
1. **Enable Plugin**: Enable RecallPaper in project plugins (disabled by default)
2. **Configure Dependencies**: Ensure Recall, PaperZD, Paper2D, and other dependencies are enabled
3. **Setup Assets**: Configure character blueprints, animation instances, and sprites
4. **Initialize Systems**: Set up 2D representation systems and actor pools

### 2D Animation Configuration
1. **Character Setup**: Configure character actor blueprints with PaperZD animation instances
2. **Animation Assets**: Set up PaperZD animation sequences and blend spaces
3. **Sprite Assets**: Configure Paper2D sprites for simple entity representation
4. **Material Setup**: Configure material overrides for character customization

## Best Practices

### 2D Animation Design
- **Deterministic Logic**: Ensure all animation logic is deterministic for multiplayer
- **Performance Considerations**: Design animation systems with scalability in mind
- **Frame Synchronization**: Coordinate animation frames with ability system timing
- **State Management**: Design animation states to be fully serializable for rollback

### Character System Design
- **Actor Pooling**: Use actor pools efficiently to minimize allocation overhead
- **Animation Optimization**: Optimize animation assets for performance with large entity counts
- **Material Efficiency**: Use material instances and overrides efficiently
- **Memory Management**: Design character systems for optimal memory usage patterns

### Integration Best Practices
- **ECS Patterns**: Follow ECS patterns for fragment and processor design
- **Animation Workflow**: Establish clear workflows from ECS data to visual output
- **Performance Monitoring**: Monitor performance with large numbers of animated entities
- **Asset Organization**: Organize 2D assets for efficient loading and management

## Technical Features

### Animation System
- **PaperZD Integration**: Complete integration with PaperZD animation blueprints
- **Frame Synchronization**: Frame-perfect synchronization with ability system
- **State Management**: Comprehensive animation state tracking and persistence
- **Performance**: Optimized animation processing for ECS architecture

### Character Representation
- **Actor Factory**: Efficient character actor creation and configuration
- **Actor Pooling**: Performance-optimized actor pooling system
- **Material Override**: Dynamic material switching system
- **Animation Instance**: Custom animation instance with ECS integration

### Sprite System
- **Paper2D Integration**: Full integration with Paper2D sprite system
- **Dynamic Sprites**: Runtime sprite switching and configuration
- **Performance**: Optimized sprite rendering for large entity counts
- **Customization**: Flexible sprite customization and material override

## Module Dependencies

### Required Plugins
- **Recall**: Core ECS framework (Required)
- **RecallGameplay**: Gameplay systems integration (Required)
- **RecallAbility**: Ability system integration (Required)
- **PaperZD**: Advanced 2D animation system (Required)
- **Paper2D**: Unreal Engine's 2D sprite system (Required)
- **VariableCollection**: Dynamic configuration management (Required)

### Framework Integration
- **Actor Factory System**: Integration with Recall actor representation
- **Fragment System**: Custom fragments for 2D animation configuration
- **Processor System**: ECS processors for 2D animation updates

## Performance Characteristics

### Animation Performance
- **Entity Processing**: Optimized for hundreds or thousands of animated 2D entities
- **Frame Synchronization**: Minimal overhead for ability system synchronization
- **Animation Updates**: Efficient animation state updates and transitions
- **Memory Usage**: Optimized memory patterns for 2D animation data

### Representation Performance
- **Actor Pooling**: Efficient actor pool management for 2D characters
- **Sprite Rendering**: Optimized sprite rendering for large entity counts
- **Material Switching**: Efficient material override and customization
- **Memory Management**: Minimized memory allocation and garbage collection

### System Integration
- **ECS Performance**: Leverages ECS performance for 2D animation processing
- **Rendering Integration**: Efficient integration with Unreal Engine's rendering pipeline
- **Asset Loading**: Optimized asset loading and management for 2D content
- **Performance Scaling**: Linear performance scaling with entity complexity

## Content Integration

### 2D Animation Assets
- **Character Blueprints**: Pre-configured character actor blueprints
- **Animation Instances**: Template animation instances for common character types
- **Animation Assets**: PaperZD animation sequences and blend spaces
- **Material Templates**: Template materials and material instances

### Sprite Assets
- **Sprite Collections**: Pre-configured sprite collections for different entity types
- **Material Overrides**: Template material overrides for sprite customization
- **Performance Assets**: Optimized assets for high-performance scenarios
- **Integration Templates**: Templates for integrating with other Recall systems

## Developer Notes

- **Author**: Bastien Van de Walle
- **Category**: Gameplay
- **Version**: 1.0
- **Default State**: Disabled by default (opt-in for 2D game projects)
- **Content Support**: Enabled for 2D animation assets and character blueprints
- **Framework**: Built on Recall ECS with comprehensive PaperZD integration
- **Inspiration**: Modern 2D games requiring high-performance animation systems

## Extension Points

The plugin provides extension points for:
- **Custom Animation Instances**: Implement specialized animation instances for unique character types
- **Custom Character Actors**: Create custom character actors with specialized functionality
- **Custom Sprite Systems**: Extend sprite system with custom rendering and effects
- **Custom Materials**: Implement specialized materials for 2D character rendering
- **Custom Processors**: Create custom ECS processors for specialized 2D animation needs

## Advanced Features

### Animation Features
- **Montage System**: Support for complex animation montages and sequences
- **Blend Space Integration**: Multi-dimensional blend spaces for directional animation
- **Animation Notifications**: Event system for animation-driven gameplay events
- **State Machines**: Integration with PaperZD state machines for complex behavior

### Character Features
- **Layered Animation**: Support for layered animation systems and bone hierarchies
- **Dynamic Materials**: Runtime material generation and customization
- **LOD System**: Level-of-detail system for animation optimization
- **Culling Integration**: Integration with Unreal Engine's culling systems

### Performance Features
- **Batch Processing**: Batch processing for animation updates and state changes
- **Instanced Rendering**: Support for instanced rendering of similar sprites
- **Occlusion Culling**: Integration with occlusion culling for performance
- **Memory Pooling**: Advanced memory pooling for animation data

## Testing Framework

### Automated Testing
- **Unit Tests**: Comprehensive unit tests for all 2D animation systems
- **Integration Tests**: Integration tests between ECS and animation systems
- **Performance Tests**: Performance testing for large numbers of animated entities
- **Animation Tests**: Automated testing of animation synchronization and state management

### Development Testing
- **Debug Visualization**: Visual debugging for animation states and synchronization
- **Test Scenarios**: Comprehensive test scenarios for 2D animation workflows
- **Performance Profiling**: Built-in profiling for animation system performance
- **Asset Validation**: Automated validation of 2D animation assets

## Use Cases

### Game Development
- **2D Platformers**: High-performance 2D platformer games with complex animation
- **2D Fighting Games**: Fighting games requiring frame-perfect animation timing
- **2D RPGs**: RPG games with character animation and visual effects
- **2D Puzzle Games**: Puzzle games with animated sprites and visual feedback

### System Integration
- **Existing Projects**: Integration with existing Unreal Engine 2D projects
- **Custom Animation**: Platform for custom 2D animation and visual systems
- **Educational**: Educational games with 2D character animation
- **Simulation**: 2D simulation applications with animated visual representation

## Credits

- **Framework Foundation**: Recall ECS Framework + PaperZD Animation System
- **Implementation**: Bastien Van de Walle - Comprehensive 2D animation integration
- **ECS Integration**: Native integration with Recall deterministic framework
- **Animation Design**: Advanced 2D animation systems with PaperZD integration
- **Performance Optimization**: High-performance 2D animation for ECS architecture