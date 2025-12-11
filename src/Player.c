#include "Player.h"


player_t* Player_Factory(moveMode_t moveMode,Color color)
{
    player_t* player = calloc(1,sizeof(player_t));
    player->moveMode=moveMode;
    player->position = (Vector2){100,100};
    player->PlayerColor = color;
    player->direction = (Vector2){0, 0};
    player->radius = 10.0f;
    player->speed = 5.0f;

    return player;
}

void DrawPlayer(player_t* player)
{
    DrawCircle(player->position.x, player->position.y, player->radius, player->PlayerColor);
}

void UpdatePlayer(player_t* player){
    switch (player->moveMode) {
        case KEYBOARD1:
            UpdateMoveByInput(player);
            break;
        case RANDOM:
            UpdateMoveByRand(player);
            break;
    }
    player->position.x += player->direction.x * player->speed;
    player->position.y += player->direction.y * player->speed;
}

void UpdateMoveByInput(player_t* player){
    player->direction= (Vector2){0, 0};
    if (IsKeyDown(KEY_RIGHT)) player->direction.x += 1.0f;
    if (IsKeyDown(KEY_LEFT))  player->direction.x -= 1.0f;
    if (IsKeyDown(KEY_UP))    player->direction.y -= 1.0f;
    if (IsKeyDown(KEY_DOWN))  player->direction.y += 1.0f;
}

void UpdateMoveByRand(player_t* player){
    //rand()/RAND_MAX is minimum 0 max 1 and is float.Then *2 is 0/2 and -1 is -1/1
    float dx = ((float)rand() / RAND_MAX) * 2.0f - 1.0f; 
    float dy = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
    player->direction = (Vector2){ dx, dy };
}

void UpdateSpeed(player_t* player, float newSpeed){
    player->speed = newSpeed;
}