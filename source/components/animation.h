#pragma once

#include "sprite.h"

class Animation
{
    public:
    Animation() = default;
    Animation(Sprite* spritesheet);
    ~Animation() = default;
    
    Sprite* m_spritesheet;
    int m_sprite_amount;
    
    int m_time_step = 0;
    int m_current_frame_index = 0;

    void PlayAnimation(int fps, bool flip_sprites);
};