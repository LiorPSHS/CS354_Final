================================================================================
CS 354: Final Report -- Sector Based Terrain Generation
================================================================================
Programmed By: Joseph Bourque, Joel Davis, and Lior Vansteenkiste
--------------------------------------------------------------------------------
BUILD INSTRUCTIONS
1. Unzip zip archive
2. In the root directory of the project do mkdir build
3. cd build
4. cmake ..
5. make -j8
6. run bin/dsquare

CONTROLS
--------------------------------------------------------------------------------
C - Change from Orbital to FPS Mode
A - FPS Pan Left, Orbital Swivel Left
D - FPS Pan Right, Oribtal Swivel Right
W - Zoom In
S - Zoom Out
UP - FPS Pan Up, Orbital Swivel Up
DOWN - FPS Pan Down, Orbital Swivel Down
LEFT - Roll Left
RIGHT - Roll Right
MOUSE LEFT - FPS Drag and Pan, Orbital Rotate
MOUSE RIGHT - Drag and Zoom
1 - Flat terrain map: no water, textures, or temperature
2 - Flat map, display map as a flat plane
3 - Cube map, display map as a cubic contour map
4 - Display smooth shaded map
9 - Regenerate Map
t - Switch between texture and temperature display mode
o - Toggle overlay

WORK BREAKDOWN
o Diamond Square Algorithm-------------------------COMPLETED - J BOURQUE
o Trimesh Silhouette-------------------------------COMPLETED - J DAVIS
o Phong Shading------------------------------------COMPLETED - J BOURQUE
o Smooth Shading for Trimesh ----------------------COMPLETED - J DAVIS
o Trimesh Expansion (Sides + Bottom of map)--------COMPLETED - J DAVIS
o Surface Subdivsion + Expansion ------------------COMPLETED - L VANSTEENKISTE
o QA + Code Cleanup -------------------------------COMPLETED - L VANSTEENKISTE

BELLS AND WHISTLES + EXTRAS
o Texture Mapping ---------------------------------COMPLETED - J BOURQUE
o Water Shading------------------------------------COMPLETED - J BOURQUE