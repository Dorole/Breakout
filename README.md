# Breakout
 
A take on the classic Breakout game, with three levels and a possibility to choose between a summer and a winter theme.<br>
Developed with C++ and [SFML library](https://www.sfml-dev.org/). <br>
Levels and assets are defined in XML files. To parse them I used [pugixml](https://pugixml.org/).<br>

Control the platform at the bottom of the screen to make the ball bounce off in the intended direction.<br>
Destroy all the bricks on the screen to clear the level.<br>
The first level contains only "soft" bricks - hit them once to destroy them.
The second level contains "soft" and "medium" bricks - hit the medium bricks twice to destroy them.
The third level has the addition of the "hard" (take three hits before they're destroyed) and "impenetrable" (cannot be destroyed) bricks.

Press ESC to pause.<br>
Cheat codes: 
* Ctrl + Alt + C to trigger Level Clear.
* Ctr + Alt + G to trigger Game Over.

! Theme cannot be changed mid-game. To try a different theme, you need to exit the game and run it again.

_Theme selection screen:_
![image](https://github.com/user-attachments/assets/5fb80ab0-914b-4dbd-8099-44a7b1bfa0bb)

_Main Menu - summer theme:_
![image](https://github.com/user-attachments/assets/fcee2239-a189-457c-a3c4-52dc3d5cecd5)

_Main Menu - winter theme:_
![image](https://github.com/user-attachments/assets/6a141b6a-fed4-44ed-9dc3-23ce9d926413)

_Level 1 - summer theme:_
![image](https://github.com/user-attachments/assets/c338cf7a-bb3a-47b4-a746-c990a78311c2)

_Level 3 - winter theme:_
![image](https://github.com/user-attachments/assets/7024eb5c-1b07-4ade-a7c0-cec94e2f5caf)

_Game Over screen - summer theme:_
![image](https://github.com/user-attachments/assets/fbdfd88a-9c67-44f6-a7cc-b1ae8d392e3d)

_Level Clear screen - winter theme:_
![image](https://github.com/user-attachments/assets/42dce9f0-c042-4c6e-8bed-6a7dff81c498)
