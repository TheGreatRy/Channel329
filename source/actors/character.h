#pragma once

// C++ includes
#include <vector>
#include <string>

// Utilities Folder
#include "../utilities/tone.h"
#include "../utilities/topic.h"
#include "../utilities/coordinate.h"

// Componenets Folder
#include "../components/sprite.h"
#include "../components/animation.h"

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
    Character(Animation* main_animation, std::string name, CHARACTER_TYPE character_type);
    ~Character() = default;

    std::string m_name;
    CHARACTER_TYPE m_character_type;

    std::vector<Animation*> m_sprite_animations;
    std::vector<Tone*> m_tones;
    std::vector<Topic*> m_topics;

    void AddSingleTone(Tone* tone);
    void AddSingleTopic(Topic* topic);
    
    void AddMultipleTones(Tone* tones[]);
    void AddMultipleTopics(Topic* topics[]);

    void AddAnimation(Animation* animation);
    void PlayAnimation(int anim_id, int fps, bool flip_sprites);
};