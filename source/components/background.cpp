#include "background.h"

/// @brief Able to initalize all background types. Only use the parameters needed for the background type
/// @param bg_type Background type as defined in BG_TYPE (`ALL`)
/// @param file File path without extension (`ALL`)
/// @param name File name without extension (`BG_TYPE_AFFINE` and `BG_TYPE_TILED_FULL`)
/// @param slot Slot number (`BG_TYPE_COL`)
/// @param width Background image width in pixels (`BG_TYPE_AFFINE`, `BG_TYPE_COL`, `BG_TYPE_TILED_FULL`, and `BG_TYPE_TILED_RANGE`)
/// @param height Background image height in pixels (`BG_TYPE_AFFINE`, `BG_TYPE_COL`, `BG_TYPE_TILED_FULL`, and `BG_TYPE_TILED_RANGE`)
/// @param tile_start First tile to load (`BG_TYPE_TILED_RANGE`)
/// @param tile_end Last tile to load (`BG_TYPE_TILED_RANGE`)
Background::Background(BG_TYPE bg_type, const char *file, const char *name = "default", u32 slot = 0, u32 width = 0, u32 height = 0, u32 tile_start = 0, u32 tile_end = 0)
{
    m_background_type = bg_type;
    m_name = name;
    m_slot = slot;
    m_width = width;
    m_height = height;
    m_start_tile = tile_start;
    m_end_tile = tile_end;

    //load background from nitrofs files
    switch (m_background_type)
    {
        case BG_TYPE_8BIT:
            NF_Load8bitsBg(file, m_slot);
            break;
        case BG_TYPE_16BIT:
            NF_Load16bitsBg(file, m_slot);
            break;
        case BG_TYPE_AFFINE:
            NF_LoadAffineBg(file, m_name, m_width, m_height);
            break;
        case BG_TYPE_COL:
            NF_LoadCollisionBg(file, m_slot, m_width, m_height);
            break;
        case BG_TYPE_TILED_FULL:
            NF_LoadTiledBg(file, m_name, m_width, m_height);
            break;
        case BG_TYPE_TILED_RANGE:
            NF_LoadTilesForBg(file, m_name, m_width, m_height, m_start_tile, m_end_tile);
            break;
    }
}

/// @brief Loads backgrounds on the specified screen and/or layer. Only use the parameters needed for the background type. The Collision Background does not need to be loaded with this function
/// @param screen The screen to display to, 0 being the top screen and 1 being the bottom screen (`ALL`)
/// @param layer The background layer to draw to (`BG_TYPE_AFFINE`, `BG_TYPE_TILED_FULL`, and `BG_TYPE_TILED_RANGE`)
/// @param copy_dest The memory location to copy the background to, with 0 being VRAM and 0 being the backbuffer (`BG_TYPE_8BIT` and `BG_TYPE_16BIT`) 
/// @param can_wrap If the background is allowed to wrap the screen (`BG_TYPE_AFFINE`)
void Background::LoadBackground(int screen, int layer = 0, int copy_dest = 0, bool can_wrap = false)
{
    m_screen = screen;
    m_layer = layer;
    switch (m_background_type)
    {
        case BG_TYPE_8BIT:
            //moved to vram or buffer
            NF_Copy8bitsBuffer(screen, copy_dest, m_slot);
            break;
        case BG_TYPE_16BIT:
            //moved to vram or buffer
            NF_Copy16bitsBuffer(screen, copy_dest, m_slot);
            break;
        case BG_TYPE_AFFINE:
            //created on ram, no vram option?
            NF_CreateAffineBg(screen, layer, m_name, can_wrap);
            break;
        case BG_TYPE_COL:
            //not needed, constructor loads it    
            return;
        case BG_TYPE_TILED_FULL:
            //moved to vram
            NF_CreateTiledBg(screen, layer, m_name);
            //free ram
            UnloadBackgroundRAM();
            break;
        case BG_TYPE_TILED_RANGE:
            //moved to vram
            NF_CreateTiledBg(screen, layer, m_name);
            //free ram
            UnloadBackgroundRAM();
            break;
    }
}


void Background::DeleteBackground()
{
    switch (m_background_type)
    {
        case BG_TYPE_8BIT:
            UnloadBackgroundRAM();
            break;
        case BG_TYPE_16BIT:
            UnloadBackgroundRAM();
            break;
        case BG_TYPE_AFFINE:
            UnloadBackgroundRAM();
            NF_DeleteAffineBg(m_screen, m_layer);
            break;
        case BG_TYPE_COL:
            UnloadBackgroundRAM();
            break;
        case BG_TYPE_TILED_FULL:
            NF_DeleteTiledBg(m_screen, m_layer);
            break;
        case BG_TYPE_TILED_RANGE:
            NF_DeleteTiledBg(m_screen, m_layer);
            break;
    }
}

void Background::UnloadBackgroundRAM()
{
    switch (m_background_type)
    {
        case BG_TYPE_8BIT:
            NF_Unload8bitsBg(m_slot);
            break;
        case BG_TYPE_16BIT:
            NF_Unload16bitsBg(m_slot);
            break;
        case BG_TYPE_AFFINE:
            NF_UnloadAffineBg(m_name);
            break;
        case BG_TYPE_COL:
            NF_UnloadCollisionBg(m_slot);
            break;
        case BG_TYPE_TILED_FULL:
            NF_UnloadTiledBg(m_name);
            break;
        case BG_TYPE_TILED_RANGE:
            NF_UnloadTiledBg(m_name);
            break;
    }
}
