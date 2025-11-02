#include "tileset.h"
#include <string>
#include <math.h>

Tileset::Tileset(const int spr_num_x, const int spr_num_y, const int spr_w, const int spr_h, TS_TAG ts_tag)
{
    if (spr_num_x >= 1)
        m_sprites_num_x = spr_num_x;
    if (spr_num_y >= 1)
        m_sprites_num_y = spr_num_y;

    if (spr_w >= 4)
        m_sprite_w = spr_w;
    if (spr_h >= 4)
        m_sprite_h = spr_h;

    m_tag = ts_tag;

    m_img_dimensions = m_sprites_num_x * m_sprites_num_y;
}

void Tileset::LoadTileset(glImage tileset_arr[], const unsigned short pal_dt[], const unsigned int tex_dt[], GL_TEXTURE_TYPE_ENUM tex_type, const unsigned int pal_len)
{
    m_texture_id =
        glLoadTileSet(tileset_arr,                                                        // Pointer to glImage array
                      m_sprite_w,                                                         // Sprite width
                      m_sprite_h,                                                         // Sprite height
                      m_sprite_w * m_sprites_num_x,                                       // Bitmap width (the part that contains useful images)
                      m_sprite_h * m_sprites_num_y,                                       // Bitmap height (the part that contains useful images)
                      tex_type,                                                           // Texture type for glTexImage2D()
                      PaddingForPowerOfTwo(m_sprite_w, m_sprites_num_x, TS_SIZE_FULL_TEX), // Full texture size X (image size)
                      PaddingForPowerOfTwo(m_sprite_h, m_sprites_num_y, TS_SIZE_FULL_TEX), // Full texture size Y (image size)
                      // Parameters for glTexImage2D()
                      TEXGEN_TEXCOORD | GL_TEXTURE_COLOR0_TRANSPARENT,
                      PaddingForPowerOfTwo(pal_len, 1, TS_SIZE_PAL_LEN), // Palette length
                      pal_dt,                                              // Pointer to texture palette data
                      tex_dt);                                             // Pointer to texture data

    if (m_texture_id < 0)
        printf("Failed to load texture: %d\n", m_texture_id);

    for (int i = 0; i < m_img_dimensions; i++)
    {
        m_tileset_img.push_back(tileset_arr[i]);
    }
}

int Tileset::PaddingForPowerOfTwo(int x, int y, TS_SIZE ts_size)
{
    int dimensions = x * y;
    float getExponent = log2((double)dimensions);

    // if the the dimensions are NOT an integer power of two, restrict it (accurate to 10 decimal places, I hope this is enough)
    if (std::to_string(getExponent).find("0000000000", 2) != 2)
    {
        // I'm aware I can combine this into one block instead of a switch case, but that requires more checks that could potentially break
        switch (ts_size)
        {
#pragma region Texture Size Checks
        // Texture images need to be between 8 and 1024, but a power of 2
        case TS_SIZE_FULL_TEX:
            if (dimensions <= 8)
                return 8;
            else if (dimensions > 8 && dimensions <= 16)
                return 16;
            else if (dimensions > 16 && dimensions <= 32)
                return 32;
            else if (dimensions > 32 && dimensions <= 64)
                return 64;
            else if (dimensions > 64 && dimensions <= 128)
                return 128;
            else if (dimensions > 128 && dimensions <= 256)
                return 256;
            else if (dimensions > 256 && dimensions <= 512)
                return 512;
            else
                return 1024;
#pragma endregion

#pragma region Palette Length Checks
        // Palette lengths can be between 4 and 256 bits, but a power of two (I actually don't know is this is required for all palettes but I'm restricting it to be safe)
        case TS_SIZE_PAL_LEN:
            if (dimensions <= 4)
                return 4;
            else if (dimensions > 4 && dimensions <= 8)
                return 8;
            else if (dimensions > 8 && dimensions <= 16)
                return 16;
            else if (dimensions > 16 && dimensions <= 32)
                return 32;
            else if (dimensions > 32 && dimensions <= 64)
                return 64;
            else if (dimensions > 64 && dimensions <= 128)
                return 128;
            else
                return 256;
#pragma endregion
        }
    }
    return (x * y);
}
