#pragma once

#include <raylib.h>
#include "config.h"
#include "frog.h"
#include "score.h"

typedef struct 
{
    Rectangle platforms[PLATFORMS_SIZE];
    int last_platform;
} PlatformManager;


PlatformManager load_platform_manager(void);
void draw_platforms(const Rectangle platforms[]);
void check_platforms_collision(Frog *frog, Rectangle platforms[], ScoreManager *score_manager);
void update_platforms(PlatformManager *platform_manager);