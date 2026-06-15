#include <raylib.h>

#define FEET_OFFSET_X 22
#define FEET_OFFSET_Y 36
#define FEET_WIDTH    22
#define FEET_HEIGHT    5

typedef struct
{
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
    Rectangle frame;
    Rectangle feetBox;
    bool isJumping;
} Frog;

int main(void)
{
    InitWindow(800, 600, "frog");

    float gravity = 300;

    Frog frog = {
        .position = {100, 100},
        .velocity = {0, 0},
        .texture = LoadTexture("assets/frog-idle.png"),
        .frame = {
            .x = 0,
            .y = 0,
            .width = 64,
            .height = 64
        },
        .isJumping = true
    };

    Rectangle frogHitbox = {
        frog.position.x + FEET_OFFSET_X,
        frog.position.y + FEET_OFFSET_Y,
        FEET_WIDTH,
        FEET_HEIGHT
    };

    Rectangle platform = {
        120,
        500,
        30,
        4
    };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (frog.isJumping)
        {
            frog.velocity.y += gravity * dt;
            frog.position.y += frog.velocity.y * dt;
            frogHitbox.y = frog.position.y + FEET_OFFSET_Y;
        }

        if (CheckCollisionRecs(frogHitbox, platform))
        {
            frog.isJumping = false;
            frog.velocity.y = 0;
            printf("collision");
        }

        BeginDrawing();

        ClearBackground(DARKGRAY);

        DrawRectangleRec(platform, DARKGREEN);

        DrawTextureRec(
            frog.texture,
            frog.frame,
            frog.position,
            WHITE
        );

        DrawRectangleLines(
            frogHitbox.x,
            frogHitbox.y,
            frogHitbox.width,
            frogHitbox.height,
            RED
        );


        EndDrawing();
    }

    UnloadTexture(frog.texture);

    CloseWindow();

    return 0;
}