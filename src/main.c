#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define VC_EXTRALEAN

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <time.h>
#include "Player.h"
#include "game.h"
#include "network.h"


#include <string.h>



player_t* playerKeyboard;

void InitGame();
void UpdateGame(networkingData* nData);
void DrawGame();

int main(void)
{
    networkingData nData;

    const int screenWidth = 480;
    const int screenHeight = 600;
    srand((unsigned int)time(NULL));

    printf("starting\n"); 

    InitWindow(screenWidth, screenHeight, "esempio 03-12-25");
    SetTargetFPS(60);
    
    printf("initializing connection");
    InitConnection(&nData);
    printf("initialized connection");

    //SetWindowTitle("Esempio 03-12-25");
    char* msg = "NEW";
    printf("Message sent");

    game_t game;
    GameInit(&game);
    SendMessage(&nData, msg);

    while(!WindowShouldClose())
    {
        float dt = GetFrameTime();
        //Update
        GameUpdate(&game, dt,&nData);
        //Draw
        GameDraw(&game);
    }
    
    CloseWindow();
    NetworkCleanUp(&nData);

    return 0;
}
