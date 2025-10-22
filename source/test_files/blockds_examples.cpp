#include "blockds_examples.h"
#include "dsinput_print.h"


void BlockDSExamples::InputTests()
{
    PrintConsole topScreen;
    PrintConsole bottomScreen;

    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankC(VRAM_C_SUB_BG);

    consoleInit(&topScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
    consoleInit(&bottomScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
    consoleSelect(&topScreen);

    bool init_ok = fatInitDefault();
    if (!init_ok)
    {
        perror("fatInitDefault()");
        wait_forever();
    }

    printf("Testing input. Please press any key");
    printf("\n");
    printf("START will exit the program");
    printf("\n");

    consoleSelect(&bottomScreen);

    while (1)
    {
        PrintDSInput *getInput = new PrintDSInput();

        swiWaitForVBlank();

        scanKeys();

        if (keysHeld() & KEY_START)
            break;

        else if (keysHeld() & static_cast<KEYPAD_BITS>(keysHeld()))
        {
            getInput->printInput(static_cast<KEYPAD_BITS>(keysHeld()));
            printf(" was held!\n");
        }
    }
}

void BlockDSExamples::BGScroll2D()
{
    // Use a video mode that sets layer 0 as a regular tiled background. Mode 0
    // sets all 4 layers as regular tiled backgrounds.
    videoSetMode(MODE_0_2D);

    // Designate VRAM A as memory for main engine backgrounds. This gives us 128
    // KB in total.
    vramSetBankA(VRAM_A_MAIN_BG);

    // Initialize layer 0 as a regular (text) background with 256 colors (8 bpp)
    // and size 256x256. The last 0 is the map base and the 1 is the tile base.
    // We'll talk about that in a minute.
    int bg = bgInit(0, BgType_Text8bpp, BgSize_T_256x256, 0, 1);

    // Copy tiles and tile map to VRAM
    dmaCopy(forest_townTiles, bgGetGfxPtr(bg), forest_townTilesLen);
    dmaCopy(forest_townMap, bgGetMapPtr(bg), forest_townMapLen);

    // Copy palete to palette RAM
    dmaCopy(forest_townPal, BG_PALETTE, forest_townPalLen);

    consoleDemoInit();

    printf("PAD:   Scroll background\n");
    printf("START: Exit to loader\n");

    int x = 0, y = 0;

    while (1)
    {
        swiWaitForVBlank();

        bgSetScroll(bg, x, y);

        bgUpdate();

        scanKeys();

        u16 keys_held = keysHeld();

        if (keys_held & KEY_UP)
            y--;
        else if (keys_held & KEY_DOWN)
            y++;

        if (keys_held & KEY_LEFT)
            x--;
        else if (keys_held & KEY_RIGHT)
            x++;

        if (keys_held & KEY_START)
            break;
    }
}

void BlockDSExamples::LayerMovement()
{
    // Enable 3D
    videoSetMode(MODE_0_3D);

    // Setup some VRAM as memory for main engine background, main engine
    // sprites, and 3D textures.
    vramSetPrimaryBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE,
                        VRAM_C_TEXTURE, VRAM_D_TEXTURE);

    // Setup console in the sub screen
    vramSetBankH(VRAM_H_SUB_BG);
    consoleDemoInit();

    // Setup 2D background
    // ===================

    int bg = bgInit(2, BgType_Text8bpp, BgSize_T_256x256, 0, 4);
    bgSetPriority(bg, 2);

    dmaCopy(cityTiles, bgGetGfxPtr(bg), cityTilesLen);
    dmaCopy(cityMap, bgGetMapPtr(bg), cityMapLen);
    dmaCopy(cityPal, BG_PALETTE, cityPalLen);

    // Setup 2D sprites
    // ================

    oamInit(&oamMain, SpriteMapping_1D_32, false);

    oamEnable(&oamMain);

    // Allocate space for the tiles and copy them there
    u16 *gfxMain = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(ballTiles, gfxMain, ballTilesLen);

    // Copy palette
    dmaCopy(ballPal, SPRITE_PALETTE, ballPalLen);

    oamSet(&oamMain, 0,
           100, 50,                                      // X, Y
           0,                                            // Priority
           0,                                            // Palette index
           SpriteSize_32x32, SpriteColorFormat_256Color, // Size, format
           gfxMain,                                      // Graphics offset
           -1,                                           // Affine index
           false,                                        // Double size
           false,                                        // Hide
           false, false,                                 // H flip, V flip
           false);                                       // Mosaic

    oamSet(&oamMain, 1,
           150, 70,                                      // X, Y
           0,                                            // Priority
           0,                                            // Palette index
           SpriteSize_32x32, SpriteColorFormat_256Color, // Size, format
           gfxMain,                                      // Graphics offset
           -1,                                           // Affine index
           false,                                        // Double size
           false,                                        // Hide
           false, false,                                 // H flip, V flip
           false);                                       // Mosaic

    // Setup 3D
    // ========

    glInit();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ANTIALIAS);

    // IMPORTANT: The 3D background must be transparent (alpha = 0) so that the
    // 2D layers behind it can be seen.
    glClearColor(0, 0, 0, 0);
    glClearPolyID(63);

    glClearDepth(0x7FFF);

    glViewport(0, 0, 255, 191);

    int textureID;

    // Load texture
    glGenTextures(1, &textureID);
    glBindTexture(0, textureID);
    if (glTexImage2D(0, 0, GL_RGBA, 128, 128, 0, TEXGEN_TEXCOORD, neonBitmap) == 0)
    {
        printf("Failed to load texture\n");
        while (1)
            swiWaitForVBlank();
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, 256.0 / 192.0, 0.1, 40);

    gluLookAt(0.0, 0.0, 2.0,  // Position
              0.0, 0.0, 0.0,  // Look at
              0.0, 1.0, 0.0); // Up

    // Setup done
    // ==========

    int angle_x = 0;
    int angle_z = 0;
    int bg_x = 150, bg_y = 70;
    int spr_x = 150, spr_y = 70;

    while (1)
    {
        // Synchronize game loop to the screen refresh
        swiWaitForVBlank();

        bgSetScroll(bg, bg_x, bg_y);
        bgUpdate();

        oamSetXY(&oamMain, 1, spr_x, spr_y);

        oamUpdate(&oamMain);

        // Print some text in the demo console
        // -----------------------------------

        consoleClear();

        // Print some controls
        printf("R + PAD: Rotate quad\n");
        printf("L + PAD: Scroll background\n");
        printf("X + PAD: Move sprite\n");
        printf("START:   Exit to loader\n");
        printf("\n");

        // Handle user input
        // -----------------

        scanKeys();

        uint16_t keys = keysHeld();

        if (keys & KEY_R)
        {
            if (keys & KEY_LEFT)
                angle_z += 3;
            if (keys & KEY_RIGHT)
                angle_z -= 3;

            if (keys & KEY_UP)
                angle_x += 3;
            if (keys & KEY_DOWN)
                angle_x -= 3;
        }

        if (keys & KEY_L)
        {
            if (keys & KEY_UP)
                bg_y--;
            else if (keys & KEY_DOWN)
                bg_y++;

            if (keys & KEY_LEFT)
                bg_x--;
            else if (keys & KEY_RIGHT)
                bg_x++;
        }

        if (keys & KEY_X)
        {
            if (keys & KEY_UP)
                spr_y--;
            else if (keys & KEY_DOWN)
                spr_y++;

            if (keys & KEY_LEFT)
                spr_x--;
            else if (keys & KEY_RIGHT)
                spr_x++;
        }

        if (keys & KEY_START)
            break;

        // Render 3D scene
        // ---------------

        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();

        glRotateZ(angle_z);
        glRotateX(angle_x);

        glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);

        glBindTexture(0, textureID);

        glColor3f(1, 1, 1);

        glBegin(GL_QUADS);

        GFX_TEX_COORD = (TEXTURE_PACK(0, inttot16(128)));
        glVertex3v16(floattov16(-1), floattov16(-1), 0);

        GFX_TEX_COORD = (TEXTURE_PACK(inttot16(128), inttot16(128)));
        glVertex3v16(floattov16(1), floattov16(-1), 0);

        GFX_TEX_COORD = (TEXTURE_PACK(inttot16(128), 0));
        glVertex3v16(floattov16(1), floattov16(1), 0);

        GFX_TEX_COORD = (TEXTURE_PACK(0, 0));
        glVertex3v16(floattov16(-1), floattov16(1), 0);

        glEnd();

        glPopMatrix(1);

        glFlush(0);
    }

    glDeleteTextures(1, &textureID);

    oamFreeGfx(&oamMain, gfxMain);
}

