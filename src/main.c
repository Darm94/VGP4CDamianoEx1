#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <time.h>
#include "Player.h"
#include "game.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


size_t djb33x_hash(void *key, size_t keylen) {
    register int hash = 5381;
    int i;
    unsigned char *key_as_num = (unsigned char *)key;
    for (i = 0; i < keylen; i++) {
        hash = ((hash << 5) + hash) ^ key_as_num[i];
    }
    return hash;
}
void hash_to_hex_string(size_t hash_value, char *output_buffer) {
    sprintf(output_buffer, "%016zX", hash_value);
}
/*
(struct sockaddr*)&clientAddr,
&clientAddrLen
*/

int main(void)
{
    const int screenWidth = 480;
    const int screenHeight = 600;
    srand((unsigned int)time(NULL));

    printf("starting\n"); 
    
    const char *key_string = "DamianoSchirru_20/04/1994";
    size_t key_length = strlen(key_string);
    size_t hash_value = djb33x_hash((void *)key_string, key_length);
    char id_string[17]; // Array di 17 caratteri
    hash_to_hex_string(hash_value, id_string);
    printf("Stringa di input: \"%s\"\n", key_string);
    printf("Valore Hash (size_t): %zu\n", hash_value);
    printf("ID esadecimale (16 char): %s\n", id_string);


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