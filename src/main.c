#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <time.h>
#include "Player.h"
#include "game.h"

int main(void)
{
    const int screenWidth = 480;
    const int screenHeight = 600;
    srand((unsigned int)time(NULL));

    printf("starting");  
    InitWindow(screenWidth, screenHeight, "esempio 03-12-25");
    SetTargetFPS(60);
    //SetWindowTitle("Esempio 03-12-25");

    game_t game;
    GameInit(&game);

    while(!WindowShouldClose())
    {
        float dt = GetFrameTime();
        //Update
        GameUpdate(&game, dt);
        //Draw
        GameDraw(&game);
    }
    
    CloseWindow();
    return 0;
}