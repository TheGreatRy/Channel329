#include "background.h"

Background::Background(int layer, BgType bg_type, BgSize bg_size, int map_base, int tile_base, bool is_main, BackgroundData *data)
{
    if (is_main)
        m_background_id = bgInit(layer, bg_type, bg_size, map_base, tile_base);
    else
        m_background_id = bgInitSub(layer, bg_type, bg_size, map_base, tile_base);

    m_is_main = is_main;
    m_data = data;
}

void Background::LoadBackground(int bpp)
{
    if (bpp == 8)
    {
        if (m_is_main)
            dmaCopy(m_data->m_pal_source, BG_PALETTE, m_data->m_pal_size);
        else
            dmaCopy(m_data->m_pal_source, BG_PALETTE_SUB, m_data->m_pal_size);

        bgSetMapBase(m_background_id, m_data->m_bitmap_base);

        dmaCopy(m_data->m_bitmap_source, bgGetGfxPtr(m_background_id), m_data->m_bitmap_size);
    }
    else if (bpp == 16)
    {
        bgSetMapBase(m_background_id, m_data->m_bitmap_base);

        dmaCopy(m_data->m_bitmap_source, bgGetGfxPtr(m_background_id), m_data->m_bitmap_size);
    }
}
