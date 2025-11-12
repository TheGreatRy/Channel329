#pragma once

// C++ includes
#include <vector>
#include <string>

// Utilities Folder
#include "../utilities/tone.h"
#include "../utilities/topic.h"
#include "../utilities/coordinate.h"

// Componenets Folder
#include "../components/tileset.h"

enum CHARACTER_TYPE
{
    CHARACTER_TYPE_MAIN,
    CHARACTER_TYPE_NPC,
    CHARACTER_TYPE_BOSS
};

class Character
{
public:
    Character() = default;
    Character(Tileset* tileset_info, std::string name);
    ~Character() = default;

    std::string m_name;
    CHARACTER_TYPE m_character_type;
    Coordinate m_draw_position;

    Tileset m_tileset_info;
    std::vector<Tileset *> m_sprite_animations;
    std::vector<Tone*> m_tones;
    std::vector<Topic*> m_topics;

    void AddSingleTone(Tone* tone);
    void AddSingleTopic(Topic* topic);
    
    void AddMultipleTones(Tone* tones[]);
    void AddMultipleTopics(Topic* topics[]);

};