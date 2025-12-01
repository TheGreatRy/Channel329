// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2025

// NDS includes
#include <nds/arm9/dldi.h>

// Engine Folder
#include "engine/game.h"

// Graphics Folder
//Idle Animations
#include "../graphics/characters/cameron/idle/cam_front_idle_spritesheet.h"
#include "../graphics/characters/cameron/idle/cam_back_idle_spritesheet.h"
#include "../graphics/characters/cameron/idle/cam_side_idle_spritesheet.h"

//Walk Animations
#include "../graphics/characters/cameron/walk/cam_front_walk_spritesheet.h"
#include "../graphics/characters/cameron/walk/cam_back_walk_spritesheet.h"
#include "../graphics/characters/cameron/walk/cam_side_walk_spritesheet.h"

//Battle Animations
#include "../graphics/characters/cameron/cam_battle.h"

//Test / Other Graphics
#include "../graphics/characters/talkingnpc.h"

#include "../graphics/test_graphics/tiny_16.h"
#include "../graphics/map/collision.h"
#include "../graphics/backgrounds/battle_bottom.h"
#include "../graphics/backgrounds/battle_top.h"

#include <../graphics/test_graphics/anuvverbubbla_8x8.h>
#include <../graphics/test_graphics/charmap_cellphone.h>
#include <../graphics/test_graphics/charmap_futuristic.h>

//Variables
// Size of a color in bytes
    const size_t size_color = 2;

// Size of a font character in 4 and 8 BPP modes in bytes
const size_t size_char_4bpp = (8 * 8) / 2;
const size_t size_char_8bpp = 8 * 8;

//Main Scene Map
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

//Main Scene Collisions
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

//Fonts
ConsoleFont font_anuvverbubbla = 
{
    .gfx = anuvverbubbla_8x8Tiles,
    .pal = anuvverbubbla_8x8Pal,
    .numColors = anuvverbubbla_8x8PalLen / size_color,
    .bpp = 8,
    .asciiOffset = 32,
    .numChars = anuvverbubbla_8x8TilesLen / size_char_8bpp,
};

ConsoleFont font_cellphone = 
{
    .gfx = charmap_cellphoneTiles,
    .pal = charmap_cellphonePal,
    .numColors = charmap_cellphonePalLen / size_color,
    .bpp = 4,
    .asciiOffset = 32,
    .numChars = charmap_cellphoneTilesLen / size_char_4bpp,
};

ConsoleFont font_futuristic = 
{
    .gfx = charmap_futuristicTiles,
    .pal = charmap_futuristicPal,
    .numColors = charmap_futuristicPalLen / size_color,
    .bpp = 4,
    .asciiOffset = 32,
    .numChars = charmap_futuristicTilesLen / size_char_4bpp,
};

