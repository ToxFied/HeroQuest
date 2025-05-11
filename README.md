# HeroQuest Console/Terminal Game

## Overview

This project is a console-based adaptation of the classic board game *HeroQuest*. The game blends adventure, fantasy, and role-playing elements to offer players a dynamic turn-based experience. In this version, players guide a team of heroes through a dungeon-like grid full of enemies, obstacles, and treasures, with the ultimate goal of clearing levels and overcoming increasingly challenging battles.

## How to Play

- **Game Setup:**  
  - The game begins with a single room (grid) that serves as the starting level.  
  - The grid dimensions, number of enemies, and difficulty are determined based on the selected difficulty:
    - **Easy:** Up to 2 enemies per room with 1–3 life points each.
    - **Medium:** Up to 4 enemies per room with 4–6 life points each.
    - **Hard:** Up to 6 enemies per room with 7–9 life points each.
  - At least one obstacle (e.g., a piece of furniture) is always present on each room.

- **Heroes and Enemies:**  
  - Players choose which heroes will participate at the beginning. The available hero classes are:
    - **Barbarian:** Starts with 8 life points.
    - **Dwarf:** Starts with 7 life points.
    - **Elf:** Starts with 6 life points.
    - **Wizard:** Starts with 4 life points.
  - Enemies are represented by numbers corresponding to their remaining life points.

- **Game Mechanics:**  
  - The game is played in turns. On the player's turn, they can perform movement and attack commands for each hero:
    - **Movement:** Heroes are moved across the grid following specific command formats. They cannot move through walls, obstacles, or enemies.
    - **Attack:** Heroes attack enemies by rolling combat dice (skulls for hitting, shields for defending). Each hero has unique attack abilities based on their class.
  - On the computer’s turn (playing as the evil wizard Zargon), enemies are moved toward heroes or attack if adjacent.
  - When all enemies in a room are defeated, the game automatically moves the player to the next level, where the grid increases in size and difficulty.

- **Commands:**  
  - **Move:** Example – `B>L3U2` (move Barbarian 3 spaces left and 2 spaces up).
  - **Attack:** Example – `D>A*D2` (Dwarf attacks enemy located in cell D2).
  - **Create/Destroy Enemy:** Allows placement or elimination of an enemy on a specified grid cell.
  - **End Turn/Quit Game:** Players can signal the end of their turn or quit the game.

## Authors

This project was developed as a part of the Programming II course by two first-year students:
- **Anestis Archontopoulos**
- **Nikolas Potaris**

Each contributed to the coding, design, and testing phases of the project, ensuring that all functionalities, such as grid generation, pathfinding, and turn-based gameplay, meet the project requirements.

---


Good luck and have fun!


![lol](https://github.com/user-attachments/assets/7f058792-bdd2-45f6-955f-a053f9f4cb85)



* * 
* * 
* * 
* * 
* * 
* * 
* * 


[![In the End - Linkin Park](https://img.youtube.com/vi/eVTXPUF4Oz4/0.jpg)](https://www.youtube.com/watch?v=eVTXPUF4Oz4)

*I tried so hard*  
*And got so far*  
*But in the end*  
*It doesn't even matter*  
*I had to fall*  
*To lose it all*  
*But in the end*  
*It doesn't even matter*


