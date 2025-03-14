# ExMORTALIS

## Project Overview
**ExMORTALIS** is an atmospheric first-person action RPG set in a Gothic 1890s-style Argentinian town called **Las Tormentas**. The game centers around **El Dedo del Diablo**, a towering dungeon where the player must ascend through procedurally generated biomes to uncover the dark secrets of the **Necrotechs**, enigmatic scientists obsessed with immortality. The player's choices shape the world, the townsfolk, and their ultimate fate.

## 🚧 Current Development Status
This project is currently in active development by Necrotek Labs. Major systems are under construction with a target to reach a playable state by the end of the year.

### Implemented Features
- Custom Entity Component System (ECS) integrated with Unreal Engine
- First-person character controller with:
  - Walking, sprinting, and crouching
  - Leaning and vaulting mechanics
  - Jump and fall damage systems
- Attribute system (Strength, Dexterity, Intelligence)
- Basic buff/status effect framework
- Input handling with Enhanced Input System
- Initial weapon and projectile framework
- Entity creation and management systems

### In Development
- Combat system completion
- Enemy AI and behavior systems
- Procedural dungeon generation
- Tower biome implementations
- Narrative elements and quest system
- World state persistence

## Technology Stack
- **Engine**: Unreal Engine 5
- **Language**: C++
- **Architecture**: Custom Entity Component System alongside Unreal's component system
- **Input**: Enhanced Input System
- **Build System**: UnrealBuildTool

## Getting Started

### Prerequisites
- Unreal Engine 5.5+
- Visual Studio 2022 or other compatible IDE
- Git LFS for asset management

### Building the Project
1. Clone the repository: `git clone https://github.com/necroteklabs/exmortalis.git`
2. Right-click the `.uproject` file and select "Generate Visual Studio project files"
3. Open the generated solution file
4. Build the solution in Development or Debug configuration
5. Launch the project through the Unreal Editor

## Project Architecture

### Core Systems

#### Entity Component System
ExMORTALIS uses a custom ECS architecture that works alongside Unreal's native component system. Key elements include:

- `EntityContainer`: Manages all entities and their components
- `EntityComponent`: Base structure for all components
- `EntityConfig`: Data asset for entity configuration
- `SystemBase`: Base class for all systems that process entities

#### Player Systems
- `ExMCharacter`: First-person character implementation
- `PlayerMovementSystem`: Handles movement, stance, and physics interactions
- `ExmStatsComponent`: Manages character attributes and derived stats

#### Combat Framework
- `WeaponSystem`: Manages weapon behavior and firing
- `DamageSystem`: Processes damage events and calculations
- `ExMResistancesComponent`: Handles damage mitigation

#### Buff System
- `BuffableComponent`: Allows entities to receive buffs and status effects
- `BuffComponent`: Manages active buffs
- `FBuffableFloat`/`FBuffableInt`: Attribute values that can be modified by buffs

### Project Structure
- `ExM/Source/ExM`: Main game code
  - `ExMCore`: Core systems and implementations
    - `Components`: Game component implementations
    - `Configs`: Data configurations
    - `Core`: ECS implementation
    - `Systems`: Game systems
    - `Utils`: Utility functions
- `EntityConfigEditor`: Editor extensions for entity configuration

## Development Roadmap

### Phase 1: Core Gameplay (Current Focus)
- Complete the combat system implementation
- Develop full damage calculation pipeline
- Implement basic enemy AI

### Phase 2: World & Environment
- Implement procedural generation for the first biome
- Create safe room mechanics
- Develop world interaction systems

### Phase 3: Progression & Polish
- Add basic narrative implementation
- Create progression systems
- Balance and refine gameplay loop

## License
© 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited.

## Contact
For inquiries, please contact moisespirela96@gmail.com