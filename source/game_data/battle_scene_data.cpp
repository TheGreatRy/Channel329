#include "battle_scene_data.h"

void BattleSceneData::InitializeData()
{
    enemy = new Sprite(SPR_TYPE_3D, "sprite/cam_battle_neut", 0, 0, 128, 128);       
    attacker = new Sprite(SPR_TYPE_3D,"sprite/john_tutorial", 1, 1, 128, 128);       
    test_battle = new Battle();

    enemy->LoadSprite(0, 0, 0, {new Position(20.0f, 10.0f)}, false, 0);
    attacker->LoadSprite(1,1,1, {new Position(100.0f, 10.0f)}, false, 0);
    
    // for (int i = 0; i < 3; i++)
    // {
    //     battle_cons[i]->InitializeTextConsole(TEXT_CON_TYPE_SUB_OPT, m_scene->m_main_consoles.size(), m_scene->m_sub_consoles.size(), {new PrintConsole}, 
    //     0, BgType_Text4bpp, BgSize_T_256x256, i, i + 1, 4, 0, false, false, &font_cellphone, 1, (i * 4) + 6, 28, 4);
    // }
    
    npc_temp = new Animation(enemy, 1);
    attack_temp = new Animation(attacker, 1);

    battle_top_bg = new Background(BG_TYPE_TILED_FULL, "bg/battle_top");
    battle_bottom_bg = new Background(BG_TYPE_8BIT, "bmp/battle_bottom");

    npc = new Character(npc_temp, "JOHN NPC", CHARACTER_TYPE_NPC);
    cam_attk = new Character(attack_temp, "CAMERON", CHARACTER_TYPE_NPC);
    
    battle_top_bg->LoadBackground(0, 3);
    battle_bottom_bg->LoadBackground(1, 2, 1);

    npc->AddMultipleTones(npc_tones);
    npc->AddMultipleTopics(npc_topics);
    
    test_battle->AddMultiplePhrases(cam_attack_phrases, 6);
    test_battle->SetDefender(npc);
    test_battle->SetAttacker(cam_attk);
    
    // for (int i = 0; i < 4; i++)
    // {
    //     m_scene->AddTextConsole(battle_cons[i]);
    // }

    m_scene->AddBattle(test_battle);
    m_scene->AddBackground(battle_top_bg);
    m_scene->AddBackground(battle_bottom_bg);
    m_scene->AddActor(npc);
    m_scene->AddActor(cam_attk);
}