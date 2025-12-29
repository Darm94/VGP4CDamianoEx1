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

-----
UPDATE
Implemented a new approach would be to use `moveMode` only for the initial configuration, using a `switch`–`case` to set the color and the associated direction-update function based on the selected mode.

-----
 # NETWORK MOD BRANCH
# Networking System – Summary of Modifications

## Goal
The goal of this work was to implement a simple UDP-based client–server networking system to synchronize player positions in real time, keeping the implementation minimal, readable, and easy to debug.

---

## Main Changes

### 1. Client Identification
Each client is identified on the server side using its UDP address (IP and port).  
When a new client connects, the server assigns it an internal **client index**, which is used as a lightweight identifier.

---

### 2. Server-side Position Updates
When the server receives a message of the form:
```  
UDP:x,y
```
it:
- parses the position data
- updates the internal position of the sending client
- rebuilds the message including the client identifier:

```
UDP:id,x,y
```
This allows all clients to know which player sent the update.

---

### 3. Broadcasting Player Data
After updating the position, the server broadcasts the message to **all other active clients**, excluding the sender.  
This ensures that each client only receives information about the other players.

The communication is handled entirely via **UDP**.

---

### 4. Client-side Parsing
On the client side, incoming messages are handled in a dedicated receiving thread.  
When a `UDP:id,x,y` message is received, the client:
- parses the player ID and coordinates
- ignores updates referring to itself
- prints the received positions in a clean and readable format

Example output:
```
[PLAYER n. 2] x = 123.50 y = 339.19
```
---

### 5. Output Readability Improvements
To improve clarity and debugging:
- floating-point values are formatted with a fixed number of decimals
- values are formatted in two digit format with the output (`%.2f`, `%.2f`)
- unnecessary per-frame/time debug prints were removed

---

## Notes:
- The networking protocol implementation is intentionally simple to make debugging easier
- The system is designed as a foundation for future graphical synchronization of remote players
- All communication is performed using UDP 
