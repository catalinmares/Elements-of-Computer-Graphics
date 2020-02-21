# Elements of Computer Graphics

This repository contains a framework which I used for implementing 3 projects in OpenGL C++.

**1. Flappy Bird**

The approach I used in realizing this implementation was the
following:
* I place the bird on the left side of the scene at height equal to half of the
resolution on Oy of the scene
* I calculate how many obstacles I can render at the same time on the screen
  based on the obstacles width (100), the offset between obstacles on Ox (300)
  * those are values I chose - and the resolution of the screen (resolution.x)
* Initially, before the game starts, I place the obstacles out of the scene,
  on the right, keeping the said distance between them
* When the first SPACE key is pressed, the game starts: the bird starts falling
  and the obstacles start moving towards the bird; this is done by making use
  of the Update function parameter deltaTimeSeconds, which allowed me to make
  the bird and the obstacles move constantly.
* In the Update function, I calculate the vertices positions for the bird and
  the obstacles and for each Update call, those vertices are calculated and
  I check whether the bird got off the map or collided with one of the obstacles.
* If the game is running (gameOn == true), I constantly translate the obstacles
  towards the bird. If one obstacle has got out of the map through the left side,
  I move it back to the right side to start over. I also calculate new scale 
  factors so that each obstacle which comes from the right seems different from
  the previous ones. Theese scale factors are random and they change every time
  an obstacle gets out by the left side and must start over from the right side.
* For the movement of the bird I used a variable called birdDirection; it has
  the value -1 unless the SPACE key is pressed; for birdDirection = 1, the bird
  will be translated upper and will face the ceiling, while for
  birdDirection = -1, the bird will be translated lower and will face the floor.
* After each action in the game, I check if there is a collision between the 
  bird and any of the obstacles. I do this by iterating through each obstacle
  and checking if any of the vertices of the bird is inside any of the obstacles.
* What I also check is whether the bird gets out of the map, simply by checking
  if any vertex has the y value negative or higher than the screen height.
* If a collision is detected or the bird got out the map, a "GAME OVER!" message
  is displayed, along with the final score; I also print the score with a
  frequency of 5 points.


**2. Plane with engine**

In this homework I implemented a plane which travels above the sea, avoiding
obstacles and collecting fuel cans for refilling the fuel bar. Apart from the
basic implementation requested by this homework, I implemented a custom plane
movement for going left and right, beside up and down. What I also did is I
implemented a reload button which, when pressed, resets the game to its initial
state.


**3. Worms 3D**

In this homework I implemented a brief simulation of the game Worms 3D. For this
I made use of a texture and its heightmap to create the terrain. I found on the
Internet a model of the worm from the classic game and I used it. I couldn't
manage to import it properly with its textures. I implemented the projectile
shooting with its camera of observation. I also implemented a third-person
camera for both players and spotlights on top of each player.
