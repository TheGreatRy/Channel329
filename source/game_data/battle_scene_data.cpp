#include "battle_scene_data.h"

void BattleSceneData::InitializeData()
{
    TextConsole* battle_cons[4]
    {
        new TextConsole(),
        new TextConsole(),
        new TextConsole(),
        new TextConsole()
    };

    Tileset* btt_top_ts = new Tileset(1,1,256,256);
    Tileset* btt_bottom_ts = new Tileset(1,1,256,256);

    Tileset* enemy = new Tileset(1,1,64,64);       
    Tileset* attacker = new Tileset(1,1,30,80);       

    Battle* test_battle = new Battle();

    enemy->LoadTileset({new glImage[enemy->m_img_dimensions]}, talkingnpcPal, talkingnpcBitmap, GL_RGB256, 256);
    attacker->LoadTileset({new glImage[attacker->m_img_dimensions]}, cam_battlePal, cam_battleBitmap, GL_RGB256, 256);
    btt_top_ts->LoadTileset({new glImage[btt_top_ts->m_img_dimensions]}, battle_topPal, battle_topBitmap, GL_RGB256, 256);
    btt_bottom_ts->LoadTileset({new glImage[btt_bottom_ts->m_img_dimensions]}, battle_bottomPal, battle_bottomBitmap, GL_RGB256, 256);
    
    for (int i = 0; i < 4; i++)
    {
        battle_cons[i]->InitializeTextConsole(TEXT_CON_TYPE_SUB_OPT, m_scene->m_main_consoles.size(), m_scene->m_sub_consoles.size(), {new PrintConsole}, 0, BgType_Text4bpp,
        BgSize_T_256x256, i, 3, 4, 0, false, false, &font_cellphone, 1, (i * 4) + 6, 28, 4);
    }
    
    Animation* npc_temp = new Animation(enemy);
    Animation* attack_temp = new Animation(attacker);

    const int16_t screen_map[] = {0};

    Background* battle_top_bg = new Background(2, BgType_Bmp8, BgSize_B8_256x256, 0, 0, false, {new BackgroundData{8, 0, battle_topBitmap, battle_bottomBitmapLen, battle_topPal, battle_bottomPalLen}});
    Background* battle_bottom_bg = new Background(2, BgType_Bmp8, BgSize_B8_256x256, 0, 0, false, {new BackgroundData{8,0, battle_bottomBitmap, battle_bottomBitmapLen, battle_bottomPal, battle_bottomPalLen}});

    Character* npc = new Character(npc_temp, "JOHN NPC", CHARACTER_TYPE_NPC);
    Character* cam_attk = new Character(attack_temp, "CAMERON", CHARACTER_TYPE_NPC);
    
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
    
    npc->AddMultipleTones(npc_tones);
    npc->AddMultipleTopics(npc_topics);
    
    test_battle->AddMultiplePhrases(cam_attack_phrases, 6);
    test_battle->SetDefender(npc);
    test_battle->SetAttacker(cam_attk);
    
    m_scene->AddBattle(test_battle);
    m_scene->AddBackground(battle_top_bg);
    m_scene->AddBackground(battle_bottom_bg);
    m_scene->AddActor(npc);
    m_scene->AddActor(cam_attk);

    for (int i = 0; i < 4; i++)
    {
        m_scene->AddTextConsole(battle_cons[i]);
    }

}