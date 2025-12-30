#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "Player.h"
#include "network.h"

typedef struct game {
    player_t* player;
    //Managers
    //GameScene currentScene ecc
    //general score,ui ecc
} game_t;

void GameInit(game_t *game);
void GameUpdate(game_t *game, float dt,networkingData* nData);
void GameDraw(const game_t *game);

#endif // GAME_H