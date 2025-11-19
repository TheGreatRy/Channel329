#include "map.h"

Map::Map(Tileset *tileset_info, int map_width, int map_height, const int16_t tile_id_arr[], MAP_TYPE map_type)
{
    m_tileset_info = *tileset_info;

    m_map_width = map_width;
    m_map_height = map_height;

    m_map_type = map_type;

    // the algorithm is inputing (x,y)[value] across the row then down the column

    // values are based on a 30 * 20 map (used for reference)

    int current_y = 0;
    for (int current_x = 0; current_x < (m_map_width * m_map_height); current_x++) // current x == 0 - (30 * 20)
    {
        // no need to mod the first row
        // also the first column is 0 and this prevents it from being incremented 1 past
        if (current_x < m_map_width) // x < 30
            m_coordinates.push_back({new Coordinate(current_x, current_y, tile_id_arr[current_x])});
        // x = 0 - 29, y = 0;

        // if we are past the first row
        else if (current_x >= m_map_width) // x >= 30
        {
            int row_reset = current_x % m_map_width; // x % 30 (should cycle every 30 values)
            if (row_reset == 0)
                current_y++; // y++ on x % 30 == 0

            m_coordinates.push_back({new Coordinate(row_reset, current_y, tile_id_arr[current_x])});
        }
    }
}

void Map::DrawMap(Character *player, int scroll_x, int scroll_y, bool &can_move_u, bool &can_move_d, bool &can_move_l, bool &can_move_r)
{
    // values are based on a 30 * 20 map (used for reference)

    // we only need to draw the necessary tiles
    int width_tile_amt = (SCREEN_WIDTH / m_tileset_info.m_sprite_w); // == 16

    int height_tile_amt = (SCREEN_HEIGHT / m_tileset_info.m_sprite_h); // == 12

    int draw_x_pos = 0;
    int draw_y_pos = 0;
    int tile_id = 0;

    int y_coord = 0;
    int x_coord = 0;

    for (int i = 0; i < (width_tile_amt * height_tile_amt); i++) // until 16*12
    {
        // //draws entire map
        // draw_x_pos = scroll_x + m_coordinates.at(i)->m_x * m_tileset_info.m_sprite_w;
        // draw_y_pos = scroll_y + m_coordinates.at(i)->m_y * m_tileset_info.m_sprite_h;

        // tile_id = m_coordinates.at(i)->m_value;

        // Draws only necessary tiles (WIP)

        // We still want to increment coords even if a tile isn't being drawn

        // drawing the map should NOT change position on the screen
        // the scroll only affects which tile is drawn
        x_coord = i % width_tile_amt; // i % 16

        if (i >= width_tile_amt) // x >= 16
        {
            if (x_coord == 0)
                y_coord++; // y++ on i % 16 == 0, cycles every 16 values
        }

        // check bounds of the map, we do not draw tiles out of bounds
        if ((x_coord + scroll_x) < 0 || (y_coord + scroll_y) < 0)
            break;
        if ((x_coord + scroll_x) > m_map_width - 1 || (y_coord + scroll_y) > m_map_height - 1)
            break;

        // set drawing positions
        draw_x_pos = x_coord * m_tileset_info.m_sprite_w;
        draw_y_pos = y_coord * m_tileset_info.m_sprite_h;

        tile_id = m_coordinates.at((x_coord + scroll_x) + (m_map_width * (y_coord + scroll_y)))->m_value;

        glSprite(draw_x_pos, draw_y_pos, GL_FLIP_NONE, &m_tileset_info.m_tileset_img[tile_id]);

        // build collision box

        //Left
        if (x_coord == (width_tile_amt / 2) - 2 && y_coord == (height_tile_amt / 2) - 1) m_collision_box.insert({'l', m_coordinates.at((x_coord + scroll_x) + (m_map_width * (y_coord + scroll_y)))->m_value});
        if (x_coord == (width_tile_amt / 2) - 2 && y_coord == (height_tile_amt / 2)) m_collision_box.insert({'L', m_coordinates.at((x_coord + scroll_x) + (m_map_width * (y_coord + scroll_y)))->m_value});

        // //Right
        // if (x_coord == (width_tile_amt / 2) + 1 && y_coord == (height_tile_amt / 2) - 1) can_move_r = false;
        // else if (x_coord == (width_tile_amt / 2) + 1 && y_coord == (height_tile_amt / 2)) can_move_r = false;
        // else can_move_r = true;

        // //Top
        // if (x_coord == (width_tile_amt / 2) - 1 && y_coord == (height_tile_amt / 2) - 2) can_move_u = false;
        // else if (x_coord == (width_tile_amt / 2) && y_coord == (height_tile_amt / 2) - 2) can_move_u = false;
        // else can_move_u = true;

        // //Bottom
        // if (x_coord == (width_tile_amt / 2) - 1 && y_coord == (height_tile_amt / 2) + 1) can_move_d = false;
        // else if (x_coord == (width_tile_amt / 2) && y_coord == (height_tile_amt / 2) + 1) can_move_d = false;
        // else can_move_d = true;
    }

    if (m_collision_box['l'] == 1 || m_collision_box['L'] == 1) can_move_l = false;
    else can_move_l = true;
}