#include "battle_scene_data.h"

void BattleSceneData::InitializeData()
{
    //Initialize objects
    enemy = new Sprite(SPR_TYPE_3D, "sprite/cam_battle_neut", 0, 0, 128, 128);       
    attacker = new Sprite(SPR_TYPE_3D,"sprite/john_tutorial", 1, 1, 128, 128);       
    test_battle = new Battle(font_anuvverbubbla);

    battle_top_bg = new Background(BG_TYPE_TILED_FULL, "bg/battle_top");
    battle_bottom_bg = new Background(BG_TYPE_8BIT, "bmp/battle_bottom");

    //Add data to objects
    enemy->LoadSprite(0, 0, 0, {new Position(20.0f, 10.0f)}, true, 2);
    attacker->LoadSprite(1, 1, 1, {new Position(100.0f, 10.0f)}, true, 2);
    
    battle_top_bg->LoadBackground(0, 3);
    battle_bottom_bg->LoadBackground(1, 3, 1);

    //create objects that depends on the ones above
    npc_temp = new Animation(enemy, 1);
    attack_temp = new Animation(attacker, 1);

    npc = new Character(npc_temp, "JOHN NPC", CHARACTER_TYPE_NPC);
    cam_attk = new Character(attack_temp, "CAMERON", CHARACTER_TYPE_NPC);
    
    npc->AddMultipleTones(npc_tones);
    npc->AddMultipleTopics(npc_topics);

    test_battle->AddMultiplePhrases(cam_attack_phrases, 7);
    test_battle->AddMultiplePhrases(defender_phrases, 6);

    test_battle->SetDefender(npc);
    test_battle->SetAttacker(cam_attk);

    //Add everything to the scene
    m_scene->AddBattle(test_battle);
    m_scene->AddBackground(battle_top_bg);
    m_scene->AddBackground(battle_bottom_bg);

    m_scene->AddActor(npc);
    m_scene->AddActor(cam_attk);
}