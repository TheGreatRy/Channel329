// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2025

#include "engine/game.h"

//Only uncomment for testing
//#include "test_files/blockds_examples.h"

// Graphics Folder
#include "../graphics/characters/cam.h"
#include "../graphics/test_graphics/tiny_16.h"
#include "../graphics/characters/talkingnpc.h"
#include "../graphics/map/collision.h"
#include <../graphics/test_graphics/anuvverbubbla_8x8.h>
#include <../graphics/test_graphics/charmap_cellphone.h>
#include <../graphics/test_graphics/charmap_futuristic.h>

#include <nds/arm9/dldi.h>

int main(int argc, char **argv)
{
    // Set the DLDI mode
    //dldiSetMode(DLDI_MODE_ARM9); // or DLDI_MODE_AUTODETECT or DLDI_MODE_ARM7

    Game* game = new Game();

    game->InitializeGame();

    Scene* demo = new Scene();
    
    // Size of a color in bytes
    const size_t size_color = 2;
    
    // Size of a font character in 4 and 8 BPP modes in bytes
    const size_t size_char_4bpp = (8 * 8) / 2;
    const size_t size_char_8bpp = 8 * 8;
    
    const int16_t map[30 * 20] = 
    {
        94, 95, 84, 85, 94, 95, 84, 85, 94, 95,  1,  1,  1,  1,  1,  1,  1,  1, 94, 95, 84, 85, 84, 85, 94, 95, 84, 85, 84, 85,
        84, 85, 94, 95, 84, 85, 94, 95,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 94, 95, 94, 95, 84, 85, 94, 95, 94, 95,
        94, 95, 84, 85, 94, 95,  1,  0,  1,  1,  1,  1,  1,  1,  7,  7,  7,  1,  0,  1,  1,  1,  1,  1, 94, 95, 84, 85, 84, 85,
        1,  1, 94, 95,  1,  1,  1,  7,  1,  1,  1,  1,  1,  1,  1,  0,  2,  1,  1,  1,  1,  1,  1,  1,  7,  7, 94, 95, 94, 95,
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  7,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 84, 85,
        1,  1,  7,  0,  1,  1,  1,  1,  1,  1,  7,  2,  1,  1,  1,  7,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 94, 95,
        1,  7,  7,  7,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1, 47, 48, 48, 48, 49,  1,  1,  1,  1,  1,  1,  1,  1,  1, 84,
        0, 17, 18, 18, 18, 18, 18, 18, 19,  1,  1,  1,  1,  1,  1, 57, 58, 58, 58, 59,  1,  1,  1,  1,  0,  1,  1,  1,  1, 94,
        0, 27,  1,  1,  1,  1,  1,  1, 29,  1,  1,  1,  1,  1,  7, 67, 68, 68, 68, 69,  1,  1,  7,  7,  2,  1,  7,  1, 84, 85,
        7, 27,  1,  1,  1,  1,  1,  1, 29,  1,  1,  1,  1,  1,  1, 87, 97, 98, 99, 89,  1,  1,  0,  7,  7,  0,  0,  1, 94, 95,
        7, 27,  1,  1,  1,  1,  1,  1, 29,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1, 84, 85, 84,
        0, 27,  1,  1,  1,  1,  1,  1, 29,  7,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1, 94, 95, 94,
        7, 27,  1,  1,  1,  1,  1,  1, 29,  2,  7,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 84, 85,
        1, 37, 38, 38, 38, 38, 28, 38, 39,  7,  7,  1,  1,  1,  1, 20, 21, 21, 21, 21, 21, 21, 21, 22,  1,  1,  1,  1, 94, 95,
        7,  0,  1,  1,  1,  1,  1,  1,  1,  1,  0,  7,  1,  1,  1, 30, 31, 31, 31, 31, 31, 31, 31, 32,  1,  1,  1,  1, 84, 85,
        0,  7,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1, 20, 44, 31, 31, 31, 31, 31, 31, 31, 43, 22,  1,  2,  1, 94, 95,
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32,  1,  7,  1,  1, 84,
        1,  1,  1,  1,  1,  1,  1,  1,  7,  1,  1,  1,  1, 20, 44, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32,  1,  1,  1,  1, 94,
        1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  0,  1,  1, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 43, 22,  1,  1,  1,  1,
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 20, 44, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32,  1,  1,  1,  1 
    };
    
    const int16_t collisions_interaction[30 * 20] =
    {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
        0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
        0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0
    };
    
    
    ConsoleFont font_anuvverbubbla = {
        .gfx = anuvverbubbla_8x8Tiles,
        .pal = anuvverbubbla_8x8Pal,
        .numColors = anuvverbubbla_8x8PalLen / size_color,
        .bpp = 8,
        .asciiOffset = 32,
        .numChars = anuvverbubbla_8x8TilesLen / size_char_8bpp,
    };
    
    ConsoleFont font_cellphone = {
        .gfx = charmap_cellphoneTiles,
        .pal = charmap_cellphonePal,
        .numColors = charmap_cellphonePalLen / size_color,
        .bpp = 4,
        .asciiOffset = 32,
        .numChars = charmap_cellphoneTilesLen / size_char_4bpp,
    };
    
    ConsoleFont font_futuristic = {
        .gfx = charmap_futuristicTiles,
        .pal = charmap_futuristicPal,
        .numColors = charmap_futuristicPalLen / size_color,
        .bpp = 4,
        .asciiOffset = 32,
        .numChars = charmap_futuristicTilesLen / size_char_4bpp,
    };
    
    //We need to initialize all objects that use a tileset
    TextConsole* text_console = new TextConsole();
    Tileset* cam_ts = new Tileset(1, 1, 32, 32);
    Tileset* town_ts = new Tileset(10, 10, 16, 16);
    Tileset* c_i_ts = new Tileset(4, 1, 16, 16);


    //Now that the objects exist, we can load the graphics
    cam_ts->LoadTileset({new glImage[cam_ts->m_img_dimensions]},camPal, camBitmap, GL_RGB256, 256);
    town_ts->LoadTileset({new glImage[town_ts->m_img_dimensions]}, tiny_16Pal, tiny_16Bitmap, GL_RGB256, 256);
    c_i_ts->LoadTileset({new glImage[c_i_ts->m_img_dimensions]}, collisionPal, collisionBitmap, GL_RGB256, 256);

    //this is a crime im so sorry
    text_console->InitializeTextConsole(TEXT_CON_TYPE_SUB_TALK, demo->m_main_consoles.size(), demo->m_sub_consoles.size(), {new PrintConsole}, 0, BgType_Text4bpp,
    BgSize_T_256x256, 3, 4, 0, false, false, &font_cellphone, 1, 1, 10, 5);
    
    Character* cam = new Character(cam_ts, "CAMERON");
    Map* town = new Map(town_ts, 30, 20, map);
    Map* coll_inter = new Map(c_i_ts, 30, 20, collisions_interaction);

    //FIFO
    demo->AddMap(town);
    demo->AddMap(coll_inter);
    demo->AddActor(cam);
    demo->AddTextConsole(text_console);
    
    //object are deleted between scenes, DO NOT REUSE
    Scene* battle = new Scene();
    TextConsole* battle_console = new TextConsole();

    Tileset* enemy = new Tileset(1,1,64,64);    
    Tileset* cam_att = new Tileset(1, 1, 32, 32);    

    Battle* test_battle = new Battle();

    enemy->LoadTileset({new glImage[enemy->m_img_dimensions]}, talkingnpcPal, talkingnpcBitmap, GL_RGB256, 256);

    cam_att->LoadTileset({new glImage[cam_att->m_img_dimensions]},camPal, camBitmap, GL_RGB256, 256);
    
    battle_console->InitializeTextConsole(TEXT_CON_TYPE_SUB_OPT, battle->m_main_consoles.size(), battle->m_sub_consoles.size(), {new PrintConsole}, 0, BgType_Text4bpp,
    BgSize_T_256x256, 3, 4, 0, false, false, &font_cellphone, 1, 1, 32, 24);
    
    Character* npc = new Character(enemy, "JOHN NPC");
    Character* cam_char_att = new Character(cam_att, "CAMERON");
    
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
    //test_battle->SetAttacker(cam_char_att);
    test_battle->SetDefender(npc);
    
    battle->AddBattle(test_battle);
    battle->AddActor(npc);
    //battle->AddActor(cam_char_att);
    battle->AddTextConsole(battle_console);
    
    game->AddScene(demo);
    game->AddScene(battle);
    
    game->RunGame();
    
    delete game;
    
    return 0;
}
