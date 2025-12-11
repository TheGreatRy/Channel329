#include "text.h"

Text::Text(TEXT_TYPE text_type, const char *font_file, const char *name, u32 width, u32 height, u32 rotation, float x_pos, float y_pos)
{
    m_text_type = text_type;
    m_name = name;
    m_rotation = rotation;
    m_write_pos = new Position(x_pos, y_pos);

    switch(m_text_type)
    {
        case TEXT_TYPE_CUST:
        NF_LoadTextFont(font_file, m_name, width, height, m_rotation);
        break;
        case TEXT_TYPE_8X16:
        NF_LoadTextFont16(font_file, m_name, width, height, m_rotation);
        break;
    }
}

void Text::AddText(const char* text)
{
    m_text = text;
}

void Text::LoadText(int screen, u32 layer)
{
    m_screen = screen;
    m_layer = layer;
    switch(m_text_type)
    {
        case TEXT_TYPE_CUST:
        NF_CreateTextLayer(screen, layer, m_rotation, m_name);
        break;
        case TEXT_TYPE_8X16:
        NF_CreateTextLayer16(screen, layer, m_rotation, m_name);
        break;
    }
}

void Text::WriteText()
{
    switch(m_text_type)
    {
        case TEXT_TYPE_CUST:
        NF_WriteText(m_screen, m_layer, m_write_pos->m_x, m_write_pos->m_y, m_text);
        break;
        case TEXT_TYPE_8X16:
        NF_WriteText16(m_screen, m_layer, m_write_pos->m_x, m_write_pos->m_y, m_text);
        break;
    }
}

void Text::ClearText()
{
    NF_ClearTextLayer(m_screen, m_layer);
}

void Text::RemoveText()
{
    NF_DeleteTextLayer(m_screen, m_layer);
}
