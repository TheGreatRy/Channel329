#pragma once

//Game Data Folder
#include "game_data.h"

//Components Folder
#include "../components/Sprite.h"

//Engine Folder
#include "../engine/text_console.h"

// // Graphics Folder
// //Battle Stills / Animations
// #include "../graphics/characters/cameron/battle/cam_battle.h"

// //Test / Other Graphics
// #include "../graphics/characters/talkingnpc.h"
// #include "../graphics/backgrounds/battle_bottom.h"
// #include "../graphics/backgrounds/battle_top.h"

class BattleSceneData : public GameData
{
    public:
    BattleSceneData(Scene* scene)
    {
        m_scene = scene;
    }
    

    Sprite* enemy;    
    Sprite* attacker;     

    Battle* test_battle;

    Animation* npc_temp;
    Animation* attack_temp;

    Background* battle_top_bg;
    Background* battle_bottom_bg;

    Character* npc;
    Character* cam_attk;

    TextConsole* battle_cons[4]
    {
        new TextConsole(),
        new TextConsole(),
        new TextConsole(),
        new TextConsole()
    };
    
    Tone* npc_tones[4] = {
        new Tone{TONE_SKILL_CASUAL, TONE_TYPE_POSITIVE},
        new Tone{TONE_SKILL_DIRECT, TONE_TYPE_NEGATIVE},
        new Tone{TONE_SKILL_PROFESS, TONE_TYPE_NEUTRAL},
        new Tone{TONE_SKILL_AUTHOR, TONE_TYPE_NEUTRAL},
    };
    
    Topic* npc_topics[4] = {
        new Topic{TOPIC_SKILL_PEOPLE, TOPIC_TYPE_KNOWN},
        new Topic{TOPIC_SKILL_CRIME, TOPIC_TYPE_UNKNOWN},
        new Topic{TOPIC_SKILL_HISTORY, TOPIC_TYPE_INDIFF},
        new Topic{TOPIC_SKILL_MAGIC, TOPIC_TYPE_INDIFF},
    };
    
    Phrase* cam_attack_phrases[6] = {
        //defender wins (neg)
        new Phrase{"Tell me everything you know about this person", TONE_SKILL_DIRECT, TOPIC_SKILL_PEOPLE, PHRASE_TYPE_ATTACK},
        //defender wins (neutral and indiff)
        new Phrase{"Hello Mx. I wanted to ask if you knew anything about how magic works?", TONE_SKILL_PROFESS, TOPIC_SKILL_MAGIC, PHRASE_TYPE_ATTACK},
        //defender wins (neutral and unknown)
        new Phrase{"I request you give any information regarding the crime in this area", TONE_SKILL_AUTHOR, TOPIC_SKILL_CRIME, PHRASE_TYPE_ATTACK},
        //attacker wins (positive and indiff)
        new Phrase{"Hey buddy, great town right? I wonder how it came to be... say, do you know anything about this town?", TONE_SKILL_CASUAL, TOPIC_SKILL_HISTORY, PHRASE_TYPE_ATTACK},
        //defender wins (positive and unknown)
        new Phrase{"Hey buddy, this town seems pretty peaceful... I wonder if it was always like that?", TONE_SKILL_CASUAL, TOPIC_SKILL_CRIME, PHRASE_TYPE_ATTACK},
        //attacker wins (positive and known)
        new Phrase{"Hey buddy, do you get around often? I'd love to know more about the people here.", TONE_SKILL_CASUAL, TOPIC_SKILL_HISTORY, PHRASE_TYPE_ATTACK},
    };
    

    void InitializeData();
};