int main(int argc, char **argv)
{
    //create game object and initialize
    Game* game = new Game();

    game->InitializeGame();

    //for now, scenes are created in main
    //in the future, they would get their own header so that I can initialize everything separately instead of all in main

    #pragma region Main Scene
    Scene* demo = new Scene(GM_STATE_MAIN, 0);
    
    //We need to initialize all objects that use a tileset
    TextConsole* text_console = new TextConsole();
    Tileset* town_ts = new Tileset(10, 10, 16, 16);
    Tileset* c_i_ts = new Tileset(4, 1, 16, 16);

    Tileset* cam_front_idle = new Tileset(4, 3, 32, 32);
    Tileset* cam_back_idle = new Tileset(4, 1, 32, 32);
    Tileset* cam_side_idle = new Tileset(4, 3, 32, 32);
    
    Tileset* cam_front_walk = new Tileset(4, 3, 32, 32);
    Tileset* cam_back_walk = new Tileset(4, 1, 32, 32);
    Tileset* cam_side_walk = new Tileset(4, 3, 32, 32);

    //Now that the objects exist, we can load the graphics
    town_ts->LoadTileset({new glImage[town_ts->m_img_dimensions]}, tiny_16Pal, tiny_16Bitmap, GL_RGB256, 256);
    c_i_ts->LoadTileset({new glImage[c_i_ts->m_img_dimensions]}, collisionPal, collisionBitmap, GL_RGB256, 256);
    
    cam_front_idle->LoadTileset({new glImage[cam_front_idle->m_img_dimensions]},cam_front_idle_spritesheetPal, cam_front_idle_spritesheetBitmap, GL_RGB256, 256);
    cam_back_idle->LoadTileset({new glImage[cam_back_idle->m_img_dimensions]},cam_back_idle_spritesheetPal, cam_back_idle_spritesheetBitmap, GL_RGB256, 256);
    cam_side_idle->LoadTileset({new glImage[cam_side_idle->m_img_dimensions]},cam_side_idle_spritesheetPal, cam_side_idle_spritesheetBitmap, GL_RGB256, 256);
    
    cam_front_walk->LoadTileset({new glImage[cam_front_walk->m_img_dimensions]},cam_front_walk_spritesheetPal, cam_front_walk_spritesheetBitmap, GL_RGB256, 256);
    cam_back_walk->LoadTileset({new glImage[cam_back_walk->m_img_dimensions]},cam_back_walk_spritesheetPal, cam_back_walk_spritesheetBitmap, GL_RGB256, 256);
    cam_side_walk->LoadTileset({new glImage[cam_side_walk->m_img_dimensions]},cam_side_walk_spritesheetPal, cam_side_walk_spritesheetBitmap, GL_RGB256, 256);

    //this is a crime im so sorry
    text_console->InitializeTextConsole(TEXT_CON_TYPE_SUB_TALK, demo->m_main_consoles.size(), demo->m_sub_consoles.size(), {new PrintConsole}, 0, BgType_Text4bpp,
    BgSize_T_256x256, 3, 4, 0, false, false, &font_cellphone, 1, 1, 10, 5);
    
    //create animations from loaded l=tilesets
    Animation* cam_idle_f = new Animation(cam_front_idle);
    Animation* cam_idle_b = new Animation(cam_back_idle);
    Animation* cam_idle_s = new Animation(cam_side_idle);
    
    Animation* cam_walk_f = new Animation(cam_front_walk);
    Animation* cam_walk_b = new Animation(cam_back_walk);
    Animation* cam_walk_s = new Animation(cam_side_walk);

    //create scene objects
    Character* cam = new Character(cam_idle_f, "CAMERON", CHARACTER_TYPE_MAIN);
    Map* coll_inter = new Map(c_i_ts, 30, 20, collisions_interaction, MAP_TYPE_COL_INTER);
    Map* town = new Map(town_ts, 30, 20, map, MAP_TYPE_BG_MAIN);

    //add animations to character object
    cam->AddAnimation(cam_idle_b);
    cam->AddAnimation(cam_idle_s);
    cam->AddAnimation(cam_walk_f);
    cam->AddAnimation(cam_walk_b);
    cam->AddAnimation(cam_walk_s);

    //add scene objects now that everything is loaded and added
    //FIFO
    demo->AddMap(coll_inter);
    demo->AddMap(town);
    demo->AddActor(cam);
    demo->AddTextConsole(text_console);
    demo->m_player_object = cam;
    
    #pragma endregion

    //---------- object are deleted between scenes, DO NOT REUSE ----------

    #pragma region Battle Scene
    Scene* battle = new Scene(GM_STATE_BATTLE, 0);
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
        battle_cons[i]->InitializeTextConsole(TEXT_CON_TYPE_SUB_OPT, battle->m_main_consoles.size(), battle->m_sub_consoles.size(), {new PrintConsole}, 0, BgType_Text4bpp,
        BgSize_T_256x256, 3, 4, 0, false, false, &font_cellphone, 1, (i * 4) + 6, 28, 4);
    }
    
    Animation* npc_temp = new Animation(enemy);
    Animation* attack_temp = new Animation(attacker);

    const int16_t screen_map[] = {0};

    Map* top_screen = new Map(btt_top_ts, 1,1, screen_map, MAP_TYPE_BG);
    Map* bottom_screen = new Map(btt_bottom_ts, 1,1, screen_map, MAP_TYPE_BG);
    
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
    
    battle->AddBattle(test_battle);
    battle->AddMap(top_screen);
    battle->AddMap(bottom_screen);
    battle->AddActor(npc);
    battle->AddActor(cam_attk);

    for (int i = 0; i < 4; i++)
    {
        battle->AddTextConsole(battle_cons[i]);
    }
    #pragma endregion

    //add scenes to the game
    game->AddScene(demo);
    game->AddScene(battle);
    
    //run game
    game->RunGame();
    
    delete game;
    
    return 0;
    
}
