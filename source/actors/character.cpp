#include "character.h"

Character::Character(Tileset* tileset_info, std::string name)
{
    m_tileset_info = *tileset_info;
    m_name = name;
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
