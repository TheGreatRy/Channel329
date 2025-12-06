#include "Sprite.h"

Sprite::Sprite(const char *file, u32 gfx_id, u32 pal_id, u32 width, u32 height)
{
    m_gfx_id = gfx_id;
    m_pal_id = pal_id;
    m_sprite_w = width;
    m_sprite_h = height;

    NF_LoadSpriteGfx(file, gfx_id, m_sprite_w, m_sprite_h);
    NF_LoadSpritePal(file, pal_id);
}

void Sprite::LoadSprite(int screen, u32 sprite_id, u32 gfx_slot, u32 pal_slot, s32 x, s32 y, bool copy_all_frames, u32 layer)
{
    m_gfx_slot = gfx_slot;
    m_pal_slot = pal_slot;
    m_sprite_id = sprite_id;
    m_x_pos = x;
    m_y_pos = y;

    NF_VramSpriteGfx(screen, m_gfx_id, gfx_slot, copy_all_frames);
    NF_VramSpritePal(screen, m_pal_id, pal_slot);

    NF_CreateSprite(screen, m_sprite_id, m_gfx_slot, m_pal_slot, m_x_pos, m_x_pos);
    NF_SpriteLayer(screen, m_sprite_id, layer);
}

void Sprite::UnloadSprite()
{
    NF_UnloadSpriteGfx(m_gfx_id);
    NF_UnloadSpritePal(m_pal_id);
}
