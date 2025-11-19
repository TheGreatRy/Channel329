#include "animation.h"

Animation::Animation(Tileset *spritesheet)
{
    m_spritesheet = *spritesheet;
}


void Animation::PlayAnimation(int x_pos, int y_pos, int fps, GL_FLIP_MODE flip_sprites)
{
    m_time_step++;
    if (m_time_step > fps)
    {
        m_time_step = 0;

        m_current_frame_index++;
        if (m_current_frame_index > (m_spritesheet.m_sprites_num_x * m_spritesheet.m_sprites_num_y) - 1) 
            m_current_frame_index = 0;   
    }
    
    glSprite(x_pos, y_pos, flip_sprites,  &m_spritesheet.m_tileset_img[m_current_frame_index]); 
}
