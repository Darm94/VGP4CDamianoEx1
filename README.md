Raylib Test project - simple white window
To create exe, use 
```
clang -o .\bin\test.exe .\src\*.c -Iinclude -L.\library -lraylibdll
```
and execute with
```
./bin/test.exe  
```  

In the following project, the main difference from the original version shown in class is the use of the **`game_t`** type and the **`game.c` / `game.h`** units, which allow grouping the various **Init**, **Update**, and **Draw** operations into specific functions that can be cleanly called from `main`.

In addition, I created my own version of a **configurable input system**, where during declaration each player is assigned a **`moveMode`**. This allows the `Update` function to update that player’s direction in different ways (for now, only through keyboard input or random movement).

In this `main` file, two identical players are declared, but with different **`moveMode`** values and different colors:

- **Red**: `moveMode == RANDOM` (random direction movement)  
- **Green**: `moveMode == KEYBOARD1` (keyboard arrows input to move)

To make this code more flexible, one could declare a single array with a predefined number of players — or a number set through `argv` — and also include in the player struct a function pointer corresponding to the direction-update function.

This way, an alternative approach would be to use `moveMode` only for the initial configuration, using a `switch`–`case` to set the color and the associated direction-update function based on the selected mode.
For now, I plan to explore this topic further during class, but in a future update I may create a new version with one or more **manager functions** for the player or other types.
