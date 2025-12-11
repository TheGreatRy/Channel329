#pragma once

#include <nf_lib.h>

#include "../utilities/position.h"

enum TEXT_TYPE
{
    TEXT_TYPE_CUST,
    TEXT_TYPE_8X16
};

class Text
{
public:
    Text() = default;
    Text(TEXT_TYPE text_type, const char *font_file, const char *name, u32 width, u32 height, u32 rotation, float x_pos, float y_pos);
    ~Text() = default;

    TEXT_TYPE m_text_type;
    Position* m_write_pos;
    const char* m_name;
    const char* m_text;
    int m_screen;
    u32 m_rotation;
    u32 m_layer;

    void AddText(const char* text);
    void LoadText(int screen, u32 layer);
    void WriteText();
    void ClearText();
    void RemoveText();
};