void BlockDSExamples::Object3D()
{
    glInit();
    consoleDemoInit();

    videoSetMode(MODE_0_3D);

    // Setup the rear plane
    glClearColor(0, 0, 0, 0); // Set BG to black
    // The BG and polygons will have the same ID unless a polygon is highlighted
    glClearPolyID(0);
    glClearDepth(0x7FFF);

    // Setup the camera
    gluLookAt(0.0, 0.0, 4.0,  // Camera position
              0.0, 0.0, 0.0,  // Look at
              0.0, 1.0, 0.0); // Up

    // Setup the light
    glLight(0, RGB15(31, 31, 31),
            floattov10(0.58), floattov10(-0.58), floattov10(-0.58));

    // Set the viewport to fullscreen
    glViewport(0, 0, 255, 191);

    // Setup the projection matrix for regular drawing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 256.0 / 192.0, 0.1, 20);

    // Use the modelview matrix while drawing
    glMatrixMode(GL_MODELVIEW);

    // Define two ranges in the table. The first range is for pixels with less
    // than half the maximum light intensity, and the second one is for pixels
    // that have over half the maximum light intensity. This way the regular
    // smooth shading is reduced to two shades.
    glSetToonTableRange(0, 15, RGB15(8, 8, 8));
    glSetToonTableRange(16, 31, RGB15(28, 28, 28));

    // Setup some material properties
    glMaterialf(GL_AMBIENT, RGB15(8, 8, 8));
    glMaterialf(GL_DIFFUSE, RGB15(24, 24, 24));
    glMaterialf(GL_SPECULAR, RGB15(0, 0, 0));
    glMaterialf(GL_EMISSION, RGB15(0, 0, 0));

    u32 rotateX = 0;
    u32 rotateY = 0;

    printf("PAD: Rotate\n");
    printf("A: Disable toon shading\n");
    printf("START: Exit to loader\n");

    while (1)
    {
        // Handle key input
        scanKeys();
        u16 keys = keysHeld();
        if (keys & KEY_UP)
            rotateX += 3 << 5;
        if (keys & KEY_DOWN)
            rotateX -= 3 << 5;
        if (keys & KEY_LEFT)
            rotateY += 3 << 5;
        if (keys & KEY_RIGHT)
            rotateY -= 3 << 5;

        if (keys & KEY_A)
            glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK | POLY_FORMAT_LIGHT0 |
                      POLY_ID(0) | POLY_DECAL);
        else
            glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK | POLY_FORMAT_LIGHT0 |
                      POLY_ID(0) | POLY_TOON_HIGHLIGHT);

        glPushMatrix();
        {
            glRotateXi(rotateX);
            glRotateYi(rotateY);

            glCallList(teapot_bin);
        }
        glPopMatrix(1);

        glFlush(0);

        swiWaitForVBlank();

        if (keys & KEY_START)
            break;
    }
}

