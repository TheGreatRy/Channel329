#include "tileset.h"
#include "../graphics/characters/cam.h"

Tileset::Tileset(const int spr_num_x, const int spr_num_y, const int spr_w, const int spr_h)
{
    if (spr_num_x >= 1) m_sprites_num_x = spr_num_x;
    if (spr_num_y >= 1) m_sprites_num_y = spr_num_y;

    if (spr_w >= 4) m_sprite_w = spr_w;
    if (spr_h >= 4) m_sprite_h = spr_h;
    
}

void Tileset::LoadTileset(glImage Tileset_arr[], const unsigned short pal_dt[], const unsigned int tex_dt[])
{
    m_texture_id =
        glLoadTileSet(Tileset_arr, // Pointer to glImage array
                      m_sprite_w,        // Sprite width
                      m_sprite_h,        // Sprite height
                      m_sprite_w * m_sprites_num_x,    // Bitmap width (the part that contains useful images)
                      m_sprite_h * m_sprites_num_y,        // Bitmap height (the part that contains useful images)
                      GL_RGB256, // Texture type for glTexImage2D()
                      m_sprite_w * m_sprites_num_x,       // Full texture size X (image size)
                      m_sprite_h * m_sprites_num_y,        // Full texture size Y (image size)
                      // Parameters for glTexImage2D()
                      TEXGEN_TEXCOORD | GL_TEXTURE_COLOR0_TRANSPARENT,
                      256,          // Length of the palette to use (256 colors)
                      pal_dt,     // Pointer to texture palette data
                      tex_dt); // Pointer to texture data

    if (m_texture_id < 0) printf("Failed to load texture: %d\n", m_texture_id);
    
    for (int i = 0; i < m_sprites_num_x; i++)
    {
        m_tileset_img.push_back(Tileset_arr[i]);
    }
}