#pragma once

#include <raylib.h>

#define FROG_WIDTH  64
#define FROG_HEIGHT 64

#define FEET_OFFSET_X 22
#define FEET_OFFSET_Y 36
#define FEET_WIDTH    22
#define FEET_HEIGHT    5

#define JUMP_POWER_CAP 400.0f
#define GRAVITY 200.0f

typedef struct
{
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
    int frame_width;
    int frame_height;
    int current_frame;
    Rectangle frame;
    Rectangle feet;
    float aim_speed;
    float aim_angle;
    float jump_power;
    bool is_jumping;
    bool is_charging;
} Frog;

Frog create_frog(Vector2 spawn_pos);
void update_frog(Frog *frog, float dt);
void draw_frog(const Frog *frog);