void BlockDSExamples::TilesetBG(Character character)
{
    consoleDemoInit();

    int tileset_texture_id =
        glLoadTileSet(tileset,         // Pointer to glImage array
                      16,              // Sprite width
                      16,              // Sprite height
                      16 * 10,         // Bitmap width (the part that contains useful images)
                      16 * 10,         // Bitmap height (the part that contains useful images)
                      GL_RGB256,       // Texture type for glTexImage2D()
                      256,             // Full texture size X (image size)
                      256,             // Full texture size Y (image size)
                      TEXGEN_TEXCOORD, // Parameters for glTexImage2D()
                      256,             // Length of the palette to use (256 colors)
                      tiny_16Pal,      // Pointer to texture palette data
                      tiny_16Bitmap);  // Pointer to texture data

    if (tileset_texture_id < 0)
        printf("Failed to load texture: %d\n", tileset_texture_id);

    // Print some controls
    printf("PAD:    Scroll\n");
    printf("START:  Exit to loader\n");
    printf("\n");

    int scroll_x = 0;
    int scroll_y = 0;

    glImage character_arr[]{character.m_frames_num};

    for (int i = 0; i < character.m_frames_num; i++)
    {
        character_arr[i] = character.m_frames_img[i];
    }

    while (1)
    {
        // Synchronize game loop to the screen refresh
        swiWaitForVBlank();

        // Handle user input
        // -----------------

        scanKeys();

        

        uint16_t keys = keysHeld();
        if (keys & KEY_START)
            break;

        if (keys & KEY_UP)
            scroll_y++;
        if (keys & KEY_DOWN)
            scroll_y--;

        if (keys & KEY_LEFT)
            scroll_x++;
        if (keys & KEY_RIGHT)
            scroll_x--;

        // Render 3D scene
        // ---------------

        // Set up GL2D for 2D mode
        glBegin2D();

        glColor(RGB15(31, 31, 31));
        glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);

        // This code could be made more intelligent by only drawing the
        // tiles that are actually shown on the screen. That would reduce
        // the number of polygons that are sent to the GPU and improve
        // performance.
        for (int j = 0; j < MAP_HEIGHT; j++)
        {
            for (int i = 0; i < MAP_WIDTH; i++)
            {
                int x = scroll_x + i * 16;
                int y = scroll_y + j * 16;
                int tile_id = map[j * MAP_WIDTH + i];

                glSprite(x, y, GL_FLIP_NONE, &tileset[tile_id]);
            }
        }
        
        

        glSprite((screen_width / 2) - (character.m_sprite_w / 2), (screen_height / 2) - (character.m_sprite_h / 2), GL_FLIP_NONE, &character_arr[0]);

        glEnd2D();

        glFlush(0);
    }

    glDeleteTextures(1, &tileset_texture_id);
    glDeleteTextures(1, &character.m_texture_id);
}

