#pragma once

//NDS Libraries
#include <nds.h>
#include <stdio.h>
#include <nf_lib.h>

#include "../utilities/position.h"

class Sprite
{
public:

    Sprite() = default;
    Sprite(const char *file, u32 gfx_id, u32 pal_id, u32 width, u32 height, int screen);
    ~Sprite() = default;

    Position* m_spr_pos;
    int m_screen;
    u32 m_sprite_id;
    u32 m_gfx_id;
    u32 m_pal_id;
    
    u32 m_gfx_slot;
    u32 m_pal_slot;

    u32 m_sprite_h;
    u32 m_sprite_w ;

    void LoadSprite(u32 sprite_id, u32 gfx_slot, u32 pal_slot, Position* pos, bool copy_all_frames, u32 layer);
    void RemoveSprite();
};