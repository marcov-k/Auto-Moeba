# Auto-Moeba
A small particle life simulation based around asymmetric Newtonian-style physics interactions between various types of particles. Built using C++ and Raylib.

## Core Features
- Various particle types with unique interactions
- Random mutation system for offspring behaviour
- Custom-coded physics and collision system
- Camera control system
- Particle spawning via mouse clicks
- Hand-made UI system
- Custom file format for saving and loading simulation states

## Motivation
I decided to create Auto-Moeba as a way of learning more about using C++, in particular its inheritance and polymorphism systems. I was vaguely inspired by Conway's Game of Life, as well as other cellular automata projects 
I have seen over the years. To get more exposure to coding C++, I opted to use Raylib for rendering, rather than a more advanced physics and/or game engine. The simulation is very much still in development, with various 
new particle types and interactions being planned.

## Current Particles
- Predator - Chases down and consumes Prey, Membranes, and Nuclei to survive and reproduce - leaves behind Waste
- Prey - Afraid of Predators - consumes Food to survive and reproduce
- Scavenger - Consumes Waste left by other particles to survive and reproduce - leaves behind Nutrients
- Membrane - Attracted to other Membranes and Nuclei - consumes food to survive and reproduce
- Nucleus - Strongly attracted to other Nuclei - consumes food to survive and reproduce
- Connector - Weakly attracts and is attracted to every particle type - consumes food to survive and reproduce
- Food - Inert by default - can gain behaviour through random mutations - consumed by certain other particle types
- Waste - Inert by default - can gain behaviour through random mutations - created as a byproduct of particle deaths - consumed by Scavengers
- Nutrients - Always inert - created as a byproduct of particle deaths and by Scavengers - becomes Food after a fixed amount of time

## File Format (.moeba)
### General Formatting Notes:
- All multi-byte numbers use little-endian encoding
- Many particle types encode additional data after the general particle data
- Data appears in the file in the exact order as listed below

### File Header Format:
- Magic number - int32 (4 bytes) - 1094996045 (spells "MEBA" in ASCII)
- Camera position - Vector2 ([see formatting](#vector2-format)) - position of the camera at the time of the save
- Particle count - uint64 (8 bytes) - total number of particles in the file

### Particle Data Format:
- Particle ID - uint16 (2 bytes) - ID of the particle's type ([see ID list](#particle-type-specific-data))
- Position - Vector2 ([see formatting](#vector2-format)) - position of the particle at the time of the save
- Attraction values - Unordered Map ([see formatting](#attraction-map-format)) - particle type attraction matrix of the particle
- Health - float (4 bytes) - health of the particle at the time of the save
- Any [type-specific data](#particle-type-specific-data) required by the particle's specific type

### Particle Type-Specific Data:
  - #### Predator (ID = 0):
      - Current eaten prey - int32 (4 bytes) - number of Prey the particle has consumed at the time of the save
      
  - #### Prey (ID = 1):
      - Current eaten food - int32 (4 bytes) - number of Food the particle has consumed at the time of the save
        
  - #### Scavenger (ID = 2):
      - Current eaten waste - int32 (4 bytes) - number of Waste the particle has consumed at the time of the save
        
  - #### Membrane (ID = 3):
      - Current eaten food - int32 (4 bytes) - number of Food the particle has consumed at the time of the save
        
  - #### Nucleus (ID = 4):
      - Current eaten food - int32 (4 bytes) - number of Food the particle has consumed at the time of the save
        
  - #### Connector (ID = 5):
      - Current eaten food - int32 (4 bytes) - number of Food the particle has consumed at the time of the save
        
  - #### Food (ID = 6):
      - No additional data
        
  - #### Waste (ID = 7):
      - No additional data
        
  - #### Nutrients (ID = 8):
      - Current growth - float (4 bytes) - growth progress of the particle at the time of the save
        
### Vector2 Format:
- X - float (4 bytes) - X component of the vector
- Y - float (4 bytes) - Y component of the vector
  
### Attraction Map Format:
- Entry count - uint64 (8 bytes) - total number of ParticleType-Attraction pairs in the map
- Entry - (int32 (4 bytes), float (4 bytes)) - underlying int32 representation of the ParticleType enum entry and the corresponding attraction value
  
## Future Plans
- Additional particle types
- More advanced particle behaviors
- More complex mutations
- Improved performance and stability