void BlockDSExamples::TilesetSprite()
{
    consoleDemoInit();

    // //Initialize OpenGL to some sensible defaults
    // glScreen2D();

    // videoSetMode(MODE_0_3D);

    // //Setup some memory to be used for textures and for texture palettes
    // vramSetBankA(VRAM_A_TEXTURE);
    // vramSetBankE(VRAM_E_TEX_PALETTE);

    // A tile set is formed by several images of the same size that start at the
    // top left corner. It increses to the right in the top row until the end of
    // the texture is reached, then it continues to the second row.
    //
    // When all the images are put together they form a bitmap with some
    // dimensions. The dimensions can be whatever is required for that specific
    // sprite, with no restrictions.
    //
    // However, the GPU of the DS requires textures to have sizes that are power
    // of two. When you have a bitmap with dimensions that aren't a power of
    // two, padding needs to be added to the bottom and to the right to fill the
    // image up to a valid size.
    //
    // Note that if you leave enough space on the right of the texture for a new
    // image, even if there aren't graphics there, it will count.
    int character_texture_id =
        glLoadTileSet(character, // Pointer to glImage array
                      22,        // Sprite width
                      64,        // Sprite height
                      22 * 6,    // Bitmap width (the part that contains useful images)
                      64,        // Bitmap height (the part that contains useful images)
                      GL_RGB256, // Texture type for glTexImage2D()
                      256,       // Full texture size X (image size)
                      64,        // Full texture size Y (image size)
                      // Parameters for glTexImage2D()
                      TEXGEN_TEXCOORD | GL_TEXTURE_COLOR0_TRANSPARENT,
                      256,          // Length of the palette to use (256 colors)
                      advntPal,     // Pointer to texture palette data
                      advntBitmap); // Pointer to texture data

    if (character_texture_id < 0)
        printf("Failed to load texture: %d\n", character_texture_id);

    // Print some controls
    printf("START:  Exit to loader\n");
    printf("\n");

    int delay = 0;
    int frame = 0;

    while (1)
    {
        // Synchronize game loop to the screen refresh
        swiWaitForVBlank();

        // Handle user input
        // -----------------

        scanKeys();

        uint16_t keys = keysHeld();
        if (keys & KEY_START)
            break;

        // Render 3D scene
        // ---------------

        // Set up GL2D for 2D mode
        glBegin2D();

        // Fill screen with a gradient
        glBoxFilledGradient(0, 0,
                            screen_width - 1, screen_height - 1,
                            RGB15(31, 0, 0),
                            RGB15(31, 31, 0),
                            RGB15(31, 0, 31),
                            RGB15(0, 31, 31));

        // Draw sprite frames individually
        glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_ID(0));
        glColor(RGB15(31, 31, 31));

        for (int i = 0; i < 6; i++)
        {
            int x = i * 24;
            int y = i * 5;
            glSprite(x, y, GL_FLIP_NONE, &character[i]);
        }

        // Draw animated sprite
        glSprite(200, 0, GL_FLIP_NONE, &character[frame]);

        // Animate (change animation frame every 10 frames)
        delay++;
        if (delay == 10)
        {
            delay = 0;

            frame++;
            if (frame == 6)
                frame = 0;
        }

        // Draw a rotated and scaled sprite
        glSpriteRotateScaleXY(40, 150,                          // Position
                              32767 / 8,                        // Rotation = 45 degrees (full circle / 8)
                              floattof32(1.2), floattof32(0.8), // Scale X and Y
                              GL_FLIP_NONE, &character[0]);

        glEnd2D();

        glFlush(0);
    }

    glDeleteTextures(1, &character_texture_id);
}