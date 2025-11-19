#pragma once

#include "tileset.h"

class Animation
{
    public:
    Animation() = default;
    Animation(Tileset* spritesheet);
    ~Animation() = default;
    
    Tileset m_spritesheet;
    
    int m_time_step = 0;
    int m_current_frame_index = 0;

    void PlayAnimation(int x_pos, int y_pos, int fps, GL_FLIP_MODE flip_sprites);
};