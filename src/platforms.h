#pragma once

#include <raylib.h>
#include "config.h"
#include "frog.h"

typedef struct 
{
    Rectangle platforms[PLATFORMS_SIZE];
    int last_platform_y;
} PlatformManager;


PlatformManager load_platform_manager(void);
void draw_platforms(Rectangle platforms[]);
void check_platforms_collision(Frog *frog, Rectangle platforms[]);
void update_platforms(PlatformManager *platform_manager);