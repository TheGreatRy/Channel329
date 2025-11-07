#pragma once

//C++ Classes
#include <map>

//Components Folder
#include "tileset.h"

//Utilities Folder
#include "../utilities/coordinate.h"

//DS screen size
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

class Map
{
public:

    //2D Array with stored values
    std::vector<Coordinate<int16_t>*> m_coordinates;

    int m_width;
    int m_height;
    
    Tileset m_layer_info;

    Map(Tileset* layer, int width, int height, const int16_t tile_id_arr[]);
    void DrawMap(int scroll_x, int scroll_y, bool& can_move_u, bool& can_move_d, bool& can_move_l, bool& can_move_r);
    bool CheckCollision(int tile_x_01, int tile_x_02, int adj_x_01, int adj_x_02);
    void CheckOverlap(Tileset* overlap);
};