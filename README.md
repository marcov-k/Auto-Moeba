# Auto-Moeba
A small particle life simulation based around asymmetric Newtonian-style physics interactions between various types of particles. Built using C++ and Raylib.
## Core Features
- Various particle types with unique interactions
- Random mutation system for offspring behaviour
- Custom-coded physics and collision system
- Camera control system
- Particle spawning via mouse clicks
- Hand-made UI system
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
## Future Plans
- Save system and file format for saving simulation states
- Additional particle types
- More advanced particle behaviors
- More complex mutations
- Improved performance and stability
