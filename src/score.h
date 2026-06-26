#pragma once

#include <raylib.h>
#include "config.h"

typedef struct 
{
    int score;
    bool scored;
    Sound score_sound;
} ScoreManager;

ScoreManager load_score_manager(void);
void draw_score(int score);