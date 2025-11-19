#include "animation.h"

Animation::Animation(Tileset *spritesheet, int total_frames)
{
    m_spritesheet = *spritesheet;
    m_total_frames = total_frames;
}


void Animation::PlayAnimation(int x_pos, int y_pos, int fps, GL_FLIP_MODE flip_sprites)
{
    m_time_step++;
    if (m_time_step > fps)
    {
        m_time_step = 0;

        m_current_frame_index++;
        if (m_current_frame_index > m_total_frames - 1) 
            m_current_frame_index = 0;   
    }
    
    glSprite(x_pos, y_pos, flip_sprites,  &m_spritesheet.m_tileset_img[m_current_frame_index]); 
}
