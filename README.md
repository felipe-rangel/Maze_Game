# Maze_Game
C++ Maze Game
Background/Setup:
  The Maze Game was originally programmed using Microsoft Visual Studio 2010 and a graphics library (library.h and libary.obj) provided at University of Miami's ECE 118 Introduction to Programming class. I created the code for the maze game in the span of a month at the end of the Fall semester 2019. The main code spans over 600 lines where it covers all elements relating to properly drawing the maze from the input text file to the semi-intellignce mode of the player/enemy. The input text file contains two different characers in '#', and ' ' which mean a wall, and a movable space respectively. The goal of the game is for the player to get to the treasure before the enemy. The player, treasure, and enemy will be randomly spawned into the map when the game starts.
Gameplay:
  When the game starts up, the user will be asked if they wish to either play the easy or hard difficulty mode. In easy mode the enemy does not have semi-intelligence and simply moves around randomly. In hard mode, the enemy has semi-intelligence meaning that it will not backtrack to places it's already been to and if it finds the treasure it will stand guard next to it. There is also an automatic mode where the player searches for the treasure on it's own also in semi-intellignence mode and will win the game if it finds the treasure.
  Take a look at the sample recordings for example gameplay of the game in easy and hard mode in their respective manual and auto modes.
