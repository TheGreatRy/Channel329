#pragma once

// NDS includes
#include <nds.h>

// C++ includes
#include <vector>

// Actors Folder
#include "../actors/character.h"

// Utilites Folder
#include "../utilities/phrase.h"

// Engine Folder
#include "text_console.h"


class Battle
{
public:

    Battle(ConsoleFont font)
    {
        // //reserve the last 2 spaces for these graphics
        // m_battle_textbox = new Sprite(SPR_TYPE_3D, "txt/battle_phrase_box", 254, 62, 256, 128, 0);
        // m_battle_textbox->LoadSprite(254, 30, 14, new Position(0.0f, 20.0f), true, 3);

        m_battle_response = new TextConsole();
        m_tone_text = new TextConsole();
        m_topic_text = new TextConsole();

        m_battle_response->InitializeTextConsole(TEXT_CON_TYPE_MAIN_TALK, new PrintConsole, 1, BgType_Text8bpp, BgSize_T_256x256, 0, 3, 0, 0, true, false, 
            &font, 1, 14, 28, 20);
            
        m_tone_text->InitializeTextConsole(TEXT_CON_TYPE_SUB_OPT, new PrintConsole, 0, BgType_Text8bpp, BgSize_T_256x256, 1, 3, 0, 0, false, false, 
            &font, 2, 5, 10, 10);
            
        m_topic_text->InitializeTextConsole(TEXT_CON_TYPE_SUB_OPT, new PrintConsole, 0, BgType_Text8bpp, BgSize_T_256x256, 2, 3, 0, 0, false, false, 
            &font, 2, 10, 10, 10);

        m_battle_response->SetText("WELCOME TO THE BATTLE! IN ORDER TO GET THE INFORMATION YOU NEED, YOU MUST USE THE CORRECT TONE AND TOPIC.\n\nYOU ARE NOT EXPECTED TO KNOW RIGHT AWAY, AS YOUR ARE FINDING WHAT PEOPLE RESPOND BEST TO THROUGHOUT THE GAME", false);
        m_battle_response->DisplayTextConsole(&m_battle_response->m_print_console);

        m_tone_text->SetText("SELECT TONE", false);
        m_tone_text->DisplayTextConsole(&m_tone_text->m_print_console);
        
        m_topic_text->SetText("SELECT TOPIC", false);
        m_topic_text->DisplayTextConsole(&m_topic_text->m_print_console);

        
    }
    ~Battle() = default;

    std::vector<Phrase *> m_attack_phrases;
    std::vector<Phrase *> m_defend_phrases;
    std::vector<Phrase *> m_boss_phrases;
    Character* m_defender;

    Tone* m_attk_tone = new Tone(TONE_SKILL_DEFAULT, TONE_TYPE_NONE);
    Topic* m_attk_topic = new Topic(TOPIC_SKILL_DEFAULT, TOPIC_TYPE_NONE);

    // Sprite* m_battle_textbox;
    // Sprite* m_options_textbox;

    TextConsole* m_battle_response;
    TextConsole* m_tone_text;
    TextConsole* m_topic_text;

    // skip default value
    int m_tone_pos = 1;
    int m_topic_pos = 1;

    bool m_attacker_advantage = false;

    void SetDefender(Character *defender);

    void AddSinglePhrase(Phrase *phrase);
    void AddMultiplePhrases(Phrase *phrases[], int size);

    void CycleTones();
    void CycleTopics();
    void ValidateToneTopicChoice();

    void CheckAttackPhrase();
    void WaitForInput();
};