#pragma once

//C++ includes
#include <string>

// Utilities Folder
#include "tone.h"
#include "topic.h"

enum PHRASE_TYPE
{
    PHRASE_TYPE_ATTACK,
    PHRASE_TYPE_DEFEND,
    PHRASE_TYPE_BOSS
};

class Phrase
{
    public:
    std::string m_text;
    TONE_SKILL m_phrase_tone;
    TOPIC_SKILL m_phrase_topic;
    PHRASE_TYPE m_type;

    Phrase(std::string text, TONE_SKILL tone, TOPIC_SKILL topic, PHRASE_TYPE type) :
        m_text{text},
        m_phrase_tone{tone},
        m_phrase_topic{topic},
        m_type{type}
    {}
    ~Phrase() = default;

};