#pragma once

#include "../components/scene.h"

// Graphics Folder
//Idle Animations
#include "../graphics/characters/cameron/idle/cam_front_idle_spritesheet.h"
#include "../graphics/characters/cameron/idle/cam_back_idle_spritesheet.h"
#include "../graphics/characters/cameron/idle/cam_side_idle_spritesheet.h"

//Walk Animations
#include "../graphics/characters/cameron/walk/cam_front_walk_spritesheet.h"
#include "../graphics/characters/cameron/walk/cam_back_walk_spritesheet.h"
#include "../graphics/characters/cameron/walk/cam_side_walk_spritesheet.h"


//Overworld Graphics
#include "../graphics/test_graphics/tiny_16.h"
#include "../graphics/map/collision.h"
#include "../graphics/backgrounds/overworld_options.h"

//Fonts
#include "custom_fonts.h"

class MainData
{
    public:
    static Scene* main_scene;
    static void InitializeMain();
};