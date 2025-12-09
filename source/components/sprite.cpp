#include "Sprite.h"

Sprite::Sprite(SPR_TYPE spr_type, const char *file, u32 gfx_id, u32 pal_id, u32 width, u32 height, int screen)
{
    m_spr_type = spr_type;
    m_gfx_id = gfx_id;
    m_pal_id = pal_id;
    m_sprite_w = width;
    m_sprite_h = height;
    m_screen = screen;

    // load sprite from nirtofs files
    NF_LoadSpriteGfx(file, gfx_id, m_sprite_w, m_sprite_h);
    NF_LoadSpritePal(file, pal_id);
}

void Sprite::LoadSprite(u32 sprite_id, u32 gfx_slot, u32 pal_slot, Position *pos, bool copy_all_frames, u32 layer)
{
    m_gfx_slot = gfx_slot;
    m_pal_slot = pal_slot;
    m_sprite_id = sprite_id;
    m_spr_pos = pos;

    

    if (m_spr_type == SPR_TYPE_256)
    {
        // move to vram
        NF_VramSpriteGfx(m_screen, m_gfx_id, gfx_slot, copy_all_frames);
        NF_VramSpritePal(m_screen, m_pal_id, pal_slot);

        // create sprite
        NF_CreateSprite(m_screen, m_sprite_id, m_gfx_slot, m_pal_slot, m_spr_pos->m_x, m_spr_pos->m_y);
    }
    else if (m_spr_type == SPR_TYPE_3D)
    {
        NF_Vram3dSpriteGfx(m_gfx_id, gfx_slot, copy_all_frames);
        NF_Vram3dSpritePal(m_pal_id, pal_slot);
        
        // create sprite
        NF_Create3dSprite(m_sprite_id, m_gfx_slot, m_pal_slot, m_spr_pos->m_x, m_spr_pos->m_y);
    }
    // free ram
    NF_UnloadSpriteGfx(m_gfx_id);
    NF_UnloadSpritePal(m_pal_id);
}

void Sprite::RemoveSprite()
{
    if (m_spr_type == SPR_TYPE_256)
    {
        // remove sprite from screen
        NF_DeleteSprite(m_screen, m_sprite_id);

        // free vram of screen, no palette option?
        NF_FreeSpriteGfx(m_screen, m_gfx_slot);
    }
    else if (m_spr_type == SPR_TYPE_3D)
    {
        // remove sprite from screen
        NF_Delete3dSprite(m_sprite_id);

        // free vram of screen, no palette option?
        NF_Free3dSpriteGfx(m_gfx_slot);
    }
    

}
