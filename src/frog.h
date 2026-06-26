#pragma once

#include <raylib.h>
#include <math.h>
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
    int current_platform;
    Sound jump_sound;
    Sound wall_hit_sound;
    Sound die_sound;
    int wall_hits;
    int max_lives;
    int current_lives;
} Frog;

Frog load_frog(void);
void unload_frog(Frog *frog);
void update_frog(Frog *frog, float dt);
void draw_frog(const Frog *frog);
void update_aim(Frog *frog, float dt);
void draw_aim(const Frog *frog);