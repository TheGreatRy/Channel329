// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2025


// Engine Folder
#include "engine/game.h"

//Game Data Folder
#include "game_data/main_data.h"

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

#include "../graphics/backgrounds/battle_bottom.h"
#include "../graphics/backgrounds/battle_top.h"
#include "../graphics/backgrounds/tutorial_bottom.h"
#include "../graphics/backgrounds/tutorial_top.h"
#include "../graphics/text_display/battle_phrase_box.h"

const int16_t background_map[1] = {0};


//Test Variables
#pragma region Ortho Proj
// void draw_box(float bx_, float by_, float bz_, float ex_, float ey_, float ez_)
// {
//     // Begin and end coordinates
//     int bx = floattov16(bx_);
//     int ex = floattov16(ex_);
//     int by = floattov16(by_);
//     int ey = floattov16(ey_);
//     int bz = floattov16(bz_);
//     int ez = floattov16(ez_);

//     glBegin(GL_QUADS);

//         glColor3f(1, 0, 0);

//         glVertex3v16(bx, by, bz);
//         glVertex3v16(bx, ey, bz);
//         glVertex3v16(ex, ey, bz);
//         glVertex3v16(ex, by, bz);

//         glColor3f(0, 1, 0);

//         glVertex3v16(bx, by, ez);
//         glVertex3v16(bx, ey, ez);
//         glVertex3v16(ex, ey, ez);
//         glVertex3v16(ex, by, ez);

//         glColor3f(0, 0, 1);

//         glVertex3v16(bx, by, bz);
//         glVertex3v16(bx, by, ez);
//         glVertex3v16(ex, by, ez);
//         glVertex3v16(ex, by, bz);

//         glColor3f(1, 0, 1);

//         glVertex3v16(bx, ey, bz);
//         glVertex3v16(bx, ey, ez);
//         glVertex3v16(ex, ey, ez);
//         glVertex3v16(ex, ey, bz);

//         glColor3f(0, 1, 1);

//         glVertex3v16(bx, by, bz);
//         glVertex3v16(bx, by, ez);
//         glVertex3v16(bx, ey, ez);
//         glVertex3v16(bx, ey, bz);

//         glColor3f(1, 1, 0);

//         glVertex3v16(ex, by, bz);
//         glVertex3v16(ex, by, ez);
//         glVertex3v16(ex, ey, ez);
//         glVertex3v16(ex, ey, bz);

//     glEnd();
// }

#pragma endregion

int main(int argc, char **argv)
{
    //Test Methods
    #pragma region Ortho Test
    // // Setup sub screen for the text console
    // consoleDemoInit();

    // videoSetMode(MODE_0_3D);

    // glInit();

    // glEnable(GL_ANTIALIAS);

    // // The background must be fully opaque and have a unique polygon ID
    // // (different from the polygons that are going to be drawn) so that
    // // antialias works.
    // glClearColor(0, 0, 0, 31);
    // glClearPolyID(63);

    // glClearDepth(0x7FFF);

    // glViewport(0, 0, 255, 191);

    // int angle_x = 0;
    // int angle_z = 0;

    // float x = 0.0;
    // float y = 0.0;
    // float z = 0.0;

    // while (1)
    // {
    //     // Synchronize game loop to the screen refresh
    //     swiWaitForVBlank();

    //     // Print some text in the demo console
    //     // -----------------------------------

    //     consoleClear();

    //     // Print some controls
    //     printf("PAD:     Move\n");
    //     printf("A,B,X,Y: Rotate\n");
    //     printf("SELECT:  Perspective/Ortho\n");
    //     printf("START:   Exit to loader\n");
    //     printf("\n");

    //     // Handle user input
    //     // -----------------

    //     scanKeys();

    //     uint16_t keys = keysHeld();

    //     if (keys & KEY_LEFT)
    //         x -= 0.05;
    //     if (keys & KEY_RIGHT)
    //         x += 0.05;

    //     if (keys & KEY_UP)
    //         y += 0.05;
    //     if (keys & KEY_DOWN)
    //         y -= 0.05;

    //     if (keys & KEY_A)
    //         angle_x += 3;
    //     if (keys & KEY_Y)
    //         angle_x -= 3;

    //     if (keys & KEY_X)
    //         angle_z += 3;
    //     if (keys & KEY_B)
    //         angle_z -= 3;

    //     if (keys & KEY_START)
    //         break;

    //     // Render 3D scene
    //     // ---------------

    //     glMatrixMode(GL_PROJECTION);
    //     glLoadIdentity();

    //     if (keys & KEY_SELECT)
    //         gluPerspective(70, 256.0 / 192.0, 0.1, 40);
    //     else
    //         glOrtho(-3, 3, -2, 2, 0.1, 100);

    //     glMatrixMode(GL_MODELVIEW);
    //     glLoadIdentity();
    //     gluLookAt(0.0, 0.0, 4.0,  // Position
    //               0.0, 0.0, 0.0,  // Look at
    //               0.0, 1.0, 0.0); // Up

    //     glTranslatef(x, y, z);

    //     glRotateY(angle_z);
    //     glRotateX(angle_x);

    //     glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);

    //     draw_box(-0.75, -0.75, -0.75,
    //              0.75, 0.75, 0.75);

    //     glFlush(0);
    // }

    // return 0;
    #pragma endregion
   
    //create game object and initialize
    Game* game = new Game();

    game->InitializeGame();

    //for now, scenes are created in main
    //in the future, they would get their own header so that I can initialize everything separately instead of all in main
    //---------- object are deleted between scenes, DO NOT REUSE ----------//

    #pragma region Tutorial Scene

    // Scene* tutorial_scene = new Scene(GM_STATE_TITLE, 0);
    // TextConsole* main_screen_text = new TextConsole();

    // main_screen_text->InitializeTextConsole(TEXT_CON_TYPE_MAIN_TALK, tutorial_scene->m_main_consoles.size(), tutorial_scene->m_sub_consoles.size(), 
    // {new PrintConsole}, 1, BgType_Text4bpp, BgSize_T_256x256, 3, 0, 0, true, false, &font_cellphone, 1, 1, 10, 5);

    // main_screen_text->SetText("Hello! Welcome to the demo of Channel329: Crimes of the Magically Inclined.\n\nThis demo is meant to represent a proof of concept for the game, so there are some hotkeys to trigger certain things.\n\nControls:\n- D-Pad: Movement\n- A: Trigger Battle\n- B: Menu", false);
    
    // tutorial_scene->AddTextConsole(main_screen_text);

    #pragma endregion

    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
    
    #pragma region Main Scene
    
    MainData* main_data = new MainData();

    main_data->InitializeMain();
    game->AddScene(main_data->main_scene);


    #pragma endregion
    
    #pragma region Battle Scene
    // Scene* battle = new Scene(GM_STATE_BATTLE, 0);
    // TextConsole* battle_cons[4]
    // {
    //     new TextConsole(),
    //     new TextConsole(),
    //     new TextConsole(),
    //     new TextConsole()
    // };

    
    // // Background* battle_top_bg = new Background(2, BgType_Bmp8, BgSize_B8_256x256, 0, 0, false);
    // // Background* battle_bottom_bg = new Background(2, BgType_Bmp8, BgSize_B8_256x256, 0, 0, false);

    // Tileset* enemy = new Tileset(1,1,64,64);       
    // Tileset* attacker = new Tileset(1,1,30,80);       

    // Battle* test_battle = new Battle();

    // enemy->LoadTileset({new glImage[enemy->m_img_dimensions]}, talkingnpcPal, talkingnpcBitmap, GL_RGB256, 256);
    // attacker->LoadTileset({new glImage[attacker->m_img_dimensions]}, cam_battlePal, cam_battleBitmap, GL_RGB256, 256);
    
    // // battle_top_bg->LoadBackground(0, battle_topBitmap, battle_bottomBitmapLen, battle_topPal, battle_bottomPalLen);
    // // battle_bottom_bg->LoadBackground(0, battle_bottomBitmap, battle_bottomBitmapLen, battle_bottomPal, battle_bottomPalLen);

    // for (int i = 0; i < 4; i++)
    // {
    //     battle_cons[i]->InitializeTextConsole(TEXT_CON_TYPE_SUB_OPT, battle->m_main_consoles.size(), battle->m_sub_consoles.size(), {new PrintConsole}, 0, BgType_Text4bpp,
    //     BgSize_T_256x256, 2, 3, 4, 0, false, false, &font_cellphone, 1, (i * 4) + 6, 28, 4);
    // }

    // Animation* npc_temp = new Animation(enemy);
    // Animation* attack_temp = new Animation(attacker);
    
    // Character* npc = new Character(npc_temp, "JOHN NPC", CHARACTER_TYPE_NPC);
    // Character* cam_attk = new Character(attack_temp, "CAMERON", CHARACTER_TYPE_NPC);
    
    // Tone* npc_tones[4] = {
    //     new Tone{TONE_SKILL_CASUAL, TONE_TYPE_POSITIVE},
    //     new Tone{TONE_SKILL_DIRECT, TONE_TYPE_NEGATIVE},
    //     new Tone{TONE_SKILL_PROFESS, TONE_TYPE_NEUTRAL},
    //     new Tone{TONE_SKILL_AUTHOR, TONE_TYPE_NEUTRAL},
    // };
    
    // Topic* npc_topics[4] = {
    //     new Topic{TOPIC_SKILL_PEOPLE, TOPIC_TYPE_KNOWN},
    //     new Topic{TOPIC_SKILL_CRIME, TOPIC_TYPE_UNKNOWN},
    //     new Topic{TOPIC_SKILL_HISTORY, TOPIC_TYPE_INDIFF},
    //     new Topic{TOPIC_SKILL_MAGIC, TOPIC_TYPE_INDIFF},
    // };
    
    // Phrase* cam_attack_phrases[6] = {
    //     //defender wins (neg)
    //     new Phrase{"Tell me everything you know about this person", TONE_SKILL_DIRECT, TOPIC_SKILL_PEOPLE, PHRASE_TYPE_ATTACK},
    //     //defender wins (neutral and indiff)
    //     new Phrase{"Hello Mx. I wanted to ask if you knew anything about how magic works?", TONE_SKILL_PROFESS, TOPIC_SKILL_MAGIC, PHRASE_TYPE_ATTACK},
    //     //defender wins (neutral and unknown)
    //     new Phrase{"I request you give any information regarding the crime in this area", TONE_SKILL_AUTHOR, TOPIC_SKILL_CRIME, PHRASE_TYPE_ATTACK},
    //     //attacker wins (positive and indiff)
    //     new Phrase{"Hey buddy, great town right? I wonder how it came to be... say, do you know anything about this town?", TONE_SKILL_CASUAL, TOPIC_SKILL_HISTORY, PHRASE_TYPE_ATTACK},
    //     //defender wins (positive and unknown)
    //     new Phrase{"Hey buddy, this town seems pretty peaceful... I wonder if it was always like that?", TONE_SKILL_CASUAL, TOPIC_SKILL_CRIME, PHRASE_TYPE_ATTACK},
    //     //attacker wins (positive and known)
    //     new Phrase{"Hey buddy, do you get around often? I'd love to know more about the people here.", TONE_SKILL_CASUAL, TOPIC_SKILL_HISTORY, PHRASE_TYPE_ATTACK},
    // };
    
    // npc->AddMultipleTones(npc_tones);
    // npc->AddMultipleTopics(npc_topics);
    
    // test_battle->AddMultiplePhrases(cam_attack_phrases, 6);
    // test_battle->SetDefender(npc);
    // test_battle->SetAttacker(cam_attk);
    
    // // battle->AddBackground(battle_top_bg);
    // // battle->AddBackground(battle_bottom_bg);

    // battle->AddBattle(test_battle);
    // battle->AddActor(npc);
    // battle->AddActor(cam_attk);

    // for (int i = 0; i < 4; i++)
    // {
    //     battle->AddTextConsole(battle_cons[i]);
    // }

    
    #pragma endregion
    
    //game->AddScene(tutorial_scene);
    //game->AddScene(battle);

    //run game
    game->RunGame();
    
    delete game;
    
    return 0;
    
}
