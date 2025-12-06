#pragma once

//NDS Libraries
#include <nds.h>
#include <stdio.h>
#include <nf_lib.h>


class Sprite
{
public:

    Sprite() = default;
    Sprite(const char *file, u32 gfx_id, u32 pal_id, u32 width, u32 height, int screen);
    ~Sprite() = default;

    int m_screen = 0;
    u32 m_sprite_id = 0;
    u32 m_gfx_id = 0;
    u32 m_pal_id = 0;
    
    u32 m_gfx_slot = 0;
    u32 m_pal_slot = 0;

    u32 m_sprite_h = 8;
    u32 m_sprite_w = 8;
    s32 m_x_pos = 0;
    s32 m_y_pos = 0;

    void LoadSprite(u32 sprite_id, u32 gfx_slot, u32 pal_slot, s32 x, s32 y, bool copy_all_frames, u32 layer);
    void RemoveSprite();
};