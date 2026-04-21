# TankShoot

TankShoot is a 2D boss-fight shooter built with C++ and SFML. I developed this project as part of a team assignment, and this repository is my personal portfolio version of the project, highlighting the areas I contributed most heavily to, especially the gameplay foundation, combat flow, state management, and overall game structure.

For CV and portfolio purposes, this project represents my ability to design and implement a complete desktop game in modern C++, work with real-time update loops, structure a multi-screen application, and deliver a playable product with graphics, audio, UI, collision handling, and boss mechanics.

## Project Summary

- Language: `C++17`
- Framework: `SFML`
- Platform: `Windows`
- IDE: `Visual Studio 2022`
- Genre: `2D shooter / boss battle`
- Resolution: `1280 x 720`

## My Role

I am `Cao Hai Vy`, and I was the primary contributor to this project.

Based on the implementation in this repository and the task allocation described in the original report, the areas I mainly drove include:

- Core project structure and game initialization
- Game configuration and foundational engine code
- State-based screen flow for intro, menu, play, pause, settings, about, and end screens
- Main gameplay loop and combat interactions
- Player behavior, cooldown logic, skill system, and survivability mechanics
- Enemy spawning flow and boss encounter structure
- Resource loading and asset-based game assembly
- UI feedback such as HP and skill cooldown display
- Audio integration for sound effects, music, and combat feedback

In practice, this means I handled most of the systems that made the game actually playable end-to-end, from application flow to the in-game combat experience.

## What This Project Demonstrates

This project showcases my ability to:

- Build a real-time game loop in C++
- Apply object-oriented design to gameplay systems
- Organize a project into reusable modules and game states
- Manage textures, fonts, audio, and scene-specific assets
- Implement collision detection and event-driven combat logic
- Design enemy patterns and a multi-phase boss fight
- Translate a team project into a polished, portfolio-ready codebase

## Gameplay

The player controls a tank at the bottom of the screen, moves horizontally, shoots upward, survives enemy waves, and eventually defeats the final boss `AirCraft`.

Main enemy types:

- `MineTrap`: falls downward and damages the player on contact
- `TankEnemy`: standard enemy tank that moves down and fires bullets
- `Plane`: moves horizontally and attacks from above
- `ArmoredTank`: heavier enemy with more health and more durable behavior
- `AirCraft`: the final boss with `150 HP`, multiple attack patterns, and escalation behavior

The boss fight includes:

- Single-shot attacks
- Triple-shot attacks
- Laser attacks with a warning phase
- Additional enemy spawns when the boss reaches low HP

The player wins when the boss is destroyed and loses when HP reaches `0`.

## Controls

- `Left` / `Right`: move
- `Space` or left mouse button: normal shot
- `Enter` or right mouse button: special skill
- `Esc` or the pause button: pause the game

## Technical Features

- State machine driven screen management
- Player HP and temporary invincibility after taking damage
- Skill cooldown system with UI feedback
- Dynamic enemy spawning
- Boss battle with staged attack behavior
- Bullet-vs-enemy, enemy-vs-player, bullet-vs-player, and bullet-vs-bullet collision handling
- Sound effects and background music integration
- Texture and font resource management
- Menu, settings, about, pause, and end-game screens

## Architecture

```text
TankShoot/
|-- Configuration/        # Game constants and tuning values
|-- CoreEngine/           # Application, base state, state machine
|-- GameObject/           # Player, enemies, bullets, spawner, boss
|-- GameState/            # Intro, menu, play, pause, setting, about, end
|-- ResourceManagement/   # Texture, font, sound, UI management
|-- Utility/              # Collision, buttons, explosion effects, singletons
```

Key modules:

- `Application`: creates the window, runs the main loop, updates and renders the active state
- `GameStateMachine`: manages state transitions across the game
- `GSPlay`: central gameplay state containing player, enemies, bullets, explosions, UI, and combat flow
- `Player`: movement, shooting, skill usage, damage, invincibility, and HP logic
- `Spawner`: initial and continuous enemy spawning
- `CollisionManager`: combat collision rules
- `ResourceManager`: texture and font loading
- `SoundManager`: sound effect and music playback

## Why I Include This In My CV

This project is a strong representation of my hands-on software engineering skills in an interactive application context. It shows that I can:

- Own a feature-heavy project beyond simple coursework exercises
- Work across architecture, gameplay logic, UI, and asset integration
- Build systems that interact cleanly instead of writing isolated code only
- Ship a complete user-facing product with multiple screens and gameplay states

It also reflects practical skills that transfer well to broader software roles:

- modular design
- debugging and iteration
- event handling
- state management
- system integration
- maintainable C++ code organization

## Build and Run

### Option 1: Run the existing build

You can run:

```text
Debug/TankShoot.exe
```

Make sure the `Data/` folder remains in the expected relative location so textures, fonts, music, and sound effects load correctly.

### Option 2: Build with Visual Studio

1. Open `TankShoot.sln` in `Visual Studio 2022`
2. Select a build configuration, preferably `Debug | x64`
3. Build the solution
4. Run the `TankShoot` project

## Requirements

- Windows
- Visual Studio 2022
- MSVC toolset `v143`
- SFML

This repository already includes the `SFML/` directory and the project references needed to run the game in the current setup.

## Assets and Resources

- `Data/Texture`: sprites, UI icons, backgrounds, bullets, boss visuals
- `Data/Sound`: sound effects
- `Data/Music`: background music
- `Data/Font`: in-game fonts

## Team Context

This project was originally developed by team `Nine`:

- Cao Hai Vy
- Nguyen Lam Thao Trang
- Nguyen Cao Tri
- Nguyen Son Truong

For this personal repository, I present the project from my own contribution perspective, with emphasis on the systems and implementation areas I mainly owned.

## Core Files

- Solution: `TankShoot.sln`
- Entry point: `TankShoot/TankShoot.cpp`
- Main gameplay state: `TankShoot/GameState/GSPlay.cpp`
- Game configuration: `TankShoot/Configuration/GameConfig.h`

