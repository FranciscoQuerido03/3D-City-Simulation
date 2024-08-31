# 3D City Simulation

This project simulates a 3D cityscape with buildings, a "T"-shaped structure, cars, and dynamic lighting. It uses OpenFrameworks for rendering and interaction.

## Features

- **City Layout**: Generates a grid of buildings with random colors and sizes.
- **T-Shaped Structure**: A T-shaped structure with a rotating horizontal part.
- **Car Movement**: Cars with adjustable speed moving within the city.
- **Lighting**: Multiple types of lights including directional, point, and spotlight with configurable attributes.
- **Textures and Materials**: Various textures for buildings, ground, and skybox; customizable materials.

## Controls

- **1-4**: Toggle different lights.
- **a**: Toggle ambient light.
- **d**: Toggle diffuse light.
- **s**: Toggle specular light.
- **g**: Switch to wireframe mode.
- **f**: Switch to filled mode.
- **v**: Change the camera view.
- **Arrow Keys**: Move the camera.
- **Shift/Control**: Adjust the lens angle.
- **r**: Reset the camera position.

## Key Components

- **Buildings**: Represented by a grid with varying sizes and textures. One building is a pyramid with a specific texture and material.
- **T-Shaped Structure**: Consists of a vertical and a rotating horizontal part with specific textures and materials.
- **Cars**: Animated with adjustable speeds.
- **Lighting**: Includes directional, point, and spotlights with different settings.

## Textures and Materials

- **Textures**:
  - `skybox.jpg`: Skybox texture.
  - `tVertical.jpg`: Texture for the vertical part of the T structure.
  - `tHorizontal.jpg`: Texture for the horizontal part of the T structure.
  - `estrada.jpg`: Ground texture.
  - `piramide.png`: Pyramid texture.
  - `opt1.jpg`, `opt2.jpg`, `opt3.jpg`, `opt4.jpg`: Building textures.

- **Materials**:
  - **Pyramid material**: Ambient, diffuse, and specular properties defined.
  - **Building material**: Customizable ambient, diffuse, and specular properties.
  - **Ground material**: Specific material properties for the ground.
  - **T-Structure material**: Light gray material for the T-shaped structure.
