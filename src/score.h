#pragma once

#include <raylib.h>
#include "config.h"

typedef struct 
{
    int score;
    int score_to_add;
    float score_to_add_alpha;
    float alpha_fade_speed;
    float score_to_add_speed;
    Vector2 score_to_add_position;
    bool scored;
    float scored_timer;
    Sound score_sound;
} ScoreManager;

ScoreManager load_score_manager(void);
void unload_score_manager(ScoreManager *score_manager);
void update_score(ScoreManager *score_manager, Vector2 frog_position, float dt);
void draw_score(const ScoreManager *score_manager);