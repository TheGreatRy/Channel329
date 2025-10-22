#include "character.h"
#include "../graphics/characters/cam.h"

Character::Character(const int frames, const int spr_w, const int spr_h)
{
    if (frames < 1) m_frames_num = 1;
    else m_frames_num = frames;

    if (spr_w < 1) m_sprite_w = 1;
    else m_sprite_w = spr_w;

    if (spr_h < 1) m_sprite_h = 1;
    else m_sprite_h = spr_h;
}

void Character::DrawCharacterFromTileset(glImage character_arr[], const unsigned short pal_dt[], const unsigned int tex_dt[])
{
    m_texture_id =
        glLoadTileSet(character_arr, // Pointer to glImage array
                      m_sprite_w,        // Sprite width
                      m_sprite_h,        // Sprite height
                      m_sprite_w * m_frames_num,    // Bitmap width (the part that contains useful images)
                      m_sprite_h,        // Bitmap height (the part that contains useful images)
                      GL_RGB256, // Texture type for glTexImage2D()
                      32,       // Full texture size X (image size)
                      32,        // Full texture size Y (image size)
                      // Parameters for glTexImage2D()
                      TEXGEN_TEXCOORD | GL_TEXTURE_COLOR0_TRANSPARENT,
                      256,          // Length of the palette to use (256 colors)
                      pal_dt,     // Pointer to texture palette data
                      tex_dt); // Pointer to texture data

    if (m_texture_id < 0) printf("Failed to load texture: %d\n", m_texture_id);
    
    for (int i = 0; i < m_frames_num; i++)
    {
        m_frames_img.push_back(character_arr[i]);
    }
}