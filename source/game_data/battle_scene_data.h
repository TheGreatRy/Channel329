#pragma once

//Game Data Folder
#include "game_data.h"

//Components Folder
#include "../components/sprite.h"

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
    
    Phrase* cam_attack_phrases[7] = {
        //defender wins (neg)
        new Phrase{"TELL ME EVERYTHING YOU KNOW ABOUT THIS PERSON", TONE_SKILL_DIRECT, TOPIC_SKILL_PEOPLE, PHRASE_TYPE_ATTACK},
        //defender wins (unknown)
        new Phrase{"I REQUEST YOU GIVE ANY INFORMATION REGARDING CRIME IN THIS AREA", TONE_SKILL_AUTHOR, TOPIC_SKILL_CRIME, PHRASE_TYPE_ATTACK},
        //defender wins (unknown)
        new Phrase{"HEY BUDDY, THIS TWON SEEMS PRETTY PEACEFUL... I WONDER IF IT WAS ALWAYS LIKE THAT?", TONE_SKILL_CASUAL, TOPIC_SKILL_CRIME, PHRASE_TYPE_ATTACK},
        //attacker wins (positive and indiff)
        new Phrase{"HEY BUDDY, GREAT TOWN, RIGHT? I WONDER HOW IT CAME TO BE... SAY, DO YOU KNOW ANYTHING ABOUT THIS TOWN?", TONE_SKILL_CASUAL, TOPIC_SKILL_HISTORY, PHRASE_TYPE_ATTACK},
        //attacker wins (positive and known)
        new Phrase{"HEY BUDDY, DO YOU GET AROUND OFTEN? I'D LOVE TO HEAR MORE ABOUT THE PEOPLE HERE.", TONE_SKILL_CASUAL, TOPIC_SKILL_PEOPLE, PHRASE_TYPE_ATTACK},
        //defender wins (neutral and indiff)
        new Phrase{"HELLO MX. I WANTED TO ASK IF YOU KNEW ANYTHING ABOUT HOW MAGIC WORKS?", TONE_SKILL_PROFESS, TOPIC_SKILL_MAGIC, PHRASE_TYPE_ATTACK},
        //defender wins (neutral and known)
        new Phrase{"HELLO, I AM AN INVESTIGATOR, AND I WOULD LIKR TO INTERVIEW YOU ABOUT THE PEOPLE OF THIS TOWN.", TONE_SKILL_PROFESS, TOPIC_SKILL_PEOPLE, PHRASE_TYPE_ATTACK}
    };
    
    Phrase* defender_phrases[6] = {
        //defender wins (neg)
        new Phrase{"That's pretty rude, buster!", TONE_SKILL_DIRECT, TOPIC_SKILL_PEOPLE, PHRASE_TYPE_DEFEND},
        //defender wins (unknown)
        new Phrase{"I don't know anything about that...", TONE_SKILL_AUTHOR, TOPIC_SKILL_CRIME, PHRASE_TYPE_DEFEND},
        //(KnPos)
        new Phrase{"Oh sure! There's my neighbor Tony... and my other neighbor Toni...", TONE_SKILL_CASUAL, TOPIC_SKILL_PEOPLE, PHRASE_TYPE_DEFEND},
        //(KnNt)
        new Phrase{"Hmmm, well there are a lot of people in this town and I don't them all, but...", TONE_SKILL_PROFESS, TOPIC_SKILL_PEOPLE, PHRASE_TYPE_DEFEND},
        //(InPos)
        new Phrase{"Not really, but Sally down south would know more!", TONE_SKILL_CASUAL, TOPIC_SKILL_HISTORY, PHRASE_TYPE_DEFEND},
        //(InNt)
        new Phrase{"Ah, I'm not the best at magic, sorry...", TONE_SKILL_PROFESS, TOPIC_SKILL_MAGIC, PHRASE_TYPE_DEFEND}
    };
    

    void InitializeData();
};