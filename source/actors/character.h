#pragma once

// C++ includes
#include <vector>

// Componenets Folder
#include "../components/tileset.h"

class Character
{
public:
    Character(Tileset* tileset_info);
    ~Character() = default;

    Tileset m_tileset_info;
    std::vector<Tileset *> m_sprites;
};