#pragma once

//C++ Classes
#include <map>

//Actor Folder
#include "../actors/character.h"

//Components Folder
#include "../components/tileset.h"

//Utilities Folder
#include "../utilities/coordinate.h"

//DS screen size
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

enum MAP_TYPE
{
    MAP_TYPE_BG,
    MAP_TYPE_COL_INTER
};

class Map
{
public:


    Map(Tileset* tileset_info, int map_width, int map_height, const int16_t tile_id_arr[], MAP_TYPE map_type);
    ~Map() = default;

    //key = [x,y] / value = tile id
    std::vector<Coordinate<int16_t>*> m_coordinates;

    std::vector<int> m_collision_box;

    Tileset m_tileset_info;
    int m_map_width;
    int m_map_height;
    MAP_TYPE m_map_type;

    void DrawMap(Character* player, int scroll_x, int scroll_y, bool& can_move_u, bool& can_move_d, bool& can_move_l, bool& can_move_r);
};