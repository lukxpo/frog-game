#pragma once

#include <raylib.h>
#include "config.h"

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
    bool is_flipped;
} Frog;

Frog load_frog(Vector2 spawn_pos);
void update_frog(Frog *frog, float dt);
void draw_frog(const Frog *frog);
void update_aim(Frog *frog, float dt);
void draw_aim(Frog *frog);