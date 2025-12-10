#include "character.h"

Character::Character(Animation* main_animation, std::string name, CHARACTER_TYPE character_type)
{
    m_sprite_animations.push_back(main_animation);   
    m_name = name;
    m_character_type = character_type;
}

void Character::AddSingleTone(Tone *tone)
{
    m_tones.push_back(tone);
}

void Character::AddSingleTopic(Topic *topic)
{
    m_topics.push_back(topic);
}

void Character::AddMultipleTones(Tone *tones[])
{
    for (int i = 0; i < sizeof(tones)/sizeof(*tones); i++)
    {
        AddSingleTone(tones[i]);
    }
}

void Character::AddMultipleTopics(Topic *topics[])
{
    for (int i = 0; i < sizeof(topics)/sizeof(*topics); i++)
    {
        AddSingleTopic(topics[i]);
    }
}

void Character::AddAnimation(Animation *animation)
{
    m_sprite_animations.push_back(animation);
}

void Character::PlayAnimation(int anim_id, int fps, bool flip_sprites)
{
    m_sprite_animations[anim_id]->PlayAnimation(fps, flip_sprites);
}

void Character::PlayAnimation(int anim_id, int fps, bool flip_sprites, int scroll_x, int scroll_y)
{   
    m_sprite_animations[anim_id]->PlayAnimation(fps, flip_sprites, scroll_x, scroll_y);
}
