# Shoot-the-Birds-Game
A simple 2D game built with SDL2 where you aim to shoot birds. Click on the birds to make them angry, and click again to calm them down and reset their position. The game features interactive gameplay, dynamic movement, and basic graphics rendering.

Features
- Interactive Gameplay: Engage with birds by clicking on them.
- Dynamic Movement: Angry birds move around the screen and bounce off edges.
- Simple Graphics: Utilizes SDL2 for rendering images and text.
- Event Handling: Responds to mouse clicks and window events.

# Prerequisites
Ensure you have the following libraries installed:
- SDL2
- SDL2_image
- SDL2_ttf

# How to Play
Objective: Click on the birds to interact with them.
- Controls:
  - Left Mouse Click: Shoot at the bird.
- Gameplay:
  - When you click on a stationary bird, it becomes angry and starts moving.
  - Click on the angry bird to calm it down and reset its position.
  - The angry bird moves around the screen and bounces off the window edges.
- Goal: Keep interacting with the birds for fun gameplay.
# Code Overview
main.cpp: The main game loop handling initialization, event processing, and rendering.
Assets:
- image/duck_web.png: Image for the normal bird.
- image/white-46066_1280.png: Image for the angry bird.
- image/bang-148261_1280.png: Image for the explosion effect when you click.
- Fonts/FreeSansBold.ttf: Font used for rendering text.

# Dependencies
- C++11 or higher
- SDL2
- SDL2_image
- SDL2_ttf
