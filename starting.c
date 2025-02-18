#include <raylib.h>
#include <time.h>
#include <stdlib.h>

#define Snake_length 100
#define Block_Size 40 

// grid bna ni 
// snake moving algorithm with struct bna na 
// food algorithm 

typedef struct {
    int x;
    int y;
} Portion;

int main(){
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Raylib Rectangle");
    SetTargetFPS(10);
    Portion snake[Snake_length];
    Color color[6] = { ORANGE, YELLOW  , GREEN ,GRAY , BLACK , BLUE };
    int length = 4;
    int score = 0;
    snake[0].x = 240;
    snake[0].y = 240;

    int dirx = Block_Size;
    int diry = 0;

    srand(time(0));

    Portion food = {
      (rand() % (screenWidth / Block_Size)) * Block_Size,
      (rand() %(screenHeight / Block_Size)) * Block_Size
    };

    while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_UP) && diry == 0){
       diry = -Block_Size;
       dirx = 0;
    }
    if (IsKeyDown(KEY_RIGHT) && dirx == 0){
       dirx = Block_Size;
       diry = 0;
    }
    if (IsKeyDown(KEY_LEFT) && dirx == 0){
       dirx = -Block_Size;
       diry = 0;
    }
    if (IsKeyDown(KEY_DOWN) && diry == 0){
       diry = Block_Size;
       dirx = 0;
    }
    
    for (int  i = length; i > 0; i--)
    {
       snake[i] = snake[i - 1];
       // for example agar let i  = 10 or us k x and y cords are 
       // 120 and 120 or snake 9 move krta ha in right direction
       // so i - 1 ho ga phir 160 and 120 or is tarah 10 ki val 9 ma
    }
    
    snake[0].x += dirx;
    snake[0].y += diry;

    //within bounds
    if (snake[0].x >= screenWidth){
        snake[0].x = 0;
    }
    if (snake[0].x < 0){
        snake[0].x = screenWidth - Block_Size;
    }
    if (snake[0].y >= screenHeight){
        snake[0].y = 0;
    }
    if (snake[0].y < 0){
        snake[0].y = screenHeight-Block_Size;
    }

    if (snake[0].x == food.x && snake[0].y == food.y ) {
        length++;
        score++;
        food.x =  (rand() % (screenWidth / Block_Size)) * Block_Size;
        food.y =  (rand() % (screenHeight / Block_Size)) * Block_Size;
    }
    for (int i = length; i > 0; i--){
            if (snake[0].x == snake[i].x  && snake[0].y == snake[i].y){
                length = 0;
            }
    }
    if (length == 0)
    {
        DrawText("game end" , 240 , 240 , 64 ,RED);
    }
    
    DrawText(TextFormat("POINTS : %d" , score), 40 , 40 , 34 ,RED);
    
    BeginDrawing();
    ClearBackground(RAYWHITE);
     for (int i = 0; i < length; i++){
        DrawRectangle(snake[i].x , snake[i].y , Block_Size ,Block_Size , color[i % 6]);
        // DrawRectangle(snake[0].x , snake[0].y , Block_Size ,Block_Size , YELLOW);
     }
     
    DrawRectangle(food.x ,food.y , Block_Size , Block_Size , RED );
    

    EndDrawing();
    }
    CloseWindow();
     return 0;
}