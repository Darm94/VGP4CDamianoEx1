
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define VC_EXTRALEAN
#include "game.h"

#include <stdlib.h>
#define CLEAR RAYWHITE
#define PLAYER_AI_COLOR RED

//very semplified way: not using a player-t collection for now but a global variable for a single other player
player_t* playerAI=NULL;
float timerAccumulator;

void GameInit(game_t *game)
{
    game->player = Player_Factory(KEYBOARD1,GREEN);
    playerAI = Player_Factory(RANDOM,PLAYER_AI_COLOR);
    timerAccumulator = 0;
}

void GameUpdate(game_t *game, float dt,networkingData* nData)
{
        //UpdateMoveByInput(game->player);
        //UpdateMoveByRand(playerAI);
        UpdatePlayer(game->player,dt);
        UpdatePlayer(playerAI,dt);

        timerAccumulator += dt;
        //printf("%f", timerAccumulator);

        if (timerAccumulator >= 0.5f)
        {
                char buffer[128];
                sprintf(buffer, "UDP:%f,%f",
                        game->player->position.x,
                        game->player->position.y);

                SendMessage(nData, buffer);
                timerAccumulator = 0;
        }
}

void GameDraw(const game_t *game)
{
        BeginDrawing();
        ClearBackground(CLEAR);
        DrawPlayer(playerAI);
        DrawPlayer(game->player);
        EndDrawing();

}





