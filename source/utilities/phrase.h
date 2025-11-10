#pragma once

//C++ includes
#include <string>

// Utilities Folder
#include "../utilities/tone.h"
#include "../utilities/topic.h"

enum PHRASE_TYPE
{
    PHRASE_TYPE_ATTACK,
    PHRASE_TYPE_DEFEND,
    PHRASE_TYPE_BOSS
};

struct Phrase
{
    public:
    std::string m_text;
    Tone m_tone;
    Topic m_topic;
    PHRASE_TYPE m_type;

    Phrase(std::string text, Tone tone, Topic topic, PHRASE_TYPE type) :
        m_text{text},
        m_tone{tone},
        m_topic{topic},
        m_type{type}
    {}
    ~Phrase() = default;

};