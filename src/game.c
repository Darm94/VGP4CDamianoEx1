
#include "game.h"
#include <stdlib.h>
#define CLEAR RAYWHITE
#define PLAYER_AI_COLOR RED

//very semplified way: not using a player-t collection for now but a global variable for a single other player
player_t* playerAI=NULL;

void GameInit(game_t *game)
{
    game->player = Player_Factory(KEYBOARD1,(Color){0,255,0,255});
    playerAI = Player_Factory(RANDOM,PLAYER_AI_COLOR);
}

void GameUpdate(game_t *game, float dt)
{
        //UpdateMoveByInput(game->player);
        //UpdateMoveByRand(playerAI);
        UpdatePlayer(game->player,dt);
        UpdatePlayer(playerAI,dt);        
}

void GameDraw(const game_t *game)
{
        BeginDrawing();
        ClearBackground(CLEAR);
        DrawPlayer(playerAI);
        DrawPlayer(game->player);
        EndDrawing();

}


