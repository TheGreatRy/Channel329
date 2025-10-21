#include <memory>

#include <nds.h>
#include <stdio.h>

#include <gl2d.h>

class Character
{
    public:
    Character(const int frames);
    ~Character() = default;

    int m_frames = 1;
    int m_character_id = 0;

    const uint32_t screen_width = 256;
    const uint32_t screen_height = 192;

    void DrawCharacterFromTileset(glImage spr_img[], const int spr_w, const int spr_h, const unsigned short pal_dt[], const unsigned int tex_dt[]);

};