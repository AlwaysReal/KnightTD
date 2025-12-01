#include "raylib.h"
#include "raymath.h"
int main()
{
    // window dimensions
    int windowDimensions[2];
    windowDimensions[0] = 384;
    windowDimensions[1] = 384;

    InitWindow(windowDimensions[0], windowDimensions[1], "First Top-down");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};
    float speed{4.0};

    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight = knight_idle;
    Vector2 knightPos{
        (float)windowDimensions[0]/2.0f - 4.0f * (0.5f * (float)knight.width/6),
        (float)windowDimensions[1]/2.0f - 4.0f * (0.5f * (float)knight.height)
    };
    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f/12.f};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;
        if (Vector2Length(direction) != 0.0)
        {
            // set mapPos = mapPos - direction
            knight = knight_run;
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f; 
        }
        else
        {
            knight = knight_idle;
        }

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        // update animation frame
        runningTime +=  GetFrameTime();
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrames) frame = 0;
        }

        // draw the character
        Rectangle knightSource{frame * (float)knight.width/6.f, 0.f, rightLeft * (float)knight.width/6.f, (float)knight.height};
        Rectangle knightDest{ knightPos.x, knightPos.y, 4.0f * knight.width/6.f, 4.0f * knight.height};
        DrawTexturePro(knight,knightSource, knightDest, Vector2{}, 0.0, WHITE);
       
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}
