#ifndef Player_H
#define Player_H
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

//enum for movement update, thats enought clean in my opinion
typedef enum moveMode {
    KEYBOARD1,
    RANDOM
    //KEYBOARD2,ENEMY AI ecc
} moveMode_t;


//advanced alternative: define directly the direction update function here instead of define a mod
typedef struct player_t
{
    Vector2 position;
    Color PlayerColor;
    Vector2 direction;
    float radius;
    float speed;
    moveMode_t moveMode;
}player_t;

player_t* Player_Factory(moveMode_t moveMode,Color color);

void UpdateMoveByInput(player_t* player);
void UpdateMoveByRand(player_t* player);
void DrawPlayer(player_t* player);

void UpdatePlayer(player_t* player);

#endif// PLAYER_H