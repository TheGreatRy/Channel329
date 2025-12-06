#include "animation.h"

Animation::Animation(Sprite *spritesheet)
{
    m_spritesheet = spritesheet;
    m_sprite_amount = (m_spritesheet->m_sprite_h / m_spritesheet->m_sprite_w);
}


void Animation::PlayAnimation(int fps, bool flip_sprites)
{
    m_time_step++;
    if (m_time_step > fps)
    {
        m_time_step = 0;

        m_current_frame_index++;
        if (m_current_frame_index > m_sprite_amount) 
            m_current_frame_index = 0;   
    }
    NF_SpriteFrame(m_spritesheet->m_screen, m_spritesheet->m_sprite_id, m_current_frame_index);
}
