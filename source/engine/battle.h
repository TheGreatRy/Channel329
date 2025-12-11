#pragma once

// C++ includes
#include <vector>

// Actors Folder
#include "../actors/character.h"

// Utilites Folder
#include "../utilities/phrase.h"

// Engine Folder
#include "text.h"

class Battle
{
public:
    Battle()
    {
        m_battle_response->LoadText(0, 1);
        m_tone_text->LoadText(1, 0);
        m_topic_text->LoadText(1, 1); 

        m_battle_response->AddText("CHOOSE TONE AND TOPIC");
        m_battle_response->WriteText();
        
        m_tone_text->AddText("SELECT");
        m_tone_text->WriteText();

        m_topic_text->AddText("SELECT");
        m_topic_text->WriteText();

        NF_UpdateTextLayers();
    }
    ~Battle() = default;

    std::vector<Phrase *> m_attack_phrases;
    std::vector<Phrase *> m_defend_phrases;
    std::vector<Phrase *> m_boss_phrases;

    Character* m_attacker;
    Character* m_defender;

    Tone* m_attk_tone;
    Topic* m_attk_topic;

    Text* m_battle_response = new Text(TEXT_TYPE_CUST, "fnt/charmap_cellphone", "battle_response", 256, 256, 0, 2.0f, 15.0f);

    Text* m_tone_text = new Text(TEXT_TYPE_CUST, "fnt/charmap_cellphone", "text_tone", 256, 256, 0, 10.0f, 2.0f);
    Text* m_topic_text = new Text(TEXT_TYPE_CUST, "fnt/charmap_cellphone", "text_topic", 256, 256, 0, 10.0f, 8.0f);

    // skip default value
    int m_tone_pos = 1;
    int m_topic_pos = 1;

    bool m_attacker_advantage = false;

    void SetAttacker(Character *attacker);
    void SetDefender(Character *defender);

    void AddSinglePhrase(Phrase *phrase);
    void AddMultiplePhrases(Phrase *phrases[], int size);

    void CycleTones();
    void CycleTopics();

    void CheckAttackPhrase();
    void WaitForInput